//********************************************************
//********************************************************
//**	Q-Input.c										**
//**	Author	-Max Lawlor								**
//**													**
//**	Input Control									**
//**								Quantum Angel		**
//**								Copyright 2006		**
//********************************************************
//********************************************************


//##### -+ Input Stages +- #####

void QNETWORKQ_Netplayer->NetplayerControl(int AIcounter, int NetPlayID)
	{

//**********************************************************************************************************
//**********************************************************************************************************
// KEYBOARD AND MOUSE INPUT ********************************************************************************


	//*----KeyBoard INput Stage One----*


		//# Reset for Key Logger
	/*if(TIME > Q_Forge->Forge[AIcounter].KL_Timer + 20)
		{
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;
		}

		//# Reset for Block Key Logger
	if(TIME > Q_Forge->Forge[AIcounter].KL_BTimer + 3)
		{
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_BTFSpecLevel = 0;
		}*/


	//### Click Logger - For Special Attacks
	/*if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSRightButton == 1)
		{
		Q_Forge->Forge[AIcounter].KL_CLogC++;
		Q_Forge->Forge[AIcounter].KL_CLogTimer = TIME;
		}

	if(Q_Forge->Forge[AIcounter].KL_CLogC >= 3)
		{
		Q_Forge->Forge[AIcounter].KL_CSpecial = 1;
		}
	else Q_Forge->Forge[AIcounter].KL_CSpecial = 0;


		//# Reset for Click Logger
	if(TIME > Q_Forge->Forge[AIcounter].KL_CLogTimer + 10) Q_Forge->Forge[AIcounter].KL_CLogC = 0;*/


	//### Key Logger - For Air Jink
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORMouseWheel)
		{
		Q_Forge->Forge[AIcounter].AirJinkLOGFT++;

		if(Q_Forge->Forge[AIcounter].Mposestate == 15 && Q_Forge->Forge[AIcounter].jumpposecnt >= 0.2)
			{ Q_Forge->Forge[AIcounter].jumpposecnt = 0.2; }
		}

	if(Q_Forge->Forge[AIcounter].AirJinkLOGFT > 2)
		{
		Q_Forge->Forge[AIcounter].AirJinkLOGFT = 0;

		if(Q_Forge->Forge[AIcounter].Mposestate == 14)
			{
			Q_Forge->Forge[AIcounter].jumpposecnt = 0;
			Q_Forge->Forge[AIcounter].blendamount[48] = 0;
			Q_Forge->Forge[AIcounter].blendamount[0] = 0;
			Q_Forge->Forge[AIcounter].Mposestate = 15;
			Q_Forge->Forge[AIcounter].TrailsCount = 0;

			Q_Forge->Forge[AIcounter].GravityON = 1;
			}
		}


	if(Q_Forge->Forge[AIcounter].Mposestate == 14 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySPACE)
		{
		geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].JumpVec);
		geVec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);
		Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump
		Q_Forge->Forge[AIcounter].JumpFG = 0;
		Q_Forge->Forge[AIcounter].Mposestate = 11;		//# Switch to normal leap
		Q_Forge->Forge[AIcounter].jumpposecnt = 0.35;
		Q_Forge->Forge[AIcounter].blendamount[4] = 0;
		Q_Forge->Forge[AIcounter].AirJinkRotFG = 0;
		Q_Forge->Forge[AIcounter].GravityON = 0;
		}


//START PLAYER MODE - WALKING
if(Q_Forge->Forge[AIcounter].PlayerMode == 0)
	{

	//*----Mouse Input----*

	//##### --- ENERGY ARCHITECT BUILD MODE --- #####
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton == 1 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel > 5 && Q_Forge->Forge[AIcounter].EnergyArchitect.BuildMODEON == 0 && Q_Forge->Forge[AIcounter].Mposestate != 16)	//Build mode activation
		{
		helly = 0;
		while(helly < 30 && (_->NomPntSprite < Q_PNTSPRITE_MAX))	//TODO ADD CRYSTAL SKILL HERE
			{
			geActor_GetBoneTransform(Q_Forge->Forge[AIcounter].Avatar.Actor, "BIP01 SPINE2", &BoneMat);

			//#### Initialise One Particle ####//
			
			Q_PntSprite->PntSprite[_->NomPntSprite].Type = GE_TEXTURED_POINT;
			Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags =	GE_RENDER_DO_NOT_OCCLUDE_OTHERS;		//GE_RENDER_DEPTH_SORT_BF
			Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.535f;										//1.135//0.1//0.025f//0.002f
			Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 2;

			Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 200;
			Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 28;
			Q_PntSprite->PntSprite[_->NomPntSprite].Pos = BoneMat.Translation;
			Q_PntSprite->PntSprite[_->NomPntSprite].InitPos = BoneMat.Translation;
			Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.X = (((float)rand() / 32767)-0.5);
			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Y = (((float)rand() / 32767)-0.5);
			Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.Z = (((float)rand() / 32767)-0.5);

			Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

			_->NomPntSprite++;
			helly++;
			}

		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;
		Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

		geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
		geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

		Q_Forge->Forge[AIcounter].EnergyArchitect.BuildMODEON = 1;
		}


	//#####	SENTRY BUILD
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton == 1 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1 && Q_Forge->Forge[AIcounter].WeaponStatus == 0 && Q_Forge->Forge[AIcounter].EnergyArchitect.BuildMODEON == 1)	//****////BUILD\\\\****
		{
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;
		Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;
		Q_Forge->Forge[AIcounter].EnergyArchitect.BuildMODEON = 0;

		if(Q_Forge->Forge[AIcounter].EnergyArchitect.ZONING == 1 && Q_Forge->Forge[AIcounter].Mposestate != 16 && Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY != 250)
			{
			//#### INITIALISE ONE SENTRY OBJECT IN THE CORE OF THE CURRENT ZONE

			//### FIND CORE
			geVec3d_Subtract(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Maxs, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core);
			geVec3d_Scale(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core, 0.5, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core);
			geVec3d_Add(&Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Mins, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core, &Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core);

			if(_->NomBMSentry < 148)
				{
				Q_BMSentry->BMSentry[_->NomBMSentry].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core;
				Q_BMSentry->BMSentry[_->NomBMSentry].ZoneID = Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE;
				Q_BMSentry->BMSentry[_->NomBMSentry].QObjID = _->NomQObject;
				Q_BMSentry->BMSentry[_->NomBMSentry].Range = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].ExpandSTRENGTH;
				Q_BMSentry->BMSentry[_->NomBMSentry].Damage = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].Damage;
				Q_BMSentry->BMSentry[_->NomBMSentry].Power = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].Power;
				Q_BMSentry->BMSentry[_->NomBMSentry].FireRate = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].FireRate;
				Q_BMSentry->BMSentry[_->NomBMSentry].Accuracy = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].Accuracy;
				Q_BMSentry->BMSentry[_->NomBMSentry].BulletCNT = Q_Forge->Forge[AIcounter].CharDATA.ItemDATA[Q_Forge->Forge[AIcounter].CharDATA.CurrZSENTRY].BulletCNT;

				if(_->NetworkOption == 2)
					{
					Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].TYPE = 0;
					Q_NetZoneENTITY->NetZoneENTITY[_->NomNetZoneENTITY].ID = _->NomBMSentry;
					_->NomNetZoneENTITY++;
					}

				_->NomBMSentry++;
				}

			//#### INITIALISE THE Q_Object->Object TO HOUSE THE SENTRY

			if(_->NomQObject < 148)
				{
				Q_Object->Object[_->NomQObject].Pos = Q_EnergyMatrix->EnergyMatrix.QMATBlock[Q_Forge->Forge[AIcounter].EnergyArchitect.WithinZONE].Core;
				Q_Object->Object[_->NomQObject].Scale = 65;
				Q_Object->Object[_->NomQObject].StrengthMAX = 1500;
				Q_Object->Object[_->NomQObject].StrengthBANK = Q_Object->Object[_->NomQObject].StrengthMAX;
				Q_Object->Object[_->NomQObject].CollisionTYPE = 0;
				Q_Object->Object[_->NomQObject].AvatarID = 250;
				Q_Object->Object[_->NomQObject].LIVE = 1;

				_->NomQObject++;
				}

			geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
							//'Jink Ready'
			geSound_PlaySoundDef(SoundSys, Medias->S_Build, _->Volume, _->Pan, _->S_TimeScale, GE_false);

			Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 5;
			}
		else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
		}


		//##### First Automatic Attacks
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_BTFSpecLevel == 1 && Q_Forge->Forge[AIcounter].Aposestate != 63 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Mposestate != 16)		//### Deflect Attack
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
		Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_BTFSpecLevel = 0;

		Q_Forge->Forge[AIcounter].attposecnt = 0;
		Q_Forge->Forge[AIcounter].Aposestate = 0;
		Q_Forge->Forge[AIcounter].blendamount[0] = 0;
		Q_Forge->Forge[AIcounter].blendamount[98] = 0;
		Q_Forge->Forge[AIcounter].TrailsOn = 0;
		Q_Forge->Forge[AIcounter].attackon = 0;

		Q_Forge->Forge[AIcounter].astackcntdir[0]++;
		Q_Forge->Forge[AIcounter].astackcnt++;

		geSound3D_GetConfig(World,
			&player[g_Player]->ViewXForm,
			&Q_Forge->Forge[AIcounter].RFistPos.Translation,
			600.0f,
			2.0f,
			&Volume,
			&Pan,
			&Frequency);

			//'Jink'		TODO NEW SOUND
		geSound_PlaySoundDef(SoundSys, Medias->S_BJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

		Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 4;
		}


	//##### Jink status Control
	if(Q_Forge->Forge[AIcounter].Aposestate == 85 || Q_Forge->Forge[AIcounter].Aposestate == 86 || Q_Forge->Forge[AIcounter].Aposestate == 87)
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton == 1)
			{
			Q_Forge->Forge[AIcounter].Aposestate = 86;
			}

		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSRightButton == 1)
			{
			Q_Forge->Forge[AIcounter].Aposestate = 87;
			}
		}


	/*if(Q_Forge->Forge[AIcounter].JinkSpecialON == 1)
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1) Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 2;
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 1) Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 2;
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 1) Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 2;
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 1) Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 2;
		}*/


		//##### Mouse Activated Attacks
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton == 1 && Q_Forge->Forge[AIcounter].WeaponStatus == 0 && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 16))	//****////PUNCHS\\\\****
		{
		if(Q_Forge->Forge[AIcounter].astackcnt <= 6)
			{

			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ == 0)
				{
				noot=0;

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW)	//FORWARD ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].Running == 1) //Running
						{
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].RunningCount = 0;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 46;
						}
					else
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 67;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 67;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 67;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 67;
						}

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;
					}
				else noot++;

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS)	//BACKWARD ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 17;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 71;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 71;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 17;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 71;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 17;

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;
					}
				else noot++;

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA)	//LEFT ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 69;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 69;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;
					}
				else noot++;

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD)	//RIGHT ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 70;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 70;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 70;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 10;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 70;

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;
					}
				else noot++;

				if(noot == 4)		//STILL ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 1;

					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 12;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 13;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 9;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 8;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 67;

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;
					//if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					}

				Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackcnt] = 0;
				}
			else		//Low Attacks
				{
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 48;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 47;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 68;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 68;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 48;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 47;
				if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 68;

				Q_Forge->Forge[AIcounter].astackcntdir[0]++;
				Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackcnt] = 0;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 1)		//### SkyPush
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 25 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 25;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 58;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[72] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 1)		//### Flame Uppercut
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 32;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 4;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}

			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 2)		//### P - Combo - 2
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 175;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 64;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 2)		//### Cyclone Kick
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 200;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 84;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 2)		//### JS RUSH PUNCH
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 175 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 175;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 85;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[119] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 1)		//### Air Dash to ground
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 30;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 53;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].Mposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[86] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					Q_Forge->Forge[AIcounter].JumpFG = 0;
					Q_Forge->Forge[AIcounter].jumpposecnt=0;
					Q_Forge->Forge[AIcounter].blendamount[4]=0;
					Q_Forge->Forge[AIcounter].Mposestate = 0;
					Q_Forge->Forge[AIcounter].AJPushOffON = 0;
					Q_Forge->Forge[AIcounter].Running = 0;
					Q_Forge->Forge[AIcounter].AirBorn = 0;
					Q_Forge->Forge[AIcounter].TimeHoleFLAG = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 2)		//Jink Special Flame Uppercut
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 240 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 240;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 57;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 4;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[55] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1)		//Rush Elbow
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy > 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 30;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 65;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[102] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

						//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}

			Q_Forge->Forge[AIcounter].astackcnt++;
			}
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSRightButton == 1 && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 16))	//****////KICKS\\\\****
		{
		if(Q_Forge->Forge[AIcounter].astackcnt < 6)
			{

			if(Q_Forge->Forge[AIcounter].WeaponStatus == 0)
				{
				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ == 0)		//Check for low attack
					{
					noot=0;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW)	//FORWARD ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

						if(Q_Forge->Forge[AIcounter].AirBorn == 1) //AirBorn
							{
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;

							Q_Forge->Forge[AIcounter].JumpFG = 0;
							Q_Forge->Forge[AIcounter].jumpposecnt=0;
							Q_Forge->Forge[AIcounter].blendamount[4]=0;
							Q_Forge->Forge[AIcounter].AJPushOffON = 0;
							Q_Forge->Forge[AIcounter].Running = 0;
							Q_Forge->Forge[AIcounter].AirBorn = 0;
							Q_Forge->Forge[AIcounter].TimeHoleFLAG = 0;
							if(Q_Forge->Forge[AIcounter].Mposestate != 9) Q_Forge->Forge[AIcounter].Mposestate = 0;
							}
						else
							{
							if(Q_Forge->Forge[AIcounter].Running == 1) //Running
								{
								Q_Forge->Forge[AIcounter].Running = 0;
								Q_Forge->Forge[AIcounter].RunningCount = 0;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
								}
							else
								{
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 27;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 27;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
								if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 27;
								}
							}

						Q_Forge->Forge[AIcounter].astackcntdir[0]++;
						}
					else noot++;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS)	//BACKWARD ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

						if(Q_Forge->Forge[AIcounter].AirBorn == 1) //AirBorn
							{
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 45;

							Q_Forge->Forge[AIcounter].JumpFG = 0;
							Q_Forge->Forge[AIcounter].jumpposecnt=0;
							Q_Forge->Forge[AIcounter].blendamount[4]=0;
							Q_Forge->Forge[AIcounter].Mposestate = 0;
							Q_Forge->Forge[AIcounter].AJPushOffON = 0;
							Q_Forge->Forge[AIcounter].Running = 0;
							Q_Forge->Forge[AIcounter].AirBorn = 0;
							Q_Forge->Forge[AIcounter].TimeHoleFLAG = 0;
							}
						else
							{
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 37;
							}

						Q_Forge->Forge[AIcounter].astackcntdir[0]++;
						}
					else noot++;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA)	//LEFT ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;

						Q_Forge->Forge[AIcounter].astackcntdir[0]++;
						}
					else noot++;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD)	//RIGHT ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 21;

						Q_Forge->Forge[AIcounter].astackcntdir[0]++;
						}
					else noot++;

					if(noot == 4)		//STILL ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 1;

						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 11;	//EDIT 37
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 38;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 39;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 40;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 33;

						Q_Forge->Forge[AIcounter].astackcntdir[0]++;
						//if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						}

					Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackcnt] = 0;
					}
				else		//Low Attacks
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 43;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 72;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 72;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 72;
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS)	//BACKWARD ATTACKS
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 44;
						}

					Q_Forge->Forge[AIcounter].astackcntdir[0]++;

					Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackcnt] = 0;
					}

				} //END Weapon Check
			else
				{
				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW)	//FORWARD ATTACKS
					{
					if(Q_Forge->Forge[AIcounter].astackcntdir[0] > 6) Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;

					if(Q_Forge->Forge[AIcounter].AirBorn == 1) //AirBorn
						{
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;
						if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 24;

						Q_Forge->Forge[AIcounter].JumpFG = 0;
						Q_Forge->Forge[AIcounter].jumpposecnt=0;
						Q_Forge->Forge[AIcounter].blendamount[4]=0;
						Q_Forge->Forge[AIcounter].Mposestate = 0;
						Q_Forge->Forge[AIcounter].AJPushOffON = 0;
						Q_Forge->Forge[AIcounter].Running = 0;
						Q_Forge->Forge[AIcounter].AirBorn = 0;
						Q_Forge->Forge[AIcounter].TimeHoleFLAG = 0;
						}
					else
						{
						if(Q_Forge->Forge[AIcounter].Running == 1) //Running
							{
							Q_Forge->Forge[AIcounter].Running = 0;
							Q_Forge->Forge[AIcounter].RunningCount = 0;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 1) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 2) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 3) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 4) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 5) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							if(Q_Forge->Forge[AIcounter].astackcntdir[0] == 6) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 77;
							}
						}
					}
				}


			//### Hyper Knee Flex
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 2 && Q_Forge->Forge[AIcounter].AirBorn == 0)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 35;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 4;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 2)	//JSRUSH
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 73;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[73] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 2)	//JSRUSHUP
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 40 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;
					if(Q_Forge->Forge[AIcounter].Aposestate != 76)
						{
						Q_Forge->Forge[AIcounter].astackcnt = 0;
						Q_Forge->Forge[AIcounter].astackrun = 0;
						Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
						Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 76;
						Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;

						Q_Forge->Forge[AIcounter].SpecLvlRESET = 3;

						Q_Forge->Forge[AIcounter].attposecnt = 0;
						Q_Forge->Forge[AIcounter].Aposestate = 0;
						Q_Forge->Forge[AIcounter].blendamount[0] = 0;
						Q_Forge->Forge[AIcounter].blendamount[73] = 0;
						Q_Forge->Forge[AIcounter].TrailsOn = 0;
						Q_Forge->Forge[AIcounter].attackon = 0;
						Q_Forge->Forge[AIcounter].ShadowsOn = 1;
						Q_Forge->Forge[AIcounter].blendamount[0] = 0;
						}
					else Q_Forge->Forge[AIcounter].AttackPos = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### Very Heavy Kick
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 1)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 35;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 4;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### Sakurat
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 2 && (Q_Forge->Forge[AIcounter].AirBorn == 1 || Q_Forge->Forge[AIcounter].WallRun == 1))
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 56;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 4;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[55] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].DownSpeed = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### RHKick
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 1)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 30 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 31;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 3;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[31] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//Leap Spin Kick
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 22;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[30] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### Static Kick
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 2 && Q_Forge->Forge[AIcounter].AirBorn == 0 && Q_Forge->Forge[AIcounter].WallRun == 0)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 200 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 75;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[122] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### Spin Kick Full Rotation
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 2 && Q_Forge->Forge[AIcounter].AirBorn == 1)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 170 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 170 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 34;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[34] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			//### Twist Kick
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 1)
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;

					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 61;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 2;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}

			Q_Forge->Forge[AIcounter].astackcnt++;
			}
		}

		//****////ENERGY\\\\****
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton == 1 && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 16))
		{
		if(Q_Forge->Forge[AIcounter].astackcnt < 6)
			{
			noot=0;

			if((Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1) && (Q_Forge->Forge[AIcounter].Aposestate == 45) && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0))		//Att Flip Renzou
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 100 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 100 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 5;

					Q_Forge->Forge[AIcounter].Aposestate = 93;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1 && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0))		//Renzou
				{
				if((Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff) && (_->NomSEnergy < _->MaxNomSEnergy))
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 19;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if((Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 2 && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0)) && (_->NomLEnergy < _->MaxNomLEnergy))		//Hadou-Ken
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 50;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 1;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[84] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 2 && (Q_Forge->Forge[AIcounter].AirBorn == 1 || Q_Forge->Forge[AIcounter].WallRun == 1) && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0))		//Power-Bomb
				{
				if((Q_Forge->Forge[AIcounter].HB_Energy >= 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff) && (_->NomLEnergy < _->MaxNomLEnergy))
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 150 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 78;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 3;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[127] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 1 && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0))		//Brolly Tribute
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 110 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 110 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;
					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 60;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;

					Q_Forge->Forge[AIcounter].SpecLvlRESET = 3;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[91] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World,
								&player[g_Player]->ViewXForm,
								&Q_Forge->Forge[AIcounter].RFistPos.Translation,
								600.0f,
								2.0f,
								&Volume,
								&Pan,
								&Frequency);

					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1 && Q_Forge->Forge[AIcounter].CharDATA.Class == 2)		//Cleric Heal
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= (15 + (100 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[1].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= (15 + (100 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[1].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 200;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 3;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 1 && Q_Forge->Forge[AIcounter].CharDATA.Class == 2)		//Cleric Plasma
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= (20 + (150 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[2].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= (20 + (150 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[2].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					Q_Forge->Forge[AIcounter].Aposestate = 204;
					Q_Forge->Forge[AIcounter].attackon = 1;
					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attposecnt = 1.39;
					Q_Forge->Forge[AIcounter].attackprog = 0;
					Q_Forge->Forge[AIcounter].collide = 0;
					Q_Forge->Forge[AIcounter].AttackSoundTRIG = 0;
					Q_Forge->Forge[AIcounter].AttackSoundINITTRIG = 0;
					Q_Forge->Forge[AIcounter].AttackPos = 0;
					Q_Forge->Forge[AIcounter].attackhitRcount = 0;

					Q_Forge->Forge[AIcounter].EnergyDisplayLock = 0;
					Q_Forge->Forge[AIcounter].EnergyDisplayAlpha = 80;
					Q_Forge->Forge[AIcounter].EnergyDisplayColor = 255;
					Q_Forge->Forge[AIcounter].EnergyDisplayScale = 0.22;
					Q_Forge->Forge[AIcounter].EnergyTargetLock = 0;
					Q_Forge->Forge[AIcounter].EnergyLockID = 0;
					Q_Forge->Forge[AIcounter].EnergyCloseDist = 0;
					Q_Forge->Forge[AIcounter].EnergyCloseID = 0;
					Q_Forge->Forge[AIcounter].EnergyTargetLaserAlpha = 0;
					Q_Forge->Forge[AIcounter].EnergyInitialise = 0;
					Q_Forge->Forge[AIcounter].AirBorn = 0;

					//### CANCELLATION
					Q_Forge->Forge[AIcounter].Cleric.HSparkInit = 0;
					Q_Forge->Forge[AIcounter].JinkSpecialON = 0;
					Q_Forge->Forge[AIcounter].DeflectLethal = 0;
					Q_Forge->Forge[AIcounter].HitLethal = 0;
					Q_Forge->Forge[AIcounter].JinkInit = 0;
					Q_Forge->Forge[AIcounter].HoldBack = 0;
					Q_Forge->Forge[AIcounter].Flip = 0;
					Q_Forge->Forge[AIcounter].HB_DmgSTORE = 0;
					Q_Forge->Forge[AIcounter].WindWake = 0;
					Q_Forge->Forge[AIcounter].TrailINIT = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 3;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 1 && Q_Forge->Forge[AIcounter].CharDATA.Class == 2)		//Cleric Offensive Plasma
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= (20 + (150 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[3].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= (20 + (150 * (1 - (Q_Forge->Forge[AIcounter].CharDATA.CLSClericSKILL[3].Cost / 5000)))) / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					Q_Forge->Forge[AIcounter].Aposestate = 207;
					Q_Forge->Forge[AIcounter].attackon = 1;
					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attposecnt = 1.39;
					Q_Forge->Forge[AIcounter].attackprog = 0;
					Q_Forge->Forge[AIcounter].collide = 0;
					Q_Forge->Forge[AIcounter].AttackSoundTRIG = 0;
					Q_Forge->Forge[AIcounter].AttackSoundINITTRIG = 0;
					Q_Forge->Forge[AIcounter].AttackPos = 0;
					Q_Forge->Forge[AIcounter].attackhitRcount = 0;

					Q_Forge->Forge[AIcounter].EnergyDisplayLock = 0;
					Q_Forge->Forge[AIcounter].EnergyDisplayAlpha = 80;
					Q_Forge->Forge[AIcounter].EnergyDisplayColor = 255;
					Q_Forge->Forge[AIcounter].EnergyDisplayScale = 0.22;
					Q_Forge->Forge[AIcounter].EnergyTargetLock = 0;
					Q_Forge->Forge[AIcounter].EnergyLockID = 0;
					Q_Forge->Forge[AIcounter].EnergyCloseDist = 0;
					Q_Forge->Forge[AIcounter].EnergyCloseID = 0;
					Q_Forge->Forge[AIcounter].EnergyTargetLaserAlpha = 0;
					Q_Forge->Forge[AIcounter].EnergyInitialise = 0;
					Q_Forge->Forge[AIcounter].AirBorn = 0;

					//### CANCELLATION
					Q_Forge->Forge[AIcounter].Cleric.HSparkInit = 0;
					Q_Forge->Forge[AIcounter].JinkSpecialON = 0;
					Q_Forge->Forge[AIcounter].DeflectLethal = 0;
					Q_Forge->Forge[AIcounter].HitLethal = 0;
					Q_Forge->Forge[AIcounter].JinkInit = 0;
					Q_Forge->Forge[AIcounter].HoldBack = 0;
					Q_Forge->Forge[AIcounter].Flip = 0;
					Q_Forge->Forge[AIcounter].HB_DmgSTORE = 0;
					Q_Forge->Forge[AIcounter].WindWake = 0;
					Q_Forge->Forge[AIcounter].TrailINIT = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 3;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 1 && Q_Forge->Forge[AIcounter].CharDATA.Class == 2)		//Cleric Energy Grab
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 202;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
						//'Jink Ready'
					geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 3;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(((Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 3) || (Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 3) || (Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 3) || (Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 3)) && (Q_Forge->Forge[AIcounter].CharDATA.Class == 2))		//Cleric Buff Spell 01
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 203;

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 3) Q_Forge->Forge[AIcounter].Cleric.SpellPNTR = 0;
					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel == 3) Q_Forge->Forge[AIcounter].Cleric.SpellPNTR = 1;
					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 3) Q_Forge->Forge[AIcounter].Cleric.SpellPNTR = 2;
					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 3) Q_Forge->Forge[AIcounter].Cleric.SpellPNTR = 3;

					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTLSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel = 0;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[7] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					geSound_PlaySoundDef(SoundSys, Medias->S_CJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);	//'Jink Ready'

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 3;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}


			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 2 && Q_Forge->Forge[AIcounter].CharDATA.Class == 2)		//Cleric Shield
				{
				if(Q_Forge->Forge[AIcounter].HB_Energy >= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
					{
					Q_Forge->Forge[AIcounter].HB_Energy -= 45 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
					Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
					if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					if(Q_Forge->Forge[AIcounter].Cleric.ShieldOn == 0) Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 201;
					else Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 205;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[85] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
					geSound_PlaySoundDef(SoundSys, Medias->S_Jink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

					Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
					}
				else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}

			Q_Forge->Forge[AIcounter].astackcnt++;
			}
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton == 1 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 3 && (Q_Forge->Forge[AIcounter].CharDATA.Class == 0 || (Q_Forge->Forge[AIcounter].CharDATA.Class == 1 && Q_Forge->Forge[AIcounter].WeaponStatus > 0)))	//Fighter Power Up Activation
		{
		if(Q_Forge->Forge[AIcounter].Mposestate == 14)
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 100 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

				Q_Forge->Forge[AIcounter].HB_Energy -= 100 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Forge->Forge[AIcounter].Mposestate = 16;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
				//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].Mposestate == 16)	//### Power up cancellation
				{
				Q_Forge->Forge[AIcounter].KL_RTFSpecLevel = 0;
				Q_Forge->Forge[AIcounter].Mposestate = 14;

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
				}
			else
				{
				if(Q_Forge->Forge[AIcounter].astackcnt < 6 && Q_Forge->Forge[AIcounter].CharDATA.Class == 0)
					{
					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 206;
					Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].blendamount[19] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;
					Q_Forge->Forge[AIcounter].ShadowsOn = 1;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;

					//Q_Jink Cancelator
					Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

					Q_Forge->Forge[AIcounter].astackcnt++;
					}
				}
			}
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton == 1 && (Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 4 || Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_FTRSpecLevel == 4) && Q_Forge->Forge[AIcounter].astackcnt < 6)	//ZONE AFFECT SWITCH ON
		{
		Q_Forge->Forge[AIcounter].astackcnt = 0;
		Q_Forge->Forge[AIcounter].astackrun = 0;
		Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
		Q_Forge->Forge[AIcounter].attackstack[Q_Forge->Forge[AIcounter].astackcnt] = 206;
		Q_Forge->Forge[AIcounter].KL_RTFSpecLevel = 0;

		Q_Forge->Forge[AIcounter].attposecnt = 0;
		Q_Forge->Forge[AIcounter].Aposestate = 0;
		Q_Forge->Forge[AIcounter].blendamount[0] = 0;
		Q_Forge->Forge[AIcounter].blendamount[19] = 0;
		Q_Forge->Forge[AIcounter].TrailsOn = 0;
		Q_Forge->Forge[AIcounter].attackon = 0;
		Q_Forge->Forge[AIcounter].ShadowsOn = 1;
		Q_Forge->Forge[AIcounter].blendamount[0] = 0;

		//Q_Jink Cancelator
		Q_Forge->Forge[AIcounter].Q_Jink.ON = 0;

		//if(Q_Forge->Forge[AIcounter].Ninja.SpeedACT == 1) Q_Forge->Forge[AIcounter].Ninja.SpeedACT = 0;
		//else if(Q_Forge->Forge[AIcounter].Ninja.SpeedACT == 0) Q_Forge->Forge[AIcounter].Ninja.SpeedACT = 1;

		if(Q_Forge->Forge[AIcounter].EnergyArchitect.AffectMatrixON == 1) Q_Forge->Forge[AIcounter].EnergyArchitect.AffectMatrixON = 0;
		else if(Q_Forge->Forge[AIcounter].EnergyArchitect.AffectMatrixON == 0) Q_Forge->Forge[AIcounter].EnergyArchitect.AffectMatrixON = 1;

		Q_Forge->Forge[AIcounter].astackcnt++;
		}


	//##### --- SOLDIER CLASS JINK MOVES --- #####
	if((Q_Forge->Forge[AIcounter].CharDATA.Class == 1) && (Q_Forge->Forge[AIcounter].EnergyArchitect.BuildMODEON == 0) && ((Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton == 1 || Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton == 1) && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 16)))
		{
		//### Damage Upgrades
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 1)		//### Single Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 35 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 1;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}


		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 2)		//### Double Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 130 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 130 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 2;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}


		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel == 3)		//### Triple Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 350 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 350 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_RTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JDamageLVL = 3;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}


		//### Accuracy Upgrades
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 1)		//### Single Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 20 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 20 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 1;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}


		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 2)		//### Double Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 75 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 75 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 2;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}


		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel == 3)		//### Triple Jink Power Upgrade
			{
			if(Q_Forge->Forge[AIcounter].HB_Energy >= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff)
				{
				Q_Forge->Forge[AIcounter].HB_Energy -= 250 / Q_Forge->Forge[AIcounter].CharDATA.BodySKILL.RELEnergyEff;
				Q_Forge->Forge[AIcounter].HB_EnergyTimer = TIME;
				if(Q_Forge->Forge[AIcounter].HB_Energy < 0) Q_Forge->Forge[AIcounter].HB_Energy = 0;

				Q_Netplayer->Netplayer[NetPlayID].ControlSET.CLog.KL_LTFSpecLevel = 0;

				//#### Upgrade Shot Damage
				Q_Forge->Forge[AIcounter].Soldier.JAccuracyLVL = 3;

				geSound3D_GetConfig(World, &player[g_Player]->ViewXForm, &Q_Forge->Forge[AIcounter].RFistPos.Translation, 600.0f, 2.0f, &Volume, &Pan, &Frequency);
					//'Jink'
				geSound_PlaySoundDef(SoundSys, Medias->S_EJink, _->Volume, _->Pan, _->S_TimeScale, GE_false);

				Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 2;
				}
			else Q_Forge->Forge[AIcounter].SNDTRIGEnergy = 1;
			}

		}//End SOLDIER JINKS


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyTAB && Q_Forge->Forge[AIcounter].WeaponStatus == 0 && !(Q_Forge->Forge[AIcounter].CharDATA.Class == 0 && Q_Forge->Forge[AIcounter].Mposestate == 16))	//****////WEAPON\\\\****
	{ Q_Forge->Forge[AIcounter].DrawWeapon = 1; }


	//### Forward Looking Coll Det for wall running etc

	Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
	Q_Forge->Forge[AIcounter].OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;

	Q_Forge->Forge[AIcounter].OldPos.Y += 60;
	Q_Forge->Forge[AIcounter].NewPos.Y += 60;

	geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Up);
	geVec3d_MA(&Q_Forge->Forge[AIcounter].OldPos, -20, &Q_Forge->Forge[AIcounter].Avatar.Up, &Q_Forge->Forge[AIcounter].NewPos);

	// This does collision detection
	if(Q_Forge->Forge[AIcounter].WallRun == 0)
		{
		if(geWorld_Collision(World, 
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins,
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs,
						 &Q_Forge->Forge[AIcounter].OldPos,
						 &Q_Forge->Forge[AIcounter].NewPos,
						 GE_CONTENTS_CANNOT_OCCUPY,                //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
						 GE_COLLIDE_MODELS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
						 0xffffffff, NULL, NULL,
						 &Q_Forge->Forge[AIcounter].WallRunCollision))
				{
				if((Q_Forge->Forge[AIcounter].attackon == 0 || (Q_Forge->Forge[AIcounter].attackon == 1 && ((Q_Forge->Forge[AIcounter].Aposestate == 24) || (Q_Forge->Forge[AIcounter].Aposestate == 73) || (Q_Forge->Forge[AIcounter].Aposestate == 76) || (Q_Forge->Forge[AIcounter].Aposestate == 53)))) && Q_Forge->Forge[AIcounter].WallRunDelay == 0 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)
					{
					if((Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == -1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0)
						|| (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 1) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == -1))
						{
						//_->TimeHole = 1;
						//_->TimeRotate = 1;
						//_->TimePlayerLock = 0;
						Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].WallRunCollision.Impact;
						Q_Forge->Forge[AIcounter].WallRun = 1;
						Q_Forge->Forge[AIcounter].Mposestate = 9;
						if(Q_Forge->Forge[AIcounter].Aposestate != 20) Q_Forge->Forge[AIcounter].attackon = 0;
						Q_Forge->Forge[AIcounter].WallRunDelay = 15;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}
					}
				}
		}

	Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
	Q_Forge->Forge[AIcounter].OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;

	Q_Forge->Forge[AIcounter].OldPos.Y += 60;
	Q_Forge->Forge[AIcounter].NewPos.Y += 60;

	geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Up);
	geVec3d_MA(&Q_Forge->Forge[AIcounter].OldPos, 20, &Q_Forge->Forge[AIcounter].Avatar.Up, &Q_Forge->Forge[AIcounter].NewPos);

	// This does collision detection
	if(Q_Forge->Forge[AIcounter].WallRun == 0)
		{
		if(geWorld_Collision(World, 
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins,
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs,
						 &Q_Forge->Forge[AIcounter].OldPos,
						 &Q_Forge->Forge[AIcounter].NewPos,
						 GE_CONTENTS_CANNOT_OCCUPY,                //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
						 GE_COLLIDE_MODELS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
						 0xffffffff, NULL, NULL,
						 &Q_Forge->Forge[AIcounter].WallRunCollision))
				{
				if((Q_Forge->Forge[AIcounter].attackon == 0 || (Q_Forge->Forge[AIcounter].attackon == 1 && ((Q_Forge->Forge[AIcounter].Aposestate == 24) || (Q_Forge->Forge[AIcounter].Aposestate == 73) || (Q_Forge->Forge[AIcounter].Aposestate == 76) || (Q_Forge->Forge[AIcounter].Aposestate == 53)))) && Q_Forge->Forge[AIcounter].WallRunDelay == 0 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)
					{
					if((Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == -1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0)
						|| (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 1) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == -1))
						{
						//_->TimeHole = 1;
						//_->TimeRotate = 1;
						//_->TimePlayerLock = 0;
						Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].WallRunCollision.Impact;
						Q_Forge->Forge[AIcounter].WallRun = 1;
						Q_Forge->Forge[AIcounter].Mposestate = 9;
						Q_Forge->Forge[AIcounter].WallRunDelay = 15;
						if(Q_Forge->Forge[AIcounter].Aposestate != 20)	Q_Forge->Forge[AIcounter].attackon = 0;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}
					}
				}
		}


	//### Forward Looking Coll Det for wall running etc

	Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
	Q_Forge->Forge[AIcounter].OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;

	Q_Forge->Forge[AIcounter].OldPos.Y += 60;
	Q_Forge->Forge[AIcounter].NewPos.Y += 60;

	geXForm3d_GetLeft(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Left);
	geVec3d_MA(&Q_Forge->Forge[AIcounter].OldPos, -20, &Q_Forge->Forge[AIcounter].Avatar.Left, &Q_Forge->Forge[AIcounter].NewPos);

	// This does collision detection
	if(Q_Forge->Forge[AIcounter].WallRun == 0)
		{
		if(geWorld_Collision(World, 
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins,
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs,
						 &Q_Forge->Forge[AIcounter].OldPos,
						 &Q_Forge->Forge[AIcounter].NewPos,
						 GE_CONTENTS_CANNOT_OCCUPY,                //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
						 GE_COLLIDE_MODELS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
						 0xffffffff, NULL, NULL,
						 &Q_Forge->Forge[AIcounter].WallRunCollision))
				{
				if((Q_Forge->Forge[AIcounter].attackon == 0 || (Q_Forge->Forge[AIcounter].attackon == 1 && ((Q_Forge->Forge[AIcounter].Aposestate == 24) || (Q_Forge->Forge[AIcounter].Aposestate == 73) || (Q_Forge->Forge[AIcounter].Aposestate == 76) || (Q_Forge->Forge[AIcounter].Aposestate == 53)))) && Q_Forge->Forge[AIcounter].WallRunDelay == 0 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)
					{
					if((Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == -1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0)
						|| (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 1) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == -1))
						{
						//_->TimeHole = 1;
						//_->TimeRotate = 1;
						//_->TimePlayerLock = 0;
						Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].WallRunCollision.Impact;
						Q_Forge->Forge[AIcounter].WallRun = 1;
						Q_Forge->Forge[AIcounter].Mposestate = 9;
						if(Q_Forge->Forge[AIcounter].Aposestate != 20)	Q_Forge->Forge[AIcounter].attackon = 0;
						Q_Forge->Forge[AIcounter].WallRunDelay = 15;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}
					}
				}
		}

	Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
	Q_Forge->Forge[AIcounter].OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;

	Q_Forge->Forge[AIcounter].OldPos.Y += 60;
	Q_Forge->Forge[AIcounter].NewPos.Y += 60;

	geXForm3d_GetLeft(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Left);
	geVec3d_MA(&Q_Forge->Forge[AIcounter].OldPos, 20, &Q_Forge->Forge[AIcounter].Avatar.Left, &Q_Forge->Forge[AIcounter].NewPos);

	// This does collision detection
	if(Q_Forge->Forge[AIcounter].WallRun == 0)
		{
		if(geWorld_Collision(World, 
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins,
						 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs,
						 &Q_Forge->Forge[AIcounter].OldPos,
						 &Q_Forge->Forge[AIcounter].NewPos,
						 GE_CONTENTS_CANNOT_OCCUPY,                //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
						 GE_COLLIDE_MODELS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
						 0xffffffff, NULL, NULL,
						 &Q_Forge->Forge[AIcounter].WallRunCollision))
				{
				if((Q_Forge->Forge[AIcounter].attackon == 0 || (Q_Forge->Forge[AIcounter].attackon == 1 && ((Q_Forge->Forge[AIcounter].Aposestate == 24) || (Q_Forge->Forge[AIcounter].Aposestate == 73) || (Q_Forge->Forge[AIcounter].Aposestate == 76) || (Q_Forge->Forge[AIcounter].Aposestate == 53)))) && Q_Forge->Forge[AIcounter].WallRunDelay == 0 && Q_Forge->Forge[AIcounter].Aposestate != 51 && Q_Forge->Forge[AIcounter].Aposestate != 52 && Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 30 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)
					{
					if((Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == -1 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 0)
						|| (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == 1) || (Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.X == 0 && Q_Forge->Forge[AIcounter].WallRunCollision.Plane.Normal.Z == -1))
						{
						//_->TimeHole = 1;
						//_->TimeRotate = 1;
						//_->TimePlayerLock = 0;
						Q_Forge->Forge[AIcounter].NewPos = Q_Forge->Forge[AIcounter].WallRunCollision.Impact;
						Q_Forge->Forge[AIcounter].WallRun = 1;
						Q_Forge->Forge[AIcounter].Mposestate = 9;
						Q_Forge->Forge[AIcounter].WallRunDelay = 15;
						if(Q_Forge->Forge[AIcounter].Aposestate != 20)	Q_Forge->Forge[AIcounter].attackon = 0;
						Q_Forge->Forge[AIcounter].StepTimer = 0;
						}
					}
				}
		}


	//#### Cancel AirJink Status for Wall Run
	if(Q_Forge->Forge[AIcounter].Mposestate == 9 && Q_Forge->Forge[AIcounter].AirJinkRotFG == 1)
		{
		Q_Forge->Forge[AIcounter].AirJinkRotFG = 0;
		Q_Forge->Forge[AIcounter].ROTATEMatrix = Q_Forge->Forge[AIcounter].STOREMatrix;
		Q_Forge->Forge[AIcounter].AJAngles.Y = Q_Forge->Forge[AIcounter].Angles.Y - Q_Forge->Forge[AIcounter].STOREAngles.Y;
		if(Q_Forge->Forge[AIcounter].AJAngles.Y > (2*PI)) Q_Forge->Forge[AIcounter].AJAngles.Y = Q_Forge->Forge[AIcounter].AJAngles.Y-(PI*2);
		if(Q_Forge->Forge[AIcounter].AJAngles.Y < 0) Q_Forge->Forge[AIcounter].AJAngles.Y = (PI*2) + Q_Forge->Forge[AIcounter].AJAngles.Y;
		geXForm3d_RotateY(&Q_Forge->Forge[AIcounter].ROTATEMatrix, Q_Forge->Forge[AIcounter].AJAngles.Y);
		geVec3d_Copy(&Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation, &Q_Forge->Forge[AIcounter].ROTATEMatrix.Translation);
		Q_Forge->Forge[AIcounter].Avatar.ActorXform = Q_Forge->Forge[AIcounter].ROTATEMatrix;
		}

	
	if(Q_Forge->Forge[AIcounter].Running == 1) Q_Forge->Forge[AIcounter].WallRunDelay = 0;

	if(Q_Forge->Forge[AIcounter].WallRunDelay > 0 && Q_Forge->Forge[AIcounter].WallRun == 0)
		{
		if(Q_Forge->Forge[AIcounter].WallRunDelay < 0) Q_Forge->Forge[AIcounter].WallRunDelay = 0;
		Q_Forge->Forge[AIcounter].WallRunDelay--;
		}
	

	//*----Keyboard Input----*


	Q_Forge->Forge[AIcounter].ForwardSpeed = 0;		// reset our forward speed

	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORMiddButton != 1)		
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT) Q_Forge->Forge[AIcounter].ForwardSpeed = -(Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Left
		else Q_Forge->Forge[AIcounter].ForwardSpeed = -(Q_Forge->Forge[AIcounter].PlayerSpeed/1.5)*_->TimeScale;							//Sidestep Left

		if(((Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS == 0) || (Q_Forge->Forge[AIcounter].Mposestate != 5 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Dependent Movement mode switch
			{
			Q_Forge->Forge[AIcounter].runposecnt = 0.08;
			Q_Forge->Forge[AIcounter].Mposestate = 5;
			Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].idleposecnt = 0;
			Q_Forge->Forge[AIcounter].StepTimer = 0;
			}

		//*** Actor
		Q_Forge->Forge[AIcounter].Avatar.OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		geXForm3d_GetLeft(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Left);
		geVec3d_MA(&Q_Forge->Forge[AIcounter].Avatar.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].Avatar.Left, &Q_Forge->Forge[AIcounter].Avatar.NewPos);

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y += 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y += 60;

		// This does collision detection
		if(geWorld_Collision(World, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs, 
					 &Q_Forge->Forge[AIcounter].Avatar.OldPos, 
					 &Q_Forge->Forge[AIcounter].Avatar.NewPos, 
					 GE_CONTENTS_CANNOT_OCCUPY,                  //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
					 GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
					 0xffffffff, NULL, NULL, 
					 &Q_Forge->Forge[AIcounter].Avatar.Collision))
			{
			// Set the new pos to the point of collision
			Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.Collision.Impact;
			Q_Forge->Forge[AIcounter].collide = 1;
			}

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y -= 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y -= 60;
	
		// Set the player to the new pos
		if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation = Q_Forge->Forge[AIcounter].Avatar.NewPos;
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORMiddButton != 1)		//Sidestep Right
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT) Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;		//Slow Sidestep Right
		else Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/1.5)*_->TimeScale;						//Sidestep Right

		if(((Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 6 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS == 0) || (Q_Forge->Forge[AIcounter].Mposestate != 6 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT)) && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Dependent Movement mode switch
			{
			Q_Forge->Forge[AIcounter].runposecnt = 0.4;
			Q_Forge->Forge[AIcounter].Mposestate = 6;
			Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
			Q_Forge->Forge[AIcounter].idleposecnt = 0;
			Q_Forge->Forge[AIcounter].StepTimer = 0;
			}

		//*** Actor
		Q_Forge->Forge[AIcounter].Avatar.OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		geXForm3d_GetLeft(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Left);
		geVec3d_MA(&Q_Forge->Forge[AIcounter].Avatar.OldPos, Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].Avatar.Left, &Q_Forge->Forge[AIcounter].Avatar.NewPos);

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y += 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y += 60;

		// This does collision detection
		if(geWorld_Collision(World, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs, 
					 &Q_Forge->Forge[AIcounter].Avatar.OldPos, 
					 &Q_Forge->Forge[AIcounter].Avatar.NewPos, 
					 GE_CONTENTS_CANNOT_OCCUPY,                  //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
					 GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
					 0xffffffff, NULL, NULL, 
					 &Q_Forge->Forge[AIcounter].Avatar.Collision))
			{
			// Set the new pos to the point of collision
			Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.Collision.Impact;
			Q_Forge->Forge[AIcounter].collide = 1;
			}

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y -= 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y -= 60;
	
		// Set the player to the new pos
		if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation = Q_Forge->Forge[AIcounter].Avatar.NewPos;
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORMiddButton != 1)
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT)
			{
			Q_Forge->Forge[AIcounter].ForwardSpeed = (Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;  //Walk Forwards

			if(Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 1 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD == 0 && Q_Forge->Forge[AIcounter].Mposestate != 8 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Movement mode switch
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
			Q_Forge->Forge[AIcounter].ForwardSpeed = Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Forwards
			
			if(Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 3 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Movement mode switch
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

		Q_Forge->Forge[AIcounter].TestValue1 = 1;


		//*** Actor
		Q_Forge->Forge[AIcounter].Avatar.OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Up);
		geVec3d_MA(&Q_Forge->Forge[AIcounter].Avatar.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].Avatar.Up, &Q_Forge->Forge[AIcounter].Avatar.NewPos);

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y += 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y += 60;

		// This does collision detection
		if(geWorld_Collision(World, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs, 
					 &Q_Forge->Forge[AIcounter].Avatar.OldPos, 
					 &Q_Forge->Forge[AIcounter].Avatar.NewPos, 
					 GE_CONTENTS_CANNOT_OCCUPY,                  //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
					 GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
					 0xffffffff, NULL, NULL, 
					 &Q_Forge->Forge[AIcounter].Avatar.Collision))
			{
			// Set the new pos to the point of collision
			Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.Collision.Impact;
			Q_Forge->Forge[AIcounter].collide = 1;
			}

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y -= 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y -= 60;
	
		// Set the player to the new pos
		if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation = Q_Forge->Forge[AIcounter].Avatar.NewPos;
		}
	else Q_Forge->Forge[AIcounter].WindWake = 0;


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORMiddButton != 1)
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySHIFT)
			{
			Q_Forge->Forge[AIcounter].ForwardSpeed = -(Q_Forge->Forge[AIcounter].PlayerSpeed/4)*_->TimeScale;  //Walk Backwards

			if(Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 2 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA == 0 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD == 0 && Q_Forge->Forge[AIcounter].Mposestate != 8 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 2;
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
			Q_Forge->Forge[AIcounter].ForwardSpeed = -Q_Forge->Forge[AIcounter].PlayerSpeed*_->TimeScale;  //Run Backwards

			if(Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 4 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Movement mode switch
				{
				Q_Forge->Forge[AIcounter].Mposestate = 4;
				Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
				Q_Forge->Forge[AIcounter].runposecnt = 0;
				Q_Forge->Forge[AIcounter].idleposecnt = 0;
				Q_Forge->Forge[AIcounter].StepTimer = 0;
				}
			}

		Q_Forge->Forge[AIcounter].TestValue1 = 1;

		//*** Actor
		Q_Forge->Forge[AIcounter].Avatar.OldPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
		geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Avatar.Up);
		geVec3d_MA(&Q_Forge->Forge[AIcounter].Avatar.OldPos, -Q_Forge->Forge[AIcounter].ForwardSpeed, &Q_Forge->Forge[AIcounter].Avatar.Up, &Q_Forge->Forge[AIcounter].Avatar.NewPos);

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y += 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y += 60;

		// This does collision detection
		if(geWorld_Collision(World, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Mins, 
					 NULL,//&Q_Forge->Forge[AIcounter].Avatar.Maxs, 
					 &Q_Forge->Forge[AIcounter].Avatar.OldPos, 
					 &Q_Forge->Forge[AIcounter].Avatar.NewPos, 
					 GE_CONTENTS_CANNOT_OCCUPY,                  //GE_CONTENTS_SOLID_CLIP, //GE_CONTENTS_CANNOT_OCCUPY, 
					 GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS,      //GE_COLLIDE_ALL, //GE_COLLIDE_MODELS | GE_COLLIDE_ACTORS, 
					 0xffffffff, NULL, NULL, 
					 &Q_Forge->Forge[AIcounter].Avatar.Collision))
			{
			// Set the new pos to the point of collision
			//Q_Forge->Forge[AIcounter].Avatar.NewPos = Q_Forge->Forge[AIcounter].Avatar.Collision.Impact;
			Q_Forge->Forge[AIcounter].collide = 1;
			}

		Q_Forge->Forge[AIcounter].Avatar.OldPos.Y -= 60;
		Q_Forge->Forge[AIcounter].Avatar.NewPos.Y -= 60;
	
		// Set the player to the new pos
		if(Q_Forge->Forge[AIcounter].collide == 0) Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation = Q_Forge->Forge[AIcounter].Avatar.NewPos;
		}


	//###--- JUMP ---###

	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySPACE && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Mposestate != 16)
		{
		Q_Forge->Forge[AIcounter].SPACEKEYcnt++;

		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS)	//### Spiral Over Enemy Jump
			{
			if(Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)
				{
				Q_Forge->Forge[AIcounter].JumpDir = 0;

				geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].JumpVec);
				geVec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

				Q_Forge->Forge[AIcounter].jumpposecnt = 0;
				Q_Forge->Forge[AIcounter].Mposestate = 13;
				Q_Forge->Forge[AIcounter].JumpFG = 0;
				}
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16)	//### Forward First Jump
				{
				Q_Forge->Forge[AIcounter].JumpDir = 0;

				geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].JumpVec);
				geVec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

				Q_Forge->Forge[AIcounter].jumpposecnt = 0;
				Q_Forge->Forge[AIcounter].Mposestate = 11;
				Q_Forge->Forge[AIcounter].JumpFG = 0;
				}
			else
				{		//### Forward Second Jump
				if((Q_Forge->Forge[AIcounter].Mposestate == 11) && ((Q_Forge->Forge[AIcounter].SPACEKEYcnt > 8) || (Q_Forge->Forge[AIcounter].SPACEKEYcnt == 1)))
					{
					Q_Forge->Forge[AIcounter].JumpDir = 0;

					geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].JumpVec);
					geVec3d_Inverse(&Q_Forge->Forge[AIcounter].JumpVec);

					if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW) Q_Forge->Forge[AIcounter].JumpDir = 1;	//Forward Jump

					Q_Forge->Forge[AIcounter].jumpposecnt = 0;
					Q_Forge->Forge[AIcounter].Mposestate = 12;
					Q_Forge->Forge[AIcounter].JumpFG = 0;
					}
				}
			}
		}
	else Q_Forge->Forge[AIcounter].SPACEKEYcnt = 0;


	if (Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyQ && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 16)		//ROLL LOW LEFT
		{
		Q_Forge->Forge[AIcounter].Mposestate = 28;
		Q_Forge->Forge[AIcounter].runposecnt = 0;
		Q_Forge->Forge[AIcounter].SideSpeed = 0;
		Q_Forge->Forge[AIcounter].JumpOff = 0;

		Q_Forge->Forge[AIcounter].Block = 0;
		Q_Forge->Forge[AIcounter].Blocking = 0;
		Q_Forge->Forge[AIcounter].BlockHeight = 1;
		}

	if (Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyE && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 16)		//ROLL LOW RIGHT
		{
		Q_Forge->Forge[AIcounter].Mposestate = 29;
		Q_Forge->Forge[AIcounter].runposecnt = 0;
		Q_Forge->Forge[AIcounter].SideSpeed = 0;
		Q_Forge->Forge[AIcounter].JumpOff = 0;

		Q_Forge->Forge[AIcounter].Block = 0;
		Q_Forge->Forge[AIcounter].Blocking = 0;
		Q_Forge->Forge[AIcounter].BlockHeight = 1;
		}

	if (Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyQ && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 16)		//CARTWHEEL LEFT
		{
		Q_Forge->Forge[AIcounter].Mposestate = 23;
		Q_Forge->Forge[AIcounter].runposecnt = 0;
		Q_Forge->Forge[AIcounter].SideSpeed = 0;
		Q_Forge->Forge[AIcounter].JumpOff = 0;

		Q_Forge->Forge[AIcounter].Block = 0;
		Q_Forge->Forge[AIcounter].Blocking = 0;
		Q_Forge->Forge[AIcounter].BlockHeight = 1;
		}

	if (Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyE && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 16)		//CARTWHEEL RIGHT
		{
		Q_Forge->Forge[AIcounter].Mposestate = 24;
		Q_Forge->Forge[AIcounter].runposecnt = 1.67;
		Q_Forge->Forge[AIcounter].SideSpeed = 0;
		Q_Forge->Forge[AIcounter].JumpOff = 0;

		Q_Forge->Forge[AIcounter].Block = 0;
		Q_Forge->Forge[AIcounter].Blocking = 0;
		Q_Forge->Forge[AIcounter].BlockHeight = 1;
		}


	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 16 && (Q_Forge->Forge[AIcounter].Aposestate != 26 && Q_Forge->Forge[AIcounter].Aposestate != 28 && Q_Forge->Forge[AIcounter].Aposestate != 30))		//DODGE LEFT / ROLL FORWARD
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyA && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].BlockHit == 0)		//ROLL LOW LEFT
			{
			Q_Forge->Forge[AIcounter].Mposestate = 28;
			Q_Forge->Forge[AIcounter].runposecnt = 0;
			Q_Forge->Forge[AIcounter].SideSpeed = 0;
			Q_Forge->Forge[AIcounter].JumpOff = 0;

			Q_Forge->Forge[AIcounter].Block = 0;
			Q_Forge->Forge[AIcounter].Blocking = 0;
			Q_Forge->Forge[AIcounter].BlockHeight = 1;
			}

		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyD && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].BlockHit == 0)		//ROLL LOW RIGHT
			{
			Q_Forge->Forge[AIcounter].Mposestate = 29;
			Q_Forge->Forge[AIcounter].runposecnt = 0;
			Q_Forge->Forge[AIcounter].SideSpeed = 0;
			Q_Forge->Forge[AIcounter].JumpOff = 0;

			Q_Forge->Forge[AIcounter].Block = 0;
			Q_Forge->Forge[AIcounter].Blocking = 0;
			Q_Forge->Forge[AIcounter].BlockHeight = 1;
			}

		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyW && Q_Forge->Forge[AIcounter].BlockHit == 0 && Q_Forge->Forge[AIcounter].Mposestate != 8)	//Player pressing forward so roll
			{
			Q_Forge->Forge[AIcounter].Mposestate = 26;
			Q_Forge->Forge[AIcounter].runposecnt = 0;
			Q_Forge->Forge[AIcounter].Aposestate = 0;
			Q_Forge->Forge[AIcounter].attackon = 0;
			Q_Forge->Forge[AIcounter].attposecnt = 0;

			Q_Forge->Forge[AIcounter].Block = 0;
			Q_Forge->Forge[AIcounter].Blocking = 0;
			Q_Forge->Forge[AIcounter].BlockHeight = 1;
			}

		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS && Q_Forge->Forge[AIcounter].BlockHit == 0)	//Pressing Back So Backflip
			{
			if(Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Aposestate != 62)
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

				Q_Forge->Forge[AIcounter].Block = 0;
				Q_Forge->Forge[AIcounter].Blocking = 0;
				Q_Forge->Forge[AIcounter].BlockHeight = 1;
				}
			else
				{
				if(Q_Forge->Forge[AIcounter].runposecnt >= 1.02)
					{
					Q_Forge->Forge[AIcounter].runposecnt = 0.14;
					Q_Forge->Forge[AIcounter].blendamount[57] = 0.5;
					}

				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSRightButton == 1)
					{
					Q_Forge->Forge[AIcounter].astackcnt = 0;
					Q_Forge->Forge[AIcounter].astackrun = 0;
					Q_Forge->Forge[AIcounter].astackcntdir[0] = 0;
					Q_Forge->Forge[AIcounter].attposecnt = Q_Forge->Forge[AIcounter].runposecnt;
					Q_Forge->Forge[AIcounter].Aposestate = 0;
					Q_Forge->Forge[AIcounter].blendamount[0] = 0;
					Q_Forge->Forge[AIcounter].TrailsOn = 0;
					Q_Forge->Forge[AIcounter].attackon = 0;

					Q_Forge->Forge[AIcounter].Mposestate = 0;
					Q_Forge->Forge[AIcounter].runposecnt = 0;
					Q_Forge->Forge[AIcounter].Aposestate = 62;
					Q_Forge->Forge[AIcounter].attackon = 1;
					Q_Forge->Forge[AIcounter].attposecnt = 0;
					Q_Forge->Forge[AIcounter].attackhits = 0;
					Q_Forge->Forge[AIcounter].attackprog = 0;
					Q_Forge->Forge[AIcounter].collide = 0;
					Q_Forge->Forge[AIcounter].AttackSoundTRIG = 0;

					Q_Forge->Forge[AIcounter].Block = 0;
					Q_Forge->Forge[AIcounter].Blocking = 0;
					Q_Forge->Forge[AIcounter].BlockHeight = 1;
					}
				}
			}
		}


	//BIKE MODES FROZEN
	/*if(KEY_DOWN(0x48))
		{
		Q_Forge->Forge[AIcounter].PlayerMode = 1;
		Q_Forge->Forge[AIcounter].idleposecnt = 0;
		Q_Forge->Forge[AIcounter].Mposestate = 0;
		}*/
	

	//##### -  WEAPON CONTROL  - #####

	Q_Forge->Forge[AIcounter].WeaponAIM = 0;
	Q_Forge->Forge[AIcounter].WeaponHolster = 0;
	Q_Forge->Forge[AIcounter].WeaponFire = 0;

	if(Q_Forge->Forge[AIcounter].Aposestate == 20 || (Q_Forge->Forge[AIcounter].WeaponStatus != 0 && Q_Forge->Forge[AIcounter].attackon == 0))	//Weapon1
		{
		if(Q_Forge->Forge[AIcounter].WeaponStatus == 3)
			{
			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton == 1)
				{
				Q_Forge->Forge[AIcounter].WeaponAIM = 1;
				}

			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyTAB == 1)
				{
				Q_Forge->Forge[AIcounter].WeaponHolster = 1;
				}
			}

		if(Q_Forge->Forge[AIcounter].WeaponStatus == 5)
			{
			/*if(player[g_Player]->WeaponZOOM == 0)
				{
				if(!KEY_DOWN(0x52)) player[g_Player]->attposecnt = ((player[g_Player]->In.Y*-1.6)+1.3)-player[g_Player]->WeaponRecoil;	//*-2  +1.5
				}
			else
				{*/
				if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyR == 0) Q_Forge->Forge[AIcounter].attposecnt = ((Q_Netplayer->Netplayer[helly].ControlSET.AvatarAngle.X*-1.6)+1.3)-Q_Forge->Forge[AIcounter].WeaponRecoil;	//*-2  +1.5
				//}

			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.NORLeftButton == 1)
				{
				Q_Forge->Forge[AIcounter].WeaponFire = 1;
				}

			if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyTAB == 1)
				{
				Q_Forge->Forge[AIcounter].WeaponHolster = 1;
				}
			}
		else
			{
			Q_Forge->Forge[AIcounter].WeaponFire = 0;
			}
		}


	//### Taunt FROZEN
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyH && Q_Forge->Forge[AIcounter].Mposestate != 51)	//Taunt
		{
		Q_Forge->Forge[AIcounter].Mposestate = 51;
		Q_Forge->Forge[AIcounter].runposecnt = 0;
		}


	//Idle Posestate		THIS IS NOT GOOD REWORK \/\/\/\/\/\/\/\/
	if(Q_Forge->Forge[AIcounter].Mposestate != 51 && Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 27 && Q_Forge->Forge[AIcounter].Mposestate != 9 && Q_Forge->Forge[AIcounter].ForwardSpeed == 0 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 25 && Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ == 0 && Q_Forge->Forge[AIcounter].Mposestate != 0 && (Q_Forge->Forge[AIcounter].Mposestate != 10 && Q_Forge->Forge[AIcounter].Mposestate != 11 && Q_Forge->Forge[AIcounter].Mposestate != 12 && Q_Forge->Forge[AIcounter].Mposestate != 13 && Q_Forge->Forge[AIcounter].Mposestate != 14 && Q_Forge->Forge[AIcounter].Mposestate != 15 && Q_Forge->Forge[AIcounter].Mposestate != 16) && Q_Forge->Forge[AIcounter].Mposestate != 23 && Q_Forge->Forge[AIcounter].Mposestate != 24 && Q_Forge->Forge[AIcounter].Mposestate != 8)
		{
		Q_Forge->Forge[AIcounter].Mposestate = 0;
		Q_Forge->Forge[AIcounter].blendamount[0] = 0; //Optimise me please
		Q_Forge->Forge[AIcounter].blendamount[1] = 0; //Optimise me pls
		Q_Forge->Forge[AIcounter].blendamount[2] = 0; //Optimise me pls
		Q_Forge->Forge[AIcounter].blendamount[3] = 0; //Optimise me pls
		Q_Forge->Forge[AIcounter].runposecnt = 0;
		Q_Forge->Forge[AIcounter].idleposecnt = 0;
		}


	//###-  Blocking  -###
	if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyS == 1 && !Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeySPACE == 1 && Q_Forge->Forge[AIcounter].WeaponStatus == 0 && Q_Forge->Forge[AIcounter].attackon == 0 && Q_Forge->Forge[AIcounter].Mposestate != 8)
		{
		if(Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ == 1)
			{
			if(Q_Forge->Forge[AIcounter].BlockHeight != 1) Q_Forge->Forge[AIcounter].attposecnt = 0;
			Q_Forge->Forge[AIcounter].BlockHeight = 1;
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].BlockHeight != 3) Q_Forge->Forge[AIcounter].attposecnt = 0;
			Q_Forge->Forge[AIcounter].BlockHeight = 3;
			}

		Q_Forge->Forge[AIcounter].Blocking = 1;
		Q_Forge->Forge[AIcounter].Block = 1;
		}
	else
		{
		if(Q_Forge->Forge[AIcounter].BlockHit == 0 && (Q_Forge->Forge[AIcounter].CrouchInit == 0 || (Q_Forge->Forge[AIcounter].CrouchInit == 1 && !((Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ && Q_Forge->Forge[AIcounter].attackon == 0) || Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackrun - 1] == 1))))
			{
			Q_Forge->Forge[AIcounter].Blocking = 0;
			Q_Forge->Forge[AIcounter].Block = 0;
			}
		}


	//if(Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackrun - 1] == 0 && Q_Forge->Forge[AIcounter].attackon == 1 && Q_Forge->Forge[AIcounter].crohposecnt != 10) Q_Forge->Forge[AIcounter].CrouchInit = 0;

	//RESET Crouch
	Q_Forge->Forge[AIcounter].Crouch = 0;

	//Crouch Hard Coded
	if(Q_Forge->Forge[AIcounter].Mposestate != 28 && Q_Forge->Forge[AIcounter].Mposestate != 29 && Q_Forge->Forge[AIcounter].Mposestate != 26 && Q_Forge->Forge[AIcounter].Mposestate != 8 && Q_Forge->Forge[AIcounter].Mposestate != 16)
		{
		if((Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyZ && Q_Forge->Forge[AIcounter].attackon == 0) || Q_Forge->Forge[AIcounter].attackstackSPECIAL[Q_Forge->Forge[AIcounter].astackrun - 1] == 1)
			{
			if(Q_Forge->Forge[AIcounter].CrouchInit == 0)
				{
				Q_Forge->Forge[AIcounter].CrouchInit = 1;
				Q_Forge->Forge[AIcounter].crohposecnt = 0;
				}

			Q_Forge->Forge[AIcounter].Crouch = 1;

			geActor_BlendPose(Q_Forge->Forge[AIcounter].Avatar.Actor, Q_Forge->Forge[AIcounter].Avatar.Motion[60], Q_Forge->Forge[AIcounter].crohposecnt, &Q_Forge->Forge[AIcounter].Avatar.ActorXform, Q_Forge->Forge[AIcounter].blendamount[60]);
			if(Q_Forge->Forge[AIcounter].crohposecnt + (0.08*_->TimeScale) < 0.335)	Q_Forge->Forge[AIcounter].crohposecnt += 0.08*_->TimeScale;
			else Q_Forge->Forge[AIcounter].crohposecnt = 0.335;

			if(Q_Forge->Forge[AIcounter].blendamount[60]+(0.3*_->TimeScale)<=1) Q_Forge->Forge[AIcounter].blendamount[60] += 0.3*_->TimeScale;
			}
		else
			{
			if(Q_Forge->Forge[AIcounter].CrouchInit == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
				{
				geActor_BlendPose(Q_Forge->Forge[AIcounter].Avatar.Actor, Q_Forge->Forge[AIcounter].Avatar.Motion[60], Q_Forge->Forge[AIcounter].crohposecnt, &Q_Forge->Forge[AIcounter].Avatar.ActorXform, Q_Forge->Forge[AIcounter].blendamount[60]);
				if(Q_Forge->Forge[AIcounter].crohposecnt + (0.08*_->TimeScale) <= 0.67) Q_Forge->Forge[AIcounter].crohposecnt += 0.08*_->TimeScale;
				else Q_Forge->Forge[AIcounter].CrouchInit = 0;
				}
			}
		}
	else
		{
		if(Q_Forge->Forge[AIcounter].CrouchInit == 1 && Q_Forge->Forge[AIcounter].attackon == 0)
			{
			geActor_BlendPose(Q_Forge->Forge[AIcounter].Avatar.Actor, Q_Forge->Forge[AIcounter].Avatar.Motion[60], Q_Forge->Forge[AIcounter].crohposecnt, &Q_Forge->Forge[AIcounter].Avatar.ActorXform, Q_Forge->Forge[AIcounter].blendamount[60]);
			if(Q_Forge->Forge[AIcounter].crohposecnt + (0.08*_->TimeScale) <= 0.67) Q_Forge->Forge[AIcounter].crohposecnt += 0.08*_->TimeScale;
			else Q_Forge->Forge[AIcounter].CrouchInit = 0;
			}
		}


	/*if (KEY_DOWN(0x25))
		{
		//geXForm3d_SetZRotation(&AIfriendly, -0.3);//*_->TimeScale);
		//geXForm3d_SetXRotation(&AIfriendly, -0.3);//*_->TimeScale);
		//	geXForm3d_Multiply(&Q_Forge->Forge[0].Avatar.ActorXform, &AIfriendly, &Q_Forge->Forge[0].Avatar.ActorXform);
		}


	if (KEY_DOWN(0x27))
		{
		//geXForm3d_SetZRotation(&AIfriendly, 0.1*_->TimeScale);
		//	geXForm3d_Multiply(&Q_Forge->Forge[0].Avatar.ActorXform, &AIfriendly, &Q_Forge->Forge[0].Avatar.ActorXform);
		}*/

	/*if((KEY_DOWN(0x50)) && (_->MusicDEPRESS == 0) && (_->MusicSWITCH != 1))
		{
		geSound3D_GetConfig(World,
							&player[g_Player]->ViewXForm,
							&Q_Forge->Forge[AIcounter].RFistPos.Translation,
							600.0f,
							2.0f,
							&Volume,
							&Pan,
							&Frequency);

			//'MUSAC'
		geSound_PlaySoundDef(SoundSys, Medias->LoopingDef3, _->Volume, _->Pan, _->S_TimeScale, GE_true);
		_->MusicDEPRESS = 1;
		_->MusicSWITCH = 1;
		}*/

	//EDIT unsure About Sound Types
	/*if((KEY_DOWN(0x50)) && (_->MusicDEPRESS == 0) && (_->MusicSWITCH != 2))
		{
		geSound_StopSound(SoundSys, &Medias->LoopingDef3);
		_->MusicSWITCH = 2;
		}*/

	/*if(!(KEY_DOWN(0x50)))
		{
		_->MusicDEPRESS = 0;
		}*/


	/*if (KEY_DOWN(0x47))
		{
		Testoor = 1;
		}
	else Testoor = 0;*/


	/*TEST VALUES
	if(KEY_DOWN(0x55))	//U
		{
		if(Q_Forge->Forge[0].Q_Brain.TestKEY1DOWN == 0)
			{
			Q_Forge->Forge[0].Q_Brain.TestKEY1DOWN = 1;
			if(Q_Forge->Forge[0].Q_Brain.TestKEY1 == 0) Q_Forge->Forge[0].Q_Brain.TestKEY1 = 1;
			else Q_Forge->Forge[0].Q_Brain.TestKEY1 = 0;
			}
		}
	else Q_Forge->Forge[0].Q_Brain.TestKEY1DOWN = 0;


	if(KEY_DOWN(0x49))	//I
		{
		if(Q_Forge->Forge[0].Q_Brain.TestKEY2DOWN == 0)
			{
			Q_Forge->Forge[0].Q_Brain.TestKEY2DOWN = 1;
			if(Q_Forge->Forge[0].Q_Brain.TestKEY2 == 0) Q_Forge->Forge[0].Q_Brain.TestKEY2 = 1;
			else Q_Forge->Forge[0].Q_Brain.TestKEY2 = 0;
			}
		}
	else Q_Forge->Forge[0].Q_Brain.TestKEY2DOWN = 0;


	if(KEY_DOWN(0x4F))	//O
		{
		if(Q_Forge->Forge[0].Q_Brain.TestKEY3DOWN == 0)
			{
			Q_Forge->Forge[0].Q_Brain.TestKEY3DOWN = 1;
			if(Q_Forge->Forge[0].Q_Brain.TestKEY3 == 0) Q_Forge->Forge[0].Q_Brain.TestKEY3 = 1;
			else Q_Forge->Forge[0].Q_Brain.TestKEY3 = 0;
			}
		}
	else Q_Forge->Forge[0].Q_Brain.TestKEY3DOWN = 0;


	/*if(KEY_DOWN(0x4C))	//L
		{
		testvalue1 -= 0.5;
		}

	if(KEY_DOWN(0x4A))		//J
		{
		lightpos.X -= 7;
		}*/


	//*----Player Reload (r)----*
	if (Q_Netplayer->Netplayer[NetPlayID].ControlSET.Key.NORkeyR)
		{
		Q_Forge->Forge[AIcounter].WeaponStatus = 8;
		Q_Forge->Forge[AIcounter].attposecnt = 0;
		Q_Forge->Forge[AIcounter].blendamount[58] = 0;
		}


	//*----Camera Control----*


	/*if (KEY_DOWN(VK_HOME))
		{
		Q_Forge->Forge[AIcounter].camrotdist -= 5;
		}

	if (KEY_DOWN(VK_END))
		{
		Q_Forge->Forge[AIcounter].camrotdist += 5;
		}*/


	//*----Effects Testing Key (o)----*

	/*if(KEY_DOWN(0x4F) && 0)
		{
		/*if(Q_Forge->Forge[3].Aposestate == 42)
			{
			if(Q_Forge->Forge[3].attposecnt > 1.33) Q_Forge->Forge[3].attposecnt = 1.33;
			}
		else
			{
			Q_Forge->Forge[3].Aposestate = 42;
			Q_Forge->Forge[3].attackon = 1;
			Q_Forge->Forge[3].attposecnt = 0;
			}*/

		/*if(_->NomPEFMesh == 0)
			{
			Stratod = Q_Forge->Forge[AIcounter].Avatar.ActorXform.Translation;
			Stratod.Y += 90;
			geXForm3d_GetIn(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Up);
			geVec3d_Inverse(&Q_Forge->Forge[AIcounter].Up);
			geXForm3d_GetLeft(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].Left);
			geVec3d_Inverse(&Q_Forge->Forge[AIcounter].Left);
			geXForm3d_GetUp(&Q_Forge->Forge[AIcounter].Avatar.ActorXform,&Q_Forge->Forge[AIcounter].In);

			PEF_CREATE_PinEffectMesh(Stratod, 30, Q_Forge->Forge[AIcounter].In, Q_Forge->Forge[AIcounter].Left, Q_Forge->Forge[AIcounter].Up);
			}
		}*/


	//*----Screen Shots (scr)----*

	/*if (KEY_DOWN(VK_SNAPSHOT))
		{
		if(ScreenCounter == 0) ScreenShot = "ScreenShots\\ScreenShot0.bmp";
		if(ScreenCounter == 1) ScreenShot = "ScreenShots\\ScreenShot1.bmp";
		if(ScreenCounter == 2) ScreenShot = "ScreenShots\\ScreenShot2.bmp";
		if(ScreenCounter == 3) ScreenShot = "ScreenShots\\ScreenShot3.bmp";
		if(ScreenCounter == 4) ScreenShot = "ScreenShots\\ScreenShot4.bmp";
		if(ScreenCounter == 5) ScreenShot = "ScreenShots\\ScreenShot5.bmp";
		if(ScreenCounter == 6) ScreenShot = "ScreenShots\\ScreenShot6.bmp";
		if(ScreenCounter == 7) ScreenShot = "ScreenShots\\ScreenShot7.bmp";
		if(ScreenCounter == 8) ScreenShot = "ScreenShots\\ScreenShot8.bmp";
		if(ScreenCounter == 9) ScreenShot = "ScreenShots\\ScreenShot9.bmp";
		if(ScreenCounter == 10) ScreenShot = "ScreenShots\\ScreenShot10.bmp";
		if(ScreenCounter == 11) ScreenShot = "ScreenShots\\ScreenShot11.bmp";
		if(ScreenCounter == 12) ScreenShot = "ScreenShots\\ScreenShot12.bmp";
		if(ScreenCounter == 13) ScreenShot = "ScreenShots\\ScreenShot13.bmp";
		if(ScreenCounter == 14) ScreenShot = "ScreenShots\\ScreenShot14.bmp";
		if(ScreenCounter == 15) ScreenShot = "ScreenShots\\ScreenShot15.bmp";
		if(ScreenCounter == 16) ScreenShot = "ScreenShots\\ScreenShot16.bmp";
		if(ScreenCounter == 17) ScreenShot = "ScreenShots\\ScreenShot17.bmp";
		if(ScreenCounter == 18) ScreenShot = "ScreenShots\\ScreenShot18.bmp";
		if(ScreenCounter == 19) ScreenShot = "ScreenShots\\ScreenShot19.bmp";
		if(ScreenCounter == 20) ScreenShot = "ScreenShots\\ScreenShot20.bmp";
		if(ScreenCounter == 21) ScreenShot = "ScreenShots\\ScreenShot21.bmp";
		if(ScreenCounter == 22) ScreenShot = "ScreenShots\\ScreenShot22.bmp";
		if(ScreenCounter == 23) ScreenShot = "ScreenShots\\ScreenShot23.bmp";
		if(ScreenCounter == 24) ScreenShot = "ScreenShots\\ScreenShot24.bmp";
		if(ScreenCounter == 25) ScreenShot = "ScreenShots\\ScreenShot25.bmp";
		if(ScreenCounter == 26) ScreenShot = "ScreenShots\\ScreenShot26.bmp";
		if(ScreenCounter == 27) ScreenShot = "ScreenShots\\ScreenShot27.bmp";
		if(ScreenCounter == 28) ScreenShot = "ScreenShots\\ScreenShot28.bmp";
		if(ScreenCounter == 29) ScreenShot = "ScreenShots\\ScreenShot29.bmp";
		if(ScreenCounter == 30) ScreenShot = "ScreenShots\\ScreenShot30.bmp";
		if(ScreenCounter == 31) ScreenShot = "ScreenShots\\ScreenShot31.bmp";
		if(ScreenCounter == 32) ScreenShot = "ScreenShots\\ScreenShot32.bmp";
		if(ScreenCounter == 33) ScreenShot = "ScreenShots\\ScreenShot33.bmp";
		if(ScreenCounter == 34) ScreenShot = "ScreenShots\\ScreenShot34.bmp";
		if(ScreenCounter == 35) ScreenShot = "ScreenShots\\ScreenShot35.bmp";
		if(ScreenCounter == 36) ScreenShot = "ScreenShots\\ScreenShot36.bmp";
		if(ScreenCounter == 37) ScreenShot = "ScreenShots\\ScreenShot37.bmp";
		if(ScreenCounter == 38) ScreenShot = "ScreenShots\\ScreenShot38.bmp";
		if(ScreenCounter == 39) ScreenShot = "ScreenShots\\ScreenShot39.bmp";
		if(ScreenCounter == 40) ScreenShot = "ScreenShots\\ScreenShot40.bmp";
		if(ScreenCounter == 41) ScreenShot = "ScreenShots\\ScreenShot41.bmp";
		if(ScreenCounter == 42) ScreenShot = "ScreenShots\\ScreenShot42.bmp";
		if(ScreenCounter == 43) ScreenShot = "ScreenShots\\ScreenShot43.bmp";
		if(ScreenCounter == 44) ScreenShot = "ScreenShots\\ScreenShot44.bmp";
		if(ScreenCounter == 45) ScreenShot = "ScreenShots\\ScreenShot45.bmp";
		if(ScreenCounter == 46) ScreenShot = "ScreenShots\\ScreenShot46.bmp";
		if(ScreenCounter == 47) ScreenShot = "ScreenShots\\ScreenShot47.bmp";
		if(ScreenCounter == 48) ScreenShot = "ScreenShots\\ScreenShot48.bmp";
		if(ScreenCounter == 49) ScreenShot = "ScreenShots\\ScreenShot49.bmp";
		if(ScreenCounter == 50) ScreenShot = "ScreenShots\\ScreenShot50.bmp";

		if(ScreenCounter <= 50) geEngine_ScreenShot(Engine, ScreenShot);

		ScreenCounter++;
		}*/


	//*----Player Invisibility (i)----*

	/*if(KEY_DOWN(0x49) && 0)
		{
		if(KeyDepress2 == 0)
			{
			if(Q_Forge->Forge[AIcounter].FirstPerson == 1)
				{
				Q_Forge->Forge[AIcounter].FirstPerson = 0;
				geActor_SetAlpha(Q_Forge->Forge[AIcounter].Avatar.Actor, 255);
				}
			else
				{
				Q_Forge->Forge[AIcounter].FirstPerson = 1;
				geActor_SetAlpha(Q_Forge->Forge[AIcounter].Avatar.Actor, 100);
				}
			}

		KeyDepress2 = 1;
		}
	else KeyDepress2 = 0;*/


	//*----Time Altering----*

	/*if (KEY_DOWN(VK_UP)) _->TimeScale += 0.01;
	if (KEY_DOWN(VK_DOWN)) _->TimeScale -= 0.01;
	if (_->TimeScale <= 0) _->TimeScale = 0.005;
	if (KEY_DOWN(VK_DELETE)) _->TimeScale = 1;*/


	//*----Build Control----*


	/*if (KEY_DOWN(0x42))
		{
		Q_Forge->Forge[AIcounter].mode = 1;		//Buildmode
		}*/


	//### Constant Changing

	/*if(KEY_DOWN(0x31))
		{
		Q_SEnergy->SEnergy[0].Const_AngleInc -= 0.01;
		}

	if(KEY_DOWN(0x32))
		{
		Q_SEnergy->SEnergy[0].Const_AngleInc += 0.01;
		}

	if(KEY_DOWN(0x33))
		{
		Q_SEnergy->SEnergy[0].Const_TurnDull -= 5;
		}

	if(KEY_DOWN(0x34))
		{
		Q_SEnergy->SEnergy[0].Const_TurnDull += 5;
		}*/



	//*----Gamma Correction----*


	/*if (KEY_DOWN(VK_ADD))
		{
		// Reset the gamma.
		gama += 0.1;
		geEngine_SetGamma(Engine, gama);
		
		// write our new gamma settings to a file
		stream = fopen("Config\\gamma.ini","w");
		fprintf(stream,"%f",gama);
		fclose(stream);
		}

	if (KEY_DOWN(VK_SUBTRACT))
		{
		// reset the gama
		gama -= 0.1;
		geEngine_SetGamma(Engine, gama);
		
		// write our new gamma settings to a file
		stream = fopen("Config\\gamma.ini","w");
		fprintf(stream,"%f",gama);
		fclose(stream);
		}

	if (KEY_DOWN(VK_MULTIPLY))
		{
		gama = 1.0;
		geEngine_SetGamma(Engine, gama);

		// write our new gamma settings to a file
		stream = fopen("Config\\gamma.ini","w");
		fprintf(stream,"%f",gama);
		fclose(stream);
		}*/


	}//END Player Mode Temporarily


	Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSLeftButton = 0;
	Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSMiddButton = 0;
	Q_Netplayer->Netplayer[NetPlayID].ControlSET.Mouse.SYSRightButton = 0;

	}