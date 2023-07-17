/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -AI Control Routines-
	*//*- Minor Component -Cleric Brain-

*/

#include "pch.h"

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

	//##### Move Attack Memory Data into Future Memory

void Q_COREFunctions::ProgressAttackMeM(int AIcounter)
	{
	if(Q_Forge->Forge[AIcounter].Q_Brain.MeMcount < 100)
		{
		//## Ensure Memory Lock
		Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;

		//## Load Current Memory ID
		Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID;

		//## Increment Attack Memory ID
		Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID++;
		if(Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID >= 100) Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = 0;
		
		//TimeStamp
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].Time = TIME;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].EventType = EVENT_AVATAR_LOSTBRIEFLY;

		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Visible = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].AV_ID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].AV_ID;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Team = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Team;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Rank = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Rank;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Pos = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Pos;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Pos.y += 65;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Ang = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Ang;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].VecTo = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].VecTo;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].ScanTurnAng = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanTurnAng;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].ScanDist = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanDist;

		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Aposestate = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Mposestate = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].attposecnt = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].attackon = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].WeaponStatus = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].Blocking = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].HitReaction = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].BlowHeight = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].HitLethal = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].NomAIPresent].BlockHit = 0;

		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].MeMMindstate = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMMindstate;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].TargetLOCKID = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].Pos = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Pos;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].Angles = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Angles;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].Health = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Health;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID].Power = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Power;

		//## Increment Memory ID's
		Q_Forge->Forge[AIcounter].Q_Brain.MeMcount++;
		if(Q_Forge->Forge[AIcounter].Q_Brain.MeMcount >= 100) Q_Forge->Forge[AIcounter].Q_Brain.MeMcount = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent++;
		if(Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent >= 100) Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = 0;
		}
	}


bool Q_COREFunctions::AIFunctionsScannerCheck(int AIcounter)
{
	QpoVec3d ScanLeft,ScanRight,ScanUp,ScanDown;
	QpoVec3d ScanScaledVecTo;
	QpoVec3d HeadIn;
	QpoTransform HeadMatrix,UseMatrix,RotMat;
	float DistLeft,DistRight,DistUp,DistDown,DistFront;
	QpoVec3d LeftToRightESCAN;
	int	TargetFound;
	int TargetLockVisible;
	int	TargetLockAIPID = -1;
	int TargetDist = MAXINT;
	QpoCollision RayTraceCOLL;

	Q_Forge->Forge[AIcounter].NomTargetsPresent = 0;
	Q_Forge->Forge[AIcounter].NomFriendlyPresent = 0;

	bool Targets = false;
	TargetLockVisible = 0;

	Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 0;
	Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent = 0;

	//TODO Add here loop to see how many people around

	//###### First Check To determine if Players are visible ######

	for(int f_Player = 0; f_Player < g_PlayerNom; f_Player++)
		{
		//## Find Vector to Player
		Qpo->Vec3d_Subtract(&playerAV[f_Player]->Xform.Translation, &Q_Forge->Forge[AIcounter].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].ScanVecTo);
		Q_Forge->Forge[AIcounter].ScanAvatarDist = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].ScanVecTo);
		ScanAvatarDist = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].ScanVecTo);

		TempVec2 = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
		TempVec2.y += 64;
		Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].ScanVecTo,  &TempVec1);
		TempVec1.y += 64;

		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].ScanVecTo);

		//## Get Avatar In Vec
		Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.In);
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].AV.In);

		//## Get Transform Matrix From Avatar's Head
		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 HEAD", &HeadMatrix);
		HeadMatrix.Translation.y += 2.85;
		TempVec2 = HeadMatrix.Translation;
		Qpo->Transform_GetIn(&HeadMatrix, &HeadIn);

		//## Draw HEAD IN Vector
		Qpo->Vec3d_Scale(&HeadIn, 200, &HeadIn);

		//### Calculate Extremity Vectors
		//## Scan Left
		UseMatrix = HeadMatrix;
		Qpo->Transform_New_ZRotation(&RotMat, -(PI/2.5));
		Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
		Qpo->Transform_GetIn(&UseMatrix, &ScanLeft);
		Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanLeft, &ScanLeft);

		//### Scan Right
		UseMatrix = HeadMatrix;
		Qpo->Transform_New_ZRotation(&RotMat, (PI/2.5));
		Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
		Qpo->Transform_GetIn(&UseMatrix, &ScanRight);
		Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanRight, &ScanRight);

		//### Scan Up
		UseMatrix = HeadMatrix;
		Qpo->Transform_New_XRotation(&RotMat, (PI/4));	//9
		Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
		Qpo->Transform_GetIn(&UseMatrix, &ScanUp);
		Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanUp, &ScanUp); 

		//### Scan Down
		UseMatrix = HeadMatrix;
		Qpo->Transform_New(&RotMat);
		Qpo->Transform_New_XRotation(&RotMat, -(PI/5));
		Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
		Qpo->Transform_GetIn(&UseMatrix, &ScanDown);
		Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanDown, &ScanDown);

		//### Build The Scaled Vector To the Enemy
		Qpo->Vec3d_AddScaled(&TempVec2, 200, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanScaledVecTo);

		//### Calculate If the VectorTo Is Within the Vision Range Using Distance Checks
		DistLeft = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanLeft);
		DistRight = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanRight);
		DistUp = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanUp);
		DistDown = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanDown);

		//May not need this, do tests?
		DistFront = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);
		Tempfloat = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);

		Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].AV.In, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanTurnVec);
		Q_Forge->Forge[AIcounter].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
		Q_Forge->Forge[AIcounter].ScanTurnAng /= 2;

		//### Check Distance between Pure Left and Right to work out direction of Turn
		Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);

		Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Right);
		Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Right);

		ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Left);
		ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Right);

		if(ScanDistL < ScanDistR) Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;

		// Avatar is to the Left of the AIs view

		// Set begin 0
		TargetFound = 0;

#ifndef SUPER_SNEAKY
		// If player's very close auto lock on
		if(ScanAvatarDist < 280.0f)
			{
			TargetFound = 1;
			}
		else
		{
#endif

		if(( ( DistLeft < 380.422 && DistRight < 380.422 ) && ( DistUp < 214.919 && DistDown < 214.919 )) )
			{
			qEyes = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			qEyes.y += 80;
			Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
			Qpo->Vec3d_AddScaled(&qEyes, 5, &Q_Forge->Forge[AIcounter].AV.Up, &qEyes);

			qEnemy = playerAV[f_Player]->Xform.Translation;
			qEnemy.y += 45;

				//## Get Target Up Vector
			Qpo->Transform_GetIn(&playerAV[f_Player]->Xform, &playerAV[f_Player]->Up);
			Qpo->Vec3d_CrossProduct(&playerAV[f_Player]->Up, &Q_Forge->Forge[AIcounter].ScanVecTo, &LeftToRightESCAN);

			Qpo->Vec3d_AddScaled(&qEnemy, 13, &LeftToRightESCAN, &qEnemyLeft);
			Qpo->Vec3d_AddScaled(&qEnemy, -13, &LeftToRightESCAN, &qEnemyRight);
			Qpo->Vec3d_AddScaled(&qEnemy, 36, &playerAV[f_Player]->Up, &qEnemyUp);
			Qpo->Vec3d_AddScaled(&qEnemy, -36, &playerAV[f_Player]->Up, &qEnemyDown);

#ifdef AVATAR_VIEW_RANGE_ON
			if(ScanAvatarDist <= AVATAR_VIEW_RANGE)
				{
#endif
				if(player[f_Player]->Invisible == 0)
					{
#if 0
					if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyLeft,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
						{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == 250) TargetFound = 1; }
					if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyRight,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
						{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == 250) TargetFound = 1; }
					if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyUp,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
						{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == 250) TargetFound = 1; }
					if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyDown,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
						{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == 250) TargetFound = 1; }
#endif

#if 1
					if(!Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyLeft,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
						{ TargetFound = 1; }
					if(!Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyRight,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
						{ TargetFound = 1; }
					if(!Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyUp,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
						{ TargetFound = 1; }
					if(!Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyDown,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
						{ TargetFound = 1; }
#endif
					}

#ifdef AVATAR_VIEW_RANGE_ON
				}
#endif
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)	//Player Is Behind Geometry
				{
				if(DistLeft > 190.2) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 1;
				else if(DistRight > 190.2) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 2;
				if(DistUp > 107.5) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 1;
				if(DistDown > 107.5) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 2;

				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 1;
				Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
				}
			}

#ifndef SUPER_SNEAKY
		}
#endif

		if(TargetFound == 1)	// Player Avatar Is Fully Visible
			{
			Targets = true;

			//###### Create or Add to Target Sighting Memory
			//Check for Attack Lock
			if(Q_Forge->Forge[AIcounter].Q_Brain.MeMLock == 1) Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID;
			else Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.MeMcount;

			//TimeStamp
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Time = TIME;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].EventType = EVENT_AVATAR_SIGHTED;

			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Visible = 1;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].AV_ID = 250;	//Player ID
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Team = player[f_Player]->Team;		//Player Team
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Rank = 0;		//Player Rank Is Highest at Start

			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Pos = playerAV[f_Player]->Xform.Translation;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Pos.y += 65;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Ang = playerAV[f_Player]->Ang;
				
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].VecTo = ScanVecTo;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanTurnAng = Q_Forge->Forge[AIcounter].ScanTurnAng;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanDist = ScanAvatarDist;

			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Aposestate = player[f_Player]->Aposestate;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Mposestate = player[f_Player]->Mposestate;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].attposecnt = player[f_Player]->attposecnt;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].attackon = player[f_Player]->attackon;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].WeaponStatus = player[f_Player]->WeaponStatus;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Blocking = player[f_Player]->Blocking;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Health = player[f_Player]->HB_Health;
			//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].HitReaction = player[f_Player]->HitReaction;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].BlowHeight = player[f_Player]->BlowHeight;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].HitLethal = player[f_Player]->HitLethal;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].BlockHit = player[f_Player]->BlockHit;


			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMMindstate = Q_Forge->Forge[AIcounter].Q_Brain.MindState;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Pos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Angles = Q_Forge->Forge[AIcounter].Angles;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Health = Q_Forge->Forge[AIcounter].HB_Health;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Power = Q_Forge->Forge[AIcounter].HB_Energy;
			
			//Avatar Currently Being Scanned Is The Currently Locked in Target
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)
				{
				TargetLockVisible = 1;
				TargetDist = ScanAvatarDist;
				TargetLockAIPID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
				}

			/*Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 1;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = 250;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 1;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;
			Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
			TargetLockVisible = 1;
			TargetDist = ScanAvatarDist;
			TargetLockAIPID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent;*/

			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent++;
			}
		else					// Player Avatar Is Not in Sight
			{
			if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)	//Player Is Behind Geometry
				{
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 2;	
				Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
				}
			}
		}
		
	//###### Loop To See How Many Avatars Are In View ######
	aero = 0;
	while(aero < _->NomAI)
		{
		if(Q_Forge->Forge[aero].LIVE == 1)
			{
			//## Find Vector to AI Avatar
			Qpo->Vec3d_Subtract(&Q_Forge->Forge[aero].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].ScanVecTo);
			Q_Forge->Forge[AIcounter].ScanAvatarDist = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].ScanVecTo);
			ScanAvatarDist = Qpo->Vec3d_Length(&Q_Forge->Forge[AIcounter].ScanVecTo);

			TempVec2 = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
			TempVec2.y += 64;
			Qpo->Vec3d_Add(&Q_Forge->Forge[AIcounter].AV.Xform.Translation, &Q_Forge->Forge[AIcounter].ScanVecTo,  &TempVec1);
			TempVec1.y += 64;

			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].ScanVecTo);

			//## Get Avatar In Vec
			Qpo->Transform_AvatarGetIn(/*ORIG GetLeft*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.In);
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].AV.In);

			//## Get Transform Matrix From Avatar's Head
			Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 HEAD", &HeadMatrix);
			HeadMatrix.Translation.y += 2.85;
			TempVec2 = HeadMatrix.Translation;
			Qpo->Transform_GetIn(&HeadMatrix, &HeadIn);

			//## Draw HEAD IN Vector
			Qpo->Vec3d_Scale(&HeadIn, 200, &HeadIn);

			//### Calculate Extremity Vectors
			//## Scan Left
			UseMatrix = HeadMatrix;
			Qpo->Transform_New_ZRotation(&RotMat, -(PI/2.5));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetIn(&UseMatrix, &ScanLeft);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanLeft, &ScanLeft);

			//### Scan Right
			UseMatrix = HeadMatrix;
			Qpo->Transform_New_ZRotation(&RotMat, (PI/2.5));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetIn(&UseMatrix, &ScanRight);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanRight, &ScanRight);

			//### Scan Up
			UseMatrix = HeadMatrix;
			Qpo->Transform_New_XRotation(&RotMat, (PI/4));	//9
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetIn(&UseMatrix, &ScanUp);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanUp, &ScanUp); 

			//### Scan Down
			UseMatrix = HeadMatrix;
			Qpo->Transform_New(&RotMat);
			Qpo->Transform_New_XRotation(&RotMat, -(PI/5));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetIn(&UseMatrix, &ScanDown);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanDown, &ScanDown);

			//## Build The Scaled Vector To the Enemy
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanScaledVecTo);

			//### Calculate If the VectorTo Is Within the Vision Range Using Distance Checks
			DistLeft = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanLeft);
			DistRight = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanRight);
			DistUp = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanUp);
			DistDown = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanDown);

			//May not need this, do tests?
			DistFront = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);
			Tempfloat = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].AV.In, &Q_Forge->Forge[AIcounter].ScanVecTo, &ScanTurnVec);
			Q_Forge->Forge[AIcounter].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
			Q_Forge->Forge[AIcounter].ScanTurnAng /= 2;

			//### Check Distance between Pure Left and Right to work out direction of Turn
			Qpo->Transform_AvatarGetLeft(/*ORIG GetUp*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Left);

			Qpo->Vec3d_Copy(&Q_Forge->Forge[AIcounter].AV.Left, &Q_Forge->Forge[AIcounter].AV.Right);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AIcounter].AV.Right);

			ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Left);
			ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AIcounter].ScanVecTo, &Q_Forge->Forge[AIcounter].AV.Right);
						//<
			if(ScanDistL < ScanDistR) Q_Forge->Forge[AIcounter].ScanTurnAng *= -1;

				//Then Avatar is to the Left of the AIs view
			TargetFound = 0;

#ifndef SUPER_SNEAKY
				//if avatars's very close auto lock on
			if(ScanAvatarDist < 150.0f)
				{
				TargetFound = 1;
				}
			else
			{
#endif

			if( (( DistLeft < 380.422 && DistRight < 380.422 ) && ( DistUp < 214.919 && DistDown < 214.919 )) )
				{
				qEyes = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				qEyes.y += 80;

				Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[AIcounter].AV.Xform, &Q_Forge->Forge[AIcounter].AV.Up);
				Qpo->Vec3d_AddScaled(&qEyes, 5, &Q_Forge->Forge[AIcounter].AV.Up, &qEyes);

				qEnemy = Q_Forge->Forge[aero].AV.Xform.Translation;
				qEnemy.y += 45;

					//## Get Target Up Vector
				Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[aero].AV.Xform, &Q_Forge->Forge[aero].AV.Up);
				Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[aero].AV.Up, &Q_Forge->Forge[AIcounter].ScanVecTo, &LeftToRightESCAN);

				Qpo->Vec3d_AddScaled(&qEnemy, 13, &LeftToRightESCAN, &qEnemyLeft);
				Qpo->Vec3d_AddScaled(&qEnemy, -13, &LeftToRightESCAN, &qEnemyRight);
				Qpo->Vec3d_AddScaled(&qEnemy, 36, &Q_Forge->Forge[aero].AV.Up, &qEnemyUp);
				Qpo->Vec3d_AddScaled(&qEnemy, -36, &Q_Forge->Forge[aero].AV.Up, &qEnemyDown);

#ifdef AVATAR_VIEW_RANGE_ON
				if(ScanAvatarDist <= AVATAR_VIEW_RANGE)
					{
#endif
					if(Q_Forge->Forge[aero].HB_Health > 0)
						{
#if 0
						if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyLeft,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
							{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
						if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyRight,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
							{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
						if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyUp,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
							{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
						if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyDown,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
							{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
#endif

#if 1

						if(Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyLeft,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL) == false)
							{ TargetFound = 1; }
						else if(Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyRight,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL) == false)
							{ TargetFound = 1; }
						else if(Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyUp,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL) == false)
							{ TargetFound = 1; }
						else if(Qpo->Collision_RayTest(NULL, NULL, &qEyes, &qEnemyDown,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL) == false)
							{ TargetFound = 1; }
#endif
						}

#ifdef AVATAR_VIEW_RANGE_ON
					}
#endif
				}
			else
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && aero == Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID)	//Avatar Currently Being Scanned Is Behind Geometry
					{
					if(DistLeft > 190.2) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 1;
					else if(DistRight > 190.2) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr = 2;
					if(DistUp > 107.5) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 1;
					if(DistDown > 107.5) Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd = 2;

					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 1;	//Target Moved Out of Vision Range
					Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
					}
				}

#ifndef SUPER_SNEAKY
			}
#endif

			if((TargetFound == 1) && (Q_Forge->Forge[aero].HB_Health > 0))	// AI Avatar Is Fully Visible
				{
				Targets = true;

				//###### Create or Add to Target Sighting Memo
				//Check for Attack Lock
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMLock == 1) Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID;
				else Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.MeMcount;

				//TimeStamp
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Time = TIME;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].EventType = EVENT_AVATAR_SIGHTED;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Visible = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].AV_ID = aero;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Team = Q_Forge->Forge[aero].Team;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Rank = 1;//Q_Forge->Forge[aero].Rank;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Pos = Q_Forge->Forge[aero].AV.Xform.Translation;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Pos.y += 65;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Ang = Q_Forge->Forge[aero].AV.Ang;
					
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].VecTo = ScanVecTo;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanTurnAng = Q_Forge->Forge[AIcounter].ScanTurnAng;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].ScanDist = ScanAvatarDist;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Aposestate = Q_Forge->Forge[aero].Aposestate;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Mposestate = Q_Forge->Forge[aero].Mposestate;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].attposecnt = Q_Forge->Forge[aero].attposecnt;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].attackon = Q_Forge->Forge[aero].attackon;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].WeaponStatus = Q_Forge->Forge[aero].WeaponStatus;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Blocking = Q_Forge->Forge[aero].Blocking;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].Health = Q_Forge->Forge[aero].HB_Health;
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].HitReaction = Q_Forge->Forge[aero].HitReaction;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].HitLethal = Q_Forge->Forge[aero].HitLethal;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent].BlockHit = Q_Forge->Forge[aero].BlockHit;

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMMindstate = Q_Forge->Forge[AIcounter].Q_Brain.MindState;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].TargetLOCKID = Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Pos = Q_Forge->Forge[AIcounter].AV.Xform.Translation;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Angles = Q_Forge->Forge[AIcounter].Angles;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Health = Q_Forge->Forge[AIcounter].HB_Health;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].Power = Q_Forge->Forge[AIcounter].HB_Energy;
					
				//##### Avatar Currently Being Scanned Is The Currently Locked in Target
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && aero == Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID)
					{
					TargetLockVisible = 1;
					TargetDist = ScanAvatarDist;
					TargetLockAIPID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent;
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
					}

				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent++;
				}
			else	// Avatar Currently Being Scanned Is Not in Sight
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && aero == Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID)	//Avatar Currently Being Scanned Is Behind Geometry
					{
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 2;
					Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
					}
				}
			}

		aero++;
		}


	if(Targets == true)	//##### Having determined targets are present: move to lock a target #####
		{
		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1)	//######-- CONDITIONAL TARGET LOCK BREAK --######
			{
			helly = 0;	//#####-- Verify Team Status to get Possible Targets 'ENEMY' and 'FRIENDY' --#####
			while(helly < Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent)
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].Team != Q_Forge->Forge[AIcounter].Team)
					{
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].AV_ID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].AV_ID;
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].Distance = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].ScanDist;
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].AIPID = helly;
					Q_Forge->Forge[AIcounter].NomTargetsPresent++;
					}
				else
					{
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].AV_ID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].AV_ID;
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].Rank = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].Rank;
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].AIPID = helly;
					Q_Forge->Forge[AIcounter].NomFriendlyPresent++;
					}

				helly++;
				}

			//#####-- Offensive 'Target Selection' Based On Certain Conditions --#####
			//### First Condition 'Distance'
			helly = 0;
			while(helly < Q_Forge->Forge[AIcounter].NomTargetsPresent)
				{
				if(helly == 0)
					{
					_->LockInTargetData.Closest = Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance;
					_->LockInTargetData.ClosestID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AV_ID;
					_->LockInTargetData.ClosestAIPID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AIPID;
					}
				else
					{
					if(Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance < _->LockInTargetData.Closest)
						{
						_->LockInTargetData.Closest = Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance;
						_->LockInTargetData.ClosestID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AV_ID;
						_->LockInTargetData.ClosestAIPID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AIPID;
						}
					}
				helly++;
				}

			//### If There is a Better Target To Change To then Switch	   // \/----EDIT - Value originally 500
			if((_->LockInTargetData.Closest < (TargetDist / 2)) && (TargetDist > 65) && Q_Forge->Forge[AIcounter].NomTargetsPresent > 0)
				{
				//###-- Target Much Closer Then Previous so  #LOCK IN TARGET#----###
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID = _->LockInTargetData.ClosestAIPID;
				Q_Forge->Forge[AIcounter].ScanTurnAng = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[_->LockInTargetData.ClosestAIPID].ScanTurnAng;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = _->LockInTargetData.ClosestID;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
				TargetLockVisible = 1;

				//Q_Forge->Forge[AIcounter].Q_Brain.MeMcount++;	//Increment Memory Bank
				}
			else
				{
				if(TargetLockVisible == 1 || Q_Forge->Forge[AIcounter].QformON == 1)	//###-- Avatar Currently Locked In Is Visible --###
					{
					Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;

					if(TargetLockAIPID < Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent)
						{
						if(TargetLockVisible == 1) Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 1;
						
						Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 1;
						Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;
						
						if(Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent < 100 &&
						   TargetLockAIPID < 255 &&
						   TargetLockVisible == 1)
							{
							Q_Forge->Forge[AIcounter].ScanTurnAng = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[TargetLockAIPID].ScanTurnAng;
							Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[TargetLockAIPID].AV_ID;
							Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID = TargetLockAIPID;
							Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
							}

						//Sprocket Purge
						//Q_Forge->Forge[AIcounter].Q_Brain.MeMcount++;	//Increment Memory Bank
						}
					}
				}
			}
		else	//##### No Previous Target so Initiate 'CONDITIONAL TARGET SELECTION' #####
			{
			helly = 0;		//### Verify Team Status to get Possible Targets
			while(helly < Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].NomAIPresent)
				{
				if(Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].Team != Q_Forge->Forge[AIcounter].Team)
					{
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].AV_ID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].AV_ID;
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].Distance = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].ScanDist;
					Q_Forge->Forge[AIcounter].TargetsPresent[Q_Forge->Forge[AIcounter].NomTargetsPresent].AIPID = helly;
					Q_Forge->Forge[AIcounter].NomTargetsPresent++;
					}
				else
					{
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].AV_ID = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].AV_ID;
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].Rank = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[helly].Rank;
					Q_Forge->Forge[AIcounter].FriendlyPresent[Q_Forge->Forge[AIcounter].NomFriendlyPresent].AIPID = helly;
					Q_Forge->Forge[AIcounter].NomFriendlyPresent++;
					}
				helly++;
				}


			//## First Condition 'Distance'
			helly = 0;
			while(helly < Q_Forge->Forge[AIcounter].NomTargetsPresent)
				{
				if(helly == 0)	//<--First Run
					{
					_->LockInTargetData.Closest = Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance;
					_->LockInTargetData.ClosestID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AV_ID;
					_->LockInTargetData.ClosestAIPID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AIPID;
					}
				else
					{
					if(Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance < _->LockInTargetData.Closest)
						{
						_->LockInTargetData.Closest = Q_Forge->Forge[AIcounter].TargetsPresent[helly].Distance;
						_->LockInTargetData.ClosestID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AV_ID;
						_->LockInTargetData.ClosestAIPID = Q_Forge->Forge[AIcounter].TargetsPresent[helly].AIPID;
						}
					}
				helly++;
				}

			
			if(Q_Forge->Forge[AIcounter].NomTargetsPresent > 0)	//###-- Decision Made Select Target --###
				{
				Q_Forge->Forge[AIcounter].ScanTurnAng = Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].AIsPresent[_->LockInTargetData.ClosestAIPID].ScanTurnAng;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockID = _->LockInTargetData.ClosestAIPID;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID = _->LockInTargetData.ClosestID;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST = 0;
				Q_Forge->Forge[AIcounter].Q_Brain.MeMLock = 1;
				Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID = Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent;
				TargetLockVisible = 1;
				
				//Q_Forge->Forge[AIcounter].Q_Brain.MeMcount++; //<--Increment Memory Bank
				}
			}


			//##### Determine the Friendly Leader #####

		if(Q_Forge->Forge[AIcounter].NomFriendlyPresent > 0)
			{
			//### First Condition 'Rank'
			helly = 0;
			while(helly < Q_Forge->Forge[AIcounter].NomFriendlyPresent)
				{
				if(helly == 0)
					{
					_->LockInLeaderData.Closest = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].Rank;
					_->LockInLeaderData.ClosestID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AV_ID;
					_->LockInLeaderData.ClosestAIPID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AIPID;
					}
				else
					{
					if(Q_Forge->Forge[AIcounter].FriendlyPresent[helly].Rank < _->LockInLeaderData.Closest)
						{
						_->LockInLeaderData.Closest = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].Rank;
						_->LockInLeaderData.ClosestID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AV_ID;
						_->LockInLeaderData.ClosestAIPID = Q_Forge->Forge[AIcounter].FriendlyPresent[helly].AIPID;
						}
					}
				helly++;
				}

				//Lock In Friendly Leader
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].MeMLockLeaderID = _->LockInLeaderData.ClosestAIPID;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER = 1;
			}
		else Q_Forge->Forge[AIcounter].Q_Brain.TargetLEADER = 0;
		}

#if 0
	if(Q_Forge->Forge[AIcounter].NomTargetsPresent <= 0)
		{
		Q_Forge->Forge[AIcounter].ScanTurnAng = 0;
		Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 0;
		TargetLockVisible = 0;
		}
#endif

	if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && TargetLockVisible == 0)
		{
		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND == 0)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].TargetLOST = Q_Forge->Forge[AIcounter].Q_Brain.TargetLOST;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].TargetWENTltr = Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTltr;
			Q_Forge->Forge[AIcounter].Q_Brain.MeMBank[Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent].TargetWENTutd = Q_Forge->Forge[AIcounter].Q_Brain.TargetWENTutd;
			}

		Q_Forge->Forge[AIcounter].Q_Brain.MeMcurrent = Q_Forge->Forge[AIcounter].Q_Brain.ATTMmemID;
		Q_Forge->Forge[AIcounter].Q_Brain.TargetFIND = 1;
		Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 0;

		if(!Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcountON)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcountON = true;
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLOSTcounter = 0;
			}
		}
	else
		{
		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 1 && TargetLockVisible == 1)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.TargetSIGHT = 1;
			}
		}

	//////// No Targets /////////
	if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCK == 0)
		{
		if(Q_Forge->Forge[AIcounter].StrPosCounter > 50)
			{
			Q_Forge->Forge[AIcounter].Q_Brain.TargetLightLOST = 1;
			Q_Forge->Forge[AIcounter].StrPosCounter = 0;
			}
		}

	return Targets;
}

};