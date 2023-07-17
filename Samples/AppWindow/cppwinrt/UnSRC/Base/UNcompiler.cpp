/*

	UNcompiler
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "UNcompiler.h"

#include "Shellapi.h"

#include <string>

UNcompiler::UNcompiler(HWND i_HWND)
{
	m_HWND = i_HWND;
}

void UNcompiler::compileASM(std::string)
{

}

void UNcompiler::compileDocument(TumDocument *i_Document)
{

}

void UNcompiler::Testcompile(void)
{
#if 0
	data/QoreResource/Source/Test.cpp /Fa"C:\Projects Base\\Unification\\Build\\Uncompiler\\Assembly\\test.asm" /Fo"Uncompiler\\Output\\" /link /LIBPATH:"C:\Program Files\Microsoft Visual Studio 8\VC\lib" /OUT:"Uncompiler\\Output\\Out.exe"

	UN_COMPILER_PATH_FULL
	QORE_RESOURCE_PATH_FULL
#endif

	std::string i_InputFile = "data/QoreResource/Source/Test.cpp ";

	std::string i_CompilerOpt1 = "/c ";

	std::string i_Assembly = "/Fa\"C:\\Projects Base\\\Unification\\Build\\Uncompiler\\Assembly\\Test.asm\" ";
	std::string i_AssignOutput = "/Fo\"Uncompiler\\\Output\\\ \" ";
	std::string i_Linkage = "/link /LIBPATH:\"C:\\Program Files\\Microsoft Visual Studio 8\\VC\\lib\" ";
	std::string i_FileOutput = "/OUT:\"Uncompiler\\Output\\Test.exe\"";

	std::string i_StrParam = i_InputFile + i_CompilerOpt1 + i_Assembly + i_AssignOutput + i_Linkage + i_FileOutput;

	LPCSTR i_Parameters = i_StrParam.c_str();

	ShellExecute(m_HWND, "open", "cl.exe", i_Parameters, "", SW_SHOW);
}