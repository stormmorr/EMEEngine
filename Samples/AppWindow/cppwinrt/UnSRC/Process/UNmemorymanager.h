/*

	Memory Management
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/
#include <windows.h>
#include <tlhelp32.h> // for the process snapshot
#include <vector>
#include <string>

#include "TCTraverse.h"
#include "MemWalk.h"

using namespace std;
using std::string;

class UNfunction
{
public:
	UNfunction();
	UNfunction(unsigned int i_Size);
	~UNfunction();

	int *m_Pointer;
	int **__w64 m_Address;
	unsigned int m_Size;

	void realloc(size_t i_Size);
};

typedef struct UNspace
{
	unsigned int m_VecPointer;
	unsigned int m_Size;
} UNspace;

class UNmemorymanager
{
public:
	UNmemorymanager(HWND i_Window);
	~UNmemorymanager();

	//--// UNprocess Pointer Allocation //--//

	void addFunction(unsigned int i_Size);
	void removeFunction(unsigned int i_Iter);
	void replaceFunction(void);

	int searchSpace(unsigned int i_Size);

	LRESULT acMemoryDump(DWORD i_Address, unsigned int i_Length);
	LRESULT acMemWalk(void);
	LRESULT OnFind(const char *i_FindChar);

	//--// Real Memory Manipulation //--//

	bool acReadMemory(DWORD i_Address, unsigned int i_Size);
	DWORD acFindModule(const char *i_ProcessName);
	void acLockModule(const char *i_ProcessName);
	int actestmemory(void);
	std::string acDumpAssembly(void);

	char *SnapLine(char *szBuf, LPSTR mem, int len, int dwid, char *olbl);

	bool AdjustPrivileges(void);

	std::vector<UNfunction*> m_Function;
	std::vector<UNspace*> m_Space;

	std::vector<DWORD> vec_Address;

	DWORD lok_PID;	// Lock ProssesID
	DWORD lok_Base; // Lock Base Address

	long lFindPageNo;
	long lFindOff;
	TCHAR	m_MemBuffer[100*500];
	CMemWalk walkObj;

	TCTraverse trBuffer;

	HWND hWindow;
};