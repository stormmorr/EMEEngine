/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Digital Enviroment-
	*/#include "pch.h"/*- Minor Component -Sound Initialization-

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

using namespace GVARS;

namespace GVARS
{

// Bitmap init *********************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

void Q_COREFunctions::InitSoundsNum(void)
{
	//printf("SOUND BEGIN:::");

	//###### SOUND FILES SETUP
	Qpo->Sound_Init();

	//printf("SOUND:::WASAPI SOUND ENGINE STARTUP...\n");

	Medias->S_Build = 55;

	//##### - VEHICLE MOTORCYCLE - #####

	//[Bike Start]
	Medias->S_VehMBStart = 0;

	//[Bike Start Loop]
	Medias->S_VehMBStartLoop = 1;

	//[Bike Skid]
	Medias->S_VehMBSkid = 2;

	//[Bike Power]
	Medias->S_VehMBPower = 3;

	//[Bike Power]
	Medias->S_VehMBLoopPower = 4;
	
	//[Bike Power]
	Medias->S_VehMBLoopPower2 = 5;

	//[Bike Power]
	Medias->S_VehMBLoopPower3 = 6;

	//##### - Gun Sounds - #####

	//[Rifle] Fire]
	Medias->S_RifleFire[0] = 7;

	//[Rifle] Fire]
	Medias->S_RifleFire[1] = 8;

	//[Rifle] Fire]
	Medias->S_RifleFire[2] = 9;

	//[Rifle] Fire]
	Medias->S_RifleFire[3] = 10;

	//[Rifle] Fire]
	Medias->S_RifleFire[4] = 11;

	//[Rifle] Fire]
	Medias->S_RifleFire[5] = 12;

	//[Rifle] Fire]
	Medias->S_RifleFire[6] = 13;

	//[Rifle] Fire]
	Medias->S_RifleFire[7] = 14;

	//[Rifle] Fire]
	Medias->S_RifleFire[11] = 15;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[0] = 16;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[1] = 17;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[2] = 18;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[3] = 19;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[4] = 20;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[5] = 21;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[6] = 22;

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[7] = 23;

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[0] = 24;

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[1] = 25;

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[2] = 26; // = Qpo->Sound_Load("QpoSound", "clipin02.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[3] = 27; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\clipin02.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[4] = 28; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\clipin04.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[5] = 29; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\clipin05.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[6] = 30; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\clipin06.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[7] = 31; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\clipin07.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[0] = 32; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[1] = 33; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[2] = 34; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[3] = 35; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[4] = 36; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[5] = 37; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[6] = 38; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[7] = 39; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltslap00.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[0] = 40; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull00.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[1] = 41; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull01.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[2] = 42; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull02.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[3] = 43; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull02.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[4] = 44; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull04.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[5] = 45; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull05.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[6] = 46; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull06.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[7] = 47; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\boltpull07.wav");

	//[Rifle] Bullet Hit Wall 1]
	Medias->S_Hitwall1 = 48; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\Hitwall\\Hitwall1.wav");

	//[Rifle] Bullet Hit Wall 2]
	Medias->S_Hitwall2 = 49; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\Hitwall\\Hitwall2.wav");

	//[Rifle] Bullet Hit Wall 3]
	Medias->S_Hitwall3 = 50; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\Hitwall\\Hitwall3.wav");

	//[Rifle] Bullet Hit Wall 4]
	Medias->S_Hitwall4 = 51; // = Qpo->Sound_Load("QpoSound", "Wav\\smg\\Hitwall\\Hitwall4.wav");

	//AI LogON
	Medias->SingleDef2 = 52; // = Qpo->Sound_Load("QpoSound", "Wav\\EvilLisa\\Hello.wav");

	////QNETWORKFrame();

	//#######-  Attack Sounds  -#######

	//### Attacking Noises

	//[Normal Swish 1]
	Medias->S_SwishN1 = 53; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishN1.wav");

	//[Normal Swish 2]
	Medias->S_SwishN2 = 54; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishN2.wav");

	//[Normal Swish 3]
	Medias->S_SwishN3 = 55; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishN3.wav");

	//[Normal Swish 4]
	Medias->S_SwishN4 = 56; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishN4.wav");

	//[Heavy Swish 1]
	Medias->S_SwishH1 = 61; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishH1.wav");

	//[Heavy Swish 2]
	Medias->S_SwishH2 = 62; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishH2.wav");

	//[Heavy Swish Spin]
	Medias->S_SwishSpin = 63; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishSpin.wav");

	//[Heavy Swish 3 Female]
	Medias->S_SwishH3FEMALE = 64; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishH3FEMALE.wav");

	//[Heavy Swish 3 Male]
	Medias->S_SwishH3MALE = 65; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\SwishH3MALE.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Medias->S_RenzouImpact = 66; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\RenzouImpact.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Medias->S_FireCrackle = 67; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\FireCrackle.wav");

	//### Attack Hits

	//[Bullet Hit Flesh]
	Medias->S_BulletHit = 68; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\BulletHit.wav");

	//[Bullet Hit Armour]
	Medias->S_BulletHitArmour = 69; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\BulletHitArmour.wav");

	//[Normal Hit 1]
	Medias->S_HitN1 = 70; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitN1.wav");

	//[Normal Hit Avatar 1]
	Medias->S_HitN1AV = 71; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitN1AV.wav");

	//[Normal Hit Self 1]
	Medias->S_HitSelfN1 = 72; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitSelfN1.wav");

	//[Normal Hit Self 2]
	Medias->S_HitSelfN2 = 73; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitSelfN2.wav");

	//[Heavy Hit 1]
	Medias->S_HitH1 = 74; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitH1.wav");

	//[Heavy Hit Self]
	Medias->S_HitSelfH1 = 75; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitSelfH1.wav");

	//[Ultra Hit Female]
	Medias->S_UltraBlowFEMALE = 76; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\UltraBlowFEMALE.wav");

	//[Ultra Hit Male]
	Medias->S_UltraBlowMALE = 77; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\UltraBlowMALE.wav");
	

	//[Block Hit]
	Medias->S_HitB1 = 78; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HitB1.wav");

	//### Jink Sound
	Medias->S_Jink = 79; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\Jink.wav");

	//### Cleric Jink Sound
	Medias->S_CJink = 80; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\CJink.wav");

	//### Jink Sound
	Medias->S_EJink = 81; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\EJink.wav");

	//### Jink Sound
	Medias->S_BJink = 82; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\DeflectJink.wav");
	
	//###Jink Ready Sound
	Medias->S_KeyLog = 83; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\KeyLog.wav");
	
	//###Jink Ready Error Low Energy
	Medias->S_KeyLogError = 84; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\KeyLogError.wav");

	//###Shock Block
	Medias->S_ShkBlock = 85; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\ShockBlock.wav");
	
	//###Deflect Block
	Medias->S_DefBlock = 86; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\DefAttack.wav");

	//###Deflect Block
	Medias->S_BrkBlock = 87; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\BrkBlock.wav");
	
	//###Flame Upper Cut Flames
	Medias->S_UppCutFlames = 88; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\UppCutFlames.wav");
	
	//##### - CLERIC SOUNDS - #####

	//### Cleric Plasma
	Medias->S_CPlasma = 89; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\CPlasma.wav");
	
	//##### - ATTACK INITIALISATIONS - #####

	//### Attack Init Single Female
	Medias->S_AttINITFEMALE = 90; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITFEMALE.wav");

	//### Attack Init Single Male
	Medias->S_AttINITMALE = 91; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITMALE.wav");
	
	//### Attack Init Multiple Female
	Medias->S_AttINITMULTFEMALE = 92; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITMULTFEMALE.wav");
	
	//### Attack Init Multiple Male
	Medias->S_AttINITMULTMALE = 93; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITMULTMALE.wav");
	
	//### Attack Init Small Female
	Medias->S_AttINITSMLFEMALE = 94; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITSMLFEMALE.wav");
	
	//### Attack Init Small Female
	Medias->S_AttINITSMLMALE = 95; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\AttINITSMLMALE.wav");

	//##### - KO SOUNDS - #####

	//### Enemy KO
	Medias->S_EnemyKO = 96; // = Qpo->Sound_Load("QpoSound", "Wav\\Deaths\\EnemyKO.wav");

	//### Player KO
	Medias->S_PlayerKO = 97; // = Qpo->Sound_Load("QpoSound", "Wav\\Deaths\\PlayerKO.wav");
	
	//###### Effects ######
	//### Mat Start
	Medias->S_MatStart = 98; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\mStart.wav");

	//### Mat End
	Medias->S_MatEnd = 99; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\mEnd.wav");
	
	//###Explosion
	Medias->S_Explosion = 100; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Explosion.wav");
	
	//###Explosion Small
	Medias->S_Explosion3000 = 101; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Explosion3001.wav");
	
	//### Renzou Fire Left
	Medias->S_RenzouFireLeft = 102; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\RenzouLeft.wav");
	
	//### Renzou Fire Right
	Medias->S_RenzouFireRight = 103; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\RenzouRight.wav");
	
	//### Renzou Fire Right
	Medias->S_RenzouFireDouble = 104; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\RenzouFireDouble.wav");
	
	//### Renzou
	Medias->S_Renzou = 105; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Renzou.wav");
	
	//### Had Warning
	Medias->S_HadWarning = 104; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HadWarning.wav");
	
	//### Jink 3RD Level Charge
	Medias->S_JINK3ChargeStart = 103; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\JINK3ChargeStart.wav");

	//### Jink 3RD Level Charge
	Medias->S_JINK3Charge = 104; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\JINK3Charge.wav");

	//### Jink 3RD Level Vocal
	Medias->S_JINK3Vocal = 105; // = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\JINK3VOCAL.wav");
	
	//### Zone Capture
	Medias->S_ZoneCapture = 106; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\ZoneCapture.wav");
	
	//### Footsteps Capture
	Medias->S_Footsteps = 107; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Footsteps.wav");

	//[BUILD]
	Medias->S_Build = 106; // = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Roaddrill.wav");

	//##### - VEHICLE MOTORCYCLE - #####

	//[Bike Start]
	/*Qpo->Sound_Load(Medias->S_VehMBStart, "QpoSound", "StartR.wav");

	//[Bike Start Loop]
	Qpo->Sound_Load(Medias->S_VehMBStartLoop, "QpoSound", "BikeLoop.wav");

	//[Bike Skid]
	Qpo->Sound_Load(Medias->S_VehMBSkid, "QpoSound", "skid02.wav");

	//[Bike Power]
	Qpo->Sound_Load(Medias->S_VehMBPower, "QpoSound", "BikeP.wav");

	//[Bike Power]
	Qpo->Sound_Load(Medias->S_VehMBLoopPower, "QpoSound", "BikeLoopP.wav");
	
	//[Bike Power]
	Qpo->Sound_Load(Medias->S_VehMBLoopPower2, "QpoSound", "BikeLoopP2.wav");

	//[Bike Power]
	Qpo->Sound_Load(Medias->S_VehMBLoopPower3, "QpoSound", "BikeLoopP3.wav");

	//##### - Gun Sounds - #####

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[0], "QpoSound", "fire00.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[1], "QpoSound", "fire01.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[2], "QpoSound", "fire02.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[3], "QpoSound", "fire03.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[4], "QpoSound", "fire04.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[5], "QpoSound", "fire05.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[6], "QpoSound", "fire06.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[7], "QpoSound", "fire07.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(Medias->S_RifleFire[11], "QpoSound", "fire11.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[0], "QpoSound", "clipout00.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[1], "QpoSound", "clipout01.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[2], "QpoSound", "clipout02.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[3], "QpoSound", "clipout02.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[4], "QpoSound", "clipout04.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[5], "QpoSound", "clipout05.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[6], "QpoSound", "clipout06.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(Medias->S_RifleClipOut[7], "QpoSound", "clipout07.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[0], "QpoSound", "clipin00.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[1], "QpoSound", "clipin01.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[2], "QpoSound", "clipin02.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[3], "QpoSound", "clipin02.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[4], "QpoSound", "clipin04.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[5], "QpoSound", "clipin05.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[6], "QpoSound", "clipin06.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(Medias->S_RifleClipIn[7], "QpoSound", "clipin07.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[0], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[1], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[2], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[3], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[4], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[5], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[6], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(Medias->S_RifleBoltOut[7], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[0], "QpoSound", "boltpull00.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[1], "QpoSound", "boltpull01.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[2], "QpoSound", "boltpull02.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[3], "QpoSound", "boltpull02.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[4], "QpoSound", "boltpull04.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[5], "QpoSound", "boltpull05.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[6], "QpoSound", "boltpull06.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(Medias->S_RifleBoltIn[7], "QpoSound", "boltpull07.wav");

	//[Rifle] Bullet Hit Wall 1]
	Qpo->Sound_Load(Medias->S_Hitwall1, "QpoSound", "Hitwall\\Hitwall1.wav");

	//[Rifle] Bullet Hit Wall 2]
	Qpo->Sound_Load(Medias->S_Hitwall2, "QpoSound", "Hitwall\\Hitwall2.wav");

	//[Rifle] Bullet Hit Wall 3]
	Qpo->Sound_Load(Medias->S_Hitwall3, "QpoSound", "Hitwall\\Hitwall3.wav");

	//[Rifle] Bullet Hit Wall 4]
	Qpo->Sound_Load(Medias->S_Hitwall4, "QpoSound", "Hitwall\\Hitwall4.wav");

	//AI LogON
	Qpo->Sound_Load(Medias->SingleDef2, "QpoSound", "Hello.wav");

	//Music??
	//Medias->LoopingDef3, "QpoSound", "Wav\\Music\\sonic1.wav");

	////QNETWORKFrame();

	//#######-  Attack Sounds  -#######

	//### Attacking Noises

	//[Normal Swish 1]
	Qpo->Sound_Load(Medias->S_SwishN1, "QpoSound", "SwishN1.wav");

	//[Normal Swish 2]
	Qpo->Sound_Load(Medias->S_SwishN2, "QpoSound", "SwishN2.wav");

	//[Normal Swish 3]
	Qpo->Sound_Load(Medias->S_SwishN3, "QpoSound", "SwishN3.wav");

	//[Normal Swish 4]
	Qpo->Sound_Load(Medias->S_SwishN4, "QpoSound", "SwishN4.wav");

	//[Heavy Swish 1]
	Qpo->Sound_Load(Medias->S_SwishH1, "QpoSound", "SwishH1.wav");

	//[Heavy Swish 2]
	Qpo->Sound_Load(Medias->S_SwishH2, "QpoSound", "SwishH2.wav");

	//[Heavy Swish Spin]
	Qpo->Sound_Load(Medias->S_SwishSpin, "QpoSound", "SwishSpin.wav");

	//[Heavy Swish 3 Female]
	Qpo->Sound_Load(Medias->S_SwishH3FEMALE, "QpoSound", "SwishH3FEMALE.wav");

	//[Heavy Swish 3 Male]
	Qpo->Sound_Load(Medias->S_SwishH3MALE, "QpoSound", "SwishH3MALE.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Load(Medias->S_RenzouImpact, "QpoSound", "RenzouImpact.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Load(Medias->S_FireCrackle, "QpoSound", "FireCrackle.wav");

	//### Attack Hits

	//[Bullet Hit Flesh]
	Qpo->Sound_Load(Medias->S_BulletHit, "QpoSound", "BulletHit.wav");

	//[Bullet Hit Armour]
	Qpo->Sound_Load(Medias->S_BulletHitArmour, "QpoSound", "BulletHitArmour.wav");

	//[Normal Hit 1]
	Qpo->Sound_Load(Medias->S_HitN1, "QpoSound", "HitN1.wav");

	//[Normal Hit Avatar 1]
	Qpo->Sound_Load(Medias->S_HitN1AV, "QpoSound", "HitN1AV.wav");

	//[Normal Hit Self 1]
	Qpo->Sound_Load(Medias->S_HitSelfN1, "QpoSound", "HitSelfN1.wav");

	//[Normal Hit Self 2]
	Qpo->Sound_Load(Medias->S_HitSelfN2, "QpoSound", "HitSelfN2.wav");

	//[Heavy Hit 1]
	Qpo->Sound_Load(Medias->S_HitH1, "QpoSound", "HitH1.wav");

	//[Heavy Hit Self]
	Qpo->Sound_Load(Medias->S_HitSelfH1, "QpoSound", "HitSelfH1.wav");

	//[Ultra Hit Female]
	Qpo->Sound_Load(Medias->S_UltraBlowFEMALE, "QpoSound", "UltraBlowFEMALE.wav");

	//[Ultra Hit Male]
	Qpo->Sound_Load(Medias->S_UltraBlowMALE, "QpoSound", "UltraBlowMALE.wav");
	

	//[Block Hit]
	Qpo->Sound_Load(Medias->S_HitB1, "QpoSound", "HitB1.wav");

	//### Jink Sound
	Qpo->Sound_Load(Medias->S_Jink, "QpoSound", "Jink.wav");

	//### Cleric Jink Sound
	Qpo->Sound_Load(Medias->S_CJink, "QpoSound", "CJink.wav");

	//### Jink Sound
	Qpo->Sound_Load(Medias->S_EJink, "QpoSound", "EJink.wav");

	//### Jink Sound
	Qpo->Sound_Load(Medias->S_BJink, "QpoSound", "DeflectJink.wav");
	
	//###Jink Ready Sound
	Qpo->Sound_Load(Medias->S_KeyLog, "QpoSound", "KeyLog.wav");
	
	//###Jink Ready Error Low Energy
	Qpo->Sound_Load(Medias->S_KeyLogError, "QpoSound", "KeyLogError.wav");

	//###Shock Block
	Qpo->Sound_Load(Medias->S_ShkBlock, "QpoSound", "ShockBlock.wav");
	
	//###Deflect Block
	Qpo->Sound_Load(Medias->S_DefBlock, "QpoSound", "DefAttack.wav");

	//###Deflect Block
	Qpo->Sound_Load(Medias->S_BrkBlock, "QpoSound", "BrkBlock.wav");
	
	//###Flame Upper Cut Flames
	Qpo->Sound_Load(Medias->S_UppCutFlames, "QpoSound", "UppCutFlames.wav");
	
	//##### - CLERIC SOUNDS - #####

	//### Cleric Plasma
	Qpo->Sound_Load(Medias->S_CPlasma, "QpoSound", "CPlasma.wav");
	
	//##### - ATTACK INITIALISATIONS - #####

	//### Attack Init Single Female
	Qpo->Sound_Load(Medias->S_AttINITFEMALE, "QpoSound", "AttINITFEMALE.wav");

	//### Attack Init Single Male
	Qpo->Sound_Load(Medias->S_AttINITMALE, "QpoSound", "AttINITMALE.wav");
	
	//### Attack Init Multiple Female
	Qpo->Sound_Load(Medias->S_AttINITMULTFEMALE, "QpoSound", "AttINITMULTFEMALE.wav");
	
	//### Attack Init Multiple Male
	Qpo->Sound_Load(Medias->S_AttINITMULTMALE, "QpoSound", "AttINITMULTMALE.wav");
	
	//### Attack Init Small Female
	Qpo->Sound_Load(Medias->S_AttINITSMLFEMALE, "QpoSound", "AttINITSMLFEMALE.wav");
	
	//### Attack Init Small Female
	Qpo->Sound_Load(Medias->S_AttINITSMLMALE, "QpoSound", "AttINITSMLMALE.wav");

	//##### - KO SOUNDS - #####

	//### Enemy KO
	Qpo->Sound_Load(Medias->S_EnemyKO, "QpoSound", "EnemyKO.wav");

	//### Player KO
	Qpo->Sound_Load(Medias->S_PlayerKO, "QpoSound", "PlayerKO.wav");
	
	//###### Effects ######
	//### Mat Start
	Qpo->Sound_Load(Medias->S_MatStart, "QpoSound", "mStart.wav");

	//### Mat End
	Qpo->Sound_Load(Medias->S_MatEnd, "QpoSound", "mEnd.wav");
	
	//###Explosion
	Qpo->Sound_Load(Medias->S_Explosion, "QpoSound", "Explosion.wav");
	
	//###Explosion Small
	Qpo->Sound_Load(Medias->S_Explosion3000, "QpoSound", "Explosion3001.wav");
	
	//### Renzou Fire Left
	Qpo->Sound_Load(Medias->S_RenzouFireLeft, "QpoSound", "RenzouLeft.wav");
	
	//### Renzou Fire Right
	Qpo->Sound_Load(Medias->S_RenzouFireRight, "QpoSound", "RenzouRight.wav");
	
	//### Renzou Fire Right
	Qpo->Sound_Load(Medias->S_RenzouFireDouble, "QpoSound", "RenzouFireDouble.wav");
	
	//### Renzou
	Qpo->Sound_Load(Medias->S_Renzou, "QpoSound", "Renzou.wav");
	
	//### Had Warning
	Qpo->Sound_Load(Medias->S_HadWarning, "QpoSound", "HadWarning.wav");
	
	//### Jink 3RD Level Charge
	Qpo->Sound_Load(Medias->S_JINK3ChargeStart, "QpoSound", "JINK3ChargeStart.wav");

	//### Jink 3RD Level Charge
	Qpo->Sound_Load(Medias->S_JINK3Charge, "QpoSound", "JINK3Charge.wav");

	//### Jink 3RD Level Vocal
	Qpo->Sound_Load(Medias->S_JINK3Vocal, "QpoSound", "JINK3VOCAL.wav");
	
	//### Zone Capture
	Qpo->Sound_Load(Medias->S_ZoneCapture, "QpoSound", "ZoneCapture.wav");
	
	//### Footsteps Capture
	Qpo->Sound_Load(Medias->S_Footsteps, "QpoSound", "Footsteps.wav");*/

	for (int f_Count = 0; f_Count < 108; f_Count++)
		{
		//Qpo->Sound_Load(Medias->S_Footsteps, "QpoSound", "Footsteps.wav");
		}

	//printf("SOUND:::Qpo->Sound_Load QpoSound LOADED\n");
}

//### Interface Sounds ####//
void Q_COREFunctions::InterfaceSounds(void)
{
	//### OnHover
	Qpo->Sound_Load(&Medias->S_Hover, "QpoSound", "hover.wav");

	//### Click
	Qpo->Sound_Load(&Medias->S_Click, "QpoSound", "click.wav");
}

void Q_COREFunctions::InitSounds(void)
{
#if 0
	printf("SOUND BEGIN:::");
#endif

	std::string f_ref_CurrentPath = g_ref_global_start + "Q_COREFunctions::InitSounds";

#if 0
	printf("SOUND:::WASAPI SOUND ENGINE STARTUP...\n");
#endif

	Medias->S_Build = 55;

	//##### - VEHICLE MOTORCYCLE - #####

	//[Bike Start]
	Qpo->Sound_Load(&Medias->S_VehMBStart, "QpoSound", "StartR.wav");

	//[Bike Start Loop]
	Qpo->Sound_Load(&Medias->S_VehMBStartLoop, "QpoSound", "BikeLoop.wav");

	//[Bike Skid]
	Qpo->Sound_Load(&Medias->S_VehMBSkid, "QpoSound", "skid02.wav");

	//[Bike Power]
	Qpo->Sound_Load(&Medias->S_VehMBPower, "QpoSound", "BikeP.wav");

	//[Bike Power]
	Qpo->Sound_Load(&Medias->S_VehMBLoopPower, "QpoSound", "BikeLoopP.wav");
	
	//[Bike Power]
	Qpo->Sound_Load(&Medias->S_VehMBLoopPower2, "QpoSound", "BikeLoopP2.wav");

	//[Bike Power]
	Qpo->Sound_Load(&Medias->S_VehMBLoopPower3, "QpoSound", "BikeLoopP3.wav");

	//##### - Gun Sounds - #####

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[0], "QpoSound", "fire00.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[1], "QpoSound", "fire01.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[2], "QpoSound", "fire02.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[3], "QpoSound", "fire03.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[4], "QpoSound", "fire04.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[5], "QpoSound", "fire05.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[6], "QpoSound", "fire06.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[7], "QpoSound", "fire07.wav");

	//[Rifle] Fire]
	Qpo->Sound_Load(&Medias->S_RifleFire[11], "QpoSound", "fire11.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[0], "QpoSound", "clipout00.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[1], "QpoSound", "clipout01.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[2], "QpoSound", "clipout02.wav");

	//[Rifle] Clip Out]
	Medias->S_RifleClipOut[3] = Medias->S_RifleClipOut[2];

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[4], "QpoSound", "clipout04.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[5], "QpoSound", "clipout05.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[6], "QpoSound", "clipout06.wav");

	//[Rifle] Clip Out]
	Qpo->Sound_Load(&Medias->S_RifleClipOut[7], "QpoSound", "clipout07.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[0], "QpoSound", "clipin00.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[1], "QpoSound", "clipin01.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[2], "QpoSound", "clipin02.wav");

	//[Rifle] Clip In]
	Medias->S_RifleClipIn[3] = Medias->S_RifleClipIn[2];

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[4], "QpoSound", "clipin04.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[5], "QpoSound", "clipin05.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[6], "QpoSound", "clipin06.wav");

	//[Rifle] Clip In]
	Qpo->Sound_Load(&Medias->S_RifleClipIn[7], "QpoSound", "clipin07.wav");

	//[Rifle] Bolt Out]
	Qpo->Sound_Load(&Medias->S_RifleBoltOut[0], "QpoSound", "boltslap00.wav");

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[1] = Medias->S_RifleBoltOut[0];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[2] = Medias->S_RifleBoltOut[1];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[3] = Medias->S_RifleBoltOut[2];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[4] = Medias->S_RifleBoltOut[3];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[5] = Medias->S_RifleBoltOut[4];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[6] = Medias->S_RifleBoltOut[5];

	//[Rifle] Bolt Out]
	Medias->S_RifleBoltOut[7] = Medias->S_RifleBoltOut[6];

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[0], "QpoSound", "boltpull00.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[1], "QpoSound", "boltpull01.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[2], "QpoSound", "boltpull02.wav");

	//[Rifle] Bolt In]
	Medias->S_RifleBoltIn[3] = Medias->S_RifleBoltIn[2];

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[4], "QpoSound", "boltpull04.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[5], "QpoSound", "boltpull05.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[6], "QpoSound", "boltpull06.wav");

	//[Rifle] Bolt In]
	Qpo->Sound_Load(&Medias->S_RifleBoltIn[7], "QpoSound", "boltpull07.wav");

	//[Rifle] Bullet Hit Wall 1]
	Qpo->Sound_Load(&Medias->S_Hitwall1, "QpoSound", "Hitwall1.wav");

	//[Rifle] Bullet Hit Wall 2]
	Qpo->Sound_Load(&Medias->S_Hitwall2, "QpoSound", "Hitwall2.wav");

	//[Rifle] Bullet Hit Wall 3]
	Qpo->Sound_Load(&Medias->S_Hitwall3, "QpoSound", "Hitwall3.wav");

	//[Rifle] Bullet Hit Wall 4]
	Qpo->Sound_Load(&Medias->S_Hitwall4, "QpoSound", "Hitwall4.wav");

	//AI LogON
	Medias->SingleDef2 = Medias->S_VehMBStart;

	//#######-  Attack Sounds  -#######

	//### Attacking Noises

	//[Normal Swish 1]
	Qpo->Sound_Load(&Medias->S_SwishN1, "QpoSound", "SwishN1.wav");

	//[Normal Swish 2]
	Qpo->Sound_Load(&Medias->S_SwishN2, "QpoSound", "SwishN2.wav");

	//[Normal Swish 3]
	Qpo->Sound_Load(&Medias->S_SwishN3, "QpoSound", "SwishN3.wav");

	//[Normal Swish 4]
	Qpo->Sound_Load(&Medias->S_SwishN4, "QpoSound", "SwishN4.wav");

	//[Heavy Swish 1]
	Qpo->Sound_Load(&Medias->S_SwishH1, "QpoSound", "SwishH1.wav");

	//[Heavy Swish 2]
	Qpo->Sound_Load(&Medias->S_SwishH2, "QpoSound", "SwishH2.wav");

	//[Heavy Swish Spin]
	Qpo->Sound_Load(&Medias->S_SwishSpin, "QpoSound", "SwishSpin.wav");

	//[Heavy Swish 3 Female]
	Qpo->Sound_Load(&Medias->S_SwishH3FEMALE, "QpoSound", "SwishH3FEMALE.wav");

	//[Heavy Swish 3 Male]
	Qpo->Sound_Load(&Medias->S_SwishH3MALE, "QpoSound", "SwishH3MALE.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Load(&Medias->S_RenzouImpact, "QpoSound", "RenzouImpact.wav");

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Load(&Medias->S_FireCrackle, "QpoSound", "FireCrackle.wav");

	//### Attack Hits

	//[Bullet Hit Flesh]
	Qpo->Sound_Load(&Medias->S_BulletHit, "QpoSound", "BulletHit.wav");

	//[Bullet Hit Armour]
	Qpo->Sound_Load(&Medias->S_BulletHitArmour, "QpoSound", "BulletHitArmour.wav");

	//[Normal Hit 1]
	Qpo->Sound_Load(&Medias->S_HitN1, "QpoSound", "HitN1.wav");

	//[Normal Hit Avatar 1]
	Qpo->Sound_Load(&Medias->S_HitN1AV, "QpoSound", "HitN1AV.wav");

	//[Normal Hit Self 1]
	Qpo->Sound_Load(&Medias->S_HitSelfN1, "QpoSound", "HiN1.wav");

	//[Normal Hit Self 2]
	Qpo->Sound_Load(&Medias->S_HitSelfN2, "QpoSound", "HiN2.wav");

	//[Heavy Hit 1]
	Qpo->Sound_Load(&Medias->S_HitH1, "QpoSound", "HitH1.wav");

	//[Heavy Hit Self]
	Qpo->Sound_Load(&Medias->S_HitSelfH1, "QpoSound", "HiH1.wav");

	//[Ultra Hit Female]
	Qpo->Sound_Load(&Medias->S_UltraBlowFEMALE, "QpoSound", "UltraBlowFEMALE.wav");

	//[Ultra Hit Male]
	Qpo->Sound_Load(&Medias->S_UltraBlowMALE, "QpoSound", "UltraBlowMALE.wav");
	

	//[Block Hit]
	Qpo->Sound_Load(&Medias->S_HitB1, "QpoSound", "HitB1.wav");

	//### Jink Sound
	Qpo->Sound_Load(&Medias->S_Jink, "QpoSound", "Jink.wav");

	//### Cleric Jink Sound
	Qpo->Sound_Load(&Medias->S_CJink, "QpoSound", "CJink.wav");

	//### Jink Sound
	Qpo->Sound_Load(&Medias->S_EJink, "QpoSound", "EJink.wav");

	//### Jink Sound
	Qpo->Sound_Load(&Medias->S_BJink, "QpoSound", "DeflectJink.wav");
	
	//###Jink Ready Sound
	Qpo->Sound_Load(&Medias->S_KeyLog, "QpoSound", "KeyLog.wav");
	
	//###Jink Ready Error Low Energy
	Qpo->Sound_Load(&Medias->S_KeyLogError, "QpoSound", "KeyLogError.wav");

	//###Shock Block
	Qpo->Sound_Load(&Medias->S_ShkBlock, "QpoSound", "ShockBlock.wav");
	
	//###Deflect Block
	Qpo->Sound_Load(&Medias->S_DefBlock, "QpoSound", "DefAttack.wav");

	//###Deflect Block
	Qpo->Sound_Load(&Medias->S_BrkBlock, "QpoSound", "BrkBlock.wav");
	
	//###Flame Upper Cut Flames
	Qpo->Sound_Load(&Medias->S_UppCutFlames, "QpoSound", "UppCutFlames.wav");
	
	//##### - CLERIC SOUNDS - #####

	//### Cleric Plasma
	Qpo->Sound_Load(&Medias->S_CPlasma, "QpoSound", "CPlasma.wav");
	
	//##### - ATTACK INITIALISATIONS - #####

	//### Attack Init Single Female
	Qpo->Sound_Load(&Medias->S_AttINITFEMALE, "QpoSound", "AttINITFEMALE.wav");

	//### Attack Init Single Male
	Qpo->Sound_Load(&Medias->S_AttINITMALE, "QpoSound", "AttINITMALE.wav");
	
	//### Attack Init Multiple Female
	Qpo->Sound_Load(&Medias->S_AttINITMULTFEMALE, "QpoSound", "AttINITMULTFEMALE.wav");
	
	//### Attack Init Multiple Male
	Qpo->Sound_Load(&Medias->S_AttINITMULTMALE, "QpoSound", "AttINITMULTMALE.wav");
	
	//### Attack Init Small Female
	Qpo->Sound_Load(&Medias->S_AttINITSMLFEMALE, "QpoSound", "AttINITSMLFEMALE.wav");
	
	//### Attack Init Small Female
	Qpo->Sound_Load(&Medias->S_AttINITSMLMALE, "QpoSound", "AttINITSMLMALE.wav");

	//##### - KO SOUNDS - #####

	//### Enemy KO
	Qpo->Sound_Load(&Medias->S_EnemyKO, "QpoSound", "EnemyKO.wav");

	//### Player KO
	Qpo->Sound_Load(&Medias->S_PlayerKO, "QpoSound", "PlayerKO.wav");
	
	//###### Effects ######
	//### Mat Start
	Qpo->Sound_Load(&Medias->S_MatStart, "QpoSound", "mStart.wav");

	//### Mat End
	Qpo->Sound_Load(&Medias->S_MatEnd, "QpoSound", "mEnd.wav");
	
	//###Explosion
	Qpo->Sound_Load(&Medias->S_Explosion, "QpoSound", "Explosion.wav");
	
	//###Explosion Small
	Qpo->Sound_Load(&Medias->S_Explosion3000, "QpoSound", "Explosion3001.wav");
	
	//### Renzou Fire Left
	Qpo->Sound_Load(&Medias->S_RenzouFireLeft, "QpoSound", "RenzouLeft.wav");
	
	//### Renzou Fire Right
	Qpo->Sound_Load(&Medias->S_RenzouFireRight, "QpoSound", "RenzouRight.wav");
	
	//### Renzou Fire Right
	Qpo->Sound_Load(&Medias->S_RenzouFireDouble, "QpoSound", "RenzouFireDouble.wav");
	
	//### Renzou
	Qpo->Sound_Load(&Medias->S_Renzou, "QpoSound", "Renzou.wav");
	
	//### Had Warning
	Qpo->Sound_Load(&Medias->S_HadWarning, "QpoSound", "HadWarning.wav");
	
	//### Jink 3RD Level Charge
	Qpo->Sound_Load(&Medias->S_JINK3ChargeStart, "QpoSound", "JINK3ChargeStart.wav");

	//### Jink 3RD Level Charge
	Qpo->Sound_Load(&Medias->S_JINK3Charge, "QpoSound", "JINK3Charge.wav");

	//### Jink 3RD Level Vocal
	Qpo->Sound_Load(&Medias->S_JINK3Vocal, "QpoSound", "JINK3VOCAL.wav");
	
	//### Zone Capture
	Qpo->Sound_Load(&Medias->S_ZoneCapture, "QpoSound", "ZoneCapture.wav");
	
	//### Footsteps Capture
	Qpo->Sound_Load(&Medias->S_Footsteps, "QpoSound", "Footsteps.wav");

#if 0
	printf("SOUND:::Qpo->Sound_Load QpoSound LOADED\n");
#endif
}

std::string Q_COREFunctions::acGetSound(int f_Index)
{
	std::string f_String;

	switch (f_Index)
	{
		case 0:
		{
			//[Bike Start]
			f_String = "StartR.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 1:
		{
			//[Bike Start Loop]
			f_String = "BikeLoop.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 2:
		{
			//[Bike Skid]
			f_String = "skid02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 3:
		{
			//[Bike Power]
			f_String = "BikeP.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 4:
		{
			//[Bike Power]
			f_String = "BikeLoopP.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 5:
		{
			//[Bike Power]
			f_String = "BikeLoopP2.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 6:
		{
			//[Bike Power]
			f_String = "BikeLoopP3.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//##### - Gun Sounds - #####
		case 7:
		{
			//[Rifle] Fire]
			f_String = "fire00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 8:
		{
			//[Rifle] Fire]
			f_String = "fire01.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 9:
		{
			//[Rifle] Fire]
			f_String = "fire02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 10:
		{
			//[Rifle] Fire]
			f_String = "fire03.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 11:
		{
			//[Rifle] Fire]
			f_String = "fire04.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 12:
		{
			//[Rifle] Fire]
			f_String = "fire05.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 13:
		{
			//[Rifle] Fire]
			f_String = "fire06.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 14:
		{
			//[Rifle] Fire]
			f_String = "fire07.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 15:
		{
			//[Rifle] Fire]
			f_String = "fire11.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 16:
		{
			//[Rifle] Clip Out]
			f_String = "clipout00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 17:
		{
			//[Rifle] Clip Out]
			f_String = "clipout01.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 18:
		{
			//[Rifle] Clip Out]
			f_String = "clipout02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 19:
		{
			//[Rifle] Clip Out]
			f_String = "clipout02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 20:
		{
			//[Rifle] Clip Out]
			f_String = "clipout04.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 21:
		{
			//[Rifle] Clip Out]
			f_String = "clipout05.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 22:
		{
			//[Rifle] Clip Out]
			f_String = "clipout06.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 23:
		{
			//[Rifle] Clip Out]
			f_String = "clipout07.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 24:
		{
			//[Rifle] Clip In]
			f_String = "clipin00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 25:
		{
			//[Rifle] Clip In]
			f_String = "clipin01.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 26:
		{
			//[Rifle] Clip In]
			f_String = "clipin02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 27:
		{
			//[Rifle] Clip In]
			f_String = "clipin02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 28:
		{
			//[Rifle] Clip In]
			f_String = "clipin04.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 29:
		{
			//[Rifle] Clip In]
			f_String = "clipin05.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 30:
		{
			//[Rifle] Clip In]
			f_String = "clipin06.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 31:
		{
			//[Rifle] Clip In]
			f_String = "clipin07.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 32:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 33:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 34:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 35:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 36:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 37:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 38:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 39:
		{
			//[Rifle] Bolt Out]
			f_String = "boltslap00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 40:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull00.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 41:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull01.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 42:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 43:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull02.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 44:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull04.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 45:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull05.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 46:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull06.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 47:
		{
			//[Rifle] Bolt In]
			f_String = "boltpull07.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 48:
		{
			//[Rifle] Bullet Hit Wall 1]
			f_String = "Hitwall\\Hitwall1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 49:
		{
			//[Rifle] Bullet Hit Wall 2]
			f_String = "Hitwall\\Hitwall2.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 50:
		{
			//[Rifle] Bullet Hit Wall 3]
			f_String = "Hitwall\\Hitwall3.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 51:
		{
			//[Rifle] Bullet Hit Wall 4]
			f_String = "Hitwall\\Hitwall4.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 52:
		{
			//AI LogON
			f_String = "Hello.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//Music??
		//Medias->LoopingDef3, "QpoSound", "Wav\\Music\\sonic1.wav";

		////QNETWORKFrame();

		//#######-  Attack Sounds  -#######

		//### Attacking Noises
		case 53:
		{
			//[Normal Swish 1]
			f_String = "SwishN1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 54:
		{
			//[Normal Swish 2]
			f_String = "SwishN2.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 55:
		{
			//[Normal Swish 3]
			f_String = "SwishN3.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 56:
		{
			//[Normal Swish 4]
			f_String = "SwishN4.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 57:
		{
			//[Heavy Swish 1]
			f_String = "SwishH1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 58:
		{
			//[Heavy Swish 2]
			f_String = "SwishH2.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 59:
		{
			//[Heavy Swish Spin]
			f_String = "SwishSpin.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 60:
		{
			//[Heavy Swish 3 Female]
			f_String = "SwishH3FEMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 61:
		{
			//[Heavy Swish 3 Male]
			f_String = "SwishH3MALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//### Renzou Hit
		case 62:
		{
			//[Renzou Hit]
			f_String = "RenzouImpact.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;

		//### Renzou Hit
		case 63:
		{
			//[Renzou Hit]
			f_String = "FireCrackle.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//### Attack Hits
		case 64:
		{
			//[Bullet Hit Flesh]
			f_String = "BulletHit.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 65:
		{
			//[Bullet Hit Armour]
			f_String = "BulletHitArmour.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 66:
		{
			//[Normal Hit 1]
			f_String = "HitN1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 67:
		{
			//[Normal Hit Avatar 1]
			f_String = "HitN1AV.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 68:
		{
			//[Normal Hit Self 1]
			f_String = "HitSelfN1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 69:
		{
			//[Normal Hit Self 2]
			f_String = "HitSelfN2.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 70:
		{
			//[Heavy Hit 1]
			f_String = "HitH1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 71:
		{
			//[Heavy Hit Self]
			f_String = "HitSelfH1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 72:
		{
			//[Ultra Hit Female]
			f_String = "UltraBlowFEMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 73:
		{
			//[Ultra Hit Male]
			f_String = "UltraBlowMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;

		case 74:
		{
			//[Block Hit]
			f_String = "HitB1.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 75:
		{
			//### Jink Sound
			f_String = "Jink.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 76:
		{
			//### Cleric Jink Sound
			f_String = "CJink.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 77:
		{
			//### Jink Sound
			f_String = "EJink.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 78:
		{
			//### Jink Sound
			f_String = "DeflectJink.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 79:
		{
			//###Jink Ready Sound
			f_String = "KeyLog.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 80:
		{
			//###Jink Ready Error Low Energy
			f_String = "KeyLogError.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 81:
		{
			//###Shock Block
			f_String = "ShockBlock.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 82:
		{
			//###Deflect Block
			f_String = "DefAttack.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 83:
		{
			//###Deflect Block
			f_String = "BrkBlock.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 84:
		{
			//###Flame Upper Cut Flames
			f_String = "UppCutFlames.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//##### - CLERIC SOUNDS - #####
		case 85:
		{
			//### Cleric Plasma
			f_String = "CPlasma.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;

		//##### - ATTACK INITIALISATIONS - #####
		case 86:
		{
			//### Attack Init Single Female
			f_String = "AttINITFEMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 87:
		{
			//### Attack Init Single Male
			f_String = "AttINITMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 88:
		{
			//### Attack Init Multiple Female
			f_String = "AttINITMULTFEMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 89:
		{
			//### Attack Init Multiple Male
			f_String = "AttINITMULTMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 90:
		{
			//### Attack Init Small Female
			f_String = "AttINITSMLFEMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 91:
		{
			//### Attack Init Small Female
			f_String = "AttINITSMLMALE.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//##### - KO SOUNDS - #####
		case 92:
		{
			//### Enemy KO
			f_String = "EnemyKO.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 93:
		{
			//### Player KO
			f_String = "PlayerKO.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		//###### Effects ######
		//### Mat Start
		case 94:
		{
			f_String = "mStart.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 95:
		{
			//### Mat End
			f_String = "mEnd.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 96:
		{
			//###Explosion
			f_String = "Explosion.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 97:
		{
			//###Explosion Small
			f_String = "Explosion3001.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 98:
		{
			//### Renzou Fire Left
			f_String = "RenzouLeft.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 99:
		{
			//### Renzou Fire Right
			f_String = "RenzouRight.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 100:
		{
			//### Renzou Fire Right
			f_String = "RenzouFireDouble.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 101:
		{
			//### Renzou
			f_String = "Renzou.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 102:
		{
			//### Had Warning
			f_String = "HadWarning.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 103:
		{
			//### Jink 3RD Level Charge
			f_String = "JINK3ChargeStart.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 104:
		{
			//### Jink 3RD Level Charge
			f_String = "JINK3Charge.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 105:
		{
			//### Jink 3RD Level Vocal
			f_String = "JINK3VOCAL.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 106:
		{
			//### Zone Capture
			f_String = "ZoneCapture.wav";
			printf("GetSound %s", f_String.c_str()); return f_String;
		}break;
		case 107:
		{
			//### Footsteps Capture
			f_String = "Footsteps.wav";
			printf("GetSound %s", f_String.c_str()); for (;;) {} return f_String;
		}break;
	}
}

void Q_COREFunctions::acSendSound(int f_Index)
{
	//##### - VEHICLE MOTORCYCLE - #####

	//[Bike Start]
	if(f_Index == 0)
		{
		Medias->S_VehMBStart = f_Index;
		}
	else if (f_Index == 1)
		{
		Medias->S_VehMBStartLoop = f_Index;// "QpoSound", "BikeLoop.wav");
		}
	else if (f_Index == 2)
		{
		Medias->S_VehMBSkid = f_Index;// "skid02.wav");
		}
	else if (f_Index == 3)
		{
		//[Bike Start Loop]
		Medias->S_VehMBPower = f_Index;// "BikeP.wav");
		}
	else if (f_Index == 4)
		{
		//[Bike Start Loop]
		Medias->S_VehMBLoopPower = f_Index;// "BikeLoopP.wav");
		}
	else if (f_Index == 5)
		{
		Medias->S_VehMBLoopPower2 = f_Index;// "BikeLoopP2.wav");
		}
	else if (f_Index == 6)
		{
		Medias->S_VehMBLoopPower3 = f_Index;// "BikeLoopP3.wav");
		}
	else if (f_Index == 7)
		{
		Medias->S_RifleFire[0] = f_Index;// "fire00.wav");
		}
	else if (f_Index == 8)
		{
		Medias->S_RifleFire[1] = f_Index;// "fire01.wav");
		}
	else if (f_Index == 9)
		{
		//[Bike Start Loop]
		Medias->S_RifleFire[2] = f_Index;// "fire02.wav");
		}
	else if (f_Index == 10)
		{
		//[Bike Start Loop]
		Medias->S_RifleFire[3] = f_Index;// "fire03.wav");
		}
	else if (f_Index == 11)
		{
		//[Bike Start Loop]
		Medias->S_RifleFire[4] = f_Index;// "fire04.wav");
		}
	else if (f_Index == 12)
		{
		//[Bike Start Loop]
		Medias->S_RifleFire[5] = f_Index;// "fire05.wav");
		}
	else if (f_Index == 13)
		{
		Medias->S_RifleFire[6] = f_Index;// "fire06.wav");
		}
	else if (f_Index == 14)
		{
		Medias->S_RifleFire[7] = f_Index;// "fire06.wav");
		}
	else if (f_Index == 15)
		{
		Medias->S_RifleFire[10] = f_Index;// "fire07.wav");
		}
	else if (f_Index == 16)
		{
		Medias->S_RifleFire[11] = f_Index;// "fire07.wav");
		}
	else if (f_Index == 17)
		{
		Medias->S_RifleClipOut[0] = f_Index;// "fire07.wav");
		}
	else if (f_Index == 18)
		{
		Medias->S_RifleClipOut[1] = f_Index;// "fire07.wav");
		}
	else if (f_Index == 19)
		{
		Medias->S_RifleClipOut[2] = f_Index;// "clipout00.wav");
		}
	else if (f_Index == 20)
		{
		Medias->S_RifleClipOut[3] = f_Index;// "clipout00.wav");
		}
	else if (f_Index == 21)
		{
		Medias->S_RifleClipOut[4] = f_Index;// "clipout02.wav");
		}
	else if (f_Index == 22)
		{
		Medias->S_RifleClipOut[5] = f_Index;// "clipout02.wav");
		}
	else if (f_Index == 23)
		{
		Medias->S_RifleClipOut[6] = f_Index;// "clipout04.wav");
		}
	else if (f_Index == 24)
		{
		Medias->S_RifleClipOut[7] = f_Index;// "clipout05.wav");
		}
	else if (f_Index == 25)
		{
		Medias->S_RifleClipIn[0] = f_Index;// "clipout06.wav");
		}
	else if (f_Index == 26)
		{
		Medias->S_RifleClipIn[1] = f_Index;// "clipout07.wav");
		}
	else if (f_Index == 27)
		{
		Medias->S_RifleClipIn[2] = f_Index;// "clipin00.wav");
		}
	else if (f_Index == 28)
		{
		Medias->S_RifleClipIn[3] = f_Index;// "clipin01.wav");
		}
	else if (f_Index == 29)
		{
		Medias->S_RifleClipIn[4] = f_Index;// "clipin02.wav");
		}
	else if (f_Index == 30)
		{
		Medias->S_RifleClipIn[5] = f_Index;// "clipin04.wav");
		}
	else if (f_Index == 31)
		{
		Medias->S_RifleClipIn[6] = f_Index;// "clipin05.wav");
		}
	else if (f_Index == 32)
		{
		Medias->S_RifleClipIn[7] = f_Index;// "clipin06.wav");
		}
	else if (f_Index == 33)
		{
		Medias->S_RifleBoltOut[0] = f_Index;// "clipin07.wav");
		}
	else if (f_Index == 34)
		{
		Medias->S_RifleBoltOut[0] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 35)
		{
		Medias->S_RifleBoltOut[1] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 36)
		{
		Medias->S_RifleBoltOut[2] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 37)
		{
		Medias->S_RifleBoltOut[3] = f_Index;// "boltslap00.wav");
		}	
	else if (f_Index == 38)
		{
		Medias->S_RifleBoltOut[4] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 39)
		{
		Medias->S_RifleBoltOut[5] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 40)
		{
		Medias->S_RifleBoltOut[6] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 41)
		{
		Medias->S_RifleBoltOut[7] = f_Index;// "boltslap00.wav");
		}
	else if (f_Index == 42)
		{
		Medias->S_RifleBoltIn[0] = f_Index;// "boltpull00.wav");
		}
	else if (f_Index == 43)
		{
		Medias->S_RifleBoltIn[1] = f_Index;// "boltpull01.wav");
		}
	else if (f_Index == 44)
		{
		Medias->S_RifleBoltIn[2] = f_Index;// "boltpull02.wav");
		}
	else if (f_Index == 45)
		{
		Medias->S_RifleBoltIn[3] = f_Index;// "boltpull02.wav");
		}
	else if (f_Index == 46)
		{
		Medias->S_RifleBoltIn[4] = f_Index;// "boltpull04.wav");
		}
	else if (f_Index == 47)
		{
		Medias->S_RifleBoltIn[5] = f_Index;// "boltpull05.wav");
		}
	else if (f_Index == 48)
		{
		Medias->S_Hitwall1 = f_Index;// "boltpull06.wav");
		}
	else if (f_Index == 49)
		{
		Medias->S_Hitwall2 = f_Index;// "boltpull07.wav");
		}
	else if (f_Index == 50)
		{
		Medias->S_Hitwall3 = f_Index;// "Hitwall\\Hitwall1.wav");
		}
	else if (f_Index == 51)
		{
		Medias->S_Hitwall4 = f_Index;// "Hitwall\\Hitwall2.wav");
		}
	else if (f_Index == 52)
		{
		Medias->SingleDef2 = f_Index;// "Hitwall\\Hitwall3.wav");
		}
	else if (f_Index == 53)
		{
		Medias->S_SwishN1 = f_Index;// "Hitwall\\Hitwall4.wav");
		}
	else if (f_Index == 54)
		{
		Medias->S_SwishN2 = f_Index;// "Hello.wav");
		}
	else if (f_Index == 55)
		{
		Medias->S_SwishN3 = f_Index;// "SwishN1.wav");
		}
	else if (f_Index == 56)
		{
		Medias->S_SwishN4 = f_Index;// "SwishN2.wav");
		}
	else if (f_Index = 57)
		{
		Medias->S_SwishH1 = f_Index;// "SwishN3.wav");
		}
	else if (f_Index == 58)
		{
		Medias->S_SwishH2 = f_Index;// "SwishN4.wav");
		}
	else if (f_Index == 59)
		{
		Medias->S_SwishSpin = f_Index;// "SwishH1.wav");
		}
	else if (f_Index == 60)
		{
		Medias->S_SwishH3FEMALE = f_Index;// "SwishH2.wav");
		}
	else if (f_Index == 61)
		{
		Medias->S_SwishH3MALE = f_Index;// "SwishSpin.wav");
		}
	else if (f_Index == 62)
		{
		Medias->S_RenzouImpact = f_Index;// "SwishH3FEMALE.wav");
		}
	else if (f_Index == 63)
		{
		Medias->S_FireCrackle = f_Index;// "SwishH3MALE.wav");
		}
	else if (f_Index == 64)
		{
		Medias->S_BulletHit = f_Index;// "RenzouImpact.wav");
		}
	else if (f_Index == 65)
		{
		Medias->S_BulletHitArmour = f_Index;// "FireCrackle.wav");
		}
	else if (f_Index == 66)
		{
		Medias->S_HitN1 = f_Index;// "BulletHit.wav");
		}
	else if (f_Index == 67)
		{
		Medias->S_HitN1AV = f_Index;// "BulletHitArmour.wav");
		}
	else if (f_Index == 68)
		{
		Medias->S_HitSelfN1 = f_Index;// "HitN1.wav");
		}
	else if (f_Index == 69)
		{
		Medias->S_HitSelfN2 = f_Index;// "HitN1AV.wav");
		}
	else if (f_Index == 70)
		{
		Medias->S_HitH1 = f_Index;// "HitSelfN1.wav");
		}
	else if (f_Index == 71)
		{
		Medias->S_HitSelfH1 = f_Index;// "HitSelfN2.wav");
		}
	else if (f_Index == 72)
		{
		Medias->S_UltraBlowFEMALE = f_Index;// "HitH1.wav");
		}
	else if (f_Index == 73)
		{
		Medias->S_UltraBlowMALE = f_Index;// "HitSelfH1.wav");
		}
	else if (f_Index == 74)
		{
		Medias->S_HitB1 = f_Index;// "UltraBlowFEMALE.wav");
		}
	else if (f_Index == 75)
		{
		Medias->S_Jink = f_Index;// "UltraBlowMALE.wav");
		}
	else if (f_Index == 76)
		{
		Medias->S_CJink = f_Index;// "HitB1.wav");
		}
	else if (f_Index == 77)
		{
		Medias->S_EJink = f_Index;// "Jink.wav");
		}
	else if (f_Index == 78)
		{
		Medias->S_BJink = f_Index;// "CJink.wav");
		}
	else if (f_Index == 79)
		{
		Medias->S_KeyLog = f_Index;// "EJink.wav");
		}
	else if (f_Index == 80)
		{
		Medias->S_KeyLogError = f_Index;// "DeflectJink.wav");
		}
	else if (f_Index == 81)
		{
		Medias->S_ShkBlock = f_Index;// "KeyLog.wav");
		}
	else if (f_Index == 82)
		{
		Medias->S_DefBlock = f_Index;// "KeyLogError.wav");
		}
	else if (f_Index == 83)
		{
		Medias->S_BrkBlock = f_Index;// "ShockBlock.wav");
		}
	else if (f_Index == 84)
		{
		Medias->S_UppCutFlames = f_Index;// "DefAttack.wav");
		}
	else if (f_Index == 85)
		{
		Medias->S_CPlasma = f_Index;// "BrkBlock.wav");
		}
	else if (f_Index == 86)
		{
		Medias->S_AttINITFEMALE = f_Index;// "UppCutFlames.wav");
		}
	else if (f_Index == 87)
		{
		Medias->S_AttINITMALE = f_Index;// "CPlasma.wav");
		}
	else if (f_Index == 88)
		{
		Medias->S_AttINITMULTFEMALE = f_Index;// "AttINITFEMALE.wav");
		}
	else if (f_Index == 89)
		{
		Medias->S_AttINITMULTMALE = f_Index;// "AttINITMALE.wav");
		}
	else if (f_Index == 90)
		{
		Medias->S_AttINITSMLFEMALE = f_Index;// "AttINITMULTFEMALE.wav");
		}
	else if (f_Index == 91)
		{
		Medias->S_AttINITSMLMALE = f_Index;// "AttINITMULTMALE.wav");
		}
	else if (f_Index == 92)
		{
		Medias->S_EnemyKO = f_Index;// "AttINITSMLFEMALE.wav");
		}
	else if (f_Index == 93)
		{
		Medias->S_PlayerKO = f_Index;// "AttINITSMLMALE.wav");
		}
	else if (f_Index == 94)
		{
		Medias->S_MatStart = f_Index;// "EnemyKO.wav");
		}
	else if (f_Index == 95)
		{
		Medias->S_MatEnd = f_Index;// "PlayerKO.wav");
		}
	else if (f_Index == 96)
		{
		Medias->S_Explosion = f_Index;// "mStart.wav");
		}
	else if (f_Index == 97)
		{
		Medias->S_Explosion3000 = f_Index;// "mEnd.wav");
		}
	else if (f_Index == 98)
		{
		Medias->S_RenzouFireLeft = f_Index;// "Explosion.wav");
		}
	else if (f_Index == 99)
		{
		Medias->S_RenzouFireRight = f_Index;// "Explosion3001.wav");
		}
	else if (f_Index == 100)
		{
		Medias->S_RenzouFireDouble = f_Index;// "RenzouLeft.wav");
		}
	else if (f_Index == 101)
		{
		Medias->S_Renzou = f_Index;// "RenzouRight.wav");
		}
	else if (f_Index == 102)
		{
		Medias->S_HadWarning = f_Index;// "RenzouFireDouble.wav");
		}
	else if (f_Index == 103)
		{
		Medias->S_JINK3ChargeStart = f_Index;// "Renzou.wav");
		}
	else if (f_Index == 104)
		{
		Medias->S_JINK3Charge = f_Index;// "HadWarning.wav");
		}
	else if (f_Index == 105)
		{
		Medias->S_JINK3Vocal = f_Index;// "JINK3ChargeStart.wav");
		for (;;) {}
		}
	else if (f_Index == 106)
		{
		Medias->S_ZoneCapture = f_Index;// "BikeLoop.wav");
		}
	else if (f_Index == 107)
		{
		Medias->S_Footsteps = f_Index;
		printf("GetSound %i", f_Index); 
		}

	printf("GetSound %i", f_Index);

	printf("SOUND:::Sound Sent\n");
}

void Q_COREFunctions::CloseSounds(void)
{
#if 0
	//[BUILD]
	Qpo->Sound_Close(Medias->S_Build);

	//##### - VEHICLE MOTORCYCLE - #####

	//[Bike Start]
	Qpo->Sound_Close(Medias->S_VehMBStart);

	//[Bike Start Loop]
	Qpo->Sound_Close(Medias->S_VehMBStartLoop);

	//[Bike Skid]
	Qpo->Sound_Close(Medias->S_VehMBSkid);

	//[Bike Power]
	Qpo->Sound_Close(Medias->S_VehMBPower);

	//[Bike Power]
	Qpo->Sound_Close(Medias->S_VehMBLoopPower);
	
	//[Bike Power]
	Qpo->Sound_Close(Medias->S_VehMBLoopPower2);

	//[Bike Power]
	Qpo->Sound_Close(Medias->S_VehMBLoopPower3);

	//##### - Gun Sounds - #####

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[0]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[1]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[2]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[3]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[4]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[5]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[6]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[7]);

	//[Rifle] Fire]
	Qpo->Sound_Close(Medias->S_RifleFire[11]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[0]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[1]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[2]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[3]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[4]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[5]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[6]);

	//[Rifle] Clip Out]
	Qpo->Sound_Close(Medias->S_RifleClipOut[7]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[0]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[1]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[2]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[3]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[4]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[5]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[6]);

	//[Rifle] Clip In]
	Qpo->Sound_Close(Medias->S_RifleClipIn[7]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[0]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[1]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[2]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[3]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[4]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[5]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[6]);

	//[Rifle] Bolt Out]
	Qpo->Sound_Close(Medias->S_RifleBoltOut[7]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[0]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[1]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[2]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[3]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[4]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[5]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[6]);

	//[Rifle] Bolt In]
	Qpo->Sound_Close(Medias->S_RifleBoltIn[7]);

	//[Rifle] Bullet Hit Wall 1]
	Qpo->Sound_Close(Medias->S_Hitwall1);

	//[Rifle] Bullet Hit Wall 2]
	Qpo->Sound_Close(Medias->S_Hitwall2);

	//[Rifle] Bullet Hit Wall 3]
	Qpo->Sound_Close(Medias->S_Hitwall3);

	//[Rifle] Bullet Hit Wall 4]
	Qpo->Sound_Close(Medias->S_Hitwall4);

	//AI LogON
	Qpo->Sound_Close(Medias->SingleDef2);

	//Music??
	//Qpo->Sound_Close(Medias->LoopingDef3);

	////QNETWORKFrame();

	//#######-  Attack Sounds  -#######

	//### Attacking Noises

	//[Normal Swish 1]
	Qpo->Sound_Close(Medias->S_SwishN1);

	//[Normal Swish 2]
	Qpo->Sound_Close(Medias->S_SwishN2);

	//[Normal Swish 3]
	Qpo->Sound_Close(Medias->S_SwishN3);

	//[Normal Swish 4]
	Qpo->Sound_Close(Medias->S_SwishN4);

	//[Heavy Swish 1]
	Qpo->Sound_Close(Medias->S_SwishH1);

	//[Heavy Swish 2]
	Qpo->Sound_Close(Medias->S_SwishH2);

	//[Heavy Swish Spin]
	Qpo->Sound_Close(Medias->S_SwishSpin);

	//[Heavy Swish 3 Female]
	Qpo->Sound_Close(Medias->S_SwishH3FEMALE);

	//[Heavy Swish 3 Male]
	Qpo->Sound_Close(Medias->S_SwishH3MALE);

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Close(Medias->S_RenzouImpact);

	//### Renzou Hit

	//[Renzou Hit]
	Qpo->Sound_Close(Medias->S_FireCrackle);

	//### Attack Hits

	//[Bullet Hit Flesh]
	Qpo->Sound_Close(Medias->S_BulletHit);

	//[Bullet Hit Armour]
	Qpo->Sound_Close(Medias->S_BulletHitArmour);

	//[Normal Hit 1]
	Qpo->Sound_Close(Medias->S_HitN1);

	//[Normal Hit Avatar 1]
	Qpo->Sound_Close(Medias->S_HitN1AV);

	//[Normal Hit Self 1]
	Qpo->Sound_Close(Medias->S_HitSelfN1);

	//[Normal Hit Self 2]
	Qpo->Sound_Close(Medias->S_HitSelfN2);

	//[Heavy Hit 1]
	Qpo->Sound_Close(Medias->S_HitH1);

	//[Heavy Hit Self]
	Qpo->Sound_Close(Medias->S_HitSelfH1);

	//[Ultra Hit Female]
	Qpo->Sound_Close(Medias->S_UltraBlowFEMALE);

	//[Ultra Hit Male]
	Qpo->Sound_Close(Medias->S_UltraBlowMALE);
	

	//[Block Hit]
	Qpo->Sound_Close(Medias->S_HitB1);

	//### Jink Sound
	Qpo->Sound_Close(Medias->S_Jink);

	//### Cleric Jink Sound
	Qpo->Sound_Close(Medias->S_CJink);

	//### Jink Sound
	Qpo->Sound_Close(Medias->S_EJink);

	//### Jink Sound
	Qpo->Sound_Close(Medias->S_BJink);
	
	//###Jink Ready Sound
	Qpo->Sound_Close(Medias->S_KeyLog);
	
	//###Jink Ready Error Low Energy
	Qpo->Sound_Close(Medias->S_KeyLogError);

	//###Shock Block
	Qpo->Sound_Close(Medias->S_ShkBlock);
	
	//###Deflect Block
	Qpo->Sound_Close(Medias->S_DefBlock);

	//###Deflect Block
	Qpo->Sound_Close(Medias->S_BrkBlock);
	
	//###Flame Upper Cut Flames
	Qpo->Sound_Close(Medias->S_UppCutFlames);
	
	//##### - CLERIC SOUNDS - #####

	//### Cleric Plasma
	Qpo->Sound_Close(Medias->S_CPlasma);
	
	//##### - ATTACK INITIALISATIONS - #####

	//### Attack Init Single Female
	Qpo->Sound_Close(Medias->S_AttINITFEMALE);

	//### Attack Init Single Male
	Qpo->Sound_Close(Medias->S_AttINITMALE);
	
	//### Attack Init Multiple Female
	Qpo->Sound_Close(Medias->S_AttINITMULTFEMALE);
	
	//### Attack Init Multiple Male
	Qpo->Sound_Close(Medias->S_AttINITMULTMALE);
	
	//### Attack Init Small Female
	Qpo->Sound_Close(Medias->S_AttINITSMLFEMALE);
	
	//### Attack Init Small Female
	Qpo->Sound_Close(Medias->S_AttINITSMLMALE);

	//##### - KO SOUNDS - #####

	//### Enemy KO
	Qpo->Sound_Close(Medias->S_EnemyKO);

	//### Player KO
	Qpo->Sound_Close(Medias->S_PlayerKO);
	
	//###### Effects ######
	//### Mat Start
	Qpo->Sound_Close(Medias->S_MatStart);

	//### Mat End
	Qpo->Sound_Close(Medias->S_MatEnd);
	
	//###Explosion
	Qpo->Sound_Close(Medias->S_Explosion);
	
	//###Explosion Small
	Qpo->Sound_Close(Medias->S_Explosion3000);
	
	//### Renzou Fire Left
	Qpo->Sound_Close(Medias->S_RenzouFireLeft);
	
	//### Renzou Fire Right
	Qpo->Sound_Close(Medias->S_RenzouFireRight);
	
	//### Renzou Fire Right
	Qpo->Sound_Close(Medias->S_RenzouFireDouble);
	
	//### Renzou
	Qpo->Sound_Close(Medias->S_Renzou);
	
	//### Had Warning
	Qpo->Sound_Close(Medias->S_HadWarning);
	
	//### Jink 3RD Level Charge
	Qpo->Sound_Close(Medias->S_JINK3ChargeStart);

	//### Jink 3RD Level Charge
	Qpo->Sound_Close(Medias->S_JINK3Charge);

	//### Jink 3RD Level Vocal
	Qpo->Sound_Close(Medias->S_JINK3Vocal);
	
	//### Zone Capture
	Qpo->Sound_Close(Medias->S_ZoneCapture);
	
	//### Footsteps Capture
	Qpo->Sound_Close(Medias->S_Footsteps);
#else
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Mix_FreeChunk( low );
#endif

	//### Close Sound API ###//
	Qpo->Sound_Shutdown();
}

};

//**********************************************************************************************************
//**********************************************************************************************************
//**********************************************************************************************************

#pragma message ("###  Initialising Sounds  [Q-InitSounds.h]")
