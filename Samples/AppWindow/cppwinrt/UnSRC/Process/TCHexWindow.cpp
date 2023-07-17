/*
 Program Name: TCHexWindow.h
 Programmer: Timothy Carpenter, 
	(c) Copyright 2003 San Diego
 Description: C++ Windows Process Memory Viewing class.
 Platform: Win XP Home VisualC++ 6.0, Pentium
*/
// TCHexWindow.cpp: implementation of the TCHexWindow class.
//
//////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "resource.h"
#include "TCHexWindow.h"
#include <stdio.h>

TCHexWindow gHexWindow;
char *SnapLine(char *szBuf, LPSTR mem, int len, int dwid, char *olbl);

//System hook
LRESULT CALLBACK gHexWindowProc(
	HWND hWindow, UINT Message,
	WPARAM wParam, LPARAM lParam
)
{
	return gHexWindow.WndProc(hWindow, Message, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
TCHexWindow::TCHexWindow()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//Init class
	szClassName[0] = '\0';
	szWinTitle[0] = '\0';
	strcpy(szClassName, "HexWindow");
	strcpy(szWinTitle, "HexWindow");
}

TCHexWindow::~TCHexWindow()
{

}

bool TCHexWindow::Register(HINSTANCE hInst)
{
#if 0
	WNDCLASSEX wcex;

	m_hInst = hInst;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)gHexWindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInst;
	wcex.hIcon			= LoadIcon(hInst, (LPCTSTR)MAKEINTRESOURCE(IDI_ICOLARGE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDM_HEXWINDOW;
	wcex.lpszClassName	= this->szClassName;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)MAKEINTRESOURCE(IDI_ICOSMALL));
#endif
	WNDCLASSEX wcex;
	return RegisterClassEx(&wcex);
}

void TCHexWindow::LoadMem(DWORD dwOffset)
{
	LPVOID lpAddress;
	DWORD dwBytesRead;

	lpAddress = (LPVOID)((DWORD)mbi.BaseAddress + dwOffset);
	ReadProcessMemory(
		m_hProcess,
		lpAddress,
		m_MemBuffer,
		16 * m_ClientLines,
		&dwBytesRead);
}

void TCHexWindow::Init(HANDLE hProcess, MEMORY_BASIC_INFORMATION	*pmbi)
{
	m_hProcess = hProcess;
	memcpy(&mbi, pmbi, sizeof(mbi));
	LoadMem(0);
}

HWND TCHexWindow::Create(HINSTANCE hInst, int nCmdShow)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int top = 10;
    int left = 10;
	this->m_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW , 
		this->szClassName, this->szWinTitle, 
		WS_OVERLAPPED | WS_SIZEBOX | WS_MAXIMIZEBOX | WS_MINIMIZEBOX |WS_SYSMENU 
		| WS_HSCROLL | WS_VSCROLL,
        left, top, (screenWidth * 4)/5,  (screenHeight * 4)/5, 
		NULL, NULL, hInst, NULL);	
	ShowWindow(this->m_hWnd, nCmdShow);
	UpdateWindow(this->m_hWnd);
	return this->m_hWnd;
}

LRESULT CALLBACK TCHexWindow::WndProc(
	HWND hWindow, UINT Message,
	WPARAM wParam, LPARAM lParam
)
{
	switch(Message)
	{
	case WM_COMMAND:
		return wmCommand(hWindow, wParam, lParam);
	case WM_HSCROLL:
		return m_hScroll.wmHScroll(hWindow, wParam, lParam);
	case WM_VSCROLL:
		return m_vScroll.wmVScroll(hWindow, wParam, lParam);
	case WM_CREATE:
		return wmCreate(hWindow);
	case WM_SIZE:
		return wmSize(hWindow, lParam);
	case WM_DESTROY:
		return wmDestroy(hWindow);
	case WM_PAINT:
		return wmPaint(hWindow);
	default:
		return DefWindowProc(hWindow, Message, wParam, lParam);
	}
	return 0l;
}

LRESULT	TCHexWindow::wmCommand(HWND hWindow, WPARAM wParam, LPARAM lParam)
{
#if 0
	switch(wParam)
	{
	case ID_FILE_EXIT:
		DestroyWindow(hWindow);
		break;
	default:
		break;
	}
	//MSDN for VC 6.0
	//If an application processes this message, it should return zero. 
#endif
	return 0l;
}

LRESULT TCHexWindow::wmCreate(HWND hWindow)
{
	char szBuffer[120];
	//MSDN for VC 6.0
	//If an application processes this message, it should: 
	//return 0 creates, -1 aborts
	SetupFont(hWindow);
	sprintf(szBuffer, "Address %08lx, %li bytes (%08lx)", this->mbi.BaseAddress, this->mbi.RegionSize, this->mbi.RegionSize);
	SetWindowText(hWindow, szBuffer);
	return 0l;
}

LRESULT TCHexWindow::wmSize(HWND hWnd, LPARAM lParam)
{
	char szBuffer[120];
	int iChLength;
	int iMaxLines;

	if(lParam)
	{
		m_ClientHeight = HIWORD(lParam);
		m_ClientWidth = LOWORD(lParam);
		m_ClientHeight = (m_ClientHeight / this->m_fontnl + 1) * this->m_fontnl;
		m_ClientLines = m_ClientHeight / this->m_fontnl;
		m_iDisplayChars = m_ClientWidth / this->m_fontx;
		SnapLine(szBuffer, (LPSTR)m_MemBuffer, 16, 16, (char *)NULL);
		iChLength = strlen(szBuffer);
		m_hScroll.mSetup(hWnd, iChLength * this->m_fontx, this->m_ClientWidth, this->m_fontx);
		iMaxLines = (mbi.RegionSize / 16) + 1;
		m_vScroll.mSetup(hWnd, iMaxLines, m_ClientHeight, m_fonty);
	}
	return 0l;
}

LRESULT TCHexWindow::wmDestroy(HWND hWindow)
{
    DeleteObject(this->m_hFont);
	return 0l;
}

LRESULT TCHexWindow::wmPaint(HWND hWindow)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR szBuffer[180];
	int i, iChWidth, iLenBuffer;
	DWORD lAddress;
	LPVOID lpData;

	hdc = BeginPaint(hWindow, &ps);
    SelectObject(hdc, m_hFont);
	LoadMem(m_vScroll.vPos * 16);
	lAddress = 0;
	for(i=0; i < this->m_ClientLines; i++)
	{
		lpData = (LPVOID)((DWORD)m_MemBuffer + lAddress);
		SnapLine(szBuffer, (char *)lpData, 16, 16, (char *) ((char *)mbi.BaseAddress + (m_vScroll.vPos * 16) + lAddress));
		iLenBuffer = strlen(szBuffer);
		iChWidth = iLenBuffer;
		if(m_iDisplayChars < iLenBuffer)
			iChWidth = m_iDisplayChars;
		TextOut(hdc,
			this->m_fontx * (-m_hScroll.m_iScrollPos + 0),
			this->m_fonty * i,
			szBuffer,
			iLenBuffer);
		lAddress += 16;
	}
	EndPaint(hWindow, &ps);
	return 0l;
}

void TCHexWindow::SetupFont(HWND hWnd)
{
	LOGFONT   cursfont;  // font structure
	HFONT     hOldFont; // handle of original font
	HFONT     hNewFont;	// handle of new fixed font
	HDC hdc;
	TEXTMETRIC tm;

    // Get the display context.
    hdc = GetDC(hWnd);

    // Build fixed screen font. 
	// Needed to display hex formated dump.
    cursfont.lfHeight         =  14;
    cursfont.lfWidth          =  9;
	cursfont.lfEscapement     =  0;
    cursfont.lfOrientation    =  0;
    cursfont.lfWeight         =  FW_NORMAL;
    cursfont.lfItalic         =  false;
    cursfont.lfUnderline      =  false;
    cursfont.lfStrikeOut      =  false;
    cursfont.lfCharSet        =  ANSI_CHARSET;
    cursfont.lfOutPrecision   =  OUT_DEFAULT_PRECIS;
    cursfont.lfClipPrecision  =  CLIP_DEFAULT_PRECIS;
    cursfont.lfQuality        =  DEFAULT_QUALITY;
    cursfont.lfPitchAndFamily =  FIXED_PITCH | FF_DONTCARE;
    strcpy((char *)cursfont.lfFaceName, "System");

    hNewFont = CreateFontIndirect((LPLOGFONT) &cursfont);

    // Install the font in the current display context.
	hOldFont = (HFONT)SelectObject(hdc, hNewFont);

    // get text metrics for paint
    GetTextMetrics(hdc, &tm);
    m_fontx = tm.tmAveCharWidth;
    m_fonty = tm.tmHeight + tm.tmExternalLeading;
    m_fontnl = tm.tmHeight;
	m_hFont = hNewFont;

    // Release the display context.
    ReleaseDC(hWnd, hdc);
}

/*
	This is code from a Borland 4.5 File Hex Dump 
	sample project 
*/
//*******************************************************************
// SnapLine - dump a line of memory
//
// paramaters:
//             szBuf         - buffer to hold result
//             mem           - pointer to memory to format
//             len           - length to format
//             dwid          - max display width (8 or 16 recomended)
//             olbl          - label to put at start of line
//
// returns:
//             A pointer to szBbuf.
//
//*******************************************************************
char *SnapLine(char *szBuf, LPSTR mem, int len, int dwid, char *olbl)
{
    int            i;
    int            j;
    unsigned char  c;
    unsigned char  buff[80];
    unsigned char  tbuf[80];

    if (len > dwid)
        len = dwid;

	 *szBuf = 0;

    // Show offset for this line.
    sprintf((char *)tbuf, "%08X  ", olbl);
    strcpy(szBuf, (char *)tbuf);

    // Format hex portion of line and save chars for ascii portion
    for (i = 0; i < len; i++)
    {
        c = *mem++;

        sprintf((char *)tbuf, "%02X ", c);
        strcat(szBuf, (char *)tbuf);

        if (c >= 32 && c < 127)
            buff[i] = c;
		  else
            buff[i] = 46;
    }

    j = dwid - i;

    buff[i] = 0;

    // Fill out hex portion of short lines.
    for (i = j; i > 0; i--)
        strcat(szBuf, "   ");

    // Add ascii portion to line.
    sprintf((char *)tbuf, " |%s|", (char *)buff);
    strcat(szBuf, (char *)tbuf);

	 // Fill out end of short lines.
    for (i = j; i > 0; i--)
        strcat(szBuf, " ");

    return(szBuf);
}

