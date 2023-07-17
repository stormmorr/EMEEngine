/*
 Program Name: TCScroll.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Interface class.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCHScroll.h: interface for the TCHScroll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCHSCROLL_H__795E6F7A_F358_4DF2_B731_ED297C50B930__INCLUDED_)
#define AFX_TCHSCROLL_H__795E6F7A_F358_4DF2_B731_ED297C50B930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define STRICT
#include <windows.h>
#include <windowsx.h>

class TCHScroll  
{
public:
	int m_iScrollPos;
	int m_iScrollMax;
	int m_xChar;
	void mSetup(HWND hWnd, int xMaxPixWidth, int xClient, int xChar);
	LRESULT wmHScroll(HWND hWnd, WPARAM wParam, LPARAM lParam);
	TCHScroll();
	virtual ~TCHScroll();

};

#endif // !defined(AFX_TCHSCROLL_H__795E6F7A_F358_4DF2_B731_ED297C50B930__INCLUDED_)
