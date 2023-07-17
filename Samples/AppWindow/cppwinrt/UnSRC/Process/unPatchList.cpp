/*

	unPatchBank - Image Overlay
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

/*#include "UNmemorymanager.h"

#include <windows.h>
#include <tlhelp32.h> // for the process snapshot
#include <vector>
#include <string>

#include <stdlib.h>
#include <tchar.h>*/

//#include "TCFind.h"
//#include "TCHexWindow.h"

#include "unPatchList.h"

bool (*FirstFunc)(int i_First, float i_Second);

bool FirstFunction(int i_First, float i_Second)
{
	return false;
};

namespace Point
{

unPatchList::unPatchList()
{
	FirstFunc = FirstFunction;
}

unPatchList::~unPatchList()
{
}

#if 0
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
#endif

#if 0
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
#endif

};