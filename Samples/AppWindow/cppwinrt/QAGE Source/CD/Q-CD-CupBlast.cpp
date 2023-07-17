/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Collision Detection-
	*/#include "pch.h"/*- Minor Component -Cup Blast -

*/


//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include <stdlib.h>

#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-CORE-Avatar.h"

using namespace GVARS;

namespace GVARS
{

	//##### CUP BLAST #####

void Q_COREFunctions::COLDET_CupBlast(QpoTransform Limb, float DamageScale)
{
	QpoVec3d	ScanLeft,ScanRight,ScanUp,ScanDown;
	QpoVec3d ScanScaledVecTo;
	QpoVec3d HeadIn;
	QpoTransform HeadMatrix,UseMatrix,RotMat;
	float DistLeft,DistRight,DistUp,DistDown,DistFront;
	QpoVec3d	EnemyLeft,EnemyRight,EnemyUp,EnemyDown,Enemy,Eyes;
	QpoVec3d	LeftToRightESCAN;
	int	TargetFound;
	int TargetLockVisible;
	int	TargetLockAIPID;
	int TargetDist;
	bool Targets;
	QpoCollision RayTraceCOLL;
	

	//TODO Add here loop to see how many people around

	//###### Loop To See How Many Avatars Are In View ######

	aero = 0;
	while(aero < _->NomAI)
		{
		if(Q_Forge->Forge[aero].LIVE == 1)
			{
			//## Find Vector to AI Avatar
			TempVec2 = Q_Forge->Forge[aero].AV.Xform.Translation;
			TempVec2.y += 45;
			Qpo->Vec3d_Subtract(&TempVec2, &Limb.Translation, &player[g_Player]->ScanVecTo);
			player[g_Player]->ScanAvatarDist = Qpo->Vec3d_Length(&player[g_Player]->ScanVecTo);
			ScanAvatarDist = Qpo->Vec3d_Length(&player[g_Player]->ScanVecTo);
			TempVec2 = Limb.Translation;
			TempVec2.y += 80;
			Qpo->Vec3d_Add(&Limb.Translation, &player[g_Player]->ScanVecTo,  &TempVec1);
			TempVec1.y += 80;

			Qpo->Vec3d_Normalize(&player[g_Player]->ScanVecTo);


			//## Get Transform Matrix From Avatar's Head
			HeadMatrix = Limb;
			TempVec2 = HeadMatrix.Translation;

			Qpo->Transform_GetUp(&HeadMatrix, &HeadIn);
			Qpo->Vec3d_Copy(&HeadMatrix.Translation, &Origin);
			
			//## Draw HEAD IN Vector
			//Qpo->Vec3d_AddScaled(&TempVec2, 200, &HeadIn, &HeadIn);
			//Q.ShowLine(&TempVec2, &HeadIn, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 0, 255, 0, 1);

			//### Calculate Extremity Vectors
			//## Scan Left
			UseMatrix = HeadMatrix;
			Qpo->Transform_New(&RotMat);
			Qpo->Transform_New_XRotation(&RotMat, (PI/2.5));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetUp(&UseMatrix, &ScanLeft);
			//Qpo->Vec3d_Inverse(&ScanLeft);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanLeft, &ScanLeft);
			//ssssQ.ShowLine(&TempVec2, &ScanLeft, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 255, 255, 0, 1);

			//## Scan Right
			UseMatrix = HeadMatrix;
			Qpo->Transform_New(&RotMat);
			Qpo->Transform_New_XRotation(&RotMat, -(PI/2.5));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetUp(&UseMatrix, &ScanRight);
			//Qpo->Vec3d_Inverse(&ScanRight);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanRight, &ScanRight);
			//Q.ShowLine(&TempVec2, &ScanRight, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 255, 255, 0, 1);

			//## Scan Up
			UseMatrix = HeadMatrix;
			Qpo->Transform_New(&RotMat);
			Qpo->Transform_New_ZRotation(&RotMat, -(PI/5));	//9
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetUp(&UseMatrix, &ScanUp);
			//Qpo->Vec3d_Inverse(&ScanUp);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanUp, &ScanUp);
			//Q.ShowLine(&TempVec2, &ScanUp, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 255, 255, 0, 1);

			//## Scan Down
			UseMatrix = HeadMatrix;
			Qpo->Transform_New(&RotMat);
			Qpo->Transform_New_ZRotation(&RotMat, (PI/4));
			Qpo->Transform_Multiply(&UseMatrix, &RotMat, &UseMatrix);
			Qpo->Transform_GetUp(&UseMatrix, &ScanDown);
			//Qpo->Vec3d_Inverse(&ScanDown);
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &ScanDown, &ScanDown);
			//Q.ShowLine(&TempVec2, &ScanDown, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 255, 255, 0, 1);


			//## Build The Scaled Vector To the Enemy
			Qpo->Vec3d_AddScaled(&TempVec2, 200, &player[g_Player]->ScanVecTo, &ScanScaledVecTo);
			//Q.ShowLine(&TempVec2, &ScanScaledVecTo, &player[g_Player]->ViewXForm.Translation, 5, Medias->LaserSight, 255, 255, 0, 0, 1);


			//### Calculate If the VectorTo Is Within the Vision Range Using Distance Checks
			DistLeft = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanLeft);
			DistRight = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanRight);
			DistUp = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanUp);
			DistDown = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanDown);

			//May not need this, do tests?
			//DistFront = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);
			//Tempfloat = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);

			//Sleep(10000);


			if(( DistLeft < 380.422 && DistRight < 380.422 ) && ( DistUp < 214.919 && DistDown < 214.919 ))
				{
				Eyes = Limb.Translation;

				Enemy = Q_Forge->Forge[aero].AV.Xform.Translation;
				Enemy.y += 45;

					//## Get Target Up Vector
				Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[aero].AV.Xform, &Q_Forge->Forge[aero].AV.Up);
				Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[aero].AV.Up, &player[g_Player]->ScanVecTo, &LeftToRightESCAN);

				Qpo->Vec3d_AddScaled(&Enemy, 13, &LeftToRightESCAN, &EnemyLeft);
				Qpo->Vec3d_AddScaled(&Enemy, -13, &LeftToRightESCAN, &EnemyRight);
				Qpo->Vec3d_AddScaled(&Enemy, 36, &Q_Forge->Forge[aero].AV.Up, &EnemyUp);
				Qpo->Vec3d_AddScaled(&Enemy, -36, &Q_Forge->Forge[aero].AV.Up, &EnemyDown);

				TargetFound = 1;

				if(Qpo->Collision_RayTest(NULL, NULL, &Eyes, &EnemyLeft, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
					{ if(RayTraceCOLL.Avatar != 0) /*if(RayTraceCOLL.Avatar.IDflag == aero)*/ TargetFound = 1; }
				if(Qpo->Collision_RayTest(NULL, NULL, &Eyes, &EnemyRight, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
					{ if(RayTraceCOLL.Avatar != 0) /*if(RayTraceCOLL.Avatar.IDflag == aero)*/ TargetFound = 1; }
				if(Qpo->Collision_RayTest(NULL, NULL, &Eyes, &EnemyUp, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
					{ if(RayTraceCOLL.Avatar != 0) /*if(RayTraceCOLL.Avatar.IDflag == aero)*/ TargetFound = 1; }
				if(Qpo->Collision_RayTest(NULL, NULL, &Eyes, &EnemyDown, /* GE_CONTENTS_CANNOT_OCCUPY GE_COLLIDE_MODELS, */ 0xffffffff, NULL, NULL, &RayTraceCOLL))
					{ if(RayTraceCOLL.Avatar != 0) /*if(RayTraceCOLL.Avatar.IDflag == aero)*/ TargetFound = 1; }


				//If Target Is inside Cup and Visible Deal Damage
				Qpo->Vec3d_Normalize(&HeadIn);
				//Q.RadialDamage(0, DamageScale, Limb.Translation, 1, HeadIn);
				if(TargetFound == 1) Q.RadialDamage(0, 250, DamageScale, DamageScale, Limb.Translation, 1, HeadIn);
				}
			}
		aero++;
		}
	}

};