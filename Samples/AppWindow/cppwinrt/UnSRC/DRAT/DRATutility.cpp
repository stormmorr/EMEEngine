/*

	DRAT Utility - Helper Functions
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "DRATutility.h"

#include "stdio.h"
#include "stdlib.h"

namespace DRAT
{

void AppendStr(const char *CharSrc, const char *CharIN)
{
	/// Perhaps Add Assert Checks ///
	printf(CharSrc, "%c", CharIN);
}

void RandomStr(const char *CharStr, UInt16 NomChar)
	{
	const char		*Klicker;
	UInt16			L,J;

	J=0;
	while(J < NomChar)
		{
		L = (((float)rand() / 32767) * 255);

		switch(L)
			{
			case 0: Klicker = "q"; break;
			case 1: Klicker = "w"; break;
			case 2: Klicker = "e"; break;
			case 3: Klicker = "r"; break;
			case 4: Klicker = "t"; break;
			case 5: Klicker = "y"; break;
			case 6: Klicker = "u"; break;
			case 7: Klicker = "i"; break;
			case 8: Klicker = "o"; break;
			case 9: Klicker = "p"; break;
			case 10: Klicker = "["; break;
			case 11: Klicker = "]"; break;
			case 12: Klicker = "a"; break;
			case 13: Klicker = "s"; break;
			case 14: Klicker = "d"; break;
			case 16: Klicker = "f"; break;
			case 17: Klicker = "g"; break;
			case 18: Klicker = "h"; break;
			case 19: Klicker = "j"; break;
			case 20: Klicker = "k"; break;
			case 21: Klicker = "l"; break;
			case 22: Klicker = ";"; break;
			case 23: Klicker = "#"; break;
			case 24: Klicker = "z"; break;
			case 25: Klicker = "x"; break;
			case 26: Klicker = "c"; break;
			case 27: Klicker = "v"; break;
			case 28: Klicker = "b"; break;
			case 29: Klicker = "n"; break;
			case 30: Klicker = "m"; break;
			case 31: Klicker = ","; break;
			case 32: Klicker = "."; break;
			case 33: Klicker = "/"; break;
			}

		printf(CharStr, "%c", Klicker);

		J++;
		}
	}

void IncSave(const char *CharStr, UInt16 NomChar)
	{
	const char		*Klicker;
	UInt16			L,J;

	J=0;
	while(J < NomChar)
		{
		L = (((float)rand() / 32767) * 255);

		switch(CharStr[J])
			{
			case 0: Klicker = "q"; break;
			case 1: Klicker = "w"; break;
			case 2: Klicker = "e"; break;
			case 3: Klicker = "r"; break;
			case 4: Klicker = "t"; break;
			case 5: Klicker = "y"; break;
			case 6: Klicker = "u"; break;
			case 7: Klicker = "i"; break;
			case 8: Klicker = "o"; break;
			case 9: Klicker = "p"; break;
			case 10: Klicker = "["; break;
			case 11: Klicker = "]"; break;
			case 12: Klicker = "a"; break;
			case 13: Klicker = "s"; break;
			case 14: Klicker = "d"; break;
			case 16: Klicker = "f"; break;
			case 17: Klicker = "g"; break;
			case 18: Klicker = "h"; break;
			case 19: Klicker = "j"; break;
			case 20: Klicker = "k"; break;
			case 21: Klicker = "l"; break;
			case 22: Klicker = ";"; break;
			case 23: Klicker = "#"; break;
			case 24: Klicker = "z"; break;
			case 25: Klicker = "x"; break;
			case 26: Klicker = "c"; break;
			case 27: Klicker = "v"; break;
			case 28: Klicker = "b"; break;
			case 29: Klicker = "n"; break;
			case 30: Klicker = "m"; break;
			case 31: Klicker = ","; break;
			case 32: Klicker = "."; break;
			case 33: Klicker = "/"; break;
			}

		printf(CharStr, "%c", Klicker);

		J++;
		}
	}

};