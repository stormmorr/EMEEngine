/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -World Event Engine-
	- Minor Component -Avatar Muzzle Flash-

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
#include "Q-ENE-EnergyTypes.h"
#include "Q-WE-BulletSystem.h"

using namespace GVARS;

namespace GVARS
{

	//##### MUZZLE FLASH #####

void Q_COREFunctions::CONTROL_AvatarMuzzleFlash(int AIcounter)
	{
	if(Q_MFlash->MFlash[AIcounter].JDamageLVL > 0)
		{
		Q_MFlash->MFlash[AIcounter].JDamageLVL--;

		//Qpo->Avatar_GetTransformAvatar(&Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_MFlash->MFlash[AIcounter].AlignMatrix, AIcounter);

		//QpoSound3D_GetConfig(World, &player->ViewXForm, &Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
		//'FIRE' SOUND
		Qpo->Sound_Play(Media->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation);
		}

	if(Q_Forge->Forge[AIcounter].MFlash == 1 && Q_MFlash->MFlash[AIcounter].SkipFlag == 0)
		{
		Q_MFlash->MFlash[AIcounter].SkipFlag = 1;

		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL == 1) Q_Forge->Forge[AIcounter].NETMFlash = 2;
		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL == 2) Q_Forge->Forge[AIcounter].NETMFlash = 3;
		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL == 3) Q_Forge->Forge[AIcounter].NETMFlash = 4;

		Q_Forge->Forge[AIcounter].NETMFlash = 1;

		//### Initialise one CARTRIDGE
							//V-- Maximum cartridge restriction
		if(_->NomCart >= 1500) _->NomCart = 0;
		//Qpo->Avatar_GetWeaponTransform(&Q_Forge->Forge[AIcounter].AV, "BONE02", &Q_Forge->Forge[AIcounter].TempXForm1);
		Qpo->Avatar_GetTransformAvatar(&Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].TempXForm1, AIcounter);

		Q_Cartridge->Cartridge[_->NomCart].WorldPos = Q_Forge->Forge[AIcounter].TempXForm1.Translation;

		if(Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID == 250)
			{
			Q_Forge->Forge[AIcounter].TempVec1 = playerAV->Xform.Translation;
			Q_Forge->Forge[AIcounter].TempVec1.y += (23 + (30*(((player->CDATA.CharDATA[player->CDATA.CurrCHAR].BodySKILL.Height/100)-0.5)*2)));
			}
		else
			{
			Q_Forge->Forge[AIcounter].TempVec1 = Q_Forge->Forge[Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID].Xform.Translation;
			Q_Forge->Forge[AIcounter].TempVec1.y += (23 + (30*(((Q_Forge->Forge[Q_Forge->Forge[AIcounter].Q_Brain.TargetLOCKID].CharDATA.BodySKILL.Height/100)-0.5)*2)));
			}

		Qpo->Vec3d_Subtract(&Q_Forge->Forge[AIcounter].TempVec1, &Q_Forge->Forge[AIcounter].TempXForm1.Translation, &Q_Forge->Forge[AIcounter].TempVec4);
		Qpo->Vec3d_Normalize(&Q_Forge->Forge[AIcounter].TempVec4);

#if 0
		Q_Forge->Forge[AIcounter].TempVec2.x = 0;
		Q_Forge->Forge[AIcounter].TempVec2.y = 1;	//Up
		Q_Forge->Forge[AIcounter].TempVec2.z = 0;
				
				//Left
		Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AIcounter].TempVec4, &Q_Forge->Forge[AIcounter].TempVec2, &Q_Forge->Forge[AIcounter].TempVec3);
		Qpo->Transform_New_LeftUpIn(&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Forge->Forge[AIcounter].TempVec3, &Q_Forge->Forge[AIcounter].TempVec2, &Q_Forge->Forge[AIcounter].TempVec4);
		//Qpo->Transform_RotateY(&Q_Forge->Forge[AIcounter].TempXForm1, -Q_Forge->Forge[AIcounter].Angles.y + PI);
		Qpo->Transform_Orthonormalize(&Q_Forge->Forge[AIcounter].TempXForm1);
		Q_Forge->Forge[AIcounter].TempXForm1.Translation = Q_Cartridge->Cartridge[_->NomCart].WorldPos;

		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Matrix = Q_Forge->Forge[AIcounter].TempXForm1.Matrix;
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.x = Q_Forge->Forge[AIcounter].TempXForm1.Translation.x;
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.y = Q_Forge->Forge[AIcounter].TempXForm1.Translation.y;
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.z = Q_Forge->Forge[AIcounter].TempXForm1.Translation.z;
#else
		if(fab(Q_Forge->Forge[AIcounter].TempVec4.y) > fab(Q_Forge->Forge[AIcounter].TempVec4.x))
			{
			major = 1;
			if(fab(Q_Forge->Forge[AIcounter].TempVec4.z) > fab(Q_Forge->Forge[AIcounter].TempVec4.y)) major = 2;
			}
		else if(fab(Q_Forge->Forge[AIcounter].TempVec4.z) > fab(Q_Forge->Forge[AIcounter].TempVec4.x)) major = 2;
							
		if(fab(Q_Forge->Forge[AIcounter].TempVec4.x) ==1.0f || fab(Q_Forge->Forge[AIcounter].TempVec4.y) == 1.0f || fab(Q_Forge->Forge[AIcounter].TempVec4.z) == 1.0f)
			{
			if ((major == 0 && Q_Forge->Forge[AIcounter].TempVec4.x > 0) || major == 1)
				{
				TempVec1.x = 0.0f;
				TempVec1.y = 0.0f;
				TempVec1.z = -1.0f;
				}
			else if (major == 0)
				{
				TempVec1.x = 0.0f;
				TempVec1.y = 0.0f;
				TempVec1.z = 1.0f;
				}
			else 
				{
				TempVec1.x = Q_Forge->Forge[AIcounter].TempVec4.z;
				TempVec1.y = 0.0f;
				TempVec1.z = 0.0f;
				}
			}
		else Qpo->Vec3d_CrossProduct(&Axis[major], &Q_Forge->Forge[AIcounter].TempVec4, &TempVec1);

		Qpo->Vec3d_Normalize(&TempVec1);
		Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AIcounter].TempVec4, &TempVec1, &TempVec2);
		Qpo->Vec3d_Normalize(&TempVec2);
							
		Qpo->Vec3d_Inverse(&TempVec1);

		Qpo->Transform_New(&Q_Forge->Forge[AIcounter].TempXForm2);
		Qpo->Transform_New_LeftUpIn(&Q_Forge->Forge[AIcounter].TempXForm2, &TempVec1, &TempVec2, &Q_Forge->Forge[AIcounter].TempVec4);
		Qpo->Transform_Orthonormalize(&Q_Forge->Forge[AIcounter].TempXForm2);

		Qpo->Transform_New_YRotation(&rotmat, PI);
		Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].TempXForm2, &rotmat, &Q_Forge->Forge[AIcounter].TempXForm2);
		Q_Bullet->Bullet[_->NomBullet].AlignMatrix = Q_Forge->Forge[AIcounter].TempXForm2;
#endif

		//Trajectory
		Qpo->Transform_GetIn(&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Cartridge->Cartridge[_->NomCart].TrajVec);
		Qpo->Vec3d_AddScaled(&Q_Cartridge->Cartridge[_->NomCart].WorldPos, -5.6, &Q_Cartridge->Cartridge[_->NomCart].TrajVec, &Q_Cartridge->Cartridge[_->NomCart].WorldPos);

		Qpo->Transform_GetLeft(&Q_Forge->Forge[AIcounter].TempXForm1, &Q_Cartridge->Cartridge[_->NomCart].TrajVec);
		Qpo->Vec3d_Inverse(&Q_Cartridge->Cartridge[_->NomCart].TrajVec);

		Q_Cartridge->Cartridge[_->NomCart].Scale = 0.5 * (Q_Forge->Forge[AIcounter].CharDATA.AvatarSCALE + (0.16*(((((Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Height+Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.Weight)/2)/100)-0.5)*2)));
		
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.x += ((float)rand() / 32767)/3;
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.z += ((float)rand() / 32767)/3;
		Q_Cartridge->Cartridge[_->NomCart].TrajVec.y += 2.2;

		Q_Cartridge->Cartridge[_->NomCart].FloorBounce = 0;
		Q_Cartridge->Cartridge[_->NomCart].Gravity = 0.8;

		//Qpo->Transform_New_YRotation(&rotmat, PI/2);
		//Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].TempXForm1, &rotmat, &Q_Forge->Forge[AIcounter].TempXForm1);

		//Qpo->Transform_New_ZRotation(&rotmat, ((float)rand() / 32767)*6);
		//Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].TempXForm1, &rotmat, &Q_Forge->Forge[AIcounter].TempXForm1);

		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)/13);
		//Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].TempXForm1, &rotmat, &Q_Forge->Forge[AIcounter].TempXForm1);

		//Qpo->Transform_New_ZRotation(&rotmat, ((float)rand() / 32767)*2);
		//Qpo->Transform_Multiply(&Q_Forge->Forge[AIcounter].TempXForm1, &rotmat, &Q_Forge->Forge[AIcounter].TempXForm1);

		//Q_Cartridge->Cartridge[_->NomCart].AlignMatrix = Q_Forge->Forge[AIcounter].TempXForm1;
		Q_Cartridge->Cartridge[_->NomCart].AlignMatrix = Q_Forge->Forge[AIcounter].TempXForm2;

		Q_Cartridge->Cartridge[_->NomCart].XSpin = ((float)rand() / 32767)/6;
		Q_Cartridge->Cartridge[_->NomCart].YSpin = ((float)rand() / 32767)/6;
		Q_Cartridge->Cartridge[_->NomCart].ZSpin = ((float)rand() / 32767)/6;

		Q_Cartridge->Cartridge[_->NomCart].Speed = (((float)rand() / 32767)+1)*3;	//*2

		Q_Cartridge->Cartridge[_->NomCart].Live = 1;

		_->NomCart++;


		//##### INITIALISE BULLET/S

		if(_->NetworkOption != 1)
			{
			SCRAM = 0;
			while((SCRAM < Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].BulletCNT) && (_->NomBullet < 398))	//=-- Maximum bullet restriction
				{
				//Initialise one BULLET
				//Q_Forge->Forge[AIcounter].TempXForm2.Matrix = Q_Forge->Forge[AIcounter].TempXForm1.Matrix;
				Q_Forge->Forge[AIcounter].TempXForm2.Matrix = Q_Forge->Forge[AIcounter].TempXForm2.Matrix;
				Q_Forge->Forge[AIcounter].TempXForm2.Translation.x = Q_Forge->Forge[AIcounter].TempXForm1.Translation.x;
				Q_Forge->Forge[AIcounter].TempXForm2.Translation.y = Q_Forge->Forge[AIcounter].TempXForm1.Translation.y;
				Q_Forge->Forge[AIcounter].TempXForm2.Translation.z = Q_Forge->Forge[AIcounter].TempXForm1.Translation.z;

				Q_Bullet->Bullet[_->NomBullet].TrajVec = Q_Forge->Forge[AIcounter].TempVec4;

				Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].TempXForm2.Translation, 100, &Q_Bullet->Bullet[_->NomBullet].TrajVec, &Q_Forge->Forge[AIcounter].TempXForm2.Translation);

				Q_Bullet->Bullet[_->NomBullet].WorldPos = Q_Forge->Forge[AIcounter].TempXForm2.Translation;
				Q_Bullet->Bullet[_->NomBullet].ORIGPos = Q_Forge->Forge[AIcounter].TempXForm2.Translation;

				if(Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL == 0)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += ((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50);
					}

				if(Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL == 1)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 3);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 3);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 3);
					}

				if(Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL == 2)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 6);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 6);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 6);
					}

				if(Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL == 3)
					{
					Q_Bullet->Bullet[_->NomBullet].TrajVec.x += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 30);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.y += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 30);
					Q_Bullet->Bullet[_->NomBullet].TrajVec.z += (((((float)rand() / 32767)-0.5)/((Q_Forge->Forge[AIcounter].CharDATA.WeaponSKILL.Accuracy/5000)*5000))*((player->WeaponRecoil*500)+1)*(((5000 - Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Accuracy) / 5000) * 50) / 30);
					}

				Q_Bullet->Bullet[_->NomBullet].AlignMatrix = Q_Forge->Forge[AIcounter].TempXForm2;
				Qpo->Transform_New_XRotation(&rotmat, PI/2);
				Qpo->Transform_Multiply(&Q_Bullet->Bullet[_->NomBullet].AlignMatrix, &rotmat, &Q_Bullet->Bullet[_->NomBullet].AlignMatrix);

				Q_Bullet->Bullet[_->NomBullet].AvID = AIcounter;

				//Spin
				Q_Bullet->Bullet[_->NomBullet].Xrot = 0;
				Q_Bullet->Bullet[_->NomBullet].Yrot = 0;
				Q_Bullet->Bullet[_->NomBullet].Zrot = 0;

				Q_Bullet->Bullet[_->NomBullet].BulletDMG = ((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Damage / 5000) * 20 * Q_Forge->Forge[AIcounter].JINK3_WeaponFactor;
				Q_Bullet->Bullet[_->NomBullet].BulletPWR = ((float)Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Power / 5000) * 20 * Q_Forge->Forge[AIcounter].JINK3_WeaponFactor;

				Q_Bullet->Bullet[_->NomBullet].JDamageLVL = Q_Forge->Forge[AIcounter].Soldier.JDamageLVL;

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
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].StartWidth = 3;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].WidthExpand = 1.75;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].LifeOfPoint = 2;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].NomPoints = 0;
					Q_VaporTrail->VaporTrail[_->NomVaporTrails].Live = 1;
					Q_Bullet->Bullet[_->NomBullet].VaporID1 = _->NomVaporTrails;
					if(_->NomVaporTrails < 598) _->NomVaporTrails++;
					}

				if(Q_Forge->Forge[AIcounter].Mech.ACTIVE == 1)
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

				_->NomBullet++;
				SCRAM++;
				}
			}

		Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 0;

		/*QpoSound3D_GetConfig(World,
					&player->ViewXForm,
					&Q_Forge->Forge[AIcounter].TempVec1,
					600.0f,
					2.0f,
					&Volume,
					&Pan,
					&Frequency);*/


		//'FIRE' SOUND
		Qpo->Sound_Play(Media->S_RifleFire[Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].QAS_Fire], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].TempXForm1.Translation);

		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL > 0)
			{ Qpo->Sound_Play(Media->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].TempVec1); }

		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL > 1)
			{ Qpo->Sound_Play(Media->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].TempVec1); }

		if(Q_Forge->Forge[AIcounter].Soldier.JDamageLVL > 2)
			{ Qpo->Sound_Play(Media->S_RifleFire[11], _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AIcounter].TempVec1); }


		//######## -  QA BULLET EFFECTS  - ########

		Q_Forge->Forge[AIcounter].QA_EFF_SWITCH = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].ON;

		Q_Forge->Forge[AIcounter].QA_EFF_COL00RED = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].Red;
		Q_Forge->Forge[AIcounter].QA_EFF_COL00GREEN = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].Green;
		Q_Forge->Forge[AIcounter].QA_EFF_COL00BLUE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].Blue;
		Q_Forge->Forge[AIcounter].QA_EFF_COL00ALPHA = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].Alpha;

		Q_Forge->Forge[AIcounter].QA_EFF_COL01RED = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[1].Red;
		Q_Forge->Forge[AIcounter].QA_EFF_COL01GREEN = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[1].Green;
		Q_Forge->Forge[AIcounter].QA_EFF_COL01BLUE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[1].Blue;
		Q_Forge->Forge[AIcounter].QA_EFF_COL01ALPHA = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[1].Alpha;

		Q_Forge->Forge[AIcounter].QA_EFF_COL02RED = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[2].Red;
		Q_Forge->Forge[AIcounter].QA_EFF_COL02GREEN = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[2].Green;
		Q_Forge->Forge[AIcounter].QA_EFF_COL02BLUE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[2].Blue;
		Q_Forge->Forge[AIcounter].QA_EFF_COL02ALPHA = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[2].Alpha;

		Q_Forge->Forge[AIcounter].QA_EFF_COL03RED = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[3].Red;
		Q_Forge->Forge[AIcounter].QA_EFF_COL03GREEN = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[3].Green;
		Q_Forge->Forge[AIcounter].QA_EFF_COL03BLUE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[3].Blue;
		Q_Forge->Forge[AIcounter].QA_EFF_COL03ALPHA = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[3].Alpha;

		Q_Forge->Forge[AIcounter].QA_EFF_COL04RED = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[4].Red;
		Q_Forge->Forge[AIcounter].QA_EFF_COL04GREEN = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[4].Green;
		Q_Forge->Forge[AIcounter].QA_EFF_COL04BLUE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[4].Blue;
		Q_Forge->Forge[AIcounter].QA_EFF_COL04ALPHA = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[4].Alpha;

		Q_Forge->Forge[AIcounter].QA_EFF_TYPE = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].TYPE;
		Q_Forge->Forge[AIcounter].QA_EFF_INTENSITY = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].Effect[0].INT;
		Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX = Q_Forge->Forge[AIcounter].TempXForm1;

		if(Q_Forge->Forge[AIcounter].QA_EFF_SWITCH == 1)
			{
			switch(Q_Forge->Forge[AIcounter].QA_EFF_TYPE)
				{
				case 1:
					{
					//###### Pink Flakes
					//SPARKS
					helly = 0;
					while(helly < Q_Forge->Forge[AIcounter].QA_EFF_INTENSITY * _->TimeScale)
						{
						Q_BSparks->BSparks[_->NomSparks].Pos = Q_Forge->Forge[AIcounter].QA_EFF_BONEMATRIX.Translation;

						Q_BSparks->BSparks[_->NomSparks].TraVec = Q_Forge->Forge[AIcounter].QA_EFF_TRAVEC;

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

		Q_MFlash->MFlash[AIcounter].JDamageLVL = Q_Forge->Forge[AIcounter].Soldier.JDamageLVL;
		Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 0;

		Q_MFlash->MFlash[AIcounter].AlignMatrix.Matrix = Q_Forge->Forge[AIcounter].TempXForm1.Matrix;
		Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation = Q_Forge->Forge[AIcounter].TempXForm1.Translation;

		Q_MFlash->MFlash[AIcounter].AlignMatrix.Matrix.load_identity();
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.x = 0;
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.y = 0;
		//Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation.z = 0;

		Qpo->Transform_New_ZRotation(&rotmat, Q_Forge->Forge[AIcounter].Angles.y + (PI/2));
		Qpo->Transform_Multiply(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &rotmat, &Q_MFlash->MFlash[AIcounter].AlignMatrix);

		Q_MFlash->MFlash[AIcounter].Pos = Q_MFlash->MFlash[AIcounter].AlignMatrix.Translation;

		//Qpo->Transform_New_YRotation(&rotmat, PI/2);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &rotmat, &Q_MFlash->MFlash[AIcounter].AlignMatrix);

		//Qpo->Transform_New_ZRotation(&rotmat, ((float)rand() / 32767)*6);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &rotmat, &Q_MFlash->MFlash[AIcounter].AlignMatrix);

		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)/13);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &rotmat, &Q_MFlash->MFlash[AIcounter].AlignMatrix);

		Qpo->Transform_GetUp(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &Q_MFlash->MFlash[AIcounter].VecUp);
		Qpo->Transform_GetLeft(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &Q_MFlash->MFlash[AIcounter].VecLeft);
		Qpo->Transform_GetIn(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &Q_MFlash->MFlash[AIcounter].VecIn);
		//Qpo->Vec3d_Inverse(&Q_MFlash->MFlash[AIcounter].VecIn);

		if(Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 3 || Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrWEAPON].ItemREF == 4)	Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[250].Pos, 105, &Q_MFlash->MFlash[250].VecIn, &Q_MFlash->MFlash[250].Pos);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, 10, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VecSTR);
		Q_MFlash->MFlash[AIcounter].Light = Qpo->Light_AddtoWorld(_->GenericLightPos);
		Q_MFlash->MFlash[AIcounter].LightColor.red = 255.0f;
		Q_MFlash->MFlash[AIcounter].LightColor.green = 255.0f;
		Q_MFlash->MFlash[AIcounter].LightColor.blue = 200.0f;
		Q_MFlash->MFlash[AIcounter].LightColor.alpha = 255.0f;
		Qpo->Light_SetAttr(Q_MFlash->MFlash[AIcounter].Light, &Q_MFlash->MFlash[AIcounter].VecSTR, &Q_MFlash->MFlash[AIcounter].LightColor, (rand() % 350) + 550, true);

		Q_MFlash->MFlash[AIcounter].Type = QPOLY_TYPE_TRI;
		Q_MFlash->MFlash[AIcounter].RenderFlags = 0;//QPOLY_REND_DEPTH_SORT;
		Q_MFlash->MFlash[AIcounter].ScaleBIT = 1.0f;

		//***** MFLASH POWER SCALE ******
		Q_MFlash->MFlash[AIcounter].Scale = 20 * (Q_Bullet->Bullet[_->NomBullet-1].BulletPWR);//20 * (Q_Bullet->Bullet[_->NomBullet-1].BulletPWR);


		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, 3, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].Pos);

			//##Flash Vertical##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, Q_MFlash->MFlash[AIcounter].Scale/8, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertFU1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFU1, Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFU1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFU1, -Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFU2);

				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFU2, -Q_MFlash->MFlash[AIcounter].Scale/4, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertFU3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFU3, Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFU4);

			//##Flash Horizontal##
				//LEFT VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, -Q_MFlash->MFlash[AIcounter].Scale/8, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertFD1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFD1, Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFD1);

				//LEFT VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFD1, -Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFD2);

				//RIGHT VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFD2, Q_MFlash->MFlash[AIcounter].Scale/4, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertFD3);

				//RIGHT VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertFD3, Q_MFlash->MFlash[AIcounter].Scale, &Q_MFlash->MFlash[AIcounter].VecIn, &Q_MFlash->MFlash[AIcounter].VertFD4);

		//Qpo->Transform_New_YRotation(&rotmat, ((float)rand() / 32767)*2);
		//Qpo->Transform_Multiply(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &rotmat, &Q_MFlash->MFlash[AIcounter].AlignMatrix);

		Qpo->Transform_GetUp(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &Q_MFlash->MFlash[AIcounter].VecUp);
		Qpo->Transform_GetLeft(&Q_MFlash->MFlash[AIcounter].AlignMatrix, &Q_MFlash->MFlash[AIcounter].VecLeft);

			/*##Flash Spinner##
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, Q_MFlash->MFlash[AIcounter].Scale/14, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertS1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS1, Q_MFlash->MFlash[AIcounter].Scale/4, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS1, -Q_MFlash->MFlash[AIcounter].Scale/2, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS2);


				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS2, -Q_MFlash->MFlash[AIcounter].Scale/7, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS3, Q_MFlash->MFlash[AIcounter].Scale/2, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS4);*/

			//##Flash Spinner##			-SQUARE
				//TOP VERT1
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].Pos, Q_MFlash->MFlash[AIcounter].Scale/4, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertS1);

		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS1, Q_MFlash->MFlash[AIcounter].Scale/4, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS1);

				//TOP VERT2
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS1, -Q_MFlash->MFlash[AIcounter].Scale/2, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS2);

				//BOTTOM VERT3
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS2, -Q_MFlash->MFlash[AIcounter].Scale/2, &Q_MFlash->MFlash[AIcounter].VecUp, &Q_MFlash->MFlash[AIcounter].VertS3);

				//BOTTOM VERT4
		Qpo->Vec3d_AddScaled(&Q_MFlash->MFlash[AIcounter].VertS3, Q_MFlash->MFlash[AIcounter].Scale/2, &Q_MFlash->MFlash[AIcounter].VecLeft, &Q_MFlash->MFlash[AIcounter].VertS4);

		a=0;
		while( a <= 2 )
			{
			b=0;
			while( b <= 3 )
				{
				Q_MFlash->MFlash[AIcounter].Lvert[a][b].a = 255;//((rand() % 200) + 15);	//200
				Q_MFlash->MFlash[AIcounter].Lvert[a][b].b = 255;//sunrise;	//100
				Q_MFlash->MFlash[AIcounter].Lvert[a][b].g = 255;//Q_MFlash->MFlash[AIcounter].Lvert[a][b].a;
				Q_MFlash->MFlash[AIcounter].Lvert[a][b].r = 255;//((rand() % 200) + 5);	//100 //180
				b++;
				}
			a++;
			}

		//##Flash Vertical##
		Q_MFlash->MFlash[AIcounter].Lvert[0][0].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[0][0].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[0][0].x = Q_MFlash->MFlash[AIcounter].VertFU1.x;
		Q_MFlash->MFlash[AIcounter].Lvert[0][0].y = Q_MFlash->MFlash[AIcounter].VertFU1.y;
		Q_MFlash->MFlash[AIcounter].Lvert[0][0].z = Q_MFlash->MFlash[AIcounter].VertFU1.z;
			
		Q_MFlash->MFlash[AIcounter].Lvert[0][1].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[0][1].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[0][1].x = Q_MFlash->MFlash[AIcounter].VertFU2.x;
		Q_MFlash->MFlash[AIcounter].Lvert[0][1].y = Q_MFlash->MFlash[AIcounter].VertFU2.y;
		Q_MFlash->MFlash[AIcounter].Lvert[0][1].z = Q_MFlash->MFlash[AIcounter].VertFU2.z;

		Q_MFlash->MFlash[AIcounter].Lvert[0][2].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[0][2].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[0][2].x = Q_MFlash->MFlash[AIcounter].VertFU3.x;
		Q_MFlash->MFlash[AIcounter].Lvert[0][2].y = Q_MFlash->MFlash[AIcounter].VertFU3.y;
		Q_MFlash->MFlash[AIcounter].Lvert[0][2].z = Q_MFlash->MFlash[AIcounter].VertFU3.z;

		Q_MFlash->MFlash[AIcounter].Lvert[0][3].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[0][3].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[0][3].x = Q_MFlash->MFlash[AIcounter].VertFU4.x;
		Q_MFlash->MFlash[AIcounter].Lvert[0][3].y = Q_MFlash->MFlash[AIcounter].VertFU4.y;
		Q_MFlash->MFlash[AIcounter].Lvert[0][3].z = Q_MFlash->MFlash[AIcounter].VertFU4.z;

		//##Flash Horizontal##
		Q_MFlash->MFlash[AIcounter].Lvert[1][0].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[1][0].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[1][0].x = Q_MFlash->MFlash[AIcounter].VertFD1.x;
		Q_MFlash->MFlash[AIcounter].Lvert[1][0].y = Q_MFlash->MFlash[AIcounter].VertFD1.y;
		Q_MFlash->MFlash[AIcounter].Lvert[1][0].z = Q_MFlash->MFlash[AIcounter].VertFD1.z;

		Q_MFlash->MFlash[AIcounter].Lvert[1][1].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[1][1].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[1][1].x = Q_MFlash->MFlash[AIcounter].VertFD2.x;
		Q_MFlash->MFlash[AIcounter].Lvert[1][1].y = Q_MFlash->MFlash[AIcounter].VertFD2.y;
		Q_MFlash->MFlash[AIcounter].Lvert[1][1].z = Q_MFlash->MFlash[AIcounter].VertFD2.z;
			
		Q_MFlash->MFlash[AIcounter].Lvert[1][2].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[1][2].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[1][2].x = Q_MFlash->MFlash[AIcounter].VertFD3.x;
		Q_MFlash->MFlash[AIcounter].Lvert[1][2].y = Q_MFlash->MFlash[AIcounter].VertFD3.y;
		Q_MFlash->MFlash[AIcounter].Lvert[1][2].z = Q_MFlash->MFlash[AIcounter].VertFD3.z;

		Q_MFlash->MFlash[AIcounter].Lvert[1][3].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[1][3].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[1][3].x = Q_MFlash->MFlash[AIcounter].VertFD4.x;
		Q_MFlash->MFlash[AIcounter].Lvert[1][3].y = Q_MFlash->MFlash[AIcounter].VertFD4.y;
		Q_MFlash->MFlash[AIcounter].Lvert[1][3].z = Q_MFlash->MFlash[AIcounter].VertFD4.z;

		//##Flash Spinner##
		Q_MFlash->MFlash[AIcounter].Lvert[2][0].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[2][0].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[2][0].x = Q_MFlash->MFlash[AIcounter].VertS1.x;
		Q_MFlash->MFlash[AIcounter].Lvert[2][0].y = Q_MFlash->MFlash[AIcounter].VertS1.y;
		Q_MFlash->MFlash[AIcounter].Lvert[2][0].z = Q_MFlash->MFlash[AIcounter].VertS1.z;

		Q_MFlash->MFlash[AIcounter].Lvert[2][1].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[2][1].v = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[2][1].x = Q_MFlash->MFlash[AIcounter].VertS2.x;
		Q_MFlash->MFlash[AIcounter].Lvert[2][1].y = Q_MFlash->MFlash[AIcounter].VertS2.y;
		Q_MFlash->MFlash[AIcounter].Lvert[2][1].z = Q_MFlash->MFlash[AIcounter].VertS2.z;
			
		Q_MFlash->MFlash[AIcounter].Lvert[2][2].u = 1;
		Q_MFlash->MFlash[AIcounter].Lvert[2][2].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[2][2].x = Q_MFlash->MFlash[AIcounter].VertS3.x;
		Q_MFlash->MFlash[AIcounter].Lvert[2][2].y = Q_MFlash->MFlash[AIcounter].VertS3.y;
		Q_MFlash->MFlash[AIcounter].Lvert[2][2].z = Q_MFlash->MFlash[AIcounter].VertS3.z;

		Q_MFlash->MFlash[AIcounter].Lvert[2][3].u = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[2][3].v = 0;
		Q_MFlash->MFlash[AIcounter].Lvert[2][3].x = Q_MFlash->MFlash[AIcounter].VertS4.x;
		Q_MFlash->MFlash[AIcounter].Lvert[2][3].y = Q_MFlash->MFlash[AIcounter].VertS4.y;
		Q_MFlash->MFlash[AIcounter].Lvert[2][3].z = Q_MFlash->MFlash[AIcounter].VertS4.z;

		/*glPushMatrix();
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		Qpo->Avatar_GetBoneTransformMP(Q_Forge->Forge[AIcounter].AV, "BIP01 R HAND", &Q_Forge->Forge[AIcounter].RFistPosV);

		glTranslatef(Q_Forge->Forge[AIcounter].RFistPosV.Translation.x, Q_Forge->Forge[AIcounter].RFistPosV.Translation.y, Q_Forge->Forge[AIcounter].RFistPosV.Translation.z);
		glMultMatrixf(Q_Forge->Forge[AIcounter].RFistPosV.Matrix.mf);*/

#if 0
		Qpo->Poly_AddOnce(&Q_MFlash->MFlash[AIcounter].Lvert[0][0], 4, Media->MFlashX, Q_MFlash->MFlash[AIcounter].Type, Q_MFlash->MFlash[AIcounter].RenderFlags, Q_MFlash->MFlash[AIcounter].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_MFlash->MFlash[AIcounter].Lvert[1][0], 4, Media->MFlashX, Q_MFlash->MFlash[AIcounter].Type, Q_MFlash->MFlash[AIcounter].RenderFlags, Q_MFlash->MFlash[AIcounter].ScaleBIT);
		Qpo->Poly_AddOnce(&Q_MFlash->MFlash[AIcounter].Lvert[2][0], 4, Media->MFlashS, Q_MFlash->MFlash[AIcounter].Type, Q_MFlash->MFlash[AIcounter].RenderFlags, Q_MFlash->MFlash[AIcounter].ScaleBIT);
#endif

		//glPopMatrix();

		Q_Forge->Forge[AIcounter].MFlash = 0;
		}

	if(Q_MFlash->MFlash[AIcounter].SkipFlag == 1)
		{
		Q_MFlash->MFlash[AIcounter].SkipFlag = 0;
		Qpo->Light_Remove(Q_MFlash->MFlash[AIcounter].Light);
		}

	//########  - 3D Star BackPack Item -  ########//
	if(Q_Forge->Forge[AIcounter].Backpack.Draw == 1)
		{
		Qpo->Avatar_GetBoneTransform(&Q_Forge->Forge[AIcounter].AV, "BIP01 SPINE2", &Q_Forge->Forge[AIcounter].Backpack.PosMatrix);
		Qpo->Transform_GetLeft(&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].Backpack.Leftvec);
		Qpo->Transform_GetUp(&Q_Forge->Forge[AIcounter].AV.Xform,&Q_Forge->Forge[AIcounter].Backpack.Upvec);
		
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation, -3, &Q_Forge->Forge[AIcounter].Backpack.Upvec, &Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation);

		Q_Forge->Forge[AIcounter].Backpack.Vert1 = Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation;


		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.Vert1, -5, &Q_Forge->Forge[AIcounter].Backpack.Upvec, &Q_Forge->Forge[AIcounter].Backpack.Vert1);
											//Distance to the Left of the Q_Forge->Forge[AIcounter]	300
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.Vert1, 200, &Q_Forge->Forge[AIcounter].Backpack.Leftvec, &Q_Forge->Forge[AIcounter].Backpack.Vert1);

									//Distance to the Right of the Q_Forge->Forge[AIcounter] from the left 600
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.Vert1, -400, &Q_Forge->Forge[AIcounter].Backpack.Leftvec, &Q_Forge->Forge[AIcounter].Backpack.Vert2);

									//Distance to the Top of the Q_Forge->Forge[AIcounter]	10
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.Vert2, 6, &Q_Forge->Forge[AIcounter].Backpack.Upvec, &Q_Forge->Forge[AIcounter].Backpack.Vert3);

									//Distance to the Top of the Q_Forge->Forge[AIcounter]	10
		Qpo->Vec3d_AddScaled(&Q_Forge->Forge[AIcounter].Backpack.Vert1, 6, &Q_Forge->Forge[AIcounter].Backpack.Upvec, &Q_Forge->Forge[AIcounter].Backpack.Vert4);

		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].a = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].b = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].g = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].r = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].u = 0;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].v = 0;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].x = Q_Forge->Forge[AIcounter].Backpack.Vert1.x;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].y = Q_Forge->Forge[AIcounter].Backpack.Vert1.y;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].z = Q_Forge->Forge[AIcounter].Backpack.Vert1.z;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].a = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].b = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].g = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].r = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].u = 1;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].v = 0;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].x = Q_Forge->Forge[AIcounter].Backpack.Vert2.x;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].y = Q_Forge->Forge[AIcounter].Backpack.Vert2.y;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][1].z = Q_Forge->Forge[AIcounter].Backpack.Vert2.z;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].a = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].b = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].g = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].r = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].u = 1;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].v = 1;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].x = Q_Forge->Forge[AIcounter].Backpack.Vert3.x;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].y = Q_Forge->Forge[AIcounter].Backpack.Vert3.y;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][2].z = Q_Forge->Forge[AIcounter].Backpack.Vert3.z;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].a = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].b = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].g = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].r = 255;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].u = 0;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].v = 1;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].x = Q_Forge->Forge[AIcounter].Backpack.Vert4.x;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].y = Q_Forge->Forge[AIcounter].Backpack.Vert4.y;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][3].z = Q_Forge->Forge[AIcounter].Backpack.Vert4.z;

		Qpo->Poly_AddOnce(&Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0], 4, Media->special4[Q_Forge->Forge[AIcounter].Backpack.Matcount], QPOLY_TYPE_TRI, QPOLY_REND_DEPTH_SORT, 1.0f);
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].x = Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation.x;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].y = Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation.y;
		Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0].z = Q_Forge->Forge[AIcounter].Backpack.PosMatrix.Translation.z;
		Qpo->Poly_AddOnce(&Q_Forge->Forge[AIcounter].Backpack.Lvert[0][0], 1, Media->special4[Q_Forge->Forge[AIcounter].Backpack.Matcount], QPOLY_TYPE_PNT, QPOLY_REND_DEPTH_SORT, 0.1f);

		if(Q_Forge->Forge[AIcounter].Backpack.MatcountDir == 0)
			{
			if(Q_Forge->Forge[AIcounter].Backpack.Matcount + 1 < 12) Q_Forge->Forge[AIcounter].Backpack.Matcount += 1;	//2
			else Q_Forge->Forge[AIcounter].Backpack.MatcountDir = 1;
			}
		if(Q_Forge->Forge[AIcounter].Backpack.MatcountDir == 1)
			{
			if(Q_Forge->Forge[AIcounter].Backpack.Matcount - 1 > 0) Q_Forge->Forge[AIcounter].Backpack.Matcount -= 1;
			else	
				{
				Q_Forge->Forge[AIcounter].Backpack.MatcountDir = 0;
				Q_Forge->Forge[AIcounter].Backpack.Draw = 0;
				}
			}
		}
	}
};