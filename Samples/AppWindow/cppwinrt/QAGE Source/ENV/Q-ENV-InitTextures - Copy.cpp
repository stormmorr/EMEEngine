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

#if 0
#include "SDL.h"
#include "SDL_thread.h"
#endif

#include "Texture/untexturebank.h"

#define UN_TEXTURE_TGA 0
#define UN_TEXTURE_PNG 1
#define UN_TEXTURE_ALP 2

winrt::Windows::Foundation::IAsyncAction mTexLoadingLoopWorker;

unTextureBank* g_TextureBank;

unsigned int global_Resource;
std::string g_StringPath;
unsigned int global_ResourceMutex;
unsigned int global_ResourceMutex2;
unsigned int global_ResourceMutex3;

using winrt::Windows::Foundation::Uri;
using winrt::Windows::Storage::FileAccessMode;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using winrt::Windows::Storage::StorageFile;

using namespace GVARS;

namespace GVARS
{

void acLoadfromStorageFile(int f_Int, winrt::Windows::Storage::StorageFile f_StorageFile, std::string f_FilePath)
{
	switch(f_Int)
		{
		case UN_TEXTURE_TGA:
			{
			global_ResourceMutex2 = 1;
			global_ResourceMutex3 = 1;

			winrt::hstring fileToken;

			fileToken = AccessCache::StorageApplicationPermissions::FutureAccessList().Add(f_StorageFile, f_StorageFile.Name());

			if(fileToken.size() != 0)
				{
				// Windows will call the server app to update the local version of the file
				Concurrency::create_task(AccessCache::StorageApplicationPermissions::FutureAccessList().GetFileAsync(fileToken)).then([](Concurrency::task<winrt::Windows::Storage::StorageFile> taskResult)
					{
					winrt::Windows::Storage::StorageFile f_LoadsFile = taskResult.get();

					//StorageFolder localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

					//winrt::hstring f_LocalPathString = localFolder.Path();

					g_StringPath = to_string(f_LoadsFile.Path());

					global_Resource = g_TextureBank->GLloadTGA(g_StringPath.c_str());

#if 0
					printf("Loaded %i Texture %s\n", global_Resource, g_StringPath.c_str());
#endif

					global_ResourceMutex2 = 2;
					});

				while(global_ResourceMutex2 < 2)
					{
					Sleep(0.25);
					}
				}
			}break;

		case UN_TEXTURE_PNG:
			{
			
			}break;

		case UN_TEXTURE_ALP:
			{
			
			}break;
		}
}

unsigned int Q_COREFunctions::acLoadTextureAlpha(std::string f_Path, std::string f_Filename, int f_Int)
{
	return 1;
}

unsigned int Q_COREFunctions::acLoadTexture(int f_Int, std::string f_File)
{
	std::string f_PathI = f_File.c_str();
	std::string f_PathO;

	f_PathO.clear();

	global_Resource = -5;
	global_ResourceMutex = 1;

	std::string f_PreString = "ms-appx:///";
	std::string f_FilePath = f_PreString + f_File;
	
	winrt::Windows::Storage::StorageFile inputFile{ (nullptr) };
	Uri f_Uri = Uri(StrUsingStr(f_FilePath));

	Concurrency::create_task(inputFile.GetFileFromApplicationUriAsync(f_Uri)).then([inputFile, f_Int, f_File](winrt::Windows::Storage::StorageFile f_StorageFile)
		{
		if(f_StorageFile != nullptr)
			{
			acLoadfromStorageFile(f_Int, f_StorageFile, f_File);
			global_ResourceMutex = 2;
			}
		});

#if 0
	global_ResourceMutex = 2;
#endif

	while(global_ResourceMutex < 2)
		{
		Sleep(0.25);
		}

	return global_Resource;
}

int acgs_ResourceLoad(void* f_Socketes)
{
	Medias->shadow = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadow.tga");

	Medias->shadowA2 = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\shadowa00G12.png");

	Medias->reticuleE = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\reticuleE.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->shineE = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shineE.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

#if 1
	Medias->QAEFF01 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF01.tga");

	Medias->QAEFF03 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF03.tga");

	Medias->QAEFF04 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF04.tga");

	Medias->QAEFF05 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.tga");

	Medias->QAEFF06 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF06.tga");

	Medias->QAEFF07 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.tga");

	Medias->QAEFF08 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.tga");

	Medias->QAEFF09 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF09.tga");

	Medias->QAEFF10 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF10.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QAEFF11 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF11.tga");

	Medias->QAEFF12 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF12.tga");

	Medias->QAEFF13 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.tga");

	Medias->QAEFF14 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF14.tga");

	Medias->QAEFF15 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF15.tga");

	Medias->QAEFF16 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF16.tga");

	Medias->QAEFF17 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF17.tga");

	Medias->QAEFF18 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF18.tga");

	Medias->QAEFF19 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF19.tga");

	Medias->QAEFF20 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF20.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QAEFF21 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF21.tga");

	Medias->QAEFF22 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF22.tga");

	Medias->QAEFF23 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF23.tga");

	Medias->QAEFF24 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF24.tga");

	Medias->QAEFF25 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF25.tga");

	Medias->QAEFF26 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF26.tga");

	Medias->QAEFF27 = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\QA_EFF\\J3L.png");

#if 0
	Medias->QAEFF28 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF28.tga");
#endif

	Medias->QAEFF28 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF51.tga");

	Medias->QAEFF29 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF29.tga");

	Medias->QAEFF30 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF30.tga");

#ifdef QAGE_SLOT
	Medias->Bonus = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Bonus.tga");

	Medias->Wild = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Wild.tga");
#endif

	Medias->QAEFF31 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF31.tga");

	Medias->QAEFF32 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF32.tga");
#endif

	//Reticule
	//^Medias->reticule = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\reticule.png");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//Screen Panel
	Medias->toppanel = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\toppanel.png");
	Medias->icon = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\icon1.png");

	Medias->hudbottom1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealthBars\\hudbottom1.tga");

#pragma message ("-  TODO Load Alpha Textures")

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->hudRadar = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HUDradar.png", "hudRadar", 0);

	Medias->hudbottom2 = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HUDbottom2.png", "Medias->hudbottom2", 255);
	Medias->hudbottom3 = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HUDbottom3.png", "Medias->hudbottom2", 255);

	Medias->Scope = Q.acLoadTextureAlpha("Assets\\Bitmaps\\ScopeA.png", "Scope", 1);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//Knock Out
	Medias->KObit[0] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\1.png", "Medias->KObit[0]", 0);
	Medias->KObit[1] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\2.png", "Medias->KObit[1]", 0);
	Medias->KObit[2] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\3.png", "Medias->KObit[2]", 0);
	Medias->KObit[3] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\4.png", "Medias->KObit[3]", 0);
	Medias->KObit[4] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\5.png", "Medias->KObit[4]", 0);
	Medias->KObit[5] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\6.png", "Medias->KObit[5]", 0);
	Medias->KObit[6] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\7.png", "Medias->KObit[6]", 0);
	Medias->KObit[7] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\8.png", "Medias->KObit[7]", 0);
	Medias->KObit[8] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\9.png", "Medias->KObit[8]", 0);
	Medias->KObit[9] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\10.png", "Medias->KObit[9]", 0);
	Medias->KObit[10] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\11.png", "Medias->KObit[10]", 0);
	Medias->KObit[11] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\KO\\12.png", "Medias->KObit[11]", 0);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->BulletCount = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletCount.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->HealthLeft = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HealthBarL.png", "Medias->HealthLeft", 0);
	Medias->HealthRight = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HealthBarR.png", "Medias->HealthRight", 0);
	Medias->HealthLeftEXT = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\HealthBarLEXT.png", "Medias->HealthLeftEXT", 0);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->EnergyBarLeft = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\EnergyBarL.png", "Medias->EnergyBarLeft", 0);
	Medias->EnergyBarRight = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\EnergyBarR.png", "Medias->EnergyBarRight", 0);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RADspritesF[0] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesF1.png", "Medias->RADspritesF[0]", 0);
	Medias->RADspritesF[1] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesF2.png", "Medias->RADspritesF[1]", 0);
	Medias->RADspritesF[2] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesF3.png", "Medias->RADspritesF[2]", 0);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RADspritesE[0] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesE1.png", "Medias->RADspritesE[0]", 0);
	Medias->RADspritesE[1] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesE2.png", "Medias->RADspritesE[1]", 0);
	Medias->RADspritesE[2] = Q.acLoadTextureAlpha("Assets\\Bitmaps\\HealthBars\\RADspritesE3.png", "Medias->RADspritesE[2]", 0);

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->VaporCAP = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\VaporCAP.tga");

	Medias->VaporLINE = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\VaporLINE.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Medias->DECAL SYSTEM
	Medias->DECAL[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[0].tga");

	Medias->DECAL[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[1].tga");

	Medias->DECAL[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[2].tga");

	Medias->DECAL[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[3].tga");

	Medias->DECAL[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[4].tga");

	Medias->DECAL[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[6].tga");

	Medias->DECAL[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[7].tga");

	Medias->DECAL[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[8].tga");

	Medias->DECAL[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[9].tga");

	Medias->DECAL[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[11].tga");

	Medias->DECAL[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[12].tga");

	Medias->DECAL[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[13].tga");

	Medias->DECAL[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[14].tga");

	Medias->DECAL[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[16].tga");

	Medias->DECAL[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[17].tga");

	Medias->DECAL[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[18].tga");

	Medias->DECAL[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[19].tga");

	Medias->DECAL[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[20].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[21].tga");

	Medias->DECAL[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[22].tga");

	Medias->DECAL[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[23].tga");

	Medias->DECAL[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[24].tga");

	Medias->DECAL[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[25].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->DECAL[26] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[26].tga");

	Medias->DECAL[27] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL[27].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//### FONT SYSTEM
	Medias->FONT[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[0].tga");

	Medias->FONT[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[1].tga");

	Medias->FONT[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[2].tga");

	Medias->FONT[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[3].tga");

	Medias->FONT[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[4].tga");

	Medias->FONT[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->FONT[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[6].tga");

	Medias->FONT[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[7].tga");

	Medias->FONT[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[8].tga");

	Medias->FONT[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT[9].tga");

	Medias->MESSAGES = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\MESSAGES.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//Bullets
	Medias->bullet = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\bullet.tga");

	Medias->pyro1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HitFlash\\pyro1.tga");

	Medias->pyro2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\pyro2.tga");

	Medias->cart1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\cartlb.tga");

	Medias->EXPexpandro1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\EXPexpandro1.tga");

	Medias->expandro1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowBLOCK.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->expandro2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\expandro2.tga");

	Medias->dot = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\WhiteS.png");

	Medias->lightning = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\lightning.tga");

	Medias->jinklightning = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\jinklightning.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->trail1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail1.tga");

	Medias->trail2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail2.tga");

	Medias->greeny = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny.tga");

	Medias->greeny2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny2.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->greenyN = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN.tga");

	Medias->greenyN2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN2.tga");

	Medias->spec = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\spec.tga");

	Medias->attsprite = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\attsprite.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Medias->SparkCorona[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[0].tga");

	Medias->SparkCorona[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[1].tga");

	Medias->SparkCorona[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[2].tga");

	Medias->SparkCorona[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona[3].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Spark Coronas
	Medias->EGrabCorona[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[0].tga");

	Medias->EGrabCorona[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[1].tga");

	Medias->EGrabCorona[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[2].tga");

	Medias->EGrabCorona[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona[3].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	Medias->BlackOut = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BlackOut.tga");

	Medias->MFlashX = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashX.tga");

	Medias->MFlashS1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS1.tga");

	Medias->MFlashS2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS2.tga");

	Medias->MFlashS3 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS3.tga");

	Medias->LaserSight = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\LaserSight.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->BulletTrail = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletTrail.tga");

	Medias->Text = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Text.tga");

	Medias->Spark = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spark.tga");

	Medias->Sparkmid = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparkmid.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Sparktail = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparktail.tga");

	Medias->HealSpark = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSpark.tga");

	Medias->HealSparkmid = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSparkmid.tga");

	Medias->HealSparktail = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSparktail.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RanSpark = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSpark.tga");

	Medias->EGrabSparktail = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\EGrabSparktail.tga");

	Medias->RanSpark = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\BlackS.png");

	Medias->RanSparkmid = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSparkmid.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->RanSparktail = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\RanSparktail.tga");

	Medias->HealSphere = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSphere.tga");

	Medias->BulHitFlash = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlash.tga");

	Medias->BulHitFlashSpin = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashSpin.tga");

	Medias->Face = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Face.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//-----Clouds-----//

	Medias->Cloud1 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud1.tga");

	Medias->Cloud2 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud2.tga");

	Medias->Cloud3 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud3.tga");

	Medias->Cloud9 = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud9.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->CloudBlood = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudBlood.tga");

	Medias->CloudLimb = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudLimb.tga");

	//---Scanner----//
	Medias->Scanner = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\Scanner\\Scanner.png");

	Medias->ScanBone = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBone.tga");

	Medias->ScanBox = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBox.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//---PEFMesh Textures
	Medias->FlameSingle = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\flamesingle.png");

	//### Better Spikes
	Medias->HHSpikeBmp = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HHSpikeBmp.tga");

	//### Hadouken Spike
	Medias->HADSpikeBmp = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HADSpikeBmp.tga");

	//### Spawn Spike
	Medias->SPAWNSpikeBmp = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\SPAWNSpikeBmp.tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//### Special4
	Medias->special4[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[0].tga");

	Medias->special4[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[1].tga");

	Medias->special4[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[2].tga");

	Medias->special4[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[3].tga");

	Medias->special4[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[4].tga");

	Medias->special4[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->special4[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[6].tga");

	Medias->special4[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[7].tga");

	Medias->special4[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[8].tga");

	Medias->special4[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[9].tga");

	Medias->special4[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[10].tga");

	Medias->special4[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\special4[11].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Flame		REQUIRED BY CLERIC
	Medias->flame[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[0].tga");

	Medias->flame[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[1].tga");

	Medias->flame[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[2].tga");

	Medias->flame[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[3].tga");

	Medias->flame[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[4].tga");

	Medias->flame[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flame[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[6].tga");

	Medias->flame[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[7].tga");

	Medias->flame[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[8].tga");

	Medias->flame[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[9].tga");

	Medias->flame[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flame[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[11].tga");

	Medias->flame[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[12].tga");

	Medias->flame[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[13].tga");

	Medias->flame[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[14].tga");

	Medias->flame[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////RAD fire
	Medias->radfire[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[0].tga");

	Medias->radfire[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[1].tga");

	Medias->radfire[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[2].tga");

	Medias->radfire[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[3].tga");

	Medias->radfire[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[4].tga");

	Medias->radfire[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->radfire[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[6].tga");

	Medias->radfire[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[7].tga");

	Medias->radfire[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[8].tga");

	Medias->radfire[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[9].tga");

	Medias->radfire[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->radfire[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[11].tga");

	Medias->radfire[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[12].tga");

	Medias->radfire[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[13].tga");

	Medias->radfire[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[14].tga");

	Medias->radfire[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\radfire[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Fire
	Medias->fire[82] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[82].tga");

	Medias->fire[83] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[83].tga");

	Medias->fire[84] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[84].tga");

	Medias->fire[85] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[85].tga");

	Medias->fire[86] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[86].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->fire[87] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[87].tga");

	Medias->fire[88] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[88].tga");

	Medias->fire[89] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[89].tga");

	Medias->fire[90] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[90].tga");

	Medias->fire[91] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[91].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->fire[92] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[92].tga");

	Medias->fire[93] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[93].tga");

	Medias->fire[94] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[94].tga");

	Medias->fire[95] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[95].tga");

	Medias->fire[96] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\fire[96].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Flame Trails
	Medias->flametrail[82] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[82].tga");

	Medias->flametrail[83] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[83].tga");

	Medias->flametrail[84] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[84].tga");

	Medias->flametrail[85] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[85].tga");

	Medias->flametrail[86] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[86].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flametrail[87] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[87].tga");

	Medias->flametrail[88] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[88].tga");

	Medias->flametrail[89] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[89].tga");

	Medias->flametrail[90] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[90].tga");

	Medias->flametrail[91] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[91].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->flametrail[92] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[92].tga");

	Medias->flametrail[93] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[93].tga");

	Medias->flametrail[94] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[94].tga");

	Medias->flametrail[95] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[95].tga");

	Medias->flametrail[96] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\flametrail[96].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	////////////Pulsar
	Medias->Pulsar[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[11].tga");

	Medias->Pulsar[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[12].tga");

	Medias->Pulsar[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[13].tga");

	Medias->Pulsar[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[14].tga");

	Medias->Pulsar[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[16].tga");

	Medias->Pulsar[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[17].tga");

	Medias->Pulsar[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[18].tga");

	Medias->Pulsar[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[19].tga");

	Medias->Pulsar[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[20].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[21].tga");

	Medias->Pulsar[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[22].tga");

	Medias->Pulsar[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[23].tga");

	Medias->Pulsar[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[24].tga");

	Medias->Pulsar[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[25].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[26] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[26].tga");

	Medias->Pulsar[27] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[27].tga");

	Medias->Pulsar[28] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[28].tga");

	Medias->Pulsar[29] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[29].tga");

	Medias->Pulsar[30] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[30].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[31] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[31].tga");

	Medias->Pulsar[32] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[32].tga");

	Medias->Pulsar[33] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[33].tga");

	Medias->Pulsar[34] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[34].tga");

	Medias->Pulsar[35] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[35].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[36] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[36].tga");

	Medias->Pulsar[37] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[37].tga");

	Medias->Pulsar[38] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[38].tga");

	Medias->Pulsar[39] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[39].tga");

	Medias->Pulsar[40] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[40].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Pulsar[41] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[41].tga");

	Medias->Pulsar[42] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Pulsar[42].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	////////////Pulsar Mid
	Medias->PulsarMid[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[11].tga");

	Medias->PulsarMid[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[12].tga");

	Medias->PulsarMid[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[13].tga");

	Medias->PulsarMid[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[14].tga");

	Medias->PulsarMid[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[16].tga");

	Medias->PulsarMid[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[17].tga");

	Medias->PulsarMid[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[18].tga");

	Medias->PulsarMid[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[19].tga");

	Medias->PulsarMid[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[20].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[21].tga");

	Medias->PulsarMid[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[22].tga");

	Medias->PulsarMid[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[23].tga");

	Medias->PulsarMid[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[24].tga");

	Medias->PulsarMid[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[25].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[26] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[26].tga");

	Medias->PulsarMid[27] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[27].tga");

	Medias->PulsarMid[28] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[28].tga");

	Medias->PulsarMid[29] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[29].tga");

	Medias->PulsarMid[30] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[30].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[31] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[31].tga");

	Medias->PulsarMid[32] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[32].tga");

	Medias->PulsarMid[33] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[33].tga");

	Medias->PulsarMid[34] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[34].tga");

	Medias->PulsarMid[35] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[35].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[36] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[36].tga");

	Medias->PulsarMid[37] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[37].tga");

	Medias->PulsarMid[38] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[38].tga");

	Medias->PulsarMid[39] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[39].tga");

	Medias->PulsarMid[40] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[40].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->PulsarMid[41] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[41].tga");

	Medias->PulsarMid[42] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\PulsarMid[42].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	//##### Rocket engine
	Medias->Rocket[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[0].tga");

	Medias->Rocket[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[1].tga");

	Medias->Rocket[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[2].tga");

	Medias->Rocket[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[3].tga");

	Medias->Rocket[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[4].tga");

	Medias->Rocket[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Rocket[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[6].tga");

	Medias->Rocket[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[7].tga");

	Medias->Rocket[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[8].tga");

	Medias->Rocket[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket[9].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	//##### Rocket engine
	Medias->Star[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[0].tga");

	Medias->Star[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[1].tga");

	Medias->Star[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[2].tga");

	Medias->Star[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[3].tga");

	Medias->Star[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[4].tga");

	Medias->Star[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[6].tga");

	Medias->Star[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[7].tga");

	Medias->Star[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[8].tga");

	Medias->Star[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[9].tga");

	Medias->Star[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[11].tga");

	Medias->Star[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[12].tga");

	Medias->Star[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[13].tga");

	Medias->Star[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[14].tga");

	Medias->Star[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[16].tga");

	Medias->Star[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[17].tga");

	Medias->Star[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[18].tga");

	Medias->Star[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[19].tga");

	Medias->Star[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[20].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Star[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[21].tga");

	Medias->Star[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[22].tga");

	Medias->Star[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[23].tga");

	Medias->Star[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[24].tga");

	Medias->Star[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star[25].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	//#### Medias->Water
	Medias->Water[124] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[124].tga");

	Medias->Water[125] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[125].tga");

	Medias->Water[126] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[126].tga");

	Medias->Water[127] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[127].tga");

	Medias->Water[128] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[128].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Water[129] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[129].tga");

	Medias->Water[130] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[130].tga");

	Medias->Water[131] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[131].tga");

	Medias->Water[132] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[132].tga");

	Medias->Water[133] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[133].tga");

	Medias->Water[134] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[134].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->Water[135] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[135].tga");

	Medias->Water[136] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water[136].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	//Mine build sign
	Medias->mmine = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\mmine.tga");

	//Build Menu
	Medias->buildm = Q.acLoadTexture(UN_TEXTURE_PNG, "Assets\\Bitmaps\\buildmenu.png");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	//##### CLOUD SMOKE
	Medias->QSmoke[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[0].tga");

	Medias->QSmoke[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[1].tga");

	Medias->QSmoke[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[2].tga");

	Medias->QSmoke[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[3].tga");

	Medias->QSmoke[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[4].tga");

	Medias->QSmoke[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[5].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[6].tga");

	Medias->QSmoke[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[7].tga");

	Medias->QSmoke[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[8].tga");

	Medias->QSmoke[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[9].tga");

	Medias->QSmoke[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[11].tga");

	Medias->QSmoke[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[12].tga");

	Medias->QSmoke[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[13].tga");

	Medias->QSmoke[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[14].tga");

	Medias->QSmoke[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[15].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[16].tga");

	Medias->QSmoke[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[17].tga");

	Medias->QSmoke[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[18].tga");

	Medias->QSmoke[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[19].tga");

	Medias->QSmoke[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[20].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[21].tga");

	Medias->QSmoke[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[22].tga");

	Medias->QSmoke[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[23].tga");

	Medias->QSmoke[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[24].tga");

	Medias->QSmoke[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[25].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[26] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[26].tga");

	Medias->QSmoke[27] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[27].tga");

	Medias->QSmoke[28] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[28].tga");

	Medias->QSmoke[29] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[29].tga");

	Medias->QSmoke[30] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[30].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[31] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[31].tga");

	Medias->QSmoke[32] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[32].tga");

	Medias->QSmoke[33] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[33].tga");

	Medias->QSmoke[34] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[34].tga");

	Medias->QSmoke[35] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[35].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[36] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[36].tga");

	Medias->QSmoke[37] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[37].tga");

	Medias->QSmoke[38] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[38].tga");

	Medias->QSmoke[39] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[39].tga");

	Medias->QSmoke[40] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[40].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[41] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[41].tga");

	Medias->QSmoke[42] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[42].tga");

	Medias->QSmoke[43] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[43].tga");

	Medias->QSmoke[44] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[44].tga");

	Medias->QSmoke[45] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[45].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->QSmoke[46] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[46].tga");

	Medias->QSmoke[47] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[47].tga");

	Medias->QSmoke[48] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[48].tga");

	Medias->QSmoke[49] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\QSmoke[49].tga");


	if (0)
	{
		//##### JINK ENERGY
		Medias->JEnergy[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

		Medias->JEnergy[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

		Medias->JEnergy[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

		Medias->JEnergy[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

		Medias->JEnergy[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

		Medias->JEnergy[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

		Medias->JEnergy[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

		Medias->JEnergy[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

		Medias->JEnergy[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

		Medias->JEnergy[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

		Medias->JEnergy[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

		Medias->JEnergy[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

		Medias->JEnergy[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

		Medias->JEnergy[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[16] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[16].tga");

		Medias->JEnergy[17] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[17].tga");

		Medias->JEnergy[18] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[18].tga");

		Medias->JEnergy[19] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[19].tga");

		Medias->JEnergy[20] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[20].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[21] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[21].tga");

		Medias->JEnergy[22] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[22].tga");

		Medias->JEnergy[23] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[23].tga");

		Medias->JEnergy[24] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[24].tga");

		Medias->JEnergy[25] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[25].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[26] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[26].tga");

		Medias->JEnergy[27] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[27].tga");

		Medias->JEnergy[28] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[28].tga");

		Medias->JEnergy[29] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[29].tga");

		Medias->JEnergy[30] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[30].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[31] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[31].tga");

		Medias->JEnergy[32] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[32].tga");

		Medias->JEnergy[33] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[33].tga");

		Medias->JEnergy[34] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[34].tga");

		Medias->JEnergy[35] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[35].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[36] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[36].tga");

		Medias->JEnergy[37] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[37].tga");

		Medias->JEnergy[38] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[38].tga");

		Medias->JEnergy[39] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[39].tga");

		Medias->JEnergy[40] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[40].tga");

#ifndef QAGEMODE_NOINTRO
		//QActiveFrameWork->acNamePlateUpdate();
#endif

		Medias->JEnergy[41] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[41].tga");

		Medias->JEnergy[42] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[42].tga");

		Medias->JEnergy[43] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[43].tga");

		Medias->JEnergy[44] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[44].tga");

		Medias->JEnergy[45] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[45].tga");
	}

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif


	//COMPACT  JINK ENERGY BITMAP
	Medias->JEnergy[0] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

	Medias->JEnergy[1] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

	Medias->JEnergy[2] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

	Medias->JEnergy[3] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

	Medias->JEnergy[4] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[5] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

	Medias->JEnergy[6] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

	Medias->JEnergy[7] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

	Medias->JEnergy[8] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

	Medias->JEnergy[9] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

	Medias->JEnergy[10] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

#ifndef QAGEMODE_NOINTRO
	//QActiveFrameWork->acNamePlateUpdate();
#endif

	Medias->JEnergy[11] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

	Medias->JEnergy[12] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

	Medias->JEnergy[13] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

	Medias->JEnergy[14] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

	Medias->JEnergy[15] = Q.acLoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");

	return 1;
}

//std::vector<SDL_Thread*> g_vec_SDLThread;

void Q_COREFunctions::InitTextures(void)
{
#if 0
	SDL_Thread* f_pSDLThread = SDL_CreateThread(acgs_ResourceLoad,"Resource Loading Thread", (void*)1);

	g_vec_SDLThread.push_back(f_pSDLThread);
#endif

	winrt::Windows::Storage::StorageFolder localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

	//printf("LocalFolder %s\n", to_string(localFolder.Path()).c_str());

#if 1
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
	//});
	
	// Run task on a dedicated high priority background thread.
	//mTexLoadingLoopWorker = Windows::System::Threading::ThreadPool::RunAsync(workItemHandler, Windows::System::Threading::WorkItemPriority::High, Windows::System::Threading::WorkItemOptions::TimeSliced);
#endif
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

void Q_COREFunctions::BlatTextures(void)
{
#if 0
		//Shadow
	shadow = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowmap.png");
	Medias->shadowA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowA.png");
	Qpo->Tex_AlphaLayerBlat(shadow, Medias->shadowA, "Assets\\Bitmaps\\shadow.tga");

	Medias->shadowA2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowa00G12.png");

	Medias->reticuleE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->reticuleEA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowA42.png");
	Qpo->Tex_AlphaLayerBlat(Medias->reticuleE, Medias->reticuleEA, "Assets\\Bitmaps\\reticuleE.tga");

	Medias->shineE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Hadouken3.png");
	Medias->shineEA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Hadouken2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->shineE, Medias->shineEA, "Assets\\Bitmaps\\shineE.tga");

	Medias->QAEFF01 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\001.png");
	Medias->QAEFF01A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF01, Medias->QAEFF01A, "Assets\\Bitmaps\\QA_EFF\\QAEFF01.tga");

	//Medias->QAEFF02 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF03.png");
	//Medias->QAEFF02A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF02.png");
	//Qpo->Tex_AlphaLayerBlat(Medias->QAEFF01, Medias->QAEFF01A, "Assets\\Bitmaps\\");

	Medias->QAEFF03 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\002.png");
	Medias->QAEFF03A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF03, Medias->QAEFF03A, "Assets\\Bitmaps\\QA_EFF\\QAEFF03.tga");

	Medias->QAEFF04 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white128.png");
	Medias->QAEFF04A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF04, Medias->QAEFF04A, "Assets\\Bitmaps\\QA_EFF\\QAEFF04.tga");

	Medias->QAEFF05 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white128.png");
	Medias->QAEFF05A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF05, Medias->QAEFF05A, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.tga");

	Medias->QAEFF06 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF06.png");
	Medias->QAEFF06A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF06, Medias->QAEFF06A, "Assets\\Bitmaps\\QA_EFF\\QAEFF06.tga");

	Medias->QAEFF07 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF09.png");
	Medias->QAEFF07A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF07, Medias->QAEFF07A, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.tga");

	Medias->QAEFF08 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF10.png");
	Medias->QAEFF08A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF08, Medias->QAEFF08A, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.tga");

	Medias->QAEFF09 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF16.png");
	Medias->QAEFF09A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF09, Medias->QAEFF09A, "Assets\\Bitmaps\\QA_EFF\\QAEFF09.tga");

	Medias->QAEFF10 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white.png");
	Medias->QAEFF10A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF07.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF10, Medias->QAEFF10A, "Assets\\Bitmaps\\QA_EFF\\QAEFF10.tga");

	Medias->QAEFF11 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white.png");
	Medias->QAEFF11A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF11, Medias->QAEFF11A, "Assets\\Bitmaps\\QA_EFF\\QAEFF11.tga");

	Medias->QAEFF12 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF14.png");
	Medias->QAEFF12A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF15.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF12, Medias->QAEFF12A, "Assets\\Bitmaps\\QA_EFF\\QAEFF12.tga");

	Medias->QAEFF13 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF17.png");
	Medias->QAEFF13A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF18.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF13, Medias->QAEFF13A, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.tga");

	Medias->QAEFF14 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QAEFF14A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF20.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF14, Medias->QAEFF14A, "Assets\\Bitmaps\\QA_EFF\\QAEFF14.tga");

	Medias->QAEFF15 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF21.png");
	Medias->QAEFF15A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF20.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF15, Medias->QAEFF15A, "Assets\\Bitmaps\\QA_EFF\\QAEFF15.tga");

	Medias->QAEFF16 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF23.png");
	Medias->QAEFF16A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF16, Medias->QAEFF16A, "Assets\\Bitmaps\\QA_EFF\\QAEFF16.tga");

	Medias->QAEFF17 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF25.png");
	Medias->QAEFF17A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF17, Medias->QAEFF17A, "Assets\\Bitmaps\\QA_EFF\\QAEFF17.tga");

	Medias->QAEFF18 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF26.png");
	Medias->QAEFF18A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF18.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF18, Medias->QAEFF18A, "Assets\\Bitmaps\\QA_EFF\\QAEFF18.tga");

	Medias->QAEFF19 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF27.png");
	Medias->QAEFF19A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF08.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF19, Medias->QAEFF19A, "Assets\\Bitmaps\\QA_EFF\\QAEFF19.tga");

	Medias->QAEFF20 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF28.png");
	Medias->QAEFF20A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF29.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF20, Medias->QAEFF20A, "Assets\\Bitmaps\\QA_EFF\\QAEFF20.tga");

	Medias->QAEFF21 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF17.png");
	Medias->QAEFF21A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF35.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF21, Medias->QAEFF21A, "Assets\\Bitmaps\\QA_EFF\\QAEFF21.tga");

	Medias->QAEFF22 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF30.png");
	Medias->QAEFF22A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF31.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF22, Medias->QAEFF22A, "Assets\\Bitmaps\\QA_EFF\\QAEFF22.tga");

	Medias->QAEFF23 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF34.png");
	Medias->QAEFF23A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF32.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF23, Medias->QAEFF23A, "Assets\\Bitmaps\\QA_EFF\\QAEFF23.tga");

	Medias->QAEFF24 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\Black.png");
	Medias->QAEFF24A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF24, Medias->QAEFF24A, "Assets\\Bitmaps\\QA_EFF\\QAEFF24.tga");

	Medias->QAEFF25 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\Black128.png");
	Medias->QAEFF25A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF25, Medias->QAEFF25A, "Assets\\Bitmaps\\QA_EFF\\QAEFF25.tga");

	Medias->QAEFF26 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF39.png");
	Medias->QAEFF26A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF40.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF26, Medias->QAEFF26A, "Assets\\Bitmaps\\QA_EFF\\QAEFF26.tga");

	Medias->QAEFF27 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\J3L.png");

	Medias->QAEFF28 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF41.png");
	Medias->QAEFF28A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF42.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF28, Medias->QAEFF28A, "Assets\\Bitmaps\\QA_EFF\\QAEFF28.tga");

	Medias->QAEFF29 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF43.png");
	Medias->QAEFF29A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF44.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF29, Medias->QAEFF29A, "Assets\\Bitmaps\\QA_EFF\\QAEFF29.tga");

	Medias->QAEFF30 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF45.png");
	Medias->QAEFF30A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF30, Medias->QAEFF30A, "Assets\\Bitmaps\\QA_EFF\\QAEFF30.tga");

	Medias->QAEFF31 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF46.png");
	Medias->QAEFF31A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF31, Medias->QAEFF31A, "Assets\\Bitmaps\\QA_EFF\\QAEFF31.tga");

	Medias->QAEFF32 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF49.png");
	Medias->QAEFF32A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\QA_EFF\\QAEFF48.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QAEFF32, Medias->QAEFF32A, "Assets\\Bitmaps\\QA_EFF\\QAEFF32.tga");

		//Reticule
	Medias->reticule = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\reticule.png");

		//Screen Panel
	Medias->toppanel = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\toppanel.png");
	icon = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\icon1.png");

	Medias->hudbottom1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealthBars\\HUDbottom1BU.png");
	Medias->hudbottom1A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealthBars\\HUDbottom1A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->hudbottom1, Medias->hudbottom1A, "Assets\\Bitmaps\\HealthBars\\hudbottom1.tga");

	hudRadar = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDradar.png", "hudRadar", 0);

	Medias->hudbottom2 = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDbottom2.png", "Medias->hudbottom2", 255);
	Medias->hudbottom3 = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HUDbottom3.png", "Medias->hudbottom2", 255);

	Scope = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\ScopeA.png", "Scope", 1);

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

	//Medias->BulletCount
	Medias->BulletCount = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletCNT.png");
	Medias->BulletCountA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletCNTA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->BulletCount, Medias->BulletCountA, "Assets\\Bitmaps\\BulletCount.tga");

	Medias->HealthLeft = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarL.png", "Medias->HealthLeft", 0);
	Medias->HealthRight = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarR.png", "Medias->HealthRight", 0);
	Medias->HealthLeftEXT = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\HealthBarLEXT.png", "Medias->HealthLeftEXT", 0);

	Medias->EnergyBarLeft = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\EnergyBarL.png", "Medias->EnergyBarLeft", 0);
	Medias->EnergyBarRight = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\EnergyBarR.png", "Medias->EnergyBarRight", 0);

	Medias->RADspritesF[0] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF1.png", "Medias->RADspritesF[0]", 0);
	Medias->RADspritesF[1] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF2.png", "Medias->RADspritesF[1]", 0);
	Medias->RADspritesF[2] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesF3.png", "Medias->RADspritesF[2]", 0);

	Medias->RADspritesE[0] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE1.png", "Medias->RADspritesE[0]", 0);
	Medias->RADspritesE[1] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE2.png", "Medias->RADspritesE[1]", 0);
	Medias->RADspritesE[2] = Qpo->Tex_LoadAlphaTexture("Assets\\Bitmaps\\HealthBars\\RADspritesE3.png", "Medias->RADspritesE[2]", 0);


	Medias->VaporCAP = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->VaporCAPA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\vaporcaN.png");
	Qpo->Tex_AlphaLayerBlat(Medias->VaporCAP, Medias->VaporCAPA, "Assets\\Bitmaps\\VaporTrails\\VaporCAP.tga");

	Medias->VaporLINE = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\whitebox16.png");
	Medias->VaporLINEA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\VaporTrails\\vaporra.png");
	Qpo->Tex_AlphaLayerBlat(Medias->VaporLINE, Medias->VaporLINEA, "Assets\\Bitmaps\\VaporTrails\\VaporLINE.tga");


	//### Medias->DECAL SYSTEM
	Medias->DECAL[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[0], Medias->DECALA[0], "Assets\\Bitmaps\\Decal\\DECAL[0].tga");

	Medias->DECAL[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL1A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[1], Medias->DECALA[1], "Assets\\Bitmaps\\Decal\\DECAL[1].tga");

	Medias->DECAL[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[2], Medias->DECALA[2], "Assets\\Bitmaps\\Decal\\DECAL[2].tga");

	Medias->DECAL[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL3A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[3], Medias->DECALA[3], "Assets\\Bitmaps\\Decal\\DECAL[3].tga");

	Medias->DECAL[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL4A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[4], Medias->DECALA[4], "Assets\\Bitmaps\\Decal\\DECAL[4].tga");

	Medias->DECAL[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL5A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[5], Medias->DECALA[5], "Assets\\Bitmaps\\Decal\\DECAL[5].tga");

	Medias->DECAL[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL6A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[6], Medias->DECALA[6], "Assets\\Bitmaps\\Decal\\DECAL[6].tga");

	Medias->DECAL[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL7A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[7], Medias->DECALA[7], "Assets\\Bitmaps\\Decal\\DECAL[7].tga");

	Medias->DECAL[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL8A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[8], Medias->DECALA[8], "Assets\\Bitmaps\\Decal\\DECAL[8].tga");

	Medias->DECAL[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL9A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[9], Medias->DECALA[9], "Assets\\Bitmaps\\Decal\\DECAL[9].tga");

	Medias->DECAL[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL10A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[10], Medias->DECALA[10], "Assets\\Bitmaps\\Decal\\DECAL[10].tga");

	Medias->DECAL[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL11A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[11], Medias->DECALA[11], "Assets\\Bitmaps\\Decal\\DECAL[11].tga");

	Medias->DECAL[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL12A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[12], Medias->DECALA[12], "Assets\\Bitmaps\\Decal\\DECAL[12].tga");

	Medias->DECAL[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL13A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[13], Medias->DECALA[13], "Assets\\Bitmaps\\Decal\\DECAL[13].tga");

	Medias->DECAL[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL14A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[14], Medias->DECALA[14], "Assets\\Bitmaps\\Decal\\DECAL[14].tga");

	Medias->DECAL[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL15A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[15], Medias->DECALA[15], "Assets\\Bitmaps\\Decal\\DECAL[15].tga");

	Medias->DECAL[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL16A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[16], Medias->DECALA[16], "Assets\\Bitmaps\\Decal\\DECAL[16].tga");

	Medias->DECAL[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL17A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[17], Medias->DECALA[17], "Assets\\Bitmaps\\Decal\\DECAL[17].tga");

	Medias->DECAL[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL18A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[18], Medias->DECALA[18], "Assets\\Bitmaps\\Decal\\DECAL[18].tga");

	Medias->DECAL[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL19A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[19], Medias->DECALA[19], "Assets\\Bitmaps\\Decal\\DECAL[19].tga");

	Medias->DECAL[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL20A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[20], Medias->DECALA[20], "Assets\\Bitmaps\\Decal\\DECAL[20].tga");

	Medias->DECAL[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL0.png");
	Medias->DECALA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL21A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[21], Medias->DECALA[21], "Assets\\Bitmaps\\Decal\\DECAL[21].tga");

	Medias->DECAL[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL1.png");
	Medias->DECALA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL22A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[22], Medias->DECALA[22], "Assets\\Bitmaps\\Decal\\DECAL[22].tga");

	Medias->DECAL[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL1.png");
	Medias->DECALA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL23A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[23], Medias->DECALA[23], "Assets\\Bitmaps\\Decal\\DECAL[23].tga");

	Medias->DECAL[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL1.png");
	Medias->DECALA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL24A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[24], Medias->DECALA[24], "Assets\\Bitmaps\\Decal\\DECAL[24].tga");

	Medias->DECAL[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL2.png");
	Medias->DECALA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL25A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[25], Medias->DECALA[25], "Assets\\Bitmaps\\Decal\\DECAL[25].tga");

	Medias->DECAL[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL3.png");
	Medias->DECALA[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL26A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[26], Medias->DECALA[26], "Assets\\Bitmaps\\Decal\\DECAL[26].tga");

	Medias->DECAL[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL3.png");
	Medias->DECALA[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Decal\\DECAL27A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->DECAL[27], Medias->DECALA[27], "Assets\\Bitmaps\\Decal\\DECAL[27].tga");


	//### FONT SYSTEM
	Medias->FONT[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[0], FONTA[0], "Assets\\Bitmaps\\Font\\FONT[0].tga");

	Medias->FONT[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT1A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[1], FONTA[1], "Assets\\Bitmaps\\Font\\FONT[1].tga");

	Medias->FONT[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[2], FONTA[2], "Assets\\Bitmaps\\Font\\FONT[2].tga");

	Medias->FONT[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT3A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[3], FONTA[3], "Assets\\Bitmaps\\Font\\FONT[3].tga");

	Medias->FONT[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT4A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[4], FONTA[4], "Assets\\Bitmaps\\Font\\FONT[4].tga");

	Medias->FONT[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT5A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[5], FONTA[5], "Assets\\Bitmaps\\Font\\FONT[5].tga");

	Medias->FONT[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT6A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[6], FONTA[6], "Assets\\Bitmaps\\Font\\FONT[6].tga");

	Medias->FONT[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT7A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[7], FONTA[7], "Assets\\Bitmaps\\Font\\FONT[7].tga");

	Medias->FONT[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT8A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[8], FONTA[8], "Assets\\Bitmaps\\Font\\FONT[8].tga");

	Medias->FONT[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT0.png");
	FONTA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\FONT9A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->FONT[9], FONTA[9], "Assets\\Bitmaps\\Font\\FONT[9].tga");

	//Player Messages
	Medias->MESSAGES = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\MESSAGES.png");
	Medias->MESSAGESA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Font\\MESSAGESA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->MESSAGES, Medias->MESSAGESA, "Assets\\Bitmaps\\Font\\MESSAGES.tga");

		//Bullets
	bullet = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\bullet1.png");
	Qpo->Tex_AlphaLayerBlat(bullet, Medias->shadowA, "Assets\\Bitmaps\\bullet.tga");

	Medias->pyro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HitFlash\\blood.png");
	Medias->pyro3 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HitFlash\\bloodA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->pyro1, Medias->pyro3, "Assets\\Bitmaps\\HitFlash\\pyro1.tga");

	Medias->pyro2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\bullet1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->pyro2, Medias->shadowA, "Assets\\Bitmaps\\pyro2.tga");

	Medias->EXPexpandro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowBLOCK.png");
	Qpo->Tex_AlphaLayerBlat(Medias->EXPexpandro1, Medias->shadowA2, "Assets\\Bitmaps\\EXPexpandro1.tga");

	Medias->expandro1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\FINAL.png");
	Medias->expandro1A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\FINALA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->expandro1, Medias->expandro1A, "Assets\\Bitmaps\\");

	Medias->expandro2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->shadowA3 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\shadowa00G2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->expandro2, Medias->shadowA3, "Assets\\Bitmaps\\expandro2.tga");

	dot = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(dot, Medias->shadowA, "Assets\\Bitmaps\\dot.tga");

	lightning = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\lightningN.png");
	Medias->lightningA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\lightningA.png");
	Qpo->Tex_AlphaLayerBlat(lightning, Medias->lightningA, "Assets\\Bitmaps\\lightning.tga");

	Medias->jinklightning = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\jinklightning.png");
	Qpo->Tex_AlphaLayerBlat(Medias->jinklightning, Medias->lightningA, "Assets\\Bitmaps\\jinklightning.tga");

	Medias->trail1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail14.png");
	Medias->trail1A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\trail1A4.png");
	Qpo->Tex_AlphaLayerBlat(Medias->trail1, Medias->trail1A, "Assets\\Bitmaps\\trail1.tga");

	Medias->greeny = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny.png");
	Medias->star2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->greeny, Medias->star2, "Assets\\Bitmaps\\greeny.tga");

	Medias->greeny2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greeny.png");
	Medias->star1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->greeny2, Medias->star1, "Assets\\Bitmaps\\greeny2.tga");

	Medias->greenyN = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN.png");
	Medias->star2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->greenyN, Medias->star2, "Assets\\Bitmaps\\greenyN.tga");

	Medias->greenyN2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\greenyN2.png");
	Medias->star1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->greenyN2, Medias->star1, "Assets\\Bitmaps\\greenyN2.tga");

	spec = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\got3.png");
	Medias->specA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\got3A.png");
	Qpo->Tex_AlphaLayerBlat(spec, Medias->specA, "Assets\\Bitmaps\\spec.tga");

	Medias->attsprite = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star4.png");
	Medias->attspriteA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\star3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->attsprite, Medias->attspriteA, "Assets\\Bitmaps\\attsprite.tga");


	//### Spark Coronas
	Medias->SparkCorona[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona.png");
	Medias->SparkCoronaA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona0.png");
	Qpo->Tex_AlphaLayerBlat(Medias->SparkCorona[0], Medias->SparkCoronaA[0], "Assets\\Bitmaps\\SparkBmp\\SparkCorona[0].tga");

	Medias->SparkCorona[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona.png");
	Medias->SparkCoronaA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->SparkCorona[1], Medias->SparkCoronaA[1], "Assets\\Bitmaps\\SparkBmp\\SparkCorona[1].tga");

	Medias->SparkCorona[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona.png");
	Medias->SparkCoronaA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->SparkCorona[2], Medias->SparkCoronaA[2], "Assets\\Bitmaps\\SparkBmp\\SparkCorona[2].tga");

	Medias->SparkCorona[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona.png");
	Medias->SparkCoronaA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->SparkCorona[3], Medias->SparkCoronaA[3], "Assets\\Bitmaps\\SparkBmp\\SparkCorona[3].tga");


	//### Spark Coronas
	Medias->EGrabCorona[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona.png");
	Medias->EGrabCoronaA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona0.png");
	Qpo->Tex_AlphaLayerBlat(Medias->EGrabCorona[0], Medias->EGrabCoronaA[0], "Assets\\Bitmaps\\EGrabCorona[0].tga");

	Medias->EGrabCorona[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona.png");
	Medias->EGrabCoronaA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->EGrabCorona[1], Medias->EGrabCoronaA[1], "Assets\\Bitmaps\\EGrabCorona[1].tga");

	Medias->EGrabCorona[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona.png");
	Medias->EGrabCoronaA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->EGrabCorona[2], Medias->EGrabCoronaA[2], "Assets\\Bitmaps\\EGrabCorona[2].tga");

	Medias->EGrabCorona[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\EGrabCorona.png");
	Medias->EGrabCoronaA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkBmp\\SparkCorona3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->EGrabCorona[3], Medias->EGrabCoronaA[3], "Assets\\Bitmaps\\EGrabCorona[3].tga");


	Medias->BlackOut = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Black.png");
	Medias->BlackOutA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JinkMedias->BlackOut3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->BlackOut, Medias->BlackOutA, "Assets\\Bitmaps\\BlackOut.tga");

	Medias->MFlashX = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlash1.png");
	Medias->MFlashXA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlash1A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->MFlashX, Medias->MFlashXA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashX.tga");

	Medias->MFlashS = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlash2.png");
	Medias->MFlashSA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\MFlash2B.png");
	Qpo->Tex_AlphaLayerBlat(Medias->MFlashS, Medias->MFlashSA, "Assets\\Bitmaps\\MuzzleFlash\\MFlashS.tga");

	Medias->LaserSight = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white128.png");
	Medias->LaserSightA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\lasersightA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->LaserSight, Medias->LaserSightA, "Assets\\Bitmaps\\LaserSight.tga");

	Medias->BulletTrail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\white128.png");
	Medias->BulletTrailA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BulletTrailA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->BulletTrail, Medias->BulletTrailA, "Assets\\Bitmaps\\BulletTrail.tga");

	Text = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Text.png");
	TextA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Text.png");
	Qpo->Tex_AlphaLayerBlat(Text, TextA, "Assets\\Bitmaps\\Text.tga");

	Spark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spark.png");
	Medias->SparkA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkA.png");
	Qpo->Tex_AlphaLayerBlat(Spark, Medias->SparkA, "Assets\\Bitmaps\\Spark.tga");

	Medias->Sparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparkmid.png");
	Medias->SparkmidA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\SparkmidA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Sparkmid, Medias->SparkmidA, "Assets\\Bitmaps\\Sparkmid.tga");

	Medias->Sparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Sparktail.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Sparktail, Medias->SparkmidA, "Assets\\Bitmaps\\Sparktail.tga");

	HealSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Medias->HealSparkA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\EnergySpark.png");
	Qpo->Tex_AlphaLayerBlat(HealSpark, Medias->HealSparkA, "Assets\\Bitmaps\\HealSpark.tga");

	Medias->HealSparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->HealSparkmid, Medias->HealSparkA, "Assets\\Bitmaps\\HealSparkmid.tga");

	Medias->HealSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->HealSparktail, Medias->HealSparkA, "Assets\\Bitmaps\\HealSparktail.tga");

	Medias->RanSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->RanSpark, Medias->SparkA, "Assets\\Bitmaps\\RanSpark.tga");

	Medias->EGrabSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BlackS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->HealSparktail, Medias->HealSparkA, "Assets\\Bitmaps\\EGrabSparktail.tga");

	Medias->RanSpark = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\BlackS.png");

	Medias->RanSparkmid = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->RanSparkmid, Medias->SparkmidA, "Assets\\Bitmaps\\RanSparkmid.tga");

	Medias->RanSparktail = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\WhiteS.png");
	Qpo->Tex_AlphaLayerBlat(Medias->RanSparktail, Medias->SparkmidA, "Assets\\Bitmaps\\RanSparktail.tga");

	Medias->HealSphere = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->HealSphereA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\HealSphereA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->HealSphere, Medias->HealSphereA, "Assets\\Bitmaps\\HealSphere.tga");

	Medias->BulHitFlash = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlash2.png");
	Medias->BulHitFlashA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->BulHitFlash, Medias->BulHitFlashA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlash.tga");

	Medias->BulHitFlashSpin = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashSpin2.png");
	Medias->BulHitFlashSpinA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashSpinA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->BulHitFlashSpin, Medias->BulHitFlashSpinA, "Assets\\Bitmaps\\MuzzleFlash\\BulHitFlashSpin.tga");

	//Scope = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\ScopeA.png");
	//ScopeA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\ScopeA.png");
	//Qpo->Tex_AlphaLayerBlat(Scope, ScopeA, "Assets\\Bitmaps\\");

	//Facial
	Face = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Facial.png");
	FaceA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\FacialA.png");
	Qpo->Tex_AlphaLayerBlat(Face, FaceA, "Assets\\Bitmaps\\Face.tga");

	//-----Clouds-----//

	Medias->Cloud1 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud1.png");
	Medias->Cloud1A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Cloud1, Medias->Cloud1A, "Assets\\Bitmaps\\Clouds\\Cloud1.tga");

	Medias->Cloud2 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->Cloud2A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Cloud2, Medias->Cloud2A, "Assets\\Bitmaps\\Clouds\\Cloud2.tga");

	Medias->Cloud3 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud6.png");
	Medias->Cloud3A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud3A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Cloud3, Medias->Cloud3A, "Assets\\Bitmaps\\Clouds\\Cloud3.tga");

	Medias->Cloud9 = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud9.png");
	Medias->Cloud9A = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\Cloud2A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Cloud9, Medias->Cloud9A, "Assets\\Bitmaps\\Clouds\\Cloud9.tga");

	Medias->CloudBlood = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudBlood.png");
	Medias->CloudBloodA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\CloudBloodA3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->CloudBlood, Medias->CloudBloodA, "Assets\\Bitmaps\\Clouds\\CloudBlood.tga");

	Medias->CloudLimb = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\name2.png");
	Medias->CloudLimbA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Clouds\\nameA3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->CloudLimb, Medias->CloudLimbA, "Assets\\Bitmaps\\Clouds\\CloudLimb.tga");


	//---Scanner----//
	Scanner = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\Scanner.png");

	Medias->ScanBone = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBone.png");
	Medias->ScanBoneA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\ScanBoneA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->ScanBone, Medias->ScanBoneA, "Assets\\Bitmaps\\Scanner\\ScanBone.tga");

	Medias->ScanBox = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\InfoBox.png");
	Medias->ScanBoxA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Scanner\\InfoBoxA.png");
	Qpo->Tex_AlphaLayerBlat(Medias->ScanBox, Medias->ScanBoxA, "Assets\\Bitmaps\\Scanner\\ScanBox.tga");


	//---PEFMesh Textures
	Medias->FlameSingle = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flamesingle.png");

	//### Better Spikes
	Medias->Q_HHSpike->HHSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\Q_HHSpike->HHSpikebmp4.png");
	Medias->Q_HHSpike->HHSpikeBmpA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\Q_HHSpike->HHSpikebmp5A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Q_HHSpike->HHSpikeBmp, Medias->Q_HHSpike->HHSpikeBmpA, "Assets\\Bitmaps\\Spikes\\Q_HHSpike->HHSpikeBmp.tga");

	//### Hadouken Spike
	Medias->HADSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HADSpikebmp18.png");
	Medias->HADSpikeBmpA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\HADSpikebmp19A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->HADSpikeBmp, Medias->HADSpikeBmpA, "Assets\\Bitmaps\\Spikes\\HADSpikeBmp.tga");

	//### Spawn Spike
	Medias->SPAWNSpikeBmp = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\Q_HHSpike->HHSpikebmp8.png");
	Medias->SPAWNSpikeBmpA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Spikes\\Q_HHSpike->HHSpikebmp5A.png");
	Qpo->Tex_AlphaLayerBlat(Medias->SPAWNSpikeBmp, Medias->SPAWNSpikeBmpA, "Assets\\Bitmaps\\Spikes\\SPAWNSpikeBmp.tga");

if(1)
	{
	Medias->special4[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00000.png");
	Medias->specialA4[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00000.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[0], Medias->specialA4[0], "Assets\\Bitmaps\\Special4\\special4[0].tga");

	Medias->special4[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00001.png");
	Medias->specialA4[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00001.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[1], Medias->specialA4[1], "Assets\\Bitmaps\\Special4\\special4[1].tga");

	Medias->special4[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00002.png");
	Medias->specialA4[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00002.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[2], Medias->specialA4[2], "Assets\\Bitmaps\\Special4\\special4[2].tga");

	Medias->special4[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00003.png");
	Medias->specialA4[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00003.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[3], Medias->specialA4[3], "Assets\\Bitmaps\\Special4\\special4[3].tga");

	Medias->special4[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00004.png");
	Medias->specialA4[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00004.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[4], Medias->specialA4[4], "Assets\\Bitmaps\\Special4\\special4[4].tga");

	Medias->special4[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00005.png");
	Medias->specialA4[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00005.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[5], Medias->specialA4[5], "Assets\\Bitmaps\\Special4\\special4[5].tga");

	Medias->special4[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00006.png");
	Medias->specialA4[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00006.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[6], Medias->specialA4[6], "Assets\\Bitmaps\\Special4\\special4[6].tga");

	Medias->special4[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00007.png");
	Medias->specialA4[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00007.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[7], Medias->specialA4[7], "Assets\\Bitmaps\\Special4\\special4[7].tga");

	Medias->special4[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00008.png");
	Medias->specialA4[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00008.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[8], Medias->specialA4[8], "Assets\\Bitmaps\\Special4\\special4[8].tga");

	Medias->special4[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00009.png");
	Medias->specialA4[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00009.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[9], Medias->specialA4[9], "Assets\\Bitmaps\\Special4\\special4[9].tga");

	Medias->special4[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00010.png");
	Medias->specialA4[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00010.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[10], Medias->specialA4[10], "Assets\\Bitmaps\\Special4\\special4[10].tga");

	Medias->special4[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\Spec00011.png");
	Medias->specialA4[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Special4\\SpecA00011.png");
	Qpo->Tex_AlphaLayerBlat(Medias->special4[11], Medias->specialA4[11], "Assets\\Bitmaps\\Special4\\special4[11].tga");
	}

	////////////Flame		REQUIRED BY CLERIC
if(1)
	{
	Medias->flame[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00000.png");
	Medias->flameA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00000.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[0], Medias->flameA[0], "Assets\\Bitmaps\\flame\\flame[0].tga");

	Medias->flame[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00001.png");
	Medias->flameA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00001.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[1], Medias->flameA[1], "Assets\\Bitmaps\\flame\\flame[1].tga");

	Medias->flame[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00002.png");
	Medias->flameA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00002.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[2], Medias->flameA[2], "Assets\\Bitmaps\\flame\\flame[2].tga");

	Medias->flame[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00003.png");
	Medias->flameA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00003.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[3], Medias->flameA[3], "Assets\\Bitmaps\\flame\\flame[3].tga");

	Medias->flame[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00004.png");
	Medias->flameA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00004.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[4], Medias->flameA[4], "Assets\\Bitmaps\\flame\\flame[4].tga");

	Medias->flame[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00005.png");
	Medias->flameA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00005.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[5], Medias->flameA[5], "Assets\\Bitmaps\\flame\\flame[5].tga");

	Medias->flame[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00006.png");
	Medias->flameA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00006.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[6], Medias->flameA[6], "Assets\\Bitmaps\\flame\\flame[6].tga");

	Medias->flame[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00007.png");
	Medias->flameA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00007.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[7], Medias->flameA[7], "Assets\\Bitmaps\\flame\\flame[7].tga");

	Medias->flame[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00008.png");
	Medias->flameA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00008.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[8], Medias->flameA[8], "Assets\\Bitmaps\\flame\\flame[8].tga");

	Medias->flame[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00009.png");
	Medias->flameA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00009.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[9], Medias->flameA[9], "Assets\\Bitmaps\\flame\\flame[9].tga");

	Medias->flame[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00010.png");
	Medias->flameA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00010.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[10], Medias->flameA[10], "Assets\\Bitmaps\\flame\\flame[10].tga");

	Medias->flame[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00011.png");
	Medias->flameA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00011.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[11], Medias->flameA[11], "Assets\\Bitmaps\\flame\\flame[11].tga");

	Medias->flame[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00012.png");
	Medias->flameA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00012.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[12], Medias->flameA[12], "Assets\\Bitmaps\\flame\\flame[12].tga");

	Medias->flame[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00013.png");
	Medias->flameA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00013.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[13], Medias->flameA[13], "Assets\\Bitmaps\\flame\\flame[13].tga");

	Medias->flame[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00014.png");
	Medias->flameA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00014.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[14], Medias->flameA[14], "Assets\\Bitmaps\\flame\\flame[14].tga");

	Medias->flame[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flame00015.png");
	Medias->flameA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\flame\\flameA00015.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flame[15], Medias->flameA[15], "Assets\\Bitmaps\\flame\\flame[15].tga");
	}


	////////////RAD fire
if(1)
	{
	Medias->radfire[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00000.png");
	radfire.fireA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00000.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[0], radfire.fireA[0], "Assets\\Bitmaps\\radfire\\radfire[0].tga");

	Medias->radfire[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00001.png");
	radfire.fireA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00001.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[1], radfire.fireA[1], "Assets\\Bitmaps\\radfire\\radfire[1].tga");

	Medias->radfire[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00002.png");
	radfire.fireA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00002.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[2], radfire.fireA[2], "Assets\\Bitmaps\\radfire\\radfire[2].tga");

	Medias->radfire[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00003.png");
	radfire.fireA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00003.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[3], radfire.fireA[3], "Assets\\Bitmaps\\radfire\\radfire[3].tga");

	Medias->radfire[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00004.png");
	radfire.fireA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00004.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[4], radfire.fireA[4], "Assets\\Bitmaps\\radfire\\radfire[4].tga");

	Medias->radfire[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00005.png");
	radfire.fireA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00005.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[5], radfire.fireA[5], "Assets\\Bitmaps\\radfire\\radfire[5].tga");

	Medias->radfire[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00006.png");
	radfire.fireA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00006.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[6], radfire.fireA[6], "Assets\\Bitmaps\\radfire\\radfire[6].tga");

	Medias->radfire[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00007.png");
	radfire.fireA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00007.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[7], radfire.fireA[7], "Assets\\Bitmaps\\radfire\\radfire[7].tga");

	Medias->radfire[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00008.png");
	radfire.fireA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00008.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[8], radfire.fireA[8], "Assets\\Bitmaps\\radfire\\radfire[8].tga");

	Medias->radfire[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00009.png");
	radfire.fireA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00009.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[9], radfire.fireA[9], "Assets\\Bitmaps\\radfire\\radfire[9].tga");

	Medias->radfire[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00010.png");
	radfire.fireA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00010.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[10], radfire.fireA[10], "Assets\\Bitmaps\\radfire\\radfire[10].tga");

	Medias->radfire[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00011.png");
	radfire.fireA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00011.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[11], radfire.fireA[11], "Assets\\Bitmaps\\radfire\\radfire[11].tga");

	Medias->radfire[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00012.png");
	radfire.fireA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00012.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[12], radfire.fireA[12], "Assets\\Bitmaps\\radfire\\radfire[12].tga");

	Medias->radfire[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00013.png");
	radfire.fireA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00013.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[13], radfire.fireA[13], "Assets\\Bitmaps\\radfire\\radfire[13].tga");

	Medias->radfire[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00014.png");
	radfire.fireA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00014.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[14], radfire.fireA[14], "Assets\\Bitmaps\\radfire\\radfire[14].tga");

	Medias->radfire[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\Spec00015.png");
	radfire.fireA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\radfire\\SpecA00015.png");
	Qpo->Tex_AlphaLayerBlat(Medias->radfire[15], radfire.fireA[15], "Assets\\Bitmaps\\radfire\\radfire[15].tga");
	}


////////////Fire
if(1)
	{
	Medias->fire[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00082.png");
	Medias->fireA[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00082.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[82], Medias->fireA[82], "Assets\\Bitmaps\\fire\\fire[82].tga");

	Medias->fire[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00083.png");
	Medias->fireA[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00083.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[83], Medias->fireA[83], "Assets\\Bitmaps\\fire\\fire[83].tga");

	Medias->fire[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00084.png");
	Medias->fireA[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00084.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[84], Medias->fireA[84], "Assets\\Bitmaps\\fire\\fire[84].tga");

	Medias->fire[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00085.png");
	Medias->fireA[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00085.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[85], Medias->fireA[85], "Assets\\Bitmaps\\fire\\fire[85].tga");

	Medias->fire[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00086.png");
	Medias->fireA[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00086.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[86], Medias->fireA[86], "Assets\\Bitmaps\\fire\\fire[86].tga");

	Medias->fire[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00087.png");
	Medias->fireA[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00087.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[87], Medias->fireA[87], "Assets\\Bitmaps\\fire\\fire[87].tga");

	Medias->fire[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00088.png");
	Medias->fireA[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00088.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[88], Medias->fireA[88], "Assets\\Bitmaps\\fire\\fire[88].tga");

	Medias->fire[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00089.png");
	Medias->fireA[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00089.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[89], Medias->fireA[89], "Assets\\Bitmaps\\fire\\fire[89].tga");

	Medias->fire[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00090.png");
	Medias->fireA[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00090.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[90], Medias->fireA[90], "Assets\\Bitmaps\\fire\\fire[90].tga");

	Medias->fire[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00091.png");
	Medias->fireA[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00091.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[91], Medias->fireA[91], "Assets\\Bitmaps\\fire\\fire[91].tga");

	Medias->fire[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00092.png");
	Medias->fireA[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00092.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[92], Medias->fireA[92], "Assets\\Bitmaps\\fire\\fire[92].tga");

	Medias->fire[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00093.png");
	Medias->fireA[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00093.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[93], Medias->fireA[93], "Assets\\Bitmaps\\fire\\fire[93].tga");

	Medias->fire[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00094.png");
	Medias->fireA[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00094.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[94], Medias->fireA[94], "Assets\\Bitmaps\\fire\\fire[94].tga");

	Medias->fire[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00095.png");
	Medias->fireA[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00095.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[95], Medias->fireA[95], "Assets\\Bitmaps\\fire\\fire[95].tga");

	Medias->fire[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\Fire00096.png");
	Medias->fireA[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\fire\\FireA00096.png");
	Qpo->Tex_AlphaLayerBlat(Medias->fire[96], Medias->fireA[96], "Assets\\Bitmaps\\fire\\fire[96].tga");
	}


	////////////Flame Trails
if(1)
	{
	Medias->flametrail[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00082.png");
	Medias->flametrailA[82] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00082.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[82], Medias->flametrailA[82], "Assets\\Bitmaps\\Trails\\fire\\flametrail[82].tga");

	Medias->flametrail[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00083.png");
	Medias->flametrailA[83] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00083.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[83], Medias->flametrailA[83], "Assets\\Bitmaps\\Trails\\fire\\flametrail[83].tga");

	Medias->flametrail[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00084.png");
	Medias->flametrailA[84] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00084.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[84], Medias->flametrailA[84], "Assets\\Bitmaps\\Trails\\fire\\flametrail[84].tga");

	Medias->flametrail[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00085.png");
	Medias->flametrailA[85] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00085.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[85], Medias->flametrailA[85], "Assets\\Bitmaps\\Trails\\fire\\flametrail[85].tga");

	Medias->flametrail[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00086.png");
	Medias->flametrailA[86] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00086.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[86], Medias->flametrailA[86], "Assets\\Bitmaps\\Trails\\fire\\flametrail[86].tga");

	Medias->flametrail[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00087.png");
	Medias->flametrailA[87] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00087.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[87], Medias->flametrailA[87], "Assets\\Bitmaps\\Trails\\fire\\flametrail[87].tga");

	Medias->flametrail[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00088.png");
	Medias->flametrailA[88] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00088.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[88], Medias->flametrailA[88], "Assets\\Bitmaps\\Trails\\fire\\flametrail[88].tga");

	Medias->flametrail[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00089.png");
	Medias->flametrailA[89] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00089.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[89], Medias->flametrailA[89], "Assets\\Bitmaps\\Trails\\fire\\flametrail[89].tga");

	Medias->flametrail[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00090.png");
	Medias->flametrailA[90] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00090.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[90], Medias->flametrailA[90], "Assets\\Bitmaps\\Trails\\fire\\flametrail[90].tga");

	Medias->flametrail[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00091.png");
	Medias->flametrailA[91] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00091.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[91], Medias->flametrailA[91], "Assets\\Bitmaps\\Trails\\fire\\flametrail[91].tga");

	Medias->flametrail[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00092.png");
	Medias->flametrailA[92] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00092.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[92], Medias->flametrailA[92], "Assets\\Bitmaps\\Trails\\fire\\flametrail[92].tga");

	Medias->flametrail[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00093.png");
	Medias->flametrailA[93] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00093.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[93], Medias->flametrailA[93], "Assets\\Bitmaps\\Trails\\fire\\flametrail[93].tga");

	Medias->flametrail[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00094.png");
	Medias->flametrailA[94] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00094.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[94], Medias->flametrailA[94], "Assets\\Bitmaps\\Trails\\fire\\flametrail[94].tga");

	Medias->flametrail[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00095.png");
	Medias->flametrailA[95] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00095.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[95], Medias->flametrailA[95], "Assets\\Bitmaps\\Trails\\fire\\flametrail[95].tga");

	Medias->flametrail[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\Fire00096.png");
	Medias->flametrailA[96] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Trails\\fire\\FireA00096.png");
	Qpo->Tex_AlphaLayerBlat(Medias->flametrail[96], Medias->flametrailA[96], "Assets\\Bitmaps\\Trails\\fire\\flametrail[96].tga");
	}


if(1)
	{
	Medias->Pulsar[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00011.png");
	Medias->PulsarA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00011.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[11], Medias->PulsarA[11], "Assets\\Bitmaps\\Pulsar\\Pulsar[11].tga");

	Medias->Pulsar[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00012.png");
	Medias->PulsarA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00012.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[12], Medias->PulsarA[12], "Assets\\Bitmaps\\Pulsar\\Pulsar[12].tga");

	Medias->Pulsar[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00013.png");
	Medias->PulsarA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00013.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[13], Medias->PulsarA[13], "Assets\\Bitmaps\\Pulsar\\Pulsar[13].tga");

	Medias->Pulsar[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00014.png");
	Medias->PulsarA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00014.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[14], Medias->PulsarA[14], "Assets\\Bitmaps\\Pulsar\\Pulsar[14].tga");

	Medias->Pulsar[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00015.png");
	Medias->PulsarA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00015.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[15], Medias->PulsarA[15], "Assets\\Bitmaps\\Pulsar\\Pulsar[15].tga");

	Medias->Pulsar[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00016.png");
	Medias->PulsarA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00016.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[16], Medias->PulsarA[16], "Assets\\Bitmaps\\Pulsar\\Pulsar[16].tga");

	Medias->Pulsar[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00017.png");
	Medias->PulsarA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00017.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[17], Medias->PulsarA[17], "Assets\\Bitmaps\\Pulsar\\Pulsar[17].tga");

	Medias->Pulsar[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00018.png");
	Medias->PulsarA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00018.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[18], Medias->PulsarA[18], "Assets\\Bitmaps\\Pulsar\\Pulsar[18].tga");

	Medias->Pulsar[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00019.png");
	Medias->PulsarA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00019.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[19], Medias->PulsarA[19], "Assets\\Bitmaps\\Pulsar\\Pulsar[19].tga");

	Medias->Pulsar[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00020.png");
	Medias->PulsarA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00020.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[20], Medias->PulsarA[20], "Assets\\Bitmaps\\Pulsar\\Pulsar[20].tga");

	Medias->Pulsar[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00021.png");
	Medias->PulsarA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00021.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[21], Medias->PulsarA[21], "Assets\\Bitmaps\\Pulsar\\Pulsar[21].tga");

	Medias->Pulsar[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00022.png");
	Medias->PulsarA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00022.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[22], Medias->PulsarA[22], "Assets\\Bitmaps\\Pulsar\\Pulsar[22].tga");

	Medias->Pulsar[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00023.png");
	Medias->PulsarA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00023.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[23], Medias->PulsarA[23], "Assets\\Bitmaps\\Pulsar\\Pulsar[23].tga");

	Medias->Pulsar[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00024.png");
	Medias->PulsarA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00024.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[24], Medias->PulsarA[24], "Assets\\Bitmaps\\Pulsar\\Pulsar[24].tga");

	Medias->Pulsar[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00025.png");
	Medias->PulsarA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00025.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[25], Medias->PulsarA[25], "Assets\\Bitmaps\\Pulsar\\Pulsar[25].tga");

	Medias->Pulsar[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00026.png");
	Medias->PulsarA[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00026.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[26], Medias->PulsarA[26], "Assets\\Bitmaps\\Pulsar\\Pulsar[26].tga");

	Medias->Pulsar[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00027.png");
	Medias->PulsarA[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00027.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[27], Medias->PulsarA[27], "Assets\\Bitmaps\\Pulsar\\Pulsar[27].tga");

	Medias->Pulsar[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00028.png");
	Medias->PulsarA[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00028.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[28], Medias->PulsarA[28], "Assets\\Bitmaps\\Pulsar\\Pulsar[28].tga");

	Medias->Pulsar[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00029.png");
	Medias->PulsarA[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00029.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[29], Medias->PulsarA[29], "Assets\\Bitmaps\\Pulsar\\Pulsar[29].tga");

	Medias->Pulsar[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00030.png");
	Medias->PulsarA[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00030.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[30], Medias->PulsarA[30], "Assets\\Bitmaps\\Pulsar\\Pulsar[30].tga");

	Medias->Pulsar[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00031.png");
	Medias->PulsarA[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00031.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[31], Medias->PulsarA[31], "Assets\\Bitmaps\\Pulsar\\Pulsar[31].tga");

	Medias->Pulsar[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00032.png");
	Medias->PulsarA[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00032.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[32], Medias->PulsarA[32], "Assets\\Bitmaps\\Pulsar\\Pulsar[32].tga");

	Medias->Pulsar[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00033.png");
	Medias->PulsarA[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00033.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[33], Medias->PulsarA[33], "Assets\\Bitmaps\\Pulsar\\Pulsar[33].tga");

	Medias->Pulsar[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00034.png");
	Medias->PulsarA[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00034.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[34], Medias->PulsarA[34], "Assets\\Bitmaps\\Pulsar\\Pulsar[34].tga");

	Medias->Pulsar[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00035.png");
	Medias->PulsarA[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00035.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[35], Medias->PulsarA[35], "Assets\\Bitmaps\\Pulsar\\Pulsar[35].tga");

	Medias->Pulsar[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00036.png");
	Medias->PulsarA[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00036.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[36], Medias->PulsarA[36], "Assets\\Bitmaps\\Pulsar\\Pulsar[36].tga");

	Medias->Pulsar[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00037.png");
	Medias->PulsarA[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00037.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[37], Medias->PulsarA[37], "Assets\\Bitmaps\\Pulsar\\Pulsar[37].tga");

	Medias->Pulsar[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00038.png");
	Medias->PulsarA[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00038.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[38], Medias->PulsarA[38], "Assets\\Bitmaps\\Pulsar\\Pulsar[38].tga");

	Medias->Pulsar[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00039.png");
	Medias->PulsarA[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00039.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[39], Medias->PulsarA[39], "Assets\\Bitmaps\\Pulsar\\Pulsar[39].tga");

	Medias->Pulsar[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00040.png");
	Medias->PulsarA[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00040.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[40], Medias->PulsarA[40], "Assets\\Bitmaps\\Pulsar\\Pulsar[40].tga");

	Medias->Pulsar[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00041.png");
	Medias->PulsarA[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00041.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[41], Medias->PulsarA[41], "Assets\\Bitmaps\\Pulsar\\Pulsar[41].tga");

	Medias->Pulsar[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\Puls00042.png");
	Medias->PulsarA[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00042.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Pulsar[42], Medias->PulsarA[42], "Assets\\Bitmaps\\Pulsar\\Pulsar[42].tga");
	}


//##### Mid Hits Pulsar
if(1)
	{
	Medias->PulsarMid[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00011.png");
	Medias->PulsarMidA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00011.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[11], Medias->PulsarMidA[11], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[11].tga");

	Medias->PulsarMid[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00012.png");
	Medias->PulsarMidA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00012.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[12], Medias->PulsarMidA[12], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[12].tga");

	Medias->PulsarMid[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00013.png");
	Medias->PulsarMidA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00013.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[13], Medias->PulsarMidA[13], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[13].tga");

	Medias->PulsarMid[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00014.png");
	Medias->PulsarMidA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00014.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[14], Medias->PulsarMidA[14], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[14].tga");

	Medias->PulsarMid[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00015.png");
	Medias->PulsarMidA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00015.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[15], Medias->PulsarMidA[15], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[15].tga");

	Medias->PulsarMid[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00016.png");
	Medias->PulsarMidA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00016.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[16], Medias->PulsarMidA[16], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[16].tga");

	Medias->PulsarMid[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00017.png");
	Medias->PulsarMidA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00017.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[17], Medias->PulsarMidA[17], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[17].tga");

	Medias->PulsarMid[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00018.png");
	Medias->PulsarMidA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00018.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[18], Medias->PulsarMidA[18], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[18].tga");

	Medias->PulsarMid[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00019.png");
	Medias->PulsarMidA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00019.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[19], Medias->PulsarMidA[19], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[19].tga");

	Medias->PulsarMid[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00020.png");
	Medias->PulsarMidA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00020.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[20], Medias->PulsarMidA[20], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[20].tga");

	Medias->PulsarMid[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00021.png");
	Medias->PulsarMidA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00021.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[21], Medias->PulsarMidA[21], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[21].tga");

	Medias->PulsarMid[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00022.png");
	Medias->PulsarMidA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00022.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[22], Medias->PulsarMidA[22], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[22].tga");

	Medias->PulsarMid[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00023.png");
	Medias->PulsarMidA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00023.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[23], Medias->PulsarMidA[23], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[23].tga");

	Medias->PulsarMid[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00024.png");
	Medias->PulsarMidA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00024.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[24], Medias->PulsarMidA[24], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[24].tga");

	Medias->PulsarMid[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00025.png");
	Medias->PulsarMidA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00025.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[25], Medias->PulsarMidA[25], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[25].tga");

	Medias->PulsarMid[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00026.png");
	Medias->PulsarMidA[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00026.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[26], Medias->PulsarMidA[26], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[26].tga");

	Medias->PulsarMid[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00027.png");
	Medias->PulsarMidA[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00027.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[27], Medias->PulsarMidA[27], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[27].tga");

	Medias->PulsarMid[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00028.png");
	Medias->PulsarMidA[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00028.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[28], Medias->PulsarMidA[28], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[28].tga");

	Medias->PulsarMid[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00029.png");
	Medias->PulsarMidA[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00029.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[29], Medias->PulsarMidA[29], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[29].tga");

	Medias->PulsarMid[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00030.png");
	Medias->PulsarMidA[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00030.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[30], Medias->PulsarMidA[30], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[30].tga");

	Medias->PulsarMid[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00031.png");
	Medias->PulsarMidA[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00031.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[31], Medias->PulsarMidA[31], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[31].tga");

	Medias->PulsarMid[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00032.png");
	Medias->PulsarMidA[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00032.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[32], Medias->PulsarMidA[32], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[32].tga");

	Medias->PulsarMid[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00033.png");
	Medias->PulsarMidA[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00033.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[33], Medias->PulsarMidA[33], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[33].tga");

	Medias->PulsarMid[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00034.png");
	Medias->PulsarMidA[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00034.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[34], Medias->PulsarMidA[34], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[34].tga");

	Medias->PulsarMid[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00035.png");
	Medias->PulsarMidA[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00035.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[35], Medias->PulsarMidA[35], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[35].tga");

	Medias->PulsarMid[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00036.png");
	Medias->PulsarMidA[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00036.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[36], Medias->PulsarMidA[36], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[36].tga");

	Medias->PulsarMid[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00037.png");
	Medias->PulsarMidA[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00037.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[37], Medias->PulsarMidA[37], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[37].tga");

	Medias->PulsarMid[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00038.png");
	Medias->PulsarMidA[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00038.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[38], Medias->PulsarMidA[38], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[38].tga");

	Medias->PulsarMid[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00039.png");
	Medias->PulsarMidA[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00039.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[39], Medias->PulsarMidA[39], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[39].tga");

	Medias->PulsarMid[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00040.png");
	Medias->PulsarMidA[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00040.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[40], Medias->PulsarMidA[40], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[40].tga");

	Medias->PulsarMid[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00041.png");
	Medias->PulsarMidA[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00041.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[41], Medias->PulsarMidA[41], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[41].tga");

	Medias->PulsarMid[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\PulsarMid\\Puls00042.png");
	Medias->PulsarMidA[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Pulsar\\PulsA00042.png");
	Qpo->Tex_AlphaLayerBlat(Medias->PulsarMid[42], Medias->PulsarMidA[42], "Assets\\Bitmaps\\PulsarMid\\PulsarMid[42].tga");
	}


	//##### Rocket engine
if(1)
	{
	Medias->Rocket[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00068.png");
	Medias->RocketA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00068.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[0], Medias->RocketA[0], "Assets\\Bitmaps\\Rocket\\Rocket[0].tga");

	Medias->Rocket[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00073.png");
	Medias->RocketA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00073.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[1], Medias->RocketA[1], "Assets\\Bitmaps\\Rocket\\Rocket[1].tga");

	Medias->Rocket[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00078.png");
	Medias->RocketA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00078.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[2], Medias->RocketA[2], "Assets\\Bitmaps\\Rocket\\Rocket[2].tga");

	Medias->Rocket[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00083.png");
	Medias->RocketA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00083.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[3], Medias->RocketA[3], "Assets\\Bitmaps\\Rocket\\Rocket[3].tga");

	Medias->Rocket[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00088.png");
	Medias->RocketA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00088.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[4], Medias->RocketA[4], "Assets\\Bitmaps\\Rocket\\Rocket[4].tga");

	Medias->Rocket[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00093.png");
	Medias->RocketA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00093.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[5], Medias->RocketA[5], "Assets\\Bitmaps\\Rocket\\Rocket[5].tga");

	Medias->Rocket[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00098.png");
	Medias->RocketA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00098.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[6], Medias->RocketA[6], "Assets\\Bitmaps\\Rocket\\Rocket[6].tga");

	Medias->Rocket[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00103.png");
	Medias->RocketA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00103.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[7], Medias->RocketA[7], "Assets\\Bitmaps\\Rocket\\Rocket[7].tga");

	Medias->Rocket[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00108.png");
	Medias->RocketA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00108.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[8], Medias->RocketA[8], "Assets\\Bitmaps\\Rocket\\Rocket[8].tga");

	Medias->Rocket[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\Rocket00113.png");
	Medias->RocketA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Rocket\\RocketA00113.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Rocket[9], Medias->RocketA[9], "Assets\\Bitmaps\\Rocket\\Rocket[9].tga");
	}


		//##### Rocket engine
if(1)
	{
	Medias->Star[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00300.png");
	Medias->StarA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00300.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[0], Medias->StarA[0], "Assets\\Bitmaps\\Star\\Star[0].tga");

	Medias->Star[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00305.png");
	Medias->StarA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00305.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[1], Medias->StarA[1], "Assets\\Bitmaps\\Star\\Star[1].tga");

	Medias->Star[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00310.png");
	Medias->StarA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00310.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[2], Medias->StarA[2], "Assets\\Bitmaps\\Star\\Star[2].tga");

	Medias->Star[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00315.png");
	Medias->StarA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00315.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[3], Medias->StarA[3], "Assets\\Bitmaps\\Star\\Star[3].tga");

	Medias->Star[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00320.png");
	Medias->StarA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00320.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[4], Medias->StarA[4], "Assets\\Bitmaps\\Star\\Star[4].tga");

	Medias->Star[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00325.png");
	Medias->StarA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00325.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[5], Medias->StarA[5], "Assets\\Bitmaps\\Star\\Star[5].tga");

	Medias->Star[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00330.png");
	Medias->StarA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00330.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[6], Medias->StarA[6], "Assets\\Bitmaps\\Star\\Star[6].tga");

	Medias->Star[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00335.png");
	Medias->StarA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00335.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[7], Medias->StarA[7], "Assets\\Bitmaps\\Star\\Star[7].tga");

	Medias->Star[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00340.png");
	Medias->StarA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00340.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[8], Medias->StarA[8], "Assets\\Bitmaps\\Star\\Star[8].tga");

	Medias->Star[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00345.png");
	Medias->StarA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00345.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[9], Medias->StarA[9], "Assets\\Bitmaps\\Star\\Star[9].tga");

	Medias->Star[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00350.png");
	Medias->StarA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00350.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[10], Medias->StarA[10], "Assets\\Bitmaps\\Star\\Star[10].tga");

	Medias->Star[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00355.png");
	Medias->StarA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00355.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[11], Medias->StarA[11], "Assets\\Bitmaps\\Star\\Star[11].tga");

	Medias->Star[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00360.png");
	Medias->StarA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00360.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[12], Medias->StarA[12], "Assets\\Bitmaps\\Star\\Star[12].tga");

	Medias->Star[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00365.png");
	Medias->StarA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00365.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[13], Medias->StarA[13], "Assets\\Bitmaps\\Star\\Star[13].tga");

	Medias->Star[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00370.png");
	Medias->StarA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00370.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[14], Medias->StarA[14], "Assets\\Bitmaps\\Star\\Star[14].tga");

	Medias->Star[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00385.png");
	Medias->StarA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00385.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[15], Medias->StarA[15], "Assets\\Bitmaps\\Star\\Star[15].tga");

	Medias->Star[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00390.png");
	Medias->StarA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00390.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[16], Medias->StarA[16], "Assets\\Bitmaps\\Star\\Star[16].tga");

	Medias->Star[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00400.png");
	Medias->StarA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00400.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[17], Medias->StarA[17], "Assets\\Bitmaps\\Star\\Star[17].tga");

	Medias->Star[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00410.png");
	Medias->StarA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00410.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[18], Medias->StarA[18], "Assets\\Bitmaps\\Star\\Star[18].tga");

	Medias->Star[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00415.png");
	Medias->StarA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00415.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[19], Medias->StarA[19], "Assets\\Bitmaps\\Star\\Star[19].tga");

	Medias->Star[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00420.png");
	Medias->StarA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00420.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[20], Medias->StarA[20], "Assets\\Bitmaps\\Star\\Star[20].tga");

	Medias->Star[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00425.png");
	Medias->StarA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00425.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[21], Medias->StarA[21], "Assets\\Bitmaps\\Star\\Star[21].tga");

	Medias->Star[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00430.png");
	Medias->StarA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00430.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[22], Medias->StarA[22], "Assets\\Bitmaps\\Star\\Star[22].tga");

	Medias->Star[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00435.png");
	Medias->StarA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00435.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[23], Medias->StarA[23], "Assets\\Bitmaps\\Star\\Star[23].tga");

	Medias->Star[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00440.png");
	Medias->StarA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00440.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[24], Medias->StarA[24], "Assets\\Bitmaps\\Star\\Star[24].tga");

	Medias->Star[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\Star00445.png");
	Medias->StarA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Star\\StarA00445.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Star[25], Medias->StarA[25], "Assets\\Bitmaps\\Star\\Star[25].tga");
	}


if(1)
	{
	//#### Medias->Water
	Medias->Water[124] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00124.png");
	Medias->WaterA[124] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00124.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[124], Medias->WaterA[124], "Assets\\Bitmaps\\Water\\Water[124].tga");

	Medias->Water[125] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00125.png");
	Medias->WaterA[125] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00125.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[125], Medias->WaterA[125], "Assets\\Bitmaps\\Water\\Water[125].tga");

	Medias->Water[126] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00126.png");
	Medias->WaterA[126] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00126.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[126], Medias->WaterA[126], "Assets\\Bitmaps\\Water\\Water[126].tga");

	Medias->Water[127] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00127.png");
	Medias->WaterA[127] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00127.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[127], Medias->WaterA[127], "Assets\\Bitmaps\\Water\\Water[127].tga");

	Medias->Water[128] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00128.png");
	Medias->WaterA[128] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00128.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[128], Medias->WaterA[128], "Assets\\Bitmaps\\Water\\Water[128].tga");

	Medias->Water[129] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00129.png");
	Medias->WaterA[129] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00129.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[129], Medias->WaterA[129], "Assets\\Bitmaps\\Water\\Water[129].tga");

	Medias->Water[130] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00130.png");
	Medias->WaterA[130] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00130.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[130], Medias->WaterA[130], "Assets\\Bitmaps\\Water\\Water[130].tga");

	Medias->Water[131] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00131.png");
	Medias->WaterA[131] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00131.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[131], Medias->WaterA[131], "Assets\\Bitmaps\\Water\\Water[131].tga");

	Medias->Water[132] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00132.png");
	Medias->WaterA[132] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00132.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[132], Medias->WaterA[132], "Assets\\Bitmaps\\Water\\Water[132].tga");

	Medias->Water[133] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00133.png");
	Medias->WaterA[133] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00133.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[133], Medias->WaterA[133], "Assets\\Bitmaps\\Water\\Water[133].tga");

	Medias->Water[134] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00134.png");
	Medias->WaterA[134] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00134.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[134], Medias->WaterA[134], "Assets\\Bitmaps\\Water\\Water[134].tga");

	Medias->Water[135] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00135.png");
	Medias->WaterA[135] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00135.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[135], Medias->WaterA[135], "Assets\\Bitmaps\\Water\\Water[135].tga");

	Medias->Water[136] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\Water00136.png");
	Medias->WaterA[136] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Water\\WaterA00136.png");
	Qpo->Tex_AlphaLayerBlat(Medias->Water[136], Medias->WaterA[136], "Assets\\Bitmaps\\Water\\Water[136].tga");
	}


		//Mine build sign
	Medias->mmine = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\mmine.png");
	//Medias->mmineA = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\mmineA.png");
	Medias->mmineAF = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\mmineAF.png");
	Qpo->Tex_AlphaLayerBlat(Medias->mmine, Medias->mmineAF, "Assets\\Bitmaps\\mmine.tga");

		//Build Menu
	Medias->buildm = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\buildmenu.png");

	//##### CLOUD SMOKE

if(1)
	{
	Medias->QSmoke[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke1.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[0], Medias->QSmokeA[0], "Assets\\Bitmaps\\Smoke1\\QSmoke[0].tga");

	Medias->QSmoke[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke2.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[1], Medias->QSmokeA[1], "Assets\\Bitmaps\\Smoke1\\QSmoke[1].tga");

	Medias->QSmoke[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke3.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[2], Medias->QSmokeA[2], "Assets\\Bitmaps\\Smoke1\\QSmoke[2].tga");

	Medias->QSmoke[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke4.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[3], Medias->QSmokeA[3], "Assets\\Bitmaps\\Smoke1\\QSmoke[3].tga");

	Medias->QSmoke[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke5.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[4], Medias->QSmokeA[4], "Assets\\Bitmaps\\Smoke1\\QSmoke[4].tga");

	Medias->QSmoke[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke6.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[5], Medias->QSmokeA[5], "Assets\\Bitmaps\\Smoke1\\QSmoke[5].tga");

	Medias->QSmoke[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke7.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[6], Medias->QSmokeA[6], "Assets\\Bitmaps\\Smoke1\\QSmoke[6].tga");

	Medias->QSmoke[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke8.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[7], Medias->QSmokeA[7], "Assets\\Bitmaps\\Smoke1\\QSmoke[7].tga");

	Medias->QSmoke[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke9.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[8], Medias->QSmokeA[8], "Assets\\Bitmaps\\Smoke1\\QSmoke[8].tga");

	Medias->QSmoke[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke10.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[9], Medias->QSmokeA[9], "Assets\\Bitmaps\\Smoke1\\QSmoke[9].tga");

	Medias->QSmoke[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke11.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[10], Medias->QSmokeA[10], "Assets\\Bitmaps\\Smoke1\\QSmoke[10].tga");

	Medias->QSmoke[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke12.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[11], Medias->QSmokeA[11], "Assets\\Bitmaps\\Smoke1\\QSmoke[11].tga");

	Medias->QSmoke[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[12], Medias->QSmokeA[12], "Assets\\Bitmaps\\Smoke1\\QSmoke[12].tga");

	Medias->QSmoke[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke14.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[13], Medias->QSmokeA[13], "Assets\\Bitmaps\\Smoke1\\QSmoke[13].tga");

	Medias->QSmoke[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke15.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[14], Medias->QSmokeA[14], "Assets\\Bitmaps\\Smoke1\\QSmoke[14].tga");

	Medias->QSmoke[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke16.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[15], Medias->QSmokeA[15], "Assets\\Bitmaps\\Smoke1\\QSmoke[15].tga");

	Medias->QSmoke[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke17.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[16], Medias->QSmokeA[16], "Assets\\Bitmaps\\Smoke1\\QSmoke[16].tga");

	Medias->QSmoke[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke18.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[17], Medias->QSmokeA[17], "Assets\\Bitmaps\\Smoke1\\QSmoke[17].tga");

	Medias->QSmoke[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke19.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[18], Medias->QSmokeA[18], "Assets\\Bitmaps\\Smoke1\\QSmoke[18].tga");

	Medias->QSmoke[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke20.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[19], Medias->QSmokeA[19], "Assets\\Bitmaps\\Smoke1\\QSmoke[19].tga");

	Medias->QSmoke[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke21.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[20], Medias->QSmokeA[20], "Assets\\Bitmaps\\Smoke1\\QSmoke[20].tga");

	Medias->QSmoke[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke22.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[21], Medias->QSmokeA[21], "Assets\\Bitmaps\\Smoke1\\QSmoke[21].tga");

	Medias->QSmoke[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke23.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[22], Medias->QSmokeA[22], "Assets\\Bitmaps\\Smoke1\\QSmoke[22].tga");

	Medias->QSmoke[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke24.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[23], Medias->QSmokeA[23], "Assets\\Bitmaps\\Smoke1\\QSmoke[23].tga");

	Medias->QSmoke[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke25.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[24], Medias->QSmokeA[24], "Assets\\Bitmaps\\Smoke1\\QSmoke[24].tga");

	Medias->QSmoke[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke26.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[25], Medias->QSmokeA[25], "Assets\\Bitmaps\\Smoke1\\QSmoke[25].tga");

	Medias->QSmoke[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke27.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[26], Medias->QSmokeA[26], "Assets\\Bitmaps\\Smoke1\\QSmoke[26].tga");

	Medias->QSmoke[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke28.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[27], Medias->QSmokeA[27], "Assets\\Bitmaps\\Smoke1\\QSmoke[27].tga");

	Medias->QSmoke[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke29.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[28], Medias->QSmokeA[28], "Assets\\Bitmaps\\Smoke1\\QSmoke[28].tga");

	Medias->QSmoke[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke30.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[29], Medias->QSmokeA[29], "Assets\\Bitmaps\\Smoke1\\QSmoke[29].tga");

	Medias->QSmoke[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke31.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[30], Medias->QSmokeA[30], "Assets\\Bitmaps\\Smoke1\\QSmoke[30].tga");

	Medias->QSmoke[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke32.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[31], Medias->QSmokeA[31], "Assets\\Bitmaps\\Smoke1\\QSmoke[31].tga");

	Medias->QSmoke[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke33.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[32], Medias->QSmokeA[32], "Assets\\Bitmaps\\Smoke1\\QSmoke[32].tga");

	Medias->QSmoke[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke34.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[33], Medias->QSmokeA[33], "Assets\\Bitmaps\\Smoke1\\QSmoke[33].tga");

	Medias->QSmoke[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke35.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[34], Medias->QSmokeA[34], "Assets\\Bitmaps\\Smoke1\\QSmoke[34].tga");

	Medias->QSmoke[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke36.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[35], Medias->QSmokeA[35], "Assets\\Bitmaps\\Smoke1\\QSmoke[35].tga");

	Medias->QSmoke[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke37.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[36], Medias->QSmokeA[36], "Assets\\Bitmaps\\Smoke1\\QSmoke[36].tga");

	Medias->QSmoke[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke38.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[37], Medias->QSmokeA[37], "Assets\\Bitmaps\\Smoke1\\QSmoke[37].tga");

	Medias->QSmoke[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke39.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[38], Medias->QSmokeA[38], "Assets\\Bitmaps\\Smoke1\\QSmoke[38].tga");

	Medias->QSmoke[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke40.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[39], Medias->QSmokeA[39], "Assets\\Bitmaps\\Smoke1\\QSmoke[39].tga");

	Medias->QSmoke[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke41.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[40], Medias->QSmokeA[40], "Assets\\Bitmaps\\Smoke1\\QSmoke[40].tga");

	Medias->QSmoke[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke42.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[41], Medias->QSmokeA[41], "Assets\\Bitmaps\\Smoke1\\QSmoke[41].tga");

	Medias->QSmoke[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke43.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[42], Medias->QSmokeA[42], "Assets\\Bitmaps\\Smoke1\\QSmoke[42].tga");

	Medias->QSmoke[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke44.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[43], Medias->QSmokeA[43], "Assets\\Bitmaps\\Smoke1\\QSmoke[43].tga");

	Medias->QSmoke[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke45.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[44], Medias->QSmokeA[44], "Assets\\Bitmaps\\Smoke1\\QSmoke[44].tga");

	Medias->QSmoke[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke46.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[45], Medias->QSmokeA[45], "Assets\\Bitmaps\\Smoke1\\QSmoke[45].tga");

	Medias->QSmoke[46] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[46] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke47.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[46], Medias->QSmokeA[46], "Assets\\Bitmaps\\Smoke1\\QSmoke[46].tga");

	Medias->QSmoke[47] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[47] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke48.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[47], Medias->QSmokeA[47], "Assets\\Bitmaps\\Smoke1\\QSmoke[47].tga");

	Medias->QSmoke[48] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[48] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke49.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[48], Medias->QSmokeA[48], "Assets\\Bitmaps\\Smoke1\\QSmoke[48].tga");

	Medias->QSmoke[49] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\White.png");
	Medias->QSmokeA[49] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\Smoke1\\Smoke50.png");
	Qpo->Tex_AlphaLayerBlat(Medias->QSmoke[49], Medias->QSmokeA[49], "Assets\\Bitmaps\\Smoke1\\QSmoke[49].tga");
	}


if(0)	//FULL  JINK ENERGY BITMAP
	{
	Medias->JEnergy[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER00.png");
	Medias->JEnergyA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA00.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[0], Medias->JEnergyA[0], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

	Medias->JEnergy[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER01.png");
	Medias->JEnergyA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA01.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[1], Medias->JEnergyA[1], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

	Medias->JEnergy[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER02.png");
	Medias->JEnergyA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[2], Medias->JEnergyA[2], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

	Medias->JEnergy[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER03.png");
	Medias->JEnergyA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA03.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[3], Medias->JEnergyA[3], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

	Medias->JEnergy[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER04.png");
	Medias->JEnergyA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA04.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[4], Medias->JEnergyA[4], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

	Medias->JEnergy[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER05.png");
	Medias->JEnergyA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[5], Medias->JEnergyA[5], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

	Medias->JEnergy[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER06.png");
	Medias->JEnergyA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA06.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[6], Medias->JEnergyA[6], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

	Medias->JEnergy[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER07.png");
	Medias->JEnergyA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA07.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[7], Medias->JEnergyA[7], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

	Medias->JEnergy[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER08.png");
	Medias->JEnergyA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA08.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[8], Medias->JEnergyA[8], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

	Medias->JEnergy[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER09.png");
	Medias->JEnergyA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA09.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[9], Medias->JEnergyA[9], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

	Medias->JEnergy[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER10.png");
	Medias->JEnergyA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA10.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[10], Medias->JEnergyA[10], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

	Medias->JEnergy[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER11.png");
	Medias->JEnergyA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA11.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[11], Medias->JEnergyA[11], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

	Medias->JEnergy[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER12.png");
	Medias->JEnergyA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA12.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[12], Medias->JEnergyA[12], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

	Medias->JEnergy[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER13.png");
	Medias->JEnergyA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[13], Medias->JEnergyA[13], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

	Medias->JEnergy[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER14.png");
	Medias->JEnergyA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA14.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[14], Medias->JEnergyA[14], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

	Medias->JEnergy[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER15.png");
	Medias->JEnergyA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA15.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[15], Medias->JEnergyA[15], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");

	Medias->JEnergy[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER16.png");
	Medias->JEnergyA[16] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA16.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[16], Medias->JEnergyA[16], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[16].tga");

	Medias->JEnergy[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER17.png");
	Medias->JEnergyA[17] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA17.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[17], Medias->JEnergyA[17], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[17].tga");

	Medias->JEnergy[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER18.png");
	Medias->JEnergyA[18] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA18.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[18], Medias->JEnergyA[18], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[18].tga");

	Medias->JEnergy[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER19.png");
	Medias->JEnergyA[19] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA19.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[19], Medias->JEnergyA[19], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[19].tga");

	Medias->JEnergy[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER20.png");
	Medias->JEnergyA[20] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA20.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[20], Medias->JEnergyA[20], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[20].tga");

	Medias->JEnergy[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER21.png");
	Medias->JEnergyA[21] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA21.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[21], Medias->JEnergyA[21], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[21].tga");

	Medias->JEnergy[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER22.png");
	Medias->JEnergyA[22] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA22.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[22], Medias->JEnergyA[22], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[22].tga");

	Medias->JEnergy[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER23.png");
	Medias->JEnergyA[23] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA23.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[23], Medias->JEnergyA[23], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[23].tga");

	Medias->JEnergy[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER24.png");
	Medias->JEnergyA[24] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA24.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[24], Medias->JEnergyA[24], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[24].tga");

	Medias->JEnergy[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER25.png");
	Medias->JEnergyA[25] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA25.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[25], Medias->JEnergyA[25], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[25].tga");

	Medias->JEnergy[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER26.png");
	Medias->JEnergyA[26] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA26.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[26], Medias->JEnergyA[26], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[26].tga");

	Medias->JEnergy[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER27.png");
	Medias->JEnergyA[27] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA27.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[27], Medias->JEnergyA[27], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[27].tga");

	Medias->JEnergy[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER28.png");
	Medias->JEnergyA[28] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA28.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[28], Medias->JEnergyA[28], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[28].tga");

	Medias->JEnergy[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER29.png");
	Medias->JEnergyA[29] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA29.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[29], Medias->JEnergyA[29], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[29].tga");

	Medias->JEnergy[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER30.png");
	Medias->JEnergyA[30] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA30.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[30], Medias->JEnergyA[30], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[30].tga");

	Medias->JEnergy[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER31.png");
	Medias->JEnergyA[31] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA31.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[31], Medias->JEnergyA[31], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[31].tga");

	Medias->JEnergy[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER32.png");
	Medias->JEnergyA[32] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA32.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[32], Medias->JEnergyA[32], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[32].tga");

	Medias->JEnergy[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER33.png");
	Medias->JEnergyA[33] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA33.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[33], Medias->JEnergyA[33], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[33].tga");

	Medias->JEnergy[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER34.png");
	Medias->JEnergyA[34] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA34.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[34], Medias->JEnergyA[34], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[34].tga");

	Medias->JEnergy[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER35.png");
	Medias->JEnergyA[35] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA35.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[35], Medias->JEnergyA[35], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[35].tga");

	Medias->JEnergy[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER36.png");
	Medias->JEnergyA[36] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA36.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[36], Medias->JEnergyA[36], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[36].tga");

	Medias->JEnergy[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER37.png");
	Medias->JEnergyA[37] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA37.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[37], Medias->JEnergyA[37], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[37].tga");

	Medias->JEnergy[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER38.png");
	Medias->JEnergyA[38] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA38.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[38], Medias->JEnergyA[38], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[38].tga");

	Medias->JEnergy[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER39.png");
	Medias->JEnergyA[39] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA39.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[39], Medias->JEnergyA[39], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[39].tga");

	Medias->JEnergy[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER40.png");
	Medias->JEnergyA[40] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA40.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[40], Medias->JEnergyA[40], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[40].tga");

	Medias->JEnergy[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER41.png");
	Medias->JEnergyA[41] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA41.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[41], Medias->JEnergyA[41], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[41].tga");

	Medias->JEnergy[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER42.png");
	Medias->JEnergyA[42] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA42.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[42], Medias->JEnergyA[42], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[42].tga");

	Medias->JEnergy[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER43.png");
	Medias->JEnergyA[43] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA43.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[43], Medias->JEnergyA[43], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[43].tga");

	Medias->JEnergy[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER44.png");
	Medias->JEnergyA[44] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA44.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[44], Medias->JEnergyA[44], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[44].tga");

	Medias->JEnergy[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER45.png");
	Medias->JEnergyA[45] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA45.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[45], Medias->JEnergyA[45], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[45].tga");
	}


if(1)	//COMPACT  JINK ENERGY BITMAP
	{
	Medias->JEnergy[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER00.png");
	Medias->JEnergyA[0] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA00.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[0], Medias->JEnergyA[0], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[0].tga");

	Medias->JEnergy[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER01.png");
	Medias->JEnergyA[1] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA01.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[1], Medias->JEnergyA[1], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[1].tga");

	Medias->JEnergy[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER02.png");
	Medias->JEnergyA[2] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA02.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[2], Medias->JEnergyA[2], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[2].tga");

	Medias->JEnergy[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER03.png");
	Medias->JEnergyA[3] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA03.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[3], Medias->JEnergyA[3], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[3].tga");

	Medias->JEnergy[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER04.png");
	Medias->JEnergyA[4] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA04.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[4], Medias->JEnergyA[4], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[4].tga");

	Medias->JEnergy[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER05.png");
	Medias->JEnergyA[5] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA05.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[5], Medias->JEnergyA[5], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[5].tga");

	Medias->JEnergy[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER06.png");
	Medias->JEnergyA[6] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA06.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[6], Medias->JEnergyA[6], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[6].tga");

	Medias->JEnergy[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER07.png");
	Medias->JEnergyA[7] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA07.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[7], Medias->JEnergyA[7], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[7].tga");

	Medias->JEnergy[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER08.png");
	Medias->JEnergyA[8] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA08.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[8], Medias->JEnergyA[8], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[8].tga");

	Medias->JEnergy[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER09.png");
	Medias->JEnergyA[9] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA09.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[9], Medias->JEnergyA[9], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[9].tga");

	Medias->JEnergy[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER10.png");
	Medias->JEnergyA[10] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA10.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[10], Medias->JEnergyA[10], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[10].tga");

	Medias->JEnergy[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER11.png");
	Medias->JEnergyA[11] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA11.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[11], Medias->JEnergyA[11], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[11].tga");

	Medias->JEnergy[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER12.png");
	Medias->JEnergyA[12] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA12.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[12], Medias->JEnergyA[12], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[12].tga");

	Medias->JEnergy[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER13.png");
	Medias->JEnergyA[13] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA13.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[13], Medias->JEnergyA[13], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[13].tga");

	Medias->JEnergy[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER14.png");
	Medias->JEnergyA[14] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA14.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[14], Medias->JEnergyA[14], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[14].tga");

	Medias->JEnergy[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJER15.png");
	Medias->JEnergyA[15] = Qpo->Tex_LoadTexture(UN_TEXTURE_TGA, "Assets\\Bitmaps\\JEnergyBit\\TJERA15.png");
	Qpo->Tex_AlphaLayerBlat(Medias->JEnergy[15], Medias->JEnergyA[15], "Assets\\Bitmaps\\JEnergyBit\\JEnergy[15].tga");
	}
#endif
}

};

#pragma message ("###  Initialising Textures  [Q-InitBitmaps.h]")
