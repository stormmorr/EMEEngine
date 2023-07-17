/*

    Osirus Main - Main Entry Point
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <memory>

//#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include "SDL.h"

#include "../UnSRC/QServerFramewrk.h"
#include "../UnSRC/Process/unMessageCore.h"
#include "Q-PortSHELL-Sound.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"

#include "OsirusCore.h"

#include "../UnSRC/Utility/unConsole.h"
#include "../UnSRC/Base/UNcompiler.h"
#include "Q-NET-ProtoMap.h"
#include "../../Server/UNSGlobalHeader.h"

#include "../Speech/SpeechDlg.h"
#include "../Server/resource.h"

#include "OSIKnowledgeBase.h"

#include "../../../Server/MasterOSI.h"
#include "al.h"

#include "Shellapi.h"

#include "../Process/UNequationbuilder.h"
#include "../Process/UNequationbay.h"

QAGE::QActiveFramewrk* QActiveFrameWork;
UN::unMessageCore* unProcessor;
OSI::OsirusCore* i_OsirusCore;
CSpeechDlg* i_CSpeechDlg;
UNequationbuilder i_UNequationbuilder;
UNequationbay *i_EQbay;

LARGE_INTEGER* m_LargeIntCurrent;
LARGE_INTEGER* m_LargeIntNew;
unsigned int m_Counter;
bool vecDpress[15];

HWND hWndMain;
SDL_Surface *screen;
bool m_ScCapture = true;
bool m_ScCapturing = true;
float *m_ScBuffer;

extern bool TX_One;

#define IDX_VI_SWIT 0
#define IDX_VI_EDIT 1
#define IDX_VI_OK 2
#define IDX_VI_CLEAR 3

#define IDX_SAPI_SWIT 4
#define IDX_SAPI_EDIT 5
#define IDX_SAPI_OK 6
#define IDX_SAPI_CLEAR 7

#define IDX_OSI_SWIT 8
#define IDX_OSI_EDIT 9
#define IDX_OSI_OK 10
#define IDX_OSI_CLEAR 11

#if 1
#define QPA_CAPTURE_ON 1
#endif

bool VI_Swit = false;
bool SAPI_Swit = false;
bool OSI_Swit = false;
bool TX_Swit = true;
bool m_StoreSwit = false;
bool m_FullScreenSwit = false;

HWND hwndVIswit;
HWND hwndVIedit;
HWND hwndVIok;
HWND hwndVIclear;
HWND hwndSAPIswit;
HWND hwndSAPIedit;
HWND hwndSAPIok;
HWND hwndSAPIclear;
HWND hwndOSIswit;
HWND hwndOSIedit;
HWND hwndOSIok;
HWND hwndOSIclear;

int m_CapModeCnt = 0;

#if 0
Master i_master;
#endif

int m_paStoreStart = 0;
int m_paStoreStartRes = 0;
int m_paStoreEquatePtr = 0;

int m_Block = 0;
int m_SkipFactor = 10;
int m_JumpFactor = 1;
float m_skiptrail = 0.3;
float m_jumptrail = 0.3;

//#define RESULTS_WINDOW_WIDTH 1075	//1090
//#define RESULTS_WINDOW_HEIGHT 700	//822

#define RESULTS_WINDOW_WIDTH 1366	//1090
#define RESULTS_WINDOW_HEIGHT 768	//822

unsigned int *tempbuf;

#define PUTPIXEL(x,y,c) ((unsigned int*)screen->pixels)[(x) + (y) * (screen->pitch / 4)] = (c);

const unsigned char sprite[] =
{
0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0
};

void drawsprite(int x, int y, unsigned int color)
{
	int i, j, c, yofs;
	yofs = y * (screen->pitch / 4) + x;
	for (i = 0, c = 0; i < 16; i++)
		{
		for (j = 0; j < 16; j++, c++)
			{
			if (sprite[c])
				{
				//10207230
				//11196408
				//12184293
				//13039561
				//13893285
				//14614142
				//698716
				//363651
				//159402
				//86477
				//79848
				//270841
				//528638
				//919032

				((unsigned int*)screen->pixels)[yofs + j] = color;
				//((unsigned int*)screen->pixels)[yofs + j] = 698716;
				}
			}
		yofs += (screen->pitch / 4);
		}

	printf("trace color %i\n", color);
}

#define PITCH (screen->pitch / 4)

unsigned int blend_avg(unsigned int source, unsigned int target)
{
    unsigned int sourcer = (source >>  0) & 0xff;
    unsigned int sourceg = (source >>  8) & 0xff;
    unsigned int sourceb = (source >> 16) & 0xff;
    unsigned int targetr = (target >>  0) & 0xff;
    unsigned int targetg = (target >>  8) & 0xff;
    unsigned int targetb = (target >> 16) & 0xff;

    targetr = (sourcer + targetr) / 2;
    targetg = (sourceg + targetg) / 2;
    targetb = (sourceb + targetb) / 2;

    return (targetr <<  0) |
           (targetg <<  8) |
           (targetb << 16);
}

unsigned int blend_mul(unsigned int source, unsigned int target)
{
    unsigned int sourcer = (source >>  0) & 0xff;
    unsigned int sourceg = (source >>  8) & 0xff;
    unsigned int sourceb = (source >> 16) & 0xff;
    unsigned int targetr = (target >>  0) & 0xff;
    unsigned int targetg = (target >>  8) & 0xff;
    unsigned int targetb = (target >> 16) & 0xff;

    targetr = (sourcer * targetr) >> 8;
    targetg = (sourceg * targetg) >> 8;
    targetb = (sourceb * targetb) >> 8;

    return (targetr <<  0) |
           (targetg <<  8) |
           (targetb << 16);
}

unsigned int blend_add(unsigned int source, unsigned int target)
{
    unsigned int sourcer = (source >>  0) & 0xff;
    unsigned int sourceg = (source >>  8) & 0xff;
    unsigned int sourceb = (source >> 16) & 0xff;
    unsigned int targetr = (target >>  0) & 0xff;
    unsigned int targetg = (target >>  8) & 0xff;
    unsigned int targetb = (target >> 16) & 0xff;

    targetr += sourcer;
    targetg += sourceg;
    targetb += sourceb;

    if (targetr > 0xff) targetr = 0xff;
    if (targetg > 0xff) targetg = 0xff;
    if (targetb > 0xff) targetb = 0xff;

    return (targetr <<  0) |
           (targetg <<  8) |
           (targetb << 16);
}

void drawsprite_add(int x, int y, unsigned int color)
{
    int i, j, c, yofs;
    yofs = y * (screen->pitch / 4) + x;
    for (i = 0, c = 0; i < 16; i++)
		{
        for (j = 0; j < 16; j++, c++)
			{
            if (sprite[c])
				{
                ((unsigned int*)screen->pixels)[yofs + j] =
                    blend_add(((unsigned int*)screen->pixels)[yofs + j], color);
				}
			}
        yofs += (screen->pitch / 4);
		}
}

void drawsprite_mul(int x, int y, unsigned int color)
{
    int i, j, c, yofs;
    yofs = y * (screen->pitch / 4) + x;
    for (i = 0, c = 0; i < 16; i++)
		{
        for (j = 0; j < 16; j++, c++)
			{
            if (sprite[c])
				{
                ((unsigned int*)screen->pixels)[yofs + j] =
                    blend_mul(((unsigned int*)screen->pixels)[yofs + j], color);
				}
			}
        yofs += (screen->pitch / 4);
		}
}

void scaleblit(void)
{
    int i, j, yofs;
    yofs = 0;
    for (i = 0; i < RESULTS_WINDOW_HEIGHT; i++)
		{
        for (j = 0; j < RESULTS_WINDOW_WIDTH; j++)
			{
            int c = (int)((i * 0.95f) + 12) * PITCH +
                    (int)((j * 0.95f) + 16);
            ((unsigned int*)screen->pixels)[yofs + j] =
                blend_avg(((unsigned int*)screen->pixels)[yofs + j], tempbuf[c]);
			}
		yofs += PITCH;
		}
}

void render(void)
{
    // Lock surface if needed
    if(SDL_MUSTLOCK(screen))
		{
        if(SDL_LockSurface(screen) < 0) return;
		}

    // Ask SDL for the time in milliseconds
    int tick = SDL_GetTicks();

    int i, d;
    for(i = 0; i < 128; i++)
		{
        d = tick + i * 4;
        drawsprite((int)((RESULTS_WINDOW_WIDTH / 2) + cos(d * 0.0034f) * cos(d * 0.0134f) * 150),
                   (int)((RESULTS_WINDOW_HEIGHT / 2) + cos(d * 0.0033f) * cos(d * 0.0234f) * 110),
                   ((int)(cos((tick * 0.2 + i) * 0.234897f) * 127 + 128) << 8) |
                   ((int)(cos((tick * 0.2 + i) * 0.123489f) * 127 + 128) <<  16) |
                   ((int)(cos((tick * 0.2 + i) * 0.312348f) * 127 + 128) <<  0));
		}

    for(i = 0; i < RESULTS_WINDOW_HEIGHT; i++)
        memcpy(tempbuf + i * RESULTS_WINDOW_WIDTH,
               ((unsigned long*)screen->pixels) +
               i * PITCH, RESULTS_WINDOW_WIDTH * 4);

    scaleblit();

    // Unlock if needed
    if (SDL_MUSTLOCK(screen))
        SDL_UnlockSurface(screen);

    // Tell SDL to update the whole screen
    SDL_UpdateRect(screen, 0, 0, RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT);
}

void clearscreen(void)
{
	for(unsigned int i_Count = 0; i_Count < RESULTS_WINDOW_WIDTH*RESULTS_WINDOW_HEIGHT; i_Count++)
		{
		((unsigned int*)screen->pixels)[i_Count] = 0;
		}
}

void renderQpaResults(void)
{
    // Lock surface if needed
    if(SDL_MUSTLOCK(screen))
		{
        if(SDL_LockSurface(screen) < 0) return;
		}

	int i_Height = 0;
	int i_Width = 0;
	int i_Point = 0;

	for(unsigned int i_Count = m_paStoreStart; i_Count < unProcessor->vec_paStore.m_ResVec.size(); i_Count++)
		{
		for(unsigned int i_CountRes = m_paStoreStartRes; i_CountRes < unProcessor->vec_paStore.m_ResVec[i_Count]->m_Results.size(); i_CountRes++)
			{
			///// Frequency /////
			i_Height = (int)(((unProcessor->vec_paStore.m_ResVec[i_Count]->m_Results[i_CountRes]->m_bestpeak_freq) / 11150) * (RESULTS_WINDOW_HEIGHT / 2));
			i_Height += (RESULTS_WINDOW_HEIGHT / 2);

			if(i_Height > RESULTS_WINDOW_HEIGHT) i_Height = RESULTS_WINDOW_HEIGHT;
			if(i_Height < (RESULTS_WINDOW_HEIGHT / 2)) i_Height = (RESULTS_WINDOW_HEIGHT / 2);

			while(i_Height > (RESULTS_WINDOW_HEIGHT / 2))
				{
				i_Point = (RESULTS_WINDOW_HEIGHT - i_Height) * (screen->pitch / 4) + i_Width;
				((unsigned int*)screen->pixels)[i_Point] = 698716;
				i_Height--;
				}

			///// Amplitude /////
			i_Height = (int)(((unProcessor->vec_paStore.m_ResVec[i_Count]->m_Results[i_CountRes]->m_amplitude) / 9000000) * (RESULTS_WINDOW_HEIGHT / 2));
			i_Height += (RESULTS_WINDOW_HEIGHT / 2);

			if(i_Height > RESULTS_WINDOW_HEIGHT) i_Height = RESULTS_WINDOW_HEIGHT;
			if(i_Height < (RESULTS_WINDOW_HEIGHT / 2)) i_Height = (RESULTS_WINDOW_HEIGHT / 2);

			while(i_Height > (RESULTS_WINDOW_HEIGHT / 2))
				{
				i_Point = ((RESULTS_WINDOW_HEIGHT - i_Height) + (RESULTS_WINDOW_HEIGHT / 2)) * (screen->pitch / 4) + i_Width;
				((unsigned int*)screen->pixels)[i_Point] = 698716;
				i_Height--;
				}

			i_Width++;
			if(i_Width > (RESULTS_WINDOW_WIDTH))
				{
				i_Count = unProcessor->vec_paStore.m_ResVec.size();
				i_CountRes = QPO_CAPTURE_STORE;
				}
			}
		}

	// Unlock if needed
	if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT);
}

bool renderEQ(void)
{
	bool i_Rendered = false;

    // Lock surface if needed
    if(SDL_MUSTLOCK(screen))
		{
        if(SDL_LockSurface(screen) < 0) return false;
		}

	int i_Point = 0;

	float i_Colr;
	//float i_Z = ((float)rand() / 32767) * 100;
	float i_Z;
	float i_Z2;
	int i_alter = 0;
	float i_altertrail = 0.3;
	int i_alter2 = 0;
	float i_altertrail1 = 0.3;
	float i_altertrail2 = 0.3;
	int i_slide = 0;
	float i_slidetrail = 0.3;

	m_Block--;
	if(m_Block < 0) m_Block = 0;

	if(m_Block == 0)
		{
		i_Rendered = true;
		clearscreen();

		m_Block = m_SkipFactor * 25;

		float i_r3 = ((float)rand() / 32767);

		if(i_r3 <= 0.5) m_skiptrail += 0.2;
		if(i_r3 > 0.5) m_skiptrail -= 0.2;

		if(m_skiptrail < 0) m_skiptrail = 0;
		if(m_skiptrail > 1) m_skiptrail = 1;

		if(m_skiptrail <= 0.5) m_SkipFactor--;
		if(m_skiptrail > 0.5) m_SkipFactor++;

		if(m_SkipFactor < 1) m_SkipFactor = 1;
		if(m_SkipFactor > 10) m_SkipFactor = 10;

		float i_r2 = ((float)rand() / 32767);

		if(i_r2 <= 0.5) m_jumptrail += 0.2;
		if(i_r2 > 0.5) m_jumptrail -= 0.2;

		if(m_jumptrail < 0) m_jumptrail = 0;
		if(m_jumptrail > 1) m_jumptrail = 1;

		if(m_jumptrail <= 0.5) m_JumpFactor--;
		if(m_jumptrail > 0.5) m_JumpFactor++;

		if(m_JumpFactor < 1) m_JumpFactor = 1;
		if(m_JumpFactor > 10) m_JumpFactor = 10;

		for(int i_Y = 0; i_Y < RESULTS_WINDOW_HEIGHT; i_Y += m_SkipFactor)
			{
			for(int i_X = 0; i_X < RESULTS_WINDOW_WIDTH; i_X += m_SkipFactor)
				{
				i_Z = i_EQbay->acRandFRPW0();
				i_EQbay->acRandFRPWN0();

				float i_r5 = i_EQbay->acRandFRPW2();
				i_EQbay->acRandFRPWN2();

				if(i_r5 <= 0.7) i_altertrail += 0.2;
				if(i_r5 > 0.5) i_altertrail -= 0.2;

				if(i_altertrail < 0) i_altertrail = 0;
				if(i_altertrail > 3) i_altertrail = 1;

				if(i_altertrail > 0 && i_altertrail < 1) i_alter = 0;
				if(i_altertrail > 1 && i_altertrail < 2) i_alter = 1;
				if(i_altertrail > 2 && i_altertrail < 3) i_alter = 2;

				i_Colr = i_EQbay->acRun(i_alter, i_X, i_Y, i_Z);

				i_EQbay->acRandF1();
				i_EQbay->acRandFRN1();
				i_EQbay->acRandFRPN1();

				if(i_Colr < 0) i_Colr *= -1;

				//int tick = SDL_GetTicks();
				int tick = 1;

				i_Colr = ((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.234897f) * 127 + 128) << 8) |
				((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.123489f) * 127 + 128) <<  16) |
				((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.312348f) * 127 + 128) <<  0);

				for(int i_Yr = 0; i_Yr < m_SkipFactor; i_Yr += m_JumpFactor)
					{
					for(int i_Xr = 0; i_Xr < m_SkipFactor; i_Xr += m_JumpFactor)
						{
						i_Point = (i_Y + i_Yr) * (screen->pitch / 4) + (i_X + i_Xr);

						if(i_Point < RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT)
							{
							((unsigned int*)screen->pixels)[i_Point] = i_Colr;
							}
						}
					}
				}

			i_EQbay->acRandFN0();

			float i_r4 = ((float)rand() / 32767);

			if(i_r4 <= 0.7) i_slidetrail += 0.2;
			if(i_r4 > 0.5) i_slidetrail -= 0.2;

			if(i_slidetrail < 0) i_slidetrail = 0;
			if(i_slidetrail > 1) i_slidetrail = 1;

			if(i_slidetrail <= 0.5) i_slide = 0;
			if(i_slidetrail > 0.5) i_slide = 1;

			if(i_slide == 1)
				{
				i_EQbay->acRandF1();
				i_EQbay->acRandF2();
				i_EQbay->acRandF3();
				i_EQbay->acRandF4();
				i_EQbay->acRandFR1();
				i_EQbay->acRandFR2();
				i_EQbay->acRandFR3();
				i_EQbay->acRandFR4();
				i_EQbay->acRandFRP1();
				i_EQbay->acRandFRP2();
				i_EQbay->acRandFRP3();
				i_EQbay->acRandFRP4();
				}
			}

		for(int i_X = 0; i_X < RESULTS_WINDOW_WIDTH; i_X += m_SkipFactor)
			{
			for(int i_Y = 0; i_Y < RESULTS_WINDOW_HEIGHT; i_Y += m_SkipFactor)
				{
				i_Z2 = i_EQbay->acRandFRPW1();
				i_EQbay->acRandFRPWN1();

				float i_r5 = i_EQbay->acRandFRPW3();
				i_EQbay->acRandFRPWN3();

				if(i_r5 <= 0.7) i_altertrail1 += 0.2;
				if(i_r5 > 0.5) i_altertrail1 -= 0.2;

				if(i_altertrail1 < 0) i_altertrail1 = 0;
				if(i_altertrail1 > 3) i_altertrail1 = 1;

				if(i_altertrail1 > 0 && i_altertrail1 < 1) i_alter2 = 0;
				if(i_altertrail1 > 1 && i_altertrail1 < 2) i_alter2 = 1;
				if(i_altertrail1 > 2 && i_altertrail1 < 3) i_alter2 = 2;

				i_Colr = i_EQbay->acRun(i_alter2, i_X, i_Y, i_Z);

				i_EQbay->acRandF1();
				i_EQbay->acRandFRN1();
				i_EQbay->acRandFRPN1();

				if(i_Colr < 0) i_Colr *= -1;

				//int tick = SDL_GetTicks();
				int tick = 1;

				i_Colr = ((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.234897f) * 127 + 128) << 8) |
				((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.123489f) * 127 + 128) <<  16) |
				((int)(cos((tick * 0.2 + (i_Colr / 50000)) * 0.312348f) * 127 + 128) <<  0);

#if 0
				float i_r7 = ((float)rand() / 32767);

				if(i_r7 <= 0.03) i_altertrail += 0.2;
				if(i_r7 > 0.03) i_altertrail -= 0.2;

				if(i_altertrail < 0) i_altertrail = 0;
				if(i_altertrail > 2) i_altertrail = 1;

				if(i_altertrail <= 0.5) ((unsigned int*)screen->pixels)[i_Point] += i_Colr;
				if(i_altertrail > 0.5) ((unsigned int*)screen->pixels)[i_Point] /= i_Colr;
#endif

#if 1
				float i_r7 = ((float)rand() / 32767);

				if(i_r7 <= 0.5) i_altertrail2 += 0.2;
				if(i_r7 > 0.5) i_altertrail2 -= 0.2;

				if(i_altertrail2 < 0) i_altertrail2 = 0;
				if(i_altertrail2 > 4) i_altertrail2 = 1;

				for(int i_Yr = 0; i_Yr < m_SkipFactor; i_Yr += m_JumpFactor)
					{
					for(int i_Xr = 0; i_Xr < m_SkipFactor; i_Xr += m_JumpFactor)
						{
						i_Point = (i_Y + i_Yr) * (screen->pitch / 4) + (i_X + i_Xr);

						if(i_Point < RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT)
							{
							if(i_altertrail2 > 0 && i_altertrail2 <= 1) ((unsigned int*)screen->pixels)[i_Point] += i_Colr;
							if(i_altertrail2 > 1 && i_altertrail2 <= 2) ((unsigned int*)screen->pixels)[i_Point] -= i_Colr;
							if(i_altertrail2 > 2 && i_altertrail2 <= 3) ((unsigned int*)screen->pixels)[i_Point] *= i_Colr;
							if(i_altertrail2 > 3 && i_altertrail2 <= 4) ((unsigned int*)screen->pixels)[i_Point] /= i_Colr;
							}
						}
					}
#endif
				}

			i_EQbay->acRandF0();
			i_EQbay->acRandF1();
			i_EQbay->acRandF2();
			i_EQbay->acRandF3();
			i_EQbay->acRandF4();
			i_EQbay->acRandFR0();
			i_EQbay->acRandFR1();
			i_EQbay->acRandFR2();
			i_EQbay->acRandFR3();
			i_EQbay->acRandFR4();
			i_EQbay->acRandFRP0();
			i_EQbay->acRandFRP1();
			i_EQbay->acRandFRP2();
			i_EQbay->acRandFRP3();
			i_EQbay->acRandFRP4();
			}
		}

	// Unlock if needed
	if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

	// Tell SDL to update the whole screen
	SDL_UpdateRect(screen, 0, 0, RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT);

	return i_Rendered;
}

// initialization
static void acInit(void)
{
	unConsoleAttribute(CONSOLE_MSG);
	Q.CoreAcquire();

	playerAV.Acquire("playerAV");

	m_LargeIntCurrent = new LARGE_INTEGER;
	m_LargeIntNew = new LARGE_INTEGER;

	m_Counter = 0;

	///// Active Framework /////
	QNetwork.Initialize();

	QAGE::QActiveFramewrk::acActiveInit();

	/// Seed the random number generator
	srand ( time(NULL) );

	i_CSpeechDlg = new CSpeechDlg();
	i_CSpeechDlg->acInit();

	i_OsirusCore = new OSI::OsirusCore();

	unProcessor = new UN::unMessageCore("default", true);

	i_EQbay = new UN::UNequationbay();

	i_UNequationbuilder.Start();

#if 0
	SDL_mutexP(i_UNequationbuilder.m_mutex_Activity);
	i_UNequationbuilder.m_Mode = EQBUILD_MODE_INITIALIZE;
	i_UNequationbuilder.m_Remote.m_Name = "AVS";
	i_UNequationbuilder.m_Remote.m_Type = 1;
	SDL_mutexV(i_UNequationbuilder.m_mutex_Activity);
#endif
}

// cleanup
static void clean()
{
    std::cout << "Finished Execution" << std::endl;
}

#pragma comment(lib, "SDLmain.lib")

HINSTANCE hInstance;

LRESULT CALLBACK WinFunc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
		{
		case WM_KEYDOWN:
		key = (char)wParam;

        switch (key)
			{
			//##### Keylogger for Left To Forward Jink
			case 'Q':
				{
				exit(1);
				} break;
			}

		case WM_KEYUP:
		key = (char)wParam;

        switch (key)
			{
			//##### Keylogger for Left To Forward Jink - Stage Three
			//case 'A':
			} break;

	    case WM_CREATE:
			{
			hWndMain=hWnd;
			} break;

		case WM_LBUTTONDOWN:
			{
			} break;

		case WM_RBUTTONDOWN:
			{
			_->rbutton=1;
			} break;

		case WM_MBUTTONDOWN:
			{
			_->mbutton=1;
			} break;

		case 0x020A:	//### Mouse Wheel Scroll
			{
			_->mwheelroll=1;
			} break;

		case WM_SIZE:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_PAINT:
			{
			} break;

		case WM_MOUSEMOVE:
			{
#if 0
			i_CSpeechDlg->acSpeak("Q_PORTShell speak");
#endif

#if 0
			unProcessor->acSoundEffect();
#endif
			} break;

		case WM_CSPEECHEVENT:
			{
#if 1
			//unProcessor->acResponseEffect();

#if 0
			printf("Event\n");
			i_CSpeechDlg->acSpeechEvent();
			i_CSpeechDlg->acSetEvent();
			i_OsirusCore->acCreateTag(i_CSpeechDlg->acSpeechEvent());
			i_OsirusCore->acSave();
			i_OsirusCore->acProcessSpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
			i_CSpeechDlg->acSpeechEvent();
#endif

#if 0
			i_OsirusCore->acProcessAPISpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
#endif

#if 1
			char *i_SpeechEvent = i_CSpeechDlg->acSpeechEvent();

			if(SAPI_Swit) SendMessage(hwndSAPIedit, WM_SETTEXT, 0, (LPARAM)i_SpeechEvent);

#if 0
			const char *i_Response = unProcessor->acResponse(i_SpeechEvent);
#endif

			if(VI_Swit)
				{
				std::string i_Response = unProcessor->acResponseStrRex(i_SpeechEvent);

				if(OSI_Swit) SendMessage(hwndOSIedit, WM_SETTEXT, 0, (LPARAM)i_Response.c_str());

				printf("trace response: %s\n", i_Response.c_str());

				TX_One = true;

				/*if(TX_Swit)
					{
					i_OsirusCore->m_UsbFrame->m_SetAllDigital();
					TX_One = true;
					}*/

				if(i_Response.compare("RANDOM PICKUP LINE") != 0) i_CSpeechDlg->acSpeak(i_Response);
				else unProcessor->acResponseEffectError();
				}
#endif
#endif
			} break;

#if 0
		case WM_USER:
			{
			SPEVENT eventItem;
			memset(&eventItem, 0, sizeof(SPEVENT));
			while(i_CSpeechDlg->m_pVoice->GetEvents(1, &eventItem, NULL) == S_OK)
				{
				switch(eventItem.eEventId)
					{
#if 0
					case SPEI_WORD_BOUNDARY:	//SPEI_SENTENCE_BOUNDARY:
							SPVOICESTATUS eventStatus;
							i_CSpeechDlg->m_pVoice->GetStatus(&eventStatus, NULL);
							if(eventStatus.dwRunningState == 1) i_CSpeechDlg->acVoice();
							break;
#endif

					default:
						break;
					}
				}
			}
#endif
			case WM_ACTIVATEAPP:
				{
				if((int)wParam != 0)
					{
					ApplicationFocus = 1;
					}
				else
					{
					ApplicationFocus = 0;
					}
				}break;

			case WM_COMMAND:
				{
				switch(HIWORD(wParam))
					{
					case BN_CLICKED:
						{
						switch(LOWORD(wParam))
							{
							case IDX_VI_SWIT:
								{
								if(!VI_Swit)	// Turn ON
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"loading...");
									SendMessage((HWND)lParam, BM_SETCHECK, 1, NULL);
									EnableWindow((HWND)lParam, false);
									EnableWindow(hwndVIedit, false);

#if 1
									unProcessor->acStartProcessorContained("default", "default", "default");
#endif

									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"VI Presence");
									EnableWindow((HWND)lParam, true);
									EnableWindow(hwndVIedit, true);

									VI_Swit = true;
									}
								else			// Turn OFF
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"VI Suspended");
									SendMessage((HWND)lParam, BM_SETCHECK, 0, NULL);
									unProcessor->acPauseProcessor();
									EnableWindow(hwndVIedit, false);

									VI_Swit = false;
									}
								}break;

							case IDX_SAPI_SWIT:
								{
								if(!SAPI_Swit)	// Turn ON
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"SAPI Results");
									SendMessage((HWND)lParam, BM_SETCHECK, 1, NULL);
									EnableWindow(hwndSAPIedit, true);

									SAPI_Swit = true;
									}
								else			// Turn OFF
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"SAPI Results Suspended");
									SendMessage((HWND)lParam, BM_SETCHECK, 0, NULL);
									EnableWindow(hwndSAPIedit, false);

									SAPI_Swit = false;
									}
								}break;

							case IDX_OSI_SWIT:
								{
								if(!OSI_Swit)	// Turn ON
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"OSI Results");
									SendMessage((HWND)lParam, BM_SETCHECK, 1, NULL);
									EnableWindow(hwndOSIedit, true);

									OSI_Swit = true;
									}
								else			// Turn OFF
									{
									SendMessage((HWND)lParam, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"OSI Results Suspended");
									SendMessage((HWND)lParam, BM_SETCHECK, 0, NULL);
									EnableWindow(hwndOSIedit, false);

									OSI_Swit = false;
									}
								}break;

							case IDX_VI_OK:
								{
								if(VI_Swit)
									{
									char i_EditText[1000];
									SendMessage((HWND)hwndVIedit, WM_GETTEXT, 200, (LPARAM)(LPCSTR)i_EditText);

									std::string i_StringText = i_EditText;

									if(i_StringText.length() > 0)
										{
										unProcessor->acResponseEffect();

										i_CSpeechDlg->acSpeak(i_StringText);

										TX_One = true;

										/*if(TX_Swit)
											{
											i_OsirusCore->m_UsbFrame->m_SetAllDigital();
											TX_One = true;
											}*/
										}

									SendMessage((HWND)hwndVIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;

							case IDX_VI_CLEAR:
								{
								if(VI_Swit)
									{
									SendMessage((HWND)hwndVIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;

							case IDX_SAPI_OK:
								{
								if(SAPI_Swit)
									{
									char i_EditText[1000];
									SendMessage((HWND)hwndSAPIedit, WM_GETTEXT, 200, (LPARAM)(LPCSTR)i_EditText);

									std::string i_StringText = i_EditText;

									if(i_StringText.length() > 0)
										{
#if 0
										unProcessor->acResponseEffect();
#endif

										i_CSpeechDlg->acSpeak(i_StringText);

										TX_One = true;

#if 0
										if(TX_Swit)
											{
											i_OsirusCore->m_UsbFrame->m_SetAllDigital();
											TX_One = true;
											}
#endif
										}

									SendMessage((HWND)hwndSAPIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;

							case IDX_SAPI_CLEAR:
								{
								if(VI_Swit)
									{
									SendMessage((HWND)hwndSAPIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;

							case IDX_OSI_OK:
								{
								if(OSI_Swit)
									{
									char i_EditText[1000];
									SendMessage((HWND)hwndOSIedit, WM_GETTEXT, 200, (LPARAM)(LPCSTR)i_EditText);

									std::string i_StringText = i_EditText;

									if(i_StringText.length() > 0)
										{
#if 0
										unProcessor->acResponseEffect();
#endif

										i_CSpeechDlg->acSpeak(i_StringText);

										TX_One = true;

#if 0
										if(TX_Swit)
											{
											i_OsirusCore->m_UsbFrame->m_SetAllDigital();
											TX_One = true;
											}
#endif
										}

									SendMessage((HWND)hwndOSIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;

							case IDX_OSI_CLEAR:
								{
								if(VI_Swit)
									{
									SendMessage((HWND)hwndOSIedit, WM_SETTEXT, 255, (LPARAM)(LPCSTR)"");
									}
								} break;
							}
						}break;
					}
				} break;
		}

	return DefWindowProc (hWnd, msg, wParam, lParam);
}

static HWND CreateDialogWindow(HINSTANCE hInstance, char *AppName, int Width, int Height)
{
		HWND					TempHWND;
        WNDCLASS                tempWinClass;
        RECT                    WindowRect;
        //
        // Set up and register application window class
        //
        tempWinClass.style         = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
        tempWinClass.lpfnWndProc   = WinFunc;
        tempWinClass.cbClsExtra    = 0;
        tempWinClass.cbWndExtra    = 0;
        tempWinClass.hInstance     = hInstance;
        tempWinClass.hIcon         = LoadIcon( hInstance, "IDI_ICON1");
        tempWinClass.hCursor       = LoadCursor(NULL, IDC_UPARROW);
        tempWinClass.hbrBackground = 0;//GetStockObject(DKGRAY_BRUSH);
        tempWinClass.lpszMenuName  = (const char*)NULL;
        tempWinClass.lpszClassName = AppName;
        RegisterClass(&tempWinClass);
        //
        // Create application's main window
        //
        TempHWND = CreateWindowEx(
                0,
                AppName,
                AppName,
                0,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                NULL,
                NULL,
                hInstance,
                NULL);

        if (!TempHWND)
			{
            MessageBox(0, "Could not create window.", "** ERROR **", MB_OK);
            _exit(1);
			}

        UpdateWindow(TempHWND);
        SetFocus(TempHWND);

        SetWindowLong(TempHWND, 
                 GWL_STYLE, 
                 GetWindowLong(TempHWND, GWL_STYLE) & ~WS_POPUP);
        SetWindowLong(TempHWND, 
                 GWL_STYLE, 
                 GetWindowLong(TempHWND, GWL_STYLE) | (WS_MAXIMIZE  | 
                                                   WS_CAPTION     | 
                                                   WS_SYSMENU     | 
                                                   WS_MINIMIZEBOX));
        SetWindowLong(TempHWND, 
                  GWL_STYLE, 
                  GetWindowLong(TempHWND, GWL_STYLE) | WS_THICKFRAME |
                                                     WS_MAXIMIZEBOX);
        SetWindowLong(TempHWND, 
                  GWL_EXSTYLE, 
                  GetWindowLong(TempHWND, GWL_EXSTYLE) | WS_EX_TOPMOST);

        //#####
        // Make window visible
        //#####
		//ShowWindow(TempHWND, SW_SHOWNORMAL);
		ShowWindow(TempHWND, SW_SHOWMAXIMIZED);
        return TempHWND;
}

// entry point
int main (int argc, char* argv[])
{
	printf("//            \\\\ -- memory allocation\n");
	printf("   OSI-Commander    \n");
	printf("\\\\            // \n");

	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wcl;
	MSG msg;

	hInstance=hInst;
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	const char *c = "OSICommander";

	tempbuf = new unsigned int[RESULTS_WINDOW_WIDTH*RESULTS_WINDOW_HEIGHT];

	vecDpress[0] = false;
	vecDpress[1] = false;
	vecDpress[2] = false;
	vecDpress[3] = false;
	vecDpress[4] = false;
	vecDpress[5] = false;

#if 1
	wcl.style			= CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc		= (WNDPROC)WinFunc;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hInstance		= hInst;
	wcl.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcl.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcl.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU);
	wcl.lpszClassName	= "OsirusCore";

	if (!RegisterClass (&wcl))
		{
		printf("ERROR:::main can't register Window\n");
		for(;;) {};
		}

	CreateWindowEx(	0,"OsirusCore",c,
					WS_OVERLAPPEDWINDOW,
					0,0,276,822,
					NULL,NULL,hInst,NULL);

	ShowWindow (hWndMain, SW_SHOWNORMAL);
#endif

#if 1
	hwndVIswit = CreateWindow(
		"BUTTON",
		"VI Suspended",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		10,
		10,
		115,
		20,
		hWndMain,
		(HMENU)IDX_VI_SWIT,
		(HINSTANCE)hInst,
		0);
#endif

#if 1
	hwndVIedit = CreateWindow(
		"EDIT",
		NULL,
		WS_BORDER | WS_VISIBLE | WS_CHILD /*| WS_VSCROLL*/ | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		5,
		30,
		250,
		220,
		hWndMain,
		(HMENU)IDX_VI_EDIT,
		(HINSTANCE)hInst,
		NULL);
	EnableWindow(hwndVIedit, false);
#if 0
	SendMessage(hwndVIedit, WM_SETTEXT, 0, (LPARAM)"Command");
#endif
#endif

#if 1
	hwndVIok = CreateWindow(
		"BUTTON",
		"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		226,
		251,
		28,
		28,
		hWndMain,
		(HMENU)IDX_VI_OK,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndVIclear = CreateWindow(
		"BUTTON",
		"CC",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		196,
		251,
		28,
		28,
		hWndMain,
		(HMENU)IDX_VI_CLEAR,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndSAPIswit = CreateWindow(
		"BUTTON",
		"SAPI Results Suspended",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		10,
		260,
		184,
		20,
		hWndMain,
		(HMENU)IDX_SAPI_SWIT,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndSAPIedit = CreateWindow(
		"EDIT",
		NULL,
		WS_BORDER | WS_VISIBLE | WS_CHILD /*| WS_VSCROLL*/ | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		5,
		280,
		250,
		220,
		hWndMain,
		(HMENU)IDX_SAPI_EDIT,
		(HINSTANCE)hInst,
		NULL);
	EnableWindow(hwndSAPIedit, false);
#endif

#if 1
	hwndSAPIok = CreateWindow(
		"BUTTON",
		"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		226,
		501,
		28,
		28,
		hWndMain,
		(HMENU)IDX_SAPI_OK,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndSAPIclear = CreateWindow(
		"BUTTON",
		"CC",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		196,
		501,
		28,
		28,
		hWndMain,
		(HMENU)IDX_SAPI_CLEAR,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndOSIswit = CreateWindow(
		"BUTTON",
		"OSI Results Suspended",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
		10,
		510,
		184,
		20,
		hWndMain,
		(HMENU)IDX_OSI_SWIT,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndOSIedit = CreateWindow(
		"EDIT",
		NULL,
		WS_BORDER | WS_VISIBLE | WS_CHILD /*| WS_VSCROLL*/ | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE,
		5,
		530,
		250,
		220,
		hWndMain,
		(HMENU)IDX_OSI_EDIT,
		(HINSTANCE)hInst,
		NULL);
	EnableWindow(hwndOSIedit, false);
#endif

#if 1
	hwndOSIok = CreateWindow(
		"BUTTON",
		"OK",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		226,
		751,
		28,
		28,
		hWndMain,
		(HMENU)IDX_OSI_OK,
		(HINSTANCE)hInst,
		NULL);
#endif

#if 1
	hwndOSIclear = CreateWindow(
		"BUTTON",
		"CC",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		196,
		751,
		28,
		28,
		hWndMain,
		(HMENU)IDX_OSI_CLEAR,
		(HINSTANCE)hInst,
		NULL);
#endif

	// Initialize SDL's subsystems
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
		}

    // Register SDL_Quit to be called at exit; makes sure things are
    // cleaned up when we quit.
    atexit(SDL_Quit);

    // Attempt to create a 32bit pixel window...
    screen = SDL_SetVideoMode(RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT, 32, SDL_HWSURFACE); // you can remove |SDL_FULLSCREEN for windowed mode

    // If we fail, return error.
    if(screen == NULL)
		{
        fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
        exit(1);
		}
    SDL_WM_SetCaption ("QPA Results Window", NULL);

	acInit();

#ifdef QPA_CAPTURE_ON
	unProcessor->acCaptureStart();
#endif

	while(1)
		{
#ifdef QPA_CAPTURE_ON
		if(m_ScCapturing)
			{
			m_ScCapture = unProcessor->acCaptureProgress();

			if(!m_ScCapture)
				{
				m_ScCapturing = false;
				m_ScBuffer = unProcessor->acCaptureGet();
				}
			}
		else
			{
			unProcessor->acCaptureAnalyse(m_ScBuffer);

			m_CapModeCnt++;
			if(m_CapModeCnt == QPO_CAPTURE_MAX)
				{
				unProcessor->acCapMode();
				unProcessor->acCapPatternMatch(QPO_CAPTURE_MAX);
				m_CapModeCnt = 0;
				}

#if 1
			m_ScCapture = true;
			m_ScCapturing = true;
#endif

			unProcessor->acCaptureStart();
			}
#endif

		int i_PointCount = 0;
		for(unsigned int i_ResVecCount = 0; i_ResVecCount < unProcessor->vec_paStore.m_ResVec.size(); i_ResVecCount++)
			{
			for(unsigned int i_ResCount = 0; i_ResCount < unProcessor->vec_paStore.m_ResVec[i_ResVecCount]->m_Results.size(); i_ResCount++)
				{
				if(m_paStoreEquatePtr < i_PointCount)
					{
					if(unProcessor->vec_paStore.m_ResVec[i_ResVecCount]->m_Results[i_ResCount]->m_amplitude > 5000000)
						{
						SDL_mutexP(i_UNequationbuilder.m_mutex_Rand);
						i_UNequationbuilder.m_Rand.push_back(unProcessor->vec_paStore.m_ResVec[i_ResVecCount]->m_Results[i_ResCount]->m_bestpeak_freq / 11150);
						SDL_mutexV(i_UNequationbuilder.m_mutex_Rand);
						}

					m_paStoreEquatePtr = i_PointCount;
					}
				i_PointCount++;
				}
			}

		if(m_StoreSwit)
			{
			SDL_mutexP(i_UNequationbuilder.m_mutex_State);
			int i_BuildStatus = i_UNequationbuilder.m_BuildStatus;
			SDL_mutexV(i_UNequationbuilder.m_mutex_State);

			if(i_BuildStatus == EQBUILD_MODE_IDLE)
				{
				SDL_mutexP(i_UNequationbuilder.m_mutex_Activity);
				i_UNequationbuilder.m_Mode = EQBUILD_MODE_INITIALIZE;
#if 0
				i_UNequationbuilder.m_Remote.m_Name = "AVS";
				i_UNequationbuilder.m_Remote.m_Type = 3;
#else
				i_UNequationbuilder.m_Remote.m_Name.clear();
				i_UNequationbuilder.m_Remote.m_Type = 2;
#endif
				SDL_mutexV(i_UNequationbuilder.m_mutex_Activity);
				}
			}

		SDL_mutexP(i_UNequationbuilder.m_mutex_Beep);
		if(i_UNequationbuilder.m_Beep)
			{
			i_UNequationbuilder.m_Beep = false;
			SDL_mutexV(i_UNequationbuilder.m_mutex_Beep);
			unProcessor->acResponseEffect();
			Sleep(400);
			}
		else SDL_mutexV(i_UNequationbuilder.m_mutex_Beep);

		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
			{
			if (GetMessage(&msg, NULL, 0, 0))
				{
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
					{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					}
				}

#if 0
			else return TRUE;
#endif
			}

#if 1
		i_CSpeechDlg->m_pVoice->GetStatus(&i_CSpeechDlg->m_VoiceStatus, NULL);
		if(i_CSpeechDlg->m_VoiceStatus.dwRunningState == 1)
			{
			if(!i_CSpeechDlg->acVoice())
				{
				/*if(TX_One)
					{
					i_OsirusCore->m_UsbFrame->m_ClearDigitalChannel(7);
					TX_One = false;
					}*/
				}
			}
#endif

		if(KEY_DOWN(QIN_DOWN))
			{
			if(!vecDpress[2])
				{
				vecDpress[2] = true;

				if(m_StoreSwit)
					{
					unProcessor->acResponseEffectError();
					m_StoreSwit = false;
					unProcessor->acCaptureStopStore();
					}
				else
					{
					unProcessor->acResponseEffectError();
					m_StoreSwit = true;
					unProcessor->acCaptureStore();
					Sleep(6500);
					}
				}
			}
		else vecDpress[2] = false;

		if(KEY_DOWN(QIN_f))
			{
			if(!vecDpress[5])
				{
				vecDpress[5] = true;

				if(m_FullScreenSwit)
					{
					m_FullScreenSwit = false;
					screen = SDL_SetVideoMode(RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT, 32, SDL_HWSURFACE); // you can remove |SDL_FULLSCREEN for windowed mode
					}
				else
					{
					m_FullScreenSwit = true;
					screen = SDL_SetVideoMode(RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT, 32, SDL_HWSURFACE|SDL_FULLSCREEN); // you can remove |SDL_FULLSCREEN for windowed mode
					}
				}
			}
		else vecDpress[5] = false;

		if(KEY_DOWN(QIN_UP))
			{
			if(!vecDpress[3] && !m_StoreSwit)
				{
				vecDpress[3] = true;

				SDL_mutexP(i_UNequationbuilder.m_mutex_State);
				int i_BuildStatus = i_UNequationbuilder.m_BuildStatus;
				SDL_mutexV(i_UNequationbuilder.m_mutex_State);

				if(i_BuildStatus == EQBUILD_MODE_IDLE)
					{
					SDL_mutexP(i_UNequationbuilder.m_mutex_Activity);
					i_UNequationbuilder.m_Mode = EQBUILD_MODE_INITIALIZE;
					i_UNequationbuilder.m_Remote.m_Name.clear();
					i_UNequationbuilder.m_Remote.m_Type = 0;
					SDL_mutexV(i_UNequationbuilder.m_mutex_Activity);
					}
				}
			}
		else vecDpress[3] = false;

		if(KEY_DOWN(QIN_LEFT))
			{
			if(!vecDpress[4])
				{
				vecDpress[4] = true;

				unProcessor->acCaptureClearStore();
				m_paStoreEquatePtr = 0;
				
				SDL_mutexP(i_UNequationbuilder.m_mutex_Clear);
				i_UNequationbuilder.m_Clear = true;
				SDL_mutexV(i_UNequationbuilder.m_mutex_Clear);
				}
			}
		else vecDpress[4] = false;

		if(KEY_DOWN(QIN_RIGHT))
			{
			if(!vecDpress[1])
				{
				vecDpress[1] = true;

				//i_CSpeechDlg->acProcessEvent("Create Command Level 17");
				//i_CSpeechDlg->acButtonMicroSetup();
				//i_CSpeechDlg->acSetEvent();

#if 1
				i_CSpeechDlg->acSpeak(unProcessor->acGenName(0));

				TX_One = true;

				/*if(TX_Swit)
					{
					i_OsirusCore->m_UsbFrame->m_SetAllDigital();
					TX_One = true;
					}*/
#endif

#if 0
				unProcessor->acSoundEffect();
#endif
				}
			}
		else vecDpress[1] = false;

#if 0
		QueryPerformanceCounter(m_LargeIntNew);

		if(m_Counter > 150000)
			{
			printf("Performance Counter %i\n", m_LargeIntNew->QuadPart - m_LargeIntCurrent->QuadPart);
			m_Counter = 0;
			}
		else m_Counter++;

		*m_LargeIntCurrent = *m_LargeIntNew;
#endif

		// Conditional Wait
#if 0
		Sleep(5000);
#endif

#if 0
		clearscreen();
		renderQpaResults();
#endif

#if 1
		renderEQ();
#endif
		}

    clean();
    return 0;
}