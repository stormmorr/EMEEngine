/*

    Tumble Document  - Tumbler Document Memory Files
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef TUM_DOCUMENT_H
#define TUM_DOCUMENT_H

#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>

#if 1
#define DOCUMENT_ASSERT
#endif

using namespace std;

class TumDocument
{
public:
	TumDocument();
	~TumDocument();
	TumDocument(std::string i_Name, char* Buffer, unsigned int i_Type);
	TumDocument(std::string i_Name, std::string i_Filename);

	void Init(void);

	bool Tumble(void);
	bool PrintFla(void);
	bool PrintResults(void);
	char* getResults(void);

	bool acOpenResource(std::string i_Filename);

#pragma message("FIXME:::Lock with mutex for thread safety")
	inline void appLine(std::string i_Line)
		{ m_Content.push_back(i_Line); }

	void addBlocker(std::string Blocker, int BlockerCNT);
	void addExtractor(std::string Extractor, int i_cntExtract, int Reset);

	std::vector<std::string> vecBlocker;
	std::vector<int> vecBlockerCNT;
	std::vector<std::string> vecExtractor;
	std::vector<int> vecExtractorReset;
	std::vector<int> veccntExtract;
	std::vector<std::string> vecResults;

	std::string m_Name;
	std::string m_String;
	unsigned int m_Type;
	size_t m_StrSize;

	std::vector<std::string> m_Content;
};

class unDocumentBank
{
public:
	unDocumentBank();
	~unDocumentBank();

	static unDocumentBank* instance();

	inline TumDocument* getDocument(unsigned int i_Index)
		{
#ifdef DOCUMENT_ERROR
		if(unsigned int >= m_Document.size())
			{
			printf("ERROR:::Document fetch out of bounds\n");
			return NULL;
			}
#endif
		return m_Document[i_Index];
		}

	//void acAddInstance(unsigned int i_VectorIndex, int i_x, int i_y, int i_z);

	std::vector<TumDocument*> m_Document;

private:
	static unDocumentBank* s_instance;
};

#endif