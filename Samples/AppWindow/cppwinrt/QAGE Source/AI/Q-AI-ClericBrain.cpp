/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	*/#include "pch.h"/*- Minor Component -Cleric Brain-

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

	//#####-- AIBrain for 'CLERIC' Class --#####

void Q_COREFunctions::AIClericBrain(int AIcounter)
	{
	switch(Q_Forge->Forge[AIcounter].Q_Brain.MindState)
		{

		case 0:   //IdleMode
			{
			LoopON = 0;

			Q_Forge->Forge[AIcounter].Mposestate = 0;
			} break;

		case 1:   //ActiveModeInit		//Functionise these 'Modes'
			{
			LoopON = 0;


			Q_Forge->Forge[AIcounter].idlemotion=0;

			//if(Q_Forge->Forge[AIcounter].Mposestate == 0 && Q_Forge->Forge[AIcounter].blendamount[8] == 1)
			//	{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CLERIC_HEAL;	//EDIT <<<<<<<<<<<<<<<<<<<
				Q_Forge->Forge[AIcounter].Mposestate = 0;
				Q_Forge->Forge[AIcounter].blendamount[8] = 0;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0;
				Q_Forge->Forge[AIcounter].AttackIdle = 2000;
				Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;	//(float)rand() / 32767) - 0.5);
			//	}

			//Q_Forge->Forge[AIcounter].Mposestate = 8;
			} break;

		case 2:   //ActiveMode
			{
			LoopON = 0;

			if(Q_Forge->Forge[AIcounter].Q_Brain.idlecnt == 0) Q_Forge->Forge[AIcounter].Q_Brain.idlecnt--;//choose random movement
			else Q_Forge->Forge[AIcounter].Q_Brain.idlecnt--;
			//Decide whether or not to execute a movement
			//or to change mode

			//Loop\|/\|/\|/\|/\|/\|/

			//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;

			//=*=- Lock On
				//Turn to Face Avatar
			/*Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);*/


			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CRUNCHDECIDE;
				}
			else
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
				}



			//If Target Sighted Log in Memory Bank

			//Continue Movement

			//Loop\|/\|/\|/\|/\|/\|/

			} break;

		case 3:   //Check Vision	//TODO Full look around - Motion Required
			{
			/*if(Q.AIFunctionsScannerCheck(AIcounter) == true)	 //## Avatar Sighted ##
				{
					//#####Create Memory
				//Check for Attack Lock
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1) Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID;
				else Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.MeMcount;

				//TimeStamp
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Time = TIME;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].EventType = EVENT_AVATAR_SIGHTED;

				//Avatars Data
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].AI_ID = 250;	// Player Sighted TODO Something
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].MeMMindstate = -1;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].Pos = playerAV[g_Player]->Xform.Translation;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].Pos.y += 65;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].Ang = playerAV[g_Player]->Ang;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].VecTo = Q_Forge->Forge[AIcounter].ScanVecTo;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].Q_Forge->Forge[AIcounter].ScanTurnAng = Q_Forge->Forge[AIcounter].ScanTurnAng;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[0].ScanDist = Q_Forge->Forge[AIcounter].ScanAvatarDist;

				//Own Data
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMMindstate = Q_Forge->Forge[AIcounter].Q_Brain.MindState;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Pos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Ang = Q_Forge->Forge[AIcounter].AV.Ang;
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Health = Q_Forge->Forge[AIcounter].AV.
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Power = 
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].PowerLevel = 
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Weapon = 

					//####Act on Sighting
				//Q_Forge->Forge[AIcounter].Q_Brain.MindState = //MIND_CRUNCHDECIDE;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMcount++;
				}
			else
				{
				//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_SEARCHTARGET;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.MeMcount;
				}

			//Return
			Q_Forge->Forge[AIcounter].Q_Brain.MindState = Q_Forge->Forge[AIcounter].Q_Brain.StateMemory;*/
			} break;

		case 4:   //AttackMode
			{
			LoopON = 0;

				//Basic Ideas

				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;


			//=*=- Lock On
				//Turn to Face Avatar

			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

				//Run Towards Avatar

			Q_Forge->Forge[AIcounter].ForwardSpeed = 5*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].runposecnt = 0;
				Q_Forge->Forge[AIcounter].idleposecnt = 0;
				Q_Forge->Forge[AIcounter].StepTimer = 0;
				}

			//*** Actor
			Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
						 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
						 &Q_Forge->Forge[AIcounter].AV.OldPos, 
						 &Q_Forge->Forge[AIcounter].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &Q_Forge->Forge[AIcounter].AV.Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
				}

			Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
		
			// Set the player to the new pos
			Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
			} break;


		case 5:   //SearchMode
			{
			LoopON = 0;

				//Basic Ideas

			Q_Forge->Forge[AIcounter].Mposestate = 0;

				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;


			//=*=- Lock On
				//Turn to Face Avatar

			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

				/*Run Towards Avatar

			Q_Forge->Forge[AIcounter].ForwardSpeed = 5*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].runposecnt = 0;
				Q_Forge->Forge[AIcounter].idleposecnt = 0;
				}

			//*** Actor
			Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
						 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
						 &Q_Forge->Forge[AIcounter].AV.OldPos, 
						 &Q_Forge->Forge[AIcounter].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
						 0xffffffff, NULL, NULL, 
						 &Q_Forge->Forge[AIcounter].AV.Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;
				}
			
			Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;

		
			// Set the player to the new pos
			Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;*/

			} break;


		case 6:   //First Crunch Decision
			{
			LoopON = 0;

			//IMP initialisation requires timer to be reset

				//Basic Ideas

			Q_Forge->Forge[AIcounter].Mposestate = 0;
			Q_Forge->Forge[AIcounter].idlemotion = 23;

				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;

			//=*=- Lock On
				//Turn to Face Avatar
			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);


			//################################################################
			//Case Switch involving a weighted random factor
			//'Logic table' to run through factor possibilities for each event

			//Factor out possibilities with 'if' trees

			//Reset Pathway Factors
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_RunA = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Comm = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Obtain = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Power = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_AttPlan = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Delay = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_GoCrazy = 0;


			//Run Away
			//If(Health too low etc).....

			//Communicate
			//If(Radio exists).....

			//Obtain Item
			//If(Item needed and exists <- check memory.....

			//Power Up
			//If(Powering Up was at all possible

			//Long Range
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 170) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR = 5000;
			//else Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR = 0;

			//Hand To Hand
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 170) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H = 500;
			else Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H = 0;

			//Delay decision
			if(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Timer < 500) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Delay = 1000 - Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Timer;

			
			//Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


			//IMP increase number of added factors here to include new modes
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.FactorSUM = Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR
											+ Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H
											+ Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Delay;


				//###Seed the finger
			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.FactorSUM;


			//###Determine Result
				//Long Range
			if(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger < Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Answer = 0;

				//Hand To Hand
			if(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger > Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR
				&& Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR + Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H ) ) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Answer = 1;

				//Delay Decision
			if(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger > ( Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR + Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H )
				&& Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR + Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H + Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Delay ) ) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Answer = 2;



			switch(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Answer)
				{
				case 0:	//Long Range
					{
					/*FROZEN@@if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
						Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
						}*/
					} break;

				case 1:	//Hand To Hand
					{
					Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
					Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;
					} break;

				case 2:	//Delay
					{
					//Still Nothing
					} break;
				}

			Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Timer++;

			//################################################################

			} break;


		case 7:   //###===--- Hand To Hand Attack
			{
			LoopON = 0;

			Q_Forge->Forge[AIcounter].idlemotion = 37;


			//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;


			//###Lock On
				//Turn to Face Avatar
			if(Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 32 && Q_Forge->Forge[AIcounter].Aposestate != 33)
				{
					//Turn to Face Avatar - Target in View *
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
					{
					if(Q_Forge->Forge[AIcounter].Aposestate != 13)
						{
						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng/1.5;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng/1.5);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}
					else
						{
						Q_Forge->Forge[AIcounter].Angles.y += (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_ZRotation(&AIfriendly, (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}

					
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
					}
				else //Turn to Face Avatar - Target Vanished *
					{//Turn To Previous Enemy Position
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
						{
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
						Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Right);
						Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Right);
						
						TempVec1 = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						TempVec1.y += 65;

						Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos, &TempVec1, &Q_Forge->Forge[AIcounter].ScanVecTo);
						Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].ScanVecTo);

						Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanTurnVec);
						Q_Forge->Forge[AIcounter].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
						Q_Forge->Forge[AIcounter].ScanTurnAng /= 2;

						ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Left);
						ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Right);
						

						if(ScanDistL < ScanDistR) //Then Avatar is to the Left of the AIs view
							{
							Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;
							}


						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng / 3;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer++;


						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 2000)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CRUNCHDECIDE;
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 50)
								{

								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.25 > -(PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.25;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.25 < (PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.25;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}

								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x < 0.05 && Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x > -0.05)
									Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 73;

								Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 1;
								}
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 1)	//Target Moves From View
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetWENTltr == 1)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.4 > -(PI/1.5) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.4;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.4 <= 0 ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.4;
									else 
										{
										if(Q_Forge->Forge[AIcounter].Aposestate != 101)
											{
											Q_Forge->Forge[AIcounter].Aposestate = 101;
											Q_Forge->Forge[AIcounter].attackon = 1;
											Q_Forge->Forge[AIcounter].attposecnt = 0;
											Q_Forge->Forge[AIcounter].astackcnt = 0;
											Q_Forge->Forge[AIcounter].astackrun = 0;
											Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
											}
										}
									}
								}


							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetWENTltr == 2)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.4 < (PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.4;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.4 >= 0 ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.4;
									else 
										{
										if(Q_Forge->Forge[AIcounter].Aposestate != 101)
											{
											Q_Forge->Forge[AIcounter].Aposestate = 101;
											Q_Forge->Forge[AIcounter].attackon = 1;
											Q_Forge->Forge[AIcounter].attposecnt = 0;
											Q_Forge->Forge[AIcounter].astackcnt = 0;
											Q_Forge->Forge[AIcounter].astackrun = 0;
											Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
											}
										}
									}
								}

							Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 1;
							}

						}
					}

				}


			//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1) Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;

			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
				{
				//###Run Towards Avatar

				Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
						
				if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
					{
					Q_Forge->Forge[AIcounter].Mposestate = 3;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
					Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
					Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
					Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
					Q_Forge->Forge[AIcounter].runposecnt = 0;
					Q_Forge->Forge[AIcounter].idleposecnt = 0;
					Q_Forge->Forge[AIcounter].StepTimer = 0;
					}

				//*** Actor
				Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

				Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

				// This does collision detection
				if(Qpo->Collision_RayTest(
							 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
							 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
							 &Q_Forge->Forge[AIcounter].AV.OldPos, 
							 &Q_Forge->Forge[AIcounter].AV.NewPos, 
							 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
							 0xffffffff, NULL, NULL, 
							 &Q_Forge->Forge[AIcounter].AV.Collision))
					{
					// Set the new pos to the point of collision
					Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
					}
				
				Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
				
					
				// Set the player to the new pos
				Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

				//Attack position not achieved yet
				Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
				}
			else Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 0;



			//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

			Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;

			//~Check for being attacked
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Blocking == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitReaction == 0)
				{
				if(Q_Forge->Forge[AIcounter].BlockInit == 0)
					{
					Q_Forge->Forge[AIcounter].BlockInit = 1;
					//Need to decide here which action to take Blocking , dodge , movement
					//Force Block cancel attacks
					if( ( rand() % 10 ) < 7) Q_Forge->Forge[AIcounter].Blocking = 1;
					//Very crap error creation REDO
					}
				}
			else
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 0 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Blocking == 1)
					{
					Q_Forge->Forge[AIcounter].Blocking = 0;
					if(Q_Forge->Forge[AIcounter].BlockInit == 1)	//Counter Hit
						{
						Q_Forge->Forge[AIcounter].BlockInit = 0;
						}
						/*if( ( rand() % 2 ) < 2)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 4 );
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;
							}
						}*/
					}
				}


			if(Q_Forge->Forge[AIcounter].BlockHit == 1)
				{
				Q_Forge->Forge[AIcounter].BlockHit = 0;

				if( ( rand() % 2 ) < 2)
					{
					Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 4 );
					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;
					}
				}



			//~Check for enemy using weapon
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30)
				{	//Switch to Long Range Attack
				Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
				/*FROZEN@@if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
					{
					Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
					Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
					}*/
				}


			//TODO **** Continue an already running attack plan skipping decisions


			//DECISION SWITCH (dependent on target in sight)############################################

			if(Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
				{
				//###Reset Pathway Factors
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Omega = 0;

				//###Infuse Factors depending on situation with 'if' trees
				//Delay - Delay Decision
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 1000;
				
				//Reset Delay Switch
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;


				//Alpha - Movement highly weighted maybe
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 105) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 10000;
				else Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 1000;

				//Beta - Attack once lightly then rethink
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta = 500;

				//Gamma - Attack Combo 1
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma = 300;

				//Delta - Attack Combo 2
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta = 300;

				//Omega - Attack Combo 3
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Omega = 300;
	
				//IMP ********\/\/\/\/\/
				//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


				//IMP increase number of added factors here to include new modes
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
												Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
												+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha
												+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta
												+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma
												+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta
												+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Omega;


					//###Seed the finger
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


				//###Determine Result
					//Delay
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;

					//Alpha
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
					&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha ) ) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 1;

					//Beta
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha )
					&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta ) ) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 2;

					//Gamma
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta )
					&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma  ) ) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 3;

					//Delta
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma )
					&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta ) ) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 4;

					//Omega
				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta )
					&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Beta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Gamma + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delta + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Omega ) ) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 5;




				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0)	//Decision Overrides
					{

					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride == 1)	//Finger Override
						{
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						}

					switch(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer)
						{
						case 0:	//Delay
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayOn = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayTimeLock = Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER + (rand() % 15) + 5;;
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].idlemotion = 23;
							} break;

						case 1:	//Alpha
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;

							if(Q_Forge->Forge[AIcounter].attackon == 0)
								{
									//~Check to see if need to - Move into Position
								if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
									{
									//###Run Towards Avatar

									Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
									
									if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
										{
										Q_Forge->Forge[AIcounter].Mposestate = 3;
										Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
										Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
										Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
										Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
										Q_Forge->Forge[AIcounter].runposecnt = 0;
										Q_Forge->Forge[AIcounter].idleposecnt = 0;
										Q_Forge->Forge[AIcounter].StepTimer = 0;
										}

									//*** Actor
									Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
									Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
									Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
									Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

									Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
									Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

									// This does collision detection
									if(Qpo->Collision_RayTest(
												 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
												 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
												 &Q_Forge->Forge[AIcounter].AV.OldPos, 
												 &Q_Forge->Forge[AIcounter].AV.NewPos, 
												 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
												 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
												 0xffffffff, NULL, NULL, 
												 &Q_Forge->Forge[AIcounter].AV.Collision))
										{
										// Set the new pos to the point of collision
										Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
										}
									
									Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
									Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
									
								
									// Set the player to the new pos
									Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

									//Attack position not achieved yet
									Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
									Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
									}
								else
									{
										Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 1;
										Q_Forge->Forge[AIcounter].Q_Brain.MoveSide = 1;
										Q_Forge->Forge[AIcounter].Q_Brain.MoveTimeLock = Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER;
										Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger = rand() % 10;
										if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger <= 5) Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = -1;
										if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger > 5)  Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = 1;

										//Attack position achieved
										Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
										
										Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/2)*_->TimeScale;
										
										if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && !KEY_DOWN_w() && !KEY_DOWN_s()) || (Q_Forge->Forge[AIcounter].Mposestate != 5 && KEY_PRESS_DOWN(QIN_LSHIFT))) && Q_Forge->Forge[AIcounter].Mposestate != 7 && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
											{
											Q_Forge->Forge[AIcounter].Mposestate = 5;
											Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
											Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
											Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
											Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
											Q_Forge->Forge[AIcounter].runposecnt = 0;
											Q_Forge->Forge[AIcounter].idleposecnt = 0;
											Q_Forge->Forge[AIcounter].StepTimer = 0;
											}

										//*** Actor
										Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
										Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
										Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);

										Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
										Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

										// This does collision detection
										if(Qpo->Collision_RayTest(
													 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
													 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
													 &Q_Forge->Forge[AIcounter].AV.OldPos, 
													 &Q_Forge->Forge[AIcounter].AV.NewPos, 
													 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
													 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
													 0xffffffff, NULL, NULL, 
													 &Q_Forge->Forge[AIcounter].AV.Collision))
											{
											// Set the new pos to the point of collision
											Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
											}
										
										Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
										Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
										

										// Set the player to the new pos
										Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
									}
								}
						} break;

						case 2:	//Beta
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### Attack once
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;	//21
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							} break;

						case 3:	//Gamma
							{

							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 13;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
		
							} break;

						case 4:	//Delta
							{
							
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}

							} break;

						case 5:	//Omega
							{

							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							
							} break;
						}

					}

					else	//###Decision Overrides
						{

						//## Side Step
						if(Q_Forge->Forge[AIcounter].Q_Brain.MoveSide == 1)
							{
							if(Q_Forge->Forge[AIcounter].attackon == 0)
								{
								//Attack position achieved
								Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
										
								if (KEY_PRESS_DOWN(QIN_LSHIFT)) Q_Forge->Forge[AIcounter].ForwardSpeed = -(Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Left
								else Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/2)*_->TimeScale;							//Sidestep Left
										
								if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && !KEY_DOWN_w() && !KEY_DOWN_s()) || (Q_Forge->Forge[AIcounter].Mposestate != 5 && KEY_PRESS_DOWN(QIN_LSHIFT))) && Q_Forge->Forge[AIcounter].Mposestate != 7 && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
									{
									Q_Forge->Forge[AIcounter].Mposestate = 5;
									Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
									Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
									Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
									Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
									if(Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect < 0) Q_Forge->Forge[AIcounter].runposecnt = 0.08;
									else Q_Forge->Forge[AIcounter].runposecnt = 0.4;
									Q_Forge->Forge[AIcounter].idleposecnt = 0;
									Q_Forge->Forge[AIcounter].StepTimer = 0;
									}

								//*** Actor
								Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
								Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);

								Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

								// This does collision detection
								if(Qpo->Collision_RayTest(
											 NULL,//&Q_Forge->Forge[AIcounter].AV.Mins, 
											 NULL,//&Q_Forge->Forge[AIcounter].AV.Maxs, 
											 &Q_Forge->Forge[AIcounter].AV.OldPos, 
											 &Q_Forge->Forge[AIcounter].AV.NewPos, 
											 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
											 // GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS //      ////GE_COLLIDE_ALL, //// GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS 
											 0xffffffff, NULL, NULL, 
											 &Q_Forge->Forge[AIcounter].AV.Collision))
									{
									// Set the new pos to the point of collision
									Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z);
									}
								
								Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
								Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
								
									
								// Set the player to the new pos
								Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
										
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER > Q_Forge->Forge[AIcounter].Q_Brain.MoveTimeLock + 10)
									{
									Q_Forge->Forge[AIcounter].Q_Brain.MoveSide = 0;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
									}
								}
							}


						//##Delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayOn == 1)
							{
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].idlemotion = 23;

							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER > Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayTimeLock)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayOn = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								}
							}


						}

					Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER++;
				}

			//################################################################





			


			//###Attacks \/\/\/\/\/\/\/\/\/\/\/\/\/

			
			//else Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;

			//Initiate High Kick
			/*if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 13;	//21

			Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
			Q_Forge->Forge[AIcounter].astackcntdir[1]++;
			Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
			Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
			Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;*/

			} break;



		case 8:   //Long Range Attack
			{
			LoopON = 0;


			Q_Forge->Forge[AIcounter].Mposestate = 0;
			Q_Forge->Forge[AIcounter].idlemotion = 23;


				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;


			if(Q_Forge->Forge[AIcounter].WeaponStatus != 8 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 31 && Q_Forge->Forge[AIcounter].Aposestate != 32)
				{

				//=****=- Lock On
					//Turn to Face Avatar - Target in View *
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
					{
					Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng / 3;
					if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
					if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

					Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng / 3);
					Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
					
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
					}
				else //Turn to Face Avatar - Target Vanished
					{												//Turn To Previous Enemy Position
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
						{
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
						Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Right);
						Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Right);
						
						TempVec1 = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						TempVec1.y += 65;

						Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID].Pos, &TempVec1, &Q_Forge->Forge[AIcounter].ScanVecTo);
						Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].ScanVecTo);

						Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanTurnVec);
						Q_Forge->Forge[AIcounter].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
						Q_Forge->Forge[AIcounter].ScanTurnAng /= 2;

						ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Left);
						ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Right);
						

						if(ScanDistL < ScanDistR) //Then Avatar is to the Left of the AIs view
							{
							Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;
							}


						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng / 3;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer++;

						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 2000)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CRUNCHDECIDE;
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 100)
								{

								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.25 > -(PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.25;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.25 < (PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.25;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}

								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x < 0.05 && Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x > -0.05)
									Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 73;

								Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 1;
								}
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 1)	//Target Moves From View
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetWENTltr == 1)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.4 > -(PI/1.5) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.4;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.4 <= 0 ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.4;
									else
										{
										if(Q_Forge->Forge[AIcounter].Aposestate != 101)
											{
											Q_Forge->Forge[AIcounter].Aposestate = 101;
											Q_Forge->Forge[AIcounter].attackon = 1;
											Q_Forge->Forge[AIcounter].attposecnt = 0;
											Q_Forge->Forge[AIcounter].astackcnt = 0;
											Q_Forge->Forge[AIcounter].astackrun = 0;
											Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
											}
										}

									}
								}


							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetWENTltr == 2)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.HeadDir == 1)
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x + 0.4 < (PI/2) ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x += 0.4;
									else Q_Forge->Forge[AIcounter].Q_Brain.HeadDir *= -1;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x - 0.4 >= 0 ) Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x -= 0.4;
									else 
										{
										if(Q_Forge->Forge[AIcounter].Aposestate != 101)
											{
											Q_Forge->Forge[AIcounter].Aposestate = 101;
											Q_Forge->Forge[AIcounter].attackon = 1;
											Q_Forge->Forge[AIcounter].attposecnt = 0;
											Q_Forge->Forge[AIcounter].astackcnt = 0;
											Q_Forge->Forge[AIcounter].astackrun = 0;
											Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
											}
										}
									}
								}

							Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 1;
							}

						}
					}


					//## Aim Weapon Up / Down
					if(Q_Forge->Forge[AIcounter].WeaponStatus == 5)
						{
							//Do No Aiming Adjustments ***
							/*Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Weapon, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].TempXForm1);
							Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*//*&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Forge->Forge[AIcounter].AimVec);
							Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AimVec);

							Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
							
							if(Q_Forge->Forge[AIcounter].AimVec.y > Q_Forge->Forge[AIcounter].AV.Up.y-0.03)
								Q_Forge->Forge[AIcounter].WeaponAimer +=  0.02;
							else Q_Forge->Forge[AIcounter].WeaponAimer -=  0.02;*/

						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 || Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND == 1)
							{
							Qpo->Avatar_GetWeaponTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].TempXForm1);
							Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Forge->Forge[AIcounter].AimVec);
							Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AimVec);
							TempVec2 = Q_Forge->Forge[AIcounter].AimVec;
							Tempfloat1 = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].TempXForm1.Translation, &Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID].Pos);
							Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].TempXForm1.Translation, Tempfloat1, &Q_Forge->Forge[AIcounter].AimVec, &Q_Forge->Forge[AIcounter].AimVec);

							Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID].Pos, &Q_Forge->Forge[AIcounter].TempXForm1.Translation,  &TempVec1);
							Qpo->Vec3d_Normalize(&TempVec1);
							Qpo->Vec3d_Normalize(&TempVec2);

							Qpo->Vec3d_Subtract(&TempVec2, &TempVec1, &Q_Forge->Forge[AIcounter].ScanVecToAimer);
							Q_Forge->Forge[AIcounter].ScanTurnAngAimer = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].ScanVecToAimer);
							Q_Forge->Forge[AIcounter].ScanTurnAngAimer /= 500;	//2

							if(TempVec2.y < TempVec1.y)
								Q_Forge->Forge[AIcounter].ScanTurnAngAimer *= -1;

							Q_Forge->Forge[AIcounter].WeaponAimer += Q_Forge->Forge[AIcounter].ScanTurnAngAimer;
							}
						}
					}
				

				//Draw Weapon from backpack
			if(Q_Forge->Forge[AIcounter].WeaponDrawn == 0)
				{
				Q_Forge->Forge[AIcounter].DrawWeapon = 1;
				Q_Forge->Forge[AIcounter].WeaponDrawn = 1;
				}

			//Aim Weapon
			Q_Forge->Forge[AIcounter].WeaponAIM = 1;

			//Avatar Firing
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 500)
					{
					Q_Forge->Forge[AIcounter].WeaponFire = 1;
					Q_Forge->Forge[AIcounter].FireRated = 0;
					Q_Forge->Forge[AIcounter].FireRateTimer = 0;
					}
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 500 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 1000 && Q_Forge->Forge[AIcounter].FireRated <= 3)
					{
					Q_Forge->Forge[AIcounter].WeaponFire = 1;
					Q_Forge->Forge[AIcounter].FireRated++;
					Q_Forge->Forge[AIcounter].FireRateTimer = 0;
					}
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 1000 && Q_Forge->Forge[AIcounter].FireRated < 1)
					{
					Q_Forge->Forge[AIcounter].WeaponFire = 1;
					Q_Forge->Forge[AIcounter].FireRated++;
					Q_Forge->Forge[AIcounter].FireRateTimer = 0;
					}
				}

			Q_Forge->Forge[AIcounter].FireRateTimer++;
			if(Q_Forge->Forge[AIcounter].FireRateTimer == 6) Q_Forge->Forge[AIcounter].FireRated = 0;


			//Holster weapon and change mode if enemy is too near
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 180)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
				Q_Forge->Forge[AIcounter].WeaponHolster = 1;
				Q_Forge->Forge[AIcounter].DrawWeapon = 0;
				Q_Forge->Forge[AIcounter].WeaponDrawn = 0;
				Q_Forge->Forge[AIcounter].WeaponAIM = 0;
				Q_Forge->Forge[AIcounter].WeaponFire = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
				}

			if(Q_Forge->Forge[AIcounter].HitShield > 0)
				{
				Q_Forge->Forge[AIcounter].HitShield = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
				Q_Forge->Forge[AIcounter].WeaponHolster = 1;
				Q_Forge->Forge[AIcounter].DrawWeapon = 0;
				Q_Forge->Forge[AIcounter].WeaponDrawn = 0;
				Q_Forge->Forge[AIcounter].WeaponAIM = 0;
				Q_Forge->Forge[AIcounter].WeaponFire = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
				}

			} break;




		case 20:   //### Cleric Heal Mode
			{
				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;

			//### Check to see if SHIELD required
			//if(Q_Forge->Forge[AIcounter].NomTargetsPresent > 1 || 1)
			if(Q_Forge->Forge[AIcounter].Cleric.ShieldOn == 0 && Q_Forge->Forge[AIcounter].Aposestate != 100)
				{
				Q_Forge->Forge[AIcounter].Aposestate = 201;
				Q_Forge->Forge[AIcounter].attackon = 1;
				Q_Forge->Forge[AIcounter].attposecnt = 0;
				Q_Forge->Forge[AIcounter].astackcnt = 0;
				Q_Forge->Forge[AIcounter].astackrun = 0;
				Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
				}

				//Increment Time
			Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.Ticker++;

				//Periodic Spot Checks
			if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.Ticker > Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.TickerTIME)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.TickerTIME = Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.Ticker + 200;
				Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceSW = 1;
				}

				//Spot Checks
			if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceSW == 1)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceSW = 0;
				Q_Forge->Forge[AIcounter].Aposestate = 101;
				Q_Forge->Forge[AIcounter].attackon = 1;
				Q_Forge->Forge[AIcounter].attposecnt = 0;
				Q_Forge->Forge[AIcounter].astackcnt = 0;
				Q_Forge->Forge[AIcounter].astackrun = 0;
				Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

				Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM = 0;
				}

			if(Q_Forge->Forge[AIcounter].NomFriendlyPresent > 0 && Q_Forge->Forge[AIcounter].Aposestate == 101)	//Store Visible Avatars
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM == 0)
					{
					helly = 0;
					while(helly < Q_Forge->Forge[AIcounter].NomFriendlyPresent)
						{
						Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].AV_ID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AV_ID;
						Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].Distance = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].Distance;
						Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].AIPID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AIPID;
					
						Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM++;
						helly++;
						}
					}
				else	//Some Avatars Already Stored Check for Duplicates
					{
					aero = 0;
					while(aero < Q_Forge->Forge[AIcounter].NomFriendlyPresent)
						{
						helly = 0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM)
							{
							if(Q_Forge->Forge[AIcounter].FriendlyMatrix[helly].AV_ID == Q_Forge->Forge[AIcounter].FriendlyPresent[aero].AV_ID) Q_Forge->Forge[AIcounter].FriendlyPresent[aero].AV_ID = -100;
							helly++;
							}

						aero++;
						}

					helly = 0;
					while(helly < Q_Forge->Forge[AIcounter].NomFriendlyPresent)
						{
						if(Q_Forge->Forge[AIcounter].TargetsPresent[helly].AV_ID != -100)
							{
							Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].AV_ID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AV_ID;
							Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].Distance = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].Distance;
							Q_Forge->Forge[AIcounter].FriendlyMatrix[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM].AIPID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AIPID;
							
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM++;
							}

						helly++;
						}
					}


					//Store Memory ID for Later Checks
				Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceMeM = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
				}




			//#### Avatar Healing
			
				//Check If Any One Person On the Team Needs Healing

			if(Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM < 6)
				{
				//### First Check for player healing
				if(Q_Forge->Forge[AIcounter].Team == player[g_Player]->Team)
					{
					if(Q_Forge->Forge[AIcounter].HB_Energy > Q_Forge->Forge[AIcounter].HB_MaxEnergy / 2)	//Cleric Has More then Half Energy
						{
						if(player[g_Player]->HB_Health < player[g_Player]->HB_MaxHealth && player[g_Player]->HB_Dead == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCue[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM] = 250;
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM++;
							}
						}
						
					if(Q_Forge->Forge[AIcounter].HB_Energy < Q_Forge->Forge[AIcounter].HB_MaxEnergy / 2)	//Cleric Has Less then Half Energy
						{
						if(player[g_Player]->HB_Health < player[g_Player]->HB_MaxHealth / 2 && player[g_Player]->HB_Dead == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCue[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM] = 250;
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM++;
							}
						}
					}


				helly = 0;
				while(helly < _->NomAI)
					{
					if(Q_Forge->Forge[helly].LIVE == 1)
						{
						if(Q_Forge->Forge[helly].Team == Q_Forge->Forge[AIcounter].Team)
							{
							if(Q_Forge->Forge[AIcounter].HB_Energy > Q_Forge->Forge[AIcounter].HB_MaxEnergy / 2)	//Cleric Has More then Half Energy
								{
								if(Q_Forge->Forge[helly].HB_Health < Q_Forge->Forge[helly].HB_MaxHealth && Q_Forge->Forge[helly].HB_Dead == 0)
									{
									Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCue[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM] = Q_Forge->Forge[helly].AV.Avatar.IDflag;
									Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM++;
									}
								}
							
							if(Q_Forge->Forge[AIcounter].HB_Energy < Q_Forge->Forge[AIcounter].HB_MaxEnergy / 2)	//Cleric Has Less then Half Energy
								{
								if(Q_Forge->Forge[helly].HB_Health < Q_Forge->Forge[helly].HB_MaxHealth / 2 && Q_Forge->Forge[helly].HB_Dead == 0)
									{
									Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCue[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM] = Q_Forge->Forge[helly].AV.Avatar.IDflag;
									Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM++;
									}
								}
							}
						}

					helly++;
					}
				}



			//####	Heal Cue
			if(Q_Forge->Forge[AIcounter].attackon == 0)	//If Idle...
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM > 0)		//..and Heal Cue is not empty
					{
					
					aero = 0;											//Check if Avatar is Visible
					while(aero < Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.GlanceNoM)		//TODO Add Priorities
						{	//WARNING EDIT ADDED QUANTATIVE VARIABLE THAT IS NOT NEEDED ##########################################
						if((_->NomHSpark < 200) && (Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCue[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM - 1] == Q_Forge->Forge[AIcounter].FriendlyMatrix[aero].AV_ID))
							{	//## Avatar Requiring Healing is present So HEAL
							Q_Forge->Forge[AIcounter].Aposestate = 200;
							Q_Forge->Forge[AIcounter].attackon = 1;
							Q_Forge->Forge[AIcounter].attposecnt = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealTarget = Q_Forge->Forge[AIcounter].FriendlyMatrix[aero].AV_ID;
							
							Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM--;
							}

						aero++;
						}

					if(Q_Forge->Forge[AIcounter].Aposestate != 200)		//Avatar Not Present So delete from cue
						{										//TODO Add A 'Real World Search' mode
						Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.HealCueNoM--;
						}
					}
				}
			


			}//END Cleric Heal Mode




		}//END Main Mode Switch



		//#####--  Avatar View Scan  --#####//

	if(Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK == 1)
		{

		//### Avatar Scans View
		Q.AIFunctionsScannerCheck(AIcounter);

		Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 0;
		}



		//##### -Effects Control- #####
	/*if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldOn == 1 && 0)
		{
		Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldPos.y += 120;
		Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldCenter = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		if(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshOn == 0)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshOn = 1;
			Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID = _->NomPEFMesh;
			Q.PEF_CREATE_SpherePEFMesh(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldPos, Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldCenter, 110, 2);
			}

		Qpo->Transform_AvatarGetUp(/*ORIG GetIn*//*&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].In);
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*//*&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].Left);
		//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].Left);
		Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].Up);
		if(Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].NoMLines < 30)
			{
			Q.PEF_ADDLINE_RingPEFMesh(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldPos, 3, Q_Forge->Forge[AIcounter].In, Q_Forge->Forge[AIcounter].Left, Q_Forge->Forge[AIcounter].Up, Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID);
			}
		else
			{
			if(Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].BaseVert[0][jet][Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].NoMLines].y < Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldCenter.y)
				{
				helly = Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].NoMLines;
				while(helly > 0)
					{
					jet=0;
					while(jet < Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].MaxNumX)
						{
						//##### Active Base Vert
						Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].BaseVert[0][jet][helly] = Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].BaseVert[0][jet][helly-1];
						//##### Active Cell
						Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].CellVert1[0][jet][helly] = Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].CellVert1[0][jet][helly-1];
						jet++;
						}

					//## Update Movement Variables
					Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].LineMoveIncZ[0][helly] = Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].LineMoveIncZ[0][helly-1];
					Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].ExpandAMT[helly] = Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].ExpandAMT[helly-1];

					helly--;
					}
				
				Q_PinEffectMesh->PinEffectMesh[Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID].NoMLines--;

				Q.PEF_ADDLINE_RingPEFMesh(Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldPos, 3, Q_Forge->Forge[AIcounter].In, Q_Forge->Forge[AIcounter].Left, Q_Forge->Forge[AIcounter].Up, Q_Forge->Forge[AIcounter].Q_Brain.CLSCleric.ShieldMeshID);
				}
			}

		
		//##### Cleric Shield Motion	TODO Set elsewhere
		Qpo->Avatar_SetPosePM(Q_Forge->Forge[AIcounter].AV.Avatar, Q_Forge->Forge[AIcounter].AV.Motion[65], Q_Forge->Forge[AIcounter].shieldposecnt, NULL);

		if(Q_Forge->Forge[AIcounter].shieldposecnt-(0.04*_->TimeScale) <= 0.33) Q_Forge->Forge[AIcounter].shieldposecnt -= 0.04*_->TimeScale;
		else Q_Forge->Forge[AIcounter].shieldposecnt = 0;
		}*/






		//#####-- Location Control For Class 'Cleric' --#####

Q_Forge->Forge[AIcounter].Role = 0;

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

		Q_Forge->Forge[AIcounter].Q_Brain.LocationState = 0;

		switch(Q_Forge->Forge[AIcounter].Q_Brain.LocationState)
			{

			case 0:	//## Initialisation Mode Avatar Just Spawned or reset
				{

					//### Leader Is Present
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1) Q_Forge->Forge[AIcounter].Q_Brain.LocationState = 0;	//EDIT //1

				} break;


			case 1:
				{
					//### Not Locked Onto Enemy Then Lock On the Leader
				if((Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1) || (Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 72) || Q_Forge->Forge[AIcounter].Q_Brain.MindState == MIND_CLERIC_HEAL)
					{
					Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
					Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3;
					if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
					if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

					Qpo->Transform_New_ZRotation(&AIfriendly, Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 3);
					Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
					
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 80)
						{

						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist < 160)
							{
							//### Walk Towards Player
							Q_Forge->Forge[AIcounter].ForwardSpeed = 2*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
							
							if(Q_Forge->Forge[AIcounter].Mposestate != 1 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
								{
								Q_Forge->Forge[AIcounter].Mposestate = 1;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].idleposecnt = 0;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								}
							}
						else
							{
							//### Run Towards Player
							Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
							
							if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
								{
								Q_Forge->Forge[AIcounter].Mposestate = 3;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].idleposecnt = 0;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								}
							}

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
							{ Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z); }

						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
											
						// Set the player to the new pos
						Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
						}
					else
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
				else
					{
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanDist > 100 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1)
						{
						//### Run Towards Player
						Q_Forge->Forge[AIcounter].ForwardSpeed = 8*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
						
						if(Q_Forge->Forge[AIcounter].Mposestate != 3 && Q_Forge->Forge[AIcounter].Mposestate != 7)	//Movement mode switch
							{
							Q_Forge->Forge[AIcounter].Mposestate = 3;
							Q_Forge->Forge[AIcounter].StepTimer = 0;
							Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
							Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
							Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
							Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
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
						if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
							{ Q_Forge->Forge[AIcounter].AV.NewPos.acSet(Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_X, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Y, Q_Forge->Forge[AIcounter].AV.Collision.Impact.m_Z); }

						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
											
						// Set the player to the new pos
						Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
						}
					else
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

	}//END CLERIC BRAIN
};