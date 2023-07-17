/*

    UNdialect - Dialect Programatic Display Deterministic Approach Scan Functer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#pragma once

#include "../Utility/datatypes.h"

#include <string>
#include <vector>

namespace UN
{

#pragma message("FIXME Quantise and add Clarity")

class dialectCC //Class Cache
{
public:
	dialectCC()
	: lettercount(0) ,
	randlong(0) ,
	randshort(0) ,
	k(0)
	{
#ifdef UN_SETTINGS_CONSOLE
#if 0
	printf("unDialect:::create class cache\n");
#endif
#endif
	};

	inline void acPrepload(void)
		{
		letter = 0;
		lettercount = 0;
		letterskip = 0;
		letterprint = 0;
		randlong = 0;
		randshort = 0;
		k = 0;
		};

	Uint16 letter;
	Uint16 lettercount;
	Uint16 letterskip;
	Uint16 letterprint;
	unsigned long randlong;
	unsigned short randshort;
	Uint16 k;
};

class unIntervalFact
{
public:
	unIntervalFact() {};
	~unIntervalFact() {};

	//set variables from script for word length and random intervals

	unsigned int m_NameMin;
	unsigned int m_NameMax;
};

class UNwordlist
{
public:
	UNwordlist(std::string i_Filename);
	~UNwordlist() {};

	std::string acPickName(unIntervalFact *i_intervalfact);
	char *getCharacterList() { return m_characterlist; }

private:
	char *m_characterlist;
	UInt32 m_size;
	UInt32 m_mark;
};

class UNdialect
{
public:
	UNdialect();
	UNdialect(std::string i_dialect);
	~UNdialect() {};

	std::string acGenerateName(UInt8 i_wordlist);

private:
	std::vector<unIntervalFact*> vec_intervalfact;
	std::vector<std::string> vec_dialect;
	std::vector<UNwordlist*> vec_wordlist;

	//// Class Cache Memory
	/////// Typedef Proxy Image ///////
	//cache
};

};