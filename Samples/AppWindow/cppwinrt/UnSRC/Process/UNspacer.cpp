/*

    UNspacer - Stack Crunch Intermediary Layer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNspacer.h"
#include "../Base/UNdialect.h"

using namespace UN;

namespace UN
{

UNspacer::UNspacer()
{
}

//// Instantiate Memory Pointers instead of cumbersome variables

void UNspacer::unProcess(UN::UNstack i_stack, UN::UNsheet i_sheet)
{
	UN::UNstack r_stack;

	/////// UNclass Prototype Only ////////
	int sheetcnt;
	for(int i=0; i < i_stack.m_stack.size(); i++)
		{
		for(int ii=0; ii < i_sheet.m_list.size(); ii++)
			{
			r_stack.m_stack.push_back(i_stack.m_stack[i]);
			sheetcnt++;
			}
		}



}

};