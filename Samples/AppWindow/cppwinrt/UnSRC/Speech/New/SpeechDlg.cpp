/*

	C-Speech Dialog Engine
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "SpeechDlg.h"
#include <sphelper.h>

extern HWND hWndMain;
extern HINSTANCE hInstance;

/////////////////////////////////////////////////////////////////////////////
// CSpeechDlg dialog

#if 0
CSpeechDlg::CSpeechDlg(void* pOwnerObject, icThreadData *pData)
	: CThread(pOwnerObject, pData)
{
	m_edit = _T("");
	m_pVoice=NULL;
	m_TapeRecording = false;

	SUPPORT_THREAD_SYNCHRONIZATION(DigiMassCore)
	SUPPORT_THREAD_NOTIFICATION

#if 1
	m_mutex_Speech = SDL_CreateMutex();
#endif
}
#endif

CSpeechDlg::CSpeechDlg()
{
	m_edit = _T("");
	m_pVoice=NULL;
	m_TapeRecording = false;

#if 0
	SUPPORT_THREAD_SYNCHRONIZATION(DigiMassCore)
	SUPPORT_THREAD_NOTIFICATION

	m_mutex_Speech = SDL_CreateMutex();
#endif
}

CSpeechDlg::~CSpeechDlg()
{
	m_pVoice->Release();
	m_pVoice = NULL;

	fclose(m_logFile);

	m_TapeRecording = false;

	printf("CSpeech:::Tape Recording [STOPPED]\n");
}

/////////////////////////////////////////////////////////////////////////////
// CSpeechDlg Threading

#if 0
int CSpeechDlg::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

#if 0
	printf("Trace SetThreadAffinityMask %i\n", SetThreadAffinityMask(GetCurrentThread(), 8));
	printf("Trace SetThreadPriority %i\n", SetThreadPriority(GetCurrentThread(), 25));
#endif

	do
		{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
			{
			case CThread::CMD_INITIALIZE:
				acInit();
				HandleCommandImmediately(CThread::CMD_RUN);
				break;

			case CThread::CMD_RUN:
				Lock();
				Run();
				Unlock();
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
#endif

#if 0
void CSpeechDlg::Run(void)
{
	while(true)
		{
		for(int i_Iter = 0; i_Iter < m_SPQueue.size(); i_Iter++)
			{
			SDL_mutexP(m_mutex_Speech);
			std::string i_text = m_SPQueue[i_Iter];
			SDL_mutexV(m_mutex_Speech);

			acVoice(i_text);
			}
		m_SPQueue.clear();
		}
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpeechDlg message handlers

bool CSpeechDlg::acInit(void)
{
	//Initialization of Com
	::CoInitialize(NULL);

	if(!acInitSpeech())
		{
		printf("CSpeech:::Error Initilizing speech engine\n");
		}

	CreateGeneralTape();

	acVoice("Susan - OSI activated and waiting");

	return true;
}

void CSpeechDlg::CreateGeneralTape(void)
{
	if(m_TapeRecording) CloseTapeBuffer();
	else
		{
		char casecntbuf[100];
		int random = rand()%55000;

		itoa(random, casecntbuf, 10);

		std::string strname = "Recording";
		std::string strnumber = casecntbuf;
		std::string strFilename = strname + strnumber;
		std::string i_path = "TapeStorage\\CSpeech\\";
		std::string i_ext = ".txt";
		std::string i_file = strFilename;
		std::string i_filepath = i_path + i_file + i_ext;

			//##### - Open our Character Data File
		m_logFile = fopen(i_filepath.c_str(), "w");

#pragma message("FIXME::: Saved filename to custom header")

		m_TapeRecording = true;
		m_TapeFileName = i_filepath;

		fprintf(m_logFile, "<Unification-CSpeech-Tape-Recording>\n", m_edit);

		printf("CSpeech:::Tape..[START] i_Filename %s\n", i_filepath.c_str());
		}
}

void CSpeechDlg::CloseTapeBuffer(void)
{
	fclose(m_logFile);

	m_TapeRecording = false;

	printf("CSpeech:::Tape Recording [STOPPED]\n");
}

//Speech Initialization is done here
bool CSpeechDlg::acInitSpeech()
{
	HRESULT hr=S_OK;

	hr=cpCSpeechEngine.CoCreateInstance(CLSID_SpInprocRecognizer);

	if( SUCCEEDED(hr) )
		{
		hr = cpCSpeechEngine->CreateRecoContext(&m_cpRecoCtxt);
		}
	else printf("ERROR:::CoCreateInstance\n");

#if 1
	if( SUCCEEDED(hr) )
		{
		hr=m_cpRecoCtxt->SetNotifyWindowMessage(hWndMain,WM_CSPEECHEVENT, 0, 0 );
		}
	else printf("ERROR:::CreateRecoContext\n");
#endif
	
	if (SUCCEEDED(hr))
		{
        // This specifies which of the recognition events are going 
		//to trigger notifications.Here, all we are interested in 
		//is the beginning and ends of sounds, as well as
        // when the engine has recognized something
		//using ISpRecoContext
        const ULONGLONG ullInterest = SPFEI(SPEI_RECOGNITION);
        hr = m_cpRecoCtxt->SetInterest(ullInterest, ullInterest);
		}
	else printf("ERROR:::SetNotifyWindowMessage\n");

	 // create default audio object
    CComPtr<ISpAudio> cpAudio;
    hr = SpCreateDefaultObjectFromCategoryId(SPCAT_AUDIOIN, &cpAudio);

    // set the input for the engine
    hr = cpCSpeechEngine->SetInput(cpAudio, true);
    hr = cpCSpeechEngine->SetRecoState( SPRST_ACTIVE );

	if (SUCCEEDED(hr))
		{
        // Specifies that the grammar we want is a dictation grammar.
        // Initializes the grammar (m_cpDictationGrammar)
		// using ISpRecoContext
        hr = m_cpRecoCtxt->CreateGrammar( GID_DICTATION, &m_cpDictationGrammar );
		}
	else printf("ERROR:::SetRecoState\n");

	if  (SUCCEEDED(hr))
		{
        //Load the dictation tool for the grammar specified
		//using ISpRecoGrammar
		hr = m_cpDictationGrammar->LoadDictation(NULL, SPLO_STATIC);
		}
	else printf("ERROR:::CreateGrammar\n");

	if (SUCCEEDED(hr))
		{
        //After loading the Dictation set the dictation state to 
		//active using ISpRecoGrammar 
		hr = m_cpDictationGrammar->SetDictationState( SPRS_ACTIVE );
		}
	else printf("ERROR:::LoadDictation\n");

	if (FAILED(hr))
		{
        //Release the grammar using ISpRecoGrammar
		m_cpDictationGrammar.Release();
		printf("ERROR:::SetDictationState\n");
		}

    hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&m_pVoice);

	m_pVoice->SetVolume(999);

	if (FAILED(hr)) printf("ERROR:::CoCreateInstance Voice\n");

	hr = m_cpLexicon.CoCreateInstance(CLSID_SpLexicon);

	m_langid = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

	if(SUCCEEDED(hr))
		{
		hr = SpCreatePhoneConverter(m_langid, NULL, NULL, &m_cpPhoneConverter);

		}
	else printf("ERROR:::CSpeech lexicon error\n");

	if(SUCCEEDED(hr))
		{
		hr = m_cpPhoneConverter->PhoneToId(L"p er d", m_wszId);
		}
	else printf("ERROR:::CSpeech m_cpPhoneConverter error\n");

	if(SUCCEEDED(hr))
		{
		hr = m_cpLexicon->AddPronunciation(L"portshell", m_langid, SPPS_Noun, m_wszId);
		}
	else printf("ERROR:::CSpeech m_cpPhoneConverter->PhoneToId error\n");

	if(hr == S_OK) printf("CSpeech word added succesfully\n");
	if(hr == SP_ALREADY_IN_LEX) printf("CSpeech word already in lexicon dictionary\n");

    return (hr == S_OK);
}

char *CSpeechDlg::acSpeechEvent()
{
	USES_CONVERSION;
    CSpEvent event;

    // Process all of the recognition events
    while (event.GetFrom(m_cpRecoCtxt) == S_OK)
		{
        switch (event.eEventId)
			{
            case SPEI_SOUND_START:
                m_bSound = true;
                break;

            case SPEI_SOUND_END:
                if (m_bSound)
					{
                    m_bSound = false;
                    if (!m_bReco)
						{
                        // The sound has started and ended, 
                        // but the engine has not succeeded in recognizing anything
						const TCHAR szNoise[] = _T("<noise>");
#pragma message("Edit here to change char to string")
                        //m_edit=szNoise;
						//UpdateData(false);
						//::SendDlgItemMessage( m_hDlg, IDC_EDIT_DICT, 
						//	EM_REPLACESEL, true, (LPARAM) szNoise );
						}
                    m_bReco = false;
					} break;

            case SPEI_RECOGNITION:
                // There may be multiple recognition results, so get all of them
				{
                m_bReco = true;
                static const WCHAR wszUnrecognized[] = L"<Unrecognized>";

                CSpDynamicString dstrText;
                if (FAILED(event.RecoResult()->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, true, &dstrText, NULL)))
					{
                    dstrText = wszUnrecognized;
					}

                // Concatenate a space onto the end of the recognized word
                dstrText.Append(L" ");
				
				m_edit=dstrText.CopyToChar();
				
				//UpdateData(false);
                //::SendDlgItemMessage(m_hWnd, IDC_EDIT_DICT, EM_REPLACESEL, true, (LPARAM) W2T(dstrText) );
				//printf("CSpeech:::%s\n", m_edit);

				fprintf(m_logFile, "%s\n", m_edit);

				//fclose(m_logFile);
				//m_logFile = fopen(m_TapeFileName.c_str(), "w");

				//_flushall();

				//acSpeak(m_edit);
				return m_edit;
                } break;

			}
		}
}


void CSpeechDlg::acButtonVoiceTraining() 
{
	// TODO: Add your control notification handler code here
	// Brings up the SR-engine-specific user training UI
    //cpCSpeechEngine->DisplayUI(m_hWnd, NULL, SPDUI_UserTraining, NULL, 0);
}

void CSpeechDlg::acButtonMicroSetup() 
{
	// TODO: Add your control notification handler code here
    // Brings up the SR-engine-specific mic training UI
	cpCSpeechEngine->DisplayUI(hWndMain, NULL, SPDUI_AddRemoveWord, NULL, 0);
}

void CSpeechDlg::acVoice(std::string i_Message)
{
	//conversion or string to wide character
	wchar_t* wszStr;
	int len = strlen(i_Message.c_str());
	wszStr = new wchar_t[len + 50];
	mbstowcs(wszStr,i_Message.c_str(),len+1);

	m_pVoice->Speak(wszStr, SVSFlagsAsync + SVSFPurgeBeforeSpeak, NULL);
}

CSpeechEvent *CSpeechDlg::acProcessEvent(char *i_Text)
{
	std::string i_EventText = i_Text;
	std::string *i_StringPTR = new std::string;

	CSpeechEvent *i_Event = new CSpeechEvent;

	for(unsigned int i_Iter = 0; i_Iter < i_EventText.length(); i_Iter++)
		{
		if(i_EventText[i_Iter] == ' ')	// Stash i_Word in event container
			{
			i_Event->m_Word.push_back(i_StringPTR);
			i_StringPTR = new std::string;
			}
		else i_StringPTR->push_back(i_EventText[i_Iter]);
		}

	i_Event->m_Word.push_back(i_StringPTR);

#if 1
	acPrintEvent(i_Event);
#endif

#if 0
	m_String.compare(c, 1, vecBlocker[cntBlocker], cntChars, 1) != 0) valid = false; }
#endif

return i_Event;
}

void CSpeechDlg::acPrintEvent(CSpeechEvent *i_Event)
{
	printf("CSpeech EVENT %i Words...\n", i_Event->m_Word.size());
	printf("Trace Nom Words %i\n", i_Event->m_Word.size());
	for(unsigned int i_Iter = 0; i_Iter < i_Event->m_Word.size(); i_Iter++)
		{
		printf("%s\n", i_Event->m_Word[i_Iter]->c_str());
		}
}