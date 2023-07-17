/*

	unPatchBank - Image Overlay
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

//#include "TCFind.h"
//#include "TCHexWindow.h"

#include "unPatchBank.h"

namespace Point
{

unPatchFunction::unPatchFunction()
{
}

unPatchFunction::~unPatchFunction()
{
}

unPatch::unPatch()
{
}

unPatch::~unPatch()
{
}

unPatchBank::unPatchBank()
{
}

unPatchBank::~unPatchBank()
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

void unPatchBank::acPush(std::string i_PatchName)
{
	std::string i_StrDll = ".dll";
	std::string i_StrTxt = ".xml";

	std::string i_PatchDll = i_PatchName + i_StrDll;
	std::string i_PatchInfo = i_PatchName + i_StrTxt;

	acInfo(i_PatchInfo.c_str());

	int patn = m_Patch.size() - 1;
	if(patn < 0)
		{
		printf("ERROR:::Patch INFO %s\n", i_PatchDll.c_str());
		for(;;) {}
		}

	m_Patch[patn]->m_hDll = LoadLibrary(i_PatchDll.c_str());
	if(m_Patch[patn]->m_hDll == NULL)
		{
		printf("ERROR:::File not found %s\n", i_PatchDll.c_str());
		for(;;) {}
		}

	printf("Point::Applied File %s\n", i_PatchName.c_str());

	LPFNDLLFUNC1 i_ProcAddr_Set_Avatar_GetBoneTransform;
	i_ProcAddr_Set_Avatar_GetBoneTransform = (LPFNDLLFUNC1)GetProcAddress(m_Patch[patn]->m_hDll, "acSet_Avatar_GetBoneTransform");
	LPFNDLLFUNC2 i_ProcAddr_Set_Transform_GetIn;
	i_ProcAddr_Set_Transform_GetIn = (LPFNDLLFUNC2)GetProcAddress(m_Patch[patn]->m_hDll, "acSet_Transform_GetIn");
	LPFNDLLFUNC3 i_ProcAddr_Set_Avatar_BlendPose;
	i_ProcAddr_Set_Avatar_BlendPose = (LPFNDLLFUNC3)GetProcAddress(m_Patch[patn]->m_hDll, "acSet_Avatar_BlendPose");
	//LPFNDLLFUNC4 i_ProcAddr_Set_TrailLineCreate;
	//i_ProcAddr_Set_TrailLineCreate = (LPFNDLLFUNC4)GetProcAddress(m_Patch[patn]->m_hDll, "acSet_TrailLineCreate");

	if(i_ProcAddr_Set_Avatar_GetBoneTransform == NULL) printf("error 1 <null>\n");
	if(i_ProcAddr_Set_Transform_GetIn == NULL) printf("error 2 <null>\n");
	if(i_ProcAddr_Set_Avatar_BlendPose == NULL) printf("error 3 <null>\n");
	//if(i_ProcAddr_Set_TrailLineCreate == NULL) printf("error 4 <null>\n");

	i_ProcAddr_Set_Transform_GetIn(Qpo->Transform_GetIn);
	i_ProcAddr_Set_Avatar_BlendPose(Qpo->Avatar_BlendPose);
	i_ProcAddr_Set_Avatar_GetBoneTransform(Qpo->Avatar_GetBoneTransform);

	Q_COREFunctions *Qset = new Q_COREFunctions();

	//i_ProcAddr_Set_TrailLineCreate(Qset->TrailLineCreate);

	LPFNDLLFUNC4 i_ProcAddr_Set_Avatar_GetBoneTransform2;
	i_ProcAddr_Set_Avatar_GetBoneTransform2 = (LPFNDLLFUNC4)GetProcAddress(m_Patch[patn]->m_hDll, "acSet_TrailLineCreate");

	i_ProcAddr_Set_Avatar_GetBoneTransform2(Qset->TrailLineCreate);

	//FreeLibrary(m_Patch[patn]->m_hDll);

	// Load the UrlMon library
	//m_Patch[patn]->m_hDll = LoadLibrary(_T("UrlMon"));

	// Get the download-to-file-cache function
	//LPURLDOWNLOAD m_lpUrlDownload = (LPURLDOWNLOAD)GetProcAddress(m_Patch[patn]->m_hDll,"URLDownloadToCacheFileA");

	//typedef void (CALLBACK* LPFNDLLFUNC5)(void (*)(void));
	LPFNDLLFUNC5 i_ProcAddr_MidShift;
	i_ProcAddr_MidShift = (LPFNDLLFUNC5)GetProcAddress(m_Patch[patn]->m_hDll, (LPCSTR)"MidShift");

	//i_ProcAddr_MidShift();
	//i_ProcAddr_MidShift();
	//i_ProcAddr_MidShift();
	//i_ProcAddr_MidShift();
	//i_ProcAddr_MidShift();
	if(i_ProcAddr_MidShift == NULL) printf("error <null>\n");

	LPFNDLLFUNC7 i_ProcAddr_Set_GlobalStruct;
	i_ProcAddr_Set_GlobalStruct = (LPFNDLLFUNC7)GetProcAddress(m_Patch[patn]->m_hDll, (LPCSTR)"acSet_GlobalStruct");
	LPFNDLLFUNC8 i_ProcAddr_Set_playerAV;
	i_ProcAddr_Set_playerAV = (LPFNDLLFUNC8)GetProcAddress(m_Patch[patn]->m_hDll, (LPCSTR)"acSet_playerAV");
	LPFNDLLFUNC9 i_ProcAddr_Set_player;
	i_ProcAddr_Set_player = (LPFNDLLFUNC9)GetProcAddress(m_Patch[patn]->m_hDll, (LPCSTR)"acSet_player");

	//if(i_ProcAddr_Set_GlobalStruct == NULL) printf("error 7 <null>\n");
	//if(i_ProcAddr_Set_playerAV == NULL) printf("error 8 <null>\n");
	//if(i_ProcAddr_Set_player == NULL) printf("error 9 <null>\n");

	i_ProcAddr_Set_GlobalStruct(_);
	i_ProcAddr_Set_playerAV(playerAV);
	i_ProcAddr_Set_player(player);

	printf("finish\n");
	for(;;) {}
}

void unPatchBank::acInfo(const char* i_Filename)
{
	FILE			*i_stream;

	errno_t i_err = fopen_s(&i_stream, i_Filename, "r");

	if(i_err)
		{
		printf("ERROR:::file not found %s\n", i_Filename);
		for(;;) {}
		}

	char i_cursor = ' ';
	std::string i_tag;

	//Cursor Seek
	while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
	fscanf_s( i_stream, "%c", &i_cursor, 1 );

	// Cursor Read
	while(i_cursor != '>')
		{
		i_tag.push_back(i_cursor);
		fscanf_s( i_stream, "%c", &i_cursor, 1 );
		}

	if(i_tag.compare("XML") != 0)
		{
		printf("ERROR:::XML definitions file corrupt\n");
		for(;;) {}
		}

	while(i_tag.compare("/XML") != 0)
		{
		// Extract XML Tag ////////////////////////////
		//Cursor Seek
		while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
		fscanf_s( i_stream, "%c", &i_cursor, 1 );

		// Cursor Read
		i_tag.clear();
		while(i_cursor != '>')
			{
			i_tag.push_back(i_cursor);
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			}
		///////////////////////////////////////////////

		if(i_tag.compare("Patch") == 0)
			{
			unPatch * i_Patch = new unPatch();

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Title") == 0)
				{
				// Cursor Read
				m_Attribute.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '<')
					{
					m_Attribute.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				i_Patch->m_Title = m_Attribute;
				}

			//// Cursor Read //////////////////////////////
			i_tag.clear();
			i_cursor = '<';
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Author") == 0)
				{
				// Cursor Read
				m_Attribute.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '<')
					{
					m_Attribute.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				i_Patch->m_Author = m_Attribute;
				}

			//// Cursor Read //////////////////////////////
			i_tag.clear();
			i_cursor = '<';
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Version") == 0) fscanf_s( i_stream, "%f", &i_Patch->m_Version, 1 );

			//// Cursor Read //////////////////////////////
			i_tag.clear();
			i_cursor = '<';
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Category") == 0)
				{
				// Cursor Read
				m_Attribute.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '<')
					{
					m_Attribute.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				i_Patch->m_Category = m_Attribute;
				}

			//// Cursor Read //////////////////////////////
			i_tag.clear();
			i_cursor = '<';
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Filename") == 0)
				{
				// Cursor Read
				m_Attribute.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '<')
					{
					m_Attribute.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				i_Patch->m_Filename = m_Attribute;
				}

			//// Cursor Read //////////////////////////////
			i_tag.clear();
			i_cursor = '<';
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("FunctionList") == 0)
				{
				// Extract XML Tag ////////////////////////////
				//Cursor Seek
				while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
				fscanf_s( i_stream, "%c", &i_cursor, 1 );

				// Cursor Read
				i_tag.clear();
				while(i_cursor != '>')
					{
					i_tag.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				///////////////////////////////////////////////

				if(i_tag.compare("Count") == 0) fscanf_s( i_stream, "%i", &i_Patch->m_Count, 1 );

				//// Cursor Read //////////////////////////////
				i_tag.clear();
				i_cursor = '<';
				while(i_cursor != '>')
					{
					i_tag.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				///////////////////////////////////////////////

				for(int i_itercom = 0; i_itercom < i_Patch->m_Count; i_itercom++)
					{
					// Extract XML Tag ////////////////////////////
					//Cursor Seek
					while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
					fscanf_s( i_stream, "%c", &i_cursor, 1 );

					// Cursor Read
					i_tag.clear();
					while(i_cursor != '>')
						{
						i_tag.push_back(i_cursor);
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						}
					///////////////////////////////////////////////

					if(i_tag.compare("Function") == 0)
						{
						unPatchFunction * i_Function = new unPatchFunction();

						// Extract XML Tag ////////////////////////////
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						if(i_tag.compare("ClsCont") == 0)
							{
							// Cursor Read
							m_Attribute.clear();
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							while(i_cursor != '<')
								{
								m_Attribute.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}

							i_Function->m_StrAdd = m_Attribute;
							}

						//// Cursor Read //////////////////////////////
						i_tag.clear();
						i_cursor = '<';
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						// Extract XML Tag ////////////////////////////
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						if(i_tag.compare("StrID") == 0)
							{
							// Cursor Read
							m_Attribute.clear();
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							while(i_cursor != '<')
								{
								m_Attribute.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}

							i_Function->m_StrID = m_Attribute;
							}

						//// Cursor Read //////////////////////////////
						i_tag.clear();
						i_cursor = '<';
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						// Extract XML Tag ////////////////////////////
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						if(i_tag.compare("RetCnt") == 0) { fscanf_s( i_stream, "%i", &i_Function->m_RetCount, 1 ); }

						//// Cursor Read //////////////////////////////
						i_tag.clear();
						i_cursor = '<';
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						// Extract XML Tag ////////////////////////////
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						if(i_tag.compare("ArgCnt") == 0) { fscanf_s( i_stream, "%i", &i_Function->m_ArgCount, 1 ); }

						//// Cursor Read //////////////////////////////
						i_tag.clear();
						i_cursor = '<';
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						for(int i_iterret = 0; i_iterret < i_Function->m_RetCount; i_iterret++)
							{
							// Extract XML Tag ////////////////////////////
							//Cursor Seek
							while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
							fscanf_s( i_stream, "%c", &i_cursor, 1 );

							// Cursor Read
							i_tag.clear();
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////

							if(i_tag.compare("Ret") == 0)
								{
								// Cursor Read
								m_Attribute.clear();
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								while(i_cursor != '<')
									{
									m_Attribute.push_back(i_cursor);
									fscanf_s( i_stream, "%c", &i_cursor, 1 );
									}

								i_Function->m_Ret.push_back(m_Attribute);
								}

							//// Cursor Read //////////////////////////////
							i_tag.clear();
							i_cursor = '<';
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////
							}

						for(int i_iterarg = 0; i_iterarg < i_Function->m_ArgCount; i_iterarg++)
							{
							// Extract XML Tag ////////////////////////////
							//Cursor Seek
							while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
							fscanf_s( i_stream, "%c", &i_cursor, 1 );

							// Cursor Read
							i_tag.clear();
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////

							if(i_tag.compare("Arg") == 0)
								{
								// Cursor Read
								m_Attribute.clear();
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								while(i_cursor != '<')
									{
									m_Attribute.push_back(i_cursor);
									fscanf_s( i_stream, "%c", &i_cursor, 1 );
									}

								i_Function->m_Arg.push_back(m_Attribute);
								}

							//// Cursor Read //////////////////////////////
							i_tag.clear();
							i_cursor = '<';
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////
							}

						// Extract XML Tag ////////////////////////////
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						///////////////////////////////////////////////

						if(i_tag.compare("/Function") != 0)
							{
							printf("ERROR:::XML definitions file corrupt at command end\n");
							for(;;) {}
							}

						i_Patch->m_Function.push_back(i_Function);

						std::vector<unPatchFunction*> * vec_PatchFunction;

						if(map_Function.find(i_Function->m_StrAdd.c_str()) == map_Function.end())
							{
							vec_PatchFunction = new std::vector<unPatchFunction*>();
							vec_PatchFunction->push_back(i_Function);
							}
						else
							{
							vec_PatchFunction = map_Function[i_Function->m_StrAdd.c_str()];
							vec_PatchFunction->push_back(i_Function);
							}
						}
					}

				// Extract XML Tag ////////////////////////////
				//Cursor Seek
				while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
				fscanf_s( i_stream, "%c", &i_cursor, 1 );

				// Cursor Read
				i_tag.clear();
				while(i_cursor != '>')
					{
					i_tag.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				///////////////////////////////////////////////

				if(i_tag.compare("/FunctionList") != 0)
					{
					printf("ERROR:::XML definitions file corrupt at command end\n");
					for(;;) {}
					}
				}

			// Extract XML Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("/Patch") != 0)
				{
				printf("ERROR:::XML definitions file corrupt at command end\n");
				for(;;) {}
				}

			m_Patch.push_back(i_Patch);
			}
		}

	printf("unPatchBank:::XML:::Patch prepared...\n XML %i Patches\n", m_Patch.size());

	fclose(i_stream);
}

};