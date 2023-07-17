/*

    UNspacer - Stack Crunch Intermediary Layer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#pragma once

#include "../Base/UNbase.h"
#include "../Base/UNdialect.h"

namespace UN
{

class UNspacer
{
public:
	UNspacer();
	~UNspacer() {};

	void unProcess(UN::UNstack i_stack, UN::UNsheet i_sheet);

	///// MUST CACHE

private:
	//// Class Cache Memory

	/////// Typedef Proxy Image ///////
	//cache
};

};