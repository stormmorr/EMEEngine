/*

	Memory Management
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "UNmemorymanager.h"

#include <windows.h>
#include <tlhelp32.h> // for the process snapshot
#include <vector>
#include <string>

#include <stdlib.h>
#include <tchar.h>
#include "TCFind.h"
#include "TCHexWindow.h"

UNmemorymanager::UNmemorymanager(HWND i_Window)
{
	hWindow = i_Window;
	walkObj.mGetPageList(0);
}

UNmemorymanager::~UNmemorymanager()
{

}

UNfunction::UNfunction()
{
	
}

UNfunction::UNfunction(unsigned int i_Size)
{
	m_Size = i_Size;
	m_Pointer = (int*)malloc(i_Size*sizeof(int));
	m_Address = &m_Pointer;

#if UN_PROCESS_Media->MESSAGES
	printf("UNprocess:::Create UNfunction at >>> m_Address %i\n", m_Address);
#endif
}

UNfunction::~UNfunction()
{

}

void UNfunction::realloc(size_t i_Size)
{

}

void UNmemorymanager::addFunction(unsigned int i_Size)
{
	if(searchSpace(i_Size) == -1)	// Space not found allocate new
		{
		UNfunction *i_Function = new UNfunction(i_Size);
		m_Function.push_back(i_Function);
		}
	//else							// Fill the space
	//	{

}

void UNmemorymanager::removeFunction(unsigned int i_Iter)
{
	UNspace *i_Space = new UNspace;
	i_Space->m_VecPointer = i_Iter;
	i_Space->m_Size = m_Function[i_Iter]->m_Size;
	m_Space.push_back(i_Space);
}

void UNmemorymanager::replaceFunction()
{

}

int UNmemorymanager::searchSpace(unsigned int i_Size)
{
	for(unsigned int i_Iter = 0; i_Iter < m_Space.size(); i_Iter++)
		if(m_Space[i_Iter]->m_Size <= i_Size) return i_Iter;
	return -1;
}

string UNmemorymanager::acDumpAssembly(void)
{
	string strPlayerName;
	char charPlayerName[32];

	//HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
	//ReadProcessMemory(hProcess, (LPVOID)(dwModBase + Player name offset), &charPlayerName, sizeof(charPlayerName), NULL);

	//CloseHandle(hProcess); // close handle
	       
	strPlayerName = charPlayerName;
	return(strPlayerName);
}

int UNmemorymanager::actestmemory(void)
{
	DWORD dwAddress;
	int value;
	//ReadProcessMemory(hFFXI, (LPVOID)(dwModBase + offset), &dwAddress, sizeof(dwAddress), NULL);
	//dwAddress = dwAddress + anotherOffset;
	//ReadProcessMemory(hFFXI, (LPVOID)(dwAddress ), &value, sizeof(value), NULL);
	return 1;
}

bool UNmemorymanager::acReadMemory(DWORD i_Address, unsigned int i_Size)
{
	void * i_Buffer = new char[15];
	//char const* i_Buffer = new char[500];
	SIZE_T *nom_Bytes = 0;

	if(!AdjustPrivileges())
		{
		MessageBox(NULL,
			"Can't adjust priveldges",
			"Error",
			MB_OK);
		}

	//int *i_Buffer = new int[i_Size];

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, lok_PID);

	printf("ReadProcessMemory %i\n", ReadProcessMemory(hProcess, (LPVOID)(lok_Base+5000), &i_Buffer, 5, nom_Bytes));

	CloseHandle(hProcess); // close handle

	//printf("%ul Bytes Read\n", nom_Bytes);
	//printf("Memory Dump::: %c\n", i_Buffer);

	return true;
}

DWORD UNmemorymanager::acFindModule(const char *i_ProcessName)
{
	DWORD dwPID; // ProssesID
	DWORD dwPolBase; // Unification.exe base address
	DWORD dwModBase; // FFXiMain.dll base address

	HANDLE   hProcessSnap;
	HANDLE   hModuleSnap;
	PROCESSENTRY32   pe32;
	MODULEENTRY32   me32;

	//** Time to locate 'unification.exe'
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
		MessageBox(0, "Error Invalid handle value","Error!", MB_OK);    
		}
	else
		{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &pe32) == NULL)
			{
			//** Error
			CloseHandle(hProcessSnap); //** Close handle, don't forget to do this or you'll have a memory leak!
			}
		else
			{
			do
				{
				if(_stricmp(pe32.szExeFile, i_ProcessName) == 0)// process entry file name = pol.exe
					{
					// FFXI found, get the pID which is stored in our PROCESSENTRY32 structure
					dwPID = pe32.th32ProcessID;

					//** Time to locate FFXiMain.dll inside pol.exe
					hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);

					if(hModuleSnap == INVALID_HANDLE_VALUE)
						{
						// Error
						CloseHandle(hProcessSnap);
						CloseHandle(hModuleSnap);
						}
					else
						{
						me32.dwSize = sizeof(MODULEENTRY32);
						if(Module32First(hModuleSnap, &me32) == NULL)
							{
							// Error
							CloseHandle(hModuleSnap);
							}
						else
							{
							do
								{
								if(_stricmp(me32.szModule, i_ProcessName) == 0)
									{
									// Found pol.exe, let's save it's base.
									dwPolBase = (DWORD)me32.modBaseAddr;
									}
#if 0
								else if(_stricmp(me32.szModule, "FFXiMain.dll") == 0)
									{
									// Found FFXiMain.dll!  Time to save it's base address
									dwModBase = (DWORD)me32.modBaseAddr;
									}
#endif
			       
								} while(Module32Next(hModuleSnap, &me32));

							CloseHandle(hModuleSnap);   // Close handle to module snapshot
							}
						}
					}
				} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);   //** Close handle to process snapshot
			}
		}
	return dwPolBase;
}

void UNmemorymanager::acLockModule(const char *i_ProcessName)
{
	DWORD dwPID;		// ProssesID
	DWORD dwPolBase;	// Base Address

	HANDLE   hProcessSnap;
	HANDLE   hModuleSnap;
	PROCESSENTRY32   pe32;
	MODULEENTRY32   me32;

	//** Time to locate 'unification.exe'
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
		MessageBox(0, "Error Invalid handle value","Error!", MB_OK);    
		}
	else
		{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &pe32) == NULL)
			{
			//** Error
			CloseHandle(hProcessSnap); //** Close handle, don't forget to do this or you'll have a memory leak!
			}
		else
			{
			do
				{
				if(_stricmp(pe32.szExeFile, i_ProcessName) == 0)// process entry file name = pol.exe
					{
					// FFXI found, get the pID which is stored in our PROCESSENTRY32 structure
					dwPID = pe32.th32ProcessID;

					//** Time to locate FFXiMain.dll inside pol.exe
					hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);

					if(hModuleSnap == INVALID_HANDLE_VALUE)
						{
						// Error
						CloseHandle(hProcessSnap);
						CloseHandle(hModuleSnap);
						}
					else
						{
						me32.dwSize = sizeof(MODULEENTRY32);
						if(Module32First(hModuleSnap, &me32) == NULL)
							{
							// Error
							CloseHandle(hModuleSnap);
							}
						else
							{
							do
								{
								if(_stricmp(me32.szModule, i_ProcessName) == 0)
									{
									// Found pol.exe, let's save it's base.
									dwPolBase = (DWORD)me32.modBaseAddr;
									}

								} while(Module32Next(hModuleSnap, &me32));

							CloseHandle(hModuleSnap);   // Close handle to module snapshot
							}
						}
					}
				} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);   //** Close handle to process snapshot
			}
		}

	lok_PID = dwPID;		// Lock ProssesID
	lok_Base = dwPolBase;	// Lock Base Address

	if(!AdjustPrivileges()) MessageBox(NULL, "Can't adjust priveldges", "Error", MB_OK);

	printf("MeM:::Lock Process PID %ul BaseAddr %ul\n", lok_PID, lok_Base);
}

bool UNmemorymanager::AdjustPrivileges(void)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	TOKEN_PRIVILEGES oldtp;
	DWORD dwSize = sizeof(TOKEN_PRIVILEGES);
	LUID luid;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
			return true;
		return false;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
	{
		CloseHandle(hToken);
		return false;
	}

	ZeroMemory(&tp, sizeof(tp));
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	/* Adjust Token Privileges */
	if (!AdjustTokenPrivileges (hToken, false, &tp, sizeof(TOKEN_PRIVILEGES), &oldtp, &dwSize))
	{
		CloseHandle(hToken);
		return false;
	}
	// close handles
    CloseHandle(hToken);

	return true;
}

LRESULT UNmemorymanager::acMemWalk(void)
{
	DWORD dwProcessID;
	char WindowText[256];
	int iPages;

#if 0
	if(hWndToOpen) 
		{
		GetWindowThreadProcessId(hWndToOpen, &dwProcessID);
#endif
		// Get Process Handle
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, lok_PID);

		//Map the address space
		walkObj.memWalk(hProcess);
		walkObj.mGetPageList(&iPages);

		//Fill display memory 
		//FillDisplay(0);

		// Show other window title in this window's caption.
		//GetWindowText(hWndToOpen, (char*)WindowText, 255);
		//printf(gWindow.szPaint, "%s - %s (%i)", this->szWinTitle, WindowText, iPages);
		//SetWindowText(this->m_hWnd, gWindow.szPaint);

		//Setup scroll bars
		//m_hScroll.mSetup(m_hWnd, this->GetChWidth() * m_fontx, this->m_ClientWidth, m_fontx);
		//m_vScroll.mSetup(m_hWnd, iPages, m_ClientHeight- m_fonty, m_fonty);

		//Init find ptr to top of memory
		//lFindPageNo = 0l;
		//lFindOff = 0l;
		//InvalidateRect(this->m_hWnd, NULL, true);
		//UpdateWindow(this->m_hWnd);
#if 0
		}
#endif
	return 0l;
}

LRESULT UNmemorymanager::OnFind(const char *i_FindChar)
{
	int iPages, notFound, iUnReadable, i;
	TCFind findIt;
	DWORD dwOffset;
	TCHAR szMsg[100];
	long lOff, newlOff;
	wchar_t szConverted[180];
	int iLen;
	LPVMOBJECT pPage;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, lok_PID);

	//Closing - reset search pointers
	lFindPageNo = 0l;
	lFindOff = 0l;

	pPage = walkObj.mGetPageList(&iPages);
	strcpy((char *)szConverted, i_FindChar);
	iLen = strlen(i_FindChar);
	//Convert string if necessary
#ifdef UNICODE
	mbstowcs(szConverted, lpfr->lpstrFindWhat, 180);
	iLen *= sizeof(wchar_t);
#endif

	notFound = true;
	while(lFindPageNo < iPages)
		{
		pPage = walkObj.mGetPageList(&iPages);
		pPage += lFindPageNo ;
		iUnReadable = 0;
		iUnReadable |= (pPage->mbi.State == MEM_FREE);;
		iUnReadable |= (pPage->mbi.State == MEM_RESERVE);
		iUnReadable |= (pPage->mbi.Protect & PAGE_WRITECOPY);
		iUnReadable |= (pPage->mbi.Protect & PAGE_EXECUTE);
		iUnReadable |= (pPage->mbi.Protect & PAGE_GUARD);
		iUnReadable |= (pPage->mbi.Protect & PAGE_NOACCESS);

		//Load and search it
		if(!iUnReadable)
			{
			trBuffer.mInit(hProcess, pPage->mbi, 0x10000);

			i = (int)(lFindOff/ trBuffer.m_lBufferSize);
			while(trBuffer.mLoad(i) > 0)
				{
				if(lFindOff > 0)
					lOff = lFindOff - (i * trBuffer.m_lBufferSize);
				else
					lOff = 0;
				newlOff = findIt.iFind((char *)trBuffer.m_lpBuffer+lOff,trBuffer.m_lBytesInBuffer-lOff, (char *)szConverted, iLen);
				if(newlOff > 0)
					{
					dwOffset = (DWORD)(newlOff + lOff);
					dwOffset += (i * trBuffer.m_lBufferSize);
					//Start next search at next byte
					lFindOff = (long)dwOffset + 1;
					printf("%s found at %08lx Base::offset %08lx:%08lx\n", i_FindChar, (DWORD)pPage->mbi.BaseAddress + dwOffset, pPage->mbi.BaseAddress, dwOffset);
					return 0l;
					}

				TCHAR szBuffer[180];
				for(i=0; i < 16; i++)
					{
					//lpData = (LPVOID)((DWORD)trBuffer.m_lpBuffer + lAddress);
					SnapLine(szBuffer, (char *)trBuffer.m_lpBuffer + (i * 16), 16, 16, ((char *)346));
					//SnapLine(szBuffer, (char *)lpData, 16, 16, ((char *)i_Address + lAddress));
					printf("%s\n", szBuffer);
					}

				//Didn't find reset offsets
				lOff = 0;
				lFindOff = 0l;
				++i;
				}
			}
		++lFindPageNo;
		}

	//End of memory : reset and return
	printf("%s not found in %li pages.\n", i_FindChar, lFindPageNo);
	lFindPageNo = 0l;
	lFindOff = 0l;

	CloseHandle(hProcess);

	return 0l;
}

LRESULT UNmemorymanager::acMemoryDump(DWORD i_Address, unsigned int i_Length)
{
	TCHAR szBuffer[180];
	int i, iChWidth, iLenBuffer;
	DWORD lAddress;
	LPVOID lpData;
	LPVMOBJECT pPage;
	int iPages;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, lok_PID);

	pPage = walkObj.mGetPageList(&iPages);

	trBuffer.mInit(hProcess, pPage->mbi, 0x10000);

	i = (int)(0 / trBuffer.m_lBufferSize);
	trBuffer.mLoad(0);

	printf("%s\n", (char *)trBuffer.m_lpBuffer);

#if 0
	lOff = lFindOff - (i * trBuffer.m_lBufferSize);
	newlOff = findIt.iFind((char *)trBuffer.m_lpBuffer+lOff,trBuffer.m_lBytesInBuffer-lOff, (char *)szConverted, iLen);
#endif


	lAddress = 0;
	for(i=0; i < i_Length; i++)
		{
		lpData = (LPVOID)((DWORD)trBuffer.m_lpBuffer + lAddress);
		SnapLine(szBuffer, (char *)trBuffer.m_lpBuffer, 16, 16, ((char *)i_Address + lAddress));
		//SnapLine(szBuffer, (char *)lpData, 16, 16, ((char *)i_Address + lAddress));
		iLenBuffer = strlen(szBuffer);
		printf("%s\n", szBuffer);
		lAddress += 16;
		}

	CloseHandle(hProcess);

	return 0l;
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
char *UNmemorymanager::SnapLine(char *szBuf, LPSTR mem, int len, int dwid, char *olbl)
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
    for (i = j; i > 0; i--) strcat(szBuf, "   ");

    // Add ascii portion to line.
    sprintf((char *)tbuf, " |%s|", (char *)buff);
    strcat(szBuf, (char *)tbuf);

	 // Fill out end of short lines.
    for (i = j; i > 0; i--) strcat(szBuf, " ");

    return(szBuf);
}