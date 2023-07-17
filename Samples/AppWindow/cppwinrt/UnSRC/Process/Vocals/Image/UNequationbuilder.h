/*

    UNequationbuilder - Equation Generating Conscious State
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#ifndef _UN_EquationBuilder_
#define _UN_EquationBuilder_

#include "../Utility/datatypes.h"
#include "../Geometry/unTrr.h"

#include "../../Server/Thread.h"

#include <vector>
#include <string>

using namespace std;

namespace UN
{

typedef struct
{
	int m_Type;
	string m_String;
	char m_Char;
	float m_Float;
} unArgument;

#define EQBUILD_MAINVAR 0
#define EQBUILD_EQUALS 1
#define EQBUILD_LPAREN 2
#define EQBUILD_RPAREN 3
#define EQBUILD_OPERATOR 4
#define EQBUILD_USERDEFINEDPARAM 5
#define EQBUILD_USERDEFINEDFUNC 6
#define EQBUILD_CONSTANTS 7
#define EQBUILD_HARDFUNC 8
#define EQBUILD_VARIABLE 9
#define EQBUILD_NUMERICLE 10
#define EQBUILD_END 11

#define EQBUILD_MODE_IDLE 0
#define EQBUILD_MODE_INITIALIZE 1
#define EQBUILD_MODE_BUILD 2
#define EQBUILD_MODE_PRINTEQ 3

typedef struct
{
	std::vector<unArgument> vec_Argument;
	string m_String;
} unEquation;

typedef struct
{
	std::vector<unEquation> vec_Equation;
} unEquationBank;

typedef struct
{
	std::string m_Name;
	int m_Type;
} unEquationRemote;

class UNequationbuilder : public CThread
{
public:
	UNequationbuilder(void* pOwnerObject = NULL, icThreadData *pData = 0);
	~UNequationbuilder() {};
	void acInit(string i_name);
	void acInit(void);
	void acQuickInit(string name, int type);
	float acMathRandom(void);
	float acAudioRandom(void);
	void acBuild(void);
	void acBuildAudio(void);
	void acPrintEQ(void);
	void acClose(void);

	void Initialize( void );
	void Run();

	int PP_STATE;

	SDL_mutex *m_mutex_State;
	int m_BuildStatus;

	SDL_mutex *m_mutex_Activity;
	int m_Mode;
	unEquationRemote m_Remote;

	SDL_mutex *m_mutex_Rand;
	std::vector<float> m_Rand;

	SDL_mutex *m_mutex_Beep;
	int m_Beep;

	SDL_mutex *m_mutex_Clear;
	bool m_Clear;

private:
	unArgument m_Argument;
	unEquation m_Equation;
	unEquationBank m_Bank;

	bool m_Ready;
	string m_name;

	char mainvar;
	string m_mainvar;
	int numofequations;
	bool showz;
	string equation;

	float expressions;
	float cz;
	float cvam;
	float clin;
	float cfm;
	float cnum;
	bool integer;
	bool nozero;
	float ccvar;
	float ccon;
	int nummax;
	float cparen;

	int counteropernumber;
	int counterhfuncnumber;
	int counterufuncnumber;
	int countercvarsnumber;
	int counterconstantnumber;
	int counternumber;
	int counterparamsnumber;

	char operformxoper[5];
	string ufuncformxufunc[7];
	string cvarsformxcvars[7];
	string constantformxconstant[32];
	string paramsformxparams[10];
	string hfuncformxhfunc[30];

	int m_filecount;

	FILE* m_fileoptions;
	FILE* m_file;

protected:
	virtual	int ThreadHandler();
};

};

#endif