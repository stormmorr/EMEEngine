/*

    unServerMain - unServer Main Entry Point
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include <string>

#include "Master.h"

#if defined(WIN32)
#include <time.h>
#include "../UnSRC/Utility/unConsole.h"
#endif

HWND hWndMain;

// initialization
static void acInitialize()
{
	/// Seed the random number generator
#if defined(WIN32)
	srand ( time(NULL) );
#endif

	Master* i_master = new Master();
    i_master->Initialize(800, 600, false);
}

// cleanup
static void acShutdown()
{
#if 0
    if (sMaster)
		{
        i_master->close();
        delete sMaster;
		}
#endif

    std::cout << "Finished Execution" << std::endl;
}

#pragma comment(lib, "SDLmain.lib")

// entry point
int main (int argc, char* argv[])
{
#if defined(WIN32)
	unConsoleAttribute(CONSOLE_MSG);
#endif

	printf("//        \\\\ -- Unification QAGE Server\n");
	printf("  unServer    \n");
	printf("\\\\        // \n");

#if 1
	Q.CoreAllocate();
#endif

#if 1
	playerAV.Allocate("playerAV");
#endif

    acInitialize();

    acShutdown();

    return 0;
}