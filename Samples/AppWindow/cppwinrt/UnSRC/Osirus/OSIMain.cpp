/*

    Osirus Main - Main Entry Point
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#if 1
#include <cstdlib>
#include <string>
#include <iostream>
#include <time.h>
#include <memory>

#include "../UnSRC/QServerFramewrk.h"
#include "../UnSRC/Process/unMessageCore.h"
#include "../UnSRC/Process/OSIPatchBank.h"

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

QAGE::QActiveFramewrk *QActiveFrameWork;
UN::unMessageCore *unProcessor;
OSI::OsirusCore *i_OsirusCore;
CSpeechDlg *i_CSpeechDlg;
Point::OSIPatchBank *i_OSIPatchBank;

LARGE_INTEGER *m_LargeIntCurrent;
LARGE_INTEGER *m_LargeIntNew;
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

bool VI_Swit = false;
bool SAPI_Swit = false;
bool OSI_Swit = false;
bool TX_Swit = true;

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

#if 0
Master i_master;
#endif

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

#if 0 ///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	DigiMass = new Digi::DigiMassCore();
	DigiMass->acInit(DIGI_ERROR_PRINT);
#endif

	i_CSpeechDlg = new CSpeechDlg();
	i_CSpeechDlg->acInit();

	i_OsirusCore = new OSI::OsirusCore();

	unProcessor = new UN::unMessageCore("default", true);

#if 0
#if 1
	i_OsirusCore->m_UsbFrame = new usbFrameWork();
#else
	i_master.Start();
#endif
#endif
}

// update menu state
void update_menu()
{
	/*HMENU menu=GetMenu(hWndMain);
	CheckMenuItem(menu,ID_VIEW_DEPTHBIAS,depthbias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_BLOOM,bloom?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_SCISSOR,scissor?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_NVRENDERDEPTHTEX,depthtex?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_DEBUG,debug?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_INFORMATION,g_render->info?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_FRAMEMEMORY,g_render->framememory?MF_CHECKED:MF_UNCHECKED);
	CheckMenuItem(menu,ID_VIEW_ANTIALIAS,antialias?MF_CHECKED:MF_UNCHECKED);
	CheckMenuRadioItem(menu,ID_VIEW_FREECAMERA,ID_VIEW_FREECAMERA+2,ID_VIEW_FREECAMERA+camera,0);
	CheckMenuRadioItem(menu,ID_VIEW_NORMAL,ID_VIEW_NORMAL+2,ID_VIEW_NORMAL+mode,0);
	CheckMenuRadioItem(menu,ID_RENDER_256X256,ID_RENDER_256X256+4,ID_RENDER_256X256+res,0);
	CheckMenuRadioItem(menu,ID_SCREEN_640X480,ID_SCREEN_640X480+5,ID_SCREEN_640X480+scrres,0);*/
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
			unProcessor->acResponseEffect();

#if 0
			printf("Event\n");
			i_CSpeechDlg->acSpeechEvent();
			i_CSpeechDlg->acSetEvent();
			i_OsirusCore->acCreateTag(i_CSpeechDlg->acSpeechEvent());
			i_OsirusCore->acSave();
			i_OsirusCore->acSpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
			i_CSpeechDlg->acSpeechEvent();
#endif

#if 1
			i_OsirusCore->acGlobalAPISpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));
#endif

#if 0
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
	printf("   OsirusCore    \n");
	printf("\\\\            // \n");

	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wcl;
	MSG msg;

	hInstance=hInst;
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	const char *c = "OsirusCore";

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

	i_OSIPatchBank = new Point::OSIPatchBank();
	i_OSIPatchBank->acPush("Patch\\OSIPat00001_Function");

	for(;;) {}

	acInit();

	unProcessor->acCaptureStart();

	while( 1 )
		{
		if(m_ScCapturing)
			{
			m_ScCapture = unProcessor->acCaptureProgress();

			if(!m_ScCapture)
				{
				m_ScCapturing = false;
				m_ScBuffer = unProcessor->acCaptureGet();
				//printf("trace buffer %i\n", m_ScBuffer);
				}
			}
		else
			{
			unProcessor->acCaptureAnalyse(m_ScBuffer);

#if 0
			m_ScCapture = true;
			m_ScCapturing = true;
#endif

			//unProcessor->acCaptureStart();
			}

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
			//else return TRUE;
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

		if(KEY_DOWN(QIN_F6))
			{
			if(!vecDpress[6])
				{
				vecDpress[6] = true;

				if(QNetwork.m_Recording) QNetwork.FinalizeTapeBuffer();
				else
					{
					char casecntbuf[100];
					std::string strFilename;
					FILE* i_filecheck;
					bool fileSwit = true;

					while(fileSwit)
						{
						int random = rand()%55000;

						itoa(random, casecntbuf, 10);

						std::string strname = "Recording";
						std::string strnumber = casecntbuf;
						strFilename = strname + strnumber;

						FILE* i_filecheck = fopen(strFilename.c_str(), "rb");
						if(i_filecheck == 0) fileSwit = false;
						}
					fclose(i_filecheck);

					QNetwork.CreateTapeBuffer(strFilename.c_str());
					}
				}
			}
		else vecDpress[6] = false;

		if(KEY_DOWN(QIN_F7))	// Exper
			{
			if(!vecDpress[7])
				{
				vecDpress[7] = true;

				if(QNetwork.m_Playing)
					{
					QNetwork.CloseTapeBuffer();
					_->NetworkOption = 0;
					}
				else
					{
					//QNetwork.OpenTapeBuffer("Recording15830.txt");
					//QNetwork.OpenTapeBuffer("Recording19348.txt");
					//QNetwork.OpenTapeBuffer("Recording24251.txt");
					QNetwork.OpenTapeBuffer("Recording26908.txt");
					_->NetworkOption = 1;
					}
				}
			}
		else vecDpress[7] = false;

		if(KEY_DOWN(QIN_F11))
			{
			if(!vecDpress[0])
				{
				vecDpress[0] = true;

				//i_CSpeechDlg->CreateGeneralTape();

				//char * i_SpeechEvent = i_CSpeechDlg->acSpeechEvent();

				const char *i_Input = "Input";

				const char *i_Response = unProcessor->acResponse(i_Input);

				//i_CSpeechDlg->acSpeak(i_Response);
				}
			}
		else vecDpress[0] = false;

		if(QNetwork.m_Recording) QNetwork.RecordWorld(1.0f);

#if 0	//Positioned for lighting
		if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
		QActiveFrameWork->acQFrame();
#endif

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
		}

    clean();
    return 0;
}
#else
#include <rebecca/all.h>
using namespace rebecca;
#include <iostream>
#include <string>
using namespace std;
#include "OSIKnowledgeBase.h"

int main (int argc, char* args[]) 
{
	try
	{
		
		/*
		 * Create the arguments object
		 * and pass it the arguments 
		 * for parsing
		 */
		Arguments arguments(argc, args);

		/*
		 * This is responsible for memory management of 
		 * GraphBuilder.
		 */
		AimlFacade aiml;

		/*
		 * Get the GraphBuilder concrete class that 
		 * was created inside of AimlFacade.
		 * DO NOT try to delete GraphBuilder.  Let
		 * AimlFacade handle that when it falls out 
		 * of scope.
		 */
		GraphBuilder &builder = aiml.getGraphBuilder();
		
		/*
		 * Create an instantiation of our custom 
		 * callbacks we created above.
		 */
		myCallBacks callback;

		/* Give the address to Rebecca for usesage.
		 * Rebecca DOES NOT delete it.  
		 */
		builder.setCallBacks(&callback);

		cout << "[Rebecca loading]" << endl;

		/* 
		 * Set the schemas for the AIML XML (AIML.xsd)
		 * and for Rebecca's own configuration files.
		 * The schema's have to be relative to where the files
		 * you are going to parse are going to be at.
		 */
		builder.setAIMLSchema(arguments.getAimlSchemaPath().c_str());
		builder.setCommonTypesSchema(arguments.getCommonTypesSchemaPath().c_str());
		builder.setBotConfigurationSchema(arguments.getBotConfigurationSchemaPath().c_str());

		/* 
		 * Set that "yes" we do want to do XML validation on
		 * both the AIML XML and Rebecca's own configuration 
		 * files.
		 */
		builder.setAIMLValidation();
		builder.setBotConfigurationValidation();

		/*
		 * Parse Rebecca's configuration files to setup 
		 * Rebecca's ability to handle input subsitutions, 
		 * what a sentence splitter is, and what bot properties
		 * she should have.
		 */
		string substitutions_xml = arguments.getConfigurationDirectory() + "/substitutions.xml";
		builder.parseSubstitutionFile(substitutions_xml.c_str());
		
		string sentence_splitters_xml = arguments.getConfigurationDirectory() + "/sentence-splitters.xml";
		builder.parseSentenceSplitterFile(sentence_splitters_xml.c_str());
		
		string properties_xml = arguments.getConfigurationDirectory() + "/properties.xml";
		builder.parsePropertiesFile(properties_xml.c_str());
		
		/*
		 * Add the entire directory.  Every file that has the 
		 * extension ".aiml" will be added to the internal queue 
		 * for latter processing.
		 */
		builder.addDirectory(arguments.getAimlDirectory().c_str());

		/*
		 * No other files to add to the internal queue.  
		 * So, let's create the AIML graph, the internal 
		 * data structures.
		 */
		builder.createGraph();

		/*
		 * Get the number of AIML categories loaded in total.
		 */
		int size = builder.getSize();

		//Print out the number of categories loaded.
		cout << endl << endl;
		cout << "[Rebecca now fully loaded]" << endl;
		cout << "[Number of categories loaded: " << size << "]" << endl;
		cout << "[Type /exit to exit]" << endl << endl << endl;

		/*
		 * Get the botName which should be Rebecca since that is 
		 * the name give in the configuration file properties.xml
		 * which we parsed above.
		 */
		string botName = builder.getBotPredicate("name").c_str();

		/*
		 * Send a initial conversation of "connect" to 
		 * annotated alice and get the response.
		 */
		StringPimpl response = builder.getResponse("connect");		

		//Send the initial opening line of the bot
		cout << botName << " says: " << response.c_str() << endl;

		/*
		 * The main loop to get the input 
		 * from the user until the user types '/exit'
		 */
		while(true)
		{
			string input;
			cout << "You say> ";

			//Get input from the user from the keyboard
			getline(cin, input); 
			
			if(input == "/exit")
			{
				/*
				 * The user wants to exit so break
				 * out of the while(true) loop
				 */
				break;
			}
			else //The user gave an input to the bot
			{
				//Here we get some internal Rebecca information.
				cout << endl
					<< "Internal information:" << endl 
					<< "=====================" << endl
					<< input << " : " 
					<< builder.getThat().c_str() << " : "
					<< builder.getTopic().c_str() << endl;

				/*
				 * Ahhh finally.  We give the user input to Rebecca Aiml's loaded 
				 * AIML and get the response back.
				 */
				StringPimpl response = builder.getResponse(input.c_str());
				
				cout << "=====================" << endl << endl;
				
				//Print out what Rebecca says.
				cout << botName << " says: " << response.c_str() << endl;
			}
		}
	}
	/* 
	 * All the exceptions are grouped here but you 
	 * might not want this since it's a bit harder 
	 * to determine where they came from.
	 */
	catch(DirectoryNotFoundException &e)
	{
		cout << "[A Directory Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(FileNotFoundException &e)
	{
		cout << "[A File Was Not Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(IllegalArgumentException &e)
	{
		cout << "[IllegalArgument Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(InitializationException &e)
	{
		cout << "[Initialization Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(XMLErrorException &e)
	{
		cout << "[XMLError Exception Found Terminating]" << endl;
		cout << "[" << e.what() << "]" << endl;
		return 1;
	}
	catch(Exception &e)
	{
		cout << "[An uknown exception occured, Terminating program]" << endl;
		cout << "[" << e.what() << "]";
		return 1;
	}

	//Everything smooth.  Exit normally.
	return 0;
}
#endif