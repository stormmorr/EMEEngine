/*

	Osirus Core - Main Entry
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OSIRUSCORE_H
#define OSIRUSCORE_H


#include "../Process/unMessageCore.h"
#include "../Utility/nPatriciaTrie.h"

#include "../Speech/SpeechDlg.h"

#include "Command.h"
#include "Class.h"

#include "../Dongle/UsbFrameWork.h"

#if 0
#define OSI_DEBUG 1
#endif

//using namespace trr;
using namespace UN;

namespace OSI
{

class OsirusCore
{
public:
	OsirusCore();
	~OsirusCore();

	/// singleton instance access
	static OsirusCore* instance();

	void acCreateFile(void);

	void acCreateCommand(char *i_Text);
	void acCreateTag(char *i_Text);
	void acCreateExpresstext(char *i_Text);
	void acCreateExpression(char *i_Text);

	void acCreateVariable(unsigned int i_Type);

	void acSpeechEvent(CSpeechEvent *i_Event);
	void acAPISpeechEvent(CSpeechEvent *i_Event);
	void acGlobalAPISpeechEventOrder(CSpeechEvent *i_Event, bool i_SpkClsName = false);
	void acGlobalAPISpeechEvent(CSpeechEvent *i_Event, bool i_SpkClsName = false);

	Command *acFindCMD(std::string *i_Word);
	Class *acFindClass(std::string *i_Word);
	Function acFindFunction(Class *i_Class, std::string *i_Word);
	Function acFindFunctionGlobal(std::string *i_Word);
	Tag *acFindTAG(std::string *i_Word);

	void acSave(const char* i_Filename);
	void acSaveUpdate(void);

	void acLoad(const char* i_Filename);
	void acLoadAPI(const char* i_Filename);
	void acLoadGlobalAPI(const char* i_Filename, const char* i_APIName);

	std::string acExtractExlTag(FILE *i_stream);
	void acTest(void);

	nPatriciaTrie<OSI::Class*>* m_ClassTrie;
	nPatriciaTrie<Command*>* m_CommandTrie;
	nPatriciaTrie<OSI::Tag*>* m_TagTrie;
	nPatriciaTrie<Expression*>* m_ExpressionTrie;
	nPatriciaTrie<Expresstext*>* m_ExpresstextTrie;

	std::vector<OSI::Class*> vec_Class;
	std::vector<Command*> vec_Command;
	std::vector<OSI::Tag*> vec_Tag;
	std::vector<Expression*> vec_Expression;
	std::vector<Expresstext*> vec_Expresstext;

	std::vector<UN::UNmap*> vec_Map;

	void acPrintVector(void);
	void acSpeakVector(void);

	unsigned int nom_Class;
	unsigned int nom_Command;
	unsigned int nom_Tag;
	unsigned int nom_Expression;
	unsigned int nom_Expresstext;

	bool switStructure;
	bool switFunction;
	bool switArgument;
	bool switClass;

	bool m_FoundFunc;

	FILE *m_logFile;
	std::string m_logName;

	usbFrameWork *m_UsbFrame;

private:
	static OsirusCore* s_instance;
};

};

#endif