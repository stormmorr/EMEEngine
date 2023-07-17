/*

	C-Speech Dialog
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#if !defined(AFX_SPEECHDLG_H__F20BA307_BA2F_4A58_AC6A_74FADA90E924__INCLUDED_)
#define AFX_SPEECHDLG_H__F20BA307_BA2F_4A58_AC6A_74FADA90E924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TRUE true
#define FALSE false

#include <sphelper.h>
#include <string>
#include <vector>

#include "../Server/Thread.h"

#define MAX_EDIT_TEXT   1000
#define GID_DICTATION   0					// Dictation grammar has grammar ID 0

#define WM_CSPEECHEVENT    WM_USER+5		// Window message used for recognition events

typedef struct CSpeechEvent
{
public:
	std::vector<std::string*> m_Word;
} CSpeechEvent;

typedef std::list<std::string> UN_MessageList_T;

/////////////////////////////////////////////////////////////////////////////
// CSpeechDlg dialog

class CSpeechDlg
{
// Construction
public:
	CSpeechDlg();
	~CSpeechDlg();

	bool acInit(void);
	bool acInitSpeech();
	char *acSpeechEvent(void);
	void acButtonVoiceTraining(void);
	void acButtonMicroSetup(void);
	void acSpeak(std::string i_Message);
	bool acVoice(void);

	void CreateGeneralTape(void);
	void CloseTapeBuffer(void);

	CSpeechEvent *acProcessEvent(char *i_Text);
	void acPrintEvent(CSpeechEvent *i_Event);

	void acAddWord(const char *i_Word, bool i_Message = false);

	//Identifies a locale for national language support. 
	//Locale information is used for international string 
	//comparisons and localized member names. 
	LCID m_lcid;

	//boolean variables
	bool m_bReco;
	bool m_bSound;

	//Initialize the Recognizer
	CComPtr<ISpRecognizer> cpCSpeechEngine;

	//The ISpRecoContext interface enables applications to create 
	//different functional views or contexts of the SR engine
	CComPtr<ISpRecoContext>     m_cpRecoCtxt;

	//The ISpRecoGrammar interface enables applications to manage 
	//the words and phrases that the SR engine will recognize.
	CComPtr<ISpRecoGrammar>		m_cpDictationGrammar;

	CComPtr<ISpPhoneConverter>		m_cpPhoneConverter;
	CComPtr<ISpLexicon>				m_cpLexicon;

	LANGID							m_langid;
	SPPHONEID						m_wszId[SP_MAX_PRON_LENGTH];

	ISpVoice* m_pVoice;
	SPVOICESTATUS m_VoiceStatus;

	bool m_TapeRecording;
	std::string m_TapeFileName;

	UN_MessageList_T m_SpeechQueue;

// Dialog Data
	//{{AFX_DATA(CSpeechDlg)
	char* m_edit;
	FILE *m_logFile;
	//}}AFX_DATA
};

inline LPWSTR LPCSTRToLPWSTR (char* pCstring)
{
	LPWSTR pszOut = NULL;

	if(pCstring != NULL)
		{
		int nInputStrLen = strlen (pCstring);

		// Double NULL Termination

		int nOutputStrLen = MultiByteToWideChar(CP_ACP, 0, pCstring, nInputStrLen, NULL, 0) + 2; 

		pszOut = new WCHAR [nOutputStrLen];

		if (pszOut)
			{
			memset (pszOut, 0x00, sizeof (WCHAR)*nOutputStrLen);
			MultiByteToWideChar (CP_ACP, 0, pCstring, nInputStrLen, pszOut, nInputStrLen);
			}
		}

return pszOut;
}

#endif
