/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Digital Enviroment-
	*/#include "pch.h"/*- Minor Component -Bitmap Initialization-

*/

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

#include "Texture/untexturebank.h"

#define UN_TEXTURE_TGA 0
#define UN_TEXTURE_PNG 1
#define UN_TEXTURE_ALP 2

winrt::Windows::Foundation::IAsyncAction mTexLoadingLoopWorker;

unTextureBank* g_TextureBank;

#if 0
using winrt::Windows::Foundation::Uri;
using winrt::Windows::Storage::FileAccessMode;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using winrt::Windows::Storage::StorageFile;
#endif

using namespace GVARS;

namespace GVARS
{

#if 0
std::future<unsigned int> acLoadfromStorageFile(int f_Int, winrt::Windows::Storage::StorageFile f_StorageFile, std::string f_FilePath)
{
	unsigned int f_Resource;

	switch(f_Int)
		{
		case UN_TEXTURE_TGA:
			{
			winrt::hstring fileToken;

			fileToken = AccessCache::StorageApplicationPermissions::FutureAccessList().Add(f_StorageFile, f_StorageFile.Name());

			if(fileToken.size() != 0)
				{
				// Windows will call the server app to update the local version of the file
				::winrt::Windows::Storage::StorageFile f_LoadsFile = co_await AccessCache::StorageApplicationPermissions::FutureAccessList().GetFileAsync(fileToken);

				//StorageFolder localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

				//winrt::hstring f_LocalPathString = localFolder.Path();

				std::string f_StringPath = to_string(f_LoadsFile.Path());

				f_Resource = g_TextureBank->GLloadTGA(f_StringPath.c_str());

#if 0
				printf("Loaded %i Texture %s\n", global_Resource, g_StringPath.c_str());
#endif
				}
			}break;

		case UN_TEXTURE_PNG:
			{
			
			}break;

		case UN_TEXTURE_ALP:
			{
			
			}break;
		}

	co_return f_Resource;
}
#endif

unsigned int Q_COREFunctions::acLoadTextureAlpha(std::string f_Path, std::string f_Filename, int f_Int)
{
	return 1;
}

unsigned int Q_COREFunctions::acLoadTexture(int f_Int, std::string f_File)
{
#if 0
	std::string f_PreString = "ms-appx:///";
	std::string f_FilePath = f_PreString + f_File;
	
	winrt::Windows::Storage::StorageFile inputFile{ (nullptr) };

	Uri f_Uri = Uri(StrUsingStr(f_FilePath));

	::winrt::Windows::Storage::StorageFile f_LoadsFile = co_await inputFile.GetFileFromApplicationUriAsync(f_Uri);
	
	co_return acLoadfromStorageFile(f_Int, f_LoadsFile, f_File);
#endif

	return 0;
}

void Q_COREFunctions::InitTextures(void)
{
	Medias->shadow = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadow.tga");

	Medias->shadowA2 = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\shadowa00G12.png");

	Medias->reticuleE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\reticuleE.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->shineE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shineE.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QAEFF01 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF01.tga");

	Medias->QAEFF03 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF03.tga");

	Medias->QAEFF04 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF04.tga");

	Medias->QAEFF05 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.tga");

	Medias->QAEFF06 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF06.tga");

	Medias->QAEFF07 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.tga");

	Medias->QAEFF08 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.tga");

	Medias->QAEFF09 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF09.tga");

	Medias->QAEFF10 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF10.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QAEFF11 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF11.tga");

	Medias->QAEFF12 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF12.tga");

	Medias->QAEFF13 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.tga");

	Medias->QAEFF14 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF14.tga");

	Medias->QAEFF15 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF15.tga");

	Medias->QAEFF16 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF16.tga");

	Medias->QAEFF17 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF17.tga");

	Medias->QAEFF18 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF18.tga");

	Medias->QAEFF19 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF19.tga");

	Medias->QAEFF20 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF20.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QAEFF21 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF21.tga");

	Medias->QAEFF22 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF22.tga");

	Medias->QAEFF23 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF23.tga");

	Medias->QAEFF24 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF24.tga");

	Medias->QAEFF25 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF25.tga");

	Medias->QAEFF26 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF26.tga");

	Medias->QAEFF27 = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\QA_EFF\\J3L.png");

#if 0
	Medias->QAEFF28 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF28.tga");
#endif

	Medias->QAEFF28 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF51.tga");

	Medias->QAEFF29 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF29.tga");

	Medias->QAEFF30 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF30.tga");

#ifdef QAGE_SLOT
	Medias->Bonus = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Bonus.tga");

	Medias->Wild = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Wild.tga");
#endif

	Medias->QAEFF31 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF31.tga");

	Medias->QAEFF32 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF32.tga");

		//Reticule
	Medias->reticule = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\reticule.png");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		//Screen Panel
	Medias->toppanel = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\toppanel.png");
	Medias->icon = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\icon1.png");

	Medias->hudbottom1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealthBars\\hudbottom1.tga");

	#pragma message ("-  TODO Load Alpha Textures")

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->hudRadar = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDradar.png", "hudRadar", 0);

	Medias->hudbottom2 = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDbottom2.png", "Medias->hudbottom2", 255);
	Medias->hudbottom3 = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDbottom3.png", "Medias->hudbottom2", 255);

	Medias->Scope = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\ScopeA.png", "Scope", 1);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//Knock Out
	Medias->KObit[0] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\1.png", "Medias->KObit[0]", 0);
	Medias->KObit[1] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\2.png", "Medias->KObit[1]", 0);
	Medias->KObit[2] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\3.png", "Medias->KObit[2]", 0);
	Medias->KObit[3] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\4.png", "Medias->KObit[3]", 0);
	Medias->KObit[4] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\5.png", "Medias->KObit[4]", 0);
	Medias->KObit[5] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\6.png", "Medias->KObit[5]", 0);
	Medias->KObit[6] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\7.png", "Medias->KObit[6]", 0);
	Medias->KObit[7] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\8.png", "Medias->KObit[7]", 0);
	Medias->KObit[8] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\9.png", "Medias->KObit[8]", 0);
	Medias->KObit[9] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\10.png", "Medias->KObit[9]", 0);
	Medias->KObit[10] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\11.png", "Medias->KObit[10]", 0);
	Medias->KObit[11] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\KO\\12.png", "Medias->KObit[11]", 0);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->BulletCount = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletCount.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->HealthLeft = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarL.png", "Medias->HealthLeft", 0);
	Medias->HealthRight = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarR.png", "Medias->HealthRight", 0);
	Medias->HealthLeftEXT = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarLEXT.png", "Medias->HealthLeftEXT", 0);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->EnergyBarLeft = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\EnergyBarL.png", "Medias->EnergyBarLeft", 0);
	Medias->EnergyBarRight = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\EnergyBarR.png", "Medias->EnergyBarRight", 0);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RADspritesF[0] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF1.png", "Medias->RADspritesF[0]", 0);
	Medias->RADspritesF[1] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF2.png", "Medias->RADspritesF[1]", 0);
	Medias->RADspritesF[2] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF3.png", "Medias->RADspritesF[2]", 0);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RADspritesE[0] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE1.png", "Medias->RADspritesE[0]", 0);
	Medias->RADspritesE[1] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE2.png", "Medias->RADspritesE[1]", 0);
	Medias->RADspritesE[2] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE3.png", "Medias->RADspritesE[2]", 0);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->VaporCAP = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\VaporCAP.tga");

	Medias->VaporLINE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\VaporLINE.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Medias->DECAL SYSTEM
	Medias->DECAL[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[0].tga");

	Medias->DECAL[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[1].tga");

	Medias->DECAL[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[2].tga");

	Medias->DECAL[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[3].tga");

	Medias->DECAL[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[4].tga");

	Medias->DECAL[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[6].tga");

	Medias->DECAL[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[7].tga");

	Medias->DECAL[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[8].tga");

	Medias->DECAL[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[9].tga");

	Medias->DECAL[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[11].tga");

	Medias->DECAL[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[12].tga");

	Medias->DECAL[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[13].tga");

	Medias->DECAL[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[14].tga");

	Medias->DECAL[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[16].tga");

	Medias->DECAL[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[17].tga");

	Medias->DECAL[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[18].tga");

	Medias->DECAL[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[19].tga");

	Medias->DECAL[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[21].tga");

	Medias->DECAL[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[22].tga");

	Medias->DECAL[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[23].tga");

	Medias->DECAL[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[24].tga");

	Medias->DECAL[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[26].tga");

	Medias->DECAL[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[27].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### FONT SYSTEM
	Medias->FONT[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[0].tga");

	Medias->FONT[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[1].tga");

	Medias->FONT[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[2].tga");

	Medias->FONT[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[3].tga");

	Medias->FONT[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[4].tga");

	Medias->FONT[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->FONT[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[6].tga");

	Medias->FONT[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[7].tga");

	Medias->FONT[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[8].tga");

	Medias->FONT[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[9].tga");

	Medias->MESSAGES = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\MESSAGES.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		//Bullets
	Medias->bullet = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\bullet.tga");

	Medias->pyro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HitFlash\\pyro1.tga");

	Medias->pyro2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\pyro2.tga");

	Medias->cart1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\cartlb.tga");

	Medias->EXPexpandro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\EXPexpandro1.tga");

	Medias->expandro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowBLOCK.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->expandro2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\expandro2.tga");

	Medias->dot = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\WhiteS.png");

	Medias->lightning = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\lightning.tga");

	Medias->jinklightning = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\jinklightning.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->trail1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail1.tga");

	Medias->trail2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail2.tga");

	Medias->greeny = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny.tga");

	Medias->greeny2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny2.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->greenyN = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN.tga");

	Medias->greenyN2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN2.tga");

	Medias->spec = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\spec.tga");

	Medias->attsprite = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\attsprite.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Medias->SparkCorona[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[0].tga");

	Medias->SparkCorona[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[1].tga");

	Medias->SparkCorona[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[2].tga");

	Medias->SparkCorona[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[3].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Medias->EGrabCorona[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[0].tga");

	Medias->EGrabCorona[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[1].tga");

	Medias->EGrabCorona[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[2].tga");

	Medias->EGrabCorona[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[3].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	Medias->BlackOut = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BlackOut.tga");

	Medias->MFlashX = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashX.tga");

	Medias->MFlashS1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS1.tga");

	Medias->MFlashS2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS2.tga");

	Medias->MFlashS3 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS3.tga");

	Medias->LaserSight = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\LaserSight.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->BulletTrail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletTrail.tga");

	Medias->Text = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Text.tga");

	Medias->Spark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spark.tga");

	Medias->Sparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparkmid.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Sparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparktail.tga");

	Medias->HealSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSpark.tga");

	Medias->HealSparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSparkmid.tga");

	Medias->HealSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSparktail.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RanSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSpark.tga");

	Medias->EGrabSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\EGrabSparktail.tga");

	Medias->RanSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\BlackS.png");

	Medias->RanSparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSparkmid.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RanSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSparktail.tga");

	Medias->HealSphere = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSphere.tga");

	Medias->BulHitFlash = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlash.tga");

	Medias->BulHitFlashSpin = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashSpin.tga");

	Medias->Face = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Face.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//-----Clouds-----//

	Medias->Cloud1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud1.tga");

	Medias->Cloud2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud2.tga");

	Medias->Cloud3 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud3.tga");

	Medias->Cloud9 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud9.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->CloudBlood = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudBlood.tga");

	Medias->CloudLimb = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudLimb.tga");

	//---Scanner----//
	Medias->Scanner = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\Scanner\\Scanner.png");

	Medias->ScanBone = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBone.tga");

	Medias->ScanBox = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBox.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//---PEFMesh Textures
	Medias->FlameSingle = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\flamesingle.png");

	//### Better Spikes
	Medias->HHSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HHSpikeBmp.tga");

	//### Hadouken Spike
	Medias->HADSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HADSpikeBmp.tga");

	//### Spawn Spike
	Medias->SPAWNSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\SPAWNSpikeBmp.tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Special4
	Medias->special4[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[0].tga");

	Medias->special4[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[1].tga");

	Medias->special4[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[2].tga");

	Medias->special4[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[3].tga");

	Medias->special4[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[4].tga");

	Medias->special4[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->special4[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[6].tga");

	Medias->special4[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[7].tga");

	Medias->special4[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[8].tga");

	Medias->special4[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[9].tga");

	Medias->special4[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[10].tga");

	Medias->special4[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[11].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Flame		REQUIRED BY CLERIC
	Medias->flame[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[0].tga");

	Medias->flame[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[1].tga");

	Medias->flame[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[2].tga");

	Medias->flame[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[3].tga");

	Medias->flame[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[4].tga");

	Medias->flame[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flame[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[6].tga");

	Medias->flame[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[7].tga");

	Medias->flame[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[8].tga");

	Medias->flame[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[9].tga");

	Medias->flame[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flame[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[11].tga");

	Medias->flame[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[12].tga");

	Medias->flame[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[13].tga");

	Medias->flame[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[14].tga");

	Medias->flame[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////RAD fire
	Medias->radfire[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[0].tga");

	Medias->radfire[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[1].tga");

	Medias->radfire[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[2].tga");

	Medias->radfire[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[3].tga");

	Medias->radfire[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[4].tga");

	Medias->radfire[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->radfire[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[6].tga");

	Medias->radfire[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[7].tga");

	Medias->radfire[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[8].tga");

	Medias->radfire[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[9].tga");

	Medias->radfire[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->radfire[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[11].tga");

	Medias->radfire[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[12].tga");

	Medias->radfire[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[13].tga");

	Medias->radfire[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[14].tga");

	Medias->radfire[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Fire
	Medias->fire[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[82].tga");

	Medias->fire[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[83].tga");

	Medias->fire[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[84].tga");

	Medias->fire[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[85].tga");

	Medias->fire[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[86].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->fire[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[87].tga");

	Medias->fire[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[88].tga");

	Medias->fire[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[89].tga");

	Medias->fire[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[90].tga");

	Medias->fire[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[91].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->fire[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[92].tga");

	Medias->fire[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[93].tga");

	Medias->fire[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[94].tga");

	Medias->fire[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[95].tga");

	Medias->fire[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[96].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////Flame Trails
	Medias->flametrail[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[82].tga");

	Medias->flametrail[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[83].tga");

	Medias->flametrail[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[84].tga");

	Medias->flametrail[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[85].tga");

	Medias->flametrail[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[86].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flametrail[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[87].tga");

	Medias->flametrail[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[88].tga");

	Medias->flametrail[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[89].tga");

	Medias->flametrail[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[90].tga");

	Medias->flametrail[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[91].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flametrail[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[92].tga");

	Medias->flametrail[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[93].tga");

	Medias->flametrail[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[94].tga");

	Medias->flametrail[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[95].tga");

	Medias->flametrail[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[96].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		////////////Pulsar
	Medias->Pulsar[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[11].tga");

	Medias->Pulsar[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[12].tga");

	Medias->Pulsar[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[13].tga");

	Medias->Pulsar[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[14].tga");

	Medias->Pulsar[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[16].tga");

	Medias->Pulsar[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[17].tga");

	Medias->Pulsar[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[18].tga");

	Medias->Pulsar[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[19].tga");

	Medias->Pulsar[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[21].tga");

	Medias->Pulsar[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[22].tga");

	Medias->Pulsar[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[23].tga");

	Medias->Pulsar[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[24].tga");

	Medias->Pulsar[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[26].tga");

	Medias->Pulsar[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[27].tga");

	Medias->Pulsar[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[28].tga");

	Medias->Pulsar[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[29].tga");

	Medias->Pulsar[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[30].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[31].tga");

	Medias->Pulsar[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[32].tga");

	Medias->Pulsar[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[33].tga");

	Medias->Pulsar[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[34].tga");

	Medias->Pulsar[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[35].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[36].tga");

	Medias->Pulsar[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[37].tga");

	Medias->Pulsar[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[38].tga");

	Medias->Pulsar[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[39].tga");

	Medias->Pulsar[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[40].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[41].tga");

	Medias->Pulsar[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[42].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////Pulsar Mid
	Medias->PulsarMid[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[11].tga");

	Medias->PulsarMid[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[12].tga");

	Medias->PulsarMid[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[13].tga");

	Medias->PulsarMid[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[14].tga");

	Medias->PulsarMid[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[16].tga");

	Medias->PulsarMid[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[17].tga");

	Medias->PulsarMid[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[18].tga");

	Medias->PulsarMid[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[19].tga");

	Medias->PulsarMid[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[21].tga");

	Medias->PulsarMid[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[22].tga");

	Medias->PulsarMid[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[23].tga");

	Medias->PulsarMid[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[24].tga");

	Medias->PulsarMid[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[26].tga");

	Medias->PulsarMid[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[27].tga");

	Medias->PulsarMid[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[28].tga");

	Medias->PulsarMid[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[29].tga");

	Medias->PulsarMid[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[30].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[31].tga");

	Medias->PulsarMid[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[32].tga");

	Medias->PulsarMid[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[33].tga");

	Medias->PulsarMid[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[34].tga");

	Medias->PulsarMid[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[35].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[36].tga");

	Medias->PulsarMid[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[37].tga");

	Medias->PulsarMid[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[38].tga");

	Medias->PulsarMid[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[39].tga");

	Medias->PulsarMid[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[40].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[41].tga");

	Medias->PulsarMid[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[42].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//##### Rocket engine
	Medias->Rocket[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[0].tga");

	Medias->Rocket[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[1].tga");

	Medias->Rocket[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[2].tga");

	Medias->Rocket[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[3].tga");

	Medias->Rocket[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[4].tga");

	Medias->Rocket[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Rocket[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[6].tga");

	Medias->Rocket[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[7].tga");

	Medias->Rocket[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[8].tga");

	Medias->Rocket[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[9].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//##### Rocket engine
	Medias->Star[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[0].tga");

	Medias->Star[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[1].tga");

	Medias->Star[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[2].tga");

	Medias->Star[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[3].tga");

	Medias->Star[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[4].tga");

	Medias->Star[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[6].tga");

	Medias->Star[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[7].tga");

	Medias->Star[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[8].tga");

	Medias->Star[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[9].tga");

	Medias->Star[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[11].tga");

	Medias->Star[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[12].tga");

	Medias->Star[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[13].tga");

	Medias->Star[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[14].tga");

	Medias->Star[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[16].tga");

	Medias->Star[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[17].tga");

	Medias->Star[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[18].tga");

	Medias->Star[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[19].tga");

	Medias->Star[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[21].tga");

	Medias->Star[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[22].tga");

	Medias->Star[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[23].tga");

	Medias->Star[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[24].tga");

	Medias->Star[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	//#### Medias->Water
	Medias->Water[124] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[124].tga");

	Medias->Water[125] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[125].tga");

	Medias->Water[126] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[126].tga");

	Medias->Water[127] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[127].tga");

	Medias->Water[128] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[128].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Water[129] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[129].tga");

	Medias->Water[130] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[130].tga");

	Medias->Water[131] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[131].tga");

	Medias->Water[132] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[132].tga");

	Medias->Water[133] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[133].tga");

	Medias->Water[134] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[134].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Water[135] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[135].tga");

	Medias->Water[136] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[136].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//Mine build sign
	Medias->mmine = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\mmine.tga");

			//Build Menu
	Medias->buildm = Qpo->Tex_LoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\buildmenu.png");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//##### CLOUD SMOKE
	Medias->QSmoke[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[0].tga");

	Medias->QSmoke[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[1].tga");

	Medias->QSmoke[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[2].tga");

	Medias->QSmoke[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[3].tga");

	Medias->QSmoke[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[4].tga");

	Medias->QSmoke[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[6].tga");

	Medias->QSmoke[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[7].tga");

	Medias->QSmoke[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[8].tga");

	Medias->QSmoke[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[9].tga");

	Medias->QSmoke[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[11].tga");

	Medias->QSmoke[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[12].tga");

	Medias->QSmoke[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[13].tga");

	Medias->QSmoke[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[14].tga");

	Medias->QSmoke[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[16].tga");

	Medias->QSmoke[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[17].tga");

	Medias->QSmoke[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[18].tga");

	Medias->QSmoke[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[19].tga");

	Medias->QSmoke[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[21].tga");

	Medias->QSmoke[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[22].tga");

	Medias->QSmoke[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[23].tga");

	Medias->QSmoke[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[24].tga");

	Medias->QSmoke[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[26].tga");

	Medias->QSmoke[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[27].tga");

	Medias->QSmoke[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[28].tga");

	Medias->QSmoke[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[29].tga");

	Medias->QSmoke[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[30].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[31].tga");

	Medias->QSmoke[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[32].tga");

	Medias->QSmoke[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[33].tga");

	Medias->QSmoke[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[34].tga");

	Medias->QSmoke[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[35].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[36].tga");

	Medias->QSmoke[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[37].tga");

	Medias->QSmoke[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[38].tga");

	Medias->QSmoke[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[39].tga");

	Medias->QSmoke[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[40].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[41].tga");

	Medias->QSmoke[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[42].tga");

	Medias->QSmoke[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[43].tga");

	Medias->QSmoke[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[44].tga");

	Medias->QSmoke[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[45].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[46] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[46].tga");

	Medias->QSmoke[47] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[47].tga");

	Medias->QSmoke[48] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[48].tga");

	Medias->QSmoke[49] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[49].tga");


if(0)
	{
	//##### JINK ENERGY
	Medias->JEnergy[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

	Medias->JEnergy[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

	Medias->JEnergy[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

	Medias->JEnergy[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

	Medias->JEnergy[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

	Medias->JEnergy[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

	Medias->JEnergy[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

	Medias->JEnergy[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

	Medias->JEnergy[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

	Medias->JEnergy[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

	Medias->JEnergy[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

	Medias->JEnergy[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

	Medias->JEnergy[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

	Medias->JEnergy[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[16].tga");

	Medias->JEnergy[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[17].tga");

	Medias->JEnergy[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[18].tga");

	Medias->JEnergy[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[19].tga");

	Medias->JEnergy[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[20].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[21].tga");

	Medias->JEnergy[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[22].tga");

	Medias->JEnergy[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[23].tga");

	Medias->JEnergy[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[24].tga");

	Medias->JEnergy[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[25].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[26].tga");

	Medias->JEnergy[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[27].tga");

	Medias->JEnergy[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[28].tga");

	Medias->JEnergy[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[29].tga");

	Medias->JEnergy[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[30].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[31].tga");

	Medias->JEnergy[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[32].tga");

	Medias->JEnergy[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[33].tga");

	Medias->JEnergy[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[34].tga");

	Medias->JEnergy[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[35].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[36].tga");

	Medias->JEnergy[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[37].tga");

	Medias->JEnergy[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[38].tga");

	Medias->JEnergy[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[39].tga");

	Medias->JEnergy[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[40].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[41].tga");

	Medias->JEnergy[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[42].tga");

	Medias->JEnergy[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[43].tga");

	Medias->JEnergy[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[44].tga");

	Medias->JEnergy[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[45].tga");
	}

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//COMPACT  JINK ENERGY BITMAP
	Medias->JEnergy[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

	Medias->JEnergy[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

	Medias->JEnergy[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

	Medias->JEnergy[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

	Medias->JEnergy[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

	Medias->JEnergy[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

	Medias->JEnergy[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

	Medias->JEnergy[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

	Medias->JEnergy[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

	Medias->JEnergy[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

	Medias->JEnergy[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

	Medias->JEnergy[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

	Medias->JEnergy[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

	Medias->JEnergy[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif
}

void Q_COREFunctions::CloseTextures(void)
{
	Qpo->Tex_Delete(Medias->shadow);

	Qpo->Tex_Delete(Medias->shadowA2);

	Qpo->Tex_Delete(Medias->reticuleE);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->shineE);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QAEFF01);

	Qpo->Tex_Delete(Medias->QAEFF03);

	Qpo->Tex_Delete(Medias->QAEFF04);

	Qpo->Tex_Delete(Medias->QAEFF05);

	Qpo->Tex_Delete(Medias->QAEFF06);

	Qpo->Tex_Delete(Medias->QAEFF07);

	Qpo->Tex_Delete(Medias->QAEFF08);

	Qpo->Tex_Delete(Medias->QAEFF09);

	Qpo->Tex_Delete(Medias->QAEFF10);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QAEFF11);

	Qpo->Tex_Delete(Medias->QAEFF12);

	Qpo->Tex_Delete(Medias->QAEFF13);

	Qpo->Tex_Delete(Medias->QAEFF14);

	Qpo->Tex_Delete(Medias->QAEFF15);

	Qpo->Tex_Delete(Medias->QAEFF16);

	Qpo->Tex_Delete(Medias->QAEFF17);

	Qpo->Tex_Delete(Medias->QAEFF18);

	Qpo->Tex_Delete(Medias->QAEFF19);

	Qpo->Tex_Delete(Medias->QAEFF20);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QAEFF21);

	Qpo->Tex_Delete(Medias->QAEFF22);

	Qpo->Tex_Delete(Medias->QAEFF23);

	Qpo->Tex_Delete(Medias->QAEFF24);

	Qpo->Tex_Delete(Medias->QAEFF25);

	Qpo->Tex_Delete(Medias->QAEFF26);

	Qpo->Tex_Delete(Medias->QAEFF27);

	Qpo->Tex_Delete(Medias->QAEFF28);

	Qpo->Tex_Delete(Medias->QAEFF29);

	Qpo->Tex_Delete(Medias->QAEFF30);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QAEFF31);

	Qpo->Tex_Delete(Medias->QAEFF32);

		//Reticule
	Qpo->Tex_Delete(Medias->reticule);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		//Screen Panel
	Qpo->Tex_Delete(Medias->toppanel);
	Qpo->Tex_Delete(Medias->icon);

	Qpo->Tex_Delete(Medias->hudbottom1);

	#pragma message ("-  TODO Load Alpha Textures")

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->hudRadar);

	Qpo->Tex_Delete(Medias->hudbottom2);
	Qpo->Tex_Delete(Medias->hudbottom3);

	Qpo->Tex_Delete(Medias->Scope);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//Knock Out
	Qpo->Tex_Delete(Medias->KObit[0]);
	Qpo->Tex_Delete(Medias->KObit[1]);
	Qpo->Tex_Delete(Medias->KObit[2]);
	Qpo->Tex_Delete(Medias->KObit[3]);
	Qpo->Tex_Delete(Medias->KObit[4]);
	Qpo->Tex_Delete(Medias->KObit[5]);
	Qpo->Tex_Delete(Medias->KObit[6]);
	Qpo->Tex_Delete(Medias->KObit[7]);
	Qpo->Tex_Delete(Medias->KObit[8]);
	Qpo->Tex_Delete(Medias->KObit[9]);
	Qpo->Tex_Delete(Medias->KObit[10]);
	Qpo->Tex_Delete(Medias->KObit[11]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->BulletCount);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->HealthLeft);
	Qpo->Tex_Delete(Medias->HealthRight);
	Qpo->Tex_Delete(Medias->HealthLeftEXT);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->EnergyBarLeft);
	Qpo->Tex_Delete(Medias->EnergyBarRight);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->RADspritesF[0]);
	Qpo->Tex_Delete(Medias->RADspritesF[1]);
	Qpo->Tex_Delete(Medias->RADspritesF[2]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->RADspritesE[0]);
	Qpo->Tex_Delete(Medias->RADspritesE[1]);
	Qpo->Tex_Delete(Medias->RADspritesE[2]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->VaporCAP);

	Qpo->Tex_Delete(Medias->VaporLINE);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Medias->DECAL SYSTEM
	Qpo->Tex_Delete(Medias->DECAL[0]);

	Qpo->Tex_Delete(Medias->DECAL[1]);

	Qpo->Tex_Delete(Medias->DECAL[2]);

	Qpo->Tex_Delete(Medias->DECAL[3]);

	Qpo->Tex_Delete(Medias->DECAL[4]);

	Qpo->Tex_Delete(Medias->DECAL[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->DECAL[6]);

	Qpo->Tex_Delete(Medias->DECAL[7]);

	Qpo->Tex_Delete(Medias->DECAL[8]);

	Qpo->Tex_Delete(Medias->DECAL[9]);

	Qpo->Tex_Delete(Medias->DECAL[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->DECAL[11]);

	Qpo->Tex_Delete(Medias->DECAL[12]);

	Qpo->Tex_Delete(Medias->DECAL[13]);

	Qpo->Tex_Delete(Medias->DECAL[14]);

	Qpo->Tex_Delete(Medias->DECAL[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->DECAL[16]);

	Qpo->Tex_Delete(Medias->DECAL[17]);

	Qpo->Tex_Delete(Medias->DECAL[18]);

	Qpo->Tex_Delete(Medias->DECAL[19]);

	Qpo->Tex_Delete(Medias->DECAL[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->DECAL[21]);

	Qpo->Tex_Delete(Medias->DECAL[22]);

	Qpo->Tex_Delete(Medias->DECAL[23]);

	Qpo->Tex_Delete(Medias->DECAL[24]);

	Qpo->Tex_Delete(Medias->DECAL[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->DECAL[26]);

	Qpo->Tex_Delete(Medias->DECAL[27]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### FONT SYSTEM
	Qpo->Tex_Delete(Medias->FONT[0]);

	Qpo->Tex_Delete(Medias->FONT[1]);

	Qpo->Tex_Delete(Medias->FONT[2]);

	Qpo->Tex_Delete(Medias->FONT[3]);

	Qpo->Tex_Delete(Medias->FONT[4]);

	Qpo->Tex_Delete(Medias->FONT[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->FONT[6]);

	Qpo->Tex_Delete(Medias->FONT[7]);

	Qpo->Tex_Delete(Medias->FONT[8]);

	Qpo->Tex_Delete(Medias->FONT[9]);

	Qpo->Tex_Delete(Medias->MESSAGES);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		//Bullets
	Qpo->Tex_Delete(Medias->bullet);

	Qpo->Tex_Delete(Medias->pyro1);

	Qpo->Tex_Delete(Medias->pyro2);

	Qpo->Tex_Delete(Medias->cart1);

	Qpo->Tex_Delete(Medias->EXPexpandro1);

	Qpo->Tex_Delete(Medias->expandro1);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->expandro2);

	Qpo->Tex_Delete(Medias->dot);

	Qpo->Tex_Delete(Medias->lightning);

	Qpo->Tex_Delete(Medias->jinklightning);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->trail1);

	Qpo->Tex_Delete(Medias->trail2);

	Qpo->Tex_Delete(Medias->greeny);

	Qpo->Tex_Delete(Medias->greeny2);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->greenyN);

	Qpo->Tex_Delete(Medias->greenyN2);

	Qpo->Tex_Delete(Medias->spec);

	Qpo->Tex_Delete(Medias->attsprite);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Qpo->Tex_Delete(Medias->SparkCorona[0]);

	Qpo->Tex_Delete(Medias->SparkCorona[1]);

	Qpo->Tex_Delete(Medias->SparkCorona[2]);

	Qpo->Tex_Delete(Medias->SparkCorona[3]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Qpo->Tex_Delete(Medias->EGrabCorona[0]);

	Qpo->Tex_Delete(Medias->EGrabCorona[1]);

	Qpo->Tex_Delete(Medias->EGrabCorona[2]);

	Qpo->Tex_Delete(Medias->EGrabCorona[3]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	Qpo->Tex_Delete(Medias->BlackOut);

	Qpo->Tex_Delete(Medias->MFlashX);

	Qpo->Tex_Delete(Medias->MFlashS1);

	Qpo->Tex_Delete(Medias->MFlashS2);

	Qpo->Tex_Delete(Medias->MFlashS3);

	Qpo->Tex_Delete(Medias->LaserSight);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->BulletTrail);

	Qpo->Tex_Delete(Medias->Text);

	Qpo->Tex_Delete(Medias->Spark);

	Qpo->Tex_Delete(Medias->Sparkmid);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Sparktail);

	Qpo->Tex_Delete(Medias->HealSpark);

	Qpo->Tex_Delete(Medias->HealSparkmid);

	Qpo->Tex_Delete(Medias->HealSparktail);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->RanSpark);

	Qpo->Tex_Delete(Medias->EGrabSparktail);

	Qpo->Tex_Delete(Medias->RanSpark);

	Qpo->Tex_Delete(Medias->RanSparkmid);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->RanSparktail);

	Qpo->Tex_Delete(Medias->HealSphere);

	Qpo->Tex_Delete(Medias->BulHitFlash);

	Qpo->Tex_Delete(Medias->BulHitFlashSpin);

	Qpo->Tex_Delete(Medias->Face);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//-----Clouds-----//

	Qpo->Tex_Delete(Medias->Cloud1);

	Qpo->Tex_Delete(Medias->Cloud2);

	Qpo->Tex_Delete(Medias->Cloud3);

	Qpo->Tex_Delete(Medias->Cloud9);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->CloudBlood);

	Qpo->Tex_Delete(Medias->CloudLimb);

	//---Scanner----//
	Qpo->Tex_Delete(Medias->Scanner);

	Qpo->Tex_Delete(Medias->ScanBone);

	Qpo->Tex_Delete(Medias->ScanBox);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//---PEFMesh Textures
	Qpo->Tex_Delete(Medias->FlameSingle);

	//### Better Spikes
	Qpo->Tex_Delete(Medias->HHSpikeBmp);

	//### Hadouken Spike
	Qpo->Tex_Delete(Medias->HADSpikeBmp);

	//### Spawn Spike
	Qpo->Tex_Delete(Medias->SPAWNSpikeBmp);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Special4
	Qpo->Tex_Delete(Medias->special4[0]);

	Qpo->Tex_Delete(Medias->special4[1]);

	Qpo->Tex_Delete(Medias->special4[2]);

	Qpo->Tex_Delete(Medias->special4[3]);

	Qpo->Tex_Delete(Medias->special4[4]);

	Qpo->Tex_Delete(Medias->special4[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->special4[6]);

	Qpo->Tex_Delete(Medias->special4[7]);

	Qpo->Tex_Delete(Medias->special4[8]);

	Qpo->Tex_Delete(Medias->special4[9]);

	Qpo->Tex_Delete(Medias->special4[10]);

	Qpo->Tex_Delete(Medias->special4[11]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Flame		REQUIRED BY CLERIC
	Qpo->Tex_Delete(Medias->flame[0]);

	Qpo->Tex_Delete(Medias->flame[1]);

	Qpo->Tex_Delete(Medias->flame[2]);

	Qpo->Tex_Delete(Medias->flame[3]);

	Qpo->Tex_Delete(Medias->flame[4]);

	Qpo->Tex_Delete(Medias->flame[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->flame[6]);

	Qpo->Tex_Delete(Medias->flame[7]);

	Qpo->Tex_Delete(Medias->flame[8]);

	Qpo->Tex_Delete(Medias->flame[9]);

	Qpo->Tex_Delete(Medias->flame[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->flame[11]);

	Qpo->Tex_Delete(Medias->flame[12]);

	Qpo->Tex_Delete(Medias->flame[13]);

	Qpo->Tex_Delete(Medias->flame[14]);

	Qpo->Tex_Delete(Medias->flame[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////RAD fire
	Qpo->Tex_Delete(Medias->radfire[0]);

	Qpo->Tex_Delete(Medias->radfire[1]);

	Qpo->Tex_Delete(Medias->radfire[2]);

	Qpo->Tex_Delete(Medias->radfire[3]);

	Qpo->Tex_Delete(Medias->radfire[4]);

	Qpo->Tex_Delete(Medias->radfire[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->radfire[6]);

	Qpo->Tex_Delete(Medias->radfire[7]);

	Qpo->Tex_Delete(Medias->radfire[8]);

	Qpo->Tex_Delete(Medias->radfire[9]);

	Qpo->Tex_Delete(Medias->radfire[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->radfire[11]);

	Qpo->Tex_Delete(Medias->radfire[12]);

	Qpo->Tex_Delete(Medias->radfire[13]);

	Qpo->Tex_Delete(Medias->radfire[14]);

	Qpo->Tex_Delete(Medias->radfire[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Fire
	Qpo->Tex_Delete(Medias->fire[82]);

	Qpo->Tex_Delete(Medias->fire[83]);

	Qpo->Tex_Delete(Medias->fire[84]);

	Qpo->Tex_Delete(Medias->fire[85]);

	Qpo->Tex_Delete(Medias->fire[86]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->fire[87]);

	Qpo->Tex_Delete(Medias->fire[88]);

	Qpo->Tex_Delete(Medias->fire[89]);

	Qpo->Tex_Delete(Medias->fire[90]);

	Qpo->Tex_Delete(Medias->fire[91]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->fire[92]);

	Qpo->Tex_Delete(Medias->fire[93]);

	Qpo->Tex_Delete(Medias->fire[94]);

	Qpo->Tex_Delete(Medias->fire[95]);

	Qpo->Tex_Delete(Medias->fire[96]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////Flame Trails
	Qpo->Tex_Delete(Medias->flametrail[82]);

	Qpo->Tex_Delete(Medias->flametrail[83]);

	Qpo->Tex_Delete(Medias->flametrail[84]);

	Qpo->Tex_Delete(Medias->flametrail[85]);

	Qpo->Tex_Delete(Medias->flametrail[86]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->flametrail[87]);

	Qpo->Tex_Delete(Medias->flametrail[88]);

	Qpo->Tex_Delete(Medias->flametrail[89]);

	Qpo->Tex_Delete(Medias->flametrail[90]);

	Qpo->Tex_Delete(Medias->flametrail[91]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->flametrail[92]);

	Qpo->Tex_Delete(Medias->flametrail[93]);

	Qpo->Tex_Delete(Medias->flametrail[94]);

	Qpo->Tex_Delete(Medias->flametrail[95]);

	Qpo->Tex_Delete(Medias->flametrail[96]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

		////////////Pulsar
	Qpo->Tex_Delete(Medias->Pulsar[11]);

	Qpo->Tex_Delete(Medias->Pulsar[12]);

	Qpo->Tex_Delete(Medias->Pulsar[13]);

	Qpo->Tex_Delete(Medias->Pulsar[14]);

	Qpo->Tex_Delete(Medias->Pulsar[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[16]);

	Qpo->Tex_Delete(Medias->Pulsar[17]);

	Qpo->Tex_Delete(Medias->Pulsar[18]);

	Qpo->Tex_Delete(Medias->Pulsar[19]);

	Qpo->Tex_Delete(Medias->Pulsar[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[21]);

	Qpo->Tex_Delete(Medias->Pulsar[22]);

	Qpo->Tex_Delete(Medias->Pulsar[23]);

	Qpo->Tex_Delete(Medias->Pulsar[24]);

	Qpo->Tex_Delete(Medias->Pulsar[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[26]);

	Qpo->Tex_Delete(Medias->Pulsar[27]);

	Qpo->Tex_Delete(Medias->Pulsar[28]);

	Qpo->Tex_Delete(Medias->Pulsar[29]);

	Qpo->Tex_Delete(Medias->Pulsar[30]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[31]);

	Qpo->Tex_Delete(Medias->Pulsar[32]);

	Qpo->Tex_Delete(Medias->Pulsar[33]);

	Qpo->Tex_Delete(Medias->Pulsar[34]);

	Qpo->Tex_Delete(Medias->Pulsar[35]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[36]);

	Qpo->Tex_Delete(Medias->Pulsar[37]);

	Qpo->Tex_Delete(Medias->Pulsar[38]);

	Qpo->Tex_Delete(Medias->Pulsar[39]);

	Qpo->Tex_Delete(Medias->Pulsar[40]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Pulsar[41]);

	Qpo->Tex_Delete(Medias->Pulsar[42]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		////////////Pulsar Mid
	Qpo->Tex_Delete(Medias->PulsarMid[11]);

	Qpo->Tex_Delete(Medias->PulsarMid[12]);

	Qpo->Tex_Delete(Medias->PulsarMid[13]);

	Qpo->Tex_Delete(Medias->PulsarMid[14]);

	Qpo->Tex_Delete(Medias->PulsarMid[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[16]);

	Qpo->Tex_Delete(Medias->PulsarMid[17]);

	Qpo->Tex_Delete(Medias->PulsarMid[18]);

	Qpo->Tex_Delete(Medias->PulsarMid[19]);

	Qpo->Tex_Delete(Medias->PulsarMid[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[21]);

	Qpo->Tex_Delete(Medias->PulsarMid[22]);

	Qpo->Tex_Delete(Medias->PulsarMid[23]);

	Qpo->Tex_Delete(Medias->PulsarMid[24]);

	Qpo->Tex_Delete(Medias->PulsarMid[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[26]);

	Qpo->Tex_Delete(Medias->PulsarMid[27]);

	Qpo->Tex_Delete(Medias->PulsarMid[28]);

	Qpo->Tex_Delete(Medias->PulsarMid[29]);

	Qpo->Tex_Delete(Medias->PulsarMid[30]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[31]);

	Qpo->Tex_Delete(Medias->PulsarMid[32]);

	Qpo->Tex_Delete(Medias->PulsarMid[33]);

	Qpo->Tex_Delete(Medias->PulsarMid[34]);

	Qpo->Tex_Delete(Medias->PulsarMid[35]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[36]);

	Qpo->Tex_Delete(Medias->PulsarMid[37]);

	Qpo->Tex_Delete(Medias->PulsarMid[38]);

	Qpo->Tex_Delete(Medias->PulsarMid[39]);

	Qpo->Tex_Delete(Medias->PulsarMid[40]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->PulsarMid[41]);

	Qpo->Tex_Delete(Medias->PulsarMid[42]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//##### Rocket engine
	Qpo->Tex_Delete(Medias->Rocket[0]);

	Qpo->Tex_Delete(Medias->Rocket[1]);

	Qpo->Tex_Delete(Medias->Rocket[2]);

	Qpo->Tex_Delete(Medias->Rocket[3]);

	Qpo->Tex_Delete(Medias->Rocket[4]);

	Qpo->Tex_Delete(Medias->Rocket[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Rocket[6]);

	Qpo->Tex_Delete(Medias->Rocket[7]);

	Qpo->Tex_Delete(Medias->Rocket[8]);

	Qpo->Tex_Delete(Medias->Rocket[9]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//##### Rocket engine
	Qpo->Tex_Delete(Medias->Star[0]);

	Qpo->Tex_Delete(Medias->Star[1]);

	Qpo->Tex_Delete(Medias->Star[2]);

	Qpo->Tex_Delete(Medias->Star[3]);

	Qpo->Tex_Delete(Medias->Star[4]);

	Qpo->Tex_Delete(Medias->Star[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Star[6]);

	Qpo->Tex_Delete(Medias->Star[7]);

	Qpo->Tex_Delete(Medias->Star[8]);

	Qpo->Tex_Delete(Medias->Star[9]);

	Qpo->Tex_Delete(Medias->Star[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Star[11]);

	Qpo->Tex_Delete(Medias->Star[12]);

	Qpo->Tex_Delete(Medias->Star[13]);

	Qpo->Tex_Delete(Medias->Star[14]);

	Qpo->Tex_Delete(Medias->Star[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Star[16]);

	Qpo->Tex_Delete(Medias->Star[17]);

	Qpo->Tex_Delete(Medias->Star[18]);

	Qpo->Tex_Delete(Medias->Star[19]);

	Qpo->Tex_Delete(Medias->Star[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Star[21]);

	Qpo->Tex_Delete(Medias->Star[22]);

	Qpo->Tex_Delete(Medias->Star[23]);

	Qpo->Tex_Delete(Medias->Star[24]);

	Qpo->Tex_Delete(Medias->Star[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


	//#### Medias->Water
	Qpo->Tex_Delete(Medias->Water[124]);

	Qpo->Tex_Delete(Medias->Water[125]);

	Qpo->Tex_Delete(Medias->Water[126]);

	Qpo->Tex_Delete(Medias->Water[127]);

	Qpo->Tex_Delete(Medias->Water[128]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Water[129]);

	Qpo->Tex_Delete(Medias->Water[130]);

	Qpo->Tex_Delete(Medias->Water[131]);

	Qpo->Tex_Delete(Medias->Water[132]);

	Qpo->Tex_Delete(Medias->Water[133]);

	Qpo->Tex_Delete(Medias->Water[134]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->Water[135]);

	Qpo->Tex_Delete(Medias->Water[136]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//Mine build sign
	Qpo->Tex_Delete(Medias->mmine);

			//Build Menu
	Qpo->Tex_Delete(Medias->buildm);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	//##### CLOUD SMOKE
	Qpo->Tex_Delete(Medias->QSmoke[0]);

	Qpo->Tex_Delete(Medias->QSmoke[1]);

	Qpo->Tex_Delete(Medias->QSmoke[2]);

	Qpo->Tex_Delete(Medias->QSmoke[3]);

	Qpo->Tex_Delete(Medias->QSmoke[4]);

	Qpo->Tex_Delete(Medias->QSmoke[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[6]);

	Qpo->Tex_Delete(Medias->QSmoke[7]);

	Qpo->Tex_Delete(Medias->QSmoke[8]);

	Qpo->Tex_Delete(Medias->QSmoke[9]);

	Qpo->Tex_Delete(Medias->QSmoke[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[11]);

	Qpo->Tex_Delete(Medias->QSmoke[12]);

	Qpo->Tex_Delete(Medias->QSmoke[13]);

	Qpo->Tex_Delete(Medias->QSmoke[14]);

	Qpo->Tex_Delete(Medias->QSmoke[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[16]);

	Qpo->Tex_Delete(Medias->QSmoke[17]);

	Qpo->Tex_Delete(Medias->QSmoke[18]);

	Qpo->Tex_Delete(Medias->QSmoke[19]);

	Qpo->Tex_Delete(Medias->QSmoke[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[21]);

	Qpo->Tex_Delete(Medias->QSmoke[22]);

	Qpo->Tex_Delete(Medias->QSmoke[23]);

	Qpo->Tex_Delete(Medias->QSmoke[24]);

	Qpo->Tex_Delete(Medias->QSmoke[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[26]);

	Qpo->Tex_Delete(Medias->QSmoke[27]);

	Qpo->Tex_Delete(Medias->QSmoke[28]);

	Qpo->Tex_Delete(Medias->QSmoke[29]);

	Qpo->Tex_Delete(Medias->QSmoke[30]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[31]);

	Qpo->Tex_Delete(Medias->QSmoke[32]);

	Qpo->Tex_Delete(Medias->QSmoke[33]);

	Qpo->Tex_Delete(Medias->QSmoke[34]);

	Qpo->Tex_Delete(Medias->QSmoke[35]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[36]);

	Qpo->Tex_Delete(Medias->QSmoke[37]);

	Qpo->Tex_Delete(Medias->QSmoke[38]);

	Qpo->Tex_Delete(Medias->QSmoke[39]);

	Qpo->Tex_Delete(Medias->QSmoke[40]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[41]);

	Qpo->Tex_Delete(Medias->QSmoke[42]);

	Qpo->Tex_Delete(Medias->QSmoke[43]);

	Qpo->Tex_Delete(Medias->QSmoke[44]);

	Qpo->Tex_Delete(Medias->QSmoke[45]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->QSmoke[46]);

	Qpo->Tex_Delete(Medias->QSmoke[47]);

	Qpo->Tex_Delete(Medias->QSmoke[48]);

	Qpo->Tex_Delete(Medias->QSmoke[49]);


if(0)
	{
	//##### JINK ENERGY
	Qpo->Tex_Delete(Medias->JEnergy[0]);

	Qpo->Tex_Delete(Medias->JEnergy[1]);

	Qpo->Tex_Delete(Medias->JEnergy[2]);

	Qpo->Tex_Delete(Medias->JEnergy[3]);

	Qpo->Tex_Delete(Medias->JEnergy[4]);

	Qpo->Tex_Delete(Medias->JEnergy[5]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[6]);

	Qpo->Tex_Delete(Medias->JEnergy[7]);

	Qpo->Tex_Delete(Medias->JEnergy[8]);

	Qpo->Tex_Delete(Medias->JEnergy[9]);

	Qpo->Tex_Delete(Medias->JEnergy[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[11]);

	Qpo->Tex_Delete(Medias->JEnergy[12]);

	Qpo->Tex_Delete(Medias->JEnergy[13]);

	Qpo->Tex_Delete(Medias->JEnergy[14]);

	Qpo->Tex_Delete(Medias->JEnergy[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[16]);

	Qpo->Tex_Delete(Medias->JEnergy[17]);

	Qpo->Tex_Delete(Medias->JEnergy[18]);

	Qpo->Tex_Delete(Medias->JEnergy[19]);

	Qpo->Tex_Delete(Medias->JEnergy[20]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[21]);

	Qpo->Tex_Delete(Medias->JEnergy[22]);

	Qpo->Tex_Delete(Medias->JEnergy[23]);

	Qpo->Tex_Delete(Medias->JEnergy[24]);

	Qpo->Tex_Delete(Medias->JEnergy[25]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[26]);

	Qpo->Tex_Delete(Medias->JEnergy[27]);

	Qpo->Tex_Delete(Medias->JEnergy[28]);

	Qpo->Tex_Delete(Medias->JEnergy[29]);

	Qpo->Tex_Delete(Medias->JEnergy[30]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[31]);

	Qpo->Tex_Delete(Medias->JEnergy[32]);

	Qpo->Tex_Delete(Medias->JEnergy[33]);

	Qpo->Tex_Delete(Medias->JEnergy[34]);

	Qpo->Tex_Delete(Medias->JEnergy[35]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[36]);

	Qpo->Tex_Delete(Medias->JEnergy[37]);

	Qpo->Tex_Delete(Medias->JEnergy[38]);

	Qpo->Tex_Delete(Medias->JEnergy[39]);

	Qpo->Tex_Delete(Medias->JEnergy[40]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[41]);

	Qpo->Tex_Delete(Medias->JEnergy[42]);

	Qpo->Tex_Delete(Medias->JEnergy[43]);

	Qpo->Tex_Delete(Medias->JEnergy[44]);

	Qpo->Tex_Delete(Medias->JEnergy[45]);
	}

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif


		//COMPACT  JINK ENERGY BITMAP
	Qpo->Tex_Delete(Medias->JEnergy[0]);

	Qpo->Tex_Delete(Medias->JEnergy[1]);

	Qpo->Tex_Delete(Medias->JEnergy[2]);

	Qpo->Tex_Delete(Medias->JEnergy[3]);

	Qpo->Tex_Delete(Medias->JEnergy[4]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[5]);

	Qpo->Tex_Delete(Medias->JEnergy[6]);

	Qpo->Tex_Delete(Medias->JEnergy[7]);

	Qpo->Tex_Delete(Medias->JEnergy[8]);

	Qpo->Tex_Delete(Medias->JEnergy[9]);

	Qpo->Tex_Delete(Medias->JEnergy[10]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif

	Qpo->Tex_Delete(Medias->JEnergy[11]);

	Qpo->Tex_Delete(Medias->JEnergy[12]);

	Qpo->Tex_Delete(Medias->JEnergy[13]);

	Qpo->Tex_Delete(Medias->JEnergy[14]);

	Qpo->Tex_Delete(Medias->JEnergy[15]);

#ifndef QAGEMODE_NOINTRO
  //QActiveFrameWork->acNamePlateUpdate();
#endif
}

};

#pragma message ("###  Initialising Textures  [Q-InitBitmaps.h]")
