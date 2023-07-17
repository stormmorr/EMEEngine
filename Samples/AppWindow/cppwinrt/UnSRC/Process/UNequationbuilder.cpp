/*

    UNequationbuilder - Equation Generating Conscious State
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNequationbuilder.h"

#include "Shellapi.h"

#include <stdio.h>
#include <fstream>

using namespace UN;

namespace UN
{

float sqreqb(float i_Float) { return i_Float * i_Float; }

bool isinitialized = false;

UNequationbuilder::UNequationbuilder(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	SUPPORT_THREAD_SYNCHRONIZATION(UNequationbuilder)
	SUPPORT_THREAD_NOTIFICATION
	PP_STATE = 0;

	m_mutex_State = SDL_CreateMutex();
	m_mutex_Activity = SDL_CreateMutex();
	m_mutex_Rand = SDL_CreateMutex();
	m_mutex_Beep = SDL_CreateMutex();
	m_mutex_Clear = SDL_CreateMutex();
	m_mutex_Load = SDL_CreateMutex();

	char casecntbuf[100];
	std::string strFilename;

	m_fileoptions = fopen("Equation//EquationBuilder.opt", "r");

	fscanf(m_fileoptions, "%i", &m_filecount);

	fclose(m_fileoptions);
	
	m_filecount++;

	m_fileoptions = fopen("Equation//EquationBuilder.opt", "w");

	fprintf(m_fileoptions, "%i ", m_filecount);

	fprintf(m_fileoptions, " //Equation file count");

	fclose(m_fileoptions);

	itoa(m_filecount, casecntbuf, 10);

	std::string strname = "Equation//Equation";
	std::string strnumber = casecntbuf;
	std::string strext = ".txt";
	strFilename = strname + strnumber + strext;

	m_file = fopen(strFilename.c_str(), "w");

	m_Ready = false;

	SDL_mutexP(m_mutex_State);
	m_BuildStatus = 0;
	m_Mode = 0;
	SDL_mutexV(m_mutex_State);

	SDL_mutexP(m_mutex_Activity);
	m_Remote.m_Type = 0;
	SDL_mutexV(m_mutex_Activity);

	SDL_mutexP(m_mutex_Beep);
	m_Beep = 0;
	SDL_mutexV(m_mutex_Beep);

	SDL_mutexP(m_mutex_Clear);
	m_Clear = false;
	SDL_mutexV(m_mutex_Clear);

	//Set Change Variable
	m_ChangeVar = 1;

	// Load Point Objects
	std::ifstream i_File;
	i_File.open("Patch\\PlanetPatch\\UNequationbayS.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayS.pnt not found");
		for(;;) {}
		}

	char* i_c = new char[1];
	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_SPNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbay1.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbay1.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_1PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbay2.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbay2.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_2PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayE.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayE.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_EPNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayF1.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayF1.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_F1PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayF2.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayF2.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_F2PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayF3.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayF3.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_F3PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayS1.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayS1.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_S1PNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbaySQ.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbaySQ.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_SQPNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	i_File.open("Patch\\PlanetPatch\\UNequationbayV.pnt", std::ios::in | std::ios::binary);
	if(!i_File)
		{
		printf("UNequationbayV.pnt not found.");
		for(;;) {}
		}

	i_c[0] = ' ';
	while(i_c[0] != '£')
		{
		m_VPNT.push_back(i_c[0]);
		i_File.read((char *)i_c, 1);
		}

	// explicitely close the file
	i_File.close();

	m_equation1 = m_F1PNT;
	m_equation2 = m_F2PNT;
	m_equation3 = m_F3PNT;

	SDL_mutexP(m_mutex_Load);
	m_Load = 0;
	SDL_mutexV(m_mutex_Load);

	// Clear Patch Directory
#if 0
	ShellExecute(m_HWND, "open", "C:\\Projects Base\\\Unification\\Build\\Patch\\PlanetPatch\\OSIDelete.bat", NULL, "", SW_SHOWMINIMIZED);
#else
	ShellExecute(m_HWND, "open", "C:\\Projects Base\\\Unification\\Build\\Patch\\PlanetPatch\\OSIDelete.bat", NULL, "", SW_HIDE);
#endif
}

void UNequationbuilder::acSetHWND(HWND i_HWND)
{
	m_HWND = i_HWND;
}

void UNequationbuilder::Initialize(void)
{
	PP_STATE = 1;
}

std::string UNequationbuilder::acRandPull(int i_Max)
{
	char casecntbuf[100];

	if(i_Max <= 3) i_Max = 3;

	int random = rand() % i_Max;

	itoa(random, casecntbuf, 10);

	std::string String = casecntbuf;

	return String;
}

std::string UNequationbuilder::acRandPullFloat(float i_Max)
{
	char* str = new char[30]; 

	float random = ((float)rand() / 32767) * i_Max;

	int check = rand() % 10;

	switch(check)
		{
		case 0:
			random = sqrt(random) / sqrt(random);
			break;

		case 1:
			random = sqrt(random);
			break;

		case 2:
			random = sqrt(random) / 5000;
			break;

		case 3:
			random = random / (rand() % 100);
			break;

		case 4:
			random = random / (rand() % 10);
			break;

		case 5:
			random = (random * random) * (random * random);
			break;

		case 6:
			random = (random * random);
			break;

		case 7:
			random = (random * random);// * 5000;
			break;

		case 8:
			random = random;// * (rand() % 1000);
			break;

		case 9:
			random = random;// * (rand() % 100);
			break;

		default:
			random = random * random;
			break;
		}

	if(random > 50000) random = 50000;
	if(random < -50000) random = -50000;

// Voctal - Delus
#if 0
	random += 0.0001;
#endif

	random += 0.1;

    sprintf(str, "%f", random);

	std::string String = str;

	return String;
}

std::string UNequationbuilder::acRandChangeFloat(float i_Input)
{
	char* str = new char[30]; 

	float random = (((float)rand() / 32767) - 0.5) * i_Input;

	//i_Input += random;

	/*switch(check)
		{
		case 0:
			random = sqrt(random) / sqrt(random);
			break;

		case 1:
			random = sqrt(random);
			break;

		case 2:
			random = sqrt(random) / 5000;
			break;

		case 3:
			random = random / (rand() % 100);
			break;

		case 4:
			random = random / (rand() % 10);
			break;

		case 5:
			random = (random * random) * (random * random);
			break;

		case 6:
			random = (random * random);
			break;

		case 7:
			random = (random * random) * 5000;
			break;

		case 8:
			random = random * (rand() % 1000);
			break;

		case 9:
			random = random * (rand() % 100);
			break;

		default:
			random = random * random;
			break;
		}*/

    sprintf(str, "%f", i_Input);

	std::string String = str;

	return String;
}

void UNequationbuilder::Run(void)
{
	while(PP_STATE > 0)
		{
		SDL_mutexP(m_mutex_State);
		int i_BuildStatus = m_BuildStatus;
		SDL_mutexV(m_mutex_State);

		SDL_mutexP(m_mutex_State);
		int i_Mode = m_Mode;
		SDL_mutexV(m_mutex_State);

		if(m_BuildStatus == EQBUILD_MODE_IDLE && i_Mode == EQBUILD_MODE_INITIALIZE)
			{
			SDL_mutexP(m_mutex_State);
			m_BuildStatus = EQBUILD_MODE_INITIALIZE;
			SDL_mutexV(m_mutex_State);

			SDL_mutexP(m_mutex_Activity);
			switch(m_Remote.m_Type)
				{
				case 0:
					acInit();
					break;
				case 1:
					acInit(m_Remote.m_Name);
					break;
				case 2:
					acInit();
					break;
				case 3:
					acInit(m_Remote.m_Name);
					break;
				}
			SDL_mutexV(m_mutex_Activity);

			SDL_mutexP(m_mutex_State);
			m_Mode = EQBUILD_MODE_BUILD;
			SDL_mutexV(m_mutex_State);
			}

		SDL_mutexP(m_mutex_State);
		i_BuildStatus = m_BuildStatus;
		SDL_mutexV(m_mutex_State);

		SDL_mutexP(m_mutex_State);
		i_Mode = m_Mode;
		SDL_mutexV(m_mutex_State);

		if(m_BuildStatus == EQBUILD_MODE_INITIALIZE && i_Mode == EQBUILD_MODE_BUILD)
			{
			SDL_mutexP(m_mutex_State);
			m_BuildStatus = EQBUILD_MODE_BUILD;
			SDL_mutexV(m_mutex_State);

			switch(m_Remote.m_Type)
				{
				case 0:
					acBuild();
					break;
				case 1:
					acBuild();
					break;
				case 2:
					acBuildAudio();
					break;
				case 3:
					acBuildAudio();
					break;
				}

			SDL_mutexP(m_mutex_State);
			m_Mode = EQBUILD_MODE_PRINTEQ;
			SDL_mutexV(m_mutex_State);
			}

		SDL_mutexP(m_mutex_State);
		i_BuildStatus = m_BuildStatus;
		SDL_mutexV(m_mutex_State);

		SDL_mutexP(m_mutex_State);
		i_Mode = m_Mode;
		SDL_mutexV(m_mutex_State);

		if(m_BuildStatus == EQBUILD_MODE_BUILD && i_Mode == EQBUILD_MODE_PRINTEQ)
			{
			SDL_mutexP(m_mutex_State);
			m_BuildStatus = EQBUILD_MODE_IDLE;
			SDL_mutexV(m_mutex_State);

			acPrintEQ();

			std::string i_PNT;
			std::string i_SemiC = ";";
			std::string i_EndChar = "\n";

			i_PNT = m_SPNT;

#if 0
			i_PNT = i_PNT + m_VPNT;
#endif

#if 1

// Voctal - Delus
#if 0
			float i_Float = ((float)rand() / 32767) * 100;
			sqrt(i_Float);
			// Same for each
#endif

			float i_Float = ((float)rand() / 32767) * 1;
			//sqrt(i_Float);

			i_PNT = i_PNT + "FN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN0_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN0_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 1;
			//sqrt(i_Float);

			i_PNT = i_PNT + "FRPWQN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN0_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN0_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 1;
			//sqrt(i_Float);

			i_PNT = i_PNT + "FRN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN0_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN0_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 1;
			//sqrt(i_Float);

			i_PNT = i_PNT + "FRPN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN0_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN0_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 1;
			//sqrt(i_Float);

			i_PNT = i_PNT + "FRPWN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN0_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_factor0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN0_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_change0 = " + acRandPullFloat(i_Float) + i_SemiC + i_EndChar;
#endif

#if 0
			float i_Float = ((float)rand() / 32767) * 3;
			int i_Int = rand() % 15;

			i_PNT = i_PNT + "FN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN0_factor0 = " + acRandChangeFloat(0.5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_factor0 = " + acRandChangeFloat(0.15) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_factor0 = " + acRandChangeFloat(0.75) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_factor0 = " + acRandChangeFloat(0.5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_factor0 = " + acRandChangeFloat(0.25) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN0_change0 = " + acRandChangeFloat(3) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN1_change0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN2_change0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN3_change0 = " + acRandChangeFloat(2) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FN4_change0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 0.01;
			i_Int = rand() % 5;

			i_PNT = i_PNT + "FRPWQN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN0_factor0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_factor0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_factor0 = " + acRandChangeFloat(0.5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_factor0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_factor0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN0_change0 = " + acRandChangeFloat(3) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN1_change0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN2_change0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN3_change0 = " + acRandChangeFloat(2) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWQN4_change0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 5;
			i_Int = rand() % 50;

			i_PNT = i_PNT + "FRN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN0_factor0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_factor0 = " + acRandChangeFloat(0.015) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_factor0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_factor0 = " + acRandChangeFloat(0.0500) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_factor0 = " + acRandChangeFloat(25) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN0_change0 = " + acRandChangeFloat(3) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN1_change0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN2_change0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN3_change0 = " + acRandChangeFloat(2) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRN4_change0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 3;
			i_Int = rand() % 500;

			i_PNT = i_PNT + "FRPN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN0_factor0 = " + acRandChangeFloat(0.5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_factor0 = " + acRandChangeFloat(0.15) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_factor0 = " + acRandChangeFloat(0.75) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_factor0 = " + acRandChangeFloat(0.500) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_factor0 = " + acRandChangeFloat(0.25) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN0_change0 = " + acRandChangeFloat(3) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN1_change0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN2_change0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN3_change0 = " + acRandChangeFloat(2) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPN4_change0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;

			i_Float = ((float)rand() / 32767) * 5000;
			i_Int = rand() % 50;

			i_PNT = i_PNT + "FRPWN0_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_point = 0" + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN0_factor0 = " + acRandChangeFloat(0.05) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_factor0 = " + acRandChangeFloat(50.015) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_factor0 = " + acRandChangeFloat(5000) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_factor0 = " + acRandChangeFloat(5000) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_factor0 = " + acRandChangeFloat(0.025) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN0_change0 = " + acRandChangeFloat(3) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN1_change0 = " + acRandChangeFloat(1) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN2_change0 = " + acRandChangeFloat(5) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN3_change0 = " + acRandChangeFloat(2) + i_SemiC + i_EndChar;
			i_PNT = i_PNT + "FRPWN4_change0 = " + acRandChangeFloat(4) + i_SemiC + i_EndChar;
#endif

			i_PNT = i_PNT + m_S1PNT;

#if 1
			// Compile Equation
			switch(m_ChangeVar)
				{
				case 0:
					m_equation1 = equation;
				break;
				case 1:
					m_equation2 = equation;
				break;
				case 2:
					m_equation3 = equation;
				break;
				}

#if 1
			i_PNT = i_PNT + m_equation1 + i_SemiC + m_1PNT + m_equation2 + i_SemiC + m_2PNT + m_equation3 + i_SemiC + m_EPNT;
#else
			i_PNT = i_PNT + m_F1PNT + i_SemiC + m_1PNT + m_equation2 + i_SemiC + m_2PNT + m_equation3 + i_SemiC + m_EPNT;
#endif
#else
			i_PNT = i_PNT + m_SQPNT + m_EPNT;
#endif

			m_ChangeVar++;
			if(m_ChangeVar == 1)
				{
				std::ofstream i_File;
				i_File.open("Patch\\PlanetPatch\\UNequationbay.cpp", std::ios::out | std::ios::binary);
				if(!i_File)
					{
					printf("UNequationbay.cpp was not spawned");
					for(;;) {}
					}

				char* i_c = new char[1];
				i_c[0] = ' ';
				for(unsigned int i_Count = 0; i_Count < i_PNT.length(); i_Count++)
					{
					i_c[0] = i_PNT[i_Count];
					i_File.write((char *)i_c, 1);
					}

				// explicitely close the file
				i_File.close();

				SDL_mutexP(m_mutex_Load);
				m_Load = 3;
				SDL_mutexV(m_mutex_Load);

				int m_Loaded = 0;
				bool i_Open = true;
				while(i_Open)
					{
					SDL_mutexP(m_mutex_Load);
					m_Loaded = m_Load;
					SDL_mutexV(m_mutex_Load);

					if(m_Loaded == 4) i_Open = false;
					}

				char casecntbuf[100];
				std::string strFilename;

				m_ppfileoptions = fopen("Patch//PlanetPatch//OSIPP.opt", "r");

				fscanf(m_ppfileoptions, "%i", &m_ppfilecount);

				fclose(m_ppfileoptions);

				m_ppfileoptions = fopen("Patch//PlanetPatch//OSIPP.opt", "w");

				fprintf(m_ppfileoptions, "%i ", m_ppfilecount + 1);

				fprintf(m_ppfileoptions, " //Planet Phone patch count");

				fclose(m_ppfileoptions);

				itoa(m_ppfilecount, casecntbuf, 10);

				std::string strname = "Patch//PlanetPatch//PlanetPatch";
				std::string strnumber = casecntbuf;
				std::string strext = ".dll";
				strFilename = strname + strnumber + strext;

				m_ppfile = fopen("Patch//PlanetPatch//OSIdllmain.def", "w");

				fprintf(m_ppfile, "LIBRARY   PlanetPatch%i.dll\n", m_ppfilecount);

				fprintf(m_ppfile, "EXPORTS\n");

				fprintf(m_ppfile, "	runImage	@1");

				fclose(m_ppfile);

				std::string strparam = "Patch//PlanetPatch//PlanetPatch";

				std::string i_ParamOutput = strparam + strnumber + strext;

				LPCSTR i_Parameters = i_ParamOutput.c_str();

#if 0
				ShellExecute(m_HWND, "open", "C:\\Projects Base\\\Unification\\Build\\Patch\\PlanetPatch\\OSIBuild.bat", i_Parameters, "", SW_SHOWMINIMIZED);
#else
				ShellExecute(m_HWND, "open", "C:\\Projects Base\\\Unification\\Build\\Patch\\PlanetPatch\\OSIBuild.bat", i_Parameters, "", SW_HIDE);
#endif

				SDL_mutexP(m_mutex_Load);
				m_Load = 2;
				SDL_mutexV(m_mutex_Load);

				SDL_mutexP(m_mutex_State);
				m_Mode = EQBUILD_MODE_IDLE;
				SDL_mutexV(m_mutex_State);
				}

			if(m_ChangeVar > 2) m_ChangeVar = 0;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int UNequationbuilder::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

	do
	{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
		{
		case CThread::CMD_INITIALIZE:
			Initialize();
			HandleCommandImmediately(CThread::CMD_RUN);
			break;

		case CThread::CMD_RUN:
			Run();
			break;

		case CThread::CMD_PAUSE:
			SetActivityStatus(CThread::THREAD_PAUSED);
			break;

		case CThread::CMD_STOP:
			bCanContinue = false;
			break;

		default:
			break;
		};

	} while (bCanContinue);

	return 0;	// ... if Thread task completition OK
}

void UNequationbuilder::acClose(void)
{
	fclose(m_file);
}

void UNequationbuilder::acInit(string i_name)
{
	acQuickInit("CLR", 1);
	acQuickInit("CLR", 2);
	acQuickInit("CLR", 3);
	acQuickInit("CLR", 4);
	acQuickInit("CLR", 5);
	acQuickInit("CLR", 6);

	acQuickInit(i_name, 1);
	acQuickInit(i_name, 2);
	acQuickInit(i_name, 3);
	acQuickInit(i_name, 4);
	acQuickInit(i_name, 5);
	acQuickInit(i_name, 6);

	m_Ready = true;
	m_name = i_name;
}

void UNequationbuilder::acInit(void)
{
	acQuickInit("CLR", 1);
	acQuickInit("CLR", 2);
	acQuickInit("CLR", 3);
	acQuickInit("CLR", 4);
	acQuickInit("CLR", 5);
	acQuickInit("CLR", 6);

	int i_selector = floor((float)acMathRandom() * 7);

	string i_name;

	switch(i_selector)
		{
		case 0: i_name = "UF"; break;
		case 1: i_name = "FE"; break;
		case 2: i_name = "TZ"; break;
		case 3: i_name = "DDR"; break;
		case 4: i_name = "AMG"; break;
		case 5: i_name = "JCD"; break;
		case 6: i_name = "AVS"; break;
		}

	acQuickInit(i_name, 1);
	acQuickInit(i_name, 2);
	acQuickInit(i_name, 3);
	acQuickInit(i_name, 4);
	acQuickInit(i_name, 5);
	acQuickInit(i_name, 6);

	m_Ready = true;
	m_name = i_name;
}

void UNequationbuilder::acQuickInit(string name, int type)
{
	if(name.compare("CLR") == 0)
		{
		if(type == 1)
			{
			counteropernumber = 0;
			}
		if(type == 2)
			{
			counterhfuncnumber = 0;
			}
		if(type == 3)
			{
			counterufuncnumber = 0;
			}
		if(type == 4)
			{
			countercvarsnumber = 0;
			}
		if(type == 5)
			{
			counterconstantnumber = 0;
			}
		if(type == 6)
			{
			counterparamsnumber = 0;
			}
		}

	mainvar = 'z';
	m_mainvar = "z";
	numofequations = 1;
	showz = true;

	if(name.compare("UF") == 0)
		{
		expressions = 15;
		cz = 20;
		cvam = 20;
		clin = 20;
		cfm = 50;
		cnum = 10;
		integer = true;
		nozero = true;
		ccvar = 10;
		ccon = 10;
		nummax = 5;
		cparen = 60;
		
		if(type == 1)
			{	
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 30;
			hfuncformxhfunc[0] = "sin(";
			hfuncformxhfunc[1] = "sinh(";
			hfuncformxhfunc[2] = "asin(";
			hfuncformxhfunc[3] = "asinh(";
			hfuncformxhfunc[4] = "cos(";
			hfuncformxhfunc[5] = "cosh(";
			hfuncformxhfunc[6] = "acos(";
			hfuncformxhfunc[7] = "acosh(";
			hfuncformxhfunc[8] = "tan(";
			hfuncformxhfunc[9] = "tanh(";
			hfuncformxhfunc[10] = "atan(";
			hfuncformxhfunc[11] = "atanh(";
			hfuncformxhfunc[12] = "cotan(";
			hfuncformxhfunc[13] = "cotanh(";
			hfuncformxhfunc[14] = "sqr(";
			hfuncformxhfunc[15] = "sqrt(";
			hfuncformxhfunc[16] = "log(";
			hfuncformxhfunc[17] = "exp(";
			hfuncformxhfunc[18] = "abs(";
			hfuncformxhfunc[19] = "cabs(";
			hfuncformxhfunc[20] = "conj(";
			hfuncformxhfunc[21] = "flip(";
			hfuncformxhfunc[22] = "ident(";
			hfuncformxhfunc[23] = "zero(";
			hfuncformxhfunc[24] = "recip(";
			hfuncformxhfunc[25] = "ceil(";
			hfuncformxhfunc[26] = "floor(";
			hfuncformxhfunc[27] = "trunc(";
			hfuncformxhfunc[28] = "round(";
			hfuncformxhfunc[29] = "atan2(";
			}

		if(type == 3)
			{
			counterufuncnumber = 4;
			ufuncformxufunc[0] = "fn1(";
			ufuncformxufunc[1] = "fn2(";
			ufuncformxufunc[2] = "fn3(";
			ufuncformxufunc[3] = "fn4(";
			}

		if(type == 4)
			{
			countercvarsnumber = 6;
			cvarsformxcvars[0] = "x";
			cvarsformxcvars[1] = "y";
			cvarsformxcvars[2] = "z";
			cvarsformxcvars[3] = "pixel";
			cvarsformxcvars[4] = "screenpixel";
			cvarsformxcvars[5] = "random";
			}

		if(type == 5)
			{
			counterconstantnumber = 10;
			constantformxconstant[0] = "angle";
			constantformxconstant[1] = "skew";
			constantformxconstant[2] = "center";
			constantformxconstant[3] = "stretch";
			constantformxconstant[4] = "magn";
			constantformxconstant[5] = "width";
			constantformxconstant[6] = "height";
			constantformxconstant[7] = "e";
			constantformxconstant[8] = "maxiter";
			constantformxconstant[9] = "pi";
			}

		if(type == 6)
			{
			counterparamsnumber = 6;
			paramsformxparams[0] = "p1";
			paramsformxparams[1] = "p2";
			paramsformxparams[2] = "p3";
			paramsformxparams[3] = "p4";
			paramsformxparams[4] = "p5";
			paramsformxparams[5] = "p6";
			}
		}

	if(name.compare("FE") == 0)
		{	
		expressions = 10;
		cz = 40;
		cvam = 30;
		clin = 30;
		cfm = 50;
		cnum = 25;
		integer = false;
		nozero = true;
		ccvar = 10;
		ccon = 10;
		nummax = 2;
		cparen = 10;
		
		if(type == 1)
			{	
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 28;
			hfuncformxhfunc[0] = "csin(";
			hfuncformxhfunc[1] = "csinh(";
			hfuncformxhfunc[2] = "casin(";
			hfuncformxhfunc[3] = "casinh(";
			hfuncformxhfunc[4] = "ccos(";
			hfuncformxhfunc[5] = "ccosh(";
			hfuncformxhfunc[6] = "cacos(";
			hfuncformxhfunc[7] = "cacosh(";
			hfuncformxhfunc[8] = "ctan(";
			hfuncformxhfunc[9] = "ctanh(";
			hfuncformxhfunc[10] = "catan(";
			hfuncformxhfunc[11] = "catanh(";
			hfuncformxhfunc[12] = "ccotan(";
			hfuncformxhfunc[13] = "ccotanh(";
			hfuncformxhfunc[14] = "csqr(";
			hfuncformxhfunc[15] = "csqrt(";
			hfuncformxhfunc[16] = "cln(";
			hfuncformxhfunc[17] = "cexp(";
			hfuncformxhfunc[18] = "cabs(";
			hfuncformxhfunc[19] = "cabs2(";
			hfuncformxhfunc[20] = "cconj(";
			hfuncformxhfunc[21] = "cflip(";
			hfuncformxhfunc[22] = "ctriple(";
			hfuncformxhfunc[23] = "cfour(";
			hfuncformxhfunc[24] = "crev(";
			hfuncformxhfunc[25] = "crev2(";
			hfuncformxhfunc[26] = "creal(";
			hfuncformxhfunc[27] = "cimag(";
			}

		if(type == 3)
			{
			counterufuncnumber = 2;
			ufuncformxufunc[0] = "fn1(";
			ufuncformxufunc[1] = "fn2(";
			}

		if(type == 4)
			{
			countercvarsnumber = 2;
			cvarsformxcvars[0] = 'c';
			cvarsformxcvars[1] = 'z';
			}

		if(type == 5)
			{
			counterconstantnumber = 1;
			constantformxconstant[0] = "1";
			}

		if(type == 6)
			{
			counterparamsnumber = 4;
			paramsformxparams[0] = "p1";
			paramsformxparams[1] = "p2";
			paramsformxparams[2] = "p3";
			paramsformxparams[3] = "p4";
			}
		}

	if(name.compare("TZ") == 0)
		{
		expressions = 5;
		cz = 50;
		cvam = 50;
		clin = 25;
		cfm = 0;
		cnum = 25;
		integer = false;
		nozero = false;
		ccvar = 25;
		ccon = 0;
		nummax = 5;
		cparen = 25;
		
		if(type == 1)
			{	
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 11;
			hfuncformxhfunc[0] = "sin(";
			hfuncformxhfunc[1] = "sinh(";
			hfuncformxhfunc[2] = "asin(";
			hfuncformxhfunc[3] = "real(";
			hfuncformxhfunc[4] = "cos(";
			hfuncformxhfunc[5] = "lost(";
			hfuncformxhfunc[6] = "acos(";
			hfuncformxhfunc[7] = "imag(";
			hfuncformxhfunc[8] = "tan(";
			hfuncformxhfunc[9] = "atan(";
			hfuncformxhfunc[10] = "log(";
			}

		if(type == 3)
			{
			counterufuncnumber = 1;
			ufuncformxufunc[0] = "(";
			}

		if(type == 4)
			{
			ccvar = 80;
			countercvarsnumber = 2;
			cvarsformxcvars[0] = 'c';
			cvarsformxcvars[1] = 'c';
			}

		if(type == 5)
			{
			counterconstantnumber = 1;
			constantformxconstant[0] = "1";
			}

		if(type == 6)
			{
			counterparamsnumber = 3;
			paramsformxparams[0] = "u";
			paramsformxparams[1] = "v";
			paramsformxparams[2] = "w";
			}
		}

	if(name.compare("DDR") == 0)
		{
		expressions = 3;
		cz = 50;
		cvam = 50;
		clin = 50;
		cfm = 50;
		cnum = 25;
		ccvar = 50;
		ccon = 50;
		integer = true;
		nozero = false;
		nummax = 5;
		cparen = 40;
		
		if(type == 1)
			{	
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 30;
			hfuncformxhfunc[0] = "sin(";
			hfuncformxhfunc[1] = "sinh(";
			hfuncformxhfunc[2] = "asin(";
			hfuncformxhfunc[3] = "asinh(";
			hfuncformxhfunc[4] = "cos(";
			hfuncformxhfunc[5] = "cosh(";
			hfuncformxhfunc[6] = "acos(";
			hfuncformxhfunc[7] = "acosh(";
			hfuncformxhfunc[8] = "tan(";
			hfuncformxhfunc[9] = "tanh(";
			hfuncformxhfunc[10] = "atan(";
			hfuncformxhfunc[11] = "atanh(";
			hfuncformxhfunc[12] = "cotan(";
			hfuncformxhfunc[13] = "cotanh(";
			hfuncformxhfunc[14] = "sqr(";
			hfuncformxhfunc[15] = "sqrt(";
			hfuncformxhfunc[16] = "log(";
			hfuncformxhfunc[17] = "exp(";
			hfuncformxhfunc[18] = "abs(";
			hfuncformxhfunc[19] = "cabs(";
			hfuncformxhfunc[20] = "conj(";
			hfuncformxhfunc[21] = "flip(";
			hfuncformxhfunc[22] = "ident(";
			hfuncformxhfunc[23] = "zero(";
			hfuncformxhfunc[24] = "recip(";
			hfuncformxhfunc[25] = "ceil(";
			hfuncformxhfunc[26] = "floor(";
			hfuncformxhfunc[27] = "trunc(";
			hfuncformxhfunc[28] = "round(";
			hfuncformxhfunc[29] = "atan2(";
			}

		if(type == 3)
			{
			counterufuncnumber = 3;
			ufuncformxufunc[0] = "fn1 (";
			ufuncformxufunc[1] = "fn2 (";
			ufuncformxufunc[2] = "fn3 (";
			}

		if(type == 4)
			{
			countercvarsnumber = 3;
			cvarsformxcvars[0] = "EPS";
			cvarsformxcvars[1] = "PI";
			cvarsformxcvars[2] = "angle";
			}

		if(type == 5)
			{
			counterconstantnumber = 33;
			constantformxconstant[0] = "(x+y)";
			constantformxconstant[1] = "(x-y)";
			constantformxconstant[2] = "(y-x)";
			constantformxconstant[3] = "(x*y)";
			constantformxconstant[4] = "(x/y)";
			constantformxconstant[5] = "(y/x)";
			constantformxconstant[6] = "(x^y)";
			constantformxconstant[7] = "(y^x)";
			constantformxconstant[8] = "(z+c)";
			constantformxconstant[9] = "(z-c)";
			constantformxconstant[10] = "(c-z)";
			constantformxconstant[11] = "(z*c)";
			constantformxconstant[12] = "(z/c)";
			constantformxconstant[13] = "(c/z)";
			constantformxconstant[14] = "(z^c)";
			constantformxconstant[15] = "(c^z)";
			constantformxconstant[16] = "(z+g)";
			constantformxconstant[17] = "(z-g)";
			constantformxconstant[18] = "(g-z)";
			constantformxconstant[19] = "(z*g)";
			constantformxconstant[20] = "(z/g)";
			constantformxconstant[21] = "(g/z)";
			constantformxconstant[22] = "(z^g)";
			constantformxconstant[23] = "(g^z)";
			constantformxconstant[24] = "(c+g)";
			constantformxconstant[25] = "(c-g)";
			constantformxconstant[26] = "(g-c)";
			constantformxconstant[27] = "(c*g)";
			constantformxconstant[28] = "(c/g)";
			constantformxconstant[29] = "(g/c)";
			constantformxconstant[30] = "(c^g)";
			constantformxconstant[31] = "(g^c)";
			}

		if(type == 6)
			{
			counterparamsnumber = 7;
			paramsformxparams[0] = "p1";
			paramsformxparams[1] = "p2";
			paramsformxparams[2] = "p3";
			paramsformxparams[3] = "x";
			paramsformxparams[4] = "y";
			paramsformxparams[5] = "g";
			paramsformxparams[6] = "c";
			}
		}

	if(name.compare("AMG") == 0)
		{
		expressions = 6;
		cz = 50;
		cvam = 25;
		clin = 45;
		cfm = 0;
		cnum = 25;
		integer = false;
		nozero = false;
		ccvar = 50;
		ccon = 25;
		nummax = 1;
		cparen = 60;
		
		if(type == 1)
			{
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 30;
			hfuncformxhfunc[0] = "cos(";
			hfuncformxhfunc[1] = "sin(";
			hfuncformxhfunc[2] = "sinh (";
			hfuncformxhfunc[3] = "cosh(";
			hfuncformxhfunc[4] = "tan(";
			hfuncformxhfunc[5] = "cotan(";
			hfuncformxhfunc[6] = "arctan(";
			hfuncformxhfunc[7] = "arc(";
			hfuncformxhfunc[8] = "exp(";
			hfuncformxhfunc[9] = "ln(";
			hfuncformxhfunc[10] = "log10(";
			hfuncformxhfunc[11] = "log2(";
			hfuncformxhfunc[12] = "logn(";
			hfuncformxhfunc[13] = "sqrt(";
			hfuncformxhfunc[14] = "sqr(";
			hfuncformxhfunc[15] = "pwer(";
			hfuncformxhfunc[16] = "intpower(";
			hfuncformxhfunc[17] = "min(";
			hfuncformxhfunc[18] = "max(";
			hfuncformxhfunc[19] = "abs(";
			hfuncformxhfunc[20] = "trunc(";
			hfuncformxhfunc[21] = "int(";
			hfuncformxhfunc[22] = "ceil(";
			hfuncformxhfunc[23] = "floor(";
			hfuncformxhfunc[24] = "heav(";
			hfuncformxhfunc[25] = "sign(";
			hfuncformxhfunc[26] = "zero(";
			hfuncformxhfunc[27] = "ph(";
			hfuncformxhfunc[28] = "rnd(";
			hfuncformxhfunc[29] = "random(";
			}

		if(type == 3)
			{
			counterufuncnumber = 1;
			ufuncformxufunc[0] = "( ";
			}

		if(type == 4)
			{
			countercvarsnumber = 3;
			cvarsformxcvars[0] = 'x';
			cvarsformxcvars[1] = 'y';
			cvarsformxcvars[2] = 'z';
			}

		if(type == 5)
			{
			counterconstantnumber = 1;
			constantformxconstant[0] = "PI";
			}
			
		if(type == 6)
			{
			counterparamsnumber = 5;
			paramsformxparams[0] = "a";
			paramsformxparams[1] = "b";
			paramsformxparams[2] = "c";
			paramsformxparams[3] = "d";
			paramsformxparams[4] = "e";
			}
		}

	if(name.compare("JCD") == 0)
		{
		expressions = 7;
		cz = 20;
		cvam = 20;
		clin = 20;
		cfm = 50;
		cnum = 10;
		integer = true;
		nozero = true;
		ccvar = 10;
		ccon = 10;
		nummax = 3;
		cparen = 60;

		if(type == 1)
			{			
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '^';
			}

		if(type == 2)
			{
			counterhfuncnumber = 1;
			hfuncformxhfunc[0] = "(";
			}

		if(type == 3)
			{
			counterufuncnumber = 2;
			ufuncformxufunc[0] = "fn1( ";
			ufuncformxufunc[1] = "fn2( ";
			}

		if(type == 4)
			{
			countercvarsnumber = 1;
			cvarsformxcvars[0] = "pixel";
			}

		if(type == 5)
			{
			counterconstantnumber = 2;
			constantformxconstant[0] = "(1/z)";
			constantformxconstant[1] = "(1/pixel)";
			}
			
		if(type == 6)
			{
			counterparamsnumber = 2;
			paramsformxparams[0] = "p1";
			paramsformxparams[1] = "p2";
			}
		}

	if(name.compare("AVS") == 0)
		{
		expressions = 5;
		cz = 30;
		cvam = 50;
		clin = 30;
		cfm = 50;
		cnum = 30;
		integer = false;
		nozero = false;
		ccvar = 50;
		ccon = 25;
		nummax = 1;
		cparen = 60;

		if(type == 1)
			{
			counteropernumber = 5;
			operformxoper[0] = '+';
			operformxoper[1] = '-';
			operformxoper[2] = '*';
			operformxoper[3] = '/';
			operformxoper[4] = '*';
			}

		if(type == 2)
			{
			counterhfuncnumber = 19;
			hfuncformxhfunc[0] = "abs(";
			hfuncformxhfunc[1] = "sin(";
			hfuncformxhfunc[2] = "cos(";
			hfuncformxhfunc[3] = "tan(";
			hfuncformxhfunc[4] = "asin(";
			hfuncformxhfunc[5] = "acos(";
			hfuncformxhfunc[6] = "atan(";
			hfuncformxhfunc[7] = "sqr(";
			hfuncformxhfunc[8] = "sqrt(";

#if 0
			hfuncformxhfunc[9] = "invsqrt(";
#else
			hfuncformxhfunc[9] = "sqr(";
#endif
			hfuncformxhfunc[10] = "exp(";
			hfuncformxhfunc[11] = "log(";
			hfuncformxhfunc[12] = "log10(";
			hfuncformxhfunc[13] = "floor(";
			hfuncformxhfunc[14] = "ceil(";

#if 0
			hfuncformxhfunc[15] = "sign(";
#else
			hfuncformxhfunc[15] = "rand(";
#endif

			hfuncformxhfunc[16] = "rand(";

#if 0
			hfuncformxhfunc[17] = "bnot(";
#else
			hfuncformxhfunc[17] = "rand(";
#endif

			hfuncformxhfunc[18] = "floor(";
			}

		if(type == 3)
			{
			counterufuncnumber = 7;
			ufuncformxufunc[0] = "atan2( v, ";
			ufuncformxufunc[1] = "pow( v, ";
			ufuncformxufunc[2] = "eqmin( v, ";
			ufuncformxufunc[3] = "eqmax( v, ";

#if 0
			ufuncformxufunc[4] = "sigmoid( v, ";
			ufuncformxufunc[5] = "band( v, ";
			ufuncformxufunc[6] = "bor( v, ";
#else
			ufuncformxufunc[4] = "atan2( v, ";
			ufuncformxufunc[5] = "pow( v, ";
			ufuncformxufunc[6] = "eqmin( v, ";
#endif
			}

		if(type == 4)
			{
			countercvarsnumber = 7;
			cvarsformxcvars[0] = 'i';
			cvarsformxcvars[1] = 'v';
			cvarsformxcvars[2] = 'x';

#if 0
			cvarsformxcvars[3] = 'y';
#else
			cvarsformxcvars[3] = 'b';
#endif

			cvarsformxcvars[4] = 'b';

#if 0
			cvarsformxcvars[5] = 'w';
			cvarsformxcvars[6] = 'h';
#else
			cvarsformxcvars[5] = 'v';
			cvarsformxcvars[6] = 'x';
#endif
			}

		if(type == 5)
			{
			counterconstantnumber = 3;
			constantformxconstant[0] = "PI";
			constantformxconstant[1] = "EPS";
			constantformxconstant[2] = "PHI";
			}

		if(type == 6)
			{
			counterparamsnumber = 10;
			paramsformxparams[0] = "i";
			paramsformxparams[1] = "v";
			paramsformxparams[2] = "x";

#if 0
			paramsformxparams[3] = "y";
#else
			paramsformxparams[3] = "b";
#endif

			paramsformxparams[4] = "b";

#if 0
			paramsformxparams[5] = "w";
			paramsformxparams[6] = "h";
#else
			paramsformxparams[5] = 'v';
			paramsformxparams[6] = 'x';
#endif

			paramsformxparams[7] = "i";
			paramsformxparams[8] = "i";
			paramsformxparams[9] = "i";
			}
		}
}

float UNequationbuilder::acMathRandom(void)
{
	return (float)rand() / 32767;
}

float UNequationbuilder::acAudioRandom(void)
{
	SDL_mutexP(m_mutex_Rand);
	int i_RandSize = m_Rand.size();
	SDL_mutexV(m_mutex_Rand);

	while(i_RandSize <= 0)
		{
		SDL_mutexP(m_mutex_Rand);
		i_RandSize = m_Rand.size();
		SDL_mutexV(m_mutex_Rand);

		SDL_mutexP(m_mutex_Clear);
		if(m_Clear)
			{
			printf("\n");
			m_Clear = false;
			SDL_mutexP(m_mutex_Activity);
			m_Mode = EQBUILD_MODE_IDLE;
			SDL_mutexV(m_mutex_Activity);
			SDL_mutexP(m_mutex_State);
			m_BuildStatus = EQBUILD_MODE_IDLE;
			SDL_mutexV(m_mutex_State);
			}
		SDL_mutexV(m_mutex_Clear);
		}

	printf(".");

	SDL_mutexP(m_mutex_Rand);
	float i_Result = m_Rand[0];

	if(m_Rand.size() > 1)
		{
		for(unsigned int i_Count = 1; i_Count < m_Rand.size(); i_Count++)
			{
			m_Rand[i_Count - 1] = m_Rand[i_Count];
			}
		}

	int i_Size = m_Rand.size();
	m_Rand.resize(i_Size - 1);
	SDL_mutexV(m_mutex_Rand);

	return i_Result;
}

void UNequationbuilder::acBuild(void)
{
	if(!m_Ready)
		{
		acQuickInit("CLR", 1);
		acQuickInit("CLR", 2);
		acQuickInit("CLR", 3);
		acQuickInit("CLR", 4);
		acQuickInit("CLR", 5);
		acQuickInit("CLR", 6);
		acQuickInit(m_name, 1);
		acQuickInit(m_name, 2);
		acQuickInit(m_name, 3);
		acQuickInit(m_name, 4);
		acQuickInit(m_name, 5);
		acQuickInit(m_name, 6);
		}

	m_Equation.vec_Argument.clear();
	equation.clear();

	int numoperators = counteropernumber;
	int numhardfuncs = counterhfuncnumber;
	int numuserfuncs = counterufuncnumber;
	int numchgvars = countercvarsnumber;
	int numconst = counterconstantnumber;
	int numuserparams = counterparamsnumber;

	int num = 0;
	int vam = 0;
	int lin = 0;
	int lix = 0;
	int opr = 0;
	int con = 0;
	int sym = 0;
	int wim = 0;
	int itr = 0;
	int oprflag = 0;
	int nofequations = 0;
	int needp = 0;

	//***********************operators array
	char* operators = new char[numoperators];
	for(int i = 0; i < numoperators; i++)
		{
		operators[i] = operformxoper[i];
		}

	//***********************hard-coded functions array
	string* link = new string[numhardfuncs];
	for(int i = 0; i < numhardfuncs; i++)
		{
		link[i] = hfuncformxhfunc[i];
		}

	//***********************user-definable functions array
	string* linx = new string[numuserfuncs];
	for(int i = 0; i < numuserfuncs; i++)
		{
		linx[i] = ufuncformxufunc[i];
		}

	//***********************changing variables
	string* symb = new string[numchgvars];
	for(int i = 0; i < numchgvars; i++)
		{
		symb[i] = cvarsformxcvars[i];
		}

	//***********************Constants
	string* cons = new string[numconst];
	for(int i = 0; i < numconst; i++)
		{
		cons[i] = constantformxconstant[i];
		}

	//***********************user definable parameters array
	string* vars = new string[numuserparams];
	for(int i = 0; i < numuserparams; i++)
		{
		vars[i] = paramsformxparams[i];
		}

	string mainvar = m_mainvar + " ";

	//***********************For each Equation We Want...
	for(int nofequations = 0; nofequations < numofequations; nofequations++)
		{
		//***********************Start the equation
		if(showz)
			{
			equation = equation + mainvar + "= ";
			m_Argument.m_Type = EQBUILD_MAINVAR;
			m_Argument.m_String = m_mainvar;
			m_Equation.vec_Argument.push_back(m_Argument);
			m_Argument.m_Type = EQBUILD_EQUALS;
			m_Argument.m_String = " = ";
			m_Equation.vec_Argument.push_back(m_Argument);
			}

		oprflag = 1;

		//***********************add a left parenthesis?
		if((acMathRandom()*100) < (cparen))
			{
			equation = equation + "(";
			m_Argument.m_Type = EQBUILD_LPAREN;
			m_Argument.m_String = "(";
			m_Equation.vec_Argument.push_back(m_Argument);
			needp++;
			}


		//***********************begin the genrating process
		while (itr < expressions)
			{
			//***********************add a main variable?
			if(floor(acMathRandom() * 101) < cz)
				{
				equation = equation + mainvar;
				m_Argument.m_Type = EQBUILD_MAINVAR;
				m_Argument.m_String = m_mainvar;
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 0;
				}

			//***********************add an operator if there was a main variable
			if(oprflag == 0)
				{
				opr = floor(acMathRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;
				}

			//***********************add a user-definable parameter?
			if(floor(acMathRandom() * 101) < cvam)
				{
				vam = floor(acMathRandom() * numuserparams);
				equation = equation + (vars[vam]) + " ";
				m_Argument.m_Type = EQBUILD_USERDEFINEDPARAM;
				m_Argument.m_String = vars[vam];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 0;

				//***********************add a right parentheses?	(more chance if there are more right parentheses)	
				if(((acMathRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation = equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}
			
				//***********************add an operator if there was a user-definable parameter
				if(oprflag == 0)
					{
					opr = floor(acMathRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a changing variable?
				if(floor(acMathRandom() * 101) < ccvar)
					{
					sym = floor(acMathRandom() * numchgvars);
					equation = equation + (symb[sym]) + " ";
					m_Argument.m_Type = EQBUILD_VARIABLE;
					m_Argument.m_String = symb[sym];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 0;
					}

				//***********************add a right parentheses?	(more chance if there are more left parentheses)	
				if(((acMathRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation =  equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}

				//***********************add an operator if there was a Changing Variable
				if(oprflag == 0)
					{
					opr = floor(acMathRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a Constant?
				if(floor(acMathRandom() * 101) < ccon)
					{
					con = floor(acMathRandom() * numconst);
					equation = equation + (cons[con]) + " ";
					m_Argument.m_Type = EQBUILD_CONSTANTS;
					m_Argument.m_String = cons[con];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 0;
					}

				//***********************add a right parentheses?	(more chance if there are more left parentheses)	
				if(((acMathRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation = equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}
			
				//***********************add an operator if there was a Constant
				if(oprflag == 0)
					{
					opr = floor(acMathRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a left parentheses?
				if((acMathRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}
				}

			//***********************add a function?
			if(floor(acMathRandom() * 101) < clin)
				{
				//***********************add a left parenthesis?	
				if((acMathRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}

				//***********************will the function be hard-coded, or user definable?	
				if(floor(acMathRandom() * 100) <= cfm)
					{
					lix = floor(acMathRandom() * numuserfuncs);
					equation = equation + (linx[lix]) + " ";
					m_Argument.m_Type = EQBUILD_USERDEFINEDFUNC;
					m_Argument.m_String = linx[lix];
					m_Equation.vec_Argument.push_back(m_Argument);
					}
				else
					{
					lin = floor(acMathRandom()*numhardfuncs);
					equation =  equation + (link[lin]) + " ";
					m_Argument.m_Type = EQBUILD_HARDFUNC;
					m_Argument.m_String = link[lin];
					m_Equation.vec_Argument.push_back(m_Argument);
					}

				if(oprflag == 1)
					{
					oprflag == 0;
					}

				needp++;
				}

			//***********************add an operator if needed
			if (oprflag == 0)
				{
				opr = floor(acMathRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;
				}

			//***********************add a numerical value?
			if(floor(acMathRandom() * 101) < cnum)
				{
				if(integer == 1)
					{
					if(nozero == 1)
						{
						num = floor(acMathRandom() * (nummax));
						while((integer==1) && (num==0))
							{
							num = floor(acMathRandom() * (nummax));
							}
						}
					else
						{
						num = floor(acMathRandom() * (nummax));
						}
					}
				else
					{
					if(nozero==1)
						{
						num = (acMathRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = (acMathRandom() * (nummax));
							}
						}
					else
						{
						num = (acMathRandom() * (nummax));
						}
					}

				char numbuf1[100];
				itoa(num, numbuf1, 10);

				equation = equation + numbuf1 + " ";
				m_Argument.m_Type = EQBUILD_NUMERICLE;
				m_Argument.m_Float = num;
				m_Equation.vec_Argument.push_back(m_Argument);

				//*********************** add an operator (it needs one)
				opr = floor(acMathRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;

				//*********************** add a left parenthesis?	
				if((acMathRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}		
				}

			//***********************DONE WITH THIS PASS
			itr++;
			}

		//***********************Add one more thing so last thing isn't an operator
		wim = floor(acMathRandom() * 5);

		switch (wim)
			{
			case 0:
				{
				//*********************** User-Definable Parameter
				vam = floor(acMathRandom() * numuserparams);
				equation = equation + (vars[vam]) + " ";
				m_Argument.m_Type = EQBUILD_USERDEFINEDPARAM;
				m_Argument.m_String = vars[vam];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 1:
				{
				//*********************** Numerical Value 
				if(integer == 1)
					{
					if(nozero == 1)
						{
						num = floor(acMathRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = floor(acMathRandom()*(nummax));
							}
						}
					else
						{
						num = floor(acMathRandom() * (nummax));
						}
					}
				else
					{
					if(nozero == 1)
						{
						num = (acMathRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = (acMathRandom() * (nummax));
							}
						}
					else
						{
						num = (acMathRandom() * (nummax));
						}
					}

				char numbuf2[100];
				itoa(num, numbuf2, 10);

				equation = equation + numbuf2 + " ";
				m_Argument.m_Type = EQBUILD_NUMERICLE;
				m_Argument.m_Float = num;
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			//*********************** Main Variable
			case 2:
				{
				equation = equation + mainvar;
				m_Argument.m_Type = EQBUILD_MAINVAR;
				m_Argument.m_String = m_mainvar;
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 3:
				{
				//*********************** Changing Variable
				sym = floor(acMathRandom() * numchgvars);
				equation =  equation + (symb[sym]) + " ";
				m_Argument.m_Type = EQBUILD_VARIABLE;
				m_Argument.m_String = symb[sym];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 4:
				{
				//*********************** Constant
				con = floor(acMathRandom() * numconst);
				equation = equation + (cons[con]) + " ";
				m_Argument.m_Type = EQBUILD_CONSTANTS;
				m_Argument.m_String = cons[con];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;
			}

		//*********************** clean up the left parentheses (good thing I counted, isn't it ;) )	
		while (needp != 0)
			{
			equation = equation + ")";
			m_Argument.m_Type = EQBUILD_RPAREN;
			m_Argument.m_String = ")";
			m_Equation.vec_Argument.push_back(m_Argument);
			needp--;
			}

		equation = equation + "\n";
		m_Argument.m_Type = EQBUILD_END;
		m_Equation.vec_Argument.push_back(m_Argument);
		itr = 0;
		}

	/// Save Equation ///
	fprintf(m_file, "%s", equation.c_str());

	flushall();

	m_Equation.m_String = equation;
	m_Bank.vec_Equation.push_back(m_Equation);

	m_Ready = false;
}

void UNequationbuilder::acBuildAudio(void)
{
	if(!m_Ready)
		{
		acQuickInit("CLR", 1);
		acQuickInit("CLR", 2);
		acQuickInit("CLR", 3);
		acQuickInit("CLR", 4);
		acQuickInit("CLR", 5);
		acQuickInit("CLR", 6);
		acQuickInit(m_name, 1);
		acQuickInit(m_name, 2);
		acQuickInit(m_name, 3);
		acQuickInit(m_name, 4);
		acQuickInit(m_name, 5);
		acQuickInit(m_name, 6);
		}

	m_Equation.vec_Argument.clear();
	equation.clear();

	int numoperators = counteropernumber;
	int numhardfuncs = counterhfuncnumber;
	int numuserfuncs = counterufuncnumber;
	int numchgvars = countercvarsnumber;
	int numconst = counterconstantnumber;
	int numuserparams = counterparamsnumber;

	int num = 0;
	int vam = 0;
	int lin = 0;
	int lix = 0;
	int opr = 0;
	int con = 0;
	int sym = 0;
	int wim = 0;
	int itr = 0;
	int oprflag = 0;
	int nofequations = 0;
	int needp = 0;

	//***********************operators array
	char* operators = new char[numoperators];
	for(int i = 0; i < numoperators; i++)
		{
		operators[i] = operformxoper[i];
		}

	//***********************hard-coded functions array
	string* link = new string[numhardfuncs];
	for(int i = 0; i < numhardfuncs; i++)
		{
		link[i] = hfuncformxhfunc[i];
		}

	//***********************user-definable functions array
	string* linx = new string[numuserfuncs];
	for(int i = 0; i < numuserfuncs; i++)
		{
		linx[i] = ufuncformxufunc[i];
		}

	//***********************changing variables
	string* symb = new string[numchgvars];
	for(int i = 0; i < numchgvars; i++)
		{
		symb[i] = cvarsformxcvars[i];
		}

	//***********************Constants
	string* cons = new string[numconst];
	for(int i = 0; i < numconst; i++)
		{
		cons[i] = constantformxconstant[i];
		}

	//***********************user definable parameters array
	string* vars = new string[numuserparams];
	for(int i = 0; i < numuserparams; i++)
		{
		vars[i] = paramsformxparams[i];
		}

	string mainvar = m_mainvar + " ";

	//***********************For each Equation We Want...
	for(int nofequations = 0; nofequations < numofequations; nofequations++)
		{
		//***********************Start the equation
		if(showz)
			{
			equation = equation + mainvar + " = ";
			m_Argument.m_Type = EQBUILD_MAINVAR;
			m_Argument.m_String = m_mainvar;
			m_Equation.vec_Argument.push_back(m_Argument);
			m_Argument.m_Type = EQBUILD_EQUALS;
			m_Argument.m_String = " = ";
			m_Equation.vec_Argument.push_back(m_Argument);
			}

		oprflag = 1;

		//***********************add a left parenthesis?
		if((acAudioRandom()*100) < (cparen))
			{
			equation = equation + "(";
			m_Argument.m_Type = EQBUILD_LPAREN;
			m_Argument.m_String = "(";
			m_Equation.vec_Argument.push_back(m_Argument);
			needp++;
			}


		//***********************begin the genrating process
		while (itr < expressions)
			{
			//***********************add a main variable?
			if(floor(acAudioRandom() * 101) < cz)
				{
				equation = equation + mainvar;
				m_Argument.m_Type = EQBUILD_MAINVAR;
				m_Argument.m_String = m_mainvar;
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 0;
				}

			//***********************add an operator if there was a main variable
			if(oprflag == 0)
				{
				opr = floor(acAudioRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;
				}

			//***********************add a user-definable parameter?
			if(floor(acAudioRandom() * 101) < cvam)
				{
				vam = floor(acAudioRandom() * numuserparams);
				equation = equation + (vars[vam]) + " ";
				m_Argument.m_Type = EQBUILD_USERDEFINEDPARAM;
				m_Argument.m_String = vars[vam];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 0;

				//***********************add a right parentheses?	(more chance if there are more right parentheses)	
				if(((acAudioRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation = equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}
			
				//***********************add an operator if there was a user-definable parameter
				if(oprflag == 0)
					{
					opr = floor(acAudioRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a changing variable?
				if(floor(acAudioRandom() * 101) < ccvar)
					{
					sym = floor(acAudioRandom() * numchgvars);
					equation = equation + (symb[sym]) + " ";
					m_Argument.m_Type = EQBUILD_VARIABLE;
					m_Argument.m_String = symb[sym];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 0;
					}

				//***********************add a right parentheses?	(more chance if there are more left parentheses)	
				if(((acAudioRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation =  equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}

				//***********************add an operator if there was a Changing Variable
				if(oprflag == 0)
					{
					opr = floor(acAudioRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a Constant?
				if(floor(acAudioRandom() * 101) < ccon)
					{
					con = floor(acAudioRandom() * numconst);
					equation = equation + (cons[con]) + " ";
					m_Argument.m_Type = EQBUILD_CONSTANTS;
					m_Argument.m_String = cons[con];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 0;
					}

				//***********************add a right parentheses?	(more chance if there are more left parentheses)	
				if(((acAudioRandom() * 100) < (cparen * needp)) && (oprflag == 0))
					{
					equation = equation + ")";
					m_Argument.m_Type = EQBUILD_RPAREN;
					m_Argument.m_String = ")";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp--;
					}
			
				//***********************add an operator if there was a Constant
				if(oprflag == 0)
					{
					opr = floor(acAudioRandom() * numoperators);
					equation = equation + (operators[opr]) + " ";
					m_Argument.m_Type = EQBUILD_OPERATOR;
					m_Argument.m_String = operators[opr];
					m_Argument.m_Char = operators[opr];
					m_Equation.vec_Argument.push_back(m_Argument);
					oprflag = 1;
					}

				//***********************add a left parentheses?
				if((acAudioRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}
				}

			//***********************add a function?
			if(floor(acAudioRandom() * 101) < clin)
				{
				//***********************add a left parenthesis?	
				if((acAudioRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}

				//***********************will the function be hard-coded, or user definable?	
				if(floor(acAudioRandom() * 100) <= cfm)
					{
					lix = floor(acAudioRandom() * numuserfuncs);
					equation = equation + (linx[lix]) + " ";
					m_Argument.m_Type = EQBUILD_USERDEFINEDFUNC;
					m_Argument.m_String = linx[lix];
					m_Equation.vec_Argument.push_back(m_Argument);
					}
				else
					{
					lin = floor(acAudioRandom()*numhardfuncs);
					equation =  equation + (link[lin]) + " ";
					m_Argument.m_Type = EQBUILD_HARDFUNC;
					m_Argument.m_String = link[lin];
					m_Equation.vec_Argument.push_back(m_Argument);
					}

				if(oprflag == 1)
					{
					oprflag == 0;
					}

				needp++;
				}

			//***********************add an operator if needed
			if (oprflag == 0)
				{
				opr = floor(acAudioRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;
				}

			//***********************add a numerical value?
			if(floor(acAudioRandom() * 101) < cnum)
				{
				if(integer == 1)
					{
					if(nozero == 1)
						{
						num = floor(acAudioRandom() * (nummax));
						while((integer==1) && (num==0))
							{
							num = floor(acAudioRandom() * (nummax));
							}
						}
					else
						{
						num = floor(acAudioRandom() * (nummax));
						}
					}
				else
					{
					if(nozero==1)
						{
						num = (acAudioRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = (acAudioRandom() * (nummax));
							}
						}
					else
						{
						num = (acAudioRandom() * (nummax));
						}
					}

				char numbuf1[100];
				itoa(num, numbuf1, 10);

				equation = equation + numbuf1 + " ";
				m_Argument.m_Type = EQBUILD_NUMERICLE;
				m_Argument.m_Float = num;
				m_Equation.vec_Argument.push_back(m_Argument);

				//*********************** add an operator (it needs one)
				opr = floor(acAudioRandom() * numoperators);
				equation = equation + (operators[opr]) + " ";
				m_Argument.m_Type = EQBUILD_OPERATOR;
				m_Argument.m_String = operators[opr];
				m_Argument.m_Char = operators[opr];
				m_Equation.vec_Argument.push_back(m_Argument);
				oprflag = 1;

				//*********************** add a left parenthesis?	
				if((acAudioRandom() * 100) < (cparen))
					{
					equation = equation + "(";
					m_Argument.m_Type = EQBUILD_LPAREN;
					m_Argument.m_String = "(";
					m_Equation.vec_Argument.push_back(m_Argument);
					needp++;
					oprflag = 1;
					}		
				}

			//***********************DONE WITH THIS PASS
			itr++;
			}

		//***********************Add one more thing so last thing isn't an operator
		wim = floor(acAudioRandom() * 5);

		switch (wim)
			{
			case 0:
				{
				//*********************** User-Definable Parameter
				vam = floor(acAudioRandom() * numuserparams);
				equation = equation + (vars[vam]) + " ";
				m_Argument.m_Type = EQBUILD_USERDEFINEDPARAM;
				m_Argument.m_String = vars[vam];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 1:
				{
				//*********************** Numerical Value 
				if(integer == 1)
					{
					if(nozero == 1)
						{
						num = floor(acAudioRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = floor(acAudioRandom()*(nummax));
							}
						}
					else
						{
						num = floor(acAudioRandom() * (nummax));
						}
					}
				else
					{
					if(nozero == 1)
						{
						num = (acAudioRandom() * (nummax));
						while((integer == 1) && (num == 0))
							{
							num = (acAudioRandom() * (nummax));
							}
						}
					else
						{
						num = (acAudioRandom() * (nummax));
						}
					}

				char numbuf2[100];
				itoa(num, numbuf2, 10);

				equation = equation + numbuf2 + " ";
				m_Argument.m_Type = EQBUILD_NUMERICLE;
				m_Argument.m_Float = num;
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			//*********************** Main Variable
			case 2:
				{
				equation = equation + mainvar;
				m_Argument.m_Type = EQBUILD_MAINVAR;
				m_Argument.m_String = m_mainvar;
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 3:
				{
				//*********************** Changing Variable
				sym = floor(acAudioRandom() * numchgvars);
				equation =  equation + (symb[sym]) + " ";
				m_Argument.m_Type = EQBUILD_VARIABLE;
				m_Argument.m_String = symb[sym];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;

			case 4:
				{
				//*********************** Constant
				con = floor(acAudioRandom() * numconst);
				equation = equation + (cons[con]) + " ";
				m_Argument.m_Type = EQBUILD_CONSTANTS;
				m_Argument.m_String = cons[con];
				m_Equation.vec_Argument.push_back(m_Argument);
				}break;
			}

		//*********************** clean up the left parentheses (good thing I counted, isn't it ;) )	
		while (needp != 0)
			{
			equation = equation + ")";
			m_Argument.m_Type = EQBUILD_RPAREN;
			m_Argument.m_String = ")";
			m_Equation.vec_Argument.push_back(m_Argument);
			needp--;
			}

		equation = equation + "\n";
		m_Argument.m_Type = EQBUILD_END;
		m_Equation.vec_Argument.push_back(m_Argument);
		itr = 0;
		}

	/// Save Equation ///
	fprintf(m_file, "%s", equation.c_str());

	flushall();

	m_Equation.m_String = equation;
	m_Bank.vec_Equation.push_back(m_Equation);

	m_Ready = false;
}

void UNequationbuilder::acPrintEQ(void)
{
	if(equation.length() <= 0) printf("ERROR:::EQ:::Equation empty...\n\n");
	else printf("\n%s\n\n", equation.c_str());

	SDL_mutexP(m_mutex_Beep);
	m_Beep = true;
	SDL_mutexV(m_mutex_Beep);
}

};

	//v = i + (log10( 0.5348647391593368 - (v * ceil( 0.2804812422734719 % (rand( 0.7732578789421318 + x )* (sigmoid( v,  0.3147164648520678 % (y )+ v )% ((sqr( 0.9910145962022891 / ($PHI ))))))))));
	//v  = v + sqr( v / h )% (h )+ y + (0.7828483455881916 % ($PHI ))