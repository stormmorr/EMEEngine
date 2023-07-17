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

#include "OsirusCore.h"

#include "../UnSRC/Utility/unConsole.h"
#include "../UnSRC/Base/UNcompiler.h"
#include "Q-NET-ProtoMap.h"
#include "../../Server/UNSGlobalHeader.h"

#include "../Speech/SpeechDlg.h"
#include "../Server/resource.h"

#if 0
QAGE::QActiveFramewrk *QActiveFrameWork;
#endif

UN::unMessageCore *unMessageCentre;

#if 0
OSI::OsirusCore *i_OsirusCore;
#endif

#if 1
CSpeechDlg *i_CSpeechDlg;
#endif

AimlFacade* m_aryFacade;

LARGE_INTEGER *m_LargeIntCurrent;
LARGE_INTEGER *m_LargeIntNew;
unsigned int m_Counter;
bool vecDpress[15];

QSharedStruct<QBStorage> m_BStorage;
QSharedStruct<Q_Existance> m_Existance[150];
QSharedStruct<Q_Existance> m_BrainExistance[50];

std::string m_Name;

int m_NomExistance;
int m_NomBrainExistance;

HWND hWndMain;

// initialization
static void acInit(void)
{
	unConsoleAttribute(CONSOLE_MSG);
	Q.CoreAcquire();

	playerAV.Acquire("playerAV");

	m_BStorage.Acquire("QBStorage");

	m_Existance[0].Acquire((char*)m_Name.c_str());

	for(int i_iter = 0; i_iter < m_Name.length(); i_iter++)
		{
		m_Existance[0]->m_Name[i_iter] = m_Name[i_iter];
		}

	m_Existance[0]->m_State = 0;

#if 0
	std::string i_Message = "C:\Projects Base\Unification\UnSRC\Process\unMessageCore";

	for(int i_iter = 0; i_iter < i_Message.length(); i_iter++)
		{
		m_Existance[0]->m_Message[i_iter] = i_Message[i_iter];
		}
#endif

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

	i_CSpeechDlg = new CSpeechDlg();
	i_CSpeechDlg->acInit();

#if 0
	i_OsirusCore = new OSI::OsirusCore();
#endif

#if 0
	unMessageCentre = new UN::unMessageCore();
#endif
}

void acScanProc(void)
{
	if(m_Existance[0]->m_State == 1)
		{
		std::string i_Message = m_Existance[0]->m_Message;
		
		GraphBuilder &builder = m_aryFacade->getGraphBuilder();

		StringPimpl response = builder.getResponse(i_Message.c_str());

		int i_iter;
		for(int i_iter = 0; i_iter < response.length(); i_iter++)
			{
			m_Existance[0]->m_Message[i_iter] = response.at(i_iter);
			}

		m_Existance[0]->m_MessageLength = i_iter;
		m_Existance[0]->m_State = 2;
		}
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
		break;

        switch (key)
			{
			//##### Keylogger for Left To Forward Jink
			//case 'A':
			} break;

		case WM_KEYUP:
		key = (char)wParam;
		break;

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
			//printf("Event\n");
			//i_CSpeechDlg->acSpeechEvent();
			//i_CSpeechDlg->acSetEvent();
			//i_OsirusCore->acCreateTag(i_CSpeechDlg->acSpeechEvent());
			//i_OsirusCore->acSave();
			//i_OsirusCore->acProcessSpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));

			//i_OsirusCore->acProcessAPISpeechEvent(i_CSpeechDlg->acProcessEvent(i_CSpeechDlg->acSpeechEvent()));

			//i_CSpeechDlg->acSpeechEvent();

#if 0
			GraphBuilder &builder = m_aryFacade->getGraphBuilder();

			//builder.createGraph(userId, botId, endUserId);

			StringPimpl i_String = builder.getResponse(i_CSpeechDlg->acSpeechEvent());

			i_CSpeechDlg->acSpeak(i_String.c_str());

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
	unConsoleAttribute(CONSOLE_TITLE);

	printf(" /           \\ \n");
	printf("{ unBrainNode }----[memory allocation]\n");
	printf(" \\           / \n");

#if 1
	if(argc == 1)
		{
		unConsoleAttribute(CONSOLE_ERROR);
		printf("ERROR::: Character Name not Set\n");
		for(;;) {}
		}
	else printf("%s Brain [START]\n", argv[1]);
	m_Name = argv[1];
#else
	m_Name = "default";
#endif

	unConsoleAttribute(CONSOLE_MSG);

#if 1
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASS wcl;
	MSG msg;

	hInstance=hInst;
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	const char *c = "unBrainNode";

	wcl.style			= CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc		= (WNDPROC)WinFunc;
	wcl.cbClsExtra		= 0;
	wcl.cbWndExtra		= 0;
	wcl.hInstance		= hInst;
	wcl.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	wcl.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground	= 0;
	wcl.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU);
	wcl.lpszClassName	= "unBrainNode";

	if(!RegisterClass (&wcl))
		{
		printf("ERROR:::main can't register Window\n");
		for(;;) {};
		}

	CreateWindowEx(	0,"unBrainNode",c,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,CW_USEDEFAULT,160,120,
					NULL,NULL,hInst,NULL);

	ShowWindow (hWndMain, SW_SHOWNORMAL);
#endif

	acInit();

	//unMessageCentre = new UN::unMessageCore(i_Name);

	m_aryFacade = new AimlFacade();

	GraphBuilder &builder = m_aryFacade->getGraphBuilder();

	myCallBacks callback;
	builder.setCallBacks(&callback);

	cout << "[loading]" << endl;

	std::string m_substitutions_xml = "conf/substitutions.xml";
	std::string m_sentence_splitters_xml = "conf/sentence-splitters.xml";
	std::string m_properties_xml = "conf/properties.xml";

	std::string m_AIMLSchema = "resources/schema/AIML.xsd";
	std::string m_CommonTypesSchema = "resources/schema/common-types.xsd";
	std::string m_BotConfigurationSchema = "resources/schema/bot-configuration.xsd";

	builder.setAIMLSchema(m_AIMLSchema.c_str());
	builder.setCommonTypesSchema(m_CommonTypesSchema.c_str());
	builder.setBotConfigurationSchema(m_BotConfigurationSchema.c_str());

	builder.setAIMLValidation();
	builder.setBotConfigurationValidation();

	builder.parseSubstitutionFile(m_substitutions_xml.c_str());
	builder.parseSentenceSplitterFile(m_sentence_splitters_xml.c_str());
	builder.parsePropertiesFile(m_properties_xml.c_str());

#if 0
	builder.addDirectoryUnlessAlreadyAdded("C:\Program Files\RebeccaAIML\aiml\annotated_alice");
#endif

	StringPimpl userId = "unMessageServer";
	StringPimpl botId = m_Name.c_str();
	StringPimpl endUserId = "user";

	builder.createGraph(userId, botId, endUserId);

	string botName = builder.getBotPredicate("name").c_str();
	StringPimpl response = builder.getResponse("connect");

	int size = builder.getSize();

	while( 1 )
		{

		//printf("%s\n", unMessageCentre->acResponse("This is a input"));

#if 1
		while(true)
		{
			Sleep(50);
			acScanProc();

			i_CSpeechDlg->m_pVoice->GetStatus(&i_CSpeechDlg->m_VoiceStatus, NULL);
			if(i_CSpeechDlg->m_VoiceStatus.dwRunningState == 1) i_CSpeechDlg->acVoice();

			if(KEY_DOWN(QIN_F12))
				{
				if(!vecDpress[1])
					{
					vecDpress[1] = true;

					//i_CSpeechDlg->acProcessEvent("Create Command Level 17");
					//i_CSpeechDlg->acButtonMicroSetup();
					//i_CSpeechDlg->acSetEvent();
					i_CSpeechDlg->acSpeak(unMessageCentre->acGenName(0));
					}
				}
			else vecDpress[1] = false;

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

			if(KEY_DOWN(QIN_RETURN))
				{
				if(!vecDpress[5])
					{
					vecDpress[5] = true;

					string input;
					cout << "You say> ";

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

						//GraphBuilder &builder = unMessageCentre->m_aryFacade->getGraphBuilder();

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
							cout << "Bot" << " says: " << response.c_str() << endl;
							i_CSpeechDlg->acSpeak(std::string(response.c_str()));
						}
					}
				}
			else vecDpress[5] = false;

			
		}
#endif

#if 0
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

		unMessageCentre->acScanProc();

#if 1
		i_CSpeechDlg->m_pVoice->GetStatus(&i_CSpeechDlg->m_VoiceStatus, NULL);
		if(i_CSpeechDlg->m_VoiceStatus.dwRunningState == 1) i_CSpeechDlg->acVoice();
#endif

#if 0
		if(KEY_DOWN(QIN_F6))
			{
			if(!vecDpress[6])
				{
				vecDpress[6] = true;
				}
			}
		else vecDpress[6] = false;

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
				i_CSpeechDlg->acSpeak(unMessageCentre->acGenName(0));
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
#if 0
		Sleep(5000);
#endif
		}

    clean();
    return 0;
}