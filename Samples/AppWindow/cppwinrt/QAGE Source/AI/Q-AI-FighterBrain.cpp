/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	*/#include "pch.h"/*- Minor Component -Fighter Brain-

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

	//#####-- AIBrain for 'FIGHTER' Class --#####

bool Q_COREFunctions::AIFighterBrain(int AIcounter)
	{
	//Failsafe return
	if (Q_Forge->Forge[AIcounter].AV.Xform.Translation.x == Q_Forge->Forge[AIcounter].StrPos.x &&
	    Q_Forge->Forge[AIcounter].AV.Xform.Translation.y == Q_Forge->Forge[AIcounter].StrPos.y &&
	    Q_Forge->Forge[AIcounter].AV.Xform.Translation.z == Q_Forge->Forge[AIcounter].StrPos.z)
		{
		Q_Forge->Forge[AIcounter].StrPosCounter++;
		}
	else
		{
		Q_Forge->Forge[AIcounter].StrPosCounter = 0;
		}

	Q_Forge->Forge[AIcounter].StrPos.x = Q_Forge->Forge[AIcounter].AV.Xform.Translation.x;
	Q_Forge->Forge[AIcounter].StrPos.y = Q_Forge->Forge[AIcounter].AV.Xform.Translation.y;
	Q_Forge->Forge[AIcounter].StrPos.z = Q_Forge->Forge[AIcounter].AV.Xform.Translation.z;

	//If idle for 5 cycles.... Reset!
	/*if(Q_Forge->Forge[AIcounter].StrPosCounter > 65 && Q_Forge->Forge[AIcounter].HB_Dead == 0)
		{
		Q_Forge->Forge[AIcounter].Q_Brain.MindState = 1;
		Q_Forge->Forge[AIcounter].Mposestate = 0;

		Q_Forge->Forge[AIcounter].StrPosCounter = 0;
		}*/

	Q_Forge->Forge[AIcounter].Blocking = 1;

	switch(Q_Forge->Forge[AIcounter].Q_Brain.MindState)
		{
		case 0:   //IdleMode
			{
			LoopON = 0;

			Q_Forge->Forge[AIcounter].Mposestate = 0;
			} break;

		case 9:   //LookMode
			{
			LoopON = 0;

			//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;

			Q_Forge->Forge[AIcounter].Mposestate = 0;

			if(Q_Forge->Forge[AIcounter].Aposestate != 100 && Q_Forge->Forge[AIcounter].AirBorn == 0)
				{
				Q_Forge->Forge[AIcounter].Aposestate = 100;
				Q_Forge->Forge[AIcounter].attackon = 1;
				Q_Forge->Forge[AIcounter].attposecnt = 0;
				Q_Forge->Forge[AIcounter].astackcnt = 0;
				Q_Forge->Forge[AIcounter].astackrun = 0;
				Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
				}

			//=*=- Lock On
			//Turn to Face Avatar
			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

#if 0
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CRUNCHDECIDE;
				}
			else
				{
				if(Q_Forge->Forge[AIcounter].attposecnt == 0 && Q_Forge->Forge[AIcounter].blendamount[140] == 0.15)
					{
					Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVEINIT;
					}
				}
#else

			Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVEINIT;
#endif
			} break;

		case 1:   //ActiveModeInit		//Functionise these 'Modes'
			{
			LoopON = 0;

			Q_Forge->Forge[AIcounter].idlemotion=0;

			if(Q_Forge->Forge[AIcounter].Mposestate == 0 && Q_Forge->Forge[AIcounter].blendamount[8] == 1)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
				Q_Forge->Forge[AIcounter].Mposestate = 0;
				Q_Forge->Forge[AIcounter].blendamount[8] = 0;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0;
				Q_Forge->Forge[AIcounter].AttackIdle = 2000;
				Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;	//(float)rand() / 32767) - 0.5);
				}

			Q_Forge->Forge[AIcounter].Blocking = 1;
			Q_Forge->Forge[AIcounter].BlockHeight = 3;

			Q_Forge->Forge[AIcounter].Q_Brain.TargetLightLOCK = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLightLOST = 1;

			Q_Forge->Forge[AIcounter].Mposestate = 50;
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
			// Turn to Face Avatar
			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_CRUNCHDECIDE;
				}
			else
				{
				Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
				}

			 ///////////////////////////////////////////
			  // If Target Sighted Log in Memory Bank
			  // 
			  // Continue Movement
			 // Run Towards Avatar

			Q_Forge->Forge[AIcounter].ForwardSpeed = 10 * _->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].StepTimer = 0;
				}

			Q_Forge->Forge[AIcounter].Running = 1;

			//*** Actor
			Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;

			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL, 
						 NULL, 
						 &Q_Forge->Forge[AIcounter].AV.OldPos, 
						 &Q_Forge->Forge[AIcounter].AV.NewPos, 
						 //GE_CONTENTS_CANNOT_OCCUPY                   //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS,
						 0xffffffff, NULL, NULL, 
						 &Q_Forge->Forge[AIcounter].AV.Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].collide = 1;
				}

			Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
		
			// Win conditiuons! Set the player to the new pos
			if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
			else
				{
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;

				Q_Forge->Forge[AIcounter].Running = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.MoveSide = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.MoveTimeLock = Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER;
				Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger = rand() % 10;
				if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger <= 5) Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = -1;
				if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger > 5)  Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = 1;

				//Attack position achieved
				Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
							
				Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed / 2.0f) * _->TimeScale;

				if(Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect < 0)
					{
					if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6) || (Q_Forge->Forge[AIcounter].Mposestate != 5)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
						{
						Q_Forge->Forge[AIcounter].Mposestate = 5;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}

					//*** Actor
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					}
				else
					{
					if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6) || (Q_Forge->Forge[AIcounter].Mposestate != 5)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
						{
						Q_Forge->Forge[AIcounter].Mposestate = 6;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}

					//*** Actor
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					}

				Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

				Q_Forge->Forge[AIcounter].collide = 0;

				// This does collision detection
				if(Qpo->Collision_RayTest(
								NULL,
								NULL,
								&Q_Forge->Forge[AIcounter].AV.OldPos,
								&Q_Forge->Forge[AIcounter].AV.NewPos,
								// GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
								//GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
								0xffffffff, NULL, NULL,
								&Q_Forge->Forge[AIcounter].AV.Collision))
					{
					// Set the new pos to the point of collision
					//Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;
					Q_Forge->Forge[AIcounter].collide = 1;
					}

				Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
							
				// Set the player to the new pos
				if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
				}

			//Loop\|/\|/\|/\|/\|/\|/
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

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

				//Run Towards Avatar

			Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].StepTimer = 0;
				}

			Q_Forge->Forge[AIcounter].Running = 1;

			//*** Actor
			Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL, 
						 NULL, 
						 &Q_Forge->Forge[AIcounter].AV.OldPos, 
						 &Q_Forge->Forge[AIcounter].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS,
						 0xffffffff, NULL, NULL, 
						 &Q_Forge->Forge[AIcounter].AV.Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].collide = 1;
				}

			Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
		
			// Set the player to the new pos
			if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;
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

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);

				//Run Towards Avatar

			Q_Forge->Forge[AIcounter].ForwardSpeed = 5*_->TimeScale;//Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].StepTimer = 0;
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
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
						 NULL, 
						 NULL, 
						 &Q_Forge->Forge[AIcounter].AV.OldPos, 
						 &Q_Forge->Forge[AIcounter].AV.NewPos, 
						 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
						 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
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

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng);
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
			if(Q_Forge->Forge[AIcounter].ScanAvatarDist >= 170) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR = 500;
			//else Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_LongR = 0;

			//Hand To Hand
			if(Q_Forge->Forge[AIcounter].ScanAvatarDist < 170) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H = 500;
			else Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Hand2H = 200;

			//Delay decision
			if(Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Timer < 500) Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.F_Delay = 100 - Q_Forge->Forge[AIcounter].Q_Brain.CRDecide.Timer;

			
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
					if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
						Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
						}
					} break;

				case 1:	//Hand To Hand
					{
					Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
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
			// Turn to Face Avatar Conditional (Not in Hit Reaction)
			if(Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
				{

				//####### -  Mode Universal Avatar Control - Update if required for mode specific Control -#####

				//##### Turn to Face Avatar - Target in View
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
					{
					if(Q_Forge->Forge[AIcounter].Aposestate != 13)
						{
						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng/1.5;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng/1.5);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}
					else
						{
						Q_Forge->Forge[AIcounter].Angles.y += (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}

					//##### Drop target if dead
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID].Health <= 0)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
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
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
						Q_Forge->Forge[AIcounter].Mposestate = 0;
						Q_Forge->Forge[AIcounter].blendamount[8] = 0;
						Q_Forge->Forge[AIcounter].blendamount[0] = 0;
						Q_Forge->Forge[AIcounter].AttackIdle = 2000;
						Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;
						Q_Forge->Forge[AIcounter].Aposestate = 0;
						Q_Forge->Forge[AIcounter].attackon = 0;

						if(Q_Forge->Forge[AIcounter].Aposestate != 100 && Q_Forge->Forge[AIcounter].AirBorn == 0)
							{
							Q_Forge->Forge[AIcounter].Aposestate = 100;
							Q_Forge->Forge[AIcounter].attackon = 1;
							Q_Forge->Forge[AIcounter].attposecnt = 0;
							Q_Forge->Forge[AIcounter].astackcnt = 0;
							Q_Forge->Forge[AIcounter].astackrun = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
							}
						}

					//### Activate Timed Search
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 20)
						{ Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED = 1; }

					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
					}
				else //##### Turn to Face Avatar - Target Vanished
					{
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
						{

						//##### - PERFECT TEN TIMED TARGET LOCK SYSTEM - #####

						if(Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer < 10)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV[g_Player]->Xform.Translation;
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							else
								{
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos = Q_Forge->Forge[Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}

#pragma("FIXME:::Weapon Excludes")
#if 0
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 300)
								{	//# Switch to Long Range Attack
								Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
								if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
									{
									Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
									Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
									Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
									}
								//### Set Note to return when enemy Lands
								Q_Forge->Forge[AIcounter].Q_Brain.MODERETURN_H2H = 1;
								}
#endif
							}

						Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer++;


						//#### Turn To PERFECT Enemy Position
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
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

						if(ScanDistL < ScanDistR) Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;

						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng / 3;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);


						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer++;
						Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer++;


							//### Timed Search End
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 150 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED == 1)
							{ Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED = 0; }

							//### Conditional Target Lost
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 50)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
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
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].blendamount[8] = 0;
							Q_Forge->Forge[AIcounter].blendamount[0] = 0;
							Q_Forge->Forge[AIcounter].AttackIdle = 2000;
							Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;
							Q_Forge->Forge[AIcounter].Aposestate = 0;
							Q_Forge->Forge[AIcounter].attackon = 0;
							break;
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED == 0)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer > 50)
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
										Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 50;

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
											if(Q_Forge->Forge[AIcounter].Aposestate != 100 && Q_Forge->Forge[AIcounter].AirBorn == 0)
												{
												Q_Forge->Forge[AIcounter].Aposestate = 100;
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
											if(Q_Forge->Forge[AIcounter].Aposestate != 100)
												{
												Q_Forge->Forge[AIcounter].Aposestate = 100;
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
								}//END Target Lost 1

							}//END Target Spotted

						}//END TargetLOCK

					}//END Else - TargetLOCK

				}//END Conditional - Hit Reaction


			//####### -  intelligence Cycle
			//#### TODO Conditionally Activate  Attack Plans
			//##### Focus Power Control Possible Time Bending

			Q_Forge->Forge[AIcounter].Q_Brain.Focus += 0.1;

			Q_Forge->Forge[AIcounter].Q_Brain.Aggression += 0.1;

			
			//##### Testing Mind Modes
			if(Q_Forge->Forge[AIcounter].Q_Brain.TestKEY1 == 1) Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 100;
			else Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 0;

			if(Q_Forge->Forge[AIcounter].Q_Brain.TestKEY2 == 1) Q_Forge->Forge[AIcounter].Q_Brain.Focus = 100;
			else Q_Forge->Forge[AIcounter].Q_Brain.Focus = 0;

			if(Q_Forge->Forge[AIcounter].Q_Brain.TestKEY3 == 1) Q_Forge->Forge[AIcounter].Q_Brain.FocusON = 1;
			else Q_Forge->Forge[AIcounter].Q_Brain.FocusON = 0;


			//TEMPORARY AGGRESSION ZAP
			//Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 0;


			//### Stabilise Aggression
			if(Q_Forge->Forge[AIcounter].Q_Brain.Aggression > 100) Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 100;
			if(Q_Forge->Forge[AIcounter].Q_Brain.Aggression < 0) Q_Forge->Forge[AIcounter].Q_Brain.Aggression = 0;

			//### Stabilise Focus
			if(Q_Forge->Forge[AIcounter].Q_Brain.Focus > 100 || 1) Q_Forge->Forge[AIcounter].Q_Brain.Focus = 100;
			if(Q_Forge->Forge[AIcounter].Q_Brain.Focus < 0) Q_Forge->Forge[AIcounter].Q_Brain.Focus = 0;

			Q_Forge->Forge[AIcounter].Q_Brain.Focus = 100;
			Q_Forge->Forge[AIcounter].Q_Brain.FocusON = 1;

			if(Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1) Q_Forge->Forge[AIcounter].Q_Brain.Focus -= 0.25;


			//### Simple Distance Check -- With Mode Switch and Full Reset

			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 120)
					{
					if(Q_Forge->Forge[AIcounter].Q_Brain.Aggression > 50)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MindMODE = MMODE_CLOSE_AGGRESSION;
						}
					else
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MindMODE = MMODE_CLOSE_DEFENSE;
						}
					}

				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120)
					{
					if(Q_Forge->Forge[AIcounter].Q_Brain.Aggression > 50)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MindMODE = MMODE_MID_AGGRESSION;
						}
					else
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MindMODE = MMODE_MID_DEFENSE;
						}
					}
				}


			//####### -  Mind Mode Switch

			switch(Q_Forge->Forge[AIcounter].Q_Brain.MindMODE)
				{

				case 0:	   //#=- Attack Plan Control
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;
						Q_Forge->Forge[AIcounter].astackcnt = 0;
						Q_Forge->Forge[AIcounter].astackrun = 0;
						Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

						if(Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
							}
						}


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
						{
						//###Run Towards Avatar

						Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
						if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
						Q_Forge->Forge[AIcounter].Mposestate = 3;
						Q_Forge->Forge[AIcounter].Running = 1;

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 //GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							//Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;
							Q_Forge->Forge[AIcounter].collide = 1;
							}
						
						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
						
							
						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

						//Attack position not achieved yet
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Q_Forge->Forge[AIcounter].astackcnt = 0;
						//Q_Forge->Forge[AIcounter].astackrun = 0;
						//Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Q_Forge->Forge[AIcounter].attackon == 0*/ && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Q_Forge->Forge[AIcounter].astackrun > 0)
								{
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Q_Forge->Forge[AIcounter].BlockInit == 0)
							{
							Q_Forge->Forge[AIcounter].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 8)))
								{
								Q_Forge->Forge[AIcounter].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Q_Forge->Forge[AIcounter].BlockHeightMeM != Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 7)))
										{
										Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
										}
									}
								else
									{
									Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Q_Forge->Forge[AIcounter].Blocking = 0;
						Q_Forge->Forge[AIcounter].BlockInit = 0;

						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 20;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 21;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 22;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 23;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Q_Forge->Forge[AIcounter].attackon == 1 && ( TIME >= Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT + 200 ) )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT + 100 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT + 30 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Q_Forge->Forge[AIcounter].LEVEL > 0 ) && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 ) && ( Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 ) )
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 6) + 8))	//4 + 2
								{
								Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 2 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 6 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 10) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 10 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 15) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 15 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 20) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 20 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 25) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 25 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 30) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 30 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 35) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 35 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 40) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 40 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 45) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 45 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 60) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 60 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 65) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 65 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 70) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 70 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 75) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 75 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 80) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 80 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 85 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 90 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 100) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 1;
							}
						}

#pragma message("FIXME:::COLDET::: Pack Crash Avoidance")
#if 0
					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 304;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;

					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, -120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 303;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;

					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 15, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 309;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].collide == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 3) + 11))
								{
								Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = Q_Forge->Forge[AIcounter].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
							}
						else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
						}

					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].astackrun > 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 5) + 2))	//7.5
								{
								Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP == 0)
						{
						if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && (Q_Forge->Forge[AIcounter].Aposestate != 30) && (Q_Forge->Forge[AIcounter].Aposestate != 51) && (Q_Forge->Forge[AIcounter].Aposestate != 52) && ((Q_Forge->Forge[AIcounter].attackon == 0) || ((Q_Forge->Forge[AIcounter].attackon == 1) && (Q_Forge->Forge[AIcounter].Aposestate == 26) || (Q_Forge->Forge[AIcounter].Aposestate == 28))))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7) + 3))
								{
								if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
									{
									Q_Forge->Forge[AIcounter].DeflectPower = 0;

									if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28)
										{
										Q_Forge->Forge[AIcounter].Deft_InReact = 1;
										Q_Forge->Forge[AIcounter].Deft_PoseState = Q_Forge->Forge[AIcounter].Aposestate;
										Q_Forge->Forge[AIcounter].Deft_attposecnt = Q_Forge->Forge[AIcounter].attposecnt;
										Q_Forge->Forge[AIcounter].Deft_HitReactScale = Q_Forge->Forge[AIcounter].HitReactScale;
										}
									}
								else Q_Forge->Forge[AIcounter].DeflectPower = 1;

								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 63;

								Q_Forge->Forge[AIcounter].attposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;
								Q_Forge->Forge[AIcounter].blendamount[98] = 0;
								Q_Forge->Forge[AIcounter].TrailsOn = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(/*Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 || */(rand() % 50) > 48)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 95))	// + 65
							{
							if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Q_Forge->Forge[AIcounter].AV.Xform.Translation.y) > 50 || 1)
								{
								if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 11;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Q_Forge->Forge[AIcounter].Mposestate == 11)
										{
										Q_Forge->Forge[AIcounter].JumpDir = 0;

										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
										//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

										if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

										Q_Forge->Forge[AIcounter].jumpposecnt = 0;
										Q_Forge->Forge[AIcounter].Mposestate = 12;
										Q_Forge->Forge[AIcounter].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Running == 1 && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7.5) + 2))
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 1;
							}
						}

#pragma("FIXME:::Weapon Excludes")
#if 0
					//### Check for enemy using weapon
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
#endif


					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
						{
						Q_Forge->Forge[AIcounter].Block = 0;
						Q_Forge->Forge[AIcounter].Blocking = 0;
						}

					//####-  JSRUSH Movetoencount
					if(Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && ((Q_Forge->Forge[AIcounter].HB_Energy / Q_Forge->Forge[AIcounter].HB_MaxEnergy) * 0.6))
						{
						if(Q_Forge->Forge[AIcounter].HB_Energy > 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
							{
							if(Q_Forge->Forge[AIcounter].astackcnt < 5)
								{
								Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 73;
								Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
								}
							Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[1]++;
							Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
							Q_Forge->Forge[AIcounter].astackcnt++;
							}
						}

					//##### Factor thru a response
					if(Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 8;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 22;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 9;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 6000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
						else
							{	//Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 30000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 2000;

						// - Single RLPunch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 4000;

						// - Single RMKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 2000;

						// - Low Punch Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 2500;

						// - Low Punch Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 2500;

						// - Single Renzou
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[0] = 1200;

						// - Attack Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[1] = 1000;

						// - Attack Combo 3
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[2] = 1000;

						// - Attack Combo 4
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[3] = 1500;

						// - Attack Combo 5
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[4] = 1000;

						// - Attack Combo 6	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[5] = 1500;

						// - Attack Combo 7	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[6] = 5000;

						// - Attack Combo 8 NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[7] = 3000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 1000;

						// - Special -  2  -  Flame Uppercut
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 800;

						// - Special -  3  -  VHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 1000;

						// - Special -  4  -  Leap Spin Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 1500;

						// - Special -  5  -  Rush Elbow
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 1000;

						// - Special -  6  -  Sky Push
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 2000;

						// - Special -  7  -  Twist Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 1000;

						// - Special -  9  -  Hadouken
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 1000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 20000;

						// - Special -  12  -  RUSHPUNCH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 15000;

						// - Special -  13  -  RUSHKICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 10000;

						// - Special -  14  -  Static Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 15000;

						// - Special -  15  -  JSRUSH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 10000;

						// - Special -  16  -  Power Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 9000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 4000;

						// - Special -  18  -  HYPER KNEE FLEX
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 4000;

						// - Special -  19  -  AIR DASH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 4000;

						// - Special -  20  -  SAKURA TRIBUTE
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 7000;

						// - Special -  21  -  SPIN KICK FULL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 4000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 3000;

						// - Move -  3  -  JUMP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 800;

						// - Move -  4  -  Roll Low Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 500;

						// - Move -  5  -  Roll Low Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 500;

						// - Move -  6  -  CartWheel Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 700;

						// - Move -  7  -  CartWheel Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 700;

						// - Move -  8  -  Forward Roll
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 200;

						// - Move -  9  -  Dodge Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 600;

						// - Move -  10  -  BackFlip
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 700;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
														Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;

				case 1:	   //#=- Close Range Aggressive
					{
							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;
						Q_Forge->Forge[AIcounter].astackcnt = 0;
						Q_Forge->Forge[AIcounter].astackrun = 0;
						Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
						}


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
						{
						//###Run Towards Avatar

						Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
						if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
						Q_Forge->Forge[AIcounter].Mposestate = 3;
						Q_Forge->Forge[AIcounter].Running = 1;

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

#if 1
						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							Q_Forge->Forge[AIcounter].collide = 1;
							}
						
						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
#endif

						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

						//Attack position not achieved yet
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Q_Forge->Forge[AIcounter].astackcnt = 0;
						//Q_Forge->Forge[AIcounter].astackrun = 0;
						//Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
						}


					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Q_Forge->Forge[AIcounter].attackon == 0*/ && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Q_Forge->Forge[AIcounter].astackrun > 0)
								{
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Q_Forge->Forge[AIcounter].BlockInit == 0)
							{
							Q_Forge->Forge[AIcounter].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < (((float)Q_Forge->Forge[AIcounter].LEVELFactor) + 9)) || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
								{
								Q_Forge->Forge[AIcounter].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Q_Forge->Forge[AIcounter].BlockHeightMeM != Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((2 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 8)) || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
										{
										Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
										}
									}
								else
									{
									Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
									}
								}
							}

						//### Counter Attack only after long attacks
						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 5) < (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2.5) + 1 || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (3.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2))  || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Q_Forge->Forge[AIcounter].Blocking = 0;
						Q_Forge->Forge[AIcounter].BlockInit = 0;

						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (1 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1))  || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (1 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1))  || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 104;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Q_Forge->Forge[AIcounter].attackon == 1 && ( TIME >= Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT + 25 ) )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT + 100 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT + 70 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 ) /*&& ( Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 )*/ )
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2) + 12))	//4 + 2
								{
								Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 2 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 6 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 10) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 10 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 15) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 15 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 20) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 20 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 25) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 25 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 30) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 30 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 35) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 35 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 40) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 40 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 45) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 45 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 60) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 60 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 65) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 65 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 70) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 70 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 75) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 75 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 80) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 80 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 85 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 90 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 100) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 304;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, -120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 303;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 15, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 309;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					/*if(Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].collide == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 3) + 11))
								{
								Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = Q_Forge->Forge[AIcounter].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
							}
						else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
						}*/


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].astackrun > 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 5) + 2)  || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))	//7.5
								{
								Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 0;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP == 0)
						{
						if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Q_Forge->Forge[AIcounter].Aposestate == 30) && !(Q_Forge->Forge[AIcounter].Aposestate == 51) && !(Q_Forge->Forge[AIcounter].Aposestate == 52))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2) + 3) || (Q_Forge->Forge[AIcounter].Q_Brain.FocusON == 1))
								{
								if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
									{
									Q_Forge->Forge[AIcounter].DeflectPower = 0;

									if(Q_Forge->Forge[AIcounter].Aposestate == 26)
										{
										Q_Forge->Forge[AIcounter].Deft_InReact = 1;
										Q_Forge->Forge[AIcounter].Deft_PoseState = Q_Forge->Forge[AIcounter].Aposestate;
										Q_Forge->Forge[AIcounter].Deft_attposecnt = Q_Forge->Forge[AIcounter].attposecnt;
										Q_Forge->Forge[AIcounter].Deft_HitReactScale = Q_Forge->Forge[AIcounter].HitReactScale;
										}
									}
								else Q_Forge->Forge[AIcounter].DeflectPower = 1;

								Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 1;

								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 63;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 0;

								Q_Forge->Forge[AIcounter].attposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;
								Q_Forge->Forge[AIcounter].blendamount[98] = 0;
								Q_Forge->Forge[AIcounter].TrailsOn = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 1;
							}
						}


					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Q_Forge->Forge[AIcounter].AV.Xform.Translation.y) > 50)
								{
								if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 11;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Q_Forge->Forge[AIcounter].Mposestate == 11)
										{
										Q_Forge->Forge[AIcounter].JumpDir = 0;

										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
										//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

										if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

										Q_Forge->Forge[AIcounter].jumpposecnt = 0;
										Q_Forge->Forge[AIcounter].Mposestate = 12;
										Q_Forge->Forge[AIcounter].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Running == 1 && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7.5) + 2))
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 1;
							}
						}


#pragma("FIXME:::Weapon Excludes")
#if 0
					//### Check for enemy using weapon
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
#endif

					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
						{
						Q_Forge->Forge[AIcounter].Block = 0;
						Q_Forge->Forge[AIcounter].Blocking = 0;
						}


					//##### Factor thru a response
					if(Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 8;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 22;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 10000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
						else
							{	//Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 500000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 6000;

						// - Single RLPunch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 6500;

						// - Single RMKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 5500;

						// - Low Punch Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 7500;

						// - Low Punch Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 6500;

						// - Single Renzou
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[0] = 8200;

						// - Attack Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[1] = 8000;

						// - Attack Combo 3
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[2] = 8000;

						// - Attack Combo 4
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[3] = 6500;

						// - Attack Combo 5
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[4] = 7000;

						// - Attack Combo 6	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[5] = 8000;

						// - Attack Combo 7	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[6] = 10000;

						// - Attack Combo 8 NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[7] = 8000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 2000;

						// - Special -  2  -  Flame Uppercut
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 2400;

						// - Special -  3  -  VHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 2500;

						// - Special -  4  -  Leap Spin Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 3500;

						// - Special -  5  -  Rush Elbow
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 2500;

						// - Special -  6  -  Sky Push
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 5000;

						// - Special -  7  -  Twist Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 1000;

						// - Special -  9  -  Hadouken
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 1000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 4000;

						// - Special -  12  -  RUSHPUNCH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 3000;

						// - Special -  13  -  RUSHKICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 2000;

						// - Special -  14  -  Static Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 7000;

						// - Special -  15  -  JSRUSH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 3000;

						// - Special -  16  -  Power Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 9000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 4000;

						// - Special -  18  -  HYPER KNEE FLEX
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 4000;

						// - Special -  19  -  AIR DASH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 4000;

						// - Special -  20  -  SAKURA TRIBUTE
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 7000;

						// - Special -  21  -  SPIN KICK FULL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 4000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 3000;

						// - Move -  3  -  JUMP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 18000;

						// - Move -  4  -  Roll Low Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 2500;

						// - Move -  5  -  Roll Low Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 2500;

						// - Move -  6  -  CartWheel Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 3700;

						// - Move -  7  -  CartWheel Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 3700;

						// - Move -  8  -  Forward Roll
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 2200;

						// - Move -  9  -  Dodge Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 7600;

						// - Move -  10  -  BackFlip
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 5000;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
														Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
						}//END Condition - Move Encount

					} break;


				case 2:	   //#=- Close Range - Defensive
					{
							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;
						Q_Forge->Forge[AIcounter].astackcnt = 0;
						Q_Forge->Forge[AIcounter].astackrun = 0;
						Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

						if(Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
							}
						}


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
						{
						//###Run Towards Avatar

						Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
						if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
						Q_Forge->Forge[AIcounter].Mposestate = 3;
						Q_Forge->Forge[AIcounter].Running = 1;

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							Q_Forge->Forge[AIcounter].collide = 1;
							}
						
						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
							
						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

						//Attack position not achieved yet
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Q_Forge->Forge[AIcounter].astackcnt = 0;
						//Q_Forge->Forge[AIcounter].astackrun = 0;
						//Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Q_Forge->Forge[AIcounter].attackon == 0*/ && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
						/*if(Q_Forge->Forge[AIcounter].astackrun > 0)
							{
							Q_Forge->Forge[AIcounter].astackcnt = 0;
							Q_Forge->Forge[AIcounter].astackrun = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
							}*/

						if(Q_Forge->Forge[AIcounter].BlockInit == 0)
							{
							Q_Forge->Forge[AIcounter].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if( (((float)rand() / 32767) * 10) < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor)) + 9) )
								{
								Q_Forge->Forge[AIcounter].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Q_Forge->Forge[AIcounter].BlockHeightMeM != Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < (((float)Q_Forge->Forge[AIcounter].LEVELFactor) + 9)))
										{
										Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
										}
									}
								else
									{
									Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 8) < 4 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (3 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Q_Forge->Forge[AIcounter].Blocking = 0;
						Q_Forge->Forge[AIcounter].BlockInit = 0;

						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 8) < (3 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 10) < (2 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Q_Forge->Forge[AIcounter].attackon == 1 && ( TIME >= Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT + 50 ) )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT + 100 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT + 100 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 ) && ( Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 ) )
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 2) + 12))	//4 + 2
								{
								Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 2 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 6 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 10) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 10 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 15) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 15 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 20) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 20 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 25) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 25 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 30) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 30 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 35) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 35 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 40) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 40 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 45) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 45 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 60) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 60 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 65) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 65 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 70) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 70 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 75) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 75 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 80) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 80 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 85 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 90 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 100) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 304;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, -120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 303;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 15, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 309;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					/*if(Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].collide == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 3) + 11))
								{
								Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = Q_Forge->Forge[AIcounter].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
							}
						else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
						}*/


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].astackrun > 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 5) + 10))	//7.5
								{
								Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP == 0)
						{
						if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Q_Forge->Forge[AIcounter].Aposestate == 30) && !(Q_Forge->Forge[AIcounter].Aposestate == 51) && !(Q_Forge->Forge[AIcounter].Aposestate == 52))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 3.5) + 1))
								{
								if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
									{
									Q_Forge->Forge[AIcounter].DeflectPower = 0;

									if(Q_Forge->Forge[AIcounter].Aposestate == 26)
										{
										Q_Forge->Forge[AIcounter].Deft_InReact = 1;
										Q_Forge->Forge[AIcounter].Deft_PoseState = Q_Forge->Forge[AIcounter].Aposestate;
										Q_Forge->Forge[AIcounter].Deft_attposecnt = Q_Forge->Forge[AIcounter].attposecnt;
										Q_Forge->Forge[AIcounter].Deft_HitReactScale = Q_Forge->Forge[AIcounter].HitReactScale;
										}
									}
								else Q_Forge->Forge[AIcounter].DeflectPower = 1;

								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 63;

								Q_Forge->Forge[AIcounter].attposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;
								Q_Forge->Forge[AIcounter].blendamount[98] = 0;
								Q_Forge->Forge[AIcounter].TrailsOn = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Q_Forge->Forge[AIcounter].AV.Xform.Translation.y) > 50)
								{
								if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 11;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Q_Forge->Forge[AIcounter].Mposestate == 11)
										{
										Q_Forge->Forge[AIcounter].JumpDir = 0;

										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
										//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

										if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

										Q_Forge->Forge[AIcounter].jumpposecnt = 0;
										Q_Forge->Forge[AIcounter].Mposestate = 12;
										Q_Forge->Forge[AIcounter].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Running == 1 && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7.5) + 2))
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 1;
							}
						}

#pragma("FIXME:::Weapon Excludes")
#if 0
					//### Check for enemy using weapon
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
#endif

					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
						{
						Q_Forge->Forge[AIcounter].Block = 0;
						Q_Forge->Forge[AIcounter].Blocking = 0;
						}


					//##### Factor thru a response
					if(Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 8;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 22;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 25000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
						else
							{	//Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 30000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;



						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 3000;

						// - Single RLPunch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 2300;

						// - Single RMKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 3300;

						// - Low Punch Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 1400;

						// - Low Punch Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 1400;

						// - Single Renzou
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[0] = 80;

						// - Attack Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[1] = 80;

						// - Attack Combo 3
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[2] = 80;

						// - Attack Combo 4
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[3] = 80;

						// - Attack Combo 5
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[4] = 80;

						// - Attack Combo 6	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[5] = 80;

						// - Attack Combo 7	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[6] = 80;

						// - Attack Combo 8 NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[7] = 80;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 50;

						// - Special -  2  -  Flame Uppercut
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 50;

						// - Special -  3  -  VHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 50;

						// - Special -  4  -  Leap Spin Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 800;

						// - Special -  5  -  Rush Elbow
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 100;

						// - Special -  6  -  Sky Push
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 200;

						// - Special -  7  -  Twist Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 300;

						// - Special -  8  -  Hover Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 50;

						// - Special -  9  -  Hadouken
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 0;

						// - Special -  10  -   JSRUSHUP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 300;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 200;

						// - Special -  12  -  RUSHPUNCH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 150;

						// - Special -  13  -  RUSHKICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 100;

						// - Special -  14  -  Static Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 500;

						// - Special -  15  -  JSRUSH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 700;

						// - Special -  16  -  Power Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 400;

						// - Special -  17  -  JS FLAME UPPERCUT
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 400;

						// - Special -  18  -  HYPER KNEE FLEX
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 400;

						// - Special -  19  -  AIR DASH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 400;

						// - Special -  20  -  SAKURA TRIBUTE
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 400;

						// - Special -  21  -  SPIN KICK FULL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 400;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 0;

						// - Move -  2  -  SideStep
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 2000;

						// - Move -  3  -  JUMP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 1500;

						// - Move -  4  -  Roll Low Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 1800;

						// - Move -  5  -  Roll Low Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 1800;

						// - Move -  6  -  CartWheel Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 1500;

						// - Move -  7  -  CartWheel Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 1500;

						// - Move -  8  -  Forward Roll
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 1100;

						// - Move -  9  -  Dodge Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 1100;

						// - Move -  10  -  BackFlip
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 1800;
						


						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
														Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;


				case 3:	   //#=- Medium Range - Aggresive
					{

					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Q_Forge->Forge[AIcounter].attackon == 0*/ && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Q_Forge->Forge[AIcounter].astackrun > 0)
								{
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Q_Forge->Forge[AIcounter].BlockInit == 0)
							{
							Q_Forge->Forge[AIcounter].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 8)))
								{
								Q_Forge->Forge[AIcounter].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Q_Forge->Forge[AIcounter].BlockHeightMeM != Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 7)))
										{
										Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
										}
									}
								else
									{
									Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Q_Forge->Forge[AIcounter].Blocking = 0;
						Q_Forge->Forge[AIcounter].BlockInit = 0;

						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].astackrun > 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 5) + 2))	//7.5
								{
								Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 1;
							}
						}




					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Q_Forge->Forge[AIcounter].AV.Xform.Translation.y) > 50)
								{
								if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 11;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Q_Forge->Forge[AIcounter].Mposestate == 11)
										{
										Q_Forge->Forge[AIcounter].JumpDir = 0;

										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
										//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

										if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

										Q_Forge->Forge[AIcounter].jumpposecnt = 0;
										Q_Forge->Forge[AIcounter].Mposestate = 12;
										Q_Forge->Forge[AIcounter].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Running == 1 && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7.5) + 2))
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 1;
							}
						}

#pragma("FIXME:::Weapon Excludes")
#if 0
					//### Check for enemy using weapon
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
#endif

					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
						{
						Q_Forge->Forge[AIcounter].Block = 0;
						Q_Forge->Forge[AIcounter].Blocking = 0;
						}


					//#### Test Distance 1
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 400)
						{

						//###Run Towards Avatar
						Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
						if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
						Q_Forge->Forge[AIcounter].Mposestate = 3;
						Q_Forge->Forge[AIcounter].Running = 1;

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							Q_Forge->Forge[AIcounter].collide = 1;
							}
						
						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
						
						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

						//Attack position not achieved yet
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;

						//##### Factor thru a response
						if(/*Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 && */Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
							{
							//##### -  Set The Number Of Factors  - #####
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 0;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 15;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 10;
							

							//##### -  Reset Pathway Factors  - #####

							//### Reset Delay and Move To Encount Factors
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
							

							//### Reset Single Attacks Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
								helly++;
								}

							//### Reset Combo Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
								helly++;
								}

							//### Reset Special Attack Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
								helly++;
								}

							//### Reset Movement and Dodge Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
								helly++;
								}

							
							//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

							//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 15000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							else
								{	//Reset Delay Switch
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 30000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
								}
							//### Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;



							//####### -  Single Attacks  - #######
							
							// - Attack once lightly then rethink
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 0;

							// - Single RLPunch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 0;

							// - Single RMKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 0;

							// - Low Punch Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 0;

							// - Low Punch Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 0;

							// - Single Renzou
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;


							//####### -  Special Attacks  - #######

							// - Special -  1  -  RHKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 0;

							// - Special -  2  -  Flame Uppercut
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 0;

							// - Special -  3  -  VHKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 0;

							// - Special -  4  -  Leap Spin Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 0;

							// - Special -  5  -  Rush Elbow
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 0;

							// - Special -  6  -  Sky Push
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 0;

							// - Special -  7  -  Twist Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 0;

							// - Special -  8  -  Hover Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 0;
							
							// - Special -  9  -  Hadou-ken
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 800;

							// - Special -  10  -   JSRUSHUP
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 1000;

							// - Special -  11  -  RUSHPUNCHNORMAL
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 0;

							// - Special -  12  -  RUSHPUNCH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 0;

							// - Special -  13  -  RUSHKICK
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 0;

							// - Special -  14  -  Static Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 0;

							// - Special -  15  -  JSRUSH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 20000;

							// - Special -  16  -  Power Combo 2
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 2000;

							// - Special -  17  -  JS FLAME UPPERCUT
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 1000;

							// - Special -  18  -  HYPER KNEE FLEX
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 1000;

							// - Special -  19  -  AIR DASH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 1000;

							// - Special -  20  -  SAKURA TRIBUTE
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 1000;

							// - Special -  21  -  SPIN KICK FULL
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

							// - Special -  22  -  CYCLONE KICK
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 8000;


							//####### -  Movement / Dodges  - #######
						
							// - Move -  1  -  Taunt
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 2000;

							// - Move -  2  -  SideStep
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 7000;

							// - Move -  3  -  JUMP
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 10000;

							// - Move -  4  -  Roll Low Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 0;

							// - Move -  5  -  Roll Low Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 0;

							// - Move -  6  -  CartWheel Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 3500;

							// - Move -  7  -  CartWheel Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 3500;

							// - Move -  8  -  Forward Roll
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 5000;

							// - Move -  9  -  Dodge Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 0;

							// - Move -  10  -  BackFlip
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 0;
							


							//IMP ********\/\/\/\/\/
							//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


							//##### Collate Factor Sums
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
								aero++;
								}


							//######## FACTOR TOTAL ########
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
															Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


							//### ---->>> Seed the finger
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


							//######### -  Determine Result  - #########

										//### Delay
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


							//##### -  Search Factor Arrays For Result  - #####

							//### Set Search Variable
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

							helly=0;	//### Attack Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
								helly++;
								}


							helly=0;	//### Combo Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
								helly++;
								}


							helly=0;	//### Special Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
								helly++;
								}


							helly=0;	//### Move Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
								helly++;
								}


							//### Set Decision to ON position
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;

							}//END Condition - Move Encount

						}//END Distance Check 1



					//#### Test Distance 2
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 400)
						{

						/*if(Q_Forge->Forge[AIcounter].attackon == 0)
							{
							//###Run Towards Avatar
							Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
							if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
							Q_Forge->Forge[AIcounter].Mposestate = 3;
							Q_Forge->Forge[AIcounter].Running = 1;

							//*** Actor
							Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*//*&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
							Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

							Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
							Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

							// This does collision detection
							if(Qpo->Collision_RayTest(
										 NULL, 
										 NULL, 
										 &Q_Forge->Forge[AIcounter].AV.OldPos, 
										 &Q_Forge->Forge[AIcounter].AV.NewPos, 
										 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
										 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
										 0xffffffff, NULL, NULL, 
										 &Q_Forge->Forge[AIcounter].AV.Collision))
								{
								// Set the new pos to the point of collision
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Collision.Impact;
								}
							
							Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
							Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
							
							// Set the player to the new pos
							Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

							//Attack position not achieved yet
							Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
							}*/
						

						//##### Factor thru a response
						if(/*Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 &&*/ Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
							{
							//##### -  Set The Number Of Factors  - #####
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 0;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 22;
							
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 10;
							

							//##### -  Reset Pathway Factors  - #####

							//### Reset Delay and Move To Encount Factors
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
							

							//### Reset Single Attacks Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
								helly++;
								}

							//### Reset Combo Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
								helly++;
								}

							//### Reset Special Attack Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
								helly++;
								}

							//### Reset Movement and Dodge Factors
							helly=0;
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
								helly++;
								}

							
							//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

							//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 10000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							else
								{	//Reset Delay Switch
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 10000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
								}
							//### Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;



							//####### -  Single Attacks  - #######
							
							// - Attack once lightly then rethink
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 0;

							// - Single RLPunch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 0;

							// - Single RMKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 0;

							// - Low Punch Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 0;

							// - Low Punch Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 0;

							// - Single Renzou
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;



							//####### -  Jink Special Attacks  - #######

							// - Special -  1  -  RHKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 0;

							// - Special -  2  -  Flame Uppercut
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 0;

							// - Special -  3  -  VHKick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 0;

							// - Special -  4  -  Leap Spin Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 6000;

							// - Special -  5  -  Rush Elbow
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 4000;

							// - Special -  6  -  Sky Push
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 0;

							// - Special -  7  -  Twist Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 3000;

							// - Special -  8  -  Hover Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 0;

							// - Special -  9  -  Hadou-ken
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 6000;

							// - Special -  10  -   JSRUSHUP
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 1000;

							// - Special -  11  -  RUSHPUNCHNORMAL
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 8000;

							// - Special -  12  -  RUSHPUNCH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 9000;

							// - Special -  13  -  RUSHKICK
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 9000;

							// - Special -  14  -  Static Kick
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 0;

							// - Special -  15  -  JSRUSH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 5000;

							// - Special -  16  -  Power Combo 2
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 2000;

							// - Special -  17  -  JS FLAME UPPERCUT
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 3000;

							// - Special -  18  -  HYPER KNEE FLEX
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 4000;

							// - Special -  19  -  AIR DASH
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 4000;

							// - Special -  20  -  SAKURA TRIBUTE
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 9000;

							// - Special -  21  -  SPIN KICK FULL
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

							// - Special -  22  -  CYCLONE KICK
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 4000;



							//####### -  Movement / Dodges  - #######
						
							// - Move -  1  -  Taunt
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 1500;

							// - Move -  2  -  SideStep
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 1500;

							// - Move -  3  -  JUMP
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 8000;

							// - Move -  4  -  Roll Low Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 1000;

							// - Move -  5  -  Roll Low Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 1000;

							// - Move -  6  -  CartWheel Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 4000;

							// - Move -  7  -  CartWheel Right
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 4000;

							// - Move -  8  -  Forward Roll
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 3000;

							// - Move -  9  -  Dodge Left
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 0;

							// - Move -  10  -  BackFlip
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 10000;
							


							//IMP ********\/\/\/\/\/
							//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


							//##### Collate Factor Sums
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
								aero++;
								}
							aero = 0;
							while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
								aero++;
								}


							//######## FACTOR TOTAL ########
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
															Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
															+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


							//### ---->>> Seed the finger
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


							//######### -  Determine Result  - #########

										//### Delay
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


							//##### -  Search Factor Arrays For Result  - #####

							//### Set Search Variable
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

							helly=0;	//### Attack Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
								helly++;
								}


							helly=0;	//### Combo Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
								helly++;
								}


							helly=0;	//### Special Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
								helly++;
								}


							helly=0;	//### Move Factors
							while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
									&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
								helly++;
								}


							//### Set Decision to ON position
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;

							}//END Condition - Move Encount

						}//END Distance Check 2

					} break;


				case 4:	   //#=- Medium Range - Defensive
					{

							//###Initial Move to encounter\/\/\/\/\/\/\/\/\/\/\/\/\/
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 120 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 1;
						Q_Forge->Forge[AIcounter].astackcnt = 0;
						Q_Forge->Forge[AIcounter].astackrun = 0;
						Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

						if(Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 6;
							//### Set Decision to ON position
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
							}
						}


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 90 && Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))
						{
						//###Run Towards Avatar

						Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
						if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
						Q_Forge->Forge[AIcounter].Mposestate = 3;
						Q_Forge->Forge[AIcounter].Running = 1;

						//*** Actor
						Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
						Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							Q_Forge->Forge[AIcounter].collide = 1;
							}

						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;

						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

						//Attack position not achieved yet
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
						//Cancel combos
						//Q_Forge->Forge[AIcounter].astackcnt = 0;
						//Q_Forge->Forge[AIcounter].astackrun = 0;
						//Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
						}
					else 
						{
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
						}



					//###Defensive Checks \/\/\/\/\/\/\/\/\/\/\/\/

					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 1;


					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].attackon == 1 /*&& Q_Forge->Forge[AIcounter].attackon == 0*/ && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 26 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 28 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate != 30)
						{
						if((((float)rand() / 32767) * 3) < 0.35 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 0.5))
							{	//~~~~~~~  Testing combo cancel to block  ~~~~~~~~~~~
							if(Q_Forge->Forge[AIcounter].astackrun > 0)
								{
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								}
							}

						if(Q_Forge->Forge[AIcounter].BlockInit == 0)
							{
							Q_Forge->Forge[AIcounter].BlockInit = 1;
							//Need to decide here which action to take Blocking , dodge , movement
							//Force Block cancel attacks
							if(( (((float)rand() / 32767) * 10) < ((2 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 8)))
								{
								Q_Forge->Forge[AIcounter].Blocking = 1;

								//When Change in Height Memory Random Check Also check with level for accuracy
								if(Q_Forge->Forge[AIcounter].BlockHeightMeM != Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight)
									{	//Personality / Class check Required Here
									if(( (((float)rand() / 32767) * 10) < ((3 * (float)Q_Forge->Forge[AIcounter].LEVELFactor) + 7)))
										{
										Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
										Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
										}
									}
								else
									{
									Q_Forge->Forge[AIcounter].BlockHeight = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlowHeight;
									Q_Forge->Forge[AIcounter].BlockHeightMeM = Q_Forge->Forge[AIcounter].BlockHeight;
									}

								}
								//Very crap error creation REDO
							}

						//### Counter Attack only after long attacks
						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if((((float)rand() / 32767) * 2) < 0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5))
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						
						}
					else
						{
						Q_Forge->Forge[AIcounter].Blocking = 0;
						Q_Forge->Forge[AIcounter].BlockInit = 0;

						if(Q_Forge->Forge[AIcounter].BlockHitFLAG == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 0)
							{
							Q_Forge->Forge[AIcounter].BlockHitFLAG = 0;
							Q_Forge->Forge[AIcounter].EnemyPoseState = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate;
							
							if(Q_Forge->Forge[AIcounter].EnemyPoseState == 27 || Q_Forge->Forge[AIcounter].EnemyPoseState == 25 || Q_Forge->Forge[AIcounter].EnemyPoseState == 24 || Q_Forge->Forge[AIcounter].EnemyPoseState == 23 || Q_Forge->Forge[AIcounter].EnemyPoseState == 22 || Q_Forge->Forge[AIcounter].EnemyPoseState == 21 || Q_Forge->Forge[AIcounter].EnemyPoseState == 17 || Q_Forge->Forge[AIcounter].EnemyPoseState == 13 || Q_Forge->Forge[AIcounter].EnemyPoseState == 10 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 41 || Q_Forge->Forge[AIcounter].EnemyPoseState == 40 || Q_Forge->Forge[AIcounter].EnemyPoseState == 39 || Q_Forge->Forge[AIcounter].EnemyPoseState == 35 || Q_Forge->Forge[AIcounter].EnemyPoseState == 34 || Q_Forge->Forge[AIcounter].EnemyPoseState == 33 || Q_Forge->Forge[AIcounter].EnemyPoseState == 32 || Q_Forge->Forge[AIcounter].EnemyPoseState == 31 || Q_Forge->Forge[AIcounter].EnemyPoseState == 28 ||
								Q_Forge->Forge[AIcounter].EnemyPoseState == 38 || Q_Forge->Forge[AIcounter].EnemyPoseState == 53 || Q_Forge->Forge[AIcounter].EnemyPoseState == 46 || Q_Forge->Forge[AIcounter].EnemyPoseState == 45 || Q_Forge->Forge[AIcounter].EnemyPoseState == 44)
								{
								if( (((float)rand() / 32767) * 2) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 6 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 2;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 3;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 5) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 4;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 5;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							else
								{
								if( (((float)rand() / 32767) * 3) < (0.5 + (((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 1.5)) )
									{
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

									Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ( rand() % 7 );
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 3) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 101;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger >= 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 102;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 103;
									if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger == 7) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 105;

									//### Set Decision to ON position
									Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
									}
								}
							}
						}


					//##### - SPECIAL ACTION RESETS - #####

					//### Reset Special nullification		This needs work maybe level altering
					if(Q_Forge->Forge[AIcounter].attackon == 1 && ( TIME >= Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT + 200 ) )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.STOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.EnergySTOP = 0;
						}

					//### Reset Collision Flip
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT + 100 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.CollSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
						}

					//### Reset Avatar Is Hit
					if(TIME >= Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT + 30 )
						{
						Q_Forge->Forge[AIcounter].Q_Brain.HitSTOPCNT = TIME;
						Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 0;
						}


					//#####-  Special attack enemy if enemy is in hit reaction  -#####
					if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP == 0)
						{
						if( ( Q_Forge->Forge[AIcounter].LEVEL > 0 ) && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 26 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 28 || Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Aposestate == 30 ) && ( Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 ) && ( Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 ) )
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 6) + 8))	//4 + 2
								{
								Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = (((float)rand() / 32767) * 100);
								//### Knock Downs
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 2) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 200;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 2 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 4) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 201;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 4 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 6) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 202;
								//### Mid Hits
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 6 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 10) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 203;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 10 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 15) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 204;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 15 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 20) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 205;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 20 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 25) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 206;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 25 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 30) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 207;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 30 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 35) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 210;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 35 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 40) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 211;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 40 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 45) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 212;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 45 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 60) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 213;

								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 60 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 65) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 215;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 65 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 70) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 216;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 70 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 75) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 217;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 75 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 80) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 218;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 80 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 219;
								//if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 85 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 90) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 220;
								if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 90 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger <= 100) Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = 221;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.SpecialSTOP = 1;
							}
						}

#if 0
					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 304;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, -120, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 303;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


					//Collision Detection
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60; Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.NewPos, 15, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);
					if(Qpo->Collision_RayTest(NULL, NULL, &Q_Forge->Forge[AIcounter].AV.OldPos, &Q_Forge->Forge[AIcounter].AV.NewPos,/* GE_CONTENTS_CANNOT_OCCUPY /* GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS */ 0xffffffff, NULL, NULL, &Q_Forge->Forge[AIcounter].AV.Collision))
						{ 
						if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != 0)
							{
							if(Q_Forge->Forge[AIcounter].AV.Collision.Avatar != Q_Forge->Forge[AIcounter].AV.Avatar)
								{
								//Q_Forge->Forge[AIcounter].collide=1;
								Q_Forge->Forge[AIcounter].Q_Brain.PREFinger = 309;
								}
							}
						}
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
#endif

					//-[[TEST]]-
					//~~~~~~~  Testing Collision Detect to Movement  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].collide == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 14);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 3) + 11))
								{
								Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 1;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverrideAnswer = Q_Forge->Forge[AIcounter].Q_Brain.PREFinger;

								//### Set Decision to ON position
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
							}
						else Q_Forge->Forge[AIcounter].Q_Brain.CollDetSTOP = 1;
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Hit Block So cancel to Block for Time  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].astackrun > 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].BlockHit == 1)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 5) + 2))	//7.5
								{
								Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.ComboCancelSTOP = 1;
							}
						}


					//-[[TEST]]-
					//~~~~~~~  Testing Deflect  ~~~~~~~~~~~
					if(Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP == 0)
						{
						if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].HitLethal == 1) && !(Q_Forge->Forge[AIcounter].Aposestate == 30) && !(Q_Forge->Forge[AIcounter].Aposestate == 51) && !(Q_Forge->Forge[AIcounter].Aposestate == 52))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7) + 3))
								{
								if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
									{
									Q_Forge->Forge[AIcounter].DeflectPower = 0;

									if(Q_Forge->Forge[AIcounter].Aposestate == 26)
										{
										Q_Forge->Forge[AIcounter].Deft_InReact = 1;
										Q_Forge->Forge[AIcounter].Deft_PoseState = Q_Forge->Forge[AIcounter].Aposestate;
										Q_Forge->Forge[AIcounter].Deft_attposecnt = Q_Forge->Forge[AIcounter].attposecnt;
										Q_Forge->Forge[AIcounter].Deft_HitReactScale = Q_Forge->Forge[AIcounter].HitReactScale;
										}
									}
								else Q_Forge->Forge[AIcounter].DeflectPower = 1;

								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 63;

								Q_Forge->Forge[AIcounter].attposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;
								Q_Forge->Forge[AIcounter].blendamount[98] = 0;
								Q_Forge->Forge[AIcounter].TrailsOn = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

									//'Jink'		TODO NEW SOUND
								Qpo->Sound_Play(Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].RFistPos.Translation);
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.DeflectSTOP = 1;
							}
						}



					//-[[TEST]]-  ---FROZEN----
					//##### TESTING SPECIAL MOVEMENT #####
					//### Jump Conditional if player is higher
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y > (Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 130))	// + 65
							{
							if((Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y - Q_Forge->Forge[AIcounter].AV.Xform.Translation.y) > 50)
								{
								if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 11;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								else
									{		//### Forward Second Jump
									if(Q_Forge->Forge[AIcounter].Mposestate == 11)
										{
										Q_Forge->Forge[AIcounter].JumpDir = 0;

										Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
										//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

										if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

										Q_Forge->Forge[AIcounter].jumpposecnt = 0;
										Q_Forge->Forge[AIcounter].Mposestate = 12;
										Q_Forge->Forge[AIcounter].JumpFG = 0;
										}
									}
								}
							}
						}


					//### Run Attack Punch
					if(Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP == 0)
						{
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Running == 1 && ( Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 100 ))
							{
							Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger = (((float)rand() / 32767) * 15);
							if(Q_Forge->Forge[AIcounter].Q_Brain.SpecialFinger < ((((float)Q_Forge->Forge[AIcounter].LEVELFactor) * 7.5) + 2))
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							else Q_Forge->Forge[AIcounter].Q_Brain.RunAttSTOP = 1;
							}
						}

#pragma("FIXME:::Weapon Excludes")
#if 0
					//### Check for enemy using weapon
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist > 200 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
						{	//# Switch to Long Range Attack
						Q_Forge->Forge[AIcounter].WeaponAimer = 1.7;
						if(Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawPrime = false;
							Q_Forge->Forge[AIcounter].Q_Brain.WeaponDrawCounter = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_LONGATTK;
							}
						//Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_HANDATTK;
						}
#endif

					//Messy
					//### Avatar Is Hit so cancel blocking
					if(Q_Forge->Forge[AIcounter].Aposestate == 26 || Q_Forge->Forge[AIcounter].Aposestate == 28 || Q_Forge->Forge[AIcounter].Aposestate == 30)
						{
						Q_Forge->Forge[AIcounter].Block = 0;
						Q_Forge->Forge[AIcounter].Blocking = 0;
						}


					//##### Factor thru a response
					if(/*Q_Forge->Forge[AIcounter].Q_Brain.MoveEncount == 0 &&*/ Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1 && Q_Forge->Forge[AIcounter].Flip == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0 && Q_Forge->Forge[AIcounter].WeaponStatus == 0)
						{
						//##### -  Set The Number Of Factors  - #####
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack = 6;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo = 8;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special = 22;
						
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move = 10;
						

						//##### -  Reset Pathway Factors  - #####

						//### Reset Delay and Move To Encount Factors
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Alpha = 0;
						

						//### Reset Single Attacks Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly] = 0;
							helly++;
							}

						//### Reset Combo Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly] = 0;
							helly++;
							}

						//### Reset Special Attack Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly] = 0;
							helly++;
							}

						//### Reset Movement and Dodge Factors
						helly=0;
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly] = 0;
							helly++;
							}

						
						//######## --< Infuse Factors depending on situation with 'if' trees >-- ########

						//####### -  Delay  -  Delay Decision	//TODO personality adjustments for delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch == 0) Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 10000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
						else
							{	//Reset Delay Switch
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay = 30000;// * (1 - Q_Forge->Forge[AIcounter].LEVELFactor));
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;
							}
						//### Reset Delay Switch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;


						//####### -  Single Attacks  - #######
						
						// - Attack once lightly then rethink
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[0] = 2000;

						// - Single RLPunch
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[1] = 4000;

						// - Single RMKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[2] = 2000;

						// - Low Punch Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[3] = 2500;

						// - Low Punch Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[4] = 2500;

						// - Single Renzou
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[5] = 0;


						//####### -  Combo Attacks  - #######

						// - Attack Combo 1
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[0] = 1200;

						// - Attack Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[1] = 1000;

						// - Attack Combo 3
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[2] = 1000;

						// - Attack Combo 4
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[3] = 1500;

						// - Attack Combo 5
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[4] = 1000;

						// - Attack Combo 6	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[5] = 1500;

						// - Attack Combo 7	NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[6] = 5000;

						// - Attack Combo 8 NEW
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[7] = 3000;



						//####### -  Jink Special Attacks  - #######

						// - Special -  1  -  RHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[0] = 1000;

						// - Special -  2  -  Flame Uppercut
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[1] = 800;

						// - Special -  3  -  VHKick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[2] = 1000;

						// - Special -  4  -  Leap Spin Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[3] = 1500;

						// - Special -  5  -  Rush Elbow
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[4] = 1000;

						// - Special -  6  -  Sky Push
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[5] = 2000;

						// - Special -  7  -  Twist Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[6] = 1500;

						// - Special -  8  -  Hover Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[7] = 1000;
							
						// - Special -  9  -  Hadou-ken
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[8] = 3000;

						// - Special -  10  -   JSRUSHUP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[9] = 10000;

						// - Special -  11  -  RUSHPUNCHNORMAL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[10] = 20000;

						// - Special -  12  -  RUSHPUNCH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[11] = 15000;

						// - Special -  13  -  RUSHKICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[12] = 10000;

						// - Special -  14  -  Static Kick
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[13] = 15000;

						// - Special -  15  -  JSRUSH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[14] = 10000;

						// - Special -  16  -  Power Combo 2
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[15] = 3000;

						// - Special -  17  -  JS FLAME UPPERCUT
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[16] = 1000;

						// - Special -  18  -  HYPER KNEE FLEX
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[17] = 1000;

						// - Special -  19  -  AIR DASH
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[18] = 1000;

						// - Special -  20  -  SAKURA TRIBUTE
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[19] = 2000;

						// - Special -  21  -  SPIN KICK FULL
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[20] = 0;

						// - Special -  22  -  CYCLONE KICK
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[21] = 1000;



						//####### -  Movement / Dodges  - #######
						
						// - Move -  1  -  Taunt
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[0] = 5000;

						// - Move -  2  -  SideStep
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[1] = 2000;

						// - Move -  3  -  JUMP
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[2] = 800;

						// - Move -  4  -  Roll Low Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[3] = 500;

						// - Move -  5  -  Roll Low Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[4] = 500;

						// - Move -  6  -  CartWheel Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[5] = 700;

						// - Move -  7  -  CartWheel Right
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[6] = 700;

						// - Move -  8  -  Forward Roll
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[7] = 200;

						// - Move -  9  -  Dodge Left
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[8] = 600;

						// - Move -  10  -  BackFlip
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[9] = 700;
						

						//IMP ********\/\/\/\/\/
						//TODO Tweak and Weight Factors according to Pathways, Logic, Experience, and Communication , Level etc


						//##### Collate Factor Sums
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move = 0;

						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[aero];
							aero++;
							}
						aero = 0;
						while(aero < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[aero];
							aero++;
							}


						//######## FACTOR TOTAL ########
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM =
														Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Attack
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Combo
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Special
														+ Q_Forge->Forge[AIcounter].Q_Brain.Decision.SUM_Move;


						//### ---->>> Seed the finger
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger = ((float)rand() / 32767) * Q_Forge->Forge[AIcounter].Q_Brain.Decision.FactorSUM;


						//######### -  Determine Result  - #########

									//### Delay
						if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > 0 && Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = 0;


						//##### -  Search Factor Arrays For Result  - #####

						//### Set Search Variable
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search = Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Delay;

						helly=0;	//### Attack Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Attack)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 1;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Attack[helly];
							helly++;
							}


						helly=0;	//### Combo Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Combo)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 100;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Combo[helly];
							helly++;
							}


						helly=0;	//### Special Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Special)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 200;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Special[helly];
							helly++;
							}


						helly=0;	//### Move Factors
						while(helly < Q_Forge->Forge[AIcounter].Q_Brain.Decision.NOM_Move)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger > Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search
								&& Q_Forge->Forge[AIcounter].Q_Brain.Decision.Finger < ( Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search + Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly])) Q_Forge->Forge[AIcounter].Q_Brain.Decision.Answer = helly + 300;

							Q_Forge->Forge[AIcounter].Q_Brain.Decision.INC_Search += Q_Forge->Forge[AIcounter].Q_Brain.Decision.F_Move[helly];
							helly++;
							}


						//### Set Decision to ON position
						Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 1;

						}//END Condition - Move Encount

					} break;
				}


			//IMPORTANT #####################
			//#### TODO Add Condition Flag here and when to activate Decision

			if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride == 0)
				{

				if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON == 1)
					{
					//### Reset Decision Live Status
					Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 0;


					//#####- Finger Override -#####

					if(Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride == 1)
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
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelayTimeLock = Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER + (rand() % 15) + 2;
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].idlemotion = 23;
							} break;

						case 1:	//Beta
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### Attack once
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;	//21
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 1;
								}
							} break;

						case 2:	//#### Single Attack Right Punch
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### RLPunch
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 3:	//#### Single Right Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### RMKick
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 4:	//#### Single Attack Low Punch Right
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### Low Right Punch
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 48;

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 5:	//#### Single Low Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//### Low Kick
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 43;

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 6:	//#### Single Renzou
							{
#if 0
							//### Renzou
							if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 19;

							Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[1]++;
							Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
							Q_Forge->Forge[AIcounter].astackcnt++;
#endif
							} break;
							

						case 100:	//Gamma
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

								if(Q_Forge->Forge[AIcounter].HB_Energy > 20 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 31;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
		
							} break;

						case 101:	//Delta
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

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 13;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].HB_Energy > 70 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 41;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								else
									{												//TODO Add better resort attack
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}

							} break;

						case 102:	//Omega
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


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].HB_Energy > 70 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 32;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								else
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							
							} break;

						case 103:	//Combo 6 - Punch Low Punch
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 47;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].HB_Energy > 70 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 61;	//21

									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 104:	//Combo 7 - Low Low
							{

							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 47;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 48;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 43;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							
							} break;

						case 105:	//Combo 8 - End With Low
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


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 43;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 32;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							
							} break;

						case 106:	//Combo 9 - Punch Kick Punch then Golrekka
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 107:	//Combo 9 - Punch Kick Punch then Golrekka
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;


								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 32;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;

								if(Q_Forge->Forge[AIcounter].astackcnt < 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;	//21

								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;



						case 200:	//Special Attack - RHKick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 31;
										Q_Forge->Forge[AIcounter].HB_Energy -= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 201:	//Special Attack - FlameUppercut
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 65 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 32;
										Q_Forge->Forge[AIcounter].HB_Energy -= 65 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 202:	//Special Attack - VHKick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 35;
										Q_Forge->Forge[AIcounter].HB_Energy -= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 203:	//Special Attack - Leap Spin Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 22;
										Q_Forge->Forge[AIcounter].HB_Energy -= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 204:	//Special Attack - Rush Elbow
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 65;
										Q_Forge->Forge[AIcounter].HB_Energy -= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 205:	//Special Attack - SkyPush
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 25 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 41;
										Q_Forge->Forge[AIcounter].HB_Energy -= 25 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 206:	//Special Attack - Twist Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 61;
										Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 207:	//Special Attack - Hover Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 55;
										Q_Forge->Forge[AIcounter].HB_Energy -= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 208:	//Special Attack - Hadou-ken
							{
#if 0
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 50;
										Q_Forge->Forge[AIcounter].HB_Energy -= 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
#endif
							} break;


						case 209:	//Special Attack - JSRUSHUP
							{
							if(Q_Forge->Forge[AIcounter].HB_Energy > 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5)
									{
									Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 76;
									Q_Forge->Forge[AIcounter].HB_Energy -= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
									}
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 210:	//Special Attack - RUSH PUNCH NORMAL
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 85;
										Q_Forge->Forge[AIcounter].HB_Energy -= 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 211:	//Special Attack - RUSH PUNCH BIG HIT
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 86;
										Q_Forge->Forge[AIcounter].HB_Energy -= 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 212:	//Special Attack - RUSH Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 87;
										Q_Forge->Forge[AIcounter].HB_Energy -= 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 213:	//Special Attack - Static Kick
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo
								if(Q_Forge->Forge[AIcounter].HB_Energy > 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 75;
										Q_Forge->Forge[AIcounter].HB_Energy -= 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 214:	//Special Attack - JSRUSH
							{
							if(Q_Forge->Forge[AIcounter].HB_Energy > 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
								{
								if(Q_Forge->Forge[AIcounter].astackcnt < 5)
									{
									Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 73;
									Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
									}
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[1]++;
								Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
								Q_Forge->Forge[AIcounter].astackcnt++;
								}
							} break;

						case 215:	//Special Attack - Power Combo 2
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 64;
										Q_Forge->Forge[AIcounter].HB_Energy -= 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 216:	//Special Attack - JS FLAME UPPERCUT
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 240 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].HB_Energy -= 240 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 57;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 217:	//Special Attack - HYPER KNEE FLEX
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 25;
										Q_Forge->Forge[AIcounter].HB_Energy -= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 218:	//Special Attack - AIR DASH
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 53;
										Q_Forge->Forge[AIcounter].HB_Energy -= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 219:	//Special Attack - SAKURA TRIBUTE
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 56;
										Q_Forge->Forge[AIcounter].HB_Energy -= 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 220:	//Special Attack - SPIN KICK FULL
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo						
								if(Q_Forge->Forge[AIcounter].HB_Energy > 170 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 34;
										Q_Forge->Forge[AIcounter].HB_Energy -= 170 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 221:	//Special Attack - CYCLONE KICK
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.ATTposON == 1)
								{
								//###Try a combo
								if(Q_Forge->Forge[AIcounter].HB_Energy > 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
									{
									if(Q_Forge->Forge[AIcounter].astackcnt < 5)
										{
										Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 84;
										Q_Forge->Forge[AIcounter].HB_Energy -= 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
										}
									Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[1]++;
									Q_Forge->Forge[AIcounter].astackcntdir[2] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[3] = 0;
									Q_Forge->Forge[AIcounter].astackcntdir[4] = 0;
									Q_Forge->Forge[AIcounter].astackcnt++;
									}
								}
							} break;

						case 300:	//Taunt
							{
							//### Taunt
							Q_Forge->Forge[AIcounter].Mposestate = 51;
							Q_Forge->Forge[AIcounter].runposecnt = 0;
							} break;

						case 301:	//Move into Position / Alternately Sidestep
							{
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DelaySwitch = 0;

							Q_Forge->Forge[AIcounter].Running = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.MoveSide = 1;
							Q_Forge->Forge[AIcounter].Q_Brain.MoveTimeLock = Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER;
							Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger = rand() % 10;
							if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger <= 5) Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = -1;
							if(Q_Forge->Forge[AIcounter].Q_Brain.MoveFinger > 5)  Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect = 1;

							//Attack position achieved
							Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
							
							Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/2)*_->TimeScale;

							if(Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect < 0)
								{
								if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6) || (Q_Forge->Forge[AIcounter].Mposestate != 5)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
									{
									Q_Forge->Forge[AIcounter].Mposestate = 5;
									Q_Forge->Forge[AIcounter].StepTimer = 0;
									}

								//*** Actor
								Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
								Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
								}
							else
								{
								if(((Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6) || (Q_Forge->Forge[AIcounter].Mposestate != 5)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
									{
									Q_Forge->Forge[AIcounter].Mposestate = 6;
									Q_Forge->Forge[AIcounter].StepTimer = 0;
									}

								//*** Actor
								Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
								Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
								Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
								}

							Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
							Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

							// This does collision detection
							if(Qpo->Collision_RayTest(
										 NULL,
										 NULL,
										 &Q_Forge->Forge[AIcounter].AV.OldPos,
										 &Q_Forge->Forge[AIcounter].AV.NewPos,
										 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
										 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
										 0xffffffff, NULL, NULL,
										 &Q_Forge->Forge[AIcounter].AV.Collision))
								{
								// Set the new pos to the point of collision
								Q_Forge->Forge[AIcounter].collide = 1;
								}

							Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
							Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
							
							// Set the player to the new pos
							if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

							} break;

						case 302:	//#### Jump
							{
							if((Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15))	//### Forward First Jump
								{
								Q_Forge->Forge[AIcounter].JumpDir = 0;

								Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
								//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

								if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

								Q_Forge->Forge[AIcounter].jumpposecnt = 0;
								Q_Forge->Forge[AIcounter].Mposestate = 11;
								Q_Forge->Forge[AIcounter].JumpFG = 0;
								}
							else
								{		//### Forward Second Jump
								if(Q_Forge->Forge[AIcounter].Mposestate == 11)
									{
									Q_Forge->Forge[AIcounter].JumpDir = 0;

									Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].JumpVec);
									//Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

									if((rand() % 50) > 35) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

									Q_Forge->Forge[AIcounter].jumpposecnt = 0;
									Q_Forge->Forge[AIcounter].Mposestate = 12;
									Q_Forge->Forge[AIcounter].JumpFG = 0;
									}
								}
							} break;

						case 303:	//#### Roll Low Left
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 28;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].SideSpeed = 0;
								Q_Forge->Forge[AIcounter].JumpOff = 0;
								}
							} break;

						case 304:	//#### Roll Low Right
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 29;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].SideSpeed = 0;
								Q_Forge->Forge[AIcounter].JumpOff = 0;
								}
							} break;

						case 305:	//#### CartWheel Left
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 23;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].SideSpeed = 0;
								Q_Forge->Forge[AIcounter].JumpOff = 0;
								}
							} break;

						case 306:	//#### CartWheel Right
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 24;
								Q_Forge->Forge[AIcounter].runposecnt = 1.67;
								Q_Forge->Forge[AIcounter].SideSpeed = 0;
								Q_Forge->Forge[AIcounter].JumpOff = 0;
								}
							} break;

						case 307:	//#### Forward Roll
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 8)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 26;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								Q_Forge->Forge[AIcounter].attposecnt = 0;
								}
							} break;

						case 308:	//#### Dodge Left
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 8)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 25;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].SideSpeed = 0;
								}
							} break;

						case 309:	//#### BackFlip
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Aposestate != 62)
								{
								Q_Forge->Forge[AIcounter].Mposestate = 8;
								Q_Forge->Forge[AIcounter].runposecnt = 0;
								Q_Forge->Forge[AIcounter].astackcnt = 0;
								Q_Forge->Forge[AIcounter].astackrun = 0;
								Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
								Q_Forge->Forge[AIcounter].attposecnt = 0;
								Q_Forge->Forge[AIcounter].Aposestate = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0;
								Q_Forge->Forge[AIcounter].TrailsOn = 0;
								Q_Forge->Forge[AIcounter].attackon = 0;
								}
							} break;

						}//End Decision Switch
						
					}//END Decision ON

				}//END Override
			else	
				{//###Decision Overrides

				//### Reset Decision Live Status
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.ON = 0;

				//## Side Step
				if(Q_Forge->Forge[AIcounter].Q_Brain.MoveSide == 1)
					{
					if(Q_Forge->Forge[AIcounter].attackon == 0)
						{
						//Attack position achieved
						Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 1;
								
						if (KEY_PRESS_DOWN(QIN_LSHIFT)) Q_Forge->Forge[AIcounter].ForwardSpeed = -(Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Left
						else Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/2)*_->TimeScale;							//Sidestep Left
						
						if(Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect < 0)
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
								{
								Q_Forge->Forge[AIcounter].Mposestate = 5;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].runposecnt = 0.4;
								Q_Forge->Forge[AIcounter].idleposecnt = 0;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								}

							//*** Actor
							Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
							Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
							}
						else
							{
							if(Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Forge->Forge[AIcounter].Mposestate != 6 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15) && Q_Forge->Forge[AIcounter].Mposestate != 23)	//Dependent Movement mode switch
								{
								Q_Forge->Forge[AIcounter].Mposestate = 6;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
								Q_Forge->Forge[AIcounter].runposecnt = 0.08;
								Q_Forge->Forge[AIcounter].idleposecnt = 0;
								Q_Forge->Forge[AIcounter].StepTimer = 0;
								}

							//*** Actor
							Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
							Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Left);
							Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed * Q_Forge->Forge[AIcounter].Q_Brain.MoveDirect, &Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.NewPos);
							}


						Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

						// This does collision detection
						if(Qpo->Collision_RayTest(
									 NULL, 
									 NULL, 
									 &Q_Forge->Forge[AIcounter].AV.OldPos, 
									 &Q_Forge->Forge[AIcounter].AV.NewPos, 
									 // GE_CONTENTS_CANNOT_OCCUPY                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
									 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
									 0xffffffff, NULL, NULL, 
									 &Q_Forge->Forge[AIcounter].AV.Collision))
							{
							// Set the new pos to the point of collision
							Q_Forge->Forge[AIcounter].collide = 1;
							}

						Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
						Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;


						// Set the player to the new pos
						if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

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


				Q_Forge->Forge[AIcounter].Q_Brain.Decision.OverrideTIMER++;

				}//END Else - Decision Overide

			//BREAK HAND TO HAND ATTACK
			} break;

		case 8:   //Long Range Attack
			{
			LoopON = 0;

			Q_Forge->Forge[AIcounter].Mposestate = 0;
			Q_Forge->Forge[AIcounter].idlemotion = 23;

				//###Check Vision
			Q_Forge->Forge[AIcounter].Q_Brain.VisionCHK = 1;

				//###Lock On
				//Turn to Face Avatar Conditional (Not in Hit Reaction)
			if(Q_Forge->Forge[AIcounter].WeaponStatus != 8 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52)
				{

				//####### -  Mode Universal Avatar Control - Update if required for mode specific Control -#####

				//##### Turn to Face Avatar - Target in View
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT == 1)
					{
					if(Q_Forge->Forge[AIcounter].Aposestate != 13)
						{
						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng/1.5;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng/1.5);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}
					else
						{
						Q_Forge->Forge[AIcounter].Angles.y += (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, (Q_Forge->Forge[AIcounter].ScanTurnAng / 1.5) + 0.07);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
						}


					//##### TEMP Run towards enemy
					//###Run Towards Avatar

					Q_Forge->Forge[AIcounter].ForwardSpeed = 10*_->TimeScale;
					if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
					Q_Forge->Forge[AIcounter].Mposestate = 3;
					Q_Forge->Forge[AIcounter].Running = 1;

					//*** Actor
					Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
					Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
					Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

					Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
					Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

					// This does collision detection
					if(Qpo->Collision_RayTest(
								 NULL, 
								 NULL, 
								 &Q_Forge->Forge[AIcounter].AV.OldPos, 
								 &Q_Forge->Forge[AIcounter].AV.NewPos, 
								 //GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
								 //GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
								 0xffffffff, NULL, NULL, 
								 &Q_Forge->Forge[AIcounter].AV.Collision))
						{
						// Set the new pos to the point of collision
						Q_Forge->Forge[AIcounter].collide = 1;
						}
					
					Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
					Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
					
						
					// Set the player to the new pos
					if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

					//Attack position not achieved yet
					Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;


					//##### Drop target if dead
					if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID].Health <= 0)
						{
						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
						Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
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
						Q_Forge->Forge[AIcounter].Mposestate = 0;
						Q_Forge->Forge[AIcounter].blendamount[8] = 0;
						Q_Forge->Forge[AIcounter].blendamount[0] = 0;
						Q_Forge->Forge[AIcounter].AttackIdle = 2000;
						Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;
						Q_Forge->Forge[AIcounter].Aposestate = 0;
						Q_Forge->Forge[AIcounter].attackon = 0;

						if(Q_Forge->Forge[AIcounter].Aposestate != 100 && Q_Forge->Forge[AIcounter].AirBorn == 0)
							{
							Q_Forge->Forge[AIcounter].Aposestate = 100;
							Q_Forge->Forge[AIcounter].attackon = 1;
							Q_Forge->Forge[AIcounter].attposecnt = 0;
							Q_Forge->Forge[AIcounter].astackcnt = 0;
							Q_Forge->Forge[AIcounter].astackrun = 0;
							Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
							}
						}

					//### Activate Timed Search
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 20)
						{ Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED = 1; }

					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadSearch = 0;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadDir = 1;
					Q_Forge->Forge[AIcounter].Q_Brain.HeadAngles.x = 0;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 0;
					}
				else //##### Turn to Face Avatar - Target Vanished
					{
					if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)
						{

						//##### - PERFECT TEN TIMED TARGET LOCK SYSTEM - #####

						if(Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer < 10)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)
								{
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos = playerAV[g_Player]->Xform.Translation;
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							else
								{
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos = Q_Forge->Forge[Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID].AV.Xform.Translation;
								Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y += 65;
								}
							}

						Q_Forge->Forge[AIcounter].Q_Brain.PERFECTTENtimer++;


						//#### Turn To PERFECT Enemy Position
						//###Check Distance between Pure Left and Right to work out direction of Turn
						Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);
						Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
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

						if(ScanDistL < ScanDistR) Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;

						Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].ScanTurnAng / 3;
						if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
						if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

						Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].ScanTurnAng / 2);
						Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);


						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer++;
						Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer++;


							//### Timed Search End
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 150 && Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED == 1)
							{ Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED = 0; }

							//### Conditional Target Drop
						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer > 50)
							{
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTtimer = 0;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 0;
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
							Q_Forge->Forge[AIcounter].Q_Brain.MindState = MIND_ACTIVE;
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].blendamount[8] = 0;
							Q_Forge->Forge[AIcounter].blendamount[0] = 0;
							Q_Forge->Forge[AIcounter].AttackIdle = 2000;
							Q_Forge->Forge[AIcounter].Q_Brain.idlecnt = 10;
							Q_Forge->Forge[AIcounter].Aposestate = 0;
							Q_Forge->Forge[AIcounter].attackon = 0;
							break;
							}


						if(Q_Forge->Forge[AIcounter].Q_Brain.TargetSPOTTED == 0)
							{
							if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOST == 2)	//Target Hiding
								{
								if(Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer > 50)
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
										Q_Forge->Forge[AIcounter].Q_Brain.TargetHIDEtimer = 50;

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
											if(Q_Forge->Forge[AIcounter].Aposestate != 100 && Q_Forge->Forge[AIcounter].AirBorn == 0)
												{
												Q_Forge->Forge[AIcounter].Aposestate = 100;
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
											if(Q_Forge->Forge[AIcounter].Aposestate != 100)
												{
												Q_Forge->Forge[AIcounter].Aposestate = 100;
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
								}//END Target Lost 1

							}//END Target Spotted

						}//END TargetLOCK

					}//END Else - TargetLOCK


				//## Aim Weapon Up / Down
				if(Q_Forge->Forge[AIcounter].WeaponStatus == 5)
					{
					//Do No Aiming Adjustments ***
					/*Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].Weapon, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].TempXForm1);
					Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*//*&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Forge->Forge[AIcounter].AimVec);
					Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AimVec);

					Qpo->Transform_AvatarGetUp(/*ORIG GetIn*//*&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);

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
						Q_Forge->Forge[AIcounter].ScanTurnAngAimer /= 500;  //500 //50 //4 //2

									//<
						if(TempVec2.y < TempVec1.y)
							Q_Forge->Forge[AIcounter].ScanTurnAngAimer *= -1;

						Q_Forge->Forge[AIcounter].WeaponAimer += Q_Forge->Forge[AIcounter].ScanTurnAngAimer;
						}
					}

				}//END Conditional - Hit Reaction
				

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
			else	//^^^WARNING^^^ ULTIMATE FIRE MODE -= May cause unnesessary bullet generation
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 1000)
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
					}
				}

			Q_Forge->Forge[AIcounter].FireRateTimer++;
			if(Q_Forge->Forge[AIcounter].FireRateTimer == 6) Q_Forge->Forge[AIcounter].FireRated = 0;


			//Holster weapon and change mode if enemy is too near Or Mode Return is Activated
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].ScanDist < 140 || (Q_Forge->Forge[AIcounter].Q_Brain.MODERETURN_H2H == 1 && (Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMLockID].Pos.y < Q_Forge->Forge[AIcounter].AV.Xform.Translation.y + 100)))
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

		}//END Main Mode Switch

	Q_Forge->Forge[AIcounter].QformON = 0;
	if(player[g_Player]->WeaponStatus != 0 && player[g_Player]->QformONtaunt == 1 && Q_Forge->Forge[AIcounter].Team == player[g_Player]->Team && player[g_Player]->QformChk && Q_Forge->Forge[AIcounter].HB_Dead == 0)
		{
		Q_Forge->Forge[AIcounter].QformON = 1;

		// Read ID's
		int f_ID = -1;
		for(int f_count = 0; f_count < player[g_Player]->QformVecID.size(); f_count++)
			{
			if(player[g_Player]->QformVecID[f_count] == AIcounter) f_ID = f_count;
			}

		if(f_ID == -1)
			{
			f_ID = player[g_Player]->QformVecID.size();
			player[g_Player]->QformVecID.push_back(AIcounter);
			}

		// Qformation - Team Movement and flight formation
		if(f_ID < player[g_Player]->QformVecPos.size())
			{
			float f_TempFloat;
			//##### Turn to Face Avatar - Target in View
			if(Q_Forge->Forge[AIcounter].Aposestate != 13)
				{
				//Q_Forge->Forge[AIcounter].Angles.y += (player[g_Player]->Angles.y - Q_Forge->Forge[AIcounter].Angles.y) / 2.5;
				f_TempFloat = Q_Forge->Forge[AIcounter].Angles.y;
				Q_Forge->Forge[AIcounter].Angles.y = player[g_Player]->Angles.y + PI;
				if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y -= (PI*2);
				if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y += (PI*2);

				f_TempFloat = (Q_Forge->Forge[AIcounter].Angles.y - f_TempFloat);
				if(f_TempFloat > 0.00035) f_TempFloat = 0.00035;
				if(f_TempFloat < -0.00035) f_TempFloat = -0.00035;

				Qpo->Transform_New_YRotation(&AIfriendly, f_TempFloat);
				Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
				}
			else
				{
				//Q_Forge->Forge[AIcounter].Angles.y += ((player[g_Player]->Angles.y - Q_Forge->Forge[AIcounter].Angles.y) / 2.5) + 0.07;
				f_TempFloat = Q_Forge->Forge[AIcounter].Angles.y;
				Q_Forge->Forge[AIcounter].Angles.y = player[g_Player]->Angles.y + PI;
				if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y -= (PI*2);
				if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y += (PI*2);

				f_TempFloat = (Q_Forge->Forge[AIcounter].Angles.y - f_TempFloat) + 0.07;
				if(f_TempFloat > 0.00035) f_TempFloat = 0.00035;
				if(f_TempFloat < -0.00035) f_TempFloat = -0.00035;

				Qpo->Transform_New_YRotation(&AIfriendly, f_TempFloat);
				Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
				}

			QpoVec3d QformVecTo;
			float QformLengthTo;
			Qpo->Vec3d_Subtract(&player[g_Player]->QformVecPos[f_ID], &Q_Forge->Forge[AIcounter].AV.Xform.Translation, &QformVecTo);
			QformLengthTo = Qpo->Vec3d_Length(&QformVecTo);
			Qpo->Vec3d_Normalize(&QformVecTo);
		
			if(QformLengthTo > 5)
				{
				Q_Forge->Forge[AIcounter].ForwardSpeed = 10 * _->TimeScale;
				if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
				Q_Forge->Forge[AIcounter].Mposestate = 3;
				Q_Forge->Forge[AIcounter].Running = 1;

				//*** Avatar
				Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &QformVecTo, &Q_Forge->Forge[AIcounter].AV.NewPos);
				Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

				// This does collision detection
				if(Qpo->Collision_RayTest(
								NULL, 
								NULL, 
								&Q_Forge->Forge[AIcounter].AV.OldPos, 
								&Q_Forge->Forge[AIcounter].AV.NewPos, 
								//GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
								//GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
								0xffffffff, NULL, NULL, 
								&Q_Forge->Forge[AIcounter].AV.Collision))
					{
					// Set the new pos to the point of collision
					Q_Forge->Forge[AIcounter].collide = 1;
					}
					
				Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
				Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
					
						
				// Set the player to the new pos
				if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

				//Attack position not achieved yet
				Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
				}
			}
		}
		

#if 0
	if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0)
		{
		//##### Turn to Face Avatar - Target in View
		if(Q_Forge->Forge[AIcounter].Aposestate != 13)
			{
			Q_Forge->Forge[AIcounter].Angles.y += Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 2.5;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 2.5);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
			}
		else
			{
			Q_Forge->Forge[AIcounter].Angles.y += (Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 2.5) + 0.07;
			if(Q_Forge->Forge[AIcounter].Angles.y > (PI*2)) Q_Forge->Forge[AIcounter].Angles.y = 0;
			if(Q_Forge->Forge[AIcounter].Angles.y < 0) Q_Forge->Forge[AIcounter].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&AIfriendly, (Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID].ScanTurnAng / 2.5) + 0.07);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].AV.Xform, &AIfriendly, &Q_Forge->Forge[AIcounter].AV.Xform);
			}


			//##### TEMP Run towards Leader
			//###Run Towards Avatar
		if(1)
			{
			Q_Forge->Forge[AIcounter].ForwardSpeed = 10 * _->TimeScale;
			if(Q_Forge->Forge[AIcounter].Mposestate != 3) Q_Forge->Forge[AIcounter].StepTimer = 0;
			Q_Forge->Forge[AIcounter].Mposestate = 3;
			Q_Forge->Forge[AIcounter].Running = 1;

			//*** Actor
			Q_Forge->Forge[AIcounter].AV.OldPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].AV.NewPos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].AV.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].AV.Up, &Q_Forge->Forge[AIcounter].AV.NewPos);

			Q_Forge->Forge[AIcounter].AV.OldPos.y += 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y += 60;

			// This does collision detection
			if(Qpo->Collision_RayTest(
							NULL, 
							NULL, 
							&Q_Forge->Forge[AIcounter].AV.OldPos, 
							&Q_Forge->Forge[AIcounter].AV.NewPos, 
							//GE_CONTENTS_SOLID_CLIP,                  //GE_CONTENTS_SOLID_CLIP, //// GE_CONTENTS_CANNOT_OCCUPY 
							//GE_COLLIDE_MODELS,      ////GE_COLLIDE_ALL, //GE_COLLIDE_MODELS, 
							0xffffffff, NULL, NULL, 
							&Q_Forge->Forge[AIcounter].AV.Collision))
				{
				// Set the new pos to the point of collision
				Q_Forge->Forge[AIcounter].collide = 1;
				}
					
			Q_Forge->Forge[AIcounter].AV.OldPos.y -= 60;
			Q_Forge->Forge[AIcounter].AV.NewPos.y -= 60;
					
						
			// Set the player to the new pos
			if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].AV.Xform.Translation = Q_Forge->Forge[AIcounter].AV.NewPos;

			//Attack position not achieved yet
			Q_Forge->Forge[AIcounter].Q_Brain.ATTposON = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.ATTinitiated = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.Decision.FingerOverride = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.Decision.DecOverride = 0;
			}
		}
#endif

	return true;
	}//END FIGHTER BRAIN

};