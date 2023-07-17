/*

    UNlabtank - Neural Net Labatory Control Tank
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#pragma once

#include "UNconsciousness.h"

class UNlabtank
{
public:
	UNlabtank();
	~UNlabtank();

private:
	UN::UNconsciousness *m_consciousness;
};