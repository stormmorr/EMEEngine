




void Q_Network::TransmitWorld(float i_Time)
{

	//Buffer_Data		Buffer;
	//UInt8			Data[555000];

	//Buffer_Set(Data, 555000);

	//SET MESSAGE TYPE AND SERVER TIME
	//Buffer_FillByte(NETMGR_MSG_UPDATE_CLIENT_WORLD);			// Let client know its updating
	Buffer_FillFloat(i_Time);								// Current Time
	//Buffer_FillFloat(Client->ServerPingBack);			// Current Time

	//###### PREPARE Player Update  #####
	//#### Find Player Avatar
	//helly=0;
	//while(Q_Netplayer->Netplayer[helly].ID != NID)
	//	{ helly++; }

	//### FILL BUFFER
	Buffer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].AV.Xform.Translation);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].Mposestate);

	if(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].EnergySWITCHOFF > 0)
		{
		Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].EnergySWITCHOFF--;
		Buffer_FillByte(205);
		}
	else Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].Aposestate);

	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].attackon);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].WeaponStatus);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].NETMFlash);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].Block);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].BlockHit);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].BlockHeight);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].Crouch);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].HitReactScale);
	Buffer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].MoveReactVec);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].MoveReactSpeed);

	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].JINK3_PowerFactor);

	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].HB_Energy);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].HB_Health);

	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].SpecLvlRESET);
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].SNDTRIGEnergy);
	
	Buffer_FillByte(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].PlayerMode);

	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].idleposecnt);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].runposecnt);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].attposecnt);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].crohposecnt);
	Buffer_FillFloat(Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].jumpposecnt);

	Buffer_FillAngle(&Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].WallRunCollision.Plane.Normal);

	Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].SNDTRIGEnergy = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].SpecLvlRESET = 0;
	Q_Forge->Forge[Q_Netplayer->Netplayer[helly].LocalCONTROLID].NETMFlash = 0;


	//###### PREPARE SERVER'S Player Update  #####
	//#### Find Server Avatar

	//#### Prepare Server Player Update

	//### FILL BUFFER
	Buffer_FillAngle(&playerAV->Xform.Translation);

#pragma message("Full matrix transmission or partial quat makeup")

	Buffer_FillAngle(&playerAV->Up);

	Buffer_FillByte(player->Mposestate);

	if(player->EnergySWITCHOFF > 0)
		{
		player->EnergySWITCHOFF--;

		Buffer_FillByte(205);
		}
	else Buffer_FillByte(player->Aposestate);

	Buffer_FillByte(player->attackon);
	Buffer_FillByte(player->WeaponStatus);
	Buffer_FillByte(player->NETMFlash);
	Buffer_FillByte(player->Block);
	Buffer_FillByte(player->BlockHit);
	Buffer_FillByte(player->BlockHeight);
	Buffer_FillByte(player->Crouch);
	Buffer_FillFloat(player->HitReactScale);
	Buffer_FillAngle(&player->MoveReactVec);
	Buffer_FillFloat(player->MoveReactSpeed);

	Buffer_FillFloat(player->JINK3_PowerFactor);

	Buffer_FillFloat(player->HB_Energy);
	Buffer_FillFloat(player->HB_Health);
	
	Buffer_FillByte(player->PlayerMode);

	Buffer_FillFloat(player->idleposecnt);
	Buffer_FillFloat(player->runposecnt);
	Buffer_FillFloat(player->attposecnt);
	Buffer_FillFloat(player->crohposecnt);
	Buffer_FillFloat(player->jumpposecnt);

	Buffer_FillAngle(&player->WallRunCollision.Plane.Normal);

	player->NETMFlash = 0;


	//######  - Other Worldly Avatars -  #####

	//#### Fill AI Avatars
	/*int i_AvatarCount = 0;
	helly2=0;
	while(helly2 < _->NomAI)
		{
		if((Q_Forge->Forge[helly2].LIVE == 1) && (helly2 != Q_Netplayer->Netplayer[helly].LocalCONTROLID)) QHost.PlayerUPDATE.AvatarCount++;
		helly2++;
		}*/


	//### Set the Avatar Count
	Buffer_FillInteger(_->NomAI - 1);

	//##### AVATAR UPDATE PREP LOOP
	jet=0;
	while(jet < _->NomAI)
		{
		if((Q_Forge->Forge[jet].LIVE == 1) && (jet != Q_Netplayer->Netplayer[helly].LocalCONTROLID))
			{
			Q_Forge->Forge[jet].NETMFlash = 0;

			//### FILL BUFFER
			Buffer_FillByte(jet);
			#pragma message("?")

			//###Get Player Data to Client
			Buffer_FillAngle(&Q_Forge->Forge[jet].AV.Xform.Translation);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

			Buffer_FillAngle(&Q_Forge->Forge[jet].Up);

			Buffer_FillByte(Q_Forge->Forge[jet].Mposestate);		//Avatar Move Pose State

			if(player->EnergySWITCHOFF > 0)
				{
				player->EnergySWITCHOFF--;

				Buffer_FillByte(205);
				}
			else Buffer_FillByte(Q_Forge->Forge[jet].Aposestate);

			Buffer_FillByte(Q_Forge->Forge[jet].attackon);		//Avatar Attack Pose State
			Buffer_FillByte(Q_Forge->Forge[jet].WeaponStatus);
			Buffer_FillByte(Q_Forge->Forge[jet].NETMFlash);
			Buffer_FillByte(Q_Forge->Forge[jet].Block);			//Avatar Attack Pose State
			Buffer_FillByte(Q_Forge->Forge[jet].BlockHit);		//Avatar Attack Pose State
			Buffer_FillByte(Q_Forge->Forge[jet].BlockHeight);
			Buffer_FillByte(Q_Forge->Forge[jet].Crouch);			//Avatar Attack Pose State
			Buffer_FillFloat(Q_Forge->Forge[jet].HitReactScale);
			Buffer_FillAngle(&Q_Forge->Forge[jet].MoveReactVec);
			Buffer_FillFloat(Q_Forge->Forge[jet].MoveReactSpeed);
			Buffer_FillFloat(Q_Forge->Forge[jet].JINK3_PowerFactor);

			Buffer_FillFloat(Q_Forge->Forge[jet].HB_Energy);
			Buffer_FillFloat(Q_Forge->Forge[jet].HB_Health);
			
			Buffer_FillByte(Q_Forge->Forge[jet].PlayerMode);

			Buffer_FillFloat(Q_Forge->Forge[jet].idleposecnt);		//Avatar Idle Pose Counter
			Buffer_FillFloat(Q_Forge->Forge[jet].runposecnt);		//Avatar Run Pose Counter
			Buffer_FillFloat(Q_Forge->Forge[jet].attposecnt);		//Avatar Attack Pose Counter
			Buffer_FillFloat(Q_Forge->Forge[jet].crohposecnt);		//Avatar Attack Pose Counter
			Buffer_FillFloat(Q_Forge->Forge[jet].jumpposecnt);		//Avatar Attack Pose Counter

			Buffer_FillAngle(&Q_Forge->Forge[jet].WallRunCollision.Plane.Normal);
			}

		jet++;
		}


	//##### Prepare Q_Object->ObjectS
	Buffer_FillFloat(_->NomQObject);

	aero = 0;
	while(aero < _->NomQObject)
		{
		Buffer_FillFloat(Q_Object->Object[aero].StrengthBANK);
		
		aero++;
		}


	//##### Prepare World Bullets
	Buffer_FillInteger(_->NomBullet);

	aero = 0;
	while(aero < _->NomBullet)
		{
		Buffer_FillByte(Q_Bullet->Bullet[aero].Live);
		Buffer_FillAngle(&Q_Bullet->Bullet[aero].TrajVec);
		Buffer_FillAngle(&Q_Bullet->Bullet[aero].WorldPos);		//Avatar Move Pose State
		Buffer_FillByte(Q_Bullet->Bullet[aero].Speed);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Bullet->Bullet[aero].AvID);		//Avatar Attack Pose State
		Buffer_FillAngle(&Q_Bullet->Bullet[aero].ORIGPos);		//Avatar Attack Pose State
		Buffer_FillFloat(Q_Bullet->Bullet[aero].ZSpin);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[0][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[0][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[0][2]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[1][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[1][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[1][2]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[2][0]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[2][1]);
		Buffer_FillFloat(Q_Bullet->Bullet[aero].AlignMatrix.Matrix.m[2][2]);
		Buffer_FillAngle(&Q_Bullet->Bullet[aero].AlignMatrix.Translation);
		Buffer_FillByte(Q_Bullet->Bullet[aero].JDamageLVL);

		aero++;
		}


	//##### Prepare World Bullet Hits
	Buffer_FillInteger(_->NomBulHit);

	aero = 0;
	while(aero < _->NomBulHit)
		{
		Buffer_FillByte(Q_BulletHit->BulletHit[aero].Live);
		Buffer_FillByte(Q_BulletHit->BulletHit[aero].Init);
		Buffer_FillByte(Q_BulletHit->BulletHit[aero].EffectType);
		Buffer_FillByte(Q_BulletHit->BulletHit[aero].AvID);
		Buffer_FillByte(Q_BulletHit->BulletHit[aero].AvatarHITID);

		Buffer_FillFloat(Q_BulletHit->BulletHit[aero].BulletDMG);
		Buffer_FillFloat(Q_BulletHit->BulletHit[aero].BulletPWR);

		Buffer_FillAngle(&Q_BulletHit->BulletHit[aero].Pos);
		Buffer_FillAngle(&Q_BulletHit->BulletHit[aero].BulletTraj);
		Buffer_FillAngle(&Q_BulletHit->BulletHit[aero].CollNormal);

		aero++;
		}


	//##### Prepare World Melee Hits
	Buffer_FillInteger(_->NomMelHit);

	aero = 0;
	while(aero < _->NomMelHit)
		{
		Buffer_FillByte(Q_MeleeHit->MeleeHit[aero].Live);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[aero].HitTYPE);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[aero].HitRESULT);

		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[aero].Impact);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[aero].Bonenum);
		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[aero].ReactionNorm);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].HitPowerPercent);
		Buffer_FillByte(Q_MeleeHit->MeleeHit[aero].BloodAmt);

		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.Radius);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.MaxRadius);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.StartFade);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.Red);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.Green);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].Expandro3D.Blue);

		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttackSTRENGTH);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttackSNAP);
		
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[0][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[0][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[0][2]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[1][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[1][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[1][2]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[2][0]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[2][1]);
		Buffer_FillFloat(Q_MeleeHit->MeleeHit[aero].AttboneXF.Matrix.m[2][2]);
		Buffer_FillAngle(&Q_MeleeHit->MeleeHit[aero].AttboneXF.Translation);

		aero++;
		}


	//##### Prepare Small Energy
	Buffer_FillInteger(_->NomSEnergy);

	aero = 0;
	while(aero < _->NomSEnergy)
		{
		Buffer_FillByte(Q_SEnergy->SEnergy[aero].Live);
		Buffer_FillAngle(&Q_SEnergy->SEnergy[aero].LightPos);
		Buffer_FillAngle(&Q_SEnergy->SEnergy[aero].TraVec);
		Buffer_FillFloat(Q_SEnergy->SEnergy[aero].Speed);
		Buffer_FillFloat(Q_SEnergy->SEnergy[aero].Scale);
		Buffer_FillByte(Q_SEnergy->SEnergy[aero].Alpha);
		Buffer_FillByte(Q_SEnergy->SEnergy[aero].TargetLock);
		Buffer_FillByte(Q_SEnergy->SEnergy[aero].TargetID);
		Buffer_FillFloat(Q_SEnergy->SEnergy[aero].AngleX);
		Buffer_FillFloat(Q_SEnergy->SEnergy[aero].AngleY);
		Buffer_FillFloat(Q_SEnergy->SEnergy[aero].AngleZ);

		aero++;
		}


	//##### Prepare Large Energy
	Buffer_FillInteger(_->NomLEnergy);

	aero = 0;
	while(aero < _->NomLEnergy)
		{
		Buffer_FillByte(Q_LEnergy->LEnergy[aero].Live);
		Buffer_FillAngle(&Q_LEnergy->LEnergy[aero].LightPos);
		Buffer_FillAngle(&Q_LEnergy->LEnergy[aero].TraVec);
		Buffer_FillFloat(Q_LEnergy->LEnergy[aero].Speed);
		Buffer_FillFloat(Q_LEnergy->LEnergy[aero].Scale);
		Buffer_FillByte(Q_LEnergy->LEnergy[aero].Alpha);
		Buffer_FillByte(Q_LEnergy->LEnergy[aero].EnergyLive);
		Buffer_FillByte(Q_LEnergy->LEnergy[aero].EnergyFire);

		aero++;
		}


	//##### Prepare World Explosions
	Buffer_FillInteger(_->NomExplosions);

	aero = 0;
	while(aero < _->NomExplosions)
		{
		Buffer_FillByte(Q_Explosion->Explosion[aero].Live);
		Buffer_FillAngle(&Q_Explosion->Explosion[aero].Pos);
		Buffer_FillFloat(Q_Explosion->Explosion[aero].ExpSize);
		Buffer_FillFloat(Q_Explosion->Explosion[aero].LargeEnergyAvID);
		Buffer_FillAngle(&Q_Explosion->Explosion[aero].CollPlaneNormal);

		aero++;
		}


	//##### Prepare Cleric Heal Sparks
	Buffer_FillInteger(_->NomHSpark);

	aero = 0;
	while(aero < _->NomHSpark)
		{
		Buffer_FillByte(Q_HealSpark->HealSpark[aero].Live);
		Buffer_FillByte(Q_HealSpark->HealSpark[aero].HTYPE);
		Buffer_FillAngle(&Q_HealSpark->HealSpark[aero].Pos);
		Buffer_FillAngle(&Q_HealSpark->HealSpark[aero].TraVec);
		Buffer_FillByte(Q_HealSpark->HealSpark[aero].Released);
		Buffer_FillByte(Q_HealSpark->HealSpark[aero].Absorbed);
		Buffer_FillByte(Q_HealSpark->HealSpark[aero].HealTarget);
		Buffer_FillFloat(Q_HealSpark->HealSpark[aero].AlpFade);
		Buffer_FillFloat(Q_HealSpark->HealSpark[aero].ScaleSTR);

		aero++;
		}


	//##### Prepare Cleric Spells
	Buffer_FillInteger(_->NomSpell);

	aero = 0;
	while(aero < _->NomSpell)
		{
		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].Live);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].HealTarget);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].NumSpheres);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].LightPos);
		Buffer_FillFloat(Q_ClericSpell->ClericSpell[aero].LightPow);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].Absorbed);

		Buffer_FillFloat(Q_ClericSpell->ClericSpell[aero].Sphere[0].Radius);
		Buffer_FillFloat(Q_ClericSpell->ClericSpell[aero].Sphere[1].Radius);

		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].Sphere[0].StartFade);
		Buffer_FillByte(Q_ClericSpell->ClericSpell[aero].Sphere[1].StartFade);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[0].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[0].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[1].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[1].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[2].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[2].Upvec);

		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[3].Leftvec);
		Buffer_FillAngle(&Q_ClericSpell->ClericSpell[aero].Sphere[3].Upvec);

		aero++;
		}


	//##### Prepare Cleric Plasma
	Buffer_FillInteger(_->NomPlasma);

	aero = 0;
	while(aero < _->NomPlasma)
		{
		Buffer_FillByte(Q_ClericPlasma->ClericPlasma[aero].Live);
		Buffer_FillAngle(&Q_ClericPlasma->ClericPlasma[aero].Pos);
		Buffer_FillAngle(&Q_ClericPlasma->ClericPlasma[aero].TraVec);
		Buffer_FillFloat(Q_ClericPlasma->ClericPlasma[aero].Speed);
		Buffer_FillFloat(Q_ClericPlasma->ClericPlasma[aero].Alpha);
		Buffer_FillByte(Q_ClericPlasma->ClericPlasma[aero].PartType);
		aero++;
		}


	//##### Prepare Net Effects Control
	Buffer_FillInteger(_->NomNetEffectControl);

	aero = 0;
	while(aero < _->NomNetEffectControl)
		{
		Buffer_FillByte(Q_NetEffectControl->NetEffectControl[aero].Live);
		if(Q_NetEffectControl->NetEffectControl[aero].Type == 0) Buffer_FillByte(Q_NetEffectControl->NetEffectControl[aero].Type);
		Buffer_FillAngle(&Q_NetEffectControl->NetEffectControl[aero].Pos);
		Buffer_FillFloat(Q_NetEffectControl->NetEffectControl[aero].Effintensity);
		if(Q_NetEffectControl->NetEffectControl[aero].Type == 1) Buffer_FillByte(Q_NetEffectControl->NetEffectControl[aero].AvID);
		
		aero++;
		}


	//###### ---- Net Effects Control ---- ######
	aero = 0;
	while(aero < _->NomNetEffectControl)
		{
		if(Q_NetEffectControl->NetEffectControl[aero].Live > 1)
			{	//#### COUNTER ####
			Q_NetEffectControl->NetEffectControl[aero].Live--;
			}
		else
			{
			Q_NetEffectControl->NetEffectControl[aero].Live = 0;

			if(Q_NetEffectControl->NetEffectControl[aero].Type = 0)
				{
				//### Energy Array Reorder
				K = aero;
				while(K < _->NomNetEffectControl - 1)
					{
					Q_NetEffectControl->NetEffectControl[K] = Q_NetEffectControl->NetEffectControl[K+1];
					K++;
					}
				}

			_->NomNetEffectControl--;
			}
		aero++;
		}


	//##### Prepare Net Zone Increment
	Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC);

	aero = 0;
	while(aero < Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC)
		{
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].AVID);

		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Maxs);
		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Mins);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Smoke.CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[0].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[1].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[2].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[3].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Effect[4].CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].Fog.CNT);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.TYPE);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.INT);
		Buffer_FillByte(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.ON);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.Red);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.Green);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.Blue);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.Alpha);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.Scale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.TIMER);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].FogLight.CNT);

		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ExpandMINS);
		Buffer_FillAngle(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ExpandMAXS);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ExpandSTRENGTH);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_TimeScale);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Gravity);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_LifeINC);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_EnergyINC);

		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_intBoost);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_EnergyEff);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Height);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Weight);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Strength);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Quickness);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Dexterity);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_Constitution);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_AggPower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_DefPower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_RArmStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_LArmStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_RLegStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_LLegStr);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_RArmSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_LArmSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_RLegSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_LLegSnap);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_WEPAccuracy);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_WEPDrawSPD);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_WEPReloadSPD);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_WEPRecoilHR);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_JINKmovespeed);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_JINKpower);
		Buffer_FillFloat(Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_EnergyMatrix->EnergyMatrix.NetZONEINC[aero]].ZONEINC_JINK3intensity);

		aero++;
		}

	//# Energy Reset
	Q_EnergyMatrix->EnergyMatrix.NomNetZonesINC = 0;


	//##### Prepare Net Zone ENTITY Increment
	Buffer_FillInteger(_->NomNetZoneENTITY);

	aero = 0;
	while(aero < _->NomNetZoneENTITY)
		{
		Buffer_FillByte(Q_NetZoneENTITY->NetZoneENTITY[aero].TYPE);
		Buffer_FillFloat(Q_NetZoneENTITY->NetZoneENTITY[aero].ID);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].ZoneID);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].QObjID);
		Buffer_FillAngle(&Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].Pos);
		Buffer_FillFloat(Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].Range);
		Buffer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].QObjID].Scale);
		Buffer_FillFloat(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].QObjID].StrengthMAX);
		Buffer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].QObjID].CollisionTYPE);
		Buffer_FillByte(Q_Object->Object[Q_BMSentry->BMSentry[Q_NetZoneENTITY->NetZoneENTITY[aero].ID].QObjID].AvID);

		aero++;
		}

	//# Energy Reset
	_->NomNetZoneENTITY = 0;


	//### FRLs
	Buffer_FillFloat(_->FRLtarget);
	Buffer_FillByte(Q_Netplayer->Netplayer[helly].FRLswitch);


	/*if (!geCSNetMgr_SendToClient(QHost.NMgr->CSNetMgr, NID, GE_true, QHost.NMgr->ServerToClientBuffer.Data, QHost.NMgr->ServerToClientBuffer.Pos))
		return GE_false;*/














void Q_Network::RecordWorld(float i_Time)
{
	Buffer_FillFloat(i_Time);

	//### FILL BUFFER
	Buffer_FillAngle(&playerAV->Xform.Translation);
	Buffer_FillByte(player->Mposestate);
	Buffer_FillByte(player->Aposestate);
	Buffer_FillByte(player->attackon);
	Buffer_FillByte(player->WeaponStatus);
	Buffer_FillByte(player->NETMFlash);
	Buffer_FillByte(player->Block);
	Buffer_FillByte(player->BlockHit);
	Buffer_FillByte(player->BlockHeight);
	Buffer_FillByte(player->Crouch);
	Buffer_FillFloat(player->HitReactScale);
	Buffer_FillAngle(&player->MoveReactVec);
	Buffer_FillFloat(player->MoveReactSpeed);

	Buffer_FillFloat(player->JINK3_PowerFactor);

	Buffer_FillFloat(player->HB_Energy);
	Buffer_FillFloat(player->HB_Health);

	Buffer_FillByte(player->SpecLvlRESET);
	Buffer_FillByte(player->SNDTRIGEnergy);
	
	Buffer_FillByte(player->PlayerMode);

	Buffer_FillFloat(player->idleposecnt);
	Buffer_FillFloat(player->runposecnt);
	Buffer_FillFloat(player->attposecnt);
	Buffer_FillFloat(player->crohposecnt);
	Buffer_FillFloat(player->jumpposecnt);

	Buffer_FillAngle(&player->WallRunCollision.Plane.Normal);

	//######  - Other Worldly Avatars -  #####

	//### Set the Avatar Count
	Buffer_FillInteger(_->NomAI);

	//##### AVATAR UPDATE PREP LOOP
	jet=0;
	while(jet < _->NomAI)
		{
		Q_Forge->Forge[jet].NETMFlash = 0;

		//### FILL BUFFER
		Buffer_FillByte(jet);
		#pragma message("?")

		//###Get Player Data to Client
		Buffer_FillAngle(&Q_Forge->Forge[jet].AV.Xform.Translation);				//Avatar Position

#pragma message("Full matrix transmission or partial quat makeup")

		Buffer_FillAngle(&Q_Forge->Forge[jet].Up);

		Buffer_FillByte(Q_Forge->Forge[jet].Mposestate);		//Avatar Move Pose State

		if(player->EnergySWITCHOFF > 0)
			{
			player->EnergySWITCHOFF--;

			Buffer_FillByte(205);
			}
		else Buffer_FillByte(Q_Forge->Forge[jet].Aposestate);

		Buffer_FillByte(Q_Forge->Forge[jet].attackon);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[jet].WeaponStatus);
		Buffer_FillByte(Q_Forge->Forge[jet].NETMFlash);
		Buffer_FillByte(Q_Forge->Forge[jet].Block);			//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[jet].BlockHit);		//Avatar Attack Pose State
		Buffer_FillByte(Q_Forge->Forge[jet].BlockHeight);
		Buffer_FillByte(Q_Forge->Forge[jet].Crouch);			//Avatar Attack Pose State
		Buffer_FillFloat(Q_Forge->Forge[jet].HitReactScale);
		Buffer_FillAngle(&Q_Forge->Forge[jet].MoveReactVec);
		Buffer_FillFloat(Q_Forge->Forge[jet].MoveReactSpeed);
		Buffer_FillFloat(Q_Forge->Forge[jet].JINK3_PowerFactor);

		Buffer_FillFloat(Q_Forge->Forge[jet].HB_Energy);
		Buffer_FillFloat(Q_Forge->Forge[jet].HB_Health);
		
		Buffer_FillByte(Q_Forge->Forge[jet].PlayerMode);

		Buffer_FillFloat(Q_Forge->Forge[jet].idleposecnt);		//Avatar Idle Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[jet].runposecnt);		//Avatar Run Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[jet].attposecnt);		//Avatar Attack Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[jet].crohposecnt);		//Avatar Attack Pose Counter
		Buffer_FillFloat(Q_Forge->Forge[jet].jumpposecnt);		//Avatar Attack Pose Counter

		Buffer_FillAngle(&Q_Forge->Forge[jet].WallRunCollision.Plane.Normal);

		jet++;
		}




	//// Layer Instigator
	t_trrvertex.y_height = 70;
	trrGrid->Grid[4][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[5][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[9][4].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 50;
	trrGrid->Grid[5][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 70;
	trrGrid->Grid[9][5].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 50;
	trrGrid->Grid[5][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 70;
	trrGrid->Grid[9][6].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 50;
	trrGrid->Grid[5][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 70;
	trrGrid->Grid[9][7].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 50;
	trrGrid->Grid[5][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 70;
	trrGrid->Grid[9][8].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[5][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[9][9].layers.push_back( t_trrvertex );

	//// Layer Terminator
	t_trrvertex.y_height = 180;
	trrGrid->Grid[4][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[5][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][4].layers.push_back( t_trrvertex );
	trrGrid->Grid[9][4].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 200;
	trrGrid->Grid[5][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][5].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][5].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 180;
	trrGrid->Grid[9][5].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 120;
	trrGrid->Grid[5][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][6].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][6].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 180;
	trrGrid->Grid[9][6].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 200;
	trrGrid->Grid[5][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][7].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][7].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 180;
	trrGrid->Grid[9][7].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 200;
	trrGrid->Grid[5][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][8].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][8].layers.push_back( t_trrvertex );
	t_trrvertex.y_height = 180;
	trrGrid->Grid[9][8].layers.push_back( t_trrvertex );

	trrGrid->Grid[4][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[5][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[6][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[7][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[8][9].layers.push_back( t_trrvertex );
	trrGrid->Grid[9][9].layers.push_back( t_trrvertex );












	//#### Update Bullets
	m_transfer->acRead(m_Recieve);

	if(m_Recieve == 0)
		{
		m_transfer->acRead(aero);
		if(aero != -5) printf("ERROR:::RecieveWorld (-5) aero %i\n", aero);
		}
	else
		{
		while(m_Recieve == 1)
			{
			m_transfer->acRead(aero);	//Array Position

			if(aero != -5)
				{
				m_transfer->acRead(m_Live);									//Live

				if(m_Live == 1)	// Generate Bullet
					{
					m_BulletTag = new BulletTag(_->NomBullet);
					m_BulletTag->m_SrcID = aero;
					m_BulletTags.push_back(m_BulletTag);

					Q_Bullet->Bullet[_->NomBullet].Live = 1;

					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AvID);		//Avatar Attack Pose State

					Q_Bullet->Bullet[_->NomBullet].AvID = AvatarID;

					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].TrajVec);		//Trajectory Vector
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].WorldPos);	//Avatar Move Pose State
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].Speed);		//Avatar Attack Pose State
					
					//if(player->NetUPDATE.Bullets[_->NomBullet].AvID == player->NetUPDATE.ServerCONTROLID) Q_Bullet->Bullet[_->NomBullet].AvID = 250;
					//if(player->NetUPDATE.Bullets[_->NomBullet].AvID == 250) Q_Bullet->Bullet[_->NomBullet].AvID = Q_Netplayer->Netplayer[0].LocalCONTROLID;

					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].ORIGPos);	//Avatar Attack Pose State
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].ZSpin);
					/*m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[0][0]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[0][1]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[0][2]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[1][0]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[1][1]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[1][2]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[2][0]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[2][1]);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Matrix.m[2][2]);*/
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].AlignMatrix.Translation);
					m_transfer->acRead(Q_Bullet->Bullet[_->NomBullet].JDamageLVL);

					_->NomBullet++;
					}
				else
					{
					mf_pnt = 0;
					mf_pntSTR = 0;
					mf_DestID = -5;
					mf_scan = true;
					while(mf_scan)
						{
						if(mf_pnt > m_BulletTags.size())
							{
							f_Scan = false;
							mf_DestID = -5;
							}
						else
							{
							if(m_BulletTags[mf_pnt]->m_SrcID == aero)
								{
								mf_scan = false;
								mf_DestID = m_BulletTags[mf_pnt]->m_DestID;
								mf_pntSTR = mf_pnt;
								}
							}
						mf_pnt++;
						}

					if(mf_DestID != -5 && mf_DestID >= 0 && mf_DestID < 15000)
						{
						Q_Bullet->Bullet[mf_DestID].Live = 0;

						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AvID);		//Avatar Attack Pose State

						Q_Bullet->Bullet[mf_DestID].AvID = AvatarID;

						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].TrajVec);		//Trajectory Vector
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].WorldPos);	//Avatar Move Pose State
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].Speed);		//Avatar Attack Pose State

						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].ORIGPos);	//Avatar Attack Pose State
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].ZSpin);
						/*m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][0]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][1]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[0][2]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][0]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][1]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[1][2]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][0]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][1]);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Matrix.m[2][2]);*/
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].AlignMatrix.Translation);
						m_transfer->acRead(Q_Bullet->Bullet[mf_DestID].JDamageLVL);

						//### Array Reorder
						int K = mf_DestID;
						while(K < _->NomBullet - 1)
							{
							Q_Bullet->Bullet[K] = Q_Bullet->Bullet[K+1];
							K++;
							}

						_->NomBullet--;

						//### Array Reorder
						K = mf_pntSTR;
						while(K < m_BulletTags.size() - 1)
							{
							m_BulletTags[K] = m_BulletTags[K+1];
							K++;
							}

						m_BulletTags.pop_back();
						}
					}

				printf("_->NomBullet %i\n", _->NomBullet);

				if(!m_transfer->acRead(m_Recieve)) m_Recieve = 0;
				}
			else m_Recieve = 0;
			}
		}






















			m_transfer->acRead(Q_Forge->Forge[AvatarID].Mposestate);		//Avatar Move Pose State
			m_transfer->acRead(Int_Aposestate);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].attackon);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].WeaponStatus);
			m_transfer->acRead(Int_Mflash);
			if(Int_Mflash == 1 && Q_MFlash->MFlash[AvatarID].SkipFlag == 0) Q_Forge->Forge[AvatarID].MFlash = Int_Mflash;
			m_transfer->acRead(Q_Forge->Forge[AvatarID].Block);			//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHit);		//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].BlockHeight);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].Crouch);			//Avatar Attack Pose State
			m_transfer->acRead(Q_Forge->Forge[AvatarID].HitReactScale);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.x);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.y);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactVec.z);
			m_transfer->acRead(Q_Forge->Forge[AvatarID].MoveReactSpeed);

			m_transfer->acRead(Float_PowerFactor);

			if(Q_Forge->Forge[AvatarID].JINK3_PowerFactor != Float_PowerFactor)
				{
				Q.DeactivateItemsAI(AvatarID);
			
				Q_Forge->Forge[AvatarID].JINK3_PowerFactor = Float_PowerFactor;

				Q.ActivateItemsAI(AvatarID);
				}

			m_transfer->acRead(m_Energy);
			m_EnergyGAIN = m_Energy - Q_Forge->Forge[AvatarID].HB_Energy;
			if(m_EnergyGAIN >= 0) Q_Forge->Forge[AvatarID].HB_Energy = m_Energy + m_EnergyGAIN;
			else Q_Forge->Forge[AvatarID].HB_Energy = m_Energy;

			m_transfer->acRead(m_Health);
			m_HealthGAIN = m_Energy - Q_Forge->Forge[AvatarID].HB_Health;
			if(m_HealthGAIN >= 0) Float_Health = m_Health + m_HealthGAIN;
			else Float_Health = m_Health;

			m_transfer->acRead(m_Armour);
			m_ArmourGAIN = m_Armour - Q_Forge->Forge[AvatarID].HB_Armour;
			if(m_ArmourGAIN >= 0) Q_Forge->Forge[AvatarID].HB_Armour = m_Armour + m_ArmourGAIN;
			else Q_Forge->Forge[AvatarID].HB_Armour = m_Armour;

			m_transfer->acRead(m_PowerBank);
			m_PowerBankGAIN = m_Energy - Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK;
			if(m_PowerBankGAIN >= 0) Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK = m_PowerBank + m_PowerBankGAIN;
			else Q_Forge->Forge[AvatarID].CharDATA.BodySKILL.POWERBANK = m_PowerBank;
			
			if((Q_Forge->Forge[AvatarID].HB_Health > 0) && (Float_Health <= 0))
				{
				Q_Forge->Forge[AvatarID].HB_Dead = 1;

				jet = 0;
				while(jet < 5)
					{
					Q.PlayerSpawnNNbot(Q_Forge->Forge[AvatarID].AV.Xform.Translation);

					jet++;
					}

				Qpo->Sound_Play(Media->S_EnemyKO, _->Volume, _->Pan, _->S_TimeScale, false, &Q_Forge->Forge[AvatarID].RFistPos.Translation);
				}

			Q_Forge->Forge[AvatarID].HB_Health = Float_Health;

			m_transfer->acRead(Q_Forge->Forge[AvatarID].PlayerMode);

			m_transfer->acRead(Q_Forge->Forge[AvatarID].idleposecnt);		//Avatar Idle Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].runposecnt);		//Avatar Run Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].attposecnt);		//Avatar Attack Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].crohposecnt);		//Avatar Attack Pose Counter
			m_transfer->acRead(Q_Forge->Forge[AvatarID].jumpposecnt);		//Avatar Attack Pose Counter

			if(Q_Forge->Forge[AvatarID].Aposestate != Int_Aposestate) Q_Forge->Forge[AvatarID].JinkInit = 0;
			else if(Q_Forge->Forge[AvatarID].attposecnt > 0.3 || Q_Forge->Forge[AvatarID].attposecnt == 0) Q_Forge->Forge[AvatarID].JinkInit = 1;

			//### Avatar Attack Pose State
			if(Int_Aposestate == 205) Q_Forge->Forge[AvatarID].EnergySWITCHOFF = 1;

			if(Q_Forge->Forge[AvatarID].EnergySWITCHOFF == 1)
				{
				Q_Forge->Forge[AvatarID].Aposestate = 205;
				Q_Forge->Forge[AvatarID].attackon = 1;
				}
			else Q_Forge->Forge[AvatarID].Aposestate = Int_Aposestate;

			//m_transfer->acRead(Q_Forge->Forge[AvatarID].WallRunCollision.Plane.Normal);

			/*Qpo->Transform_GetLeft(&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
			Q_Forge->Forge[AvatarID].TempVec1 = Q_Forge->Forge[AvatarID].AnglesVec;
			Q_Forge->Forge[AvatarID].TempVec1.y = 0;
			Qpo->Vec3d_Normalize(&Q_Forge->Forge[AvatarID].TempVec1);
			Q_Forge->Forge[AvatarID].Up.y = 0;
			Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Up);

			//### Check Distance between Pure Left and Right to work out direction of Turn
			Qpo->Transform_GetUp(&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Left);
			//Qpo->Transform_GetIn(&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].Up);
			Qpo->Vec3d_Copy(&Q_Forge->Forge[AvatarID].Left, &Q_Forge->Forge[AvatarID].Right);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].Right);

			Q_Forge->Forge[AvatarID].ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Left);
			Q_Forge->Forge[AvatarID].ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].TempVec1, &Q_Forge->Forge[AvatarID].Right);

			if(Q_Forge->Forge[AvatarID].ScanDistL > Q_Forge->Forge[AvatarID].ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

			Q_Forge->Forge[AvatarID].trueAngles.y -= Q_Forge->Forge[AvatarID].ScanTurnAng / 3;

			Q_Forge->Forge[AvatarID].Angles.y -= Q_Forge->Forge[AvatarID].ScanTurnAng / 3;
			if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y = 0;
			if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2);

			Qpo->Transform_New_YRotation(&RotateMatrix, -(Q_Forge->Forge[AvatarID].ScanTurnAng / 3));
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &RotateMatrix, &Q_Forge->Forge[AvatarID].AV.Xform);*/

#if 1
			//Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].AV.STR_Xform.Matrix;

			//Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].AnglesChg.y);
			//Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);

			Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].STOREMatrix.Matrix;

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].QNetAngles.y);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);

			Qpo->Transform_GetLeft(&Q_Forge->Forge[AvatarID].AV.Xform, &Q_Forge->Forge[AvatarID].AV.Up);

			Q_Forge->Forge[AvatarID].AV.Up.y = 0;
			Q_Forge->Forge[AvatarID].AnglesVec.y = 0;

			Qpo->Vec3d_Subtract(&Q_Forge->Forge[AvatarID].AV.Up, &Q_Forge->Forge[AvatarID].AnglesVec, &ScanTurnVec);
			Q_Forge->Forge[AvatarID].ScanTurnAng = Qpo->Vec3d_Length(&ScanTurnVec);
			Q_Forge->Forge[AvatarID].ScanTurnAng /= 3; //2

			//### Check Distance between Pure Left and Right to work out direction of Turn
			//QpoVec3d f_UPP, LeftToRightESCAN;
			//f_UPP.x = 0;
			//f_UPP.y = 1;
			//f_UPP.z = 0;
			//Qpo->Vec3d_CrossProduct(&Q_Forge->Forge[AvatarID].AnglesVec, &f_UPP, &LeftToRightESCAN);

			Qpo->Transform_GetUp(&Q_Forge->Forge[AvatarID].AV.Xform, &LeftToRightESCAN);

			LeftToRightESCAN.y = 0;

			Qpo->Vec3d_Copy(&LeftToRightESCAN, &Q_Forge->Forge[AvatarID].AV.Left);
			Qpo->Vec3d_Copy(&LeftToRightESCAN, &Q_Forge->Forge[AvatarID].AV.Right);
			Qpo->Vec3d_Inverse(&Q_Forge->Forge[AvatarID].AV.Right);

			ScanDistL = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].AnglesVec, &Q_Forge->Forge[AvatarID].AV.Left);
			ScanDistR = Qpo->Vec3d_DistanceBetween(&Q_Forge->Forge[AvatarID].AnglesVec, &Q_Forge->Forge[AvatarID].AV.Right);

#if 0
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.z;
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.y;
			TempVec2.x = Q_Forge->Forge[AvatarID].AV.Xform.Translation.z;

	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Left.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Left.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Left.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
	glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Right.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Right.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Right.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(0.0f, 0.0f, 1.0f);	//BLUE
	glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AnglesVec.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AnglesVec.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AnglesVec.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 1.0f, 1.0f);	//BLUE
	glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (ScanTurnVec.x * 250), TempVec2.y + (ScanTurnVec.y * 250), TempVec2.z + (ScanTurnVec.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 1.0f);	//BLUE
	glBegin(GL_LINES);
	glVertex3f(TempVec2.x, TempVec2.y, TempVec2.z);
	glVertex3f(TempVec2.x + (Q_Forge->Forge[AvatarID].AV.Up.x * 250), TempVec2.y + (Q_Forge->Forge[AvatarID].AV.Up.y * 250), TempVec2.z + (Q_Forge->Forge[AvatarID].AV.Up.z * 250));
	glEnd();
#endif

			if(ScanDistL < ScanDistR) Q_Forge->Forge[AvatarID].ScanTurnAng *= -1;

			Q_Forge->Forge[AvatarID].trueAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;

			Q_Forge->Forge[AvatarID].Angles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			if(Q_Forge->Forge[AvatarID].Angles.y > (PI*2)) Q_Forge->Forge[AvatarID].Angles.y -= (PI*2);
			if(Q_Forge->Forge[AvatarID].Angles.y < 0) Q_Forge->Forge[AvatarID].Angles.y = (PI*2) - Q_Forge->Forge[AvatarID].Angles.y;

			Q_Forge->Forge[AvatarID].QNetAngles.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			if(Q_Forge->Forge[AvatarID].QNetAngles.y > (PI*2)) Q_Forge->Forge[AvatarID].QNetAngles.y -= (PI*2);
			if(Q_Forge->Forge[AvatarID].QNetAngles.y < 0) Q_Forge->Forge[AvatarID].QNetAngles.y = (PI*2) - Q_Forge->Forge[AvatarID].QNetAngles.y;

			//Q_Forge->Forge[AvatarID].AnglesChg.y += Q_Forge->Forge[AvatarID].ScanTurnAng;
			//if(Q_Forge->Forge[AvatarID].AnglesChg.y > (PI*2)) Q_Forge->Forge[AvatarID].AnglesChg.y -= (PI*2);
			//if(Q_Forge->Forge[AvatarID].AnglesChg.y < 0) Q_Forge->Forge[AvatarID].AnglesChg.y += (PI*2);

			//Q_Forge->Forge[AvatarID].AV.Xform.Matrix = Q_Forge->Forge[AvatarID].AV.STR_Xform.Matrix;

			Qpo->Transform_New_YRotation(&AIfriendly, Q_Forge->Forge[AvatarID].ScanTurnAng);
			Qpo->Transform_Multiply(&Q_Forge->Forge[AvatarID].AV.Xform, &AIfriendly, &Q_Forge->Forge[AvatarID].AV.Xform);














	

	//This certainly has a performance and memory profile effect and thus should be used
	//only in non-production builds.
#pragma message("'Performance Inhibitor' used :::DigiMassCore::acInitContained:::recordMemoryAllocations")
	bool recordMemoryAllocations = true;
	const bool useCustomTrackingAllocator = true;

	initSampleAllocator();

	PxAllocatorCallback* allocator = &gDefaultAllocatorCallback;

	if (useCustomTrackingAllocator)		
		allocator = getSampleAllocator();		//optional override that will track memory allocations

	PxTolerancesScale f_Scale;
	f_Scale.length = 10;
	f_Scale.mass = 0.5;
	f_Scale.speed = 0.1;

	digi_PhysicsSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *allocator, gDefaultErrorCallback, f_Scale, recordMemoryAllocations );
	if(!digi_PhysicsSDK)
		{
		unConsoleAttribute(CONSOLE_ERROR);
		if(m_InternalMsgLvl == 1 || m_InternalMsgLvl == 3) printf("ERROR:::DigiMassCore:::acInitContained PxCreatePhysics failed\n");
		if(m_InternalMsgLvl == 2) MessageBox(NULL, "ERROR::: PxCreatePhysics failed", "Digi-Mass:::DigiMassCore:::acInitContained error", MB_OK | MB_ICONEXCLAMATION);
		unConsoleAttribute(CONSOLE_INIT);
		for(;;) {}
		}

	PxFoundation& foundation = digi_PhysicsSDK->getFoundation();

#if 0
	if ( getOrCreateProfileZone(foundation) )
		digi_PhysicsSDK->getProfileZoneManager().addProfileZone(*getProfileZone());
#endif

	if(!PxInitExtensions(*digi_PhysicsSDK))
		{
		unConsoleAttribute(CONSOLE_ERROR);
		if(m_InternalMsgLvl == 1 || m_InternalMsgLvl == 3) printf("ERROR:::DigiMassCore:::acInitContained PxInitExtensions failed\n");
		if(m_InternalMsgLvl == 2) MessageBox(NULL, "ERROR::: PxInitExtensions failed", "Digi-Mass:::DigiMassCore:::acInitContained error", MB_OK | MB_ICONEXCLAMATION);
		unConsoleAttribute(CONSOLE_INIT);
		for(;;) {}
		}

	// Initialize cooking library
	acInitCooking();

#if 0
	if(digi_PhysicsSDK->getPvdConnectionManager())
		{
		if (digi_PhysicsSDK->getPvdConnectionManager()->getCurrentConnection())
			digi_PhysicsSDK->getPvdConnectionManager()->disconnect();
		else
			createPvdConnection();
		}

	if(digi_PhysicsSDK->getPvdConnectionManager())
		digi_PhysicsSDK->getPvdConnectionManager()->addHandler(this);
#endif

	bool f_CreateCudaCtxManager = false;

	if (f_CreateCudaCtxManager)
		{
#ifdef PX_WINDOWS
		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
		m_CudaContextManager = pxtask::createCudaContextManager(cudaContextManagerDesc);
#endif
		}

#ifdef PX_PS3
	PxGetPS3Extension().initSDK(5);
#endif

	PxSceneDesc sceneDesc(digi_PhysicsSDK->getTolerancesScale());

	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

#if 0
	customizeSceneDesc(sceneDesc);
#endif

#if defined(PX_PS3)
	int f_NbThreads = 1;
#elif defined(PX_X360)
	int f_NbThreads = 3;
#else
	int f_NbThreads = 4;
#endif

	if(!sceneDesc.cpuDispatcher)
		{
		m_CpuDispatcher = PxDefaultCpuDispatcherCreate(f_NbThreads);

		if(!m_CpuDispatcher)
			{
			unConsoleAttribute(CONSOLE_ERROR);
			if(m_InternalMsgLvl == 1 || m_InternalMsgLvl == 3) printf("ERROR:::DigiMassCore:::acInitContained PxDefaultCpuDispatcherCreate failed\n");
			if(m_InternalMsgLvl == 2) MessageBox(NULL, "ERROR::: PxDefaultCpuDispatcherCreate failed", "Digi-Mass:::DigiMassCore:::acInitContained error", MB_OK | MB_ICONEXCLAMATION);
			unConsoleAttribute(CONSOLE_INIT);
			for(;;) {}
			}

		sceneDesc.cpuDispatcher	= m_CpuDispatcher;
		}

	if(!sceneDesc.filterShader)
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;

#if 0
#ifdef PX_WINDOWS
	if(!sceneDesc.gpuDispatcher && m_CudaContextManager)
		{
		sceneDesc.gpuDispatcher = m_CudaContextManager->getGpuDispatcher();
		}
#endif
#endif

	digi_Scene = digi_PhysicsSDK->createScene(sceneDesc);

	if (!digi_Scene)
		{
		unConsoleAttribute(CONSOLE_ERROR);
		if(m_InternalMsgLvl == 1 || m_InternalMsgLvl == 3) printf("ERROR:::DigiMassCore:::acInitContained createScene failed\n");
		if(m_InternalMsgLvl == 2) MessageBox(NULL, "ERROR::: createScene failed", "Digi-Mass:::DigiMassCore:::acInitContained error", MB_OK | MB_ICONEXCLAMATION);
		unConsoleAttribute(CONSOLE_INIT);
		for(;;) {}
		}

	digi_Scene->setVisualizationParameter(PxVisualizationParameter::eSCALE,	false ? 1.0f : 0.0f);
	digi_Scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	// setup default material...
	mMaterial = digi_PhysicsSDK->createMaterial(0.5f, 0.5f, 0.1f);
	if(!mMaterial)
		{
		unConsoleAttribute(CONSOLE_ERROR);
		if(m_InternalMsgLvl == 1 || m_InternalMsgLvl == 3) printf("ERROR:::DigiMassCore:::acInitContained createMaterial failed\n");
		if(m_InternalMsgLvl == 2) MessageBox(NULL, "ERROR::: createMaterial failed", "Digi-Mass:::DigiMassCore:::acInitContained error", MB_OK | MB_ICONEXCLAMATION);
		unConsoleAttribute(CONSOLE_INIT);
		for(;;) {}
		}

	//Renderer* renderer = getRenderer();
	//SampleAssetManager* assetManager = getAssetManager();
	//m_DebugRenderer = SAMPLE_NEW(RenderPhysX3Debug)(*renderer, *assetManager);

	//PxU32 clientWidth, clientHeight;
	//renderer->getWindowSize(clientWidth, clientHeight);

	//updateCameraViewport(clientWidth, clientHeight);

	// Create managed materials
	/*{
		const PxReal c = 0.75f;
		const PxReal opacity = 1.0f;
		const bool doubleSided = false;
		const PxU32 id = 0xffffffff;

		mManagedMaterials[MATERIAL_GREY]	= SAMPLE_NEW(RenderMaterial)(*renderer, PxVec3(0.5f, 0.5f, 0.5f),	opacity, doubleSided, id, NULL);
		mManagedMaterials[MATERIAL_RED]		= SAMPLE_NEW(RenderMaterial)(*renderer, PxVec3(c, 0.0f, 0.0f),		opacity, doubleSided, id, NULL);
		mManagedMaterials[MATERIAL_GREEN]	= SAMPLE_NEW(RenderMaterial)(*renderer, PxVec3(0.0f, c, 0.0f),		opacity, doubleSided, id, NULL);
		mManagedMaterials[MATERIAL_BLUE]	= SAMPLE_NEW(RenderMaterial)(*renderer, PxVec3(0.0f, 0.0f, c),		opacity, doubleSided, id, NULL);
		mManagedMaterials[MATERIAL_YELLOW]	= SAMPLE_NEW(RenderMaterial)(*renderer, PxVec3(c, c, 0.0f),			opacity, doubleSided, id, NULL);

		mRenderMaterials.push_back(mManagedMaterials[MATERIAL_GREY]);
		mRenderMaterials.push_back(mManagedMaterials[MATERIAL_RED]);
		mRenderMaterials.push_back(mManagedMaterials[MATERIAL_GREEN]);
		mRenderMaterials.push_back(mManagedMaterials[MATERIAL_BLUE]);
		mRenderMaterials.push_back(mManagedMaterials[MATERIAL_YELLOW]);
	}*/

	/*RendererDirectionalLightDesc lightdesc;
	lightdesc.intensity = 1;

	lightdesc.color     = RendererColor(250, 250, 250, 255);
	lightdesc.direction = PxVec3(-0.707f, -0.707f, -0.707f);
	mLights.push_back(renderer->createLight(lightdesc));

	lightdesc.color     = RendererColor(50, 50, 100, 255);
	lightdesc.direction = PxVec3( 0.707f, -0.707f,  0.707f);
	mLights.push_back(renderer->createLight(lightdesc));*/

	//renderer->initTexter();
	//renderer->initScreenquad();

#if 0
	PxReal xpos = 120;
	PxReal ypos = 2.0f;
	PxReal zdist = 5.0f;
	PxReal zpos = 10.f;

	createCarWithDesc(PxVec3(xpos,ypos,zpos + zdist * 0), true, false, false, false, false, digi_PhysicsSDK);//"1 - normal fw car\n"
	//createCarWithDesc(PxVec3(xpos,ypos,zpos + zdist * 1), true, false, false, false, true, digi_PhysicsSDK);//old style "1 - normal fw car\n"
	createCarWithDesc(PxVec3(xpos,ypos,zpos + zdist * 1), false, true, true, false, false, digi_PhysicsSDK);//corvette rw
	createCart		 (PxVec3(xpos,ypos,zpos + zdist * 2), false, true, false);//cart rw
	createCarWithDesc(PxVec3(xpos,ypos,zpos + zdist * 3), true, true, false, true, false, digi_PhysicsSDK);//old style box style monster truck, 4x4
	createTruckPuller(PxVec3(xpos, ypos, zpos + zdist * 4), 10, false);			//truck
	createFullTruck(PxVec3(xpos, ypos, zpos + zdist * 6), 32, false, false);	//full truck
	createFullTruck(PxVec3(xpos, ypos, zpos + zdist * 7), 32, true, false);		//full truck 4 axis
	createTruckWithTrailer1(PxVec3(xpos-50, ypos, zpos + zdist * 3),15, false);	//truck w trailer
	createFullTruckWithTrailer2(PxVec3(xpos-50, ypos, zpos + zdist * 5), 16, false);//full truck 4 axis w trailer

	PxAllVehicles::selectNext();
	PxAllVehicles::selectNext();	//select 1st car.
#endif

#if 0
	PxRigidActor* rodPivoty = CreateBoneSphere(PxVec3(-0.870032, 0.881602, 63.461063), PxMat33(PxVec3(-0.870032, 0.881602, 63.461063), PxVec3(0.000000, 1.000000, 0.000000), PxVec3(0.000000, 0.000000, 1.000000)), 7.670390, 10.000000, PxVec3(3.289997, 0.000000, 0.000000), PxMat33(PxVec3(1.000000, 0.000000, 0.000000), PxVec3(0.000000, 1.000000, 0.000000), PxVec3(0.000000, 0.000000, 1.000000)));
	PxRigidActor* wheelPivot = CreateBoneBox(PxVec3(-0.870061, 0.885579, 41.578762), PxMat33(PxVec3(0.000001, -0.000002, 1.000000), PxVec3(-0.000798, -1.000000, -0.000002), PxVec3(1.000000, -0.000798, -0.000001)), PxVec3(4.528068, 1.903659, 1.234290), 10.000000, PxVec3(7.560078, 0.535133, 0.000000));
#else
	//PxRigidActor* rodPivoty = CreateBoneSphere(PxVec3(-0.870032, 0.881602, 63.461063), PxMat33(PxVec3(-0.870032, 0.881602, 63.461063), PxVec3(0.000000, 1.000000, 0.000000), PxVec3(0.000000, 0.000000, 1.000000)), 7.670390, 10.000000, PxVec3(3.289997, 0.000000, 0.000000), PxMat33(PxVec3(1.000000, 0.000000, 0.000000), PxVec3(0.000000, 1.000000, 0.000000), PxVec3(0.000000, 0.000000, 1.000000)));
	//PxRigidActor* wheelPivot = CreateBoneBox(PxVec3(-0.870061, 0.885579, 41.578762), PxMat33(PxVec3(0.000001, -0.000002, 1.000000), PxVec3(-0.000798, -1.000000, -0.000002), PxVec3(1.000000, -0.000798, -0.000001)), PxVec3(4.528068, 1.903659, 1.234290), 10.000000, PxVec3(7.560078, 0.535133, 0.000000));
#endif

	// Joint
	/*PxSphericalJointDesc sphericalDesc(digi_PhysicsSDK->getTolerancesScale());
	sphericalDesc.actor[0] = rodPivoty;
	sphericalDesc.actor[1] = wheelPivot;
	sphericalDesc.setGlobalPose(PxTransform(PxVec3(0,0,0), PxQuat(0,1,0,0)));*/

	/*sphericalDesc.flags |= NX_SJF_TWIST_LIMIT_ENABLED;
	sphericalDesc.twistLimit.low.value = -(PxReal)0.025*PxPi;
	sphericalDesc.twistLimit.low.hardness = 0.5;
	sphericalDesc.twistLimit.low.restitution = 0.5;
	sphericalDesc.twistLimit.high.value = (PxReal)0.025*PxPi;
	sphericalDesc.twistLimit.high.hardness = 0.5;
	sphericalDesc.twistLimit.high.restitution = 0.5;

	sphericalDesc.flags |= NX_SJF_SWING_LIMIT_ENABLED;
	sphericalDesc.swingLimit.value = (PxReal)0.25*PxPi;
	sphericalDesc.swingLimit.hardness = 0.5;
	sphericalDesc.swingLimit.restitution = 0.5;

	sphericalDesc.flags |= NX_SJF_TWIST_SPRING_ENABLED;
	sphericalDesc.twistSpring.spring = 0.5;
	sphericalDesc.twistSpring.damper = 1;

	sphericalDesc.flags |= NX_SJF_SWING_SPRING_ENABLED;
	sphericalDesc.swingSpring.spring = 0.5;
	sphericalDesc.swingSpring.damper = 1;

	sphericalDesc.projectionDistance = (PxReal)0.15;
	sphericalDesc.projectionMode = NX_JPM_POINT_MINDIST;

	digi_Scene->createJoint(sphericalDesc);*/

	PxReal d = 0.0f;
	PxU32 axis = 1;
	PxTransform pose;

	if(axis == 0)
		pose = PxTransform(PxVec3(d, 0.0f, 0.0f));
	else if(axis == 1)
		pose = PxTransform(PxVec3(0.0f, d, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	else if(axis == 2)
		pose = PxTransform(PxVec3(0.0f, 0.0f, d), PxQuat(-PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));

	PxRigidStatic* plane = digi_PhysicsSDK->createRigidStatic(pose);
	PxShape* shape = plane->createShape(PxPlaneGeometry(), *mMaterial);
	digi_Scene->addActor(*plane);

	// Initialization Complete set internal state
	m_InternalState = 1;

return true;