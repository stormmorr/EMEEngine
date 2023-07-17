/*

    Web Tumbler - Tumble Files Downloaded from the Internet
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

/////// Includes ///////
#include <windows.h>
#include <urlmon.h>
#include "resource.h"
#include "masterstring.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "TumDocument.h"

#if 1
#define DOWNLOAD_SEARCH
#endif

#if 0
#define DONT_DOWNLOAD_SEARCH
#endif

#define NOM_DOWNLOAD 5

#pragma message("FIXME:::Optimisation suggestions:::Remove getResults call to improve speed")

#define BGO 12
// programs important varaibles
HFONT  prog_font = CreateFont(16,0,0,0,FW_DONTCARE,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_MODERN,"Arial");
HINSTANCE hInst;
HWND      hwnd;
HWND      edit;
HWND      bgo; // button go
HWND      html_view;
WNDPROC   oldproc;
char*	  filebuffer;

// callback functions
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
// useful functions
inline void Init(void);
inline void SetMyFont(HWND hwnd);

// go get it 
void onGet(void);
bool onPrint(void);

FILE *stream;

int	caseinc;
int	pageinc;
int	inc;

#pragma message("FIXME:::Temporary DocuFrame Structure")

// Vector of documents
std::vector<TumDocument*> vecDocuments;

int APIENTRY WinMain(HINSTANCE hInstx,HINSTANCE hPrev,LPSTR line,int CmdShow)
{
	MSG msg;

	hInst = hInstx;
	Init();

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// initlize
inline void Init(void)
{
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) MainProc;
	wc.lpszClassName = "MasterURL";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hwnd = CreateWindow("MasterURL","Tumbler",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,250,250,0,0,hInst,0);

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
}
// set the font
inline void SetMyFont(HWND hwnd)
{
	SendMessage(hwnd,WM_SETFONT,(WPARAM)prog_font,0);
}

// main callback
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			HWND st;
			HWND st2;
			st = CreateWindow("Static","Enter the Search Term ",WS_CHILD | WS_VISIBLE,5,5,200,20,hwnd,0,hInst,0);
			edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit","",WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,5,25,200,20,hwnd,0,hInst,0);
			bgo = CreateWindow("Button","Get!",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,205,25,35,20,hwnd,(HMENU)BGO,hInst,0);
			st2 = CreateWindow("Static","Downloaded HTML",WS_CHILD | WS_VISIBLE ,5,25+20+5,200,20,hwnd,0,hInst,0);
			html_view = CreateWindowEx(WS_EX_STATICEDGE,"Edit",NULL,WS_CHILD |  ES_READONLY | WS_VISIBLE | ES_MULTILINE | WS_BORDER |  WS_VSCROLL,5,25+20+5+20+5,230,140,hwnd,0,hInst,0);

			oldproc = (WNDPROC) SetWindowLong(edit,GWL_WNDPROC,(LONG)(WNDPROC)EditProc);

			SetMyFont(html_view);
			SetMyFont(st2);
			SetMyFont(bgo);
			SetMyFont(edit);
			SetMyFont(st);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			
			
		}
		break;
	case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
			case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
					case BGO:
						{
							SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"downloading..");

							onGet();
						}
						break;
					}
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
// edit callback
LRESULT APIENTRY EditProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_RETURN:
				{
						SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"downloading..");

					onGet();
				}
				break;
			}
		}
		break;
	default: return CallWindowProc(oldproc,hwnd,msg,wParam,lParam);
	}
	return 0;
}
// go get it
void onGet()
{
	int pagecnt = 0;
	char searchterm[200];
	SendMessage(edit,WM_GETTEXT,200,(LPARAM)(LPCSTR)searchterm);
	UpdateWindow(hwnd);

#if 0
	//"http://www.google.co.uk/search?q=hentai+filetype:swf&hl=en&start=0&sa=N"
#endif

	for (int y=0; y < NOM_DOWNLOAD; ++y)
		{
		char pagecntbuf[100];
		itoa(pagecnt, pagecntbuf, 10);

		////// Generate Search Request
		std::string strinitiator = "http://www.google.co.uk/search?q=";
		std::string strterm = searchterm;
		std::string strfiletype = "+filetype:swf&hl=en&start=";
		std::string strpagecntbuff = pagecntbuf;
		std::string strterminator = "&sa=N";
		std::string searchURL = strinitiator + searchterm + strfiletype + strpagecntbuff + strterminator;

		////// Generate File Name
		std::string strpath = "Results/";
		std::string strhtmlterm = ".html";
		std::string strFilename = strpath + strterm + strpagecntbuff + strhtmlterm;

#ifdef DOWNLOAD_SEARCH
		if(URLDownloadToFile(0, searchURL.c_str(), strFilename.c_str(), 0, 0))
			{
			MessageBox(hwnd,"Error:\nFile Not Found or you are offline","Error",MB_OK | MB_ICONERROR);
			SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Tumble Tumbler");
			return;
			}
		else
			{
#endif
			filebuffer = new char[getfilestringlength((char*)strFilename.c_str())+20];
			strloadfile((char*)strFilename.c_str(),filebuffer);

			/////// Tumble Document
			TumDocument* TDocument = new TumDocument(strterm, filebuffer);
			TDocument->hwnd = hwnd;
			TDocument->addBlocker("[FLASH]", 40);
			TDocument->addExtractor(".swf", 40, 0);
			TDocument->Tumble();
			//TDocument->PrintResults();
			vecDocuments.push_back(TDocument);

			SendMessage(html_view,WM_SETTEXT,strlen(filebuffer),(LPARAM)(LPCSTR)TDocument->getResults());
			delete [] filebuffer;
			SendMessage(hwnd,WM_SETTEXT,255,(LPARAM)(LPCSTR)"File Tumbler");
#ifdef DOWNLOAD_SEARCH
			}
#endif

		///// Increment PageCount
		pagecnt+=10;
		}

	// Print Formatted Results
	onPrint();
}

bool onPrint(void)
{
	char casecntbuf[100];
	caseinc = 0;

	///// Generate Filename
	std::string strpath = "Output\\";
	std::string strtype = ".txt";
	std::string strFilename = strpath + vecDocuments[0]->m_Name + strtype;

	//##### - Open our Character Data File
	stream = fopen(strFilename.c_str(), "w");

	//##### - Clarify File Status
	fprintf(stream, "// OSIREM::FileTumbler Output\n// Output formatted for Quadrix Gate\n\n");

	fprintf(stream, "// Security Clearance\n\n");

	fprintf(stream, "switch(fingerSWF)\n");
	fprintf(stream, "    {\n");

	for(pageinc = 0; pageinc < vecDocuments.size(); pageinc++)
		{
		for(inc = 0; inc < vecDocuments[pageinc]->vecResults.size(); inc++)
			{
			itoa(caseinc, casecntbuf, 10);

			////// Generate Case Value
			std::string strinitiator = "    case ";
			std::string strterminator = ":\n";
			std::string strcasecntbuff = casecntbuf;
			std::string casevalue = strinitiator + strcasecntbuff + strterminator;

			fprintf(stream, casevalue.c_str());
			fprintf(stream, "        {\n");
			fprintf(stream, "        System.security.allowDomain(\"");
			if(vecDocuments[pageinc]->vecResults[inc].length() > 0) fprintf(stream, "%s", vecDocuments[pageinc]->vecResults[inc].c_str());
			fprintf(stream, "\", 2);\n");
			fprintf(stream, "        }break;\n");

			caseinc++;
			}
		}

	fprintf(stream, "    }\n");

	fprintf(stream, "\n// Load Movie\n\n");

	fprintf(stream, "switch(fingerSWF)\n");
	fprintf(stream, "    {\n");

	caseinc = 0;
	for(pageinc = 0; pageinc < vecDocuments.size(); pageinc++)
		{
		for(inc = 0; inc < vecDocuments[pageinc]->vecResults.size(); inc++)
			{
			itoa(caseinc, casecntbuf, 10);

			////// Generate Case Value
			std::string strinitiator = "    case ";
			std::string strterminator = ":\n";
			std::string strcasecntbuff = casecntbuf;
			std::string casevalue = strinitiator + strcasecntbuff + strterminator;

			fprintf(stream, casevalue.c_str());
			fprintf(stream, "        {\n");
			fprintf(stream, "        loadMovieNum(\"");
			if(vecDocuments[pageinc]->vecResults[inc].length() > 0) fprintf(stream, "%s", vecDocuments[pageinc]->vecResults[inc].c_str());
			fprintf(stream, "\", 2);\n");
			fprintf(stream, "        }break;\n");

			caseinc++;
			}
		}

	fprintf(stream, "    }\n");

	fclose(stream);

	return true;
}