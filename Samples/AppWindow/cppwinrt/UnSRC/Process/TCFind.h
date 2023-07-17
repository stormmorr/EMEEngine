/*
 Program Name: TCFind.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: Functions to put up a Find dialog
	And a C++ class to search a buffer.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCFind.h: interface for the TCFind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCFIND_H__613EEFD1_D21B_11D4_8BCA_DA23C8E5C406__INCLUDED_)
#define AFX_TCFIND_H__613EEFD1_D21B_11D4_8BCA_DA23C8E5C406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define STRICT
#include <windows.h>
#include <commdlg.h>

extern	LPSTR szWinMessage;
UINT	initFind(HWND hWindow);
HWND	getFind(HWND hWindow, TCHAR *szFind);

class TCFind  
{
public:
	TCFind();
	virtual ~TCFind();
	char *	find(char *buffer, int bufferSize, char *match, int iMatchLen);
	char *	backFind(char *buffer, int bufferSize, char *bufferOff, char *match);
	int		iFind(char *buffer, int bufferSize, char *match, int iMatchLen);
};

#endif // !defined(AFX_TCFIND_H__613EEFD1_D21B_11D4_8BCA_DA23C8E5C406__INCLUDED_)
