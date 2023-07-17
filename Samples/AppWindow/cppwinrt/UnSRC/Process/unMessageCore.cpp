/*

    unMessageCore - Command Processor
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

////// Interchange Base Definitions
//#include "../Base/UNbase.h"

//#include "../Base/UNcplusinterface.h"
#include "unMessageCore.h"

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"
#include "Q-PortSHELL-Sound.h"

#include "Q-Includes.h"

#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-AI-Heart.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-CORE-Avatar.h"
#include "Q-Prototypes.h"
#include "Q-GlobalHeader.h"
#include "Q-AI-NNbot.h"

#include "../Osirus/OSIKnowledgeBase.h"

#include "../Sound/Spectrum.h"
#include "../Utility/FFT.h"

#define OCTAVE 4		// 10241
//unsigned long WindowSize = 16384 >> OCTAVE;
unsigned long WindowSize = 32;

using namespace rebecca;

using namespace UN;

namespace UN
{

int memberinit (int argc, char* args[]);

StringPimpl m_ActiveResponse;

float *autocorr = 0;
int autocorrLen = 0;

unMessageCore::unMessageCore()
{
	UNdialect *i_dialect = new UNdialect("UN_ASIMAGE0");
	vec_dialect.push_back(i_dialect);

	//m_spacer = new UNspacer();
	//m_main = new UNcore();
	//m_labtank = new UNlabtank();

	m_BStorage.Acquire("QBStorage");
	m_BStorage->NomBrains = 0;
	m_NomExistance = 0;
	m_NomBrainExistance = 0;
	vec_paCapture.m_ResLen = 0;
	vec_paStore.m_ResLen = 0;

	m_VILoaded = 0;
}

unMessageCore::unMessageCore(std::string i_Name)
{
	UNdialect *i_dialect = new UNdialect("UN_ASIMAGE0");
	vec_dialect.push_back(i_dialect);

	//m_spacer = new UNspacer();
	//m_main = new UNcore();
	//m_labtank = new UNlabtank();

	m_attributes = new UNProcessAttributes();
	m_attributes->m_Name = i_Name;

	acSetPaths();
	acStartProcessor(i_Name.c_str(), "default", "default");

	m_BStorage.Acquire("QBStorage");

	m_VILoaded = 1;

	vec_paCapture.m_ResLen = 0;
	vec_paStore.m_ResLen = 0;
}

unMessageCore::unMessageCore(std::string i_Name, bool i_RexFacade)
{
	UNdialect *i_dialect = new UNdialect("UN_ASIMAGE0");
	vec_dialect.push_back(i_dialect);
	m_VILoaded = 0;

	//m_spacer = new UNspacer();
	//m_main = new UNcore();
	//m_labtank = new UNlabtank();

	m_attributes = new UNProcessAttributes();
	m_attributes->m_Name = i_Name;

	acSetPaths();

#if 0
	if(i_RexFacade)
		{
#if 0
		acStartProcessorRex(i_Name.c_str(), "default", "default");
#endif
		acStartProcessorContained(i_Name.c_str(), "default", "default");
		m_VILoaded = 1;
		}
	else
		{
		acStartProcessor(i_Name.c_str(), "default", "default");
		m_VILoaded = 1;
		}
#endif

	Qpo->Sound_Init();

	sfx_Response = Qpo->Sound_Load("QpoSound", "Wav\\Effects\\Cplasma.wav");
	sfx_ResponseEnd = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\KeyLogError.wav");
	sfx_Warning = Qpo->Sound_Load("QpoSound", "Wav\\Attacks\\HadWarning.wav");

	m_BStorage.Acquire("QBStorage");

	vec_paCapture.m_ResLen = 0;
	vec_paStore.m_ResLen = 0;
}

///////// Start All Services /////////

void unMessageCore::acSetPaths(void)
{
	m_substitutions_xml = "/var/unserver/Deps/rebecca/conf/substitutions.xml";
	m_sentence_splitters_xml = "/var/unserver/Deps/rebecca/conf/sentence-splitters.xml";
	m_properties_xml = "/var/unserver/Deps/rebecca/conf/properties.xml";

	m_AIMLSchema = "/var/unserver/Deps/rebecca/resources/schema/AIML.xsd";
	m_CommonTypesSchema = "/var/unserver/Deps/rebecca/resources/schema/common-types.xsd";
	m_BotConfigurationSchema = "/var/unserver/Deps/rebecca/resources/schema/bot-configuration.xsd";
}

void unMessageCore::acStartProcessor(const char* i_BotID, const char* i_UserID, const char* i_EndUserID)
{
	Arguments arguments(0, 0);

	m_aryFacade = new AimlFacade();

	GraphBuilder &builder = m_aryFacade->getGraphBuilder();

	myCallBacks callback;
	builder.setCallBacks(&callback);

	cout << "[loading]" << endl;

	builder.setAIMLSchema(m_AIMLSchema.c_str());
	builder.setCommonTypesSchema(m_CommonTypesSchema.c_str());
	builder.setBotConfigurationSchema(m_BotConfigurationSchema.c_str());

	builder.setAIMLValidation();
	builder.setBotConfigurationValidation();

	builder.parseSubstitutionFile(m_substitutions_xml.c_str());
	builder.parseSentenceSplitterFile(m_sentence_splitters_xml.c_str());
	builder.parsePropertiesFile(m_properties_xml.c_str());

#if 0
	builder.addDirectoryUnlessAlreadyAdded("C:\Program Files\RebeccaAIML\aiml\annotated_alice");
#endif

#if 1
	builder.createGraph();
#endif

#if 1
#if 0
	StringPimpl userId = "unMessageServer";
	StringPimpl botId = m_attributes->m_Name.c_str();
	StringPimpl endUserId = "user";

	builder.createGraph(userId, botId, endUserId);
#endif

	int size = builder.getSize();

	//Print out the number of categories loaded.
	cout << endl << endl;
	cout << "[AIML fully loaded]" << endl;
	cout << "[Number of categories loaded: " << size << "]" << endl;
	cout << "[Type /exit to exit]" << endl << endl << endl;

	string botName = builder.getBotPredicate("name").c_str();
	StringPimpl response = builder.getResponse("connect");
#endif

#if 0
	while(true)
		{
		string input;
		cout << "You say> ";

		//Get input from the user from the keyboard
		getline(cin, input); 
		
		if(input == "/exit")
			{
			break;
			}
		else //The user gave an input to the bot
			{
			//Here we get some internal Rebecca information.
			cout << endl
				<< "Internal information:" << endl 
				<< "=====================" << endl
				<< input << " : " 
				<< builder.getThat().c_str() << " : "
				<< builder.getTopic().c_str() << endl;

			/*
			 * Ahhh finally.  We give the user input to Rebecca Aiml's loaded 
			 * AIML and get the response back.
			 */
			StringPimpl response = builder.getResponse(input.c_str());
			
			cout << "=====================" << endl << endl;
			
			//Print out what Rebecca says.
			cout << botName << " says: " << response.c_str() << endl;
			}
		}
#endif

	m_Existance[0].Acquire((char*)m_attributes->m_Name.c_str());

	for(int i_iter = 0; i_iter < m_attributes->m_Name.length(); i_iter++)
		{
		m_Existance[0]->m_Name[i_iter] = m_attributes->m_Name[i_iter];
		}

	m_Existance[0]->m_State = 0;
};

void unMessageCore::acStartProcessorRex(const char* i_BotID, const char* i_UserID, const char* i_EndUserID)
{
	Arguments arguments(0, 0);

	GraphBuilder &builder = m_RexaryFacade.getGraphBuilder();

	myCallBacks callback;
	builder.setCallBacks(&callback);

	cout << "[loading]" << endl;

	builder.setAIMLSchema(m_AIMLSchema.c_str());
	builder.setCommonTypesSchema(m_CommonTypesSchema.c_str());
	builder.setBotConfigurationSchema(m_BotConfigurationSchema.c_str());

	builder.setAIMLValidation();
	builder.setBotConfigurationValidation();

	builder.parseSubstitutionFile(m_substitutions_xml.c_str());
	builder.parseSentenceSplitterFile(m_sentence_splitters_xml.c_str());
	builder.parsePropertiesFile(m_properties_xml.c_str());

#if 1
	//builder.addDirectory(arguments.getAimlDirectory().c_str());
	builder.addDirectory("aiml/annotated_alice");
	builder.addDirectory("C:/Projects Base/Unification/Build/aiml/annotated_alice");
#endif

#if 1
	builder.createGraph();
#endif

#if 1
#if 0
	StringPimpl userId = "unMessageServer";
	StringPimpl botId = m_attributes->m_Name.c_str();
	StringPimpl endUserId = "user";

	builder.createGraph(userId, botId, endUserId);
#endif

	int size = builder.getSize();

	//Print out the number of categories loaded.
	cout << endl << endl;
	cout << "[AIML fully loaded]" << endl;
	cout << "[Number of categories loaded: " << size << "]" << endl;
	cout << "[Type /exit to exit]" << endl << endl << endl;

	string botName = builder.getBotPredicate("name").c_str();
	StringPimpl response = builder.getResponse("connect");
#endif

#if 0
	while(true)
		{
		string input;
		cout << "You say> ";

		//Get input from the user from the keyboard
		getline(cin, input); 
		
		if(input == "/exit")
			{
			break;
			}
		else //The user gave an input to the bot
			{
			//Here we get some internal Rebecca information.
			cout << endl
				<< "Internal information:" << endl 
				<< "=====================" << endl
				<< input << " : " 
				<< builder.getThat().c_str() << " : "
				<< builder.getTopic().c_str() << endl;

			/*
			 * Ahhh finally.  We give the user input to Rebecca Aiml's loaded 
			 * AIML and get the response back.
			 */
			StringPimpl response = builder.getResponse(input.c_str());
			
			cout << "=====================" << endl << endl;
			
			//Print out what Rebecca says.
			cout << botName << " says: " << response.c_str() << endl;
			}
		}
#endif

	m_Existance[0].Acquire((char*)m_attributes->m_Name.c_str());

	for(int i_iter = 0; i_iter < m_attributes->m_Name.length(); i_iter++)
		{
		m_Existance[0]->m_Name[i_iter] = m_attributes->m_Name[i_iter];
		}

	m_Existance[0]->m_State = 0;
};

bool unMessageCore::acStartProcessorContained(const char* i_BotID, const char* i_UserID, const char* i_EndUserID)
{
	if(m_VILoaded > 0) return true;

	acSetPaths();

	Arguments arguments(0, 0);

	arguments.m_aimlSchemaPath = "/var/unserver/Deps/rebecca/resources/schema/AIML.xsd";
	arguments.m_commonTypesSchemaPath = "/var/unserver/Deps/rebecca/resources/schema/common-types.xsd";
	arguments.m_botConfigurationSchemaPath = "/var/unserver/Deps/rebecca/resources/schema/bot-configuration.xsd";
	arguments.m_configurationDirectory = "/var/unserver/Deps/rebecca/conf";
	arguments.m_aimlDirectory = "/var/unserver/Deps/rebecca/aiml/annotated_alice";

	GraphBuilder &builder = m_RexaryFacade.getGraphBuilder();

	myCallBacks callback;
	builder.setCallBacks(&callback);

	cout << "[loading]" << endl;

	builder.setAIMLSchema(arguments.getAimlSchemaPath().c_str());
	builder.setCommonTypesSchema(arguments.getCommonTypesSchemaPath().c_str());
	builder.setBotConfigurationSchema(arguments.getBotConfigurationSchemaPath().c_str());

	/* 
	 * Set that "yes" we do want to do XML validation on
	 * both the AIML XML and Rebecca's own configuration 
	 * files.
	 */
	builder.setAIMLValidation();
	builder.setBotConfigurationValidation();

	/*
	 * Parse Rebecca's configuration files to setup 
	 * Rebecca's ability to handle input subsitutions, 
	 * what a sentence splitter is, and what bot properties
	 * she should have.
	 */
	string substitutions_xml = arguments.getConfigurationDirectory() + "/substitutions.xml";
	builder.parseSubstitutionFile(substitutions_xml.c_str());
	
	string sentence_splitters_xml = arguments.getConfigurationDirectory() + "/sentence-splitters.xml";
	builder.parseSentenceSplitterFile(sentence_splitters_xml.c_str());
	
	string properties_xml = arguments.getConfigurationDirectory() + "/properties.xml";
	builder.parsePropertiesFile(properties_xml.c_str());
	
	/*
	 * Add the entire directory.  Every file that has the 
	 * extension ".aiml" will be added to the internal queue 
	 * for latter processing.
	 */
	builder.addDirectory(arguments.getAimlDirectory().c_str());

	/*
	 * No other files to add to the internal queue.  
	 * So, let's create the AIML graph, the internal 
	 * data structures.
	 */
	builder.createGraph();

#if 1
#if 0
	StringPimpl userId = "unMessageServer";
	StringPimpl botId = m_attributes->m_Name.c_str();
	StringPimpl endUserId = "user";

	builder.createGraph(userId, botId, endUserId);
#endif

	int size = builder.getSize();

	//Print out the number of categories loaded.
	cout << endl << endl;
	cout << "[AIML fully loaded]" << endl;
	cout << "[Number of categories loaded: " << size << "]" << endl;

	m_botName = builder.getBotPredicate("name").c_str();
#endif

#if 0
	while(true)
		{
		string input;
		cout << "You say> ";

		//Get input from the user from the keyboard
		getline(cin, input); 
		
		if(input == "/exit")
			{
			break;
			}
		else //The user gave an input to the bot
			{
			//Here we get some internal Rebecca information.
			cout << endl
				<< "Internal information:" << endl 
				<< "=====================" << endl
				<< input << " : " 
				<< builder.getThat().c_str() << " : "
				<< builder.getTopic().c_str() << endl;

			/*
			 * Ahhh finally.  We give the user input to Rebecca Aiml's loaded 
			 * AIML and get the response back.
			 */
			StringPimpl response = builder.getResponse(input.c_str());
			
			cout << "=====================" << endl << endl;
			
			//Print out what Rebecca says.
			cout << botName << " says: " << response.c_str() << endl;
			}
		}
#endif

	/*m_Existance[0].Acquire((char*)m_attributes->m_Name.c_str());

	for(int i_iter = 0; i_iter < m_attributes->m_Name.length(); i_iter++)
		{
		m_Existance[0]->m_Name[i_iter] = m_attributes->m_Name[i_iter];
		}

	m_Existance[0]->m_State = 0;*/

	m_VILoaded = 1;

	return true;
};

bool unMessageCore::acPauseProcessor(void)
{
	m_VILoaded = 0;
	return true;
};

void unMessageCore::acScanProc(void)
{
	if(m_Existance[0]->m_State == 1)
		{
		std::string i_Message = m_Existance[0]->m_Message;
		
		GraphBuilder &builder = m_aryFacade->getGraphBuilder();

		StringPimpl response = builder.getResponse(i_Message.c_str());

		//OSI EDIT rebecca version clash string .length not in current source version
		/*int i_iter;
		for(int i_iter = 0; i_iter < response.length(); i_iter++)
			{
			//OSI EDIT rebecca version clash string .at not in current source version
			//m_Existance[0]->m_Message[i_iter] = response.at(i_iter);
			}*/
		//m_Existance[0]->m_MessageLength = i_iter;

		m_Existance[0]->m_State = 2;
		}
}

void unMessageCore::acResponse(unsigned int i_Index, std::string i_Input)
{
	int i_iter;
	for(int i_iter = 0; i_iter < i_Input.length(); i_iter++)
		{
		//OSI EDIT rebecca version clash string .at not in current source version
		//m_Existance[i_Index]->m_Message[i_iter] = i_Input.at(i_iter);
		}

	m_Existance[i_Index]->m_MessageLength = i_iter;
	m_Existance[i_Index]->m_State = 1;
}

const char *unMessageCore::acResponse(std::string i_Input)
{
	i_Input.resize(i_Input.size() - 1);

	m_MessageStack.push_back(i_Input);
	int i_index = m_MessageStack.size() - 1;
	if(i_index >= m_MessageStack.size())
		{
		printf("ERROR::: m_MessageStack index out of bounds\n");
		for(;;) {}
		}

	printf("unTrace i_index %i\n", i_index);

	GraphBuilder &builder = m_aryFacade->getGraphBuilder();

	printf("unTrace m_MessageStack[i_index] %s\n", m_MessageStack[i_index].c_str());

	StringPimpl i_response = builder.getResponse(m_MessageStack[i_index].c_str());

	printf("Response: %s\n", i_response.c_str());

	//printf("%s: %s\n", m_attributes->m_Name, i_response.c_str());

	m_MessageStack.clear();

	return i_response.c_str();
}

std::string unMessageCore::acResponseStr(std::string i_Input)
{
	i_Input.resize(i_Input.size() - 1);

	m_MessageStack.push_back(i_Input);
	int i_index = m_MessageStack.size() - 1;
	if(i_index >= m_MessageStack.size())
		{
		printf("ERROR::: m_MessageStack index out of bounds\n");
		for(;;) {}
		}

	printf("unTrace i_index %i\n", i_index);

	GraphBuilder &builder = m_aryFacade->getGraphBuilder();

	StringPimpl i_response = builder.getResponse(m_MessageStack[i_index].c_str());

	printf("Response: %s\n", i_response.c_str());

	std::string i_responseStr = i_response.c_str();

	m_MessageStack.clear();

	return i_responseStr;
}

std::string unMessageCore::acResponseStrRex(std::string i_Input)
{
	std::string i_responseStr;

	if(m_VILoaded > 0)
		{
		i_Input.resize(i_Input.size() - 1);

		m_MessageStack.push_back(i_Input);
		int i_index = m_MessageStack.size() - 1;
		if(i_index >= m_MessageStack.size())
			{
			printf("ERROR::: m_MessageStack index out of bounds\n");
			for(;;) {}
			}

		printf("unTrace i_index %i\n", i_index);

		GraphBuilder &builder = m_RexaryFacade.getGraphBuilder();

		printf("trace i_conversionstring: %s\n", i_Input.c_str());

		char * i_Buffer = (char*)i_Input.c_str();

#if 0
		printf("trace i_Buffer: %s\n", i_Buffer);
#endif

		StringPimpl i_response = builder.getResponse(i_Buffer);

		i_responseStr = i_response.c_str();

		m_MessageStack.clear();
		}

	return i_responseStr;
}

void unMessageCore::acSoundEffect(QpoSoundDef i_SoundDef)
{
	QpoVec3d i_Position;
	i_Position.x = 0;
	i_Position.y = 0;
	i_Position.z = 0;
	Qpo->Sound_Play_Effect(i_SoundDef, 0.175, 2, 1, true, &i_Position, true);
}

void unMessageCore::acResponseEffect(void)
{
	acSoundEffect(sfx_Response);
}

void unMessageCore::acResponseEffectError(void)
{
	acSoundEffect(sfx_ResponseEnd);
}

void unMessageCore::acResponseEffectWarning(void)
{
	acSoundEffect(sfx_Warning);
}

void unMessageCore::acCaptureStart(void)
{
	Qpo->Sound_Capture_Start();
}

bool unMessageCore::acCaptureProgress(void)
{
	return Qpo->Sound_Capture_Progress();
}

float *unMessageCore::acCaptureGet(void)
{
	return Qpo->Sound_Capture_Get();
}

void unMessageCore::acCaptureStore(void)
{
	m_CaptureMark = 1;
}

void unMessageCore::acCaptureStopStore(void)
{
	m_CaptureMark = 0;
}

void unMessageCore::acCaptureClearStore(void)
{
	vec_paStore.m_ResVec.clear();
	vec_paStore.m_ResLen = 0;
}

bool unMessageCore::acCaptureAnalyse(float *i_ScData)
{
	QpaRecData i_RecData;

	i_RecData.frameIndex = 0;
	i_RecData.maxFrameIndex = QPO_CAPTURE_MAX;
	i_RecData.recordedSamples = i_ScData;
	i_RecData.samplesPerFrame = 1;

	SAMPLE max;
	SAMPLE average_abs;
	float bestpeak_freq, perfect_freq, centsOff, amplitude;
	char* pitchname;
	QpaResults* i_Results;
	QpaResVec* i_ResVec = new QpaResVec();

	int i_BufferPos = 0;
	int i_Count = QPO_CAPTURE_SAMPLE;
	while(i_BufferPos < 1024)
		{
		acSoundProcess(i_RecData, i_BufferPos, i_Count, 22050,
							 max, average_abs,
							 bestpeak_freq, perfect_freq, centsOff,
							 pitchname);

		i_Results = new QpaResults();

		i_Results->m_bestpeak_freq = bestpeak_freq;
		i_Results->m_perfect_freq = perfect_freq;
		i_Results->m_centsOff = centsOff;
		i_Results->m_amplitude = average_abs;

		i_ResVec->m_Results.push_back(i_Results);

		i_Count += QPO_CAPTURE_SAMPLE;
		i_BufferPos += QPO_CAPTURE_SAMPLE;

#if 0
#if 1
		printf("QpaCapture:::bestpeak_freq %f perfect_freq %f centsOff %f average_abs %f\n", bestpeak_freq, perfect_freq, centsOff, average_abs);
#else
		printf("QpaCapture:::average_abs %f\n", average_abs);
#endif
#endif
		}

	if(m_CaptureMark)
		{
		i_ResVec->m_Storage = 1;
		vec_paStore.m_ResVec.push_back(i_ResVec);
		vec_paStore.m_ResLen++;
		}
	else i_ResVec->m_Storage = 0;

	vec_paCapture.m_ResVec.push_back(i_ResVec);
	vec_paCapture.m_ResLen++;

	if(vec_paCapture.m_ResLen > QPO_CAPTURE_MAX) acCapturePullFront();

	return true;
}

bool unMessageCore::acCapMode(void)
{
	float i_AmpStr = 999999;
	float i_FreqStr = 6000;
	int i_XPoints = 0;
	int i_YPoints = 0;
	int i_ZPoints = 0;

	for(unsigned int i_Count = 0; i_Count < vec_paCapture.m_ResVec.size(); i_Count++)
		{
		for(unsigned int i_ResCount = 0; i_ResCount < vec_paCapture.m_ResVec[i_Count]->m_Results.size(); i_ResCount++)
			{
			/// Amplitude ///
			if(vec_paCapture.m_ResVec[i_Count]->m_Results[i_ResCount]->m_amplitude > i_AmpStr)
				{
				/// Frequency ///
				if(vec_paCapture.m_ResVec[i_Count]->m_Results[i_ResCount]->m_perfect_freq > i_FreqStr)
					{
					i_XPoints++;
					}
				}
			}
		}

	if(i_XPoints <= 500) return false;

	acSoundEffect(sfx_Warning);
	return true;
}

bool unMessageCore::acCapPatternMatch(int i_StartDist)
{
	for(unsigned int i_Count = i_StartDist; i_Count < QPO_CAPTURE_MAX; i_Count++)
		{
		for(unsigned int i_ResCount = 0; i_ResCount < QPO_CAPTURE_STORE; i_ResCount++)
			{
			vec_paCapture.m_ResVec[55]->m_Results[55]->m_bestpeak_freq;
			vec_paCapture.m_ResVec[55]->m_Results[55]->m_perfect_freq;
			vec_paCapture.m_ResVec[55]->m_Results[55]->m_centsOff;
			vec_paCapture.m_ResVec[55]->m_Results[55]->m_amplitude;
			}
		}

	/*for(unsigned int i_Return)
		{
		int hhhhh
		= 0;
		}*/

	//EX

	return true;
}

void unMessageCore::acCaptureStructureSwitch(unsigned int i_Index)
{
	switch(i_Index)
		{
		case QPA_STRUCTURE_SQUARE:
			{
			std::vector<QpaRange> i_Structure;
			m_Range.m_LowerBounds = 5000;
			m_Range.m_UpperBounds = 7500;
			i_Structure.push_back(m_Range);
			m_Range.m_LowerBounds = 9000;
			m_Range.m_UpperBounds = 9999;
			i_Structure.push_back(m_Range);
			m_Structure.m_Range.push_back(i_Structure);
			m_Structure.m_Range.push_back(i_Structure);
			} break;

		case QPA_STRUCTURE_PLUS:
			{
			std::vector<QpaRange> i_Structure;
			m_Range.m_LowerBounds = 7000;
			m_Range.m_UpperBounds = 8500;
			i_Structure.push_back(m_Range);
			m_Structure.m_Range.push_back(i_Structure);
			i_Structure[0].m_LowerBounds = 9000;
			i_Structure[0].m_UpperBounds = 9999;
			m_Structure.m_Range.push_back(i_Structure);
			m_Range.m_LowerBounds = 5000;
			m_Range.m_UpperBounds = 6500;
			m_Structure.m_Range[0].push_back(m_Range);
			i_Structure[0].m_LowerBounds = 7000;
			i_Structure[0].m_UpperBounds = 8500;
			m_Structure.m_Range[0].push_back(m_Range);
			} break;
		}
}

bool unMessageCore::acCapStructureMarch(int i_StartDist)
{
	float i_AmpStr = 999999;

	for(unsigned int i_Count = i_StartDist; i_Count < QPO_CAPTURE_MAX; i_Count++)
		{
		for(unsigned int i_ResCount = 0; i_ResCount < QPO_CAPTURE_STORE; i_ResCount++)
			{
			if(vec_paCapture.m_ResVec[i_Count]->m_Results[i_ResCount]->m_amplitude < i_AmpStr)
				{
				vec_paCapture.m_ResVec[i_Count]->m_Results[i_ResCount]->m_perfect_freq;
				}
			}
		}

	return true;
}

void unMessageCore::acCapturePullFront(void)
{
	if(vec_paCapture.m_ResVec[0]->m_Storage == 0)
		{
		for(unsigned int i_DelCount = 1; i_DelCount < vec_paCapture.m_ResVec[0]->m_Results.size(); i_DelCount++)
			{
			delete vec_paCapture.m_ResVec[0]->m_Results[i_DelCount];
			}

		delete vec_paCapture.m_ResVec[0];
		}

	for(unsigned int i_Count = 1; i_Count < vec_paCapture.m_ResVec.size(); i_Count++)
		{
		vec_paCapture.m_ResVec[i_Count - 1] = vec_paCapture.m_ResVec[i_Count];
		}

	vec_paCapture.m_ResVec.resize(vec_paCapture.m_ResVec.size() - 1);
	vec_paCapture.m_ResLen--;
}

const char *unMessageCore::acResponseFast(std::string i_Input)
{
	i_Input.resize(i_Input.size() - 1);

	GraphBuilder &builder = m_aryFacade->getGraphBuilder();

	StringPimpl i_response = builder.getResponse(i_Input.c_str());

	printf("Response: %s\n", i_response.c_str());

	return i_response.c_str();
}

void unMessageCore::unFrame(void)
{
#if 0
	//////// Pre Crunch Command Processor Wed 15th 2007 ///////

	//// Thread Delay Spike Divisal

	//// Processor Growth Inspection

	//UN::UNscale m_divscale;

	//////// Crunch Trip

#if 0
	UN::UNstruct im_variable;
	UN::UNsheet sep_variable;

	UN::UNstruct im_struct;
	UN::UNsheet sep_struct;

	UN::UNclass	im_class;
	UN::UNsheet sep_class;
#endif

	///// Changes Image for conditional crunch

	/////// UNvariable ////////
	for(int i=0; i < m_trip.im_variable.size(); i++)
		{
		for(int ii=0; ii < m_trip.im_variable[i].m_sheet.size(); ii++)
			{
			m_spacer->unProcess(m_trip.im_variable[i].m_stack[ii], m_trip.im_variable[i].m_sheet[ii]);
			}
		}

	/////// UNstruct ////////
	for(int i=0; i < m_trip.im_struct.size(); i++)
		{
		for(int ii=0; ii < m_trip.im_struct[i].m_sheet.size(); ii++)
			{
			m_spacer->unProcess(m_trip.im_struct[i].m_stack[ii], m_trip.im_struct[i].m_sheet[ii]);
			}
		}

	/////// UNclass Prototype Only ////////
	for(int i=0; i < m_trip.im_class.size(); i++)
		{
		for(int ii=0; ii < m_trip.im_class[i].getPrivate()->m_sheet.size(); ii++)
			{
			m_spacer->unProcess(m_trip.im_class[i].getPrivate()->m_stack[ii], m_trip.im_class[i].getPrivate()->m_sheet[ii]);
			}
		}

	/////// Construct Image

	//// Factor Stack Progression
	for(int id=0; id < m_divsheet.size(); id++)
		{
		///// Execute Image /////
		m_main->unExecute(m_divisor[id], m_divsheet[id]);
		}

	//UN::UNstruct im_variable;
	//UN::UNsheet sep_variable;

	//UN::UNstruct im_struct;
	//UN::UNsheet sep_struct;

	//UN::UNclass im_class;
	//UN::UNsheet sep_class;

	//float[3] m_Divisor;
	//float Scale;

	/// caching memory Image Load Save Jitter
#endif
};

void unMessageCore::acPrintName(int i_DialectIndex)
{
	printf("acGenerateName %s\n", vec_dialect[i_DialectIndex]->acGenerateName(0).c_str());
}

std::string unMessageCore::acGenName(int i_DialectIndex)
{
	std::string i_Name = vec_dialect[i_DialectIndex]->acGenerateName(0);
	i_Name = STRtolower(i_Name);
	return i_Name;
}

#if 0
void unMessageCore::acSpeech(int i_DialectIndex)
{

}
#endif

void unSpeechEvent::acFinish(void)
{
	//Calculate Extremeties

	/*SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			float i_Distance = Qpo->Vec3d_DistanceBetween(m_Pos, Q_Forge->Forge[SCRAM].AV.Xform.Translation);

			//if(
			}
		SCRAM++;
		}*/
}

void unMessageCore::acVocalFrame(void)
{
	// Process Speech Buffer

	//If end of sentence then acSpeechEvent
}

bool unMessageCore::acSoundProcess(QpaRecData& data, int sampleStart, int sampleEnd, double sample_rate,
             SAMPLE& max, SAMPLE& average_abs,
             float& bestpeak_freq, float& perfect_freq, float& centsOff,
             char*& pitchname)
{
	bool gotSound = false;

	autocorr = new float[sampleEnd - sampleStart];

	/* Measure peak and average amplitude. */
		{
		SAMPLE val;
		int i;

		max = 0;
		average_abs = 0;
		for(i = sampleStart; i < sampleEnd; i++)
			{
			val = data.recordedSamples[i];
			if(val < 0) val = -val; /* ABS */
			if(val > max) max = val;
			average_abs += val;
			}

#if 0
		printf("sample max amplitude = " SAMPLE_FORMAT "\n", max );
#endif

		average_abs /= sampleEnd - sampleStart;

#if 0
		printf("sample average_abs = " SAMPLE_FORMAT "\n", average_abs );
		fflush(stdout);
#endif
		}

#if 0 //jmt
	printf("analyzeAudio : NS=%d,max=%f,av=%f\n", numSamples, max, average_abs);
#endif

	/* Write out the analyzed spectrum of the recorded data */
	autocorrLen = 0;

#if 0
	if (autocorr) free(autocorr);
#endif

	if(average_abs <= 0) printf("QpaCapture:::ERROR:::average_abs is NULL\n");

	// Gotta have something to go on
	if(((sampleEnd - sampleStart) > 0) && (average_abs > 0))
		{
		/* Get an autocorrelation-- The highest peak is the pitch */
		if (Autocorrelation(data.recordedSamples, sampleStart, sampleEnd,
							 WindowSize /* window size in samples */,
							 &autocorr, autocorrLen))
			{
			/* Find the tallest peak, and print its frequency and pitch */
			float bestpeak_x = bestPeak2(autocorr, autocorrLen, sample_rate);

#if 0
			printf("trace bestpeak_x %f\n", bestpeak_x);
#endif

			if (bestpeak_x > 0)
				{
				bestpeak_freq = sample_rate / bestpeak_x;

				if ((bestpeak_freq > 1) && (bestpeak_freq < 20000))
					{
					float bestpeak_pitch = Freq2Pitch(bestpeak_freq);
					int bestpeak_pitch_int = int(bestpeak_pitch+0.5);
					perfect_freq = Pitch2Freq(int(bestpeak_pitch+0.5));
					pitchname = PitchName(bestpeak_pitch_int, 0 /* No flats */);

					// The pitch might still be stupid because max was really
					// small, hence we're just scraping up noise, but I'll
					// leave that to the client to decide
					gotSound = true;

					centsOff = (bestpeak_pitch - bestpeak_pitch_int) * 100;
					}
				}
			}
		}

	if(!gotSound)
		{
		// Silence or weirdness, hence forget about pitch
		perfect_freq = 0;
		bestpeak_freq = 0;
		centsOff = 0;
		pitchname = "";
		}

#if 0
	free(autocorr);
#endif

	return gotSound;
}

};