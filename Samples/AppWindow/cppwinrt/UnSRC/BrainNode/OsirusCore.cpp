/*

	Osirus Core - Main Entry
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "OsirusCore.h"

#include "../Utility/FunctionSwitch.h"

#include "../Process/UNprocessor.h"

#if 0
using namespace QAGE;
using namespace Digi;
using namespace trr;
#endif

extern CSpeechDlg *i_CSpeechDlg;
extern UN::UNprocessor *unProcessor;

namespace OSI
{

//----- Osirus Core Constructors -----//

OsirusCore::OsirusCore()
{
	m_ClassTrie = new nPatriciaTrie<OSI::Class*>();
	m_CommandTrie = new nPatriciaTrie<Command*>();
	m_TagTrie = new nPatriciaTrie<Tag*>();
	m_ExpressionTrie = new nPatriciaTrie<Expression*>();
	m_ExpresstextTrie = new nPatriciaTrie<Expresstext*>();

	nom_Class = 0;
	nom_Command = 0;
	nom_Tag = 0;
	nom_Expression = 0;
	nom_Expresstext = 0;

	UN::UNmap *i_Map = new UN::UNmap();
	vec_Map.push_back(i_Map);

#if 1	//Data Server Appeasement
	acCreateFile();
#endif

	//Load Definitions File
	acLoad("Osirus\\DefinitionsLive.exl");

	acLoadAPI("Osirus\\QPortSHELLFUN.exl");

#if 0	//Data Server Appeasement
	acSpeakVector();
#endif

#if 0
	acPrintVector();
#endif

#if 0
	m_logName.c_str()
	acSave("Osirus\\DefinitionsSAVE.exl");
#endif
}

OsirusCore::~OsirusCore()
{
	
}

//----- Osirus Core Instance -----//

OsirusCore* OsirusCore::s_instance = 0;
OsirusCore* OsirusCore::instance()
{
  return s_instance;
}

//----- Osirus Command Interface -----//

void OsirusCore::acCreateCommand(char *i_Text)
{
	Command *i_Command = new Command();
	i_Command->m_Text= i_Text;
	m_CommandTrie->Insert(i_Text, i_Command);
	vec_Command.push_back(i_Command);
	nom_Command++;

	// Expo data levels
	// End Affectors - Utilize reverse criteria inspired case checking with stored results

#if 0
	void (unAvatar::*pt2Member01)(int) = NULL;
	float (unAvatar::*pt2Member02)(void) = NULL;

	pt2Member01 = &unAvatar::executeAction;
	pt2Member02 = &unAvatar::getLodLevel;

	printf("Member function 01 Address %ul\n", pt2Member01);
	printf("Member function 02 Address %ul\n", pt2Member02);

	unAvatar instance1;
	float result = (instance1.*pt2Member02)();
#endif

	//acPushGuiEvent(m_GUI->getLast()->addButton(0, 12, m_GUI->getLastID(), 4, unGL::GLvecf2(242, 257), unGL::GLvecf2(182, 257), unGL::GLvecf2(210, 292), unGL::GLvecf2(213, 292)), UNGUI_EVE_CLICK, SubscriberSlot(&testclass::testfunction, &m_testclass));
}

void OsirusCore::acCreateTag(char *i_Text)
{
	OSI::Tag *i_Tag = new Tag();
	i_Tag->m_Text = i_Text;
	m_TagTrie->Insert(i_Text, i_Tag);
	vec_Tag.push_back(i_Tag);
	nom_Tag++;
}

void OsirusCore::acCreateExpresstext(char *i_Text)
{
	Expresstext *i_Expresstext = new Expresstext();
	i_Expresstext->m_Text = i_Text;
	m_ExpresstextTrie->Insert(i_Text, i_Expresstext);
	vec_Expresstext.push_back(i_Expresstext);
	nom_Expresstext++;
}

void OsirusCore::acCreateExpression(char *i_Text)
{
	Expression *i_Expression = new Expression();
	i_Expression->vec_Link.push_back(new OSI::Element());
	m_ExpressionTrie->Insert(i_Text, i_Expression);
	vec_Expression.push_back(i_Expression);
	nom_Expression++;
}

void OsirusCore::acCreateVariable(unsigned int i_Type)
{
	//Expresstext *i_Expresstext = new Expresstext();
	//i_Expresstext->i_Text = i_Text;
	//m_ExpresstextTrie->Insert(i_Text, nom_Expresstext);
	//vec_Expresstext.push_back(i_Expresstext);
	//nom_Expresstext++;
}

//~~~~~ File Loading ~~~~~//
void OsirusCore::acPrintVector(void)
{
	printf("OSI:::PrintVector <EXL>\n");
	for(int i_iterclass = 0; i_iterclass < nom_Class; i_iterclass++)
		{
		printf("Start Class ::: %s\n", vec_Class[i_iterclass]->m_Name.c_str());

		for(int i_iterfunc = 0; i_iterfunc < vec_Class[i_iterclass]->nom_Function; i_iterfunc++)
			{
			unsigned int i_iter;
			unsigned int i_iterpara;

			for(i_iter = 0; i_iter < vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Return.size(); i_iter++)
				{
				printf("%s ", vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Return[i_iter].m_Text.c_str());
				}

			printf("%s ", vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Name.m_Text.c_str());

			for(i_iter = 0; i_iter < vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Argument.size(); i_iter++)
				{
				for(i_iterpara = 0; i_iterpara < vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Argument[i_iter].m_Parameter.size(); i_iterpara++)
					{
					printf("%s ", vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Argument[i_iter].m_Parameter[i_iterpara].m_Text.c_str());
					}

				printf("%s ", vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Argument[i_iter].m_Name.c_str());
				}

			printf("\n");
			Sleep(500);
			}

		printf("End Class ::: %s\n", vec_Class[i_iterclass]->m_Name.c_str());
		}
}

//~~~~~ Apply Definitions to speech engine ~~~~~//
void OsirusCore::acSpeakVector(void)
{
//#ifndef OSI_DEBUG
#if 0
	for(int i_iterclass = 0; i_iterclass < nom_Class; i_iterclass++)
		{
		i_CSpeechDlg->acAddWord(vec_Class[i_iterclass]->m_Name.c_str());

		for(int i_iterfunc = 0; i_iterfunc < vec_Class[i_iterclass]->nom_Function; i_iterfunc++)
			{
			i_CSpeechDlg->acAddWord(vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Name.m_Text.c_str());
			}
		}
#else
	for(int i_iterclass = 0; i_iterclass < nom_Class; i_iterclass++)
		{
		i_CSpeechDlg->acAddWord(vec_Class[i_iterclass]->m_Name.c_str(), true);

		for(int i_iterfunc = 0; i_iterfunc < vec_Class[i_iterclass]->nom_Function; i_iterfunc++)
			{
			i_CSpeechDlg->acAddWord(vec_Class[i_iterclass]->vec_Function[i_iterfunc].m_Name.m_Text.c_str(), true);
			}
		}
#endif
}

//~~~~~ File Loading ~~~~~//
void OsirusCore::acCreateFile(void)
{
	char casecntbuf[100];
	std::string i_filepath;
	FILE* i_filecheck;
	bool fileSwit = true;

	while(fileSwit)
		{
		int random = rand() % 55000;

		itoa(random, casecntbuf, 10);

		std::string strname = "Definitions";
		std::string strnumber = casecntbuf;
		std::string strFilename = strname + strnumber;
		std::string i_path = "Osirus\\";
		std::string i_ext = ".exl";
		std::string i_file = strFilename;
		i_filepath = i_path + i_file + i_ext;

		FILE* i_filecheck = fopen(i_filepath.c_str(), "rb");
		if(i_filecheck == 0) fileSwit = false;
		else fclose(i_filecheck);
		}

#if 1
	m_logFile = fopen(i_filepath.c_str(), "w");
#endif

	m_logName = i_filepath;

	printf("OSI:::<EXL> Definitions file..[START] %s\n", i_filepath.c_str());
	fprintf(m_logFile, "<OSIrus-API-Recording>\n");
}

#if 0
void OsirusCore::acCreateExpression(char *i_Text, int Vars)
{
	Expresstext *i_Expresstext = new Expresstext();
	i_Expresstext->i_Text = i_Text;
	m_ExpresstextTrie->Insert(i_Text, nom_Expresstext);
	vec_Expresstext.push_back(i_Expresstext);
	nom_Expresstext++;
}
#endif

void OsirusCore::acSave(const char* i_Filename)
{
	FILE			*i_Stream;
	unsigned int	i_Iter, i_Finger;

		//##### - Open our Character Data File
	i_Stream = fopen(i_Filename, "w");

	printf("OSI:::<EXL> Definitions file..[START] %s\n", m_logName.c_str());

	fprintf(i_Stream, "Osirus EXL Expression Text Definitions\n");

	fprintf(i_Stream, "<EXL>\n");

	fprintf(i_Stream, "<Command><Nom>%i</Nom>\n", nom_Command);

	for(i_Iter = 0; i_Iter < nom_Command; i_Iter++)
		fprintf(i_Stream, "%s\n", vec_Command[i_Iter]->m_Text.c_str());

	fprintf(i_Stream, "</Command>\n", nom_Command);

	fprintf(i_Stream, "<Tag><Nom>%i</Nom>\n", nom_Tag);

	for(i_Iter = 0; i_Iter < nom_Tag; i_Iter++)
		fprintf(i_Stream, "%s\n", vec_Tag[i_Iter]->m_Text.c_str());

	fprintf(i_Stream, "</Tag>\n", nom_Command);

	fprintf(i_Stream, "<Expression><Nom>%i</Nom>\n", nom_Expression);

	for(i_Iter = 0; i_Iter < nom_Expression; i_Iter++)
		{
		for(i_Finger = 0; i_Finger < vec_Expression[i_Iter]->vec_Link.size(); i_Finger++)
			{
			switch(vec_Expression[i_Iter]->vec_Link[i_Iter]->m_Type)
				{
				case OSI_COMMAND:
					{
					//fprintf(i_Stream, "<C><%i><%s>", vec_Command[vec_Expression[i_Iter]->vec_Link[i_Finger]->m_Ptr]->m_Text.c_str());
					fprintf(i_Stream, "_C_ _%i_ _text_\n", vec_Expression[i_Iter]->vec_Link[i_Finger]->m_Ptr);
					} break;

				case OSI_TAG:
					{
					//fprintf(i_Stream, "<T><%i><%s>", vec_Tag[vec_Expression[i_Iter]->vec_Link[i_Finger]->m_Ptr]->m_Text.c_str());
					fprintf(i_Stream, "_C_ _%i_ _text_\n", vec_Expression[i_Iter]->vec_Link[i_Finger]->m_Ptr);
					} break;
				}
			}
		}

	fprintf(i_Stream, "</Expression>\n", nom_Command);

	fprintf(i_Stream, "<Expresstext><Nom>%i</Nom>\n", nom_Expresstext);

	for(i_Iter = 0; i_Iter < nom_Expresstext; i_Iter++)
		fprintf(i_Stream, "%s\n", vec_Expresstext[i_Iter]->m_Text.c_str());

	fprintf(i_Stream, "</Expresstext>\n", nom_Command);

	fprintf(i_Stream, "</EXL>");

	fclose(i_Stream);
}

void OsirusCore::acSaveUpdate(void)
{

}

void OsirusCore::acLoad(const char* i_Filename)
{
	FILE			*i_stream;

	int i_nom_Command = 0;
	int i_nom_Tag = 0;
	int i_nom_Expression = 0;
	int i_nom_Expresstext = 0;

	errno_t err = fopen_s( &i_stream, i_Filename, "r" );

	if( err )
		{
		printf("ERROR:::file not found %s\n", i_Filename);
		for(;;) {}
		}

	char i_cursor;
	std::string i_tag;

	//Cursor Seek
	while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
	fscanf_s( i_stream, "%c", &i_cursor, 1 );

	// Cursor Read
	while(i_cursor != '>')
		{
		i_tag.push_back(i_cursor);
		fscanf_s( i_stream, "%c", &i_cursor, 1 );
		}

	if(i_tag.compare("EXL") != 0)
		{
		printf("ERROR:::EXL definitions file corrupt\n");
		for(;;) {}
		}

	while(i_tag.compare("/EXL") != 0)
		{
		// Extract EXL Tag ////////////////////////////
		//Cursor Seek
		while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
		fscanf_s( i_stream, "%c", &i_cursor, 1 );

		// Cursor Read
		i_tag.clear();
		while(i_cursor != '>')
			{
			i_tag.push_back(i_cursor);
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			}
		///////////////////////////////////////////////

		if(i_tag.compare("Command") == 0)
			{
			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Nom") == 0) fscanf_s( i_stream, "%i", &i_nom_Command, 1 );

			// Extract /Nom Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			///////////////////////////////////////////////

			// OSI Commands //
			std::string i_command;

			for(int i_itercom = 0; i_itercom < i_nom_Command; i_itercom++)
				{
				// Cursor Read
				i_command.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '\n')
					{
					i_command.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				acCreateCommand((char*)i_command.c_str());
				}

			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("/Command") != 0)
				{
				printf("ERROR:::EXL definitions file corrupt at command end\n");
				for(;;) {}
				}
			}//End OSI Commands

		if(i_tag.compare("Tag") == 0)
			{
			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Nom") == 0) fscanf_s( i_stream, "%i", &i_nom_Tag, 1 );

			// Extract /Nom Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			///////////////////////////////////////////////

			// OSI Commands //
			std::string i_ositag;

			for(int i_itercom = 0; i_itercom < i_nom_Tag; i_itercom++)
				{
				// Cursor Read
				i_ositag.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '\n')
					{
					i_ositag.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				acCreateTag((char*)i_ositag.c_str());
				}

			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("/Tag") != 0)
				{
				printf("ERROR:::EXL definitions file corrupt at tag end\n");
				for(;;) {}
				}
			}//End OSI Commands

		if(i_tag.compare("Expression") == 0)
			{
			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Nom") == 0) fscanf_s( i_stream, "%i", &i_nom_Expression, 1 );

			// Extract /Nom Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			///////////////////////////////////////////////

			// OSI Commands //
			std::string i_expression;

			for(int i_itercom = 0; i_itercom < i_nom_Expression; i_itercom++)
				{
				// Cursor Read
				i_expression.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '\n')
					{
					i_expression.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				acCreateExpression((char*)i_expression.c_str());
				}

			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("/Expression") != 0)
				{
				printf("ERROR:::EXL definitions file corrupt at expression end\n");
				for(;;) {}
				}
			}//End OSI Commands

		if(i_tag.compare("Expresstext") == 0)
			{
			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Nom") == 0) fscanf_s( i_stream, "%i", &i_nom_Expresstext, 1 );

			// Extract /Nom Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			///////////////////////////////////////////////

			// OSI Commands //
			std::string i_expresstext;

			for(int i_itercom = 0; i_itercom < i_nom_Expresstext; i_itercom++)
				{
				// Cursor Read
				i_expresstext.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '\n')
					{
					i_expresstext.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}

				acCreateExpresstext((char*)i_expresstext.c_str());
				}

			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("/Expresstext") != 0)
				{
				printf("ERROR:::EXL definitions file corrupt at expresstext end\n");
				for(;;) {}
				}
			}//End OSI Commands
		}

	printf("OSI:::Definitions prepared...\n EXL %i Commands\n EXL %i Tags\n EXL %i Expressions\n EXL %i Expresstexts\n", i_nom_Command, i_nom_Tag, i_nom_Expression, i_nom_Expresstext);

	fclose(i_stream);
}


void OsirusCore::acLoadAPI(const char* i_Filename)
{
	FILE			*i_stream;

	int i_nom_Command = 0;
	int i_nom_Tag = 0;
	int i_nom_Expression = 0;
	int i_nom_Expresstext = 0;

	errno_t err = fopen_s( &i_stream, i_Filename, "r" );

	if( err )
		{
		printf("ERROR:::file not found %s\n", i_Filename);
		for(;;) {}
		}

	char i_cursor;
	std::string i_tag;

	//Cursor Seek
	while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
	fscanf_s( i_stream, "%c", &i_cursor, 1 );

	// Cursor Read
	while(i_cursor != '>')
		{
		i_tag.push_back(i_cursor);
		fscanf_s( i_stream, "%c", &i_cursor, 1 );
		}

	if(i_tag.compare("EXL") != 0)
		{
		printf("ERROR:::EXL definitions file corrupt\n");
		for(;;) {}
		}

	bool i_tagseek = true;
	while(i_tagseek)
		{
		// Extract EXL Tag ////////////////////////////
		//Cursor Seek
		while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
		fscanf_s( i_stream, "%c", &i_cursor, 1 );

		// Cursor Read
		i_tag.clear();
		while(i_cursor != '>')
			{
			i_tag.push_back(i_cursor);
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			}
		///////////////////////////////////////////////

		// OSI Function //
		OSI::Function i_Function;
		OSI::Argument i_Argument;
		///////////////////////////////////////////////

		if(i_tag.compare("Class") == 0)
			{
			// Allocate OSI Class /////////////////////////
			OSI::Class *i_Class = new OSI::Class();
			i_Class->m_FunctionTrie = new nPatriciaTrie<Function*>();
			i_Class->nom_Function = 0;
			switStructure = false;
			switFunction = false;
			switArgument = false;
			switClass = true;
			///////////////////////////////////////////////

			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			if(i_tag.compare("Name") == 0)
				{
				// Cursor Read
				i_Class->m_Name.clear();
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				while(i_cursor != '<')
					{
					i_Class->m_Name.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				}

			// Extract /Name Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			i_tag.clear();
			while(i_cursor != '>')
				{
				i_tag.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			fscanf_s( i_stream, "%c", &i_cursor, 1 );
			///////////////////////////////////////////////
			
			// Extract EXL Tag ////////////////////////////
			//Cursor Seek
			while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
			fscanf_s( i_stream, "%c", &i_cursor, 1 );

			// Cursor Read
			std::string i_funtext;
			while(i_cursor != '>')
				{
				i_funtext.push_back(i_cursor);
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				}
			///////////////////////////////////////////////

			while(switClass)
				{
				if(i_funtext.compare("CName") == 0)
					{
					if(!switStructure)
						{
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						}
					else
						{
						// Cursor Read
						i_Function.m_Name.m_Text.clear();
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						while(i_cursor != '<')
							{
							i_Function.m_Name.m_Text.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}
						}
					}

				if(i_funtext.compare("CReturn") == 0)
					{
					if(!switStructure) // First Function //
						{
						switStructure = true;
						switArgument = false;
						switFunction = false;
						}
					else
						{
						if(switFunction)
							{				 // Function Creation //
							i_Class->m_FunctionTrie->Insert((nPatriciaTrieKey)i_Function.m_Name.m_Text.c_str(), &i_Function);
							i_Class->vec_Function.push_back(i_Function);
							i_Class->nom_Function++;

							i_Function.m_Return.clear();
							i_Function.m_Argument.clear();
							switArgument = false;
							switFunction = false;
							}
						}

					// OSI Return //
					OSI::Parameter i_Parameter;

					// Cursor Read
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					while(i_cursor != '<')
						{
						i_Parameter.m_Text.push_back(i_cursor);
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						}

					i_Function.m_Return.push_back(i_Parameter);
					}

				if(i_funtext.compare("CArgument") == 0)
					{
					switFunction = true;

					if(!switArgument)
						{
						i_Argument.m_Name.clear();
						i_Argument.m_Parameter.clear();

						// OSI Return //
						OSI::Parameter i_Parameter;

						// Cursor Read
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						while(i_cursor != '<')
							{
							i_Parameter.m_Text.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}

						i_Argument.m_Parameter.push_back(i_Parameter);
						switArgument = true;
						}
					else
						{
						// OSI Return //
						OSI::Parameter i_Parameter;

						// Cursor Read
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						while(i_cursor != '<')
							{
							i_Parameter.m_Text.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}

						i_Argument.m_Parameter.push_back(i_Parameter);
						}
					}

				if(i_funtext.compare("CArgumentName") == 0)
					{
					switFunction = true;

					if(switArgument)
						{
						i_Function.m_Argument.push_back(i_Argument);
						i_Argument.m_Name.clear();
						i_Argument.m_Parameter.clear();
						switArgument = false;

						// Cursor Read
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						while(i_cursor != '<')
							{
							i_Argument.m_Name.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}

						i_Function.m_Argument.push_back(i_Argument);
						}
					else
						{
						i_Argument.m_Name.clear();
						i_Argument.m_Parameter.clear();
						switArgument = false;

						// Cursor Read
						fscanf_s( i_stream, "%c", &i_cursor, 1 );
						while(i_cursor != '<')
							{
							i_Argument.m_Name.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}

						i_Function.m_Argument.push_back(i_Argument);
						}
					}

				// Cursor Read ////////////////////////////
				i_tag.clear();
				while(i_cursor != '>')
					{
					i_tag.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				fscanf_s( i_stream, "%c", &i_cursor, 1 );
				///////////////////////////////////////////////
#pragma message("WARNING checking closing tags assumed not needed")
				///////////////////////////////////////////////

				// Extract EXL Tag ////////////////////////////
				//Cursor Seek
				while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
				fscanf_s( i_stream, "%c", &i_cursor, 1 );

				// Cursor Read
				i_funtext.clear();
				while(i_cursor != '>')
					{
					i_funtext.push_back(i_cursor);
					fscanf_s( i_stream, "%c", &i_cursor, 1 );
					}
				///////////////////////////////////////////////

				if(i_funtext.compare("/Class") == 0)
					{
					m_ClassTrie->Insert((nPatriciaTrieKey)i_Class->m_Name.c_str(), i_Class);
					vec_Class.push_back(i_Class);
					nom_Class++;

					bool i_seek = true;
					while(i_seek)
						{
						//Cursor Seek
						while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
						fscanf_s( i_stream, "%c", &i_cursor, 1 );

						// Cursor Read
						i_tag.clear();
						while(i_cursor != '>')
							{
							i_tag.push_back(i_cursor);
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							}

						if(i_tag.compare("Class") == 0)
							{
							i_seek = false;

							// Allocate OSI Class /////////////////////////
							OSI::Class *i_Class = new OSI::Class();
							i_Class->m_FunctionTrie = new nPatriciaTrie<Function*>();
							i_Class->nom_Function = 0;
							switStructure = false;
							switArgument = false;
							switClass = true;
							///////////////////////////////////////////////

							// Extract EXL Tag ////////////////////////////
							//Cursor Seek
							while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
							fscanf_s( i_stream, "%c", &i_cursor, 1 );

							// Cursor Read
							i_tag.clear();
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////

							if(i_tag.compare("Name") == 0)
								{
								// Cursor Read
								i_Class->m_Name.clear();
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								while(i_cursor != '<')
									{
									i_Class->m_Name.push_back(i_cursor);
									fscanf_s( i_stream, "%c", &i_cursor, 1 );
									}
								}

							// Extract /Name Tag ////////////////////////////
							//Cursor Seek
							while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
							fscanf_s( i_stream, "%c", &i_cursor, 1 );

							// Cursor Read
							i_tag.clear();
							while(i_cursor != '>')
								{
								i_tag.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							fscanf_s( i_stream, "%c", &i_cursor, 1 );
							///////////////////////////////////////////////
							
							// Extract EXL Tag ////////////////////////////
							//Cursor Seek
							while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
							fscanf_s( i_stream, "%c", &i_cursor, 1 );

							// Cursor Read
							i_funtext.clear();
							while(i_cursor != '>')
								{
								i_funtext.push_back(i_cursor);
								fscanf_s( i_stream, "%c", &i_cursor, 1 );
								}
							///////////////////////////////////////////////
							}

						if(i_tag.compare("/EXL") == 0)
							{
							i_seek = false;
							i_tagseek = false;
							switClass = false;
							}
						}
					}
				}

			}//End OSI Class
		}

	printf("OSI:::API prepared...\n EXL %i Classes\n", nom_Class);

	fclose(i_stream);
}


std::string OsirusCore::acExtractExlTag(FILE *i_stream)
{
	//Cursor Seek
	char i_cursor;
	while(i_cursor != '<') fscanf_s( i_stream, "%c", &i_cursor, 1 );
	fscanf_s( i_stream, "%c", &i_cursor, 1 );

	// Cursor Read
	std::string i_exltag;
	while(i_cursor != '>')
		{
		i_exltag.push_back(i_cursor);
		fscanf_s( i_stream, "%c", &i_cursor, 1 );
		}

	return i_exltag;
}

void OsirusCore::acProcessSpeechEvent(CSpeechEvent *i_Event)
{
	// First Lookup the first word and for now assume it is a command
	OSI::Command *i_Action = m_CommandTrie->Lookup((nPatriciaTrieKey)i_Event->m_Word[0]->c_str());

	if(!i_Action) i_Action = acFindCMD(i_Event->m_Word[0]);

	if(!i_Action)	//Command not found - Search for leading TAG
		{
		// First Lookup the first word and for now assume it is a command
		OSI::Tag *i_Tag = m_TagTrie->Lookup((nPatriciaTrieKey)i_Event->m_Word[0]->c_str());

		if(!i_Action) i_Tag = acFindTAG(i_Event->m_Word[0]);
		}

	FILE *index;

	//vec_Command[m_CommandTrie->Lookup(i_Event->m_Word[0]->c_str())]
}

void OsirusCore::acProcessAPISpeechEvent(CSpeechEvent *i_Event)
{
	OSI::Class *i_Class = 0;
	OSI::Function i_Function;

	int i_Iter = 0;

	while(!i_Class && i_Iter < i_Event->m_Word.size())
		{
		// First Lookup the first word and for now assume it is a command
		i_Class = m_ClassTrie->Lookup((nPatriciaTrieKey)i_Event->m_Word[i_Iter]->c_str());

		if(!i_Class) i_Class = acFindClass(i_Event->m_Word[i_Iter]);

		i_Iter++;
		}

	if(i_Class)
		{
		//std::string i_ClassName(i_Class->m_Name.c_str());
		i_CSpeechDlg->acSpeak(i_Class->m_Name.c_str());
		fprintf(m_logFile, "%s\n", i_Class->m_Name.c_str());
		flushall();
		}
	else
		{
#if 0
		i_CSpeechDlg->acSpeak("ERROR class not found");
#endif

		printf("OSI:::class not found\n");
		}

	while(i_Iter < i_Event->m_Word.size())
		{
		m_FoundFunc = false;

		// First Lookup the first word and for now assume it is a command
#if 0
		i_Function = i_Class->m_FunctionTrie->Lookup((nPatriciaTrieKey)i_Event->m_Word[i_Iter]->c_str());
#endif

		/*if(!i_Function)*/ i_Function = acFindFunction(i_Class, i_Event->m_Word[i_Iter]);

		if(m_FoundFunc)
			{
			//std::string i_FunctionName(i_Function.m_Name.m_Text.c_str());
			i_CSpeechDlg->acSpeak(i_Function.m_Name.m_Text.c_str());
			fprintf(m_logFile, "%s\n", i_Function.m_Name.m_Text.c_str());
			flushall();

#if 0
			i_Iter = i_Event->m_Word.size();
#endif
			}
		else
			{
#if 0
			i_CSpeechDlg->acSpeak("ERROR function not found");
#endif
#if 0
			i_CSpeechDlg->acSpeak(unProcessor->acGenName(0));
#endif
			printf("OSI:::Function not found\n");
			}

		i_Iter++;
		}

#if 0
	if(!i_Action)	//Command not found - Search for leading TAG
		{
		// First Lookup the first word and for now assume it is a command
		OSI::Tag *i_Tag = m_TagTrie->Lookup((nPatriciaTrieKey)i_Event->m_Word[0]->c_str());

		if(!i_Action) i_Tag = acFindTAG(i_Event->m_Word[0]);
		}

	FILE *index;
#endif
}

Command *OsirusCore::acFindCMD(std::string *i_Word)
{
	Command *i_resultCommand = 0;

	std::vector<unsigned int> i_wordindex;
	std::vector<unsigned int> i_keyindex;

	unsigned int m_sequencepoints = 0;
	unsigned int m_separationpoints = 0;

	for(unsigned int i_iter = 0; i_iter < vec_Command.size(); i_iter++)
		{
		for(unsigned int i_iterword = 0; i_iterword < i_Word->length(); i_iterword++)
			{
			for(unsigned int i_iterkey = 0; i_iterkey < vec_Command[i_iter]->m_Text.length(); i_iterkey++)
				{
				if(i_Word->at(i_iterword) == vec_Command[i_iter]->m_Text[i_iterkey])
					{
					i_wordindex.push_back(i_iterword);
					i_keyindex.push_back(i_iterkey);
					}
				}
			}

		if(i_wordindex.size() > 0 && i_keyindex.size() > 0)
			{
			unsigned int i_wordindexstack = i_wordindex[0];
			unsigned int i_keyindexstack = i_keyindex[0];
			unsigned int i_sequencepoints = 0;
			unsigned int i_separationpoints = 0;

			for(unsigned int i_iterindex = 1; i_iterindex < i_wordindex.size(); i_iterindex++)
				{
				if(i_wordindex[i_iterindex] == i_wordindexstack + 1
				&& i_keyindex[i_iterindex] == i_keyindexstack + 1)
					{
					i_sequencepoints++;
					}
				else i_separationpoints++;

				i_wordindexstack = i_wordindex[i_iterindex];
				i_keyindexstack = i_keyindex[i_iterindex];
				}

			if(i_sequencepoints > m_sequencepoints
			&& i_separationpoints <= m_separationpoints)
				{
				i_resultCommand = vec_Command[i_iter];

				m_sequencepoints = i_sequencepoints;
				m_separationpoints = i_separationpoints;
				}
			else
				{
				if(i_sequencepoints == m_sequencepoints
				&& i_separationpoints < m_separationpoints)
					{
					i_resultCommand = vec_Command[i_iter];

					m_sequencepoints = i_sequencepoints;
					m_separationpoints = i_separationpoints;
					}
				}
			}
		}

	return i_resultCommand;
}

Class *OsirusCore::acFindClass(std::string *i_Word)
{
	Class *i_resultClass = 0;

	std::vector<unsigned int> i_wordindex;
	std::vector<unsigned int> i_keyindex;

	unsigned int m_samepoints = 0;
	unsigned int m_sequencepoints = 0;
	unsigned int m_separationpoints = 0;

	for(unsigned int i_iter = 0; i_iter < vec_Class.size(); i_iter++)
		{
		for(unsigned int i_iterword = 0; i_iterword < i_Word->length(); i_iterword++)
			{
			for(unsigned int i_iterkey = 0; i_iterkey < vec_Class[i_iter]->m_Name.length(); i_iterkey++)
				{
				if(i_Word->at(i_iterword) == vec_Class[i_iter]->m_Name[i_iterkey])
					{
					i_wordindex.push_back(i_iterword);
					i_keyindex.push_back(i_iterkey);
					}
				}
			}

		if(i_wordindex.size() > 0 && i_keyindex.size() > 0)
			{
			unsigned int i_wordindexstack = i_wordindex[0];
			unsigned int i_keyindexstack = i_keyindex[0];
			unsigned int i_sequencepoints = 0;
			unsigned int i_separationpoints = 0;

			for(unsigned int i_iterindex = 1; i_iterindex < i_wordindex.size(); i_iterindex++)
				{
				if(i_wordindex[i_iterindex] == i_wordindexstack + 1
				&& i_keyindex[i_iterindex] == i_keyindexstack + 1)
					{
					i_sequencepoints++;
					}
				else i_separationpoints++;

				i_wordindexstack = i_wordindex[i_iterindex];
				i_keyindexstack = i_keyindex[i_iterindex];
				}

			if(i_sequencepoints > 0)	// Character in the same pattern
				{
				if(i_sequencepoints > m_sequencepoints
				&& i_separationpoints <= m_separationpoints)
					{
					i_resultClass = vec_Class[i_iter];

					m_samepoints = i_wordindex.size();
					m_sequencepoints = i_sequencepoints;
					m_separationpoints = i_separationpoints;
					}
				else
					{
					if(i_sequencepoints == m_sequencepoints
					&& i_separationpoints < m_separationpoints)
						{
						i_resultClass = vec_Class[i_iter];

						m_samepoints = i_wordindex.size();
						m_sequencepoints = i_sequencepoints;
						m_separationpoints = i_separationpoints;
						}
					}
				}
			else	//Only Matching Characters
				{
				if(i_wordindex.size() > m_samepoints)
					{
					i_resultClass = vec_Class[i_iter];

					m_samepoints = i_wordindex.size();
					m_sequencepoints = i_sequencepoints;
					m_separationpoints = i_separationpoints;
					}
				}
			}
		}

	return i_resultClass;
}

Function OsirusCore::acFindFunction(Class *i_Class, std::string *i_Word)
{
	Function i_resultFunction;
	m_FoundFunc = false;

	std::vector<unsigned int> i_wordindex;
	std::vector<unsigned int> i_keyindex;

	unsigned int m_samepoints = 0;
	unsigned int m_sequencepoints = 0;
	unsigned int m_separationpoints = 0;

	for(unsigned int i_iter = 0; i_iter < i_Class->vec_Function.size(); i_iter++)
		{
		for(unsigned int i_iterword = 0; i_iterword < i_Word->length(); i_iterword++)
			{
			for(unsigned int i_iterkey = 0; i_iterkey < i_Class->vec_Function[i_iter].m_Name.m_Text.length(); i_iterkey++)
				{
				if(i_Word->at(i_iterword) == i_Class->vec_Function[i_iter].m_Name.m_Text[i_iterkey])
					{
					i_wordindex.push_back(i_iterword);
					i_keyindex.push_back(i_iterkey);
					}
				}
			}

		if(i_wordindex.size() > 0 && i_keyindex.size() > 0)
			{
			unsigned int i_wordindexstack = i_wordindex[0];
			unsigned int i_keyindexstack = i_keyindex[0];
			unsigned int i_sequencepoints = 0;
			unsigned int i_separationpoints = 0;

			for(unsigned int i_iterindex = 1; i_iterindex < i_wordindex.size(); i_iterindex++)
				{
				if(i_wordindex[i_iterindex] == i_wordindexstack + 1
				&& i_keyindex[i_iterindex] == i_keyindexstack + 1)
					{
					i_sequencepoints++;
					}
				else i_separationpoints++;

				i_wordindexstack = i_wordindex[i_iterindex];
				i_keyindexstack = i_keyindex[i_iterindex];
				}

			if(i_sequencepoints > 0)	// Character in the same pattern
				{
				if(i_sequencepoints > m_sequencepoints
				&& i_separationpoints <= m_separationpoints)
					{
					i_resultFunction = i_Class->vec_Function[i_iter];
					m_FoundFunc = true;

					m_samepoints = i_wordindex.size();
					m_sequencepoints = i_sequencepoints;
					m_separationpoints = i_separationpoints;
					}
				else
					{
					if(i_sequencepoints == m_sequencepoints
					&& i_separationpoints < m_separationpoints)
						{
						i_resultFunction = i_Class->vec_Function[i_iter];
						m_FoundFunc = true;

						m_samepoints = i_wordindex.size();
						m_sequencepoints = i_sequencepoints;
						m_separationpoints = i_separationpoints;
						}
					}
				}
			else	//Only Matching Characters
				{
				if(i_wordindex.size() > m_samepoints)
					{
					i_resultFunction = i_Class->vec_Function[i_iter];
					m_FoundFunc = true;

					m_samepoints = i_wordindex.size();
					m_sequencepoints = i_sequencepoints;
					m_separationpoints = i_separationpoints;
					}
				}
			}
		}

	return i_resultFunction;
}

Tag *OsirusCore::acFindTAG(std::string *i_Word)
{
	return new Tag;
}

void OsirusCore::acTest(void)
{
#if 0
	nPatriciaTrie<int> *p = new nPatriciaTrie<int>();

    // Insert some (key,data) pairs into the structure.
    printf("Inserting... %s\n", p->Insert("foobar1 isnt what i expected to read", 1) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar2", 2) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar3", 3) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar4", 4) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("foobar5", 5) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("__2867", 23) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("_23437256", 234) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("c:\\work\\development", -20) ? "OK" : "FAILED!");
	printf("Inserting... %s\n", p->Insert("c:\\work\\release", -22) ? "OK" : "FAILED!");

    // Lookup
    printf("foobar1 = %d\n", p->Lookup("foobar1 isnt what i expected to read"));
	printf("foobar2 = %d\n", p->Lookup("foobar2"));
	printf("foobar3 = %d\n", p->Lookup("foobar3"));
	printf("foobar4 = %d\n", p->Lookup("foobar4"));
	printf("foobar5 = %d\n", p->Lookup("foobar5"));
	printf("__2867 = %d\n", p->Lookup("__2867"));
	printf("_23437256 = %d\n", p->Lookup("_23437256"));
	printf("c:\\work\\development = %d\n", p->Lookup("c:\\work\\development"));
	printf("c:\\work\\release = %d\n", p->Lookup("c:\\work\\release"));

    // Remove some items from the structure
	printf("Deleting 'foobar4'... %s\n", p->Delete("foobar4") ? "OK" : "Uh-oh!");
	printf("Deleting 'foobar5'... %s\n", p->Delete("foobar5") ? "OK" : "Uh-oh!");

    // Lookup
    printf("Looking up 'foobar4'... %s\n", p->LookupNode("foobar4") ? "Still there!" : "Not there (OK).");
    printf("Looking up 'foobar5'... %s\n", p->LookupNode("foobar5") ? "Still there!" : "Not there (OK).");

	delete p;
#endif
}

};