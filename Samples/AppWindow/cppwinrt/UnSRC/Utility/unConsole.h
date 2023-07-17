/*

    unConsole - Console Helper Functions
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.
*/

#ifndef ICCONSOLE_H
#define ICCONSOLE_H

//----------------------------------------------------------------------------//
// INCLUDES				                                                  //
//----------------------------------------------------------------------------//

//#include <iostream>

//----------------------------------------------------------------------------//
// DEFINITIONS                                                            //
//----------------------------------------------------------------------------//

#define CONSOLE_TITLE 78
#define CONSOLE_INIT 6
#define CONSOLE_ERROR 4
#define CONSOLE_MSG 14
#define CONSOLE_HIGHLIGHT 46

//----------------------------------------------------------------------------//
// DECLARATIONS                                                           //
//----------------------------------------------------------------------------//

bool unConsoleAttribute(int Attribute);
bool unConsoleReset(void);

bool unPrintError(const char* ErrText);
bool unPrintAttribute(const char* Text, int Attribute);

#endif