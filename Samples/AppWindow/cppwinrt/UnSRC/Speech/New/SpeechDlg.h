/*

	C-Speech Dialog
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#if !defined(AFX_SPEECHDLG_H__F20BA307_BA2F_4A58_AC6A_74FADA90E924__INCLUDED_)
#define AFX_SPEECHDLG_H__F20BA307_BA2F_4A58_AC6A_74FADA90E924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sphelper.h>
#include <string>
#include <vector>

#include "../Utility/Thread.h"

#define MAX_EDIT_TEXT   1000
#define GID_DICTATION   0					// Dictation grammar has grammar ID 0

#define WM_CSPEECHEVENT    WM_USER+5		// Window message used for recognition events

typedef struct CSpeechEvent
{
public:
	std::vector<std::string*> m_Word;
} CSpeechEvent;

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
	void acVoice(std::string i_Message);

	void CreateGeneralTape(void);
	void CloseTapeBuffer(void);

	CSpeechEvent *acProcessEvent(char *i_Text);
	void acPrintEvent(CSpeechEvent *i_Event);

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

	bool m_TapeRecording;
	std::string m_TapeFileName;

// Dialog Data
	//{{AFX_DATA(CSpeechDlg)
	char* m_edit;
	FILE *m_logFile;
	//}}AFX_DATA
};

#endif
