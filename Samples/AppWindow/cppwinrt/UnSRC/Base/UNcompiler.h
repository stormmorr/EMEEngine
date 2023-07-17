/*

	UNcompiler
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UN_COMPILER_H
#define UN_COMPILER_H

#include "../Gui/Tumdocument.h"

#include "windows.h"
#include <string>

#define UN_COMPILER_PATH C:\Projects Base\Unification\Build\Uncompiler
#define UN_COMPILER_PATH_FULL C:\Projects Base\\Unification\\Build\\Uncompiler
#define QORE_RESOURCE_PATH C:\Projects Base\Unification\Build\data\QoreResource\
#define QORE_RESOURCE_PATH_FULL C:\Projects Base\\Unification\\Build\\data\\QoreResource\\

class UNcompiler
{
public:
	UNcompiler(HWND i_HWND);
	~UNcompiler();

	void compileASM(std::string);
	void compileDocument(TumDocument *i_Document);
	void Testcompile(void);

	HWND m_HWND;
};

#endif