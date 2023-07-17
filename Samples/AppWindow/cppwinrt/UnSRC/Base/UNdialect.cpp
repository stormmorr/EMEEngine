/*

    UNdialect - Dialect Programatic Display Deterministic Approach Scan Functer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNdialect.h"
#include "../DRAT/TrueRandom.h"

namespace UN
{

dialectCC CC;

UNdialect::UNdialect(std::string i_dialect)
{
	vec_dialect.push_back(i_dialect);

#pragma message("Load dialect sketch sheet --- set variables from script for word length and random intervals")

	//UNwordlist *i_wordlist = new UNwordlist("../../UnificationSVN/Utilities/WordlistGenerator/WordLists/Example.txt");
	UNwordlist *i_wordlist = new UNwordlist("WordList/Example.txt");

	vec_wordlist.push_back(i_wordlist);

	unIntervalFact *i_IntervalFact = new unIntervalFact();

	i_IntervalFact->m_NameMin = 4;
	i_IntervalFact->m_NameMax = 14;

	vec_intervalfact.push_back(i_IntervalFact);
};

std::string UNdialect::acGenerateName(UInt8 i_wordlist)
{
	return std::string(vec_wordlist[i_wordlist]->acPickName(vec_intervalfact[0]));
}

UNwordlist::UNwordlist(std::string i_Filename) : m_mark(0)
{
	FILE* i_file = fopen(i_Filename.c_str(), "rb");
    if (i_file == 0)
		{
		printf("UN:::Error:::Failed to open word list");
		for(;;) {};
		}

	////// Character Count //////
	fseek(i_file, 0, SEEK_END);
    m_size = ftell(i_file);
    fseek(i_file, 0, SEEK_SET);

	///// Read Data /////
	m_characterlist = new char[m_size];
	fread(m_characterlist, 1, m_size, i_file);
	fclose(i_file);

#if 0
	printf("CharacterList %s\n", m_characterlist);
#endif

	printf("||- UNwordlist Loaded - %s \n", i_Filename.c_str());
}

std::string UNwordlist::acPickName(unIntervalFact* i_intervalfact)
{
#if 0
#ifdef UN_SETTINGS_CONSOLE && USE_TrueRandom
	if(!e_CTrueRandom->m_Active) return std::string("ActivateError");
#endif

	std::string i_name;

	CC.lettercount = 0;
	CC.letterskip = 32767 / 5;
	CC.letterprint = 32767 / 4;

	for(;;)
		{
		CC.letter = e_CTrueRandom->GetRand() / CC.letterprint;
		for(CC.k = 0; CC.k < CC.letter; ++CC.k)
			{
			if(m_characterlist[m_mark] != '\n')
				{
				i_name.push_back(m_characterlist[m_mark]);
				CC.lettercount++;
				}
			m_mark++;
			}

		m_mark += e_CTrueRandom->GetRand() / CC.letterskip;
		if(m_mark >= m_size) m_mark = m_size - m_mark;

		if(CC.lettercount >= i_intervalfact->m_NameMax)
			{
			i_name.resize(i_intervalfact->m_NameMax);
			break;
			}
		else
			{
			if(CC.lettercount >= i_intervalfact->m_NameMin)
				{
				break;
				}
			}
		}

#if 0
	printf("i_Name %s\n", i_name.c_str());
#endif

	//// Class Cache Memory
	/////// Typedef Proxy Image ///////
	// cache

	return i_name;
#endif

	std::string i_name;

	CC.lettercount = 0;
	CC.letterskip = 32767 / 5;
	CC.letterprint = 32767 / 4;

	for(;;)
		{
		CC.letter = rand() / CC.letterprint;
		for(CC.k = 0; CC.k < CC.letter; ++CC.k)
			{
			if(m_characterlist[m_mark] != '\n')
				{
				i_name.push_back(m_characterlist[m_mark]);
				CC.lettercount++;
				}
			m_mark++;
			}

		m_mark += rand() / CC.letterskip;
		if(m_mark >= m_size) m_mark = m_size - m_mark;

		if(CC.lettercount >= i_intervalfact->m_NameMax)
			{
			i_name.resize(i_intervalfact->m_NameMax);
			break;
			}
		else
			{
			if(CC.lettercount >= i_intervalfact->m_NameMin)
				{
				break;
				}
			}
		}

#if 0
	printf("i_Name %s\n", i_name.c_str());
#endif

	//// Class Cache Memory
	/////// Typedef Proxy Image ///////
	// cache

	return i_name;
}

};