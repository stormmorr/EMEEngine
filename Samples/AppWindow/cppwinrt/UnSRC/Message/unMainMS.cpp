/*

    unMainBS - Main Entry Point
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

#include "../UnSRC/QServerFramewrk.h"
#include "../UnSRC/Process/unMessageCore.h"

#include "../UnSRC/Utility/Singleton.h"
#include "../UnSRC/Utility/datatypes.h"

#include "../Osirus/OsirusCore.h"

#include "../UnSRC/Utility/unConsole.h"
#include "../UnSRC/Base/UNcompiler.h"
#include "../../Server/UNSGlobalHeader.h"

#include "Q-NET-ProtoMap.h"

#include "../Speech/SpeechDlg.h"
#include "../Server/resource.h"

#if 0
QAGE::QActiveFramewrk *QActiveFrameWork;
#endif

UN::unMessageCore *unSlowDating;

#if 0
OSI::OsirusCore *i_OsirusCore;
CSpeechDlg *i_CSpeechDlg;
#endif

LARGE_INTEGER *m_LargeIntCurrent;
LARGE_INTEGER *m_LargeIntNew;
unsigned int m_Counter;
bool vecDpress[15];

HWND hWndMain;

// initialization
static void acInit(void)
{
	unConsoleAttribute(CONSOLE_MSG);
	Q.CoreAcquire();

	playerAV.Acquire("playerAV");

	m_LargeIntCurrent = new LARGE_INTEGER;
	m_LargeIntNew = new LARGE_INTEGER;
	m_Counter = 0;

#if 0
	///// Active Framework /////
	QNetwork.Initialize();

	QAGE::QActiveFramewrk::acActiveInit();
#endif

	/// Seed the random number generator
	srand ( time(NULL) );

#if 0 ///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	DigiMass = new Digi::DigiMassCore();
	DigiMass->acInit(DIGI_ERROR_PRINT);
#endif

#if 0
	i_CSpeechDlg = new CSpeechDlg();
	i_CSpeechDlg->acInit();
#endif

#if 0
	i_OsirusCore = new OSI::OsirusCore();
#endif

	unSlowDating = new UN::unMessageCore();
}

void acStartBrainNode(std::string i_Name, int i_CDataID)
{
	std::string i_ParamSignal = "/name ";
	std::string i_ParamFull = i_ParamSignal + i_Name;
	std::string i_NullString = "";

	LPCSTR i_Parameters = i_Name.c_str();

	ShellExecute(hWndMain, "open", "unBrainNode.exe", i_Parameters, "", SW_SHOW);

	unSlowDating->m_BStorage->CDataID[unSlowDating->m_BStorage->NomBrains] = i_CDataID;

	unSlowDating->m_BrainExistance[unSlowDating->m_BStorage->NomBrains].Acquire((char*)i_Name.c_str());

#if 0
	for(int i_iter = 0; i_iter < i_Name.length(); i_iter++)
		{
		unSlowDating->m_BrainExistance[unSlowDating->m_BStorage->NomBrains]->m_Name[i_iter] = i_Name[i_iter];
		}

	unSlowDating->m_BrainExistance[i_aviter]->m_State = 0;
#endif

	unSlowDating->m_NomBrainExistance++;
	unSlowDating->m_BStorage->NomBrains++;
}

void acScan(void)
{
	for(int i_aviter = 0; i_aviter < unSlowDating->m_NomExistance; i_aviter++)
		{
#if 1
		printf("unTrace aviter %i state %i %s %s\n", i_aviter, unSlowDating->m_Existance[i_aviter]->m_State, unSlowDating->m_Existance[i_aviter]->m_Name, unSlowDating->m_Existance[i_aviter]->m_Message);
#endif
		if(unSlowDating->m_Existance[i_aviter]->m_State == 1)
			{
#if 1
			if(unSlowDating->m_Existance[i_aviter]->m_BDataID >= unSlowDating->m_NomBrainExistance)
				{
				printf("ERROR::: m_Existance out of bounds\n");
				for(;;) {}
				}
#endif

			for(int i_iter = 0; i_iter < unSlowDating->m_Existance[i_aviter]->m_MessageLength; i_iter++)
				{
				unSlowDating->m_BrainExistance[unSlowDating->m_Existance[i_aviter]->m_BDataID]->m_Message[i_iter] = unSlowDating->m_Existance[i_aviter]->m_Message[i_iter];
				}

			unSlowDating->m_BrainExistance[unSlowDating->m_Existance[i_aviter]->m_BDataID]->m_CID = i_aviter;
			unSlowDating->m_BrainExistance[unSlowDating->m_Existance[i_aviter]->m_BDataID]->m_State = 1;
			unSlowDating->m_Existance[i_aviter]->m_State = 2;
			}
		}

	for(int i_briter = 0; i_briter < unSlowDating->m_NomBrainExistance; i_briter++)
		{
#if 1
		printf("unTrace brID %i state %i %s %s\n", i_briter, unSlowDating->m_BrainExistance[i_briter]->m_State, unSlowDating->m_BrainExistance[i_briter]->m_Name, unSlowDating->m_BrainExistance[i_briter]->m_Message);
#endif

		if(unSlowDating->m_BrainExistance[i_briter]->m_State == 2)
			{
#if 1
			if(unSlowDating->m_BrainExistance[i_briter]->m_CID >= unSlowDating->m_NomExistance)
				{
				printf("ERROR::: m_Existance out of bounds\n");
				for(;;) {}
				}
#endif

			if(unSlowDating->m_Existance[unSlowDating->m_BrainExistance[i_briter]->m_CID]->m_State == 0)
				{
				for(int i_iter = 0; i_iter < unSlowDating->m_BrainExistance[i_briter]->m_MessageLength; i_iter++)
					{
					unSlowDating->m_Existance[unSlowDating->m_BrainExistance[i_briter]->m_CID]->m_Message[i_iter] = unSlowDating->m_BrainExistance[i_briter]->m_Message[i_iter];
					}

				unSlowDating->m_Existance[unSlowDating->m_BrainExistance[i_briter]->m_CID]->m_State = 2;
				unSlowDating->m_BrainExistance[i_briter]->m_State = 0;
				}
			}
		}
}

// cleanup
static void clean(void)
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
			//case 'A':
			} break;

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
			//_->rbutton=1;
			} break;

		case WM_MBUTTONDOWN:
			{
			//_->mbutton=1;
			} break;

		case 0x020A:	//### Mouse Wheel Scroll
			{
			//_->mwheelroll=1;
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
			} break;

		case WM_CSPEECHEVENT:
			{
#if 0
			//printf("Event\n");
			//i_CSpeechDlg->acSpeechEvent();
			//i_CSpeechDlg->acSetEvent();
			//i_OsirusCore->acCreateTag(i_CSpeechDlg->acSpeechEvent());
			//i_OsirusCore->acSave();
			//i_OsirusCore->acProcessSpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
			i_OsirusCore->acProcessAPISpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
			//i_CSpeechDlg->acSpeechEvent();
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
		}

	return DefWindowProc (hWnd, msg, wParam, lParam);
}

// entry point
int main (int argc, char* argv[])
{
	printf("//               \\\\ -- memory allocation\n");
	printf("  unMessageServer  \n");
	printf("\\\\               // \n");

#if 1
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wcl;
	MSG msg;

	hInstance=hInst;
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	const char *c = "unMessageServer";

	wcl.style			= CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc		= (WNDPROC)WinFunc;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hInstance		= hInst;
	wcl.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcl.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground	= 0;
	wcl.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU);
	wcl.lpszClassName	= "unMessageServer";

	if (!RegisterClass (&wcl))
		{
		printf("ERROR:::main can't register Window\n");
		for(;;) {};
		}

	CreateWindowEx(	0,"unMessageServer",c,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,CW_USEDEFAULT,160,120,
					NULL,NULL,hInst,NULL);

	ShowWindow (hWndMain, SW_SHOWNORMAL);
#endif

	acInit();

	acStartBrainNode("Lisa", 0);
	acStartBrainNode("default", 6);
	acStartBrainNode("default", 3);

#if 0
	for(int iter = 0; iter < 5; iter++)
		{
		acStartBrainNode("default", 0);
		}
#endif

#if 0
	acStartBrainNode("other1");
	acStartBrainNode("other2");
	acStartBrainNode("other3");
	acStartBrainNode("other4");
	acStartBrainNode("other5");
#endif

	if(unSlowDating->m_BStorage->m_State > 0)
		{
		for(int i_aviter = 0; i_aviter < unSlowDating->m_BStorage->NomAI; i_aviter++)
			{
			std::string i_IdentHM = acIdentGen("QBrain");
			unSlowDating->m_Existance[i_aviter].Acquire((char*)i_IdentHM.c_str());

			for(int i_iter = 0; i_iter < i_IdentHM.length(); i_iter++)
				{
				unSlowDating->m_Existance[i_aviter]->m_Name[i_iter] = i_IdentHM[i_iter];
				}

			unSlowDating->m_Existance[i_aviter]->m_State = 0;
			unSlowDating->m_NomExistance++;
			}

		unSlowDating->m_BStorage->m_State = 2;
		printf("unMessageServer::: Serving %i Avatars\n", unSlowDating->m_BStorage->NomAI);
		}
	else printf("unMessageServer::: Waiting...\n");

	while( 1 )
		{
#if 1
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
			else return TRUE;
			}
#endif

		if(unSlowDating->m_BStorage->m_State == 1)
			{
			for(int i_aviter = 0; i_aviter < unSlowDating->m_BStorage->NomAI; i_aviter++)
				{
				std::string i_IdentHM = acIdentGen("QBrain");
				unSlowDating->m_Existance[i_aviter].Acquire((char*)i_IdentHM.c_str());

				for(int i_iter = 0; i_iter < i_IdentHM.length(); i_iter++)
					{
					unSlowDating->m_Existance[i_aviter]->m_Name[i_iter] = i_IdentHM[i_iter];
					}

				unSlowDating->m_Existance[i_aviter]->m_State = 0;
				unSlowDating->m_NomExistance++;
				}

			unSlowDating->m_BStorage->m_State = 2;
			printf("unMessageServer::: Serving %i Avatars\n", unSlowDating->m_BStorage->NomAI);
			}

		/// Scan for messages
		/*if(unSlowDating->m_BStorage->m_State == 2)*/ acScan();

#if 0
		i_CSpeechDlg->m_pVoice->GetStatus(&i_CSpeechDlg->m_VoiceStatus, NULL);
		if(i_CSpeechDlg->m_VoiceStatus.dwRunningState == 1) i_CSpeechDlg->acVoice();
#endif

		if(KEY_DOWN(QIN_F6))
			{
			if(!vecDpress[6])
				{
				vecDpress[6] = true;
				}
			}
		else vecDpress[6] = false;

#if 0
		if(KEY_DOWN(QIN_F7))
			{
			if(!vecDpress[7])
				{
				vecDpress[7] = true;
				}
			}
		else vecDpress[7] = false;

		if(KEY_DOWN(QIN_F11))
			{
			if(!vecDpress[0])
				{
				vecDpress[0] = true;

				i_CSpeechDlg->CreateGeneralTape();
				}
			}
		else vecDpress[0] = false;

		if(QNetwork.m_Recording) QNetwork.RecordWorld(1.0f);

#if 1	//Positioned for lighting
		if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
		QActiveFrameWork->acQFrame();
#endif

		if(KEY_DOWN(QIN_F12))
			{
			if(!vecDpress[1])
				{
				vecDpress[1] = true;

				//i_CSpeechDlg->acProcessEvent("Create Command Level 17");
				//i_CSpeechDlg->acButtonMicroSetup();
				//i_CSpeechDlg->acSetEvent();
				i_CSpeechDlg->acSpeak(unSlowDating->acGenName(0));
				}
			}
		else vecDpress[1] = false;
#endif

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
#if 1
		Sleep(150);
#endif
		}

    clean();
    return 0;
}