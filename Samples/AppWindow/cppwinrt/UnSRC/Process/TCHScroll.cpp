/*
 Program Name: TCHScroll.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Horizontal scrollbar manager.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCHScroll.cpp: implementation of the TCHScroll class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#undef NOMINMAX

#include "TCHScroll.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCHScroll::TCHScroll()
{
	m_iScrollPos = 0;
}

TCHScroll::~TCHScroll()
{

}

LRESULT TCHScroll::wmHScroll(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int nHscrollInc;
	switch (GET_WM_HSCROLL_CODE(wParam, lParam))
	{
	case SB_LINEUP:
		nHscrollInc = -1;
		break;
	case SB_LINEDOWN:
		nHscrollInc = 1;
		break;
	case SB_PAGEUP:
		nHscrollInc = -8;
		break;
	case SB_PAGEDOWN:
		nHscrollInc = 8;
		break;
	case SB_THUMBPOSITION:
		nHscrollInc = GET_WM_HSCROLL_POS(wParam, lParam) - m_iScrollPos;
		break;
	case SB_THUMBTRACK:
		nHscrollInc = GET_WM_HSCROLL_POS(wParam, lParam) - m_iScrollPos;
		break;
	default:
		nHscrollInc = 0;
	}

    nHscrollInc = max(-m_iScrollPos,
            min(nHscrollInc, m_iScrollMax - m_iScrollPos));
	if(nHscrollInc)
	{
		m_iScrollPos += nHscrollInc;
		ScrollWindow(hWnd, -m_xChar * nHscrollInc, 0, NULL, NULL);
		SetScrollPos(hWnd, SB_HORZ, m_iScrollPos, true);
		UpdateWindow(hWnd);
	}
	return 0l;
}

void TCHScroll::mSetup(HWND hWnd, int xMaxPixWidth, int xClient, int xChar)
{
	//Char width in pixels
	m_xChar = xChar;
	//Max scroll value in chars
	m_iScrollMax = max(0, 1 + ((xMaxPixWidth - xClient) / m_xChar));
	m_iScrollPos = min(m_iScrollPos, m_iScrollMax);
	SetScrollRange (hWnd, SB_HORZ, 0, m_iScrollMax, false);
	SetScrollPos   (hWnd, SB_HORZ, m_iScrollPos, true);
}
