/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	*/#include "pch.h"/*- Minor Component -Player Muzzle Flash-

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

extern float WeaponvalueX;
extern float WeaponvalueY;
extern float WeaponvalueZ;
extern float WeaponvalueW;
extern float WeaponvalueshtX;
extern float WeaponvalueshtY;
extern float WeaponvalueshtZ;

using namespace GVARS;

namespace GVARS
{

//#####- MUZZLE FLASH -#####
void Q_COREFunctions::CONTROL_PlayerMuzzleFlash(void)
	{
	if(Q_MFlash->MFlash[250].SkipFlag == 1)
		{
		Q_MFlash->MFlash[250].SkipFlag = 0;
		Qpo->Light_Remove(Q_MFlash->MFlash[250].Light);
		}

	if(Q_MFlash->MFlash[250].JDamageLVL > 0)
		{
		Q_MFlash->MFlash[250].JDamageLVL--;

		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &Q_MFlash->MFlash[250].AlignMatrix);

		Qpo->Avatar_GetWeaponTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &Q_MFlash->MFlash[250].AlignMatrix);

		//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_MFlash->MFlash[250].AlignMatrix.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//'FIRE' SOUND
		Qpo->Sound_Play(Medias->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &Q_MFlash->MFlash[250].AlignMatrix.Translation);
		}

	if(player[g_Player]->MFlash > 0 && Q_MFlash->MFlash[250].SkipFlag == 0)
		{
		//INIT
		Q_MFlash->MFlash[250].SkipFlag = 1;

		if(player[g_Player]->MFlash == 2) Q_MFlash->MFlash[250].JDamageLVL = 1;
		if(player[g_Player]->MFlash == 3) Q_MFlash->MFlash[250].JDamageLVL = 2;
		if(player[g_Player]->MFlash == 4) Q_MFlash->MFlash[250].JDamageLVL = 3;

		//### Initialise one CARTRIDGE
							//V-- Maximum cartridge restriction
		if(_->NomCart >= 1450) _->NomCart = 0;
		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->TempXForm1);
		//Q_Cartridge->Cartridge[_->NomCart].WorldPos = player[g_Player]->TempXForm1.Translation;
		
		QpoVec3d f_vecIN, f_vecUP, f_vecLEFT, f_PosSTR;

		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			QpoVec3d ScanLeft,ScanRight,ScanUp,ScanDown;
			QpoVec3d ScanScaledVecTo;
			QpoVec3d HeadIn;
			QpoTransform HeadMatrix,UseMatrix,RotMat;
			float DistLeft,DistRight,DistUp,DistDown,DistFront;
			QpoVec3d LeftToRightESCAN;
			int	TargetFound;
			int TargetLockVisible;
			int	TargetLockAIPID;
			int TargetDist;
			bool Targets;
			QpoCollision RayTraceCOLL;

			player[g_Player]->NomTargetsPresent = 0;

			//###### Loop To See How Many Avatars Are In View ######

			aero = 0;
			while(aero < _->NomAI)
				{
				if(Q_Forge->Forge[aero].LIVE == 1 && Q_Forge->Forge[aero].HB_Health > 0)
					{
					//## Find Vector to AI Avatar
					Qpo->Vec3d_Subtract(&Q_Forge->Forge[aero].AV.Xform.Translation, &playerAV[g_Player]->Xform.Translation, &player[g_Player]->ScanVecTo);
					player[g_Player]->ScanAvatarDist = Qpo->Vec3d_Length(&player[g_Player]->ScanVecTo);
					ScanAvatarDist = Qpo->Vec3d_Length(&player[g_Player]->ScanVecTo);

					TempVec2 = playerAV[g_Player]->Xform.Translation;
					TempVec2.y += 64;
					Qpo->Vec3d_Add(&playerAV[g_Player]->Xform.Translation, &player[g_Player]->ScanVecTo,  &TempVec1);
					TempVec1.y += 64;

					Qpo->Vec3d_Normalize(&player[g_Player]->ScanVecTo);

					//## Get Avatar In Vec
					Qpo->Transform_AvatarGetIn(&playerAV[g_Player]->Xform, /*ORIG GetLeft*/ &playerAV[g_Player]->Up);
					Qpo->Vec3d_Normalize(&playerAV[g_Player]->Up);

					//## Get Transform Matrix From Avatar's Head
					Qpo->Avatar_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 HEAD", &HeadMatrix);
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
					Qpo->Vec3d_AddScaled(&TempVec2, 200, &player[g_Player]->ScanVecTo, &ScanScaledVecTo);

					//### Calculate If the VectorTo Is Within the Vision Range Using Distance Checks
					DistLeft = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanLeft);
					DistRight = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanRight);
					DistUp = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanUp);
					DistDown = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &ScanDown);

					//May not need this, do tests?
					DistFront = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);
					Tempfloat = Qpo->Vec3d_DistanceBetween(&ScanScaledVecTo, &HeadIn);

					Qpo->Vec3d_Subtract(&playerAV[g_Player]->Up, &player[g_Player]->ScanVecTo, &ScanTurnVec);
					player[g_Player]->ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
					player[g_Player]->ScanTurnAng /= 2;

					//### Check Distance between Pure Left and Right to work out direction of Turn
					Qpo->Transform_AvatarGetLeft(&playerAV[g_Player]->Xform, /*ORIG GetUp*/ &playerAV[g_Player]->Left);

					Qpo->Vec3d_Copy(&playerAV[g_Player]->Left, &playerAV[g_Player]->Right);
					Qpo->Vec3d_Inverse(&playerAV[g_Player]->Right);

					ScanDistL = Qpo->Vec3d_DistanceBetween(&player[g_Player]->ScanVecTo, &playerAV[g_Player]->Left);
					ScanDistR = Qpo->Vec3d_DistanceBetween(&player[g_Player]->ScanVecTo, &playerAV[g_Player]->Right);

					if(ScanDistL < ScanDistR) player[g_Player]->ScanTurnAng *= -1;
						//Then Avatar is to the Left of the AIs view

					TargetFound = 0;

					//if avatars's very close auto lock on
					if(ScanAvatarDist < 280)
						{ TargetFound = 1; }

					if( ( DistLeft < 380.422 && DistRight < 380.422 ) && ( DistUp < 214.919 && DistDown < 214.919 ) )
						{
						qEyes = playerAV[g_Player]->Xform.Translation;
						qEyes.y += 80;

						Qpo->Transform_AvatarGetUp(&playerAV[g_Player]->Xform, /*ORIG GetIn*/&playerAV[g_Player]->Up);
						Qpo->Vec3d_AddScaled(&qEyes, 5, &playerAV[g_Player]->Up, &qEyes);

						qEnemy = Q_Forge->Forge[aero].AV.Xform.Translation;
						qEnemy.y += 45;

							//## Get Target Up Vector
						Qpo->Transform_AvatarGetUp(/*ORIG GetIn*/&Q_Forge->Forge[aero].AV.Xform, &Q_Forge->Forge[aero].AV.Up);
						Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[aero].AV.Up, &player[g_Player]->ScanVecTo, &LeftToRightESCAN);

						Qpo->Vec3d_AddScaled(&qEnemy, 13, &LeftToRightESCAN, &qEnemyLeft);
						Qpo->Vec3d_AddScaled(&qEnemy, -13, &LeftToRightESCAN, &qEnemyRight);
						Qpo->Vec3d_AddScaled(&qEnemy, 36, &Q_Forge->Forge[aero].AV.Up, &qEnemyUp);
						Qpo->Vec3d_AddScaled(&qEnemy, -36, &Q_Forge->Forge[aero].AV.Up, &qEnemyDown);


#if 0
							if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyLeft,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
								{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
							if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyRight,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
								{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
							if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyUp,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
								{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
							if(Qpo->Collision_RayTest_Avatar(NULL, NULL, &Eyes, &EnemyDown,/* Contents cannot occupy / Models / Actors */ 0xffffffff, NULL, NULL, &RayTraceCOLL, AIcounter))
								{ if(RayTraceCOLL.Avatar != 0) if(RayTraceCOLL.Avatar.IDflag == aero) TargetFound = 1; }
#else
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

					if(Q_Forge->Forge[aero].Team != player[g_Player]->Team)
						{
						player[g_Player]->TargetsPresent[player[g_Player]->NomTargetsPresent].AV_ID = aero;
						player[g_Player]->TargetsPresent[player[g_Player]->NomTargetsPresent].Distance = ScanAvatarDist;
						player[g_Player]->TargetsPresent[player[g_Player]->NomTargetsPresent].ScanVecTo = player[g_Player]->ScanVecTo;
						player[g_Player]->TargetsPresent[player[g_Player]->NomTargetsPresent].AIPID = player[g_Player]->NomTargetsPresent;
						player[g_Player]->NomTargetsPresent++;
						}
					}

				aero++;
				}

			//#####-- Offensive 'Target Selection' Based On Certain Conditions --#####

			//### First Condition 'Distance'
			helly = 0;
			while(helly < player[g_Player]->NomTargetsPresent)
				{
				if(helly == 0)
					{
					_->LockInTargetData.Closest = player[g_Player]->TargetsPresent[helly].Distance;
					_->LockInTargetData.ClosestID = player[g_Player]->TargetsPresent[helly].AV_ID;
					_->LockInTargetData.ClosestAIPID = player[g_Player]->TargetsPresent[helly].AIPID;
					}
				else
					{
					if(player[g_Player]->TargetsPresent[helly].Distance < _->LockInTargetData.Closest)
						{
						_->LockInTargetData.Closest = player[g_Player]->TargetsPresent[helly].Distance;
						_->LockInTargetData.ClosestID = player[g_Player]->TargetsPresent[helly].AV_ID;
						_->LockInTargetData.ClosestAIPID = player[g_Player]->TargetsPresent[helly].AIPID;
						}
					}
				helly++;
				}

			Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPos, true);

			f_PosSTR = player[g_Player]->RFistPos.Translation;

			f_vecIN.x = player[g_Player]->TargetsPresent[_->LockInTargetData.ClosestAIPID].ScanVecTo.x;
			f_vecIN.y = player[g_Player]->TargetsPresent[_->LockInTargetData.ClosestAIPID].ScanVecTo.y;
			f_vecIN.z = player[g_Player]->TargetsPresent[_->LockInTargetData.ClosestAIPID].ScanVecTo.z;
			f_vecUP.x = 0;
			f_vecUP.y = 1;
			f_vecUP.z = 0;

			Qpo->Vec3d_CrossProduct(&f_vecIN, &f_vecUP, &f_vecLEFT);
			Qpo->Transform_New_LeftUpIn(&player[g_Player]->RFistPos, &f_vecLEFT, &f_vecUP, &f_vecIN);

			player[g_Player]->RFistPos.Translation = f_PosSTR;
			}
		else
			{
			playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

			Qpo->Avatar_GetWeaponTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPos);
			}

		Q_Cartridge->Cartridge[_->NomCart].WorldPos = player[g_Player]->RFistPos.Translation;

		//##### MiniGUN Rotation
		/*if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			if(KEY_PRESS_DOWN(QIN_KP4))
				{
				Ange.x = WeaponvalueshtX;//(PI/2);
				Ange.y = WeaponvalueshtY;//PI;
				Ange.z = WeaponvalueshtZ;//(PI/2);
				}
			else
				{
				Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
				Ange.y = -0.87; //WeaponvalueshtY;//PI;
				Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);
				}

			// Set the actor's angle
			Qpo->Transform_RotateY(&player[g_Player]->RFistPos, Ange.y);
			Qpo->Transform_RotateX(&player[g_Player]->RFistPos, Ange.x);
			Qpo->Transform_RotateZ(&player[g_Player]->RFistPos, Ange.z);
			//#####
			}*/

		player[g_Player]->TempXForm1.Matrix = player[g_Player]->RFistPos.Matrix;
		player[g_Player]->TempXForm1.Translation.x = player[g_Player]->RFistPos.Translation.x;
		player[g_Player]->TempXForm1.Translation.y = player[g_Player]->RFistPos.Translation.y;
		player[g_Player]->TempXForm1.Translation.z = player[g_Player]->RFistPos.Translation.z;

		/*//glLoadIdentity();

		//glMultMatrixf((float *)&g_render->camera.mat_t);
		//glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		//float valueX = -0.14;
		//float valueY = 10.05;
		//float valueZ = 2.55;

		if(player[g_Player]->AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);
		else Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);

		//glTranslatef(player[g_Player]->RFistPosV.Translation.x, player[g_Player]->RFistPosV.Translation.y, player[g_Player]->RFistPosV.Translation.z);
		//glMultMatrixf(player[g_Player]->RFistPosV.Matrix.mf);

		//glTranslatef(valueX, valueY, valueZ);

		//glScalef(player[g_Player]->Weapon.Scale.x, player[g_Player]->Weapon.Scale.y, player[g_Player]->Weapon.Scale.z);

		player[g_Player]->RFistPosV.Translation.x += valueX;
		player[g_Player]->RFistPosV.Translation.y += valueY;
		player[g_Player]->RFistPosV.Translation.z += valueZ;*/

		Qpo->Transform_GetIn(&player[g_Player]->RFistPos, &Q_Bullet->Bullet[_->NomBullet].VecIn);

		player[g_Player]->RFistPos = player[g_Player]->TempXForm1;
		player[g_Player]->RFistPos.Translation.x = player[g_Player]->TempXForm1.Translation.x;
		player[g_Player]->RFistPos.Translation.y = player[g_Player]->TempXForm1.Translation.y;
		player[g_Player]->RFistPos.Translation.z = player[g_Player]->TempXForm1.Translation.z;

		//Trajectory
		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->TempXForm1);
		player[g_Player]->TempXForm1.Matrix = player[g_Player]->RFistPos.Matrix;
		player[g_Player]->TempXForm1.Translation.x = player[g_Player]->RFistPos.Translation.x;
		player[g_Player]->TempXForm1.Translation.y = player[g_Player]->RFistPos.Translation.y;
		player[g_Player]->TempXForm1.Translation.z = player[g_Player]->RFistPos.Translation.z;
		Qpo->Transform_GetIn(&player[g_Player]->TempXForm1, &Q_Cartridge->Cartridge[_->NomCart].TrajVec);
		Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[_->NomCart].WorldPos, -5.6, &Q_Cartridge->Cartridge[_->NomCart].TrajVec, &Q_Cartridge->Cartridge[_->NomCart].WorldPos);

		Qpo->Transform_GetLeft(&player[g_Player]->TempXForm1, &Q_Cartridge->Cartridge[_->NomCart].TrajVec);
		Qpo->Vec3d_Inverse(&Q_Cartridge->Cartridge[_->NomCart].TrajVec);

		Q_Cartridge->Cartridge[_->NomCart].Scale = 0.5 * (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE+(0.16*(((((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height+player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight)/2)/100)-0.5)*2)));
		
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.x += (((float)rand() / 32767)/3);
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.z += (((float)rand() / 32767)/3);
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.y += 2.2;
		
		Q_Cartridge->Cartridge[_->NomCart].FloorBounce = 0;
		Q_Cartridge->Cartridge[_->NomCart].Gravity = 7.8;		//0.4

		//Qpo->Transform_New_YRotation(&rotmat, PI/2);
		//Qpo->Transform_Multiply(&player[g_Player]->TempXForm1, &rotmat, &player[g_Player]->TempXForm1);

		//Qpo->Transform_New_ZRotation(&rotmat, ((float)rand() / 32767)*6);
		//Qpo->Transform_Multiply(&player[g_Player]->TempXForm1, &rotmat, &player[g_Player]->TempXForm1);

		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)/13);
		//Qpo->Transform_Multiply(&player[g_Player]->TempXForm1, &rotmat, &player[g_Player]->TempXForm1);

		//Qpo->Transform_New_ZRotation(&rotmat, ((float)rand() / 32767)*2);
		//Qpo->Transform_Multiply(&player[g_Player]->TempXForm1, &rotmat, &player[g_Player]->TempXForm1);

		Q_Cartridge->Cartridge[_->NomCart].AlignMatrix = player[g_Player]->TempXForm1;

		Q_Cartridge->Cartridge[_->NomCart].XSpin = ((float)rand() / 32767)/6;
		Q_Cartridge->Cartridge[_->NomCart].YSpin = ((float)rand() / 32767)/6;
		Q_Cartridge->Cartridge[_->NomCart].ZSpin = ((float)rand() / 32767)/6;

		Q_Cartridge->Cartridge[_->NomCart].Speed = (((float)rand() / 32767)+1)*0.9;	//*2

		Q_Cartridge->Cartridge[_->NomCart].Live = 1;

		Q_Cartridge->Cartridge[_->NomCart].AvID = -1;

		_->NomCart++;
		if(_->NomCart >= 1500) _->NomCart = 0;


		//###### Initialise BULLET/S

		if(_->NetworkOption != 1 || 1)
			{
			SCRAM = 0;
			while((SCRAM < player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].BulletCNT) && (_->NomBullet < 14999))	//V-- Maximum bullet restriction
				{
				//Trajectory
				//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->TempXForm2);

				player[g_Player]->TempXForm2.Matrix = player[g_Player]->TempXForm1.Matrix;
				player[g_Player]->TempXForm2.Translation.x = player[g_Player]->TempXForm1.Translation.x;
				player[g_Player]->TempXForm2.Translation.y = player[g_Player]->TempXForm1.Translation.y;
				player[g_Player]->TempXForm2.Translation.z = player[g_Player]->TempXForm1.Translation.z;

				Qpo->Transform_GetIn(&player[g_Player]->TempXForm2, &Q_Bullet->Bullet[_->NomBullet].TrajVec);
				Qpo->Vec3d_Inverse(&Q_Bullet->Bullet[_->NomBullet].TrajVec);

				if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec = f_vecIN;
					}

				//Qpo->Vec3d_AddScaled(&player[g_Player]->TempXForm2.Translation, 55, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &player[g_Player]->TempXForm2.Translation);

				if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
					{
					Qpo->Vec3d_AddScaled(&player[g_Player]->TempXForm2.Translation, 200, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &player[g_Player]->TempXForm2.Translation);
					}
				else Qpo->Vec3d_AddScaled(&player[g_Player]->TempXForm2.Translation, 100, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &player[g_Player]->TempXForm2.Translation);

				Q_Bullet->Bullet[_->NomBullet].WorldPos = player[g_Player]->TempXForm2.Translation;
				Q_Bullet->Bullet[_->NomBullet].ORIGPos = player[g_Player]->TempXForm2.Translation;

				if(player[g_Player]->Soldier.JAccuracyLVL == 0)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*5000))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*5000))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += ((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*5000))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5);
					}

				if(player[g_Player]->Soldier.JAccuracyLVL == 1)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 3);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 3);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 3);
					}

				if(player[g_Player]->Soldier.JAccuracyLVL == 2)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 6);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 6);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 6);
					}

				if(player[g_Player]->Soldier.JAccuracyLVL == 3)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 30);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 30);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].WeaponSKILL.Accuracy/5000)*500))*((player[g_Player]->WeaponRecoil*500)+1)*(((5000 - player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Accuracy) / 5000) * 5) / 30);
					}

				player[g_Player]->QA_EFF_TRAVEC = Q_Bullet->Bullet[_->NomBullet].TrajVec;

				Q_Bullet->Bullet[_->NomBullet].AlignMatrix = player[g_Player]->TempXForm1;
				Qpo->Transform_New_YRotation(&rotmat, PI);
				Qpo->Transform_Multiply(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &rotmat, &Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

				Q_Bullet->Bullet[_->NomBullet].AvID = -1;

				//Spin
				Q_Bullet->Bullet[_->NomBullet].Xrot = 0;
				Q_Bullet->Bullet[_->NomBullet].Yrot = 0;
				Q_Bullet->Bullet[_->NomBullet].Zrot = 0;

				//printf("Damage %f Power %f player[g_Player]->JINK3_WeaponFactor %f\n", (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Damage, (float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Power, player[g_Player]->JINK3_WeaponFactor);
				//printf("player[g_Player]->BFO.CurrCHAR %i player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON %i\n", player[g_Player]->BFO.CurrCHAR, player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON);

				Q_Bullet->Bullet[_->NomBullet].BulletDMG = ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Damage / 5000) * 0.025 * player[g_Player]->JINK3_WeaponFactor;
				Q_Bullet->Bullet[_->NomBullet].BulletPWR = ((float)player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Power / 5000) * 5 * player[g_Player]->JINK3_WeaponFactor;

				Q_Bullet->Bullet[_->NomBullet].JDamageLVL = player[g_Player]->Soldier.JDamageLVL;

				player[g_Player]->Soldier.JDamageLVLCounter++;
				if(player[g_Player]->Soldier.JDamageLVLCounter > 17)
					{
					player[g_Player]->Soldier.JDamageLVL = 0;
					}

				if(Q_Bullet->Bullet[_->NomBullet].JDamageLVL == 1)
					{
					Q_Bullet->Bullet[_->NomBullet].BulletDMG = Q_Bullet->Bullet[_->NomBullet].BulletDMG * 1.15;
					Q_Bullet->Bullet[_->NomBullet].BulletPWR = Q_Bullet->Bullet[_->NomBullet].BulletPWR * 1.15;
					}

				if(Q_Bullet->Bullet[_->NomBullet].JDamageLVL == 2)
					{
					Q_Bullet->Bullet[_->NomBullet].BulletDMG = Q_Bullet->Bullet[_->NomBullet].BulletDMG * 1.75;
					Q_Bullet->Bullet[_->NomBullet].BulletPWR = Q_Bullet->Bullet[_->NomBullet].BulletPWR * 1.75;
					}

				if(Q_Bullet->Bullet[_->NomBullet].JDamageLVL == 3 || Q_Bullet->Bullet[_->NomBullet].BulletPWR > 45.5)
					{
					Q_Bullet->Bullet[_->NomBullet].BulletDMG = Q_Bullet->Bullet[_->NomBullet].BulletDMG * 3;
					Q_Bullet->Bullet[_->NomBullet].BulletPWR = Q_Bullet->Bullet[_->NomBullet].BulletPWR * 3;

					//##### INITIALISE A VAPOR TRAIL FOR ROCKET
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].StartWidth = 1.75;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].WidthExpand = 2;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].LifeOfPoint = 4;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].NomPoints = 0;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].Live = 1;
					Q_Bullet->Bullet[_->NomBullet].VaporID1 = _->NomVaporTrails;
					if(_->NomVaporTrails < 598) _->NomVaporTrails++;
					}

				if(player[g_Player]->Mech.ACTIVE == 1)
					{
					Q_Bullet->Bullet[_->NomBullet].JDamageLVL = 4;

					Q_Bullet->Bullet[_->NomBullet].BulletDMG = Q_Bullet->Bullet[_->NomBullet].BulletDMG * 10;
					Q_Bullet->Bullet[_->NomBullet].BulletPWR = Q_Bullet->Bullet[_->NomBullet].BulletPWR * 40;

					Q_Bullet->Bullet[_->NomBullet].Scale = 10;
					Q_Bullet->Bullet[_->NomBullet].Speed = 65;		//80

					//##### INITIALISE A VAPOR TRAIL FOR ROCKET
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].StartWidth = 2;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].WidthExpand = 4;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].LifeOfPoint = 3;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].NomPoints = 0;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].Live = 1;
					Q_Bullet->Bullet[_->NomBullet].VaporID1 = _->NomVaporTrails;
					if(_->NomVaporTrails < 598) _->NomVaporTrails++;

					//##### INITIALISE A VAPOR TRAIL FOR ROCKET
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].StartWidth = 4;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].WidthExpand = 6;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].LifeOfPoint = 3;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].NomPoints = 0;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].Live = 1;
					Q_Bullet->Bullet[_->NomBullet].VaporID2 = _->NomVaporTrails;
					if(_->NomVaporTrails < 598) _->NomVaporTrails++;

					//##### INITIALISE A VAPOR TRAIL FOR ROCKET
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].StartWidth = 6;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].WidthExpand = 8;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].LifeOfPoint = 3;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].NomPoints = 0;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].Live = 1;
					Q_Bullet->Bullet[_->NomBullet].VaporID3 = _->NomVaporTrails;
					if(_->NomVaporTrails < 598) _->NomVaporTrails++;
					}
				else
					{
					Q_Bullet->Bullet[_->NomBullet].Scale = 0.5;
					Q_Bullet->Bullet[_->NomBullet].Speed = 250;	//80
					}

				Q_Bullet->Bullet[_->NomBullet].ZSpin = ((float)rand() / 32767)/3;

				Q_Bullet->Bullet[_->NomBullet].Gravity = 0.0001;

				Q_Bullet->Bullet[_->NomBullet].Live = 1;

				Q_Bullet->Bullet[_->NomBullet].NetFlag = 0;

				_->NomBullet++;
				SCRAM++;
				}
			}


		player[g_Player]->Soldier.JAccuracyLVL = 0;

		player[g_Player]->Soldier.JAccuracyLVLCounter++;
		if(player[g_Player]->Soldier.JAccuracyLVLCounter > 17)
			{
			player[g_Player]->Soldier.JAccuracyLVL = 0;
			}
			
		//QpoSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &player[g_Player]->TempXForm1.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//'FIRE' SOUND

		Qpo->Sound_Play(Medias->S_RifleFire[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].QAS_Fire], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->TempXForm1.Translation);

		if(player[g_Player]->Soldier.JDamageLVL > 0)
			{ Qpo->Sound_Play(Medias->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->TempXForm1.Translation); }

		if(player[g_Player]->Soldier.JDamageLVL > 1)
			{ Qpo->Sound_Play(Medias->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->TempXForm1.Translation); }

		if(player[g_Player]->Soldier.JDamageLVL > 2)
			{ Qpo->Sound_Play(Medias->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &player[g_Player]->TempXForm1.Translation); }


		//######## -  QA BULLET EFFECTS  - ########

		player[g_Player]->QA_EFF_SWITCH = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].ON;

		player[g_Player]->QA_EFF_COL00RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Red;
		player[g_Player]->QA_EFF_COL00GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Green;
		player[g_Player]->QA_EFF_COL00BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Blue;
		player[g_Player]->QA_EFF_COL00ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].Alpha;

		player[g_Player]->QA_EFF_COL01RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Red;
		player[g_Player]->QA_EFF_COL01GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Green;
		player[g_Player]->QA_EFF_COL01BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Blue;
		player[g_Player]->QA_EFF_COL01ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[1].Alpha;

		player[g_Player]->QA_EFF_COL02RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Red;
		player[g_Player]->QA_EFF_COL02GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Green;
		player[g_Player]->QA_EFF_COL02BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Blue;
		player[g_Player]->QA_EFF_COL02ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[2].Alpha;

		player[g_Player]->QA_EFF_COL03RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Red;
		player[g_Player]->QA_EFF_COL03GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Green;
		player[g_Player]->QA_EFF_COL03BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Blue;
		player[g_Player]->QA_EFF_COL03ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[3].Alpha;

		player[g_Player]->QA_EFF_COL04RED = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Red;
		player[g_Player]->QA_EFF_COL04GREEN = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Green;
		player[g_Player]->QA_EFF_COL04BLUE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Blue;
		player[g_Player]->QA_EFF_COL04ALPHA = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[4].Alpha;

		player[g_Player]->QA_EFF_TYPE = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].TYPE;
		player[g_Player]->QA_EFF_INTENSITY = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].Effect[0].INT;
		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &player[g_Player]->QA_EFF_BONEMATRIX);

		player[g_Player]->QA_EFF_BONEMATRIX.Matrix = player[g_Player]->TempXForm1.Matrix;
		player[g_Player]->QA_EFF_BONEMATRIX.Translation.x = player[g_Player]->TempXForm1.Translation.x;
		player[g_Player]->QA_EFF_BONEMATRIX.Translation.y = player[g_Player]->TempXForm1.Translation.y;
		player[g_Player]->QA_EFF_BONEMATRIX.Translation.z = player[g_Player]->TempXForm1.Translation.z;

		if(player[g_Player]->QA_EFF_SWITCH == 1)
			{
			switch(player[g_Player]->QA_EFF_TYPE)
				{
				case 1:
					{
					//###### Pink Flakes
					//SPARKS
					helly = 0;
					while(helly < player[g_Player]->QA_EFF_INTENSITY * _->TimeScale)
						{
						Q_BSparks->BSparks[_->NomSparks].Pos = player[g_Player]->QA_EFF_BONEMATRIX.Translation;

						Q_BSparks->BSparks[_->NomSparks].TraVec = player[g_Player]->QA_EFF_TRAVEC;

						Q_BSparks->BSparks[_->NomSparks].TraVec.x += ((((float)rand() / 32767)-0.15));
						Q_BSparks->BSparks[_->NomSparks].TraVec.y += ((((float)rand() / 32767)-0.15));
						Q_BSparks->BSparks[_->NomSparks].TraVec.z += ((((float)rand() / 32767)-0.15));

						Q_BSparks->BSparks[_->NomSparks].AlpFade = 255;
						Q_BSparks->BSparks[_->NomSparks].Timer = 0;
						Q_BSparks->BSparks[_->NomSparks].TimerGoal = ((((float)rand() / 32767)*30)+10);

						Qpo->Vec3d_AddScaled(&Q_BSparks->BSparks[_->NomSparks].Pos, 1, &Q_BSparks->BSparks[_->NomSparks].TraVec, &Q_BSparks->BSparks[_->NomSparks].Pos);
						
						Q_BSparks->BSparks[_->NomSparks].Speed = 8;

						Q_BSparks->BSparks[_->NomSparks].Gravity = 0.12;

						Q_BSparks->BSparks[_->NomSparks].Bounce = 0;

						Q_BSparks->BSparks[_->NomSparks].SmokeTrail = 0;
						Q_BSparks->BSparks[_->NomSparks].Live = 1;

						_->NomSparks++;
						if(_->NomSparks > 499) _->NomSparks = 0;
						helly++;
						}
					}break;
				}
			}

		Q_MFlash->MFlash[250].JDamageLVL = player[g_Player]->Soldier.JDamageLVL;
		player[g_Player]->Soldier.JDamageLVL = 0;


		//Qpo->Avatar_GetBoneTransform(&player[g_Player]->Weapon, "BIP01 R HAND", &Q_MFlash->MFlash[250].AlignMatrix);

		Q_MFlash->MFlash[250].AlignMatrix.Matrix = player[g_Player]->TempXForm2.Matrix;

		//Qpo->Transform_New_YRotation(&rotmat, PI/2);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[250].AlignMatrix, &rotmat, &Q_MFlash->MFlash[250].AlignMatrix);

		//Qpo->Transform_New_ZRotation(&rotmat, (((float)rand() / 32767)*0.3) - 0.15);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[250].AlignMatrix, &rotmat, &Q_MFlash->MFlash[250].AlignMatrix);

		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)/13);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[250].AlignMatrix, &rotmat, &Q_MFlash->MFlash[250].AlignMatrix);


		//Qpo->Transform_GetUp(&Q_MFlash->MFlash[250].AlignMatrix, &Q_MFlash->MFlash[250].VecUp);
		//Qpo->Transform_GetLeft(&Q_MFlash->MFlash[250].AlignMatrix, &Q_MFlash->MFlash[250].VecLeft);
		//Qpo->Transform_GetIn(&Q_MFlash->MFlash[250].AlignMatrix, &Q_MFlash->MFlash[250].VecIn);

		Q_MFlash->MFlash[250].Pos.x = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.x;
		Q_MFlash->MFlash[250].Pos.y = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.y;
		Q_MFlash->MFlash[250].Pos.z = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.z;

		Q_MFlash->MFlash[250].AlignMatrix.Translation.x = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.x;
		Q_MFlash->MFlash[250].AlignMatrix.Translation.y = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.y;
		Q_MFlash->MFlash[250].AlignMatrix.Translation.z = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.z;

		Qpo->Transform_GetUp(&player[g_Player]->TempXForm1, &Q_MFlash->MFlash[250].VecUp);
		Qpo->Transform_GetLeft(&player[g_Player]->TempXForm1, &Q_MFlash->MFlash[250].VecLeft);

		Q_MFlash->MFlash[250].VecUp.x += Q_MFlash->MFlash[250].VecLeft.x * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecUp.y += Q_MFlash->MFlash[250].VecLeft.y * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecUp.z += Q_MFlash->MFlash[250].VecLeft.z * ((((float)rand() / 32767) * 0.4) - 0.2);

		Q_MFlash->MFlash[250].VecLeft.x += Q_MFlash->MFlash[250].VecUp.x * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecLeft.y += Q_MFlash->MFlash[250].VecUp.y * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecLeft.z += Q_MFlash->MFlash[250].VecUp.z * ((((float)rand() / 32767) * 0.4) - 0.2);

		Q_MFlash->MFlash[250].VecIn.x = Q_Bullet->Bullet[_->NomBullet - 1].TrajVec.x;
		Q_MFlash->MFlash[250].VecIn.y = Q_Bullet->Bullet[_->NomBullet - 1].TrajVec.y;
		Q_MFlash->MFlash[250].VecIn.z = Q_Bullet->Bullet[_->NomBullet - 1].TrajVec.z;

		//if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 3 || player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].ItemDATA[player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].CurrWEAPON].ItemREF == 4)	Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, 105, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].Pos);

		//Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, 10, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VecSTR);
		Q_MFlash->MFlash[250].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_MFlash->MFlash[250].LightColor.red = 255.0f;
		int f_Fact = (rand() % 55);
		Q_MFlash->MFlash[250].LightColor.green = 255.0f - f_Fact;
		Q_MFlash->MFlash[250].LightColor.blue = 200.0f - f_Fact;
		Q_MFlash->MFlash[250].LightColor.alpha = 255.0f;
		Qpo->Light_SetAttr(Q_MFlash->MFlash[250].Light, &Q_MFlash->MFlash[250].VecSTR, &Q_MFlash->MFlash[250].LightColor, (rand() % 2350) + 3550, true);

		Q_MFlash->MFlash[250].Type = QPOLY_TYPE_TRI;
		Q_MFlash->MFlash[250].RenderFlags = 0;	//0	//QPOLY_REND_DEPTH_SORT;
		Q_MFlash->MFlash[250].ScaleBIT = 0.20f;


		//***** MFLASH POWER SCALE ******
		Q_MFlash->MFlash[250].Scale = 20 * (Q_Bullet->Bullet[_->NomBullet-1].BulletPWR);


		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, -15, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].Pos);


			//##Flash Vertical##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, Q_MFlash->MFlash[250].Scale/8, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertFU1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFU1, Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFU1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFU1, -Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFU2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFU2, -Q_MFlash->MFlash[250].Scale/4, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertFU3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFU3, Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFU4);


			//##Flash Horizontal##
				//LEFT VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, -Q_MFlash->MFlash[250].Scale/8, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertFD1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFD1, Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFD1);


				//LEFT VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFD1, -Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFD2);


				//RIGHT VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFD2, Q_MFlash->MFlash[250].Scale/4, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertFD3);

				//RIGHT VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertFD3, Q_MFlash->MFlash[250].Scale, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].VertFD4);
	
						// Z
		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)*2);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[250].AlignMatrix, &rotmat, &Q_MFlash->MFlash[250].AlignMatrix);

		Qpo->Transform_GetUp(&Q_MFlash->MFlash[250].AlignMatrix, &Q_MFlash->MFlash[250].VecUp);
		Qpo->Transform_GetLeft(&Q_MFlash->MFlash[250].AlignMatrix, &Q_MFlash->MFlash[250].VecLeft);
		Qpo->Vec3d_Inverse(&Q_MFlash->MFlash[250].VecLeft);

		Q_MFlash->MFlash[250].VecUp.x += Q_MFlash->MFlash[250].VecLeft.x * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecUp.y += Q_MFlash->MFlash[250].VecLeft.y * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecUp.z += Q_MFlash->MFlash[250].VecLeft.z * ((((float)rand() / 32767) * 0.4) - 0.2);

		Q_MFlash->MFlash[250].VecLeft.x += Q_MFlash->MFlash[250].VecUp.x * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecLeft.y += Q_MFlash->MFlash[250].VecUp.y * ((((float)rand() / 32767) * 0.4) - 0.2);
		Q_MFlash->MFlash[250].VecLeft.z += Q_MFlash->MFlash[250].VecUp.z * ((((float)rand() / 32767) * 0.4) - 0.2);

			//##Flash Spinner##
				//TOP VERT1
		/*Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, Q_MFlash->MFlash[250].Scale/14, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertS1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS1, Q_MFlash->MFlash[250].Scale/4, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS1, -Q_MFlash->MFlash[250].Scale/2, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS2, -Q_MFlash->MFlash[250].Scale/7, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS3, Q_MFlash->MFlash[250].Scale/2, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS4);*/


			//##Flash Spinner##			-SQUARE
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, Q_MFlash->MFlash[250].Scale/4, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertS1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS1, Q_MFlash->MFlash[250].Scale/4, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS1, -Q_MFlash->MFlash[250].Scale/2, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS2, -Q_MFlash->MFlash[250].Scale/2, &Q_MFlash->MFlash[250].VecUp, &Q_MFlash->MFlash[250].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].VertS3, Q_MFlash->MFlash[250].Scale/2, &Q_MFlash->MFlash[250].VecLeft, &Q_MFlash->MFlash[250].VertS4);


			int a=0;
			while( a <= 2 )
				{
				int b=0;
				while( b <= 3 )
					{
					Q_MFlash->MFlash[250].Lvert[a][b].a = 255;
					Q_MFlash->MFlash[250].Lvert[a][b].b = 255;
					Q_MFlash->MFlash[250].Lvert[a][b].g = 255;
					Q_MFlash->MFlash[250].Lvert[a][b].r = 255;
					b++;
					}
				a++;
				}


				//##Flash Vertical##

				Q_MFlash->MFlash[250].Lvert[0][0].u = 0;
				Q_MFlash->MFlash[250].Lvert[0][0].v = 1;
				Q_MFlash->MFlash[250].Lvert[0][0].x = Q_MFlash->MFlash[250].VertFU1.x;
				Q_MFlash->MFlash[250].Lvert[0][0].y = Q_MFlash->MFlash[250].VertFU1.y;
				Q_MFlash->MFlash[250].Lvert[0][0].z = Q_MFlash->MFlash[250].VertFU1.z;

					
				Q_MFlash->MFlash[250].Lvert[0][1].u = 1;
				Q_MFlash->MFlash[250].Lvert[0][1].v = 1;
				Q_MFlash->MFlash[250].Lvert[0][1].x = Q_MFlash->MFlash[250].VertFU2.x;
				Q_MFlash->MFlash[250].Lvert[0][1].y = Q_MFlash->MFlash[250].VertFU2.y;
				Q_MFlash->MFlash[250].Lvert[0][1].z = Q_MFlash->MFlash[250].VertFU2.z;

					
				Q_MFlash->MFlash[250].Lvert[0][2].u = 1;
				Q_MFlash->MFlash[250].Lvert[0][2].v = 0;
				Q_MFlash->MFlash[250].Lvert[0][2].x = Q_MFlash->MFlash[250].VertFU3.x;
				Q_MFlash->MFlash[250].Lvert[0][2].y = Q_MFlash->MFlash[250].VertFU3.y;
				Q_MFlash->MFlash[250].Lvert[0][2].z = Q_MFlash->MFlash[250].VertFU3.z;


				Q_MFlash->MFlash[250].Lvert[0][3].u = 0;
				Q_MFlash->MFlash[250].Lvert[0][3].v = 0;
				Q_MFlash->MFlash[250].Lvert[0][3].x = Q_MFlash->MFlash[250].VertFU4.x;
				Q_MFlash->MFlash[250].Lvert[0][3].y = Q_MFlash->MFlash[250].VertFU4.y;
				Q_MFlash->MFlash[250].Lvert[0][3].z = Q_MFlash->MFlash[250].VertFU4.z;



				//##Flash Horizontal##

				Q_MFlash->MFlash[250].Lvert[1][0].u = 0;
				Q_MFlash->MFlash[250].Lvert[1][0].v = 1;
				Q_MFlash->MFlash[250].Lvert[1][0].x = Q_MFlash->MFlash[250].VertFD1.x;
				Q_MFlash->MFlash[250].Lvert[1][0].y = Q_MFlash->MFlash[250].VertFD1.y;
				Q_MFlash->MFlash[250].Lvert[1][0].z = Q_MFlash->MFlash[250].VertFD1.z;

					
				Q_MFlash->MFlash[250].Lvert[1][1].u = 1;
				Q_MFlash->MFlash[250].Lvert[1][1].v = 1;
				Q_MFlash->MFlash[250].Lvert[1][1].x = Q_MFlash->MFlash[250].VertFD2.x;
				Q_MFlash->MFlash[250].Lvert[1][1].y = Q_MFlash->MFlash[250].VertFD2.y;
				Q_MFlash->MFlash[250].Lvert[1][1].z = Q_MFlash->MFlash[250].VertFD2.z;

					
				Q_MFlash->MFlash[250].Lvert[1][2].u = 1;
				Q_MFlash->MFlash[250].Lvert[1][2].v = 0;
				Q_MFlash->MFlash[250].Lvert[1][2].x = Q_MFlash->MFlash[250].VertFD3.x;
				Q_MFlash->MFlash[250].Lvert[1][2].y = Q_MFlash->MFlash[250].VertFD3.y;
				Q_MFlash->MFlash[250].Lvert[1][2].z = Q_MFlash->MFlash[250].VertFD3.z;


				Q_MFlash->MFlash[250].Lvert[1][3].u = 0;
				Q_MFlash->MFlash[250].Lvert[1][3].v = 0;
				Q_MFlash->MFlash[250].Lvert[1][3].x = Q_MFlash->MFlash[250].VertFD4.x;
				Q_MFlash->MFlash[250].Lvert[1][3].y = Q_MFlash->MFlash[250].VertFD4.y;
				Q_MFlash->MFlash[250].Lvert[1][3].z = Q_MFlash->MFlash[250].VertFD4.z;


				//##Flash Spinner##

				Q_MFlash->MFlash[250].Lvert[2][0].u = 0;
				Q_MFlash->MFlash[250].Lvert[2][0].v = 1;
				Q_MFlash->MFlash[250].Lvert[2][0].x = Q_MFlash->MFlash[250].VertS1.x;
				Q_MFlash->MFlash[250].Lvert[2][0].y = Q_MFlash->MFlash[250].VertS1.y;
				Q_MFlash->MFlash[250].Lvert[2][0].z = Q_MFlash->MFlash[250].VertS1.z;

					
				Q_MFlash->MFlash[250].Lvert[2][1].u = 1;
				Q_MFlash->MFlash[250].Lvert[2][1].v = 1;
				Q_MFlash->MFlash[250].Lvert[2][1].x = Q_MFlash->MFlash[250].VertS2.x;
				Q_MFlash->MFlash[250].Lvert[2][1].y = Q_MFlash->MFlash[250].VertS2.y;
				Q_MFlash->MFlash[250].Lvert[2][1].z = Q_MFlash->MFlash[250].VertS2.z;

					
				Q_MFlash->MFlash[250].Lvert[2][2].u = 1;
				Q_MFlash->MFlash[250].Lvert[2][2].v = 0;
				Q_MFlash->MFlash[250].Lvert[2][2].x = Q_MFlash->MFlash[250].VertS3.x;
				Q_MFlash->MFlash[250].Lvert[2][2].y = Q_MFlash->MFlash[250].VertS3.y;
				Q_MFlash->MFlash[250].Lvert[2][2].z = Q_MFlash->MFlash[250].VertS3.z;


				Q_MFlash->MFlash[250].Lvert[2][3].u = 0;
				Q_MFlash->MFlash[250].Lvert[2][3].v = 0;
				Q_MFlash->MFlash[250].Lvert[2][3].x = Q_MFlash->MFlash[250].VertS4.x;
				Q_MFlash->MFlash[250].Lvert[2][3].y = Q_MFlash->MFlash[250].VertS4.y;
				Q_MFlash->MFlash[250].Lvert[2][3].z = Q_MFlash->MFlash[250].VertS4.z;

				/*Q_MFlash->MFlash[250].Lvert[0][0].u = 0;
				Q_MFlash->MFlash[250].Lvert[0][0].v = 1;
				Q_MFlash->MFlash[250].Lvert[0][0].a = 255;
				Q_MFlash->MFlash[250].Lvert[0][0].b = 255;
				Q_MFlash->MFlash[250].Lvert[0][0].g = 255;
				Q_MFlash->MFlash[250].Lvert[0][0].r = 255;
				Q_MFlash->MFlash[250].Lvert[0][0].x = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.x;
				Q_MFlash->MFlash[250].Lvert[0][0].y = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.y;
				Q_MFlash->MFlash[250].Lvert[0][0].z = Q_Bullet->Bullet[_->NomBullet - 1].WorldPos.z;

				unsigned int MFLASHbmp;

				float f_Random = (((float)rand() / 32767) * 3);

				if(f_Random >= 0 && f_Random < 1) MFLASHbmp = Medias->MFlashS1;
				if(f_Random >= 1 && f_Random < 2) MFLASHbmp = Medias->MFlashS2;
				if(f_Random >= 2 && f_Random < 3) MFLASHbmp = Medias->MFlashS3;

				Qpo->Poly_AddOnce(&Q_MFlash->MFlash[250].Lvert[0][0], 1, MFLASHbmp, Q_MFlash->MFlash[250].Type, Q_MFlash->MFlash[250].RenderFlags, Q_MFlash->MFlash[250].ScaleBIT);*/

				//Qpo->Vec3d_AddScaled(&Q_Bullet->Bullet[_->NomBullet - 1].WorldPos, Q_MFlash->MFlash[250].Scale, &Q_Bullet->Bullet[_->NomBullet - 1].TrajVec, &Q_MFlash->MFlash[250].PosEnd);
		
				//Q.ShowLine(&Q_Bullet->Bullet[_->NomBullet - 1].WorldPos, &Q_MFlash->MFlash[250].PosEnd, &player[g_Player]->ViewXForm.Translation, Q_MFlash->MFlash[250].Scale, Medias->MFlashX, 125, 255, 255, 255, 1);

#if 1
				Qpo->Poly_AddOnce(&Q_MFlash->MFlash[250].Lvert[0][0], 4, Medias->MFlashX, Q_MFlash->MFlash[250].Type, Q_MFlash->MFlash[250].RenderFlags, Q_MFlash->MFlash[250].ScaleBIT);
				Qpo->Poly_AddOnce(&Q_MFlash->MFlash[250].Lvert[1][0], 4, Medias->MFlashX, Q_MFlash->MFlash[250].Type, Q_MFlash->MFlash[250].RenderFlags, Q_MFlash->MFlash[250].ScaleBIT);
				Qpo->Poly_AddOnce(&Q_MFlash->MFlash[250].Lvert[2][0], 4, Medias->MFlashS1, Q_MFlash->MFlash[250].Type, Q_MFlash->MFlash[250].RenderFlags, Q_MFlash->MFlash[250].ScaleBIT);
#endif

		player[g_Player]->MFlash = 0;
		}
	}

};