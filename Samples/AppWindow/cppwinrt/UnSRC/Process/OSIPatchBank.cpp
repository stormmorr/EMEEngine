/*

	OSIPatchBank - Image Overlay
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "UNmemorymanager.h"

#include <windows.h>
#include <tlhelp32.h> // for the process snapshot
#include <vector>
#include <string>

#include <stdlib.h>
#include <tchar.h>

#include "OSIPatchBank.h"

namespace Point
{

OSIPatchBank::OSIPatchBank()
{
}

OSIPatchBank::~OSIPatchBank()
{
}

void OSIPatchBank::acPush(std::string i_PatchName)
{
	//printf("File %s\n", i_PatchName.c_str());

	//std::string i_StrDll = ".dll";
	//std::string i_StrTxt = ".xml";

	//std::string i_PatchDll = i_PatchName + i_StrDll;
	//std::string i_PatchInfo = i_PatchName + i_StrTxt;

#if 0
	acInfo(i_PatchInfo.c_str());
#endif

	std::string i_PatchDll = "Patch\\OSIPat00001_Function.dll";

	HMODULE i_hDll = LoadLibrary("Patch\\OSIPat00001_Function.dll");
	if(i_hDll == NULL)
		{
		printf("ERROR:::File not found %s\n", i_PatchDll.c_str());
		for(;;) {}
		}

	printf("Point::Applied File %s\n", i_PatchDll.c_str());

	LPFNDLLFUNC10 i_ProcAddr_dllmain;
	i_ProcAddr_dllmain = (LPFNDLLFUNC10)GetProcAddress(i_hDll, "dllmain");

	if(i_ProcAddr_dllmain == NULL) printf("error 1 <null>\n");

	float i_result = i_ProcAddr_dllmain(1, 5, 5, 5);

#if 0
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
#endif

	printf("finish\n");
	for(;;) {}
}

#if 0
void OSIPatchBank::acInfo(const char* i_Filename)
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

	printf("OSIPatchBank:::XML:::Patch prepared...\n XML %i Patches\n", m_Patch.size());

	fclose(i_stream);
}
#endif

};