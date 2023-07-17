/*
 Program Name: TCFind.cpp
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: Functions to put up a Find dialog
	And a C++ class to search a buffer.
 Platform: Win XP Home VisualC++ 6.0, Pentium

Usage:
static UINT WM_FIND = WM_USER+1;
static HWND hFind = NULL;

	WM_CREATE:
		WM_FIND = initFind(hWnd);
	WM_COMMAND:
		//When appropriate
		hFind = getFind(hWnd, szFind);
	default:
		if(Message == WM_FIND)
		{
			LPFINDREPLACE lpfr = (LPFINDREPLACE) lParam;
			if(lpfr->Flags & FR_FINDNEXT)
			{
				//Find & Highlite the next match in the edit box.
				//findNext(lpfr->lpstrFindWhat, matchSize, lpfr->Flags & FR_DOWN);
			}
		}


*/
// TCFind.cpp: implementation of the TCFind class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "TCFind.h"
#include <cderr.h>  // for CommDlgExtendedError() 
#include <stdio.h>

LPSTR szWinMessage = "FindMessage";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCFind::TCFind()
{

}

TCFind::~TCFind()
{

}

int	TCFind::iFind(char *buffer, int bufferSize, char *match, int iMatchLen)
{
	char *sptr = find(buffer, bufferSize, match, iMatchLen);
	if(sptr)
		return (sptr - buffer);
	return -1;
}

char *TCFind::find(char *buffer, int bufferSize, char *match, int iMatchLen)
{
	char	*sptr0, *sptr1;
	char	*mptr0, *mptr1;
	int	pos, mpos, matchSize, length;

	if(bufferSize <= 0) return NULL;
	if(buffer == NULL) return NULL;
   if(match == NULL) return NULL;
	pos = 0;
	sptr0 = buffer;
	mptr0 = match;
	matchSize = iMatchLen;
	while(pos < bufferSize)
	{
		if(*sptr0 == *mptr0)
		{
			mpos = 1;
			sptr1 = sptr0 + 1;
			mptr1 = mptr0 + 1;
			length = matchSize;
			if((bufferSize - pos) < matchSize) return NULL;
			while(--length > 0)
			{
				if(*sptr1++ != *mptr1++) break;
			}
			if(length == 0) return sptr0;
		}
		++pos;
		++sptr0;
	}
	return NULL;
}

char *TCFind::backFind(char *buffer, int bufferSize, char *bufferOff, char *match)
{
	char	*sptr0, *sptr1;
	char	*mptr0, *mptr1;
	int	pos, mpos, matchSize, length;

	if(bufferSize <= 0) return NULL;
	if(buffer == NULL) return NULL;
	if(match == NULL) return NULL;
	if((bufferOff - buffer) < 0) return NULL;
	if(((buffer + bufferSize) - bufferOff) <= 0) return NULL;
	pos = bufferOff - buffer;
	sptr0 = bufferOff;
	mptr0 = match;
	matchSize = strlen(match);
	while(pos >= 0)
	{
		if(*sptr0 == *mptr0)
		{
			mpos = 1;
			sptr1 = sptr0 + 1;
			mptr1 = mptr0 + 1;
			length = matchSize;
			if((bufferSize - pos) >= matchSize)
			{
				while(--length > 0)
				{
					if(*sptr1++ != *mptr1++) break;
				}
				if(length == 0) return sptr0;
			}
		}
		--pos;
		--sptr0;
	}
	return NULL;
}

void ShowComDlgError(HWND hWnd)    
{
    DWORD   dwError ;
    char    cBuf [64] ;
    
    dwError = CommDlgExtendedError () ;
    if (dwError)
    {
		sprintf(cBuf, "Error %li", dwError);
        MessageBox (hWnd, "Common Dialog Error Detected", cBuf,
            MB_ICONEXCLAMATION | MB_OK) ;        
    }
}

UINT	initFind(HWND hWindow)
{
	return RegisterWindowMessage(FINDMSGSTRING);
}

HWND getFind(HWND hWindow, TCHAR *szFind)
{
	static FINDREPLACE fr;	//static for modeless
	HWND hDlg;
	fr.lStructSize = sizeof(FINDREPLACE);
	fr.hwndOwner = hWindow;
	fr.hInstance = NULL;
	//fr.Flags = FR_HIDEUPDOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD;
	fr.Flags = FR_DOWN | FR_HIDEWHOLEWORD;
	fr.lpstrFindWhat = szFind;
	fr.lpstrReplaceWith = NULL;
	fr.wFindWhatLen = sizeof(TCHAR) * 256;
	fr.wReplaceWithLen = 0;
	fr.lCustData = 0;
	fr.lpfnHook = NULL;
	fr.lpTemplateName = NULL;

	hDlg = FindText(&fr);
	if(hDlg == NULL)
	{
		ShowComDlgError(hWindow);
	}
	return hDlg;
}
