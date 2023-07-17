/*
 Program Name: TCVScroll.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Vertical scrollbar manager.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCVScroll.cpp: implementation of the TCVScroll class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#undef NOMINMAX

#include "TCVScroll.h"
#include <limits.h>	//INT_MAX

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCVScroll::TCVScroll()
{
	m_iScrollMax  = 0;
	m_iScrollPos = 0;
	vPos = 0;
}

TCVScroll::~TCVScroll()
{

}

void	TCVScroll::mSetup(HWND hWnd, long maxLines, int yClient, int yChar)
{
	int iClientLines;
	m_yChar = yChar;
	m_yClient = yClient;

	//vMax is the topmost line of the final display
	iClientLines = (yClient / yChar);
	vMax = maxLines - iClientLines;
	vInc = 1;

	m_iScrollMax = max(0, (int)vMax);
	if(m_iScrollMax != vMax) 
	{
		vInc = (vMax / INT_MAX) + 1;
		m_iScrollMax = INT_MAX;
	}
	m_iScrollPos = min(m_iScrollPos, m_iScrollMax);
	vPos = min((long)m_iScrollPos * vInc, vMax);
	SetScrollRange (hWnd, SB_VERT, 0, m_iScrollMax, false);
	SetScrollPos   (hWnd, SB_VERT, m_iScrollPos, true);
}

LRESULT TCVScroll::wmVScroll(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int nVscrollInc;
	SCROLLINFO si;
	bool bOk;
	// Initialize SCROLLINFO structure
	ZeroMemory(&si, sizeof(SCROLLINFO));
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_TRACKPOS;
 
	// Call GetScrollInfo to get current tracking 
	//    position in si.nTrackPos
	bOk = GetScrollInfo(hWnd, SB_VERT, &si);
	// Ignore bOk for now

	switch (GET_WM_VSCROLL_CODE(wParam, lParam))
	{
	case SB_TOP:
		nVscrollInc = -m_iScrollPos;
		break;
	case SB_BOTTOM:
		nVscrollInc = m_iScrollMax  - m_iScrollPos;
		break;
	case SB_LINEUP:
		nVscrollInc = -1;
		break;
	case SB_LINEDOWN:
		nVscrollInc = 1;
		break;
	case SB_PAGEUP:
		nVscrollInc = -max(1, m_yClient / m_yChar);
		break;
	case SB_PAGEDOWN:
		nVscrollInc = max(1, m_yClient / m_yChar);
		break;
	case SB_THUMBPOSITION:
		nVscrollInc = si.nTrackPos - m_iScrollPos;
		break;
	case SB_THUMBTRACK:
		nVscrollInc = si.nTrackPos - m_iScrollPos;
		break;
	default:
		nVscrollInc = 0;
	}

	//Can't move back more than current pos (m_iScrollPos)
	//Can't moce forward more than the units till max
	nVscrollInc = max(
		-m_iScrollPos,
		min(nVscrollInc, m_iScrollMax - m_iScrollPos));

	//Save time for 0 change
	if(nVscrollInc)
	{
		m_iScrollPos += nVscrollInc;
		//Ok translate scroll values into file values
		vPos = min((long)m_iScrollPos * vInc, vMax);
		//Adjust the window
		//Have to not scroll the columns 
		//ScrollWindow(hWnd, 0, -m_yChar * nVscrollInc, NULL, NULL);
		SetScrollPos(hWnd, SB_VERT, m_iScrollPos, true);
		//- bah, just redraw everything
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
	}
	return 0l;
}
