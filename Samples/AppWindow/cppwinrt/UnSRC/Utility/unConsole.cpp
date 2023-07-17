/*

    unConsole - Console Helper Functions
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/
#if 0
#include "unConsole.h"

//#include <string>
//using namespace std;

#include "stdio.h"

#if defined (WIN32)
#include "windows.h"
#endif

//----------------------------------------------------------------------------//
// Function Definitions                                                       //
//----------------------------------------------------------------------------//

bool unConsoleAttribute(int Attribute)
{
#if defined(WIN32) // No PhysX under Linux yet.

	HANDLE  hConsole;

	//*hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	return true;//*SetConsoleTextAttribute(hConsole, Attribute);

#endif
}

bool unConsoleReset(void)
{
#if defined(WIN32) // No PhysX under Linux yet.

	HANDLE  hConsole;

	//*hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	return true;//*SetConsoleTextAttribute(hConsole, CONSOLE_MSG);

#endif
}

bool unPrintError(const char* ErrText)
{
#if defined(WIN32) // No PhysX under Linux yet.

	HANDLE  hConsole;
	bool result = true;

	//*hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//*result = SetConsoleTextAttribute(hConsole, 4);

	printf(ErrText);

	//*result = SetConsoleTextAttribute(hConsole, CONSOLE_MSG);

	return result;

#endif
}

bool icPrintAttribute(const char* Text, int Attribute)
{
#if defined(WIN32) // No PhysX under Linux yet.

	HANDLE  hConsole;
	bool result = true;

	//*hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//*result = SetConsoleTextAttribute(hConsole, Attribute);

	printf(Text);

	//*result = SetConsoleTextAttribute(hConsole, CONSOLE_MSG);

	return result;

#endif
}
#endif