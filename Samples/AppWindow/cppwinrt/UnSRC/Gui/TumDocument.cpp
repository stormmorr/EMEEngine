/*

    Tumble Document  - Tumbler Document Memory Files
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "TumDocument.h"
#include <iostream>
#include <fstream>

std::string itoa_new(int i)
{
	char data[99];
	sprintf(data, "%i", i);

	std::string s = data;
	return s;
}

TumDocument::TumDocument()
{
}

TumDocument::~TumDocument()
{
}

void TumDocument::Init(void)
{
}

TumDocument::TumDocument(std::string i_Name, char* Buffer, unsigned int i_Type)
{
	//// Create Tumbler Document From Char Bank
	m_Name = i_Name;
	m_String = Buffer;
	m_Type = i_Type;
}

TumDocument::TumDocument(std::string i_Name, std::string i_Filename)
{
	//// Create Tumbler Document
	m_Name = i_Name;

	//// Load Resource file
	acOpenResource(i_Filename);
}

bool TumDocument::acOpenResource(std::string i_Filename)
{
	std::ifstream i_file;
	i_file.open(i_Filename.c_str(), std::ios::in | std::ios::binary);

#ifdef DOCUMENT_ASSERT
	if(!i_file)
		{
		std::cerr << "ERROR:::Failed to open resource file '" << "TestDocument.qore" << "'." << std::endl;
		return false;
		}
#endif

#pragma message("FIXME:::Add document class cache")

	std::string i_Line;
	while(!i_file.eof())
		{
		std::getline(i_file, i_Line);
		appLine(i_Line);
		}

	char* i_char = new char[55];
	char* i_constchar = "Test Line Version III";

	i_char[0] = 81;
	i_char[1] = 0;
	i_char[2] = 81;
	i_char[3] = 0;
	i_char[4] = 81;
	i_char[5] = 0;
	i_char[6] = 81;
	i_char[7] = 81;

	i_constchar[0] = 81;
	i_constchar[1] = 81;
	i_constchar[2] = 81;
	i_constchar[3] = 81;
	i_constchar[4] = 81;
	i_constchar[5] = 81;
	i_constchar[6] = 81;
	i_constchar[7] = 81;

	appLine("Test line with spaces");
	appLine(std::string(i_char));
	appLine(std::string(i_constchar));
	//appLine("Test line version II with spaces");
	////i_file.ignore(1, ' ');

	i_file.close();
	return true;
}

void TumDocument::addBlocker(std::string Blocker, int BlockerCNT)
{
	vecBlocker.push_back(Blocker);
	vecBlockerCNT.push_back(BlockerCNT);
}

void TumDocument::addExtractor(std::string Extractor, int i_cntExtract, int Reset)
{
	veccntExtract.push_back(i_cntExtract);
	vecExtractor.push_back(Extractor);
	vecExtractorReset.push_back(Reset);
}

bool TumDocument::Tumble(void)
{
	/////// Assertions
	if(vecBlocker.size() == 0 || vecExtractor.size() == 0) return false;

	std::string extstring;
	int cntBlocker = 0;
	int cntChars = 0;
	int cntExtract = 0;
	bool valid = true;
	bool block = true;

	for (int l=0; l < m_String.length(); ++l)
		{
		/////// Find first Blocker ///////
		if(block)
			{
			valid = true;
			cntChars = 0;
			for (int c = l - (vecBlocker[cntBlocker].size() - 1); c < l; ++c)
				{
				if(c >= 0 && c < m_String.length())
				{ if(m_String.compare(c, 1, vecBlocker[cntBlocker], cntChars, 1) != 0) valid = false; }
				else valid = false;
				cntChars++;
				}

			////// Start Extracting
			if(valid)
				{
				extstring.clear();
				cntExtract = 0;
#if 0
				MessageBox(hwnd,"BlockValid","Error",MB_OK | MB_ICONERROR);
#endif
				block = false;
				}
			}
		else
			{
			if(cntExtract >= veccntExtract[cntBlocker])
				{
				extstring.push_back(m_String[l]);
				valid = true;
				cntChars = 0;
				for (int c = l - (vecExtractor[cntBlocker].size() - 1); c < l; ++c)
					{
					if(c >= 0 && c < m_String.length())
					{ if(m_String.compare(c, 1, vecExtractor[cntBlocker], cntChars, 1) != 0) valid = false; }
					else valid = false;
					cntChars++;
					}

				////// Extract String
				if(valid)
					{
#if 0
					MessageBox(hwnd,"Extracted Valid","Error",MB_OK | MB_ICONERROR);
#endif
					////// Flip Blockers
					block = true;
					vecResults.push_back(extstring);

					/// Reset Extractors and Blockers
					cntBlocker = vecExtractorReset[cntBlocker];
					}
				}
			else cntExtract++;
			}
		}

	return true;
}

bool TumDocument::PrintResults(void)
{
	FILE			*stream;
	int				caseinc = 0;
	char			casecntbuf[100];

	///// Generate Filename
	std::string strpath = "Output\\";
	std::string strtype = ".txt";
	std::string strFilename = strpath + m_Name + strtype;

	//##### - Open our Character Data File
	stream = fopen(strFilename.c_str(), "w");

	//##### - Clarify File Status
	fprintf(stream, "// OSIREM::FileTumbler Output\n// Output formatted for Quadrix Gate\n\n");

	fprintf(stream, "// Security Clearance\n\n");

	fprintf(stream, "switch(fingerSWF)\n");
	fprintf(stream, "    {\n");

	for(caseinc = 0; caseinc < vecResults.size(); caseinc++)
		{
		////// Generate Case Value
		std::string strinitiator = "    case ";
		std::string strterminator = ":\n";
		std::string strcasecntbuff = itoa_new(caseinc);
		std::string casevalue = strinitiator + strcasecntbuff + strterminator;

		fprintf(stream, casevalue.c_str());
		fprintf(stream, "        {\n");
		fprintf(stream, "        System.security.allowDomain(\"");
		fprintf(stream, vecResults[caseinc].c_str());
		fprintf(stream, "\", 2);\n");
		fprintf(stream, "        }break;\n");
		}

	fprintf(stream, "\n// Load Movie\n\n");

	for(caseinc = 0; caseinc < vecResults.size(); caseinc++)
		{
		////// Generate Case Value
		std::string strinitiator = "    case ";
		std::string strterminator = ":\n";
		std::string strcasecntbuff = itoa_new(caseinc);
		std::string casevalue = strinitiator + strcasecntbuff + strterminator;

		fprintf(stream, casevalue.c_str());
		fprintf(stream, "        {\n");
		fprintf(stream, "        loadMovieNum(\"");
		fprintf(stream, vecResults[caseinc].c_str());
		fprintf(stream, "\", 2);\n");
		fprintf(stream, "        }break;\n");
		}

	fprintf(stream, "    }\n");

	fclose(stream);

	return true;
}

bool TumDocument::PrintFla(void)
{
	return true;
}

char* TumDocument::getResults(void)
{
	/////// Calculate Character Size
	int charsize = 0;
	for (int b=0; b < vecResults.size(); ++b)
		{
		for (int v=0; v < vecResults[b].length(); ++v)
			{
			charsize++;
			}
		}

	char* output = new char[charsize];

	for (int b=0; b < vecResults.size(); ++b)
		{
#if 0
		MessageBox(hwnd,"getResults","Error",MB_OK | MB_ICONERROR);
#endif
		for (int v=0; v < vecResults[b].length(); ++v)
			{
			output[v] = vecResults[b][v];
			}
		}
	
	return output;
}

unDocumentBank::unDocumentBank(void)
{
}