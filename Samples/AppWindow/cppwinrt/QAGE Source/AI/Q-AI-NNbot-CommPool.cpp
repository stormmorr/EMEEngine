/*

	Quantum Angel Game Engine Codex
	-Virtual Library -

	DATE - 11/05/06
		Copyright - J M Lawlor

	- Major Component -Nueral Net Functions-
	*/#include "pch.h"/*- Minor Component -Avatar Spawn NNbot-

*/

//### INCLUDES
#include "Q-PortSHELL-VAR.h"
#include "Q-PortSHELL-FUN.h"

#include "Q-Includes.h"
#include "Q-AI-Cortex.h"
#include "Q-AI-Brain.h"
#include "Q-WE-WorldEffects.h"
#include "Q-ITEM-ItemDef.h"
#include "Q-Structs.h"
#include "Q-GlobalHeader.h"
#include "Q-Prototypes.h"

using namespace GVARS;

namespace GVARS
{

void Q_COREFunctions::ReadMeMPathways(void)
	{
	FILE			*stream;
	int				Integer;
	float			Float;
	//int				K,L,J;


	//##### - Open our Character Data File
	stream = fopen("nnTank//Q_MeMPathways.ini","r");


	if(!stream)
		{
		printf("ERROR:::file not found nnTank//Q_MeMPathways.ini\n");
		for(;;) {}
		}


	//##### - Get _->NomRealisation
	fscanf(stream,"%d",&Integer);
	_->NomRealisation = Integer;

	int K=0;
	while(K < _->NomRealisation)
		{
		//##### - Get Q_MeMPathway->MeMPathway[K].InputType
		fscanf(stream,"%d",&Integer);
		Q_MeMPathway->MeMPathway[K].InputType = Integer;

		//##### - Get Q_MeMPathway->MeMPathway[K].InputType
		fscanf(stream,"%d",&Integer);
		Q_MeMPathway->MeMPathway[K].ControlType = Integer;

		//##### - Get Q_MeMPathway->MeMPathway[K].InputType
		fscanf(stream,"%d",&Integer);
		Q_MeMPathway->MeMPathway[K].OutputType = Integer;

		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].TheoryLVL = Float;

		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].InputRange = Float;


		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].TDimension1 = Float;

		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].TDimension2 = Float;

		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].TDimension3 = Float;

		//##### - Get Item Damage
		fscanf(stream,"%f",&Float);
		Q_MeMPathway->MeMPathway[K].TDimension4 = Float;

		K++;
		}

	fclose(stream);
	}


void Q_COREFunctions::WriteMeMPathways(void)
	{
	FILE			*stream;
	int				L,J;
	int				Integer;
	float			Float;


	//##### - Open our Character Data File
	stream = fopen("c:\\Projects Base\\Unification\\nnTank\\Q_MeMPathways.ini","w");


	//##### - Set Q_MeMPathway->MeMPathway[K].InputType
	Integer = _->NomRealisation;
	fprintf(stream,"%d\n",Integer);


	int K=0;
	while(K < _->NomRealisation)
		{
		//##### - Set Q_MeMPathway->MeMPathway[K].InputType
		Integer = Q_MeMPathway->MeMPathway[K].InputType;
		fprintf(stream,"%d ",Integer);

		//##### - Set Q_MeMPathway->MeMPathway[K].ControlType
		Integer = Q_MeMPathway->MeMPathway[K].ControlType;
		fprintf(stream,"%d ",Integer);

		//##### - Set Q_MeMPathway->MeMPathway[K].OutputType
		Integer = Q_MeMPathway->MeMPathway[K].OutputType;
		fprintf(stream,"%d ",Integer);

		//##### - Set Q_MeMPathway->MeMPathway[K].InputRange
		Float = Q_MeMPathway->MeMPathway[K].TheoryLVL;
		fprintf(stream,"%f ",Float);

		//##### - Set Q_MeMPathway->MeMPathway[K].InputRange
		Float = Q_MeMPathway->MeMPathway[K].InputRange;
		fprintf(stream,"%f ",Float);


		//##### - Set Q_MeMPathway->MeMPathway[K].TDimension1
		Float = Q_MeMPathway->MeMPathway[K].TDimension1;
		fprintf(stream,"%f ",Float);

		//##### - Set Q_MeMPathway->MeMPathway[K].TDimension2
		Float = Q_MeMPathway->MeMPathway[K].TDimension2;
		fprintf(stream,"%f ",Float);

		//##### - Set Q_MeMPathway->MeMPathway[K].TDimension3
		Float = Q_MeMPathway->MeMPathway[K].TDimension3;
		fprintf(stream,"%f ",Float);

		//##### - Set Q_MeMPathway->MeMPathway[K].TDimension4
		Float = Q_MeMPathway->MeMPathway[K].TDimension4;
		fprintf(stream,"%f\n",Float);

		K++;
		}

	fclose(stream);
	}


void Q_COREFunctions::FileGen(void)
	{
	FILE			*stream;
	const char		*Filename,*Klicker;
	int				L,J;

	Filename = "c:\\Projects Base\\Unification\\nnTank\\";

	Klicker = new char();

	J=0;
	while(J < 5)
		{
		L = (((float)rand() / 32767) * 255);

		switch(L)
			{
			case 0: Klicker = "q"; break;
			case 1: Klicker = "w"; break;
			case 2: Klicker = "e"; break;
			case 3: Klicker = "r"; break;
			case 4: Klicker = "t"; break;
			case 5: Klicker = "y"; break;
			case 6: Klicker = "u"; break;
			case 7: Klicker = "i"; break;
			case 8: Klicker = "o"; break;
			case 9: Klicker = "p"; break;
			case 10: Klicker = "["; break;
			case 11: Klicker = "]"; break;
			case 12: Klicker = "a"; break;
			case 13: Klicker = "s"; break;
			case 14: Klicker = "d"; break;
			case 16: Klicker = "f"; break;
			case 17: Klicker = "g"; break;
			case 18: Klicker = "h"; break;
			case 19: Klicker = "j"; break;
			case 20: Klicker = "k"; break;
			case 21: Klicker = "l"; break;
			case 22: Klicker = ";"; break;
			case 23: Klicker = "#"; break;
			case 24: Klicker = "z"; break;
			case 25: Klicker = "x"; break;
			case 26: Klicker = "c"; break;
			case 27: Klicker = "v"; break;
			case 28: Klicker = "b"; break;
			case 29: Klicker = "n"; break;
			case 30: Klicker = "m"; break;
			case 31: Klicker = ","; break;
			case 32: Klicker = "."; break;
			case 33: Klicker = "/"; break;
			}

		printf(Filename, "%c", Klicker);

		J++;
		}


	//##### - Open our Data File
	stream = fopen(Filename, "w");


	/*//##### - Set Q_MeMPathway->MeMPathway[K].InputType
	Integer = Q_MeMPathway->MeMPathway[K].InputType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].ControlType
	Integer = Q_MeMPathway->MeMPathway[K].ControlType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].OutputType
	Integer = Q_MeMPathway->MeMPathway[K].OutputType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].Active
	Integer = Q_MeMPathway->MeMPathway[K].Active;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].InputRange
	Float = Q_MeMPathway->MeMPathway[K].InputRange;
	fprintf(stream,"%f ",Float);*/

	}

};

// Pathway picker GUI
