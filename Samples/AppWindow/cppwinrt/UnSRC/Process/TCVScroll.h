/*
 Program Name: TCVScroll.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Interface class.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCVScroll.h: interface for the TCVScroll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCVSCROLL_H__2E613ADB_AB7E_4A3C_A184_8D129D421977__INCLUDED_)
#define AFX_TCVSCROLL_H__2E613ADB_AB7E_4A3C_A184_8D129D421977__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define STRICT
#include <windows.h>
#include <windowsx.h>

class TCVScroll  
{
public:
	int m_yChar, m_yClient;
	//Actual values for scrollbar movement
	int m_iScrollPos;
	int m_iScrollMax;
	//Virtual values for file movement
	long vPos;
	long vMax;
	int vInc;
public:
	TCVScroll();
	virtual ~TCVScroll();
	void	mSetup(HWND hWnd, long maxLines, int yClient, int yChar);
	LRESULT wmVScroll(HWND hWnd, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_TCVSCROLL_H__2E613ADB_AB7E_4A3C_A184_8D129D421977__INCLUDED_)
