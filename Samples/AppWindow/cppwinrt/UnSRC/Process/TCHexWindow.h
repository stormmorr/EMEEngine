/*
 Program Name: TCHexWindow.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Interface class.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCHexWindow.h: interface for the TCHexWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCHEXWINDOW_H__A2B1688B_52A9_4839_9A32_39FB0FC9908B__INCLUDED_)
#define AFX_TCHEXWINDOW_H__A2B1688B_52A9_4839_9A32_39FB0FC9908B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define STRICT
#include <windows.h>
#include "TCHScroll.h"
#include "TCVScroll.h"

class TCHexWindow  
{
private:
	TCHScroll	m_hScroll;
	TCVScroll	m_vScroll;
	HFONT m_hFont;
	int m_fontx, m_fonty, m_fontnl;
    int	m_ClientWidth;
    int	m_ClientHeight;
	int m_ClientLines;
	int m_iDisplayChars;
public:
	char szClassName[50];
	char szWinTitle[50];
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	TCHAR	m_MemBuffer[100*500];
	HANDLE m_hProcess;
	MEMORY_BASIC_INFORMATION	mbi;
public:
	void LoadMem(DWORD dwOffset);
	TCHexWindow();
	virtual ~TCHexWindow();
	bool Register(HINSTANCE hInst);
	void Init(HANDLE hProcess, MEMORY_BASIC_INFORMATION	*pmbi);
	HWND Create(HINSTANCE hInst, int nCmdShow);
	LRESULT CALLBACK WndProc(
		HWND hWindow, UINT Message,
		WPARAM wParam, LPARAM lParam
	);
	LRESULT	wmCommand(HWND hWindow, WPARAM wParam, LPARAM lParam);
	LRESULT wmCreate(HWND hWindow);
	LRESULT wmSize(HWND hWnd, LPARAM lParam);
	LRESULT wmDestroy(HWND hWindow);
	LRESULT wmPaint(HWND hWindow);
	void SetupFont(HWND hWnd);
};

extern TCHexWindow gHexWindow;

#endif // !defined(AFX_TCHEXWINDOW_H__A2B1688B_52A9_4839_9A32_39FB0FC9908B__INCLUDED_)
