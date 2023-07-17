/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	- Minor Component -Fighter Brain-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
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

	//#####-- AIBrain for 'FIGHTER' Class --#####

void Q_COREFunctions::AIFighterBrain(int AIcount)
	{
	switch(Forge[AIcount].Q_Brain.MindState)
		{

		case 0:   //IdleMode
			{
			LoopON = 0;

			Forge[AIcount].Mposestate = 0;
			} break;

		case 1:   //ActiveModeInit		//Functionise these 'Modes'
			{
			LoopON = 0;

			Forge[AIcount].idlemotion=0;

			printf("TRACE ActiveModeInit\n");

			if(Forge[AIcount].Mposestate == 0 && Forge[AIcount].blendamount[8] == 1)
				{
				Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
				Forge[AIcount].Mposestate = 0;
				Forge[AIcount].blendamount[8] = 0;
				Forge[AIcount].blendamount[0] = 0;
				Forge[AIcount].AttackIdle = 2000;
				Forge[AIcount].Q_Brain.idlecnt = 10;	//(float)rand() / 32767) - 0.5);
				}

			Forge[AIcount].Blocking = 1;
			Forge[AIcount].BlockHeight = 3;


			Forge[AIcount].Mposestate = 50;
			} break;

		case 2:   //ActiveMode
			{
			LoopON = 0;

			if(Forge[AIcount].Q_Brain.idlecnt == 0) Forge[AIcount].Q_Brain.idlecnt--;//choose random movement
			else Forge[AIcount].Q_Brain.idlecnt--;
			//Decide whether or not to execute a movement
			//or to change mode

			printf("TRACE ActiveMode\n");

			//Loop\|/\|/\|/\|/\|/\|/

			//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;

			//=*=- Lock On
				//Turn to Face Avatar
			/*Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng;
			if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
			if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng);
			Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);*/

			if(Forge[AIcount].Q_Brain.TargetLOCK == 1)
				{
				Forge[AIcount].Q_Brain.MindState = MIND_CRUNCHDECIDE;
				}
			else
				{
				Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
				}



			//If Target Sighted Log in Memory Bank

			//Continue Movement

			//Loop\|/\|/\|/\|/\|/\|/

			} break;

		case 3:   //Check Vision	//TODO Full look around - Motion Required - Cleric Glance
			{
			//LoopON = 1;

				printf("TRACE Check Vision\n");

			/*if(Q.AIFunctionsScannerCheck(AIcount) == TRUE)	 //## Avatar Sighted ##
				{
					//#####Create Memory
				//Check for Attack Lock
				if(Forge[AIcount].Q_Brain.MeMLock = 1) Forge[AIcount].Q_Brain.MeMcurrent = Forge[AIcount].Q_Brain.ATTMmemID;
				else Forge[AIcount].Q_Brain.MeMcurrent = Forge[AIcount].Q_Brain.MeMcount;

				//TimeStamp
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Time = TIME;

				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].EventType = EVENT_AVATAR_SIGHTED;

				//Avatars Data
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].AI_ID = 250;	// Player Sighted TODO Something
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].MeMMindstate = -1;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].Pos = playerAV.Xform.Translation;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].Pos.y += 65;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].Ang = playerAV.Ang;

				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].VecTo = Forge[AIcount].ScanVecTo;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].Forge[AIcount].ScanTurnAng = Forge[AIcount].ScanTurnAng;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[0].ScanDist = Forge[AIcount].ScanAvatarDist;

				//Own Data
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMMindstate = Forge[AIcount].Q_Brain.MindState;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Pos = Forge[AIcount].AV.Xform.Translation;
				Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Ang = Forge[AIcount].AV.Ang;
				//Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Health = Forge[AIcount].AV.
				//Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Power = 
				//Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].PowerLevel = 
				//Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].Weapon = 

					//####Act on Sighting
				//Forge[AIcount].Q_Brain.MindState = //MIND_CRUNCHDECIDE;
				Forge[AIcount].Q_Brain.TargetLOCK = 1;
				Forge[AIcount].Q_Brain.MeMLock = 1;
				Forge[AIcount].Q_Brain.ATTMmemID = Forge[AIcount].Q_Brain.MeMcurrent;

				Forge[AIcount].Q_Brain.MeMcount++;
				}
			else
				{
				//Forge[AIcount].Q_Brain.MindState = MIND_SEARCHTARGET;
				Forge[AIcount].Q_Brain.TargetLOCK = 0;
				Forge[AIcount].Q_Brain.MeMLock = 0;
				Forge[AIcount].Q_Brain.MeMcurrent = Forge[AIcount].Q_Brain.MeMcount;
				}

			//Return
			Forge[AIcount].Q_Brain.MindState = Forge[AIcount].Q_Brain.StateMemory;*/
			} break;

		case 4:   //AttackMode
			{
			LoopON = 0;

				//Basic Ideas

				//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;

			printf("TRACE AttackMode\n");


			//=*=- Lock On
				//Turn to Face Avatar

			Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng;
			if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
			if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng);
			Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);

				//Run Towards Avatar

			Forge[AIcount].ForwardSpeed = 10*TimeScale;//Forge[AIcount].PlayerSpeed*TimeScale;  //Run Forwards
			
			if(Forge[AIcount].Mposestate != 3 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//Movement mode switch
				{
				Forge[AIcount].Mposestate = 3;
				Forge[AIcount].StepTimer = 0;
				//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
				//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
				//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
				//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
				//Forge[AIcount].runposecnt = 0;
				//Forge[AIcount].idleposecnt = 0;
				}

			Forge[AIcount].Running = 1;

			//*** Actor
			Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
			Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
			Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
			Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

			Forge[AIcount].AV.OldPos.y += 60;
			Forge[AIcount].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL, 
						 NULL, 
						 &Forge[AIcount].AV.OldPos, 
						 &Forge[AIcount].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS,
						 0xffffffff, NULL, NULL, 
						 &Forge[AIcount].AV.Collision))
				{
				// Set the new pos to the point of collision
				//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
				Forge[AIcount].collide = 1;
				}

			Forge[AIcount].AV.OldPos.y -= 60;
			Forge[AIcount].AV.NewPos.y -= 60;
		
			// Set the player to the new pos
			if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;
			} break;


		case 5:   //SearchMode
			{
			LoopON = 0;

				//Basic Ideas

			Forge[AIcount].Mposestate = 0;

				//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;

			printf("TRACE SearchMode\n");


			//=*=- Lock On
				//Turn to Face Avatar

			Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng;
			if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
			if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng);
			Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);

				/*Run Towards Avatar

			Forge[AIcount].ForwardSpeed = 5*TimeScale;//Forge[AIcount].PlayerSpeed*TimeScale;  //Run Forwards
			
			if(Forge[AIcount].Mposestate != 3 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//Movement mode switch
				{
				Forge[AIcount].Mposestate = 3;
				Forge[AIcount].StepTimer = 0;
				Forge[AIcount].blendamount[0] = 0; //Optimise me pls
				Forge[AIcount].blendamount[1] = 0; //Optimise me pls
				Forge[AIcount].blendamount[2] = 0; //Optimise me pls
				Forge[AIcount].blendamount[3] = 0; //Optimise me pls
				Forge[AIcount].runposecnt = 0;
				Forge[AIcount].idleposecnt = 0;
				}

			//*** Actor
			Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
			Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
			Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
			Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

			Forge[AIcount].AV.OldPos.y += 60;
			Forge[AIcount].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL, 
						 NULL, 
						 &Forge[AIcount].AV.OldPos, 
						 &Forge[AIcount].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
						 0xffffffff, NULL, NULL, 
						 &Forge[AIcount].AV.Collision))
				{
				// Set the new pos to the point of collision
				Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
				}
			
			Forge[AIcount].AV.OldPos.y -= 60;
			Forge[AIcount].AV.NewPos.y -= 60;
		
			// Set the player to the new pos
			Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;*/

			} break;


		case 6:   //First Crunch Decision
			{
			LoopON = 0;

			//IMP initialisation requires timer to be reset

			printf("TRACE First Crunch Decision\n");

				//Basic Ideas

			Forge[AIcount].Mposestate = 0;
			Forge[AIcount].idlemotion = 23;

				//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;

			//=*=- Lock On
				//Turn to Face Avatar
			Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng;
			if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
			if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng);
			Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);


			//################################################################
			//Case Switch involving a weighted random factor
			//'Logic table' to run through factor possibilities for each event

			//Factor out possibilities with 'if' trees

			//Reset Pathway Factors
			Forge[AIcount].Q_Brain.CRDecide.F_RunA = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_Comm = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_Obtain = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_Power = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_LongR = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_Hand2H = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_AttPlan = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_Delay = 0;
			Forge[AIcount].Q_Brain.CRDecide.F_GoCrazy = 0;


			//Run Away
			//If(Health too low etc).....

			//Communicate
			//If(Radio exists).....

			//Obtain Item
			//If(Item needed and exists <- check memory.....

			//Power Up
			//If(Powering Up was at all possible

			//Long Range
			if(Forge[AIcount].ScanAvatarDist > 170) Forge[AIcount].Q_Brain.CRDecide.F_LongR = 500;
			//else Forge[AIcount].Q_Brain.CRDecide.F_LongR = 0;

			//Hand To Hand
			if(Forge[AIcount].ScanAvatarDist < 170) Forge[AIcount].Q_Brain.CRDecide.F_Hand2H = 500;
			else Forge[AIcount].Q_Brain.CRDecide.F_Hand2H = 200;

			//Delay decision
			if(Forge[AIcount].Q_Brain.CRDecide.Timer < 500) Forge[AIcount].Q_Brain.CRDecide.F_Delay = 100 - Forge[AIcount].Q_Brain.CRDecide.Timer;

			
			//Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


			//IMP increase number of added factors here to include new modes
			Forge[AIcount].Q_Brain.CRDecide.FactorSUM = Forge[AIcount].Q_Brain.CRDecide.F_LongR
											+ Forge[AIcount].Q_Brain.CRDecide.F_Hand2H
											+ Forge[AIcount].Q_Brain.CRDecide.F_Delay;


				//###Seed the finger
			Forge[AIcount].Q_Brain.CRDecide.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.CRDecide.FactorSUM;


			//###Determine Result
				//Long Range
			if(Forge[AIcount].Q_Brain.CRDecide.Finger > 0 && Forge[AIcount].Q_Brain.CRDecide.Finger < Forge[AIcount].Q_Brain.CRDecide.F_LongR) Forge[AIcount].Q_Brain.CRDecide.Answer = 0;

				//Hand To Hand
			if(Forge[AIcount].Q_Brain.CRDecide.Finger > Forge[AIcount].Q_Brain.CRDecide.F_LongR
				&& Forge[AIcount].Q_Brain.CRDecide.Finger < ( Forge[AIcount].Q_Brain.CRDecide.F_LongR + Forge[AIcount].Q_Brain.CRDecide.F_Hand2H ) ) Forge[AIcount].Q_Brain.CRDecide.Answer = 1;

				//Delay Decision
			if(Forge[AIcount].Q_Brain.CRDecide.Finger > ( Forge[AIcount].Q_Brain.CRDecide.F_LongR + Forge[AIcount].Q_Brain.CRDecide.F_Hand2H )
				&& Forge[AIcount].Q_Brain.CRDecide.Finger < ( Forge[AIcount].Q_Brain.CRDecide.F_LongR + Forge[AIcount].Q_Brain.CRDecide.F_Hand2H + Forge[AIcount].Q_Brain.CRDecide.F_Delay ) ) Forge[AIcount].Q_Brain.CRDecide.Answer = 2;


			switch(Forge[AIcount].Q_Brain.CRDecide.Answer)
				{
				case 0:	//Long Range
					{
					Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
					//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
					} break;

				case 1:	//Hand To Hand
					{
					Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
					//Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
					//Forge[AIcount].Q_Brain.MoveEncount = 1;
					} break;

				case 2:	//Delay
					{
					//Still Nothing
					} break;
				}

			Forge[AIcount].Q_Brain.CRDecide.Timer++;

			//################################################################

			} break;


		case 7:   //###===--- Hand To Hand Attack
			{
			LoopON = 0;

			Forge[AIcount].idlemotion = 37;

			printf("TRACE Hand To Hand Attack\n");

			//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;


			//###Lock On
				//Turn to Face Avatar Conditional (Not in Hit Reaction)
			if(Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
				{

				//####### -  Mode Universal Avatar Control - Update if required for mode specific Control -#####

				//##### Turn to Face Avatar - Target in View
				if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
					{
					if(Forge[AIcount].Aposestate != 13)
						{
						Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng/1.5;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng/1.5);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);
						}
					else
						{
						Forge[AIcount].Angles.y += (Forge[AIcount].ScanTurnAng / 1.5) + 0.07;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, (Forge[AIcount].ScanTurnAng / 1.5) + 0.07);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);
						}


					//##### Drop target if dead
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockID].Health <= 0)
						{
						Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
						Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
						Forge[AIcount].Q_Brain.HeadAngles.x = 0;
						Forge[AIcount].Q_Brain.HeadSearch = 0;
						Forge[AIcount].Q_Brain.HeadDir = 1;
						Forge[AIcount].Q_Brain.HeadAngles.x = 0;
						Forge[AIcount].Q_Brain.MeMLock = 0;
						Forge[AIcount].Q_Brain.TargetLOCK = 0;
						Forge[AIcount].Q_Brain.TargetLOCKID = 0;
						Forge[AIcount].Q_Brain.TargetSIGHT = 0;
						Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
						Forge[AIcount].Q_Brain.TargetLOST = 0;
						Forge[AIcount].Q_Brain.TargetWENTltr = 0;
						Forge[AIcount].Q_Brain.TargetWENTutd = 0;
						Forge[AIcount].Q_Brain.TargetFIND = 0;
						Forge[AIcount].Q_Brain.ATTMmemID = 0;
						//Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
						Forge[AIcount].Mposestate = 0;
						Forge[AIcount].blendamount[8] = 0;
						Forge[AIcount].blendamount[0] = 0;
						Forge[AIcount].AttackIdle = 2000;
						Forge[AIcount].Q_Brain.idlecnt = 10;
						Forge[AIcount].Aposestate = 0;
						Forge[AIcount].attackon = 0;

						if(Forge[AIcount].Aposestate != 100 && Forge[AIcount].AirBorn == 0)
							{
							Forge[AIcount].Aposestate = 100;
							Forge[AIcount].attackon = 1;
							Forge[AIcount].attposecnt = 0;
							Forge[AIcount].astackcnt = 0;
							Forge[AIcount].astackrun = 0;
							Forge[AIcount].astackcntdir[0] = 0;
							}
						}

					//### Activate Timed Search
					if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 20)
						{ Forge[AIcount].Q_Brain.TargetSPOTTED = 1; }

					Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
					Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
					Forge[AIcount].Q_Brain.PERFECTTENtimer = 0;
					Forge[AIcount].Q_Brain.HeadAngles.x = 0;
					Forge[AIcount].Q_Brain.HeadSearch = 0;
					Forge[AIcount].Q_Brain.HeadDir = 1;
					Forge[AIcount].Q_Brain.HeadAngles.x = 0;

					Forge[AIcount].Q_Brain.TargetFIND = 0;
					}
				else //##### Turn to Face Avatar - Target Vanished
					{
					if(Forge[AIcount].Q_Brain.TargetLOCK == 1)
						{

						//##### - PERFECT TEN TIMED TARGET LOCK SYSTEM - #####

						if(Forge[AIcount].Q_Brain.PERFECTTENtimer < 10)
							{
							if(Forge[AIcount].Q_Brain.TargetLOCKID == 250)
								{
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV.Xform.Translation;
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							else
								{
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos = Forge[Forge[AIcount].Q_Brain.TargetLOCKID].AV.Xform.Translation;
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}

							if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > Forge[AIcount].AV.Xform.Translation.y + 300)
								{	//# Switch to Long Range Attack
								Forge[AIcount].WeaponAimer = 1.7;
								Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
								//### Set Note to return when enemy Lands
								Forge[AIcount].Q_Brain.MODERETURN_H2H = 1;
								}
							}

						Forge[AIcount].Q_Brain.PERFECTTENtimer++;


						//#### Turn To PERFECT Enemy Position
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Left);
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);
						Qpo->Vec3d_Copy(&Forge[AIcount].AV.Left, &Forge[AIcount].AV.Right);
						Qpo->Vec3d_Inverse(&Forge[AIcount].AV.Right);

						TempVec1 = Forge[AIcount].AV.Xform.Translation;
						TempVec1.y += 65;

						Qpo->Vec3d_Subtract(&Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos, &TempVec1, &Forge[AIcount].ScanVecTo);
						Qpo->Vec3d_Normalize(&Forge[AIcount].ScanVecTo);

						Qpo->Vec3d_Subtract(&Forge[AIcount].AV.Up, &Forge[AIcount].ScanVecTo, &ScanTurnVec);
						Forge[AIcount].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
						Forge[AIcount].ScanTurnAng /= 2;

						ScanDistL = Qpo->Vec3d_DistanceBetween(&Forge[AIcount].ScanVecTo, &Forge[AIcount].AV.Left);
						ScanDistR = Qpo->Vec3d_DistanceBetween(&Forge[AIcount].ScanVecTo, &Forge[AIcount].AV.Right);

						if(ScanDistL < ScanDistR) Forge[AIcount].ScanTurnAng *= -1;

						Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng / 3;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);


						Forge[AIcount].Q_Brain.TargetLOSTtimer++;
						Forge[AIcount].Q_Brain.TargetHIDEtimer++;


							//### Timed Search End
						if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 150 && Forge[AIcount].Q_Brain.TargetSPOTTED == 1)
							{ Forge[AIcount].Q_Brain.TargetSPOTTED = 0; }

							//### Conditional Target Lost
						if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 50)
							{
							Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
							Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
							Forge[AIcount].Q_Brain.HeadAngles.x = 0;
							Forge[AIcount].Q_Brain.HeadSearch = 0;
							Forge[AIcount].Q_Brain.HeadDir = 1;
							Forge[AIcount].Q_Brain.HeadAngles.x = 0;
							Forge[AIcount].Q_Brain.MeMLock = 0;
							Forge[AIcount].Q_Brain.TargetLOCK = 0;
							Forge[AIcount].Q_Brain.TargetLOCKID = 0;
							Forge[AIcount].Q_Brain.TargetSIGHT = 0;
							Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
							Forge[AIcount].Q_Brain.TargetLOST = 0;
							Forge[AIcount].Q_Brain.TargetWENTltr = 0;
							Forge[AIcount].Q_Brain.TargetWENTutd = 0;
							Forge[AIcount].Q_Brain.TargetFIND = 0;
							Forge[AIcount].Q_Brain.ATTMmemID = 0;
							Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
							Forge[AIcount].Mposestate = 0;
							Forge[AIcount].blendamount[8] = 0;
							Forge[AIcount].blendamount[0] = 0;
							Forge[AIcount].AttackIdle = 2000;
							Forge[AIcount].Q_Brain.idlecnt = 10;
							Forge[AIcount].Aposestate = 0;
							Forge[AIcount].attackon = 0;
							break;
							}


						if(Forge[AIcount].Q_Brain.TargetSPOTTED == 0)
							{
							if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
								{
								if(Forge[AIcount].Q_Brain.TargetHIDEtimer > 50)
									{

									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.25 > -(PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.25;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.25 < (PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.25;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}

									if(Forge[AIcount].Q_Brain.HeadAngles.x < 0.05 && Forge[AIcount].Q_Brain.HeadAngles.x > -0.05)
										Forge[AIcount].Q_Brain.TargetHIDEtimer = 50;

									Forge[AIcount].Q_Brain.HeadSearch = 1;
									}
								}


							if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetLOST == 1)	//Target Moves From View
								{
								if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetWENTltr == 1)
									{
									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.4 > -(PI/1.5) ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.4;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.4 <= 0 ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.4;
										else 
											{
											if(Forge[AIcount].Aposestate != 100 && Forge[AIcount].AirBorn == 0)
												{
												Forge[AIcount].Aposestate = 100;
												Forge[AIcount].attackon = 1;
												Forge[AIcount].attposecnt = 0;
												Forge[AIcount].astackcnt = 0;
												Forge[AIcount].astackrun = 0;
												Forge[AIcount].astackcntdir[0] = 0;
												}
											}
										}
									}


								if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetWENTltr == 2)
									{
									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.4 < (PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.4;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.4 >= 0 ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.4;
										else 
											{
											if(Forge[AIcount].Aposestate != 100)
												{
												Forge[AIcount].Aposestate = 100;
												Forge[AIcount].attackon = 1;
												Forge[AIcount].attposecnt = 0;
												Forge[AIcount].astackcnt = 0;
												Forge[AIcount].astackrun = 0;
												Forge[AIcount].astackcntdir[0] = 0;
												}
											}
										}
									}

								Forge[AIcount].Q_Brain.HeadSearch = 1;
								}//END Target Lost 1

							}//END Target Spotted

						}//END TargetLOCK

					}//END Else - TargetLOCK

				}//END Conditional - Hit Reaction



			//####### -  intelligence Cycle

			//#### TODO Conditionally Activate  Attack Plans
			//##### Focus Power Control Possible Time Bending

			Forge[AIcount].Q_Brain.Focus += 0.1;

			Forge[AIcount].Q_Brain.Aggression += 0.1;

			
			//##### Testing Mind Modes
			if(Forge[AIcount].Q_Brain.TestKEY1 == 1) Forge[AIcount].Q_Brain.Aggression = 100;
			else Forge[AIcount].Q_Brain.Aggression = 0;

			if(Forge[AIcount].Q_Brain.TestKEY2 == 1) Forge[AIcount].Q_Brain.Focus = 100;
			else Forge[AIcount].Q_Brain.Focus = 0;

			if(Forge[AIcount].Q_Brain.TestKEY3 == 1) Forge[AIcount].Q_Brain.FocusON = 1;
			else Forge[AIcount].Q_Brain.FocusON = 0;


			//TEMPORARY AGGRESSION ZAP
			//Forge[AIcount].Q_Brain.Aggression = 0;


			//### Stabilise Aggression
			if(Forge[AIcount].Q_Brain.Aggression > 100) Forge[AIcount].Q_Brain.Aggression = 100;
			if(Forge[AIcount].Q_Brain.Aggression < 0) Forge[AIcount].Q_Brain.Aggression = 0;

			//### Stabilise Focus
			if(Forge[AIcount].Q_Brain.Focus > 100) Forge[AIcount].Q_Brain.Focus = 100;
			if(Forge[AIcount].Q_Brain.Focus < 0) Forge[AIcount].Q_Brain.Focus = 0;

			if(Forge[AIcount].Q_Brain.FocusON == 1) Forge[AIcount].Q_Brain.Focus -= 0.25;


			//### Simple Distance Check -- With Mode Switch and Full Reset

			if(Forge[AIcount].Q_Brain.TargetLOCK == 1 && Forge[AIcount].Q_Brain.TargetSIGHT == 1)
				{
				if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 120)
					{
					if(Forge[AIcount].Q_Brain.Aggression > 50)
						{
						Forge[AIcount].Q_Brain.MindMODE = MMODE_CLOSE_AGGRESSION;
						}
					else
						{
						Forge[AIcount].Q_Brain.MindMODE = MMODE_CLOSE_DEFENSE;
						}
					}

				if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120)
					{
					if(Forge[AIcount].Q_Brain.Aggression > 50)
						{
						Forge[AIcount].Q_Brain.MindMODE = MMODE_MID_AGGRESSION;
						}
					else
						{
						Forge[AIcount].Q_Brain.MindMODE = MMODE_MID_DEFENSE;
						}
					}
				}


			//####### -  Mind Mode Switch

			switch(Forge[AIcount].Q_Brain.MindMODE)
				{

				case 0:	   //#=- Attack Plan Control
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						Forge[AIcount].Q_Brain.MoveEncount = 1;
						Forge[AIcount].astackcnt = 0;
						Forge[AIcount].astackrun = 0;
						Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

						if(Forge[AIcount].Q_Brain.EnergySTOP == 0)
							{
							Forge[AIcount].Q_Brain.EnergySTOP = 1;
							Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
							Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Forge[AIcount].Q_Brain.Decision.ON = 1;
							}
						}


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Forge[AIcount].Q_Brain.MoveEncount == 1 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
						{
						//###Run Towards Avatar

						Forge[AIcount].ForwardSpeed = 10*TimeScale;
						if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
						Forge[AIcount].Mposestate = 3;
						Forge[AIcount].Running = 1;

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 //GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}
						
						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
						
							
						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						//Attack position not achieved yet
						Forge[AIcount].Q_Brain.ATTposON = 0;
						Forge[AIcount].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Forge[AIcount].astackcnt = 0;
						//Forge[AIcount].astackrun = 0;
						//Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Forge[AIcount].Running = 0;
						Forge[AIcount].Q_Brain.MoveEncount = 0;
						Forge[AIcount].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Forge[AIcount].Q_Brain.ATTinitiated = 1;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Forge[AIcount].attackon == 0*/ && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Forge[AIcount].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Forge[AIcount].astackrun > 0)
								{
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Forge[AIcount].BlockInit == 0)
							{
							Forge[AIcount].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Forge[AIcount].LEVELFactor) + 8)))
								{
								Forge[AIcount].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Forge[AIcount].BlockHeightMeM != Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Forge[AIcount].LEVELFactor) + 7)))
										{
										Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
										}
									}
								else
									{
									Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Forge[AIcount].Blocking = 0;
						Forge[AIcount].BlockInit = 0;

						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 20;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 21;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 22;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 23;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Forge[AIcount].attackon == 1 && ( TIME >= Forge[AIcount].Q_Brain.STOPCNT + 200 ) )
						{
						Forge[AIcount].Q_Brain.STOPCNT = TIME;
						Forge[AIcount].Q_Brain.SpecialSTOP = 0;
						Forge[AIcount].Q_Brain.RunAttSTOP = 0;
						Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
						Forge[AIcount].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Forge[AIcount].Q_Brain.CollSTOPCNT + 100 )
						{
						Forge[AIcount].Q_Brain.CollSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Forge[AIcount].Q_Brain.HitSTOPCNT + 30 )
						{
						Forge[AIcount].Q_Brain.HitSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Forge[AIcount].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Forge[AIcount].LEVEL > 0 ) && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 ) && ( Forge[AIcount].Q_Brain.MoveEncount == 0 ) )
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 6) + 8))	//4 + 2
								{
								Forge[AIcount].Q_Brain.SpecialSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Forge[AIcount].Q_Brain.Decision.Finger <= 2) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 2 && Forge[AIcount].Q_Brain.Decision.Finger <= 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 4 && Forge[AIcount].Q_Brain.Decision.Finger <= 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Forge[AIcount].Q_Brain.Decision.Finger > 6 && Forge[AIcount].Q_Brain.Decision.Finger <= 10) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 10 && Forge[AIcount].Q_Brain.Decision.Finger <= 15) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 15 && Forge[AIcount].Q_Brain.Decision.Finger <= 20) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 20 && Forge[AIcount].Q_Brain.Decision.Finger <= 25) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 25 && Forge[AIcount].Q_Brain.Decision.Finger <= 30) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 30 && Forge[AIcount].Q_Brain.Decision.Finger <= 35) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 35 && Forge[AIcount].Q_Brain.Decision.Finger <= 40) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 40 && Forge[AIcount].Q_Brain.Decision.Finger <= 45) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 45 && Forge[AIcount].Q_Brain.Decision.Finger <= 60) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 60 && Forge[AIcount].Q_Brain.Decision.Finger <= 65) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 65 && Forge[AIcount].Q_Brain.Decision.Finger <= 70) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 70 && Forge[AIcount].Q_Brain.Decision.Finger <= 75) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 75 && Forge[AIcount].Q_Brain.Decision.Finger <= 80) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 80 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Forge[AIcount].Q_Brain.Decision.Finger > 85 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 90 && Forge[AIcount].Q_Brain.Decision.Finger <= 100) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.SpecialSTOP = 1;
							}
						}

#pragma message("FIXME:::COLDET::: Pack Crash Avoidance")
#if 0
					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 304;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;

					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, -120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 303;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;

					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 15, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 309;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.CollDetSTOP == 0)
						{
						if(Forge[AIcount].collide == 1 && Forge[AIcount].attackon == 0)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 3) + 11))
								{
								Forge[AIcount].Q_Brain.CollDetSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = Forge[AIcount].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
							}
						else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
						}

					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Forge[AIcount].astackrun > 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 5) + 2))	//7.5
								{
								Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Forge[AIcount].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.DeflectSTOP == 0)
						{
						if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && (Forge[AIcount].Aposestate != 30) && (Forge[AIcount].Aposestate != 51) && (Forge[AIcount].Aposestate != 52) && ((Forge[AIcount].attackon == 0) || ((Forge[AIcount].attackon == 1) && (Forge[AIcount].Aposestate == 26) || (Forge[AIcount].Aposestate == 28))))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7) + 3))
								{
								if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
									{
									Forge[AIcount].DeflectPower = 0;

									if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28)
										{
										Forge[AIcount].Deft_InReact = 1;
										Forge[AIcount].Deft_PoseState = Forge[AIcount].Aposestate;
										Forge[AIcount].Deft_attposecnt = Forge[AIcount].attposecnt;
										Forge[AIcount].Deft_HitReactScale = Forge[AIcount].HitReactScale;
										}
									}
								else Forge[AIcount].DeflectPower = 1;

								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 63;

								Forge[AIcount].attposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].blendamount[0] = 0;
								Forge[AIcount].blendamount[98] = 0;
								Forge[AIcount].TrailsOn = 0;
								Forge[AIcount].attackon = 0;
								Forge[AIcount].blendamount[0] = 0;

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								/*QpoSound3D_GetConfig(World,
									&player.ViewXForm,
									&Forge[AIcount].RFistPos.Translation,
									600.0f,
									2.0f,
									&Volume,
									&Pan,
									&Frequency);*/

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(S_BJink, Volume, Pan, S_TimeScale, FALSE);
								}
							else Forge[AIcount].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Forge[AIcount].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Forge[AIcount].AV.Xform.Translation.y) > 50)
								{
								if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 11;
									Forge[AIcount].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Forge[AIcount].Mposestate == 11)
										{
										Forge[AIcount].JumpDir = 0;

										Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
										//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

										if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

										Forge[AIcount].jumpposecnt = 0;
										Forge[AIcount].Mposestate = 12;
										Forge[AIcount].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Forge[AIcount].Q_Brain.RunAttSTOP == 0)
						{
						if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Running == 1 && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7.5) + 2))
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 46;
								Forge[AIcount].astackcnt++;
								}
							else Forge[AIcount].Q_Brain.RunAttSTOP = 1;
							}
						}


					//### Check for enemy using weapon
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Forge[AIcount].WeaponAimer = 1.7;
						Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
						//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
						}


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
						{
						Forge[AIcount].Block = 0;
						Forge[AIcount].Blocking = 0;
						}


					//##### Factor thru a response
					if(Forge[AIcount].Q_Brain.MoveEncount == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Combo = 8;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Special = 22;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Move = 9;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
						Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 6000;// * (1 - Forge[AIcount].LEVELFactor));
						else
							{	//Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.F_Delay = 30000;// * (1 - Forge[AIcount].LEVELFactor));
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 2000;

						// - Single RLPunch
						Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 4000;

						// - Single RMKick
						Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 2000;

						// - Low Punch Right
						Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 2500;

						// - Low Punch Left
						Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 2500;

						// - Single Renzou
						Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 2000;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Forge[AIcount].Q_Brain.Decision.F_Combo[0] = 1200;

						// - Attack Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Combo[1] = 1000;

						// - Attack Combo 3
						Forge[AIcount].Q_Brain.Decision.F_Combo[2] = 1000;

						// - Attack Combo 4
						Forge[AIcount].Q_Brain.Decision.F_Combo[3] = 1500;

						// - Attack Combo 5
						Forge[AIcount].Q_Brain.Decision.F_Combo[4] = 1000;

						// - Attack Combo 6	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[5] = 1500;

						// - Attack Combo 7	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[6] = 5000;

						// - Attack Combo 8 NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[7] = 3000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[0] = 1000;

						// - Special -  2  -  Flame Uppercut
						Forge[AIcount].Q_Brain.Decision.F_Special[1] = 800;

						// - Special -  3  -  VHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[2] = 1000;

						// - Special -  4  -  Leap Spin Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[3] = 1500;

						// - Special -  5  -  Rush Elbow
						Forge[AIcount].Q_Brain.Decision.F_Special[4] = 1000;

						// - Special -  6  -  Sky Push
						Forge[AIcount].Q_Brain.Decision.F_Special[5] = 2000;

						// - Special -  7  -  Twist Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[7] = 1000;

						// - Special -  9  -  Hadouken
						Forge[AIcount].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Forge[AIcount].Q_Brain.Decision.F_Special[9] = 1000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Forge[AIcount].Q_Brain.Decision.F_Special[10] = 20000;

						// - Special -  12  -  RUSHPUNCH
						Forge[AIcount].Q_Brain.Decision.F_Special[11] = 15000;

						// - Special -  13  -  RUSHKICK
						Forge[AIcount].Q_Brain.Decision.F_Special[12] = 10000;

						// - Special -  14  -  Static Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[13] = 15000;

						// - Special -  15  -  JSRUSH
						Forge[AIcount].Q_Brain.Decision.F_Special[14] = 10000;

						// - Special -  16  -  Power Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Special[15] = 9000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Forge[AIcount].Q_Brain.Decision.F_Special[16] = 4000;

						// - Special -  18  -  HYPER KNEE FLEX
						Forge[AIcount].Q_Brain.Decision.F_Special[17] = 4000;

						// - Special -  19  -  AIR DASH
						Forge[AIcount].Q_Brain.Decision.F_Special[18] = 4000;

						// - Special -  20  -  SAKURA TRIBUTE
						Forge[AIcount].Q_Brain.Decision.F_Special[19] = 7000;

						// - Special -  21  -  SPIN KICK FULL
						Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Forge[AIcount].Q_Brain.Decision.F_Special[21] = 4000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Forge[AIcount].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Forge[AIcount].Q_Brain.Decision.F_Move[1] = 3000;

						// - Move -  3  -  JUMP
						Forge[AIcount].Q_Brain.Decision.F_Move[2] = 800;

						// - Move -  4  -  Roll Low Left
						Forge[AIcount].Q_Brain.Decision.F_Move[3] = 500;

						// - Move -  5  -  Roll Low Right
						Forge[AIcount].Q_Brain.Decision.F_Move[4] = 500;

						// - Move -  6  -  CartWheel Left
						Forge[AIcount].Q_Brain.Decision.F_Move[5] = 700;

						// - Move -  7  -  CartWheel Right
						Forge[AIcount].Q_Brain.Decision.F_Move[6] = 700;

						// - Move -  8  -  Forward Roll
						Forge[AIcount].Q_Brain.Decision.F_Move[7] = 200;

						// - Move -  9  -  Dodge Left
						Forge[AIcount].Q_Brain.Decision.F_Move[8] = 600;

						// - Move -  10  -  BackFlip
						Forge[AIcount].Q_Brain.Decision.F_Move[9] = 700;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Forge[AIcount].Q_Brain.Decision.FactorSUM =
														Forge[AIcount].Q_Brain.Decision.F_Delay
														+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
														+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
														+ Forge[AIcount].Q_Brain.Decision.SUM_Special
														+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Forge[AIcount].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;

				case 1:	   //#=- Close Range Aggressive
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						Forge[AIcount].Q_Brain.MoveEncount = 1;
						Forge[AIcount].astackcnt = 0;
						Forge[AIcount].astackrun = 0;
						Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Forge[AIcount].Q_Brain.MoveEncount == 1 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
						{
						//###Run Towards Avatar

						Forge[AIcount].ForwardSpeed = 10*TimeScale;
						if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
						Forge[AIcount].Mposestate = 3;
						Forge[AIcount].Running = 1;

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

#if 0
						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}
						
						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
#endif

						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						//Attack position not achieved yet
						Forge[AIcount].Q_Brain.ATTposON = 0;
						Forge[AIcount].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Forge[AIcount].astackcnt = 0;
						//Forge[AIcount].astackrun = 0;
						//Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Forge[AIcount].Running = 0;
						Forge[AIcount].Q_Brain.MoveEncount = 0;
						Forge[AIcount].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Forge[AIcount].Q_Brain.ATTinitiated = 1;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Forge[AIcount].attackon == 0*/ && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Forge[AIcount].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Forge[AIcount].astackrun > 0)
								{
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Forge[AIcount].BlockInit == 0)
							{
							Forge[AIcount].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < (((float)Forge[AIcount].LEVELFactor) + 9)) || (Forge[AIcount].Q_Brain.FocusON == 1))
								{
								Forge[AIcount].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Forge[AIcount].BlockHeightMeM != Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((2 * (float)Forge[AIcount].LEVELFactor) + 8)) || (Forge[AIcount].Q_Brain.FocusON == 1))
										{
										Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
										}
									}
								else
									{
									Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 5) < (((float)Forge[AIcount].LEVELFactor) * 2.5) + 1 || (Forge[AIcount].Q_Brain.FocusON == 1))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (3.5 + (((float)Forge[AIcount].LEVELFactor) * 2))  || (Forge[AIcount].Q_Brain.FocusON == 1))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Forge[AIcount].Blocking = 0;
						Forge[AIcount].BlockInit = 0;

						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (1 + (((float)Forge[AIcount].LEVELFactor) * 1))  || (Forge[AIcount].Q_Brain.FocusON == 1))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (1 + (((float)Forge[AIcount].LEVELFactor) * 1))  || (Forge[AIcount].Q_Brain.FocusON == 1))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 104;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Forge[AIcount].attackon == 1 && ( TIME >= Forge[AIcount].Q_Brain.STOPCNT + 25 ) )
						{
						Forge[AIcount].Q_Brain.STOPCNT = TIME;
						Forge[AIcount].Q_Brain.SpecialSTOP = 0;
						Forge[AIcount].Q_Brain.RunAttSTOP = 0;
						Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
						Forge[AIcount].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Forge[AIcount].Q_Brain.CollSTOPCNT + 100 )
						{
						Forge[AIcount].Q_Brain.CollSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Forge[AIcount].Q_Brain.HitSTOPCNT + 70 )
						{
						Forge[AIcount].Q_Brain.HitSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Forge[AIcount].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 ) /*&& ( Forge[AIcount].Q_Brain.MoveEncount == 0 )*/ )
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 2) + 12))	//4 + 2
								{
								Forge[AIcount].Q_Brain.SpecialSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Forge[AIcount].Q_Brain.Decision.Finger <= 2) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 2 && Forge[AIcount].Q_Brain.Decision.Finger <= 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 4 && Forge[AIcount].Q_Brain.Decision.Finger <= 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Forge[AIcount].Q_Brain.Decision.Finger > 6 && Forge[AIcount].Q_Brain.Decision.Finger <= 10) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 10 && Forge[AIcount].Q_Brain.Decision.Finger <= 15) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 15 && Forge[AIcount].Q_Brain.Decision.Finger <= 20) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 20 && Forge[AIcount].Q_Brain.Decision.Finger <= 25) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 25 && Forge[AIcount].Q_Brain.Decision.Finger <= 30) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 30 && Forge[AIcount].Q_Brain.Decision.Finger <= 35) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 35 && Forge[AIcount].Q_Brain.Decision.Finger <= 40) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 40 && Forge[AIcount].Q_Brain.Decision.Finger <= 45) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 45 && Forge[AIcount].Q_Brain.Decision.Finger <= 60) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 60 && Forge[AIcount].Q_Brain.Decision.Finger <= 65) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 65 && Forge[AIcount].Q_Brain.Decision.Finger <= 70) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 70 && Forge[AIcount].Q_Brain.Decision.Finger <= 75) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 75 && Forge[AIcount].Q_Brain.Decision.Finger <= 80) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 80 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Forge[AIcount].Q_Brain.Decision.Finger > 85 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 90 && Forge[AIcount].Q_Brain.Decision.Finger <= 100) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 304;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, -120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 303;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 15, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 309;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					/*if(Forge[AIcount].Q_Brain.CollDetSTOP == 0)
						{
						if(Forge[AIcount].collide == 1 && Forge[AIcount].attackon == 0)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 3) + 11))
								{
								Forge[AIcount].Q_Brain.CollDetSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = Forge[AIcount].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
							}
						else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
						}*/


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Forge[AIcount].astackrun > 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 5) + 2)  || (Forge[AIcount].Q_Brain.FocusON == 1))	//7.5
								{
								Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								Forge[AIcount].Q_Brain.Decision.ON = 0;
								}
							else Forge[AIcount].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.DeflectSTOP == 0)
						{
						if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Forge[AIcount].Aposestate == 30) && !(Forge[AIcount].Aposestate == 51) && !(Forge[AIcount].Aposestate == 52))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 2) + 3) || (Forge[AIcount].Q_Brain.FocusON == 1))
								{
								if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
									{
									Forge[AIcount].DeflectPower = 0;

									if(Forge[AIcount].Aposestate == 26)
										{
										Forge[AIcount].Deft_InReact = 1;
										Forge[AIcount].Deft_PoseState = Forge[AIcount].Aposestate;
										Forge[AIcount].Deft_attposecnt = Forge[AIcount].attposecnt;
										Forge[AIcount].Deft_HitReactScale = Forge[AIcount].HitReactScale;
										}
									}
								else Forge[AIcount].DeflectPower = 1;

								Forge[AIcount].Q_Brain.DeflectSTOP = 1;

								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 63;
								Forge[AIcount].Q_Brain.Decision.ON = 0;

								Forge[AIcount].attposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].blendamount[0] = 0;
								Forge[AIcount].blendamount[98] = 0;
								Forge[AIcount].TrailsOn = 0;
								Forge[AIcount].attackon = 0;
								Forge[AIcount].blendamount[0] = 0;

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								/*QpoSound3D_GetConfig(World,
									&player.ViewXForm,
									&Forge[AIcount].RFistPos.Translation,
									600.0f,
									2.0f,
									&Volume,
									&Pan,
									&Frequency);*/

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(S_BJink, Volume, Pan, S_TimeScale, FALSE);
								}
							else Forge[AIcount].Q_Brain.DeflectSTOP = 1;
							}
						}


					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Forge[AIcount].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Forge[AIcount].AV.Xform.Translation.y) > 50)
								{
								if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 11;
									Forge[AIcount].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Forge[AIcount].Mposestate == 11)
										{
										Forge[AIcount].JumpDir = 0;

										Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
										//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

										if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

										Forge[AIcount].jumpposecnt = 0;
										Forge[AIcount].Mposestate = 12;
										Forge[AIcount].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Forge[AIcount].Q_Brain.RunAttSTOP == 0)
						{
						if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Running == 1 && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7.5) + 2))
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 46;
								Forge[AIcount].astackcnt++;
								}
							else Forge[AIcount].Q_Brain.RunAttSTOP = 1;
							}
						}


					//### Check for enemy using weapon
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Forge[AIcount].WeaponAimer = 1.7;
						Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
						//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
						}


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
						{
						Forge[AIcount].Block = 0;
						Forge[AIcount].Blocking = 0;
						}


					//##### Factor thru a response
					if(Forge[AIcount].Q_Brain.MoveEncount == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Combo = 8;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Special = 22;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
						Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 10000;// * (1 - Forge[AIcount].LEVELFactor));
						else
							{	//Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.F_Delay = 500000;// * (1 - Forge[AIcount].LEVELFactor));
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 6000;

						// - Single RLPunch
						Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 6500;

						// - Single RMKick
						Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 5500;

						// - Low Punch Right
						Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 7500;

						// - Low Punch Left
						Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 6500;

						// - Single Renzou
						Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 500;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Forge[AIcount].Q_Brain.Decision.F_Combo[0] = 8200;

						// - Attack Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Combo[1] = 8000;

						// - Attack Combo 3
						Forge[AIcount].Q_Brain.Decision.F_Combo[2] = 8000;

						// - Attack Combo 4
						Forge[AIcount].Q_Brain.Decision.F_Combo[3] = 6500;

						// - Attack Combo 5
						Forge[AIcount].Q_Brain.Decision.F_Combo[4] = 7000;

						// - Attack Combo 6	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[5] = 8000;

						// - Attack Combo 7	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[6] = 10000;

						// - Attack Combo 8 NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[7] = 8000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[0] = 2000;

						// - Special -  2  -  Flame Uppercut
						Forge[AIcount].Q_Brain.Decision.F_Special[1] = 2400;

						// - Special -  3  -  VHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[2] = 2500;

						// - Special -  4  -  Leap Spin Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[3] = 3500;

						// - Special -  5  -  Rush Elbow
						Forge[AIcount].Q_Brain.Decision.F_Special[4] = 2500;

						// - Special -  6  -  Sky Push
						Forge[AIcount].Q_Brain.Decision.F_Special[5] = 5000;

						// - Special -  7  -  Twist Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[7] = 1000;

						// - Special -  9  -  Hadouken
						Forge[AIcount].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Forge[AIcount].Q_Brain.Decision.F_Special[9] = 1000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Forge[AIcount].Q_Brain.Decision.F_Special[10] = 4000;

						// - Special -  12  -  RUSHPUNCH
						Forge[AIcount].Q_Brain.Decision.F_Special[11] = 3000;

						// - Special -  13  -  RUSHKICK
						Forge[AIcount].Q_Brain.Decision.F_Special[12] = 2000;

						// - Special -  14  -  Static Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[13] = 7000;

						// - Special -  15  -  JSRUSH
						Forge[AIcount].Q_Brain.Decision.F_Special[14] = 3000;

						// - Special -  16  -  Power Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Special[15] = 9000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Forge[AIcount].Q_Brain.Decision.F_Special[16] = 4000;

						// - Special -  18  -  HYPER KNEE FLEX
						Forge[AIcount].Q_Brain.Decision.F_Special[17] = 4000;

						// - Special -  19  -  AIR DASH
						Forge[AIcount].Q_Brain.Decision.F_Special[18] = 4000;

						// - Special -  20  -  SAKURA TRIBUTE
						Forge[AIcount].Q_Brain.Decision.F_Special[19] = 7000;

						// - Special -  21  -  SPIN KICK FULL
						Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Forge[AIcount].Q_Brain.Decision.F_Special[21] = 4000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Forge[AIcount].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Forge[AIcount].Q_Brain.Decision.F_Move[1] = 3000;

						// - Move -  3  -  JUMP
						Forge[AIcount].Q_Brain.Decision.F_Move[2] = 18000;

						// - Move -  4  -  Roll Low Left
						Forge[AIcount].Q_Brain.Decision.F_Move[3] = 2500;

						// - Move -  5  -  Roll Low Right
						Forge[AIcount].Q_Brain.Decision.F_Move[4] = 2500;

						// - Move -  6  -  CartWheel Left
						Forge[AIcount].Q_Brain.Decision.F_Move[5] = 3700;

						// - Move -  7  -  CartWheel Right
						Forge[AIcount].Q_Brain.Decision.F_Move[6] = 3700;

						// - Move -  8  -  Forward Roll
						Forge[AIcount].Q_Brain.Decision.F_Move[7] = 2200;

						// - Move -  9  -  Dodge Left
						Forge[AIcount].Q_Brain.Decision.F_Move[8] = 7600;

						// - Move -  10  -  BackFlip
						Forge[AIcount].Q_Brain.Decision.F_Move[9] = 5000;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Forge[AIcount].Q_Brain.Decision.FactorSUM =
														Forge[AIcount].Q_Brain.Decision.F_Delay
														+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
														+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
														+ Forge[AIcount].Q_Brain.Decision.SUM_Special
														+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Forge[AIcount].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;


				case 2:	   //#=- Close Range - Defensive
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						Forge[AIcount].Q_Brain.MoveEncount = 1;
						Forge[AIcount].astackcnt = 0;
						Forge[AIcount].astackrun = 0;
						Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

						if(Forge[AIcount].Q_Brain.EnergySTOP == 0)
							{
							Forge[AIcount].Q_Brain.EnergySTOP = 1;
							Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
							Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Forge[AIcount].Q_Brain.Decision.ON = 1;
							}
						}


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Forge[AIcount].Q_Brain.MoveEncount == 1 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
						{
						//###Run Towards Avatar

						Forge[AIcount].ForwardSpeed = 10*TimeScale;
						if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
						Forge[AIcount].Mposestate = 3;
						Forge[AIcount].Running = 1;

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

#if 0
						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}
						
						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
#endif
							
						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						//Attack position not achieved yet
						Forge[AIcount].Q_Brain.ATTposON = 0;
						Forge[AIcount].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Forge[AIcount].astackcnt = 0;
						//Forge[AIcount].astackrun = 0;
						//Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Forge[AIcount].Running = 0;
						Forge[AIcount].Q_Brain.MoveEncount = 0;
						Forge[AIcount].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Forge[AIcount].Q_Brain.ATTinitiated = 1;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Forge[AIcount].attackon == 0*/ && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
						/*if(Forge[AIcount].astackrun > 0)
							{
							Forge[AIcount].astackcnt = 0;
							Forge[AIcount].astackrun = 0;
							Forge[AIcount].astackcntdir[0] = 0;
							Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
							}*/

						if(Forge[AIcount].BlockInit == 0)
							{
							Forge[AIcount].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if( (((float)rand() / 32767) * 10) < ((((float)Forge[AIcount].LEVELFactor)) + 9) )
								{
								Forge[AIcount].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Forge[AIcount].BlockHeightMeM != Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < (((float)Forge[AIcount].LEVELFactor) + 9)))
										{
										Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
										}
									}
								else
									{
									Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 8) < 4 + (((float)Forge[AIcount].LEVELFactor) * 2))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (3 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Forge[AIcount].Blocking = 0;
						Forge[AIcount].BlockInit = 0;

						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 8) < (3 + (((float)Forge[AIcount].LEVELFactor) * 2)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (2 + (((float)Forge[AIcount].LEVELFactor) * 2)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Forge[AIcount].attackon == 1 && ( TIME >= Forge[AIcount].Q_Brain.STOPCNT + 50 ) )
						{
						Forge[AIcount].Q_Brain.STOPCNT = TIME;
						Forge[AIcount].Q_Brain.SpecialSTOP = 0;
						Forge[AIcount].Q_Brain.RunAttSTOP = 0;
						Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
						Forge[AIcount].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Forge[AIcount].Q_Brain.CollSTOPCNT + 100 )
						{
						Forge[AIcount].Q_Brain.CollSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Forge[AIcount].Q_Brain.HitSTOPCNT + 100 )
						{
						Forge[AIcount].Q_Brain.HitSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Forge[AIcount].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 ) && ( Forge[AIcount].Q_Brain.MoveEncount == 0 ) )
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 2) + 12))	//4 + 2
								{
								Forge[AIcount].Q_Brain.SpecialSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Forge[AIcount].Q_Brain.Decision.Finger <= 2) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 2 && Forge[AIcount].Q_Brain.Decision.Finger <= 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 4 && Forge[AIcount].Q_Brain.Decision.Finger <= 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Forge[AIcount].Q_Brain.Decision.Finger > 6 && Forge[AIcount].Q_Brain.Decision.Finger <= 10) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 10 && Forge[AIcount].Q_Brain.Decision.Finger <= 15) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 15 && Forge[AIcount].Q_Brain.Decision.Finger <= 20) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 20 && Forge[AIcount].Q_Brain.Decision.Finger <= 25) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 25 && Forge[AIcount].Q_Brain.Decision.Finger <= 30) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 30 && Forge[AIcount].Q_Brain.Decision.Finger <= 35) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 35 && Forge[AIcount].Q_Brain.Decision.Finger <= 40) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 40 && Forge[AIcount].Q_Brain.Decision.Finger <= 45) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 45 && Forge[AIcount].Q_Brain.Decision.Finger <= 60) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 60 && Forge[AIcount].Q_Brain.Decision.Finger <= 65) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 65 && Forge[AIcount].Q_Brain.Decision.Finger <= 70) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 70 && Forge[AIcount].Q_Brain.Decision.Finger <= 75) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 75 && Forge[AIcount].Q_Brain.Decision.Finger <= 80) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 80 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Forge[AIcount].Q_Brain.Decision.Finger > 85 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 90 && Forge[AIcount].Q_Brain.Decision.Finger <= 100) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 304;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, -120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 303;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 15, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 309;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					/*if(Forge[AIcount].Q_Brain.CollDetSTOP == 0)
						{
						if(Forge[AIcount].collide == 1 && Forge[AIcount].attackon == 0)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 3) + 11))
								{
								Forge[AIcount].Q_Brain.CollDetSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = Forge[AIcount].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
							}
						else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
						}*/


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Forge[AIcount].astackrun > 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 5) + 10))	//7.5
								{
								Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Forge[AIcount].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.DeflectSTOP == 0)
						{
						if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Forge[AIcount].Aposestate == 30) && !(Forge[AIcount].Aposestate == 51) && !(Forge[AIcount].Aposestate == 52))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 3.5) + 1))
								{
								if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
									{
									Forge[AIcount].DeflectPower = 0;

									if(Forge[AIcount].Aposestate == 26)
										{
										Forge[AIcount].Deft_InReact = 1;
										Forge[AIcount].Deft_PoseState = Forge[AIcount].Aposestate;
										Forge[AIcount].Deft_attposecnt = Forge[AIcount].attposecnt;
										Forge[AIcount].Deft_HitReactScale = Forge[AIcount].HitReactScale;
										}
									}
								else Forge[AIcount].DeflectPower = 1;

								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 63;

								Forge[AIcount].attposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].blendamount[0] = 0;
								Forge[AIcount].blendamount[98] = 0;
								Forge[AIcount].TrailsOn = 0;
								Forge[AIcount].attackon = 0;
								Forge[AIcount].blendamount[0] = 0;

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								/*QpoSound3D_GetConfig(World,
									&player.ViewXForm,
									&Forge[AIcount].RFistPos.Translation,
									600.0f,
									2.0f,
									&Volume,
									&Pan,
									&Frequency);*/

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(S_BJink, Volume, Pan, S_TimeScale, FALSE);
								}
							else Forge[AIcount].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Forge[AIcount].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Forge[AIcount].AV.Xform.Translation.y) > 50)
								{
								if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 11;
									Forge[AIcount].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Forge[AIcount].Mposestate == 11)
										{
										Forge[AIcount].JumpDir = 0;

										Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
										//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

										if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

										Forge[AIcount].jumpposecnt = 0;
										Forge[AIcount].Mposestate = 12;
										Forge[AIcount].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Forge[AIcount].Q_Brain.RunAttSTOP == 0)
						{
						if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Running == 1 && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7.5) + 2))
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 46;
								Forge[AIcount].astackcnt++;
								}
							else Forge[AIcount].Q_Brain.RunAttSTOP = 1;
							}
						}


					//### Check for enemy using weapon
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Forge[AIcount].WeaponAimer = 1.7;
						Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
						//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
						}


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
						{
						Forge[AIcount].Block = 0;
						Forge[AIcount].Blocking = 0;
						}


					//##### Factor thru a response
					if(Forge[AIcount].Q_Brain.MoveEncount == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Combo = 8;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Special = 22;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
						Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 25000;// * (1 - Forge[AIcount].LEVELFactor));
						else
							{	//Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.F_Delay = 30000;// * (1 - Forge[AIcount].LEVELFactor));
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 3000;

						// - Single RLPunch
						Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 2300;

						// - Single RMKick
						Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 3300;

						// - Low Punch Right
						Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 1400;

						// - Low Punch Left
						Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 1400;

						// - Single Renzou
						Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 0;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Forge[AIcount].Q_Brain.Decision.F_Combo[0] = 80;

						// - Attack Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Combo[1] = 80;

						// - Attack Combo 3
						Forge[AIcount].Q_Brain.Decision.F_Combo[2] = 80;

						// - Attack Combo 4
						Forge[AIcount].Q_Brain.Decision.F_Combo[3] = 80;

						// - Attack Combo 5
						Forge[AIcount].Q_Brain.Decision.F_Combo[4] = 80;

						// - Attack Combo 6	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[5] = 80;

						// - Attack Combo 7	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[6] = 80;

						// - Attack Combo 8 NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[7] = 80;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[0] = 50;

						// - Special -  2  -  Flame Uppercut
						Forge[AIcount].Q_Brain.Decision.F_Special[1] = 50;

						// - Special -  3  -  VHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[2] = 50;

						// - Special -  4  -  Leap Spin Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[3] = 800;

						// - Special -  5  -  Rush Elbow
						Forge[AIcount].Q_Brain.Decision.F_Special[4] = 100;

						// - Special -  6  -  Sky Push
						Forge[AIcount].Q_Brain.Decision.F_Special[5] = 200;

						// - Special -  7  -  Twist Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[6] = 300;

						// - Special -  8  -  Hover Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[7] = 50;

						// - Special -  9  -  Hadouken
						Forge[AIcount].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Forge[AIcount].Q_Brain.Decision.F_Special[9] = 300;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Forge[AIcount].Q_Brain.Decision.F_Special[10] = 200;

						// - Special -  12  -  RUSHPUNCH
						Forge[AIcount].Q_Brain.Decision.F_Special[11] = 150;

						// - Special -  13  -  RUSHKICK
						Forge[AIcount].Q_Brain.Decision.F_Special[12] = 100;

						// - Special -  14  -  Static Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[13] = 500;

						// - Special -  15  -  JSRUSH
						Forge[AIcount].Q_Brain.Decision.F_Special[14] = 700;

						// - Special -  16  -  Power Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Special[15] = 400;

						// - Special -  17  -  JS FLAME UPPERCUT
						Forge[AIcount].Q_Brain.Decision.F_Special[16] = 400;

						// - Special -  18  -  HYPER KNEE FLEX
						Forge[AIcount].Q_Brain.Decision.F_Special[17] = 400;

						// - Special -  19  -  AIR DASH
						Forge[AIcount].Q_Brain.Decision.F_Special[18] = 400;

						// - Special -  20  -  SAKURA TRIBUTE
						Forge[AIcount].Q_Brain.Decision.F_Special[19] = 400;

						// - Special -  21  -  SPIN KICK FULL
						Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Forge[AIcount].Q_Brain.Decision.F_Special[21] = 400;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Forge[AIcount].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Forge[AIcount].Q_Brain.Decision.F_Move[1] = 2000;

						// - Move -  3  -  JUMP
						Forge[AIcount].Q_Brain.Decision.F_Move[2] = 1500;

						// - Move -  4  -  Roll Low Left
						Forge[AIcount].Q_Brain.Decision.F_Move[3] = 1800;

						// - Move -  5  -  Roll Low Right
						Forge[AIcount].Q_Brain.Decision.F_Move[4] = 1800;

						// - Move -  6  -  CartWheel Left
						Forge[AIcount].Q_Brain.Decision.F_Move[5] = 1500;

						// - Move -  7  -  CartWheel Right
						Forge[AIcount].Q_Brain.Decision.F_Move[6] = 1500;

						// - Move -  8  -  Forward Roll
						Forge[AIcount].Q_Brain.Decision.F_Move[7] = 1100;

						// - Move -  9  -  Dodge Left
						Forge[AIcount].Q_Brain.Decision.F_Move[8] = 1100;

						// - Move -  10  -  BackFlip
						Forge[AIcount].Q_Brain.Decision.F_Move[9] = 1800;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Forge[AIcount].Q_Brain.Decision.FactorSUM =
														Forge[AIcount].Q_Brain.Decision.F_Delay
														+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
														+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
														+ Forge[AIcount].Q_Brain.Decision.SUM_Special
														+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Forge[AIcount].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;


				case 3:	   //#=- Medium Range - Aggresive
					{

					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Forge[AIcount].Q_Brain.ATTinitiated = 1;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Forge[AIcount].attackon == 0*/ && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Forge[AIcount].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Forge[AIcount].astackrun > 0)
								{
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Forge[AIcount].BlockInit == 0)
							{
							Forge[AIcount].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Forge[AIcount].LEVELFactor) + 8)))
								{
								Forge[AIcount].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Forge[AIcount].BlockHeightMeM != Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Forge[AIcount].LEVELFactor) + 7)))
										{
										Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
										}
									}
								else
									{
									Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Forge[AIcount].Blocking = 0;
						Forge[AIcount].BlockInit = 0;

						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Forge[AIcount].astackrun > 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 5) + 2))	//7.5
								{
								Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Forge[AIcount].Q_Brain.ComboCancelSTOP = 1;
							}
						}




					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Forge[AIcount].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Forge[AIcount].AV.Xform.Translation.y) > 50)
								{
								if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 11;
									Forge[AIcount].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Forge[AIcount].Mposestate == 11)
										{
										Forge[AIcount].JumpDir = 0;

										Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
										//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

										if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

										Forge[AIcount].jumpposecnt = 0;
										Forge[AIcount].Mposestate = 12;
										Forge[AIcount].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Forge[AIcount].Q_Brain.RunAttSTOP == 0)
						{
						if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Running == 1 && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7.5) + 2))
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 46;
								Forge[AIcount].astackcnt++;
								}
							else Forge[AIcount].Q_Brain.RunAttSTOP = 1;
							}
						}


					//### Check for enemy using weapon
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Forge[AIcount].WeaponAimer = 1.7;
						Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
						//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
						}


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
						{
						Forge[AIcount].Block = 0;
						Forge[AIcount].Blocking = 0;
						}


					//#### Test Distance 1
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 400)
						{

						//###Run Towards Avatar
						Forge[AIcount].ForwardSpeed = 10*TimeScale;
						if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
						Forge[AIcount].Mposestate = 3;
						Forge[AIcount].Running = 1;

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

#if 0
						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}
						
						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
#endif
						
						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						//Attack position not achieved yet
						Forge[AIcount].Q_Brain.ATTposON = 0;
						Forge[AIcount].Q_Brain.ATTinitiated = 0;

						//##### Factor thru a response
						if(/*Forge[AIcount].Q_Brain.MoveEncount == 0 && */Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
							{
							//##### -  Set The Number Of Factors  - #####
							Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Combo = 0;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Special = 15;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Move = 10;
							

							//##### -  Reset Pathway Factors  - #####

							//### Reset Delay and Move To Encount Factors
							Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
							Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
							

							//### Reset Single Attacks Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
								helly++;
								}

							//### Reset Combo Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
								helly++;
								}

							//### Reset Special Attack Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
								helly++;
								}

							//### Reset Movement and Dodge Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
								helly++;
								}

							
							//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

							//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
							if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 15000;// * (1 - Forge[AIcount].LEVELFactor));
							else
								{	//Reset Delay Switch
								Forge[AIcount].Q_Brain.Decision.F_Delay = 30000;// * (1 - Forge[AIcount].LEVELFactor));
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
								}
							//### Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



							//####### -  Single Attacks  - #######
							
							// - Attack once lightly then rethink
							Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 0;

							// - Single RLPunch
							Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 0;

							// - Single RMKick
							Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 0;

							// - Low Punch Right
							Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 0;

							// - Low Punch Left
							Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 0;

							// - Single Renzou
							Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 500;


							//####### -  Special Attacks  - #######

							// - Special -  1  -  RHKick
							Forge[AIcount].Q_Brain.Decision.F_Special[0] = 0;

							// - Special -  2  -  Flame Uppercut
							Forge[AIcount].Q_Brain.Decision.F_Special[1] = 0;

							// - Special -  3  -  VHKick
							Forge[AIcount].Q_Brain.Decision.F_Special[2] = 0;

							// - Special -  4  -  Leap Spin Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[3] = 0;

							// - Special -  5  -  Rush Elbow
							Forge[AIcount].Q_Brain.Decision.F_Special[4] = 0;

							// - Special -  6  -  Sky Push
							Forge[AIcount].Q_Brain.Decision.F_Special[5] = 0;

							// - Special -  7  -  Twist Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[6] = 0;

							// - Special -  8  -  Hover Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[7] = 0;
							
							// - Special -  9  -  Hadou-ken
							Forge[AIcount].Q_Brain.Decision.F_Special[8] = 800;

							// - Special -  10  -   JSRUSHUP
							Forge[AIcount].Q_Brain.Decision.F_Special[9] = 1000;

							// - Special -  11  -  RUSHPUNCHNORMAL
							Forge[AIcount].Q_Brain.Decision.F_Special[10] = 0;

							// - Special -  12  -  RUSHPUNCH
							Forge[AIcount].Q_Brain.Decision.F_Special[11] = 0;

							// - Special -  13  -  RUSHKICK
							Forge[AIcount].Q_Brain.Decision.F_Special[12] = 0;

							// - Special -  14  -  Static Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[13] = 0;

							// - Special -  15  -  JSRUSH
							Forge[AIcount].Q_Brain.Decision.F_Special[14] = 20000;

							// - Special -  16  -  Power Combo 2
							Forge[AIcount].Q_Brain.Decision.F_Special[15] = 2000;

							// - Special -  17  -  JS FLAME UPPERCUT
							Forge[AIcount].Q_Brain.Decision.F_Special[16] = 1000;

							// - Special -  18  -  HYPER KNEE FLEX
							Forge[AIcount].Q_Brain.Decision.F_Special[17] = 1000;

							// - Special -  19  -  AIR DASH
							Forge[AIcount].Q_Brain.Decision.F_Special[18] = 1000;

							// - Special -  20  -  SAKURA TRIBUTE
							Forge[AIcount].Q_Brain.Decision.F_Special[19] = 1000;

							// - Special -  21  -  SPIN KICK FULL
							Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

							// - Special -  22  -  CYCLONE KICK
							Forge[AIcount].Q_Brain.Decision.F_Special[21] = 8000;


							//####### -  Movement / Dodges  - #######
						
							// - Move -  1  -  Taunt
							Forge[AIcount].Q_Brain.Decision.F_Move[0] = 2000;

							// - Move -  2  -  SideStep
							Forge[AIcount].Q_Brain.Decision.F_Move[1] = 7000;

							// - Move -  3  -  JUMP
							Forge[AIcount].Q_Brain.Decision.F_Move[2] = 10000;

							// - Move -  4  -  Roll Low Left
							Forge[AIcount].Q_Brain.Decision.F_Move[3] = 0;

							// - Move -  5  -  Roll Low Right
							Forge[AIcount].Q_Brain.Decision.F_Move[4] = 0;

							// - Move -  6  -  CartWheel Left
							Forge[AIcount].Q_Brain.Decision.F_Move[5] = 3500;

							// - Move -  7  -  CartWheel Right
							Forge[AIcount].Q_Brain.Decision.F_Move[6] = 3500;

							// - Move -  8  -  Forward Roll
							Forge[AIcount].Q_Brain.Decision.F_Move[7] = 5000;

							// - Move -  9  -  Dodge Left
							Forge[AIcount].Q_Brain.Decision.F_Move[8] = 0;

							// - Move -  10  -  BackFlip
							Forge[AIcount].Q_Brain.Decision.F_Move[9] = 0;
							


							//IMP ********\/\/\/\/\/
							//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


							//##### Collate Factor Sums
							Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
								aero++;
								}


							//######## FACTOR TOTAL ########
							Forge[AIcount].Q_Brain.Decision.FactorSUM =
															Forge[AIcount].Q_Brain.Decision.F_Delay
															+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
															+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
															+ Forge[AIcount].Q_Brain.Decision.SUM_Special
															+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


							//### ---->>> Seed the finger
							Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


							//######### -  Determine Result  - #########

										//### Delay
							if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


							//##### -  Search Factor Arrays For Result  - #####

							//### Set Search Variable
							Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

							helly=0;	//### Attack Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
								helly++;
								}


							helly=0;	//### Combo Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
								helly++;
								}


							helly=0;	//### Special Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
								helly++;
								}


							helly=0;	//### Move Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
								helly++;
								}


							//### Set Decision to ON position
							Forge[AIcount].Q_Brain.Decision.ON = 1;

							}//END Condition - Move Encount

						}//END Distance Check 1



					//#### Test Distance 2
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 400)
						{

						/*if(Forge[AIcount].attackon == 0)
							{
							//###Run Towards Avatar
							Forge[AIcount].ForwardSpeed = 10*TimeScale;
							if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
							Forge[AIcount].Mposestate = 3;
							Forge[AIcount].Running = 1;

							//*** Actor
							Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
							Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
							Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
							Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

							Forge[AIcount].AV.OldPos.y += 60;
							Forge[AIcount].AV.NewPos.y += 60;

							// This does collision detection
							if(Qpo->Collision_RayTest(
										 NULL, 
										 NULL, 
										 &Forge[AIcount].AV.OldPos, 
										 &Forge[AIcount].AV.NewPos, 
										 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
										 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
										 0xffffffff, NULL, NULL, 
										 &Forge[AIcount].AV.Collision))
								{
								// Set the new pos to the point of collision
								Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
								}
							
							Forge[AIcount].AV.OldPos.y -= 60;
							Forge[AIcount].AV.NewPos.y -= 60;
							
							// Set the player to the new pos
							Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

							//Attack position not achieved yet
							Forge[AIcount].Q_Brain.ATTposON = 0;
							Forge[AIcount].Q_Brain.ATTinitiated = 0;
							}*/
						

						//##### Factor thru a response
						if(/*Forge[AIcount].Q_Brain.MoveEncount == 0 &&*/ Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
							{
							//##### -  Set The Number Of Factors  - #####
							Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Combo = 0;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Special = 22;
							
							Forge[AIcount].Q_Brain.Decision.NOM_Move = 10;
							

							//##### -  Reset Pathway Factors  - #####

							//### Reset Delay and Move To Encount Factors
							Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
							Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
							

							//### Reset Single Attacks Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
								helly++;
								}

							//### Reset Combo Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
								helly++;
								}

							//### Reset Special Attack Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
								helly++;
								}

							//### Reset Movement and Dodge Factors
							helly=0;
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
								helly++;
								}

							
							//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

							//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
							if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 10000;// * (1 - Forge[AIcount].LEVELFactor));
							else
								{	//Reset Delay Switch
								Forge[AIcount].Q_Brain.Decision.F_Delay = 10000;// * (1 - Forge[AIcount].LEVELFactor));
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
								}
							//### Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



							//####### -  Single Attacks  - #######
							
							// - Attack once lightly then rethink
							Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 0;

							// - Single RLPunch
							Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 0;

							// - Single RMKick
							Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 0;

							// - Low Punch Right
							Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 0;

							// - Low Punch Left
							Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 0;

							// - Single Renzou
							Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 1000;



							//####### -  Jink Special Attacks  - #######

							// - Special -  1  -  RHKick
							Forge[AIcount].Q_Brain.Decision.F_Special[0] = 0;

							// - Special -  2  -  Flame Uppercut
							Forge[AIcount].Q_Brain.Decision.F_Special[1] = 0;

							// - Special -  3  -  VHKick
							Forge[AIcount].Q_Brain.Decision.F_Special[2] = 0;

							// - Special -  4  -  Leap Spin Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[3] = 6000;

							// - Special -  5  -  Rush Elbow
							Forge[AIcount].Q_Brain.Decision.F_Special[4] = 4000;

							// - Special -  6  -  Sky Push
							Forge[AIcount].Q_Brain.Decision.F_Special[5] = 0;

							// - Special -  7  -  Twist Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[6] = 3000;

							// - Special -  8  -  Hover Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[7] = 0;

							// - Special -  9  -  Hadou-ken
							Forge[AIcount].Q_Brain.Decision.F_Special[8] = 6000;

							// - Special -  10  -   JSRUSHUP
							Forge[AIcount].Q_Brain.Decision.F_Special[9] = 1000;

							// - Special -  11  -  RUSHPUNCHNORMAL
							Forge[AIcount].Q_Brain.Decision.F_Special[10] = 8000;

							// - Special -  12  -  RUSHPUNCH
							Forge[AIcount].Q_Brain.Decision.F_Special[11] = 9000;

							// - Special -  13  -  RUSHKICK
							Forge[AIcount].Q_Brain.Decision.F_Special[12] = 9000;

							// - Special -  14  -  Static Kick
							Forge[AIcount].Q_Brain.Decision.F_Special[13] = 0;

							// - Special -  15  -  JSRUSH
							Forge[AIcount].Q_Brain.Decision.F_Special[14] = 5000;

							// - Special -  16  -  Power Combo 2
							Forge[AIcount].Q_Brain.Decision.F_Special[15] = 2000;

							// - Special -  17  -  JS FLAME UPPERCUT
							Forge[AIcount].Q_Brain.Decision.F_Special[16] = 3000;

							// - Special -  18  -  HYPER KNEE FLEX
							Forge[AIcount].Q_Brain.Decision.F_Special[17] = 4000;

							// - Special -  19  -  AIR DASH
							Forge[AIcount].Q_Brain.Decision.F_Special[18] = 4000;

							// - Special -  20  -  SAKURA TRIBUTE
							Forge[AIcount].Q_Brain.Decision.F_Special[19] = 9000;

							// - Special -  21  -  SPIN KICK FULL
							Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

							// - Special -  22  -  CYCLONE KICK
							Forge[AIcount].Q_Brain.Decision.F_Special[21] = 4000;



							//####### -  Movement / Dodges  - #######
						
							// - Move -  1  -  Taunt
							Forge[AIcount].Q_Brain.Decision.F_Move[0] = 1500;

							// - Move -  2  -  SideStep
							Forge[AIcount].Q_Brain.Decision.F_Move[1] = 1500;

							// - Move -  3  -  JUMP
							Forge[AIcount].Q_Brain.Decision.F_Move[2] = 8000;

							// - Move -  4  -  Roll Low Left
							Forge[AIcount].Q_Brain.Decision.F_Move[3] = 1000;

							// - Move -  5  -  Roll Low Right
							Forge[AIcount].Q_Brain.Decision.F_Move[4] = 1000;

							// - Move -  6  -  CartWheel Left
							Forge[AIcount].Q_Brain.Decision.F_Move[5] = 4000;

							// - Move -  7  -  CartWheel Right
							Forge[AIcount].Q_Brain.Decision.F_Move[6] = 4000;

							// - Move -  8  -  Forward Roll
							Forge[AIcount].Q_Brain.Decision.F_Move[7] = 3000;

							// - Move -  9  -  Dodge Left
							Forge[AIcount].Q_Brain.Decision.F_Move[8] = 0;

							// - Move -  10  -  BackFlip
							Forge[AIcount].Q_Brain.Decision.F_Move[9] = 10000;
							


							//IMP ********\/\/\/\/\/
							//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


							//##### Collate Factor Sums
							Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
							Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
								aero++;
								}
							aero = 0;
							while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
								aero++;
								}


							//######## FACTOR TOTAL ########
							Forge[AIcount].Q_Brain.Decision.FactorSUM =
															Forge[AIcount].Q_Brain.Decision.F_Delay
															+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
															+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
															+ Forge[AIcount].Q_Brain.Decision.SUM_Special
															+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


							//### ---->>> Seed the finger
							Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


							//######### -  Determine Result  - #########

										//### Delay
							if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


							//##### -  Search Factor Arrays For Result  - #####

							//### Set Search Variable
							Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

							helly=0;	//### Attack Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
								helly++;
								}


							helly=0;	//### Combo Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
								helly++;
								}


							helly=0;	//### Special Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
								helly++;
								}


							helly=0;	//### Move Factors
							while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
								{
								if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
									&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

								Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
								helly++;
								}


							//### Set Decision to ON position
							Forge[AIcount].Q_Brain.Decision.ON = 1;

							}//END Condition - Move Encount

						}//END Distance Check 2

					} break;


				case 4:	   //#=- Medium Range - Defensive
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						Forge[AIcount].Q_Brain.MoveEncount = 1;
						Forge[AIcount].astackcnt = 0;
						Forge[AIcount].astackrun = 0;
						Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

						if(Forge[AIcount].Q_Brain.EnergySTOP == 0)
							{
							Forge[AIcount].Q_Brain.EnergySTOP = 1;
							Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
							Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Forge[AIcount].Q_Brain.Decision.ON = 1;
							}
						}


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Forge[AIcount].Q_Brain.MoveEncount == 1 && Forge[AIcount].Q_Brain.TargetSIGHT == 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
						{
						//###Run Towards Avatar

						Forge[AIcount].ForwardSpeed = 10*TimeScale;
						if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
						Forge[AIcount].Mposestate = 3;
						Forge[AIcount].Running = 1;

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

#if 0
						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}

						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
#endif

						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						//Attack position not achieved yet
						Forge[AIcount].Q_Brain.ATTposON = 0;
						Forge[AIcount].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Forge[AIcount].astackcnt = 0;
						//Forge[AIcount].astackrun = 0;
						//Forge[AIcount].astackcntdir[0] = 0;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Forge[AIcount].Running = 0;
						Forge[AIcount].Q_Brain.MoveEncount = 0;
						Forge[AIcount].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Forge[AIcount].Q_Brain.ATTinitiated = 1;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Forge[AIcount].attackon == 0*/ && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Forge[AIcount].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Forge[AIcount].astackrun > 0)
								{
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Forge[AIcount].BlockInit == 0)
							{
							Forge[AIcount].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Forge[AIcount].LEVELFactor) + 8)))
								{
								Forge[AIcount].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Forge[AIcount].BlockHeightMeM != Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Forge[AIcount].LEVELFactor) + 7)))
										{
										Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
										}
									}
								else
									{
									Forge[AIcount].BlockHeight = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Forge[AIcount].BlockHeightMeM = Forge[AIcount].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5))
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Forge[AIcount].Blocking = 0;
						Forge[AIcount].BlockInit = 0;

						if(Forge[AIcount].BlockHitFLAG == 1 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Forge[AIcount].BlockHitFLAG = 0;
							Forge[AIcount].EnemyPoseState = Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Forge[AIcount].EnemyPoseState == 27 || Forge[AIcount].EnemyPoseState == 25 || Forge[AIcount].EnemyPoseState == 24 || Forge[AIcount].EnemyPoseState == 23 || Forge[AIcount].EnemyPoseState == 22 || Forge[AIcount].EnemyPoseState == 21 || Forge[AIcount].EnemyPoseState == 17 || Forge[AIcount].EnemyPoseState == 13 || Forge[AIcount].EnemyPoseState == 10 ||
								Forge[AIcount].EnemyPoseState == 41 || Forge[AIcount].EnemyPoseState == 40 || Forge[AIcount].EnemyPoseState == 39 || Forge[AIcount].EnemyPoseState == 35 || Forge[AIcount].EnemyPoseState == 34 || Forge[AIcount].EnemyPoseState == 33 || Forge[AIcount].EnemyPoseState == 32 || Forge[AIcount].EnemyPoseState == 31 || Forge[AIcount].EnemyPoseState == 28 ||
								Forge[AIcount].EnemyPoseState == 38 || Forge[AIcount].EnemyPoseState == 53 || Forge[AIcount].EnemyPoseState == 46 || Forge[AIcount].EnemyPoseState == 45 || Forge[AIcount].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Forge[AIcount].Q_Brain.Decision.Finger < 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 5) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Forge[AIcount].LEVELFactor) * 1.5)) )
									{
									Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
									Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

									Forge[AIcount].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Forge[AIcount].Q_Brain.Decision.Finger <= 3) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Forge[AIcount].Q_Brain.Decision.Finger >= 4 && Forge[AIcount].Q_Brain.Decision.Finger < 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Forge[AIcount].Q_Brain.Decision.Finger == 7) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Forge[AIcount].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Forge[AIcount].attackon == 1 && ( TIME >= Forge[AIcount].Q_Brain.STOPCNT + 200 ) )
						{
						Forge[AIcount].Q_Brain.STOPCNT = TIME;
						Forge[AIcount].Q_Brain.SpecialSTOP = 0;
						Forge[AIcount].Q_Brain.RunAttSTOP = 0;
						Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
						Forge[AIcount].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Forge[AIcount].Q_Brain.CollSTOPCNT + 100 )
						{
						Forge[AIcount].Q_Brain.CollSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Forge[AIcount].Q_Brain.HitSTOPCNT + 30 )
						{
						Forge[AIcount].Q_Brain.HitSTOPCNT = TIME;
						Forge[AIcount].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Forge[AIcount].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Forge[AIcount].LEVEL > 0 ) && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52 ) && ( Forge[AIcount].Q_Brain.MoveEncount == 0 ) )
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 6) + 8))	//4 + 2
								{
								Forge[AIcount].Q_Brain.SpecialSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Forge[AIcount].Q_Brain.Decision.Finger <= 2) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 2 && Forge[AIcount].Q_Brain.Decision.Finger <= 4) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 4 && Forge[AIcount].Q_Brain.Decision.Finger <= 6) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Forge[AIcount].Q_Brain.Decision.Finger > 6 && Forge[AIcount].Q_Brain.Decision.Finger <= 10) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 10 && Forge[AIcount].Q_Brain.Decision.Finger <= 15) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 15 && Forge[AIcount].Q_Brain.Decision.Finger <= 20) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 20 && Forge[AIcount].Q_Brain.Decision.Finger <= 25) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 25 && Forge[AIcount].Q_Brain.Decision.Finger <= 30) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 30 && Forge[AIcount].Q_Brain.Decision.Finger <= 35) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 35 && Forge[AIcount].Q_Brain.Decision.Finger <= 40) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 40 && Forge[AIcount].Q_Brain.Decision.Finger <= 45) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 45 && Forge[AIcount].Q_Brain.Decision.Finger <= 60) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Forge[AIcount].Q_Brain.Decision.Finger > 60 && Forge[AIcount].Q_Brain.Decision.Finger <= 65) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 65 && Forge[AIcount].Q_Brain.Decision.Finger <= 70) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 70 && Forge[AIcount].Q_Brain.Decision.Finger <= 75) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 75 && Forge[AIcount].Q_Brain.Decision.Finger <= 80) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 80 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Forge[AIcount].Q_Brain.Decision.Finger > 85 && Forge[AIcount].Q_Brain.Decision.Finger <= 90) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Forge[AIcount].Q_Brain.Decision.Finger > 90 && Forge[AIcount].Q_Brain.Decision.Finger <= 100) Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 304;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, -120, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 303;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;


					//Collision Detection
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
					Forge[AIcount].AV.OldPos.y += 60; Forge[AIcount].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.NewPos, 15, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
						{ 
						if(Forge[AIcount].AV.Collision.Avatar != 0)
							{
							if(Forge[AIcount].AV.Collision.Avatar != Forge[AIcount].AV.Avatar)
								{
								//Forge[AIcount].collide=1;
								Forge[AIcount].Q_Brain.PREFinger = 309;
								}
							}
						}
					Forge[AIcount].AV.OldPos.y -= 60;Forge[AIcount].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.CollDetSTOP == 0)
						{
						if(Forge[AIcount].collide == 1 && Forge[AIcount].attackon == 0)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 3) + 11))
								{
								Forge[AIcount].Q_Brain.CollDetSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverride = 1;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;

								Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer = Forge[AIcount].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Forge[AIcount].Q_Brain.Decision.ON = 1;
								}
							else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
							}
						else Forge[AIcount].Q_Brain.CollDetSTOP = 1;
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Forge[AIcount].astackrun > 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 5) + 2))	//7.5
								{
								Forge[AIcount].Q_Brain.ComboCancelSTOP = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Forge[AIcount].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Forge[AIcount].Q_Brain.DeflectSTOP == 0)
						{
						if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Forge[AIcount].Aposestate == 30) && !(Forge[AIcount].Aposestate == 51) && !(Forge[AIcount].Aposestate == 52))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7) + 3))
								{
								if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
									{
									Forge[AIcount].DeflectPower = 0;

									if(Forge[AIcount].Aposestate == 26)
										{
										Forge[AIcount].Deft_InReact = 1;
										Forge[AIcount].Deft_PoseState = Forge[AIcount].Aposestate;
										Forge[AIcount].Deft_attposecnt = Forge[AIcount].attposecnt;
										Forge[AIcount].Deft_HitReactScale = Forge[AIcount].HitReactScale;
										}
									}
								else Forge[AIcount].DeflectPower = 1;

								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 63;

								Forge[AIcount].attposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].blendamount[0] = 0;
								Forge[AIcount].blendamount[98] = 0;
								Forge[AIcount].TrailsOn = 0;
								Forge[AIcount].attackon = 0;
								Forge[AIcount].blendamount[0] = 0;

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								/*QpoSound3D_GetConfig(World,
									&player.ViewXForm,
									&Forge[AIcount].RFistPos.Translation,
									600.0f,
									2.0f,
									&Volume,
									&Pan,
									&Frequency);*/

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(S_BJink, Volume, Pan, S_TimeScale, FALSE);
								}
							else Forge[AIcount].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
						{
						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Forge[AIcount].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Forge[AIcount].AV.Xform.Translation.y) > 50)
								{
								if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 11;
									Forge[AIcount].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Forge[AIcount].Mposestate == 11)
										{
										Forge[AIcount].JumpDir = 0;

										Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
										//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

										if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

										Forge[AIcount].jumpposecnt = 0;
										Forge[AIcount].Mposestate = 12;
										Forge[AIcount].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Forge[AIcount].Q_Brain.RunAttSTOP == 0)
						{
						if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Running == 1 && ( Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Forge[AIcount].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Forge[AIcount].Q_Brain.SpecialFinger < ((((float)Forge[AIcount].LEVELFactor) * 7.5) + 2))
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 46;
								Forge[AIcount].astackcnt++;
								}
							else Forge[AIcount].Q_Brain.RunAttSTOP = 1;
							}
						}


					//### Check for enemy using weapon
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 28 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Forge[AIcount].WeaponAimer = 1.7;
						Forge[AIcount].Q_Brain.MindState = MIND_LONGATTK;
						//Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
						}


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Forge[AIcount].Aposestate == 26 || Forge[AIcount].Aposestate == 28 || Forge[AIcount].Aposestate == 30)
						{
						Forge[AIcount].Block = 0;
						Forge[AIcount].Blocking = 0;
						}


					//##### Factor thru a response
					if(/*Forge[AIcount].Q_Brain.MoveEncount == 0 &&*/ Forge[AIcount].Q_Brain.TargetSIGHT == 1 && Forge[AIcount].Flip == 0 && Forge[AIcount].attackon == 0 && Forge[AIcount].Q_Brain.Decision.DecOverride == 0 && Forge[AIcount].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Forge[AIcount].Q_Brain.Decision.NOM_Attack = 6;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Combo = 8;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Special = 22;
						
						Forge[AIcount].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Forge[AIcount].Q_Brain.Decision.F_Delay = 0;
						Forge[AIcount].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Forge[AIcount].Q_Brain.Decision.DelaySwitch == 0) Forge[AIcount].Q_Brain.Decision.F_Delay = 10000;// * (1 - Forge[AIcount].LEVELFactor));
						else
							{	//Reset Delay Switch
							Forge[AIcount].Q_Brain.Decision.F_Delay = 30000;// * (1 - Forge[AIcount].LEVELFactor));
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Forge[AIcount].Q_Brain.Decision.F_Attack[0] = 2000;

						// - Single RLPunch
						Forge[AIcount].Q_Brain.Decision.F_Attack[1] = 4000;

						// - Single RMKick
						Forge[AIcount].Q_Brain.Decision.F_Attack[2] = 2000;

						// - Low Punch Right
						Forge[AIcount].Q_Brain.Decision.F_Attack[3] = 2500;

						// - Low Punch Left
						Forge[AIcount].Q_Brain.Decision.F_Attack[4] = 2500;

						// - Single Renzou
						Forge[AIcount].Q_Brain.Decision.F_Attack[5] = 3000;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Forge[AIcount].Q_Brain.Decision.F_Combo[0] = 1200;

						// - Attack Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Combo[1] = 1000;

						// - Attack Combo 3
						Forge[AIcount].Q_Brain.Decision.F_Combo[2] = 1000;

						// - Attack Combo 4
						Forge[AIcount].Q_Brain.Decision.F_Combo[3] = 1500;

						// - Attack Combo 5
						Forge[AIcount].Q_Brain.Decision.F_Combo[4] = 1000;

						// - Attack Combo 6	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[5] = 1500;

						// - Attack Combo 7	NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[6] = 5000;

						// - Attack Combo 8 NEW
						Forge[AIcount].Q_Brain.Decision.F_Combo[7] = 3000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[0] = 1000;

						// - Special -  2  -  Flame Uppercut
						Forge[AIcount].Q_Brain.Decision.F_Special[1] = 800;

						// - Special -  3  -  VHKick
						Forge[AIcount].Q_Brain.Decision.F_Special[2] = 1000;

						// - Special -  4  -  Leap Spin Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[3] = 1500;

						// - Special -  5  -  Rush Elbow
						Forge[AIcount].Q_Brain.Decision.F_Special[4] = 1000;

						// - Special -  6  -  Sky Push
						Forge[AIcount].Q_Brain.Decision.F_Special[5] = 2000;

						// - Special -  7  -  Twist Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[7] = 1000;
							
						// - Special -  9  -  Hadou-ken
						Forge[AIcount].Q_Brain.Decision.F_Special[8] = 3000;

						// - Special -  10  -   JSRUSHUP
						Forge[AIcount].Q_Brain.Decision.F_Special[9] = 10000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Forge[AIcount].Q_Brain.Decision.F_Special[10] = 20000;

						// - Special -  12  -  RUSHPUNCH
						Forge[AIcount].Q_Brain.Decision.F_Special[11] = 15000;

						// - Special -  13  -  RUSHKICK
						Forge[AIcount].Q_Brain.Decision.F_Special[12] = 10000;

						// - Special -  14  -  Static Kick
						Forge[AIcount].Q_Brain.Decision.F_Special[13] = 15000;

						// - Special -  15  -  JSRUSH
						Forge[AIcount].Q_Brain.Decision.F_Special[14] = 10000;

						// - Special -  16  -  Power Combo 2
						Forge[AIcount].Q_Brain.Decision.F_Special[15] = 3000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Forge[AIcount].Q_Brain.Decision.F_Special[16] = 1000;

						// - Special -  18  -  HYPER KNEE FLEX
						Forge[AIcount].Q_Brain.Decision.F_Special[17] = 1000;

						// - Special -  19  -  AIR DASH
						Forge[AIcount].Q_Brain.Decision.F_Special[18] = 1000;

						// - Special -  20  -  SAKURA TRIBUTE
						Forge[AIcount].Q_Brain.Decision.F_Special[19] = 2000;

						// - Special -  21  -  SPIN KICK FULL
						Forge[AIcount].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Forge[AIcount].Q_Brain.Decision.F_Special[21] = 1000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Forge[AIcount].Q_Brain.Decision.F_Move[0] = 5000;

						// - Move -  2  -  SideStep
						Forge[AIcount].Q_Brain.Decision.F_Move[1] = 2000;

						// - Move -  3  -  JUMP
						Forge[AIcount].Q_Brain.Decision.F_Move[2] = 800;

						// - Move -  4  -  Roll Low Left
						Forge[AIcount].Q_Brain.Decision.F_Move[3] = 500;

						// - Move -  5  -  Roll Low Right
						Forge[AIcount].Q_Brain.Decision.F_Move[4] = 500;

						// - Move -  6  -  CartWheel Left
						Forge[AIcount].Q_Brain.Decision.F_Move[5] = 700;

						// - Move -  7  -  CartWheel Right
						Forge[AIcount].Q_Brain.Decision.F_Move[6] = 700;

						// - Move -  8  -  Forward Roll
						Forge[AIcount].Q_Brain.Decision.F_Move[7] = 200;

						// - Move -  9  -  Dodge Left
						Forge[AIcount].Q_Brain.Decision.F_Move[8] = 600;

						// - Move -  10  -  BackFlip
						Forge[AIcount].Q_Brain.Decision.F_Move[9] = 700;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Forge[AIcount].Q_Brain.Decision.SUM_Attack = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Combo = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Special = 0;
						Forge[AIcount].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Attack += Forge[AIcount].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Combo += Forge[AIcount].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Special += Forge[AIcount].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							Forge[AIcount].Q_Brain.Decision.SUM_Move += Forge[AIcount].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Forge[AIcount].Q_Brain.Decision.FactorSUM =
														Forge[AIcount].Q_Brain.Decision.F_Delay
														+ Forge[AIcount].Q_Brain.Decision.SUM_Attack
														+ Forge[AIcount].Q_Brain.Decision.SUM_Combo
														+ Forge[AIcount].Q_Brain.Decision.SUM_Special
														+ Forge[AIcount].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Forge[AIcount].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Forge[AIcount].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Forge[AIcount].Q_Brain.Decision.Finger > 0 && Forge[AIcount].Q_Brain.Decision.Finger < Forge[AIcount].Q_Brain.Decision.F_Delay) Forge[AIcount].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Forge[AIcount].Q_Brain.Decision.INC_Search = Forge[AIcount].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Attack)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Attack[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 1;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Combo)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Combo[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 100;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Special)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Special[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 200;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Forge[AIcount].Q_Brain.Decision.NOM_Move)
							{
							if(Forge[AIcount].Q_Brain.Decision.Finger > Forge[AIcount].Q_Brain.Decision.INC_Search
								&& Forge[AIcount].Q_Brain.Decision.Finger < ( Forge[AIcount].Q_Brain.Decision.INC_Search + Forge[AIcount].Q_Brain.Decision.F_Move[helly])) Forge[AIcount].Q_Brain.Decision.Answer = helly + 300;

							Forge[AIcount].Q_Brain.Decision.INC_Search += Forge[AIcount].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Forge[AIcount].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;
				}


			//IMPORTANT #####################
			//#### TODO Add Condition Flag here and when to activate Decision

			if(Forge[AIcount].Q_Brain.Decision.DecOverride == 0)
				{

				if(Forge[AIcount].Q_Brain.Decision.ON == 1)
					{
					//### Reset Decision Live Status
					Forge[AIcount].Q_Brain.Decision.ON = 0;


					//#####- Finger Override -#####

					if(Forge[AIcount].Q_Brain.Decision.FingerOverride == 1)
						{
						Forge[AIcount].Q_Brain.Decision.Answer = Forge[AIcount].Q_Brain.Decision.FingerOverrideAnswer;
						Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
						}


					switch(Forge[AIcount].Q_Brain.Decision.Answer)
						{
						case 0:	//Delay
							{
							Forge[AIcount].Q_Brain.Decision.DecOverride = 1;
							Forge[AIcount].Q_Brain.Decision.DelayOn = 1;
							Forge[AIcount].Q_Brain.Decision.DelayTimeLock = Forge[AIcount].Q_Brain.Decision.OverrideTIMER + (rand() % 15) + 2;
							Forge[AIcount].Mposestate = 0;
							Forge[AIcount].idlemotion = 23;
							} break;

						case 1:	//Beta
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//### Attack once
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 12;	//21
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								Forge[AIcount].Q_Brain.Decision.DelaySwitch = 1;
								}
							} break;

						case 2:	//#### Single Attack Right Punch
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//### RLPunch
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;
								}
							} break;

						case 3:	//#### Single Right Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//### RMKick
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 11;

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;
								}
							} break;

						case 4:	//#### Single Attack Low Punch Right
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//### Low Right Punch
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 48;

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;
								}
							} break;

						case 5:	//#### Single Low Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//### Low Kick
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 43;

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;
								}
							} break;

						case 6:	//#### Single Renzou
							{
							//### Renzou
							if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 19;

							Forge[AIcount].astackcntdir[0] = 0;
							Forge[AIcount].astackcntdir[1]++;
							Forge[AIcount].astackcntdir[2] = 0;
							Forge[AIcount].astackcntdir[3] = 0;
							Forge[AIcount].astackcntdir[4] = 0;
							Forge[AIcount].astackcnt++;
							} break;
							

						case 100:	//Gamma
							{

							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 8;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].HB_Energy > 20 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 31;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								else
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 21;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								}
		
							} break;

						case 101:	//Delta
							{
							
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 11;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 13;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].HB_Energy > 70 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 41;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								else
									{												//TODO Add better resort attack
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 12;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								}

							} break;

						case 102:	//Omega
							{

							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 8;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 12;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].HB_Energy > 70 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 32;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								else
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 21;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								}
							
							} break;

						case 103:	//Combo 6 - Punch Low Punch
							{

							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 47;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 12;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].HB_Energy > 70 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 61;	//21

									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 104:	//Combo 7 - Low Low
							{

							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 47;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 48;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 43;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 40;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;
								}
							
							} break;

						case 105:	//Combo 8 - End With Low
							{

							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 8;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 43;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 8;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 32;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;
								}
							
							} break;

						case 106:	//Combo 9 - Punch Kick Punch then Golrekka
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 11;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 12;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 40;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;
								}
							} break;

						case 107:	//Combo 9 - Punch Kick Punch then Golrekka
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 11;	//21

								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcntdir[2] = 0;
								Forge[AIcount].astackcntdir[3] = 0;
								Forge[AIcount].astackcntdir[4] = 0;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 9;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;


								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 32;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;

								if(Forge[AIcount].astackcnt < 5) Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 40;	//21

								Forge[AIcount].astackcntdir[1]++;
								Forge[AIcount].astackcnt++;
								}
							} break;



						case 200:	//Special Attack - RHKick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 31;
										Forge[AIcount].HB_Energy -= 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 201:	//Special Attack - FlameUppercut
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 65 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 32;
										Forge[AIcount].HB_Energy -= 65 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 202:	//Special Attack - VHKick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 45 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 35;
										Forge[AIcount].HB_Energy -= 45 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 203:	//Special Attack - Leap Spin Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 22;
										Forge[AIcount].HB_Energy -= 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 204:	//Special Attack - Rush Elbow
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 65;
										Forge[AIcount].HB_Energy -= 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 205:	//Special Attack - SkyPush
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 25 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 41;
										Forge[AIcount].HB_Energy -= 25 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 206:	//Special Attack - Twist Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 35 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 61;
										Forge[AIcount].HB_Energy -= 35 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 207:	//Special Attack - Hover Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 45 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 55;
										Forge[AIcount].HB_Energy -= 45 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 208:	//Special Attack - Hadou-ken
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 150 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 50;
										Forge[AIcount].HB_Energy -= 150 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;


						case 209:	//Special Attack - JSRUSHUP
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 40 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 76;
										Forge[AIcount].HB_Energy -= 40 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 210:	//Special Attack - RUSH PUNCH NORMAL
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 85;
										Forge[AIcount].HB_Energy -= 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 211:	//Special Attack - RUSH PUNCH BIG HIT
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 86;
										Forge[AIcount].HB_Energy -= 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 212:	//Special Attack - RUSH Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 87;
										Forge[AIcount].HB_Energy -= 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 213:	//Special Attack - Static Kick
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo
								if(Forge[AIcount].HB_Energy > 200 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 75;
										Forge[AIcount].HB_Energy -= 200 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 214:	//Special Attack - JSRUSH
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 35 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 73;
										Forge[AIcount].HB_Energy -= 35 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 215:	//Special Attack - Power Combo 2
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 64;
										Forge[AIcount].HB_Energy -= 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 216:	//Special Attack - JS FLAME UPPERCUT
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 240 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].HB_Energy -= 240 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 57;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 217:	//Special Attack - HYPER KNEE FLEX
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 40 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 25;
										Forge[AIcount].HB_Energy -= 40 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 218:	//Special Attack - AIR DASH
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 53;
										Forge[AIcount].HB_Energy -= 30 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 219:	//Special Attack - SAKURA TRIBUTE
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 56;
										Forge[AIcount].HB_Energy -= 175 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 220:	//Special Attack - SPIN KICK FULL
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Forge[AIcount].HB_Energy > 170 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 34;
										Forge[AIcount].HB_Energy -= 170 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 221:	//Special Attack - CYCLONE KICK
							{
							if(Forge[AIcount].Q_Brain.ATTposON == 1)
								{
								//###Try a combo
								if(Forge[AIcount].HB_Energy > 200 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Forge[AIcount].astackcnt < 5)
										{
										Forge[AIcount].attackstack[Forge[AIcount].astackcnt] = 84;
										Forge[AIcount].HB_Energy -= 200 / Forge[AIcount].CharDATA.BodySKILL.RELEnergyEff;
										}
									Forge[AIcount].astackcntdir[0] = 0;
									Forge[AIcount].astackcntdir[1]++;
									Forge[AIcount].astackcntdir[2] = 0;
									Forge[AIcount].astackcntdir[3] = 0;
									Forge[AIcount].astackcntdir[4] = 0;
									Forge[AIcount].astackcnt++;
									}
								}
							} break;

						case 300:	//Taunt
							{
							//### Taunt
							Forge[AIcount].Mposestate = 51;
							Forge[AIcount].runposecnt = 0;
							} break;

						case 301:	//Move into Position / Alternately Sidestep
							{
							Forge[AIcount].Q_Brain.Decision.DelaySwitch = 0;

							Forge[AIcount].Running = 0;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 1;
							Forge[AIcount].Q_Brain.MoveSide = 1;
							Forge[AIcount].Q_Brain.MoveTimeLock = Forge[AIcount].Q_Brain.Decision.OverrideTIMER;
							Forge[AIcount].Q_Brain.MoveFinger = rand() % 10;
							if(Forge[AIcount].Q_Brain.MoveFinger <= 5) Forge[AIcount].Q_Brain.MoveDirect = -1;
							if(Forge[AIcount].Q_Brain.MoveFinger > 5)  Forge[AIcount].Q_Brain.MoveDirect = 1;

							//Attack position achieved
							Forge[AIcount].Q_Brain.ATTposON = 1;
							
							Forge[AIcount].ForwardSpeed = (Forge[AIcount].PlayerSpeed/2)*TimeScale;

							if(Forge[AIcount].Q_Brain.MoveDirect < 0)
								{
								if(((Forge[AIcount].Mposestate != 5 && Forge[AIcount].Mposestate != 6 && !KEY_DOWN(QIN_w) && !KEY_DOWN(QIN_s)) || (Forge[AIcount].Mposestate != 5 && KEY_DOWN(QIN_LSHIFT))) && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15) && Forge[AIcount].Mposestate != 23)	//Dependent Movement mode switch
									{
									Forge[AIcount].Mposestate = 5;
									Forge[AIcount].StepTimer = 0;
									}

								//*** Actor
								Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
								Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
								Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
								Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, -Forge[AIcount].ForwardSpeed * Forge[AIcount].Q_Brain.MoveDirect, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
								}
							else
								{
								if(((Forge[AIcount].Mposestate != 5 && Forge[AIcount].Mposestate != 6 && !KEY_DOWN(QIN_w) && !KEY_DOWN(QIN_s)) || (Forge[AIcount].Mposestate != 5 && KEY_DOWN(QIN_LSHIFT))) && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15) && Forge[AIcount].Mposestate != 23)	//Dependent Movement mode switch
									{
									Forge[AIcount].Mposestate = 6;
									Forge[AIcount].StepTimer = 0;
									}

								//*** Actor
								Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
								Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
								Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
								Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed * Forge[AIcount].Q_Brain.MoveDirect, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
								}

#if 0
							Forge[AIcount].AV.OldPos.y += 60;
							Forge[AIcount].AV.NewPos.y += 60;

							// This does collision detection
							if(Qpo->Collision_RayTest(
										 NULL,
										 NULL,
										 &Forge[AIcount].AV.OldPos,
										 &Forge[AIcount].AV.NewPos,
										 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
										 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
										 0xffffffff, NULL, NULL,
										 &Forge[AIcount].AV.Collision))
								{
								// Set the new pos to the point of collision
								//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
								Forge[AIcount].collide = 1;
								}

							Forge[AIcount].AV.OldPos.y -= 60;
							Forge[AIcount].AV.NewPos.y -= 60;
#endif
							
							// Set the player to the new pos
							if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

							} break;

						case 302:	//#### Jump
							{
							if((Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//### Forward First Jump
								{
								Forge[AIcount].JumpDir = 0;

								Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
								//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

								if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

								Forge[AIcount].jumpposecnt = 0;
								Forge[AIcount].Mposestate = 11;
								Forge[AIcount].JumpFG = 0;
								}
							else
								{		//### Forward Second Jump
								if(Forge[AIcount].Mposestate == 11)
									{
									Forge[AIcount].JumpDir = 0;

									Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].JumpVec);
									//Qpo->Vec3d_Inverse(&Forge[AIcount].JumpVec);

									if(KEY_DOWN(QIN_w)) Forge[AIcount].JumpDir = 1;	//Forward Jump

									Forge[AIcount].jumpposecnt = 0;
									Forge[AIcount].Mposestate = 12;
									Forge[AIcount].JumpFG = 0;
									}
								}
							} break;

						case 303:	//#### Roll Low Left
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 23 && Forge[AIcount].Mposestate != 24 && Forge[AIcount].Mposestate != 28 && Forge[AIcount].Mposestate != 29)
								{
								Forge[AIcount].Mposestate = 28;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].SideSpeed = 0;
								Forge[AIcount].JumpOff = 0;
								}
							} break;

						case 304:	//#### Roll Low Right
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 23 && Forge[AIcount].Mposestate != 24 && Forge[AIcount].Mposestate != 28 && Forge[AIcount].Mposestate != 29)
								{
								Forge[AIcount].Mposestate = 29;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].SideSpeed = 0;
								Forge[AIcount].JumpOff = 0;
								}
							} break;

						case 305:	//#### CartWheel Left
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 23 && Forge[AIcount].Mposestate != 24 && Forge[AIcount].Mposestate != 28 && Forge[AIcount].Mposestate != 29)
								{
								Forge[AIcount].Mposestate = 23;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].SideSpeed = 0;
								Forge[AIcount].JumpOff = 0;
								}
							} break;

						case 306:	//#### CartWheel Right
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 23 && Forge[AIcount].Mposestate != 24 && Forge[AIcount].Mposestate != 28 && Forge[AIcount].Mposestate != 29)
								{
								Forge[AIcount].Mposestate = 24;
								Forge[AIcount].runposecnt = 1.67;
								Forge[AIcount].SideSpeed = 0;
								Forge[AIcount].JumpOff = 0;
								}
							} break;

						case 307:	//#### Forward Roll
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 8)
								{
								Forge[AIcount].Mposestate = 26;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].attackon = 0;
								Forge[AIcount].attposecnt = 0;
								}
							} break;

						case 308:	//#### Dodge Left
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 8)
								{
								Forge[AIcount].Mposestate = 25;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].SideSpeed = 0;
								}
							} break;

						case 309:	//#### BackFlip
							{
							if(Forge[AIcount].Mposestate != 9 && Forge[AIcount].Mposestate != 25 && Forge[AIcount].Mposestate != 26 && Forge[AIcount].Mposestate != 8 && Forge[AIcount].Aposestate != 62)
								{
								Forge[AIcount].Mposestate = 8;
								Forge[AIcount].runposecnt = 0;
								Forge[AIcount].astackcnt = 0;
								Forge[AIcount].astackrun = 0;
								Forge[AIcount].astackcntdir[0] = 0;
								Forge[AIcount].attposecnt = 0;
								Forge[AIcount].Aposestate = 0;
								Forge[AIcount].blendamount[0] = 0;
								Forge[AIcount].TrailsOn = 0;
								Forge[AIcount].attackon = 0;
								}
							} break;

						}//End Decision Switch

					}//END Decision ON

				}//END Override
			else	
				{//###Decision Overrides

				//### Reset Decision Live Status
				Forge[AIcount].Q_Brain.Decision.ON = 0;

				//## Side Step
				if(Forge[AIcount].Q_Brain.MoveSide == 1)
					{
					if(Forge[AIcount].attackon == 0)
						{
						//Attack position achieved
						Forge[AIcount].Q_Brain.ATTposON = 1;
								
						if (KEY_DOWN(QIN_LSHIFT)) Forge[AIcount].ForwardSpeed = -(Forge[AIcount].PlayerSpeed/4)*TimeScale;		//Slow Sidestep Left
						else Forge[AIcount].ForwardSpeed = (Forge[AIcount].PlayerSpeed/2)*TimeScale;							//Sidestep Left
						
						if(Forge[AIcount].Q_Brain.MoveDirect < 0)
							{
							if(Forge[AIcount].Mposestate != 5 && Forge[AIcount].Mposestate != 6 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15) && Forge[AIcount].Mposestate != 23)	//Dependent Movement mode switch
								{
								Forge[AIcount].Mposestate = 5;
								Forge[AIcount].StepTimer = 0;
								Forge[AIcount].blendamount[0] = 0; //Optimise me pls
								Forge[AIcount].blendamount[1] = 0; //Optimise me pls
								Forge[AIcount].blendamount[2] = 0; //Optimise me pls
								Forge[AIcount].blendamount[3] = 0; //Optimise me pls
								Forge[AIcount].runposecnt = 0.4;
								Forge[AIcount].idleposecnt = 0;
								Forge[AIcount].StepTimer = 0;
								}

							//*** Actor
							Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
							Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
							Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Left);
							Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed * Forge[AIcount].Q_Brain.MoveDirect, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
							}
						else
							{
							if(Forge[AIcount].Mposestate != 5 && Forge[AIcount].Mposestate != 6 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15) && Forge[AIcount].Mposestate != 23)	//Dependent Movement mode switch
								{
								Forge[AIcount].Mposestate = 6;
								Forge[AIcount].StepTimer = 0;
								Forge[AIcount].blendamount[0] = 0; //Optimise me pls
								Forge[AIcount].blendamount[1] = 0; //Optimise me pls
								Forge[AIcount].blendamount[2] = 0; //Optimise me pls
								Forge[AIcount].blendamount[3] = 0; //Optimise me pls
								Forge[AIcount].runposecnt = 0.08;
								Forge[AIcount].idleposecnt = 0;
								Forge[AIcount].StepTimer = 0;
								}

							//*** Actor
							Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
							Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
							Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Left);
							Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed * Forge[AIcount].Q_Brain.MoveDirect, &Forge[AIcount].AV.Left, &Forge[AIcount].AV.NewPos);
							}

#if 0
						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Forge[AIcount].AV.OldPos, 
									 &Forge[AIcount].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Forge[AIcount].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
							Forge[AIcount].collide = 1;
							}

						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
#endif

						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

						if(Forge[AIcount].Q_Brain.Decision.OverrideTIMER > Forge[AIcount].Q_Brain.MoveTimeLock + 10)
							{
							Forge[AIcount].Q_Brain.MoveSide = 0;
							Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
							}
						}
					}


				//##Delay
				if(Forge[AIcount].Q_Brain.Decision.DelayOn == 1)
					{
					Forge[AIcount].Mposestate = 0;
					Forge[AIcount].idlemotion = 23;

					if(Forge[AIcount].Q_Brain.Decision.OverrideTIMER > Forge[AIcount].Q_Brain.Decision.DelayTimeLock)
						{
						Forge[AIcount].Q_Brain.Decision.DelayOn = 0;
						Forge[AIcount].Q_Brain.Decision.DecOverride = 0;
						}
					}


				Forge[AIcount].Q_Brain.Decision.OverrideTIMER++;

				}//END Else - Decision Overide

			//BREAK HAND TO HAND ATTACK
			} break;



		case 8:   //Long Range Attack
			{
			LoopON = 0;

			Forge[AIcount].Mposestate = 0;
			Forge[AIcount].idlemotion = 23;

				//###Check Vision
			Forge[AIcount].Q_Brain.VisionCHK = 1;

				//###Lock On
				//Turn to Face Avatar Conditional (Not in Hit Reaction)
			if(Forge[AIcount].WeaponStatus != 8 && Forge[AIcount].Aposestate != 26 && Forge[AIcount].Aposestate != 30 && Forge[AIcount].Aposestate != 51 && Forge[AIcount].Aposestate != 52)
				{

				//####### -  Mode Universal Avatar Control - Update if required for mode specific Control -#####

				//##### Turn to Face Avatar - Target in View
				if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
					{
					if(Forge[AIcount].Aposestate != 13)
						{
						Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng/1.5;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng/1.5);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);
						}
					else
						{
						Forge[AIcount].Angles.y += (Forge[AIcount].ScanTurnAng / 1.5) + 0.07;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, (Forge[AIcount].ScanTurnAng / 1.5) + 0.07);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);
						}


					//##### TEMP Runn towards enemy
					//###Run Towards Avatar

					Forge[AIcount].ForwardSpeed = 10*TimeScale;
					if(Forge[AIcount].Mposestate != 3) Forge[AIcount].StepTimer = 0;
					Forge[AIcount].Mposestate = 3;
					Forge[AIcount].Running = 1;

					//*** Actor
					Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
					Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
					Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
					Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

					Forge[AIcount].AV.OldPos.y += 60;
					Forge[AIcount].AV.NewPos.y += 60;

					// This does collision detection
					if(Qpo->Collision_RayTest(
								 NULL, 
								 NULL, 
								 &Forge[AIcount].AV.OldPos, 
								 &Forge[AIcount].AV.NewPos, 
								 //GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
								 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
								 0xffffffff, NULL, NULL, 
								 &Forge[AIcount].AV.Collision))
						{
						// Set the new pos to the point of collision
						//Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;
						Forge[AIcount].collide = 1;
						}
					
					Forge[AIcount].AV.OldPos.y -= 60;
					Forge[AIcount].AV.NewPos.y -= 60;
					
						
					// Set the player to the new pos
					if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;

					//Attack position not achieved yet
					Forge[AIcount].Q_Brain.ATTposON = 0;
					Forge[AIcount].Q_Brain.ATTinitiated = 0;
					Forge[AIcount].Q_Brain.Decision.FingerOverride = 0;
					Forge[AIcount].Q_Brain.Decision.DecOverride = 0;


					//##### Drop target if dead
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockID].Health <= 0)
						{
						Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
						Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
						Forge[AIcount].Q_Brain.HeadAngles.x = 0;
						Forge[AIcount].Q_Brain.HeadSearch = 0;
						Forge[AIcount].Q_Brain.HeadDir = 1;
						Forge[AIcount].Q_Brain.HeadAngles.x = 0;
						Forge[AIcount].Q_Brain.MeMLock = 0;
						Forge[AIcount].Q_Brain.TargetLOCK = 0;
						Forge[AIcount].Q_Brain.TargetLOCKID = 0;
						Forge[AIcount].Q_Brain.TargetSIGHT = 0;
						Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
						Forge[AIcount].Q_Brain.TargetLOST = 0;
						Forge[AIcount].Q_Brain.TargetWENTltr = 0;
						Forge[AIcount].Q_Brain.TargetWENTutd = 0;
						Forge[AIcount].Q_Brain.TargetFIND = 0;
						Forge[AIcount].Q_Brain.ATTMmemID = 0;
						//Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
						Forge[AIcount].Mposestate = 0;
						Forge[AIcount].blendamount[8] = 0;
						Forge[AIcount].blendamount[0] = 0;
						Forge[AIcount].AttackIdle = 2000;
						Forge[AIcount].Q_Brain.idlecnt = 10;
						Forge[AIcount].Aposestate = 0;
						Forge[AIcount].attackon = 0;

						if(Forge[AIcount].Aposestate != 100 && Forge[AIcount].AirBorn == 0)
							{
							Forge[AIcount].Aposestate = 100;
							Forge[AIcount].attackon = 1;
							Forge[AIcount].attposecnt = 0;
							Forge[AIcount].astackcnt = 0;
							Forge[AIcount].astackrun = 0;
							Forge[AIcount].astackcntdir[0] = 0;
							}
						}

					//### Activate Timed Search
					if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 20)
						{ Forge[AIcount].Q_Brain.TargetSPOTTED = 1; }

					Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
					Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
					Forge[AIcount].Q_Brain.PERFECTTENtimer = 0;
					Forge[AIcount].Q_Brain.HeadAngles.x = 0;
					Forge[AIcount].Q_Brain.HeadSearch = 0;
					Forge[AIcount].Q_Brain.HeadDir = 1;
					Forge[AIcount].Q_Brain.HeadAngles.x = 0;

					Forge[AIcount].Q_Brain.TargetFIND = 0;
					}
				else //##### Turn to Face Avatar - Target Vanished
					{
					if(Forge[AIcount].Q_Brain.TargetLOCK == 1)
						{

						//##### - PERFECT TEN TIMED TARGET LOCK SYSTEM - #####

						if(Forge[AIcount].Q_Brain.PERFECTTENtimer < 10)
							{
							if(Forge[AIcount].Q_Brain.TargetLOCKID == 250)
								{
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV.Xform.Translation;
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							else
								{
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos = Forge[Forge[AIcount].Q_Brain.TargetLOCKID].AV.Xform.Translation;
								Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							}

						Forge[AIcount].Q_Brain.PERFECTTENtimer++;


						//#### Turn To PERFECT Enemy Position
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_GetUp(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Left);
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);
						Qpo->Vec3d_Copy(&Forge[AIcount].AV.Left, &Forge[AIcount].AV.Right);
						Qpo->Vec3d_Inverse(&Forge[AIcount].AV.Right);
						
						TempVec1 = Forge[AIcount].AV.Xform.Translation;
						TempVec1.y += 65;

						Qpo->Vec3d_Subtract(&Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos, &TempVec1, &Forge[AIcount].ScanVecTo);
						Qpo->Vec3d_Normalize(&Forge[AIcount].ScanVecTo);

						Qpo->Vec3d_Subtract(&Forge[AIcount].AV.Up, &Forge[AIcount].ScanVecTo, &ScanTurnVec);
						Forge[AIcount].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
						Forge[AIcount].ScanTurnAng /= 2;

						ScanDistL = Qpo->Vec3d_DistanceBetween(&Forge[AIcount].ScanVecTo, &Forge[AIcount].AV.Left);
						ScanDistR = Qpo->Vec3d_DistanceBetween(&Forge[AIcount].ScanVecTo, &Forge[AIcount].AV.Right);

						if(ScanDistL < ScanDistR) Forge[AIcount].ScanTurnAng *= -1;

						Forge[AIcount].Angles.y += Forge[AIcount].ScanTurnAng / 3;
						if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
						if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);


						Forge[AIcount].Q_Brain.TargetLOSTtimer++;
						Forge[AIcount].Q_Brain.TargetHIDEtimer++;


							//### Timed Search End
						if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 150 && Forge[AIcount].Q_Brain.TargetSPOTTED == 1)
							{ Forge[AIcount].Q_Brain.TargetSPOTTED = 0; }

							//### Conditional Target Drop
						if(Forge[AIcount].Q_Brain.TargetLOSTtimer > 50)
							{
							Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
							Forge[AIcount].Q_Brain.TargetHIDEtimer = 0;
							Forge[AIcount].Q_Brain.HeadAngles.x = 0;
							Forge[AIcount].Q_Brain.HeadSearch = 0;
							Forge[AIcount].Q_Brain.HeadDir = 1;
							Forge[AIcount].Q_Brain.HeadAngles.x = 0;
							Forge[AIcount].Q_Brain.MeMLock = 0;
							Forge[AIcount].Q_Brain.TargetLOCK = 0;
							Forge[AIcount].Q_Brain.TargetLOCKID = 0;
							Forge[AIcount].Q_Brain.TargetSIGHT = 0;
							Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
							Forge[AIcount].Q_Brain.TargetLOST = 0;
							Forge[AIcount].Q_Brain.TargetWENTltr = 0;
							Forge[AIcount].Q_Brain.TargetWENTutd = 0;
							Forge[AIcount].Q_Brain.TargetFIND = 0;
							Forge[AIcount].Q_Brain.ATTMmemID = 0;
							Forge[AIcount].Q_Brain.MindState = MIND_ACTIVE;
							Forge[AIcount].Mposestate = 0;
							Forge[AIcount].blendamount[8] = 0;
							Forge[AIcount].blendamount[0] = 0;
							Forge[AIcount].AttackIdle = 2000;
							Forge[AIcount].Q_Brain.idlecnt = 10;
							Forge[AIcount].Aposestate = 0;
							Forge[AIcount].attackon = 0;
							break;
							}


						if(Forge[AIcount].Q_Brain.TargetSPOTTED == 0)
							{
							if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
								{
								if(Forge[AIcount].Q_Brain.TargetHIDEtimer > 50)
									{

									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.25 > -(PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.25;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.25 < (PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.25;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}

									if(Forge[AIcount].Q_Brain.HeadAngles.x < 0.05 && Forge[AIcount].Q_Brain.HeadAngles.x > -0.05)
										Forge[AIcount].Q_Brain.TargetHIDEtimer = 50;

									Forge[AIcount].Q_Brain.HeadSearch = 1;
									}
								}


							if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetLOST == 1)	//Target Moves From View
								{
								if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetWENTltr == 1)
									{
									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.4 > -(PI/1.5) ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.4;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.4 <= 0 ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.4;
										else 
											{
											if(Forge[AIcount].Aposestate != 100 && Forge[AIcount].AirBorn == 0)
												{
												Forge[AIcount].Aposestate = 100;
												Forge[AIcount].attackon = 1;
												Forge[AIcount].attposecnt = 0;
												Forge[AIcount].astackcnt = 0;
												Forge[AIcount].astackrun = 0;
												Forge[AIcount].astackcntdir[0] = 0;
												}
											}
										}
									}


								if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].TargetWENTltr == 2)
									{
									if(Forge[AIcount].Q_Brain.HeadDir == 1)
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x + 0.4 < (PI/2) ) Forge[AIcount].Q_Brain.HeadAngles.x += 0.4;
										else Forge[AIcount].Q_Brain.HeadDir *= -1;
										}
									else
										{
										if(Forge[AIcount].Q_Brain.HeadAngles.x - 0.4 >= 0 ) Forge[AIcount].Q_Brain.HeadAngles.x -= 0.4;
										else 
											{
											if(Forge[AIcount].Aposestate != 100)
												{
												Forge[AIcount].Aposestate = 100;
												Forge[AIcount].attackon = 1;
												Forge[AIcount].attposecnt = 0;
												Forge[AIcount].astackcnt = 0;
												Forge[AIcount].astackrun = 0;
												Forge[AIcount].astackcntdir[0] = 0;
												}
											}
										}
									}

								Forge[AIcount].Q_Brain.HeadSearch = 1;
								}//END Target Lost 1

							}//END Target Spotted

						}//END TargetLOCK

					}//END Else - TargetLOCK


				//## Aim Weapon Up / Down
				if(Forge[AIcount].WeaponStatus == 5)
					{
					//Do No Aiming Adjustments ***
					/*Qpo->Avatar_GetBoneTransform(&Forge[AIcount].Weapon, "BONE03", &Forge[AIcount].TempXForm1);
					Qpo->Transform_GetUp(&Forge[AIcount].TempXForm1, &Forge[AIcount].AimVec);
					Qpo->Vec3d_Inverse(&Forge[AIcount].AimVec);

					Qpo->Transform_GetIn(&Forge[AIcount].AV.Xform, &Forge[AIcount].AV.Up);

					if(Forge[AIcount].AimVec.y > Forge[AIcount].AV.Up.y-0.03)
						Forge[AIcount].WeaponAimer +=  0.02;
					else Forge[AIcount].WeaponAimer -=  0.02;*/

					if(Forge[AIcount].Q_Brain.TargetSIGHT == 1 || Forge[AIcount].Q_Brain.TargetFIND == 1)
						{
						Qpo->Avatar_GetBoneTransform(&Forge[AIcount].Weapon, "BONE03", &Forge[AIcount].TempXForm1);
						Qpo->Transform_GetUp(&Forge[AIcount].TempXForm1, &Forge[AIcount].AimVec);
						Qpo->Vec3d_Inverse(&Forge[AIcount].AimVec);
						TempVec2 = Forge[AIcount].AimVec;
						Tempfloat1 = Qpo->Vec3d_DistanceBetween(&Forge[AIcount].TempXForm1.Translation, &Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockID].Pos);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].TempXForm1.Translation, Tempfloat1, &Forge[AIcount].AimVec, &Forge[AIcount].AimVec);

						Qpo->Vec3d_Subtract(&Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockID].Pos, &Forge[AIcount].TempXForm1.Translation,  &TempVec1);
						Qpo->Vec3d_Normalize(&TempVec1);
						Qpo->Vec3d_Normalize(&TempVec2);

						Qpo->Vec3d_Subtract(&TempVec2, &TempVec1, &Forge[AIcount].ScanVecToAimer);
						Forge[AIcount].ScanTurnAngAimer = Qpo->Vec3d_Length(&Forge[AIcount].ScanVecToAimer);
						Forge[AIcount].ScanTurnAngAimer /= 4;	//2

						if(TempVec2.y < TempVec1.y)
							Forge[AIcount].ScanTurnAngAimer *= -1;

						Forge[AIcount].WeaponAimer += Forge[AIcount].ScanTurnAngAimer;
						}
					}

				}//END Conditional - Hit Reaction
				

				//Draw Weapon from backpack
			if(Forge[AIcount].WeaponDrawn == 0)
				{
				Forge[AIcount].DrawWeapon = 1;
				Forge[AIcount].WeaponDrawn = 1;
				}

			//Aim Weapon
			Forge[AIcount].WeaponAIM = 1;

			//Avatar Firing
			if(Forge[AIcount].Q_Brain.TargetSIGHT == 1)
				{
				if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 500)
					{
					Forge[AIcount].WeaponFire = 1;
					Forge[AIcount].FireRated = 0;
					Forge[AIcount].FireRateTimer = 0;
					}
				if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 500 && Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 1000 && Forge[AIcount].FireRated <= 3)
					{
					Forge[AIcount].WeaponFire = 1;
					Forge[AIcount].FireRated++;
					Forge[AIcount].FireRateTimer = 0;
					}
				if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 1000 && Forge[AIcount].FireRated < 1)
					{
					Forge[AIcount].WeaponFire = 1;
					Forge[AIcount].FireRated++;
					Forge[AIcount].FireRateTimer = 0;
					}
				}

			Forge[AIcount].FireRateTimer++;
			if(Forge[AIcount].FireRateTimer == 6) Forge[AIcount].FireRated = 0;


			//Holster weapon and change mode if enemy is too near Or Mode Return is Activated
			if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 140 || (Forge[AIcount].Q_Brain.MODERETURN_H2H == 1 && (Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.ATTMmemID].MeMLockID].Pos.y < Forge[AIcount].AV.Xform.Translation.y + 100)))
				{
				Forge[AIcount].Q_Brain.HeadSearch = 0;
				Forge[AIcount].WeaponHolster = 1;
				Forge[AIcount].DrawWeapon = 0;
				Forge[AIcount].WeaponDrawn = 0;
				Forge[AIcount].WeaponAIM = 0;
				Forge[AIcount].WeaponFire = 0;
				Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
				}

			if(Forge[AIcount].HitShield > 0)
				{
				Forge[AIcount].HitShield = 0;
				Forge[AIcount].Q_Brain.HeadSearch = 0;
				Forge[AIcount].WeaponHolster = 1;
				Forge[AIcount].DrawWeapon = 0;
				Forge[AIcount].WeaponDrawn = 0;
				Forge[AIcount].WeaponAIM = 0;
				Forge[AIcount].WeaponFire = 0;
				Forge[AIcount].Q_Brain.MindState = MIND_HANDATTK;
				}

			} break;

		}//END Main Mode Switch



		//#####--  Avatar View Scan  --#####//

	if(Forge[AIcount].Q_Brain.VisionCHK == 1)
		{
			
		//### Avatar Scans View
		Q.AIFunctionsScannerCheck(AIcount);

		Forge[AIcount].Q_Brain.VisionCHK = 0;
		}




		//#####-- Location Control For Class 'Cleric' --#####

switch(Forge[AIcount].Role)	//####- Switch Avatar's Current Role
	{
	case 0:	//## Standard Freelance Mode
		{
		switch(Forge[AIcount].Q_Brain.LocationState) //####- Switch Avatar's Current Location Mode
			{
			case 0:	//## Initialisation Mode Avatar Just Spawned or reset
				{
				} break;

			}
		} break;


	case 1:	//## Active Team Mode
		{
		switch(Forge[AIcount].Q_Brain.LocationState)
			{

			case 0:	//## Initialisation Mode Avatar Just Spawned or reset
				{

					//### Leader Is Present
				if(Forge[AIcount].Q_Brain.TargetLEADER == 1) Forge[AIcount].Q_Brain.LocationState = 1;

				} break;


			case 1:
				{
					//### Not Locked Onto Enemy Then Lock On the Leader
				if((Forge[AIcount].Q_Brain.TargetLOCK == 0 && Forge[AIcount].Q_Brain.TargetLEADER == 1) || (Forge[AIcount].Q_Brain.TargetLOCK == 1 && Forge[AIcount].Q_Brain.TargetLOSTtimer > 1500))
					{
					Forge[AIcount].ScanTurnAng = 0;
					Forge[AIcount].Angles.y += Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3;
					if(Forge[AIcount].Angles.y > (PI*2)) Forge[AIcount].Angles.y = 0;
					if(Forge[AIcount].Angles.y < 0) Forge[AIcount].Angles.y = (PI*2);

					Qpo->Transform_New_YRotation(&AIfriendly, Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3);
					Qpo->Transform_Multiply(&Forge[AIcount].AV.Xform, &AIfriendly, &Forge[AIcount].AV.Xform);
					
					//Forge[AIcount].Q_Brain.TargetLOSTtimer = 0;
					//Forge[AIcount].Q_Brain.HeadAngles.x = 0;
					//Forge[AIcount].Q_Brain.HeadSearch = 0;
					//Forge[AIcount].Q_Brain.HeadDir = 1;
					//Forge[AIcount].Q_Brain.HeadAngles.x = 0;

					Forge[AIcount].Q_Brain.TargetFIND = 0;


					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 80)
						{

						if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist < 160 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
							{
							//### Walk Towards Player
							Forge[AIcount].ForwardSpeed = 2*TimeScale;//Forge[AIcount].PlayerSpeed*TimeScale;  //Run Forwards
							Forge[AIcount].Running = 0;

							if(Forge[AIcount].Mposestate != 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//Movement mode switch
								{
								Forge[AIcount].Mposestate = 1;
								Forge[AIcount].StepTimer = 0;
								//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
								//Forge[AIcount].runposecnt = 0;
								//Forge[AIcount].idleposecnt = 0;
								}
							}
						else
							{
							//### Run Towards Player
							Forge[AIcount].ForwardSpeed = 8*TimeScale;//Forge[AIcount].PlayerSpeed*TimeScale;  //Run Forwards
							Forge[AIcount].Running = 1;

							if(Forge[AIcount].Mposestate != 3 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//Movement mode switch
								{
								Forge[AIcount].Mposestate = 3;
								Forge[AIcount].StepTimer = 0;
								//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
								//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
								//Forge[AIcount].runposecnt = 0;
								//Forge[AIcount].idleposecnt = 0;
								}
							}

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;
						Qpo->Transform_GetLeft(&Forge[AIcount].AV.Xform,&Forge[AIcount].AV.Up);
						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
							{ /*Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;*/ Forge[AIcount].collide = 1; }

						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
				
						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;
						}
					else
						{
						Forge[AIcount].Running = 0;

						if(Forge[AIcount].Q_Brain.TargetLOCK == 0)
							{
							Forge[AIcount].Mposestate = 0;
							//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
							//Forge[AIcount].runposecnt = 0;
							//Forge[AIcount].idleposecnt = 0;
							}
						}
					}
				else
					{
					if(Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 100 && Forge[AIcount].Q_Brain.TargetLEADER == 1 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))
						{
						//### Run Towards Player
						Forge[AIcount].ForwardSpeed = 8*TimeScale;//Forge[AIcount].PlayerSpeed*TimeScale;  //Run Forwards
						Forge[AIcount].Running = 1;
						
						if(Forge[AIcount].Mposestate != 3 && (Forge[AIcount].Mposestate != 10 && Forge[AIcount].Mposestate != 11 && Forge[AIcount].Mposestate != 12 && Forge[AIcount].Mposestate != 13 && Forge[AIcount].Mposestate != 14 && Forge[AIcount].Mposestate != 15))	//Movement mode switch
							{
							Forge[AIcount].Mposestate = 3;
							Forge[AIcount].StepTimer = 0;
							//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
							//Forge[AIcount].runposecnt = 0;
							//Forge[AIcount].idleposecnt = 0;
							}

						//*** Actor
						Forge[AIcount].AV.OldPos = Forge[AIcount].AV.Xform.Translation;
						Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Xform.Translation;

						Qpo->Vec3d_Subtract(&Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].AIsPresent[Forge[AIcount].Q_Brain.MeMBank[Forge[AIcount].Q_Brain.MeMcurrent].MeMLockLeaderID].Pos, &Forge[AIcount].AV.Xform.Translation, &Forge[AIcount].AV.Up);
						Forge[AIcount].AV.Up.y = 0;
						Qpo->Vec3d_Normalize(&Forge[AIcount].AV.Up);
						Qpo->Vec3d_Inverse(&Forge[AIcount].AV.Up);


						Qpo->Vec3d_AddScaled(&Forge[AIcount].AV.OldPos, -Forge[AIcount].ForwardSpeed, &Forge[AIcount].AV.Up, &Forge[AIcount].AV.NewPos);

						Forge[AIcount].AV.OldPos.y += 60;
						Forge[AIcount].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(NULL, NULL, &Forge[AIcount].AV.OldPos, &Forge[AIcount].AV.NewPos, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &Forge[AIcount].AV.Collision))
							{ /*Forge[AIcount].AV.NewPos = Forge[AIcount].AV.Collision.Impact;*/ Forge[AIcount].collide = 1; }

						Forge[AIcount].AV.OldPos.y -= 60;
						Forge[AIcount].AV.NewPos.y -= 60;
											
						// Set the player to the new pos
						if(Forge[AIcount].collide == 0) Forge[AIcount].AV.Xform.Translation = Forge[AIcount].AV.NewPos;
						}
					else
						{
						Forge[AIcount].Running = 0;

						if(Forge[AIcount].Q_Brain.TargetLOCK == 0)
							{
							Forge[AIcount].Mposestate = 0;
							//Forge[AIcount].blendamount[0] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[1] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[2] = 0; //Optimise me pls
							//Forge[AIcount].blendamount[3] = 0; //Optimise me pls
							//Forge[AIcount].runposecnt = 0;
							//Forge[AIcount].idleposecnt = 0;
							}
						}
					}

				} break;

			}
		} break;


	case 2:	//Sentry Mode
		{
		switch(Forge[AIcount].Q_Brain.LocationState)
			{



			}
		} break;


	case 3:	//Search and Destroy Mode
		{
		switch(Forge[AIcount].Q_Brain.LocationState)
			{



			}
		} break;


	}//END Role Switch



	}//END FIGHTER BRAIN

};