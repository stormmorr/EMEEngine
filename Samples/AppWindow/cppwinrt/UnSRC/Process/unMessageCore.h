/*

    unMessageCore - Command Processor
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain */#include "pch.h"/*the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_Processor_
#define _UN_Processor_

#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

//#include "UNlabtank.h"
//#include "UNspacer.h"
#include "../Process/UNattributes.h"
//#include "../Base/UNcplusinterface.h"
//#include "../UNcore.h"
#include "../Base/UNdialect.h"
#include "../Utility/Singleton.h"

#if defined(WIN32)
#include "../Memory/unIdentManager.h"
#endif

//#include "boost/multi_array.hpp"
//#include "boost/array.hpp"
//#include "boost/cstdlib.hpp"

// SERVER EDIT
//#include "UNmemorymanager.h"

#include <rebecca/all.h>

using namespace rebecca;

#include <iostream>
#include <string>
#include <vector>

#if 0
#define UN_PROCESS_Media->MESSAGES 1
#endif

//typedef boost::multi_array<AimlFacade, 1> facadeAry;
//typedef facadeAry::index facadeIndex;

namespace UN
{

class unSpeechEvent
{
public:
	QpoVec3d m_Pos;

	float Volume;
	float Tone;
	float Impertinance;

	void acFinish(void);

	std::string m_Speech;
};

typedef struct QBStorage
{
	int NomAI;
	int NomBrains;
	int CDataID[50];
	int m_State;
} QBStorage;

typedef struct Q_Existance
{
	char m_Name[128];
	int m_NameLength;
	char m_Message[4096];
	int m_MessageLength;
	int m_BDataID;
	int m_CID;
	int m_State;
} Q_Existance;

typedef float SAMPLE;

typedef struct QpaRecData
{
  int		frameIndex;
  int		maxFrameIndex;
  int		samplesPerFrame;
  SAMPLE	*recordedSamples;
} QpaRecData;

typedef struct QpaResults
{
	float m_bestpeak_freq;
	float m_perfect_freq;
	float m_centsOff;
	float m_amplitude;
} QpaResults;

typedef struct QpaResVec
{
	std::vector<QpaResults*> m_Results;
	float m_TimeStamp;
	int m_Storage;
} QpaResVec;

typedef struct QpaStream
{
	std::vector<QpaResVec*> m_ResVec;
	float m_TimeStamp;
	int m_ResLen;
} QpaStream;

typedef struct QpaEmitter
{
	int m_PlaceH;
} QpaEmitter;

typedef struct QpaAttractor
{
	int m_PlaceH;
} QpaAttractor;

//2d Vocal Logic Gates
class QpaRange
{
public:
	QpaRange() {};
	~QpaRange() {};

	unsigned int m_LowerBounds;
	unsigned int m_UpperBounds;
	std::vector<QpaEmitter> m_Emitter;
	std::vector<QpaAttractor> m_Attractor;
	int m_Value;
};

typedef struct QpaStructure
{
	std::vector<std::vector<QpaRange> > m_Range;
} QpaStructure;

#define QPA_STRUCTURE_SQUARE 0
#define QPA_STRUCTURE_PLUS 1

//LIFE GAME!!

typedef struct Qpa_AMDA
{
	int m_time;
	int m_order;
	int m_height;
	int m_position;

	//Experiment binary download
	unsigned int m_factorEx1;
	unsigned int m_factorEx2;
	unsigned int m_factorEx4;
	unsigned int m_factorEx8;
	unsigned int m_factorEx16;
	unsigned int m_factorEx32;
	unsigned int m_factorEx64;
	unsigned int m_factorEx128;
} Qpa_AMDA;
// Trace vectors

class unMessageCore : public unSingleton<unMessageCore>
{
	//FIXME::: class-key
	friend class unSingleton<unMessageCore>;

public:
	unMessageCore();
	unMessageCore(std::string i_Name);
	unMessageCore(std::string i_Name, bool i_RexFacade);
	~unMessageCore() {};

	void acSetPaths(void);
	void acStartProcessor(const char* i_BotID, const char* i_UserID, const char* i_EndUserID);
	void acStartProcessorRex(const char* i_BotID, const char* i_UserID, const char* i_EndUserID);
	bool acStartProcessorContained(const char* i_BotID, const char* i_UserID, const char* i_EndUserID);
	bool acPauseProcessor(void);
	void acResponse(unsigned int i_Index, std::string i_Input);
	const char *acResponse(std::string i_Input);
	const char *acResponseFast(std::string i_Input);
	std::string acResponseStr(std::string i_Input);
	std::string acResponseStrRex(std::string i_Input);
	void acSoundEffect(QpoSoundDef i_SoundDef);
	void acResponseEffect(void);
	void acResponseEffectError(void);
	void acResponseEffectWarning(void);
	void acCaptureStart(void);
	bool acCaptureProgress(void);
	float *acCaptureGet(void);
	bool acCaptureAnalyse(float *i_ScData);

	bool acSoundProcess(QpaRecData& data, int sampleStart, int sampleEnd,
						 double sample_rate,
						 SAMPLE& max, SAMPLE& average_abs,
						 float& bestpeak_freq, float& perfect_freq, float& centsOff,
						 char*& pitchname);

	void acCapturePullFront(void);
	void acCaptureStore(void);
	void acCaptureStopStore(void);
	void acCaptureClearStore(void);

	bool acCapMode(void);
	void acCapPatternMatch(void);
	void acCaptureStructureSwitch(unsigned int i_Index);
	bool acCapPatternMatch(int i_StartDist);
	bool acCapStructureMarch(int i_StartDist);

	void acScanProc(void);
	void unFrame(void);

	void acVocalFrame(void);

	void acPrintName(int i_DialectIndex);
	std::string acGenName(int i_DialectIndex);

	std::vector<std::string> m_MessageStack;

	int m_CaptureMark;

	QpaStructure m_Structure;
	QpaRange m_Range;

	string m_botName;

	AimlFacade m_RexaryFacade;

	// SERVER EDIT
	//UNmemorymanager *m_memorymanager;

	QSharedStruct<QBStorage> m_BStorage;
	QSharedStruct<Q_Existance> m_Existance[150];
	QSharedStruct<Q_Existance> m_BrainExistance[50];

	int m_NomExistance;
	int m_NomBrainExistance;

	QpaStream vec_paCapture;
	QpaStream vec_paStore;

	/////// Knowledge Database And Learning ///////
	AimlFacade* m_aryFacade;

	std::string m_substitutions_xml;
	std::string m_sentence_splitters_xml;
	std::string m_properties_xml;

	std::string m_AIMLSchema;
	std::string m_CommonTypesSchema;
	std::string m_BotConfigurationSchema;

	int m_VILoaded;

	//// Sound Effects ////
	QpoSoundDef sfx_Response;
	QpoSoundDef sfx_ResponseEnd;
	QpoSoundDef sfx_Warning;

private:
	std::string m_name;

	std::vector<UN::UNdialect*> vec_dialect;

	UNProcessAttributes* m_attributes;

	/////// Typedef Proxy Image ///////
	//std::vector<UN::UNmap*> m_funimage;

	//cache function image
	//std::vector<UN::UNmap*> mem_funimage;
};

};

inline std::string STRtolower(std::string i_String)
{
	std::string i_Result;
	for(int i_Iter = 0; i_Iter < i_String.length(); i_Iter++)
		{
		i_Result.push_back(i_String[i_Iter] + 32);
		}
	return i_Result;
}

#define sProcessor unMessageCore::Instance()

#endif