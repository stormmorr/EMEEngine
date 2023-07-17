/*

Contract - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "../Musion/Code.h"
#include "../Musion/CodeLine.h"
#include "../Musion/Function.h"
#include "../Musion/Class.h"

#include "Contract.h"

#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <vector>

using namespace ecoin;

namespace ecoin
{

	//Global ESL Musion Ownership //mutex????
std::vector<std::shared_ptr<Class>> g_Class;
std::vector<std::shared_ptr<ClassVar>> g_ClassVar;

std::vector<std::shared_ptr<Condition>> g_Condition;

std::vector<std::shared_ptr<Function>> g_Function;
std::vector<std::shared_ptr<Function>> g_systemFunction;

std::vector<std::shared_ptr<Contract>> g_vec_CompileScope_Contract;
std::vector<std::shared_ptr<Contract>> g_vec_OperatorScope_Contract;

int g_ContractID = 0;

Contract::Contract()
{
	m_Active = false;
	m_entered_Function = nullptr;
	m_entered_Class = nullptr;
	m_Frame_Function = nullptr;
	m_vec_Function.clear();
	m_vec_Class.clear();

	m_ContractID = g_ContractID;
	g_ContractID++; //mutex????

	m_Chk = 0;
	m_Str_Command.clear();

	m_System = new System();
}

Contract::Contract(std::string f_IN)
{
	m_Active = false;
	m_entered_Function = nullptr;
	m_entered_Class = nullptr;

	m_Frame_Function = nullptr;
	m_vec_Function.clear();
	m_vec_Class.clear();

	m_ContractID = g_ContractID;
	g_ContractID++;

	m_Chk = 0;

	//Input
	m_Str_Command = f_IN;

	m_System = new System();

	acExtractLines();

	acScan_Lines();
}

Contract::Contract(std::shared_ptr<Cube::Qcom_eslfunction> f_IN)
{
	m_Active = false;
	m_entered_Function = nullptr;
	m_entered_Class = nullptr;

	m_Frame_Function = nullptr;
	m_vec_Function.clear();
	m_vec_Class.clear();

	m_ContractID = g_ContractID;
	g_ContractID++;

	m_Chk = 0;

	//Input
	m_Str_Command = f_IN->m_FunctionLine;

	m_System = new System();

	for(int f_XY = 0; f_XY < f_IN->m_vec_InitLineOrdered.size(); f_XY++)
		{
		m_Line.push_back(f_IN->m_vec_InitLineOrdered[f_XY]);
		}

#ifdef ESL_LOAD_VARS // Load Default Vars
	ac_LoadVars();
#endif

	g_vec_CompileScope_Contract.push_back((std::shared_ptr<Contract>)this);

	// ESL_SPEED_BENCH vFix new scan_lines
	acScan_Lines();
}

Contract::~Contract()
{
	m_Chk = 0;
	m_Str_Command.clear();
}

bool Contract::acLoad_StrIn(std::string f_IN)
{
	m_Str_Command = f_IN;

	acExtractLines();

	acScan_Lines();

	return true;
}


bool Contract::acExtractLines(void)
{
	std::string f_Line;
	
	uint f_Chk = 0;
	int f_Length = m_Str_Command.length();

	bool f_Scan = true;
	while(f_Chk < f_Length)
		{
		f_Line.clear();

		// char step
		char f_Char = acFileReadChar(m_Str_Command, f_Chk);
		f_Chk++;

		bool f_IntScan = true;
		while((f_Char != '/n') && (f_Char != '/r') && (f_IntScan == true))
			{
			//PUSH LINE
			f_Line.push_back(f_Char);

			// char step
			f_Char = acFileReadChar(m_Str_Command, f_Chk);
			f_Chk++;

			if(f_Chk < f_Length)
				{
				f_IntScan = false;

				//PUSH LINE
				f_Line.push_back(f_Char);
				}
			}

		m_Line.push_back(f_Line);
		}

	return true;
}

bool Contract::acScan_Lines(void)
{
	if(m_Frame_Function == nullptr)
		{
		m_Frame_Function = std::make_shared<Function>(MuFunc_Frame, (std::shared_ptr<Contract>)this);
		m_entered_Function = m_Frame_Function;

		g_Function.push_back(m_Frame_Function);

		m_vec_Function.clear();
		m_vec_Function.push_back(m_Frame_Function);
		}

	for(int f_LineCount = 0; f_LineCount < m_Line.size(); f_LineCount++)
		{ /////////////////
		 /////////////////
		// Line Detect //
		acScan_LineDetect(m_Line[f_LineCount]);
		}

	// reset compiler stage IIII
	m_entered_Function = nullptr;
	m_entered_Class = nullptr;

	return true;
}

void Contract::acScan_LineDetect(std::string f_Line)
{
	std::string f_ref_CurrentPath = g_ref_flow_reset + "Contract::acScan_LineDetect";

	std::shared_ptr<CodeLine> f_CodeLine = NULL;

	//ESL::New Line::...
	uint f_Chk = 0;
	while(f_Chk < f_Line.length() - 2)
		{
		//Constructor
		f_CodeLine = std::make_shared<CodeLine>(f_Line, &f_Chk, m_System);

		//Contract Function
		f_CodeLine->ac_Contract_Function((std::shared_ptr<Contract>)this, m_entered_Function);

		  /////////////////////////////////////////
		 // ESL Compiler Stage III Verify Entry //
		/////////////////////////////////////////

		if(f_CodeLine->m_CodeLine < 3)
			{
			if(m_entered_Function != nullptr)
				{
				if(m_entered_Class != nullptr)
					{
					for(int f_Jet = 0; f_Jet < f_CodeLine->m_vec_Variable.size(); f_Jet++)
						{
						std::shared_ptr<Variable> f_Var = f_CodeLine->m_vec_Variable[f_Jet];
					
						if(m_entered_Function->m_MxName.compare(m_entered_Class->m_MxName) == 0)
							{
							f_Var->m_lnk_Class = m_entered_Class;

							m_entered_Class->m_vec_Variable.push_back(f_Var);
							}
						}
					}
				}
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Condition_Ajax)
			{
			std::shared_ptr<Code> f_LtCode = f_CodeLine->m_vec_Code[0];
			std::shared_ptr<Code> f_CnCode = f_CodeLine->m_vec_Code[1];
			std::shared_ptr<Code> f_RtCode = f_CodeLine->m_vec_Code[2];

			std::shared_ptr<Condition> f_Condition = std::make_shared<Condition>(f_CnCode->m_MxName);

			f_Condition->m_Condition = f_CnCode->m_Type[0]->m_VarType;
			f_Condition->m_VarType = f_LtCode->m_Type[0]->m_VarType;

			f_Condition->leftHand = f_LtCode->m_Type[0]->m_MxVar;
			f_CodeLine->m_vec_Variable.push_back(f_Condition->leftHand);

			if(f_RtCode->m_Number.size() >= 1)
				{
				f_Condition->rightHand = f_RtCode->m_Number[0]->m_MxVar;
				f_CodeLine->m_vec_Variable.push_back(f_Condition->rightHand);
				}
			else
				{
				f_Condition->rightHand = std::make_shared<Variable>(f_RtCode->m_Name[0]->m_MxName, f_RtCode->m_Code);
				f_CodeLine->m_vec_Variable.push_back(f_Condition->rightHand);
				}

			f_CnCode->m_Condition.push_back(f_Condition);
			g_Condition.push_back(f_Condition);
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Function)
			{
			if(f_CodeLine->m_vec_Code[0]->m_Code == MuCode_Function)	//position zero
				{
				std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[0];

				std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType, (std::shared_ptr<Contract>)this);

				f_FnCode->m_FunctionLink = f_Function;
				}
			else if(f_CodeLine->m_vec_Code[0]->m_Code == MuFunc_Reflection)
				{
				std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[0];

				std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType, (std::shared_ptr<Contract>)this);

				f_Function->m_MxName = f_FnCode->m_Type[0]->m_Cvref_FuncName;

				f_FnCode->m_FunctionLink = f_Function;
				}
			else if(f_CodeLine->m_vec_Code.size() > 1)
				{
				if(f_CodeLine->m_vec_Code[1]->m_Code == MuCode_Function)	//position one
					{
					std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[1];

					std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType, (std::shared_ptr<Contract>)this);

					f_FnCode->m_FunctionLink = f_Function;
					}
				else if(f_CodeLine->m_vec_Code[1]->m_Code == MuFunc_Reflection)
					{
					std::shared_ptr<Code> f_FnCode = f_CodeLine->m_vec_Code[1];

					std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_FnCode->m_Type[0]->m_VarType, (std::shared_ptr<Contract>)this);

					f_Function->m_MxName = f_FnCode->m_Type[0]->m_Cvref_FuncName;

					f_FnCode->m_FunctionLink = f_Function;
					}
				}
			}
		else if(f_CodeLine->m_CodeLine == MuLine_Function_Custom)
			{
			std::shared_ptr<Code> f_CodeA = f_CodeLine->m_vec_Code[0];
			std::shared_ptr<Code> f_CodeX = nullptr;

			bool f_Custom = true;
			
			if(f_CodeA->m_Code == MuCode_Function)
				{
				f_CodeX = f_CodeA;

				f_Custom = false;
				}
			else if(f_CodeA->m_Code == MuCode_FunctionStart)
				{
				f_CodeX = f_CodeA;
				}
			else
				{
				if(f_CodeLine->m_vec_Code.size() > 1)
					{
					f_CodeA = f_CodeLine->m_vec_Code[1];

					if(f_CodeA->m_Code == MuCode_Function)
						{
						f_CodeX = f_CodeA;

						f_Custom = false;
						}
					else if(f_CodeA->m_Code == MuCode_FunctionStart)
						{
						f_CodeX = f_CodeA;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak();
						}
#endif
					}
#ifdef ECOIN_DEBUG_BREAKS
				else
					{
					__debugbreak();
					}
#endif
				}
			
			if(f_Custom == false)
				{
				std::shared_ptr<Function> f_Function = std::make_shared<Function>(f_CodeX->m_Type[0]->m_VarType, (std::shared_ptr<Contract>)this);

				f_CodeX->m_FunctionLink = f_Function;
				}
			else
				{
				std::string f_ClassName = f_CodeX->m_Name[0]->m_MxName;
				std::string f_Name = f_CodeX->m_Name[1]->m_MxName;

				if(f_CodeX->m_VarType == MuFunc_Frame)
					{
					std::shared_ptr<Function> f_New_Function = std::make_shared<Function>(MuFunc_Frame, (std::shared_ptr<Contract>)this);

					f_New_Function->m_Start_CodeLine = f_CodeLine;
					f_New_Function->m_MxName = f_Name;
					f_New_Function->m_ClassName = f_ClassName;

					f_CodeLine->m_Execute = false;
					f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

					if(m_entered_Class != nullptr)
						{
						f_New_Function->m_lnk_Class = m_entered_Class;
						m_entered_Class->m_vec_Function.push_back(f_New_Function);
						}

					g_Function.push_back(f_New_Function);

					m_vec_Function.push_back(f_New_Function);

					m_entered_Function = f_New_Function;
					}
				else
					{
					if(f_CodeX->m_Name[0]->m_MxName.compare("Success") == 0)
						{
						if(g_Function.size() >= 1 && g_Condition.size() >= 1)
							{
							std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom, (std::shared_ptr<Contract>)this);
					
							f_Function->m_MxName = f_Name;
							f_Function->m_ClassName = f_ClassName;

							if(f_CodeX->m_Name.size() >= 2)
								{
								for(int f_XYZ = 0; f_XYZ < g_Condition.size(); f_XYZ++)
									{
									if(g_Condition[f_XYZ]->m_MxName.compare(f_CodeX->m_Name[1]->m_MxName) == 0)
										{
										g_Condition[f_XYZ]->m_Success_Contract_FunctionID = g_Function.size();
										}
									}
								}
							else
								{
								g_Condition[g_Condition.size() - 1]->m_Success_Contract_FunctionID = g_Function.size();
								}

							f_Function->m_Start_CodeLine = f_CodeLine;

							f_CodeX->m_ContractID = g_Function.size();

							g_Function.push_back(f_Function);

							m_vec_Function.push_back(f_Function);

							if(m_entered_Class != nullptr)
								{
								f_Function->m_lnk_Class = m_entered_Class;

								m_entered_Class->m_vec_Function.push_back(f_Function);
								}

							m_entered_Function = f_Function;
							}
						}
					else if(f_CodeX->m_Name[0]->m_MxName.compare("Failure") == 0)
						{
						if(g_Function.size() >= 2 && g_Condition.size() >= 1)
							{
							std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom, (std::shared_ptr<Contract>)this);
					
							f_Function->m_MxName = f_Name;
							f_Function->m_ClassName = f_ClassName;

							if(f_CodeX->m_Name.size() >= 2)
								{
								for(int f_XYZ = 0; f_XYZ < g_Condition.size(); f_XYZ++)
									{
									if(g_Condition[f_XYZ]->m_MxName.compare(f_CodeX->m_Name[1]->m_MxName) == 0)
										{
										g_Condition[f_XYZ]->m_Failure_Contract_FunctionID = g_Function.size();
										}
									}
								}
							else
								{
								g_Condition[g_Condition.size() - 1]->m_Failure_Contract_FunctionID = g_Function.size();
								}

							f_Function->m_Start_CodeLine = f_CodeLine;

							f_CodeX->m_ContractID = g_Function.size();

							g_Function.push_back(f_Function);

							m_vec_Function.push_back(f_Function);

							if(m_entered_Class != nullptr)
								{
								f_Function->m_lnk_Class = m_entered_Class;

								m_entered_Class->m_vec_Function.push_back(f_Function);
								}

							m_entered_Function = f_Function;
							}
						}
					else
						{
						// NEW Custom Function
						if((f_Name.compare("Body") != 0) && (f_Name.length() > 0))
							{
							std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom, (std::shared_ptr<Contract>)this);

							f_Function->m_MxName = f_Name;
							f_Function->m_ClassName = f_ClassName;
							f_Function->m_Start_CodeLine = f_CodeLine;

							f_CodeLine->m_Execute = false;
							f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

							g_Function.push_back(f_Function);

							m_vec_Function.push_back(f_Function);

							if(m_entered_Class != nullptr)
								{
								f_Function->m_lnk_Class = m_entered_Class;

								m_entered_Class->m_vec_Function.push_back(f_Function);
								}

							m_entered_Function = f_Function;
							}
						}
					}
				}
			}
		else if (f_CodeLine->m_CodeLine == MuLine_For_Loop)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];
			std::string f_Name = f_Code->m_Name[0]->m_MxName;

			std::shared_ptr<Function> f_Function = std::make_shared<Function>(MuFunc_Custom, (std::shared_ptr<Contract>)this);

			f_Function->m_Start_CodeLine = f_CodeLine;
			f_Function->m_MxName = f_Name;
			f_CodeLine->m_Execute = false;
			f_CodeLine->m_vec_Code[0]->m_ContractID = g_Function.size();

			g_Function.push_back(f_Function);

			m_vec_Function.push_back(f_Function);

			if(m_entered_Class != nullptr)
				{
				f_Function->m_lnk_Class = m_entered_Class;

				m_entered_Class->m_vec_Function.push_back(f_Function);
				}

			m_entered_Function = f_Function;
			}
		else if (f_CodeLine->m_CodeLine == MuLine_ClassStart)
			{
			std::shared_ptr<Code> f_Code = f_CodeLine->m_vec_Code[0];

			std::string f_Namespace = f_Code->m_Name[0]->m_MxName;
			std::string f_Name = f_Code->m_Name[1]->m_MxName;

			std::shared_ptr<Class> f_Class = std::make_shared<Class>();

			f_Class->m_Namespace = f_Namespace;
			f_Class->m_MxName = f_Name;

			g_Class.push_back(f_Class);

			m_vec_Class.push_back(f_Class);

			m_entered_Class = f_Class;
			}

		    //////////////
		   // Storage  //
		  // Custom   //
		 // Complete //
		/////////////////////////////////
		if( (f_CodeLine->m_CodeLine != MuLine_ClassStart) && 
			(f_CodeLine->m_CodeLine != MuLine_Function_Custom) )
			{
			m_entered_Function->m_vec_CodeLine.push_back(f_CodeLine);
			}
		else
			{
			m_Frame_Function->m_vec_CodeLine.push_back(f_CodeLine);
			}
		}
}

#ifdef ESL_VAR_BY_NAME_METHOD
std::shared_ptr<Variable> Contract::ac_VarByName(std::shared_ptr<Variable> f_Variable)
{
	if(!f_Variable->m_lnk_ClassVar) //Var
		{
		for(int f_Jet = 0; f_Jet < g_vec_CompileScope_Contract.size(); f_Jet++)
			{
			std::shared_ptr<Contract> f_Contract = g_vec_CompileScope_Contract[f_Jet];

			uint f_CntStore = 0;
			while(f_CntStore < f_Contract->m_vec_Variable_Store.size())
				{
				std::shared_ptr<Variable> f_VariableStore = f_Contract->m_vec_Variable_Store[f_CntStore];

				if((f_VariableStore->m_lnk_ClassVar->m_MxName.compare(f_Variable->m_MxName) == 0)/* &&
				   (f_VariableStore->m_MxName.compare("Con") != 0)*/)
					{
					return f_VariableStore;
					}

				f_CntStore++;
				}
			}

		m_vec_Variable_Store.push_back(f_Variable);

#if 0
		if(f_Variable->m_MxName.compare("Con") == 0) //!constant
			{
			m_vec_Variable_Store.push_back(f_Variable);
			}
#endif
		}
	else //ClassVar
		{
		for(int f_Jet = 0; f_Jet < g_vec_CompileScope_Contract.size(); f_Jet++)
			{
			std::shared_ptr<Contract> f_Contract = g_vec_CompileScope_Contract[f_Jet];

			uint f_CntStore = 0;
			while(f_CntStore < f_Contract->m_vec_Variable_Store.size())
				{
				std::shared_ptr<Variable> f_VariableStore = f_Contract->m_vec_Variable_Store[f_CntStore];

				if(!f_VariableStore->m_lnk_ClassVar) //Var
					{
					if(f_VariableStore->m_lnk_ClassVar->m_MxName.compare(f_Variable->m_MxName.c_str()) == 0)
						{
						return f_VariableStore;
						}
					}

				f_CntStore++;
				}
			}

		m_vec_Variable_Store.push_back(f_Variable);

#if 0
		if(f_Variable->m_MxName.compare("Con") == 0) //!constant
			{
			m_vec_Variable_Store.push_back(f_Variable);
			}
#endif
		}

	return f_Variable;
}

void Contract::ac_SetupVars(void)
{
	for(int f_XY = 0; f_XY < g_Function.size(); f_XY++)
		{
		uint f_CodeLineSize = g_Function[f_XY]->m_vec_CodeLine.size();

		uint f_CntCodeLine = 0;
		while(f_CntCodeLine < f_CodeLineSize)
			{
			std::shared_ptr<CodeLine> f_CodeLine = g_Function[f_XY]->m_vec_CodeLine[f_CntCodeLine];

			uint f_VarSize = f_CodeLine->m_vec_Variable.size();

			switch(f_CodeLine->m_CodeLine)
				{
				case MuLine_Init_Var:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Init_ClassVar:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Assign:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Assign_Opr:
					{
					f_CodeLine->m_vec_Operator[0]->leftHand = ac_VarByName(f_CodeLine->m_vec_Operator[0]->leftHand);
					f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->leftHand);

					if(f_CodeLine->m_vec_Code[2]->m_Number.size() > 0)
						{
						f_CodeLine->m_vec_Operator[0]->rightHand = f_CodeLine->m_vec_Code[2]->m_Number[0]->m_MxVar;
						f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->rightHand);
						}
					else
						{
						f_CodeLine->m_vec_Operator[0]->rightHand = ac_VarByName(f_CodeLine->m_vec_Operator[0]->rightHand);
						f_CodeLine->m_vec_Variable.push_back(f_CodeLine->m_vec_Operator[0]->rightHand);
						}
					}break;

				case MuLine_Condition_Ajax:
					{
					f_CodeLine->m_vec_Code[1]->m_Condition[0]->leftHand = ac_VarByName(f_CodeLine->m_vec_Code[1]->m_Condition[0]->leftHand);

					if(f_CodeLine->m_vec_Variable[2]->m_MxName.compare("Con") != 0)
						{
						f_CodeLine->m_vec_Code[1]->m_Condition[0]->rightHand = ac_VarByName(f_CodeLine->m_vec_Code[1]->m_Condition[0]->rightHand);
						}
					}break;

				case MuLine_For_Loop:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Function:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Function_Custom:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Function_Reflect:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Return:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_Template:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;

				case MuLine_ClassStart:
					{
					for(int f_XYZ = 0; f_XYZ < f_CodeLine->m_vec_Variable.size(); f_XYZ++)
						{
						f_CodeLine->m_vec_Variable[f_XYZ] = ac_VarByName(f_CodeLine->m_vec_Variable[f_XYZ]);
						}
					}break;
				}

			f_CntCodeLine++;
			}
		}

	 ///////////////
	// Actions
	for(int f_Index = 0; f_Index < m_vec_Variable_Store.size(); f_Index++)
		{
		std::shared_ptr<Variable> f_Var = m_vec_Variable_Store[f_Index];

		if(f_Var->m_Action == MuAct_Random)
			{
			*(f_Var) = Cube::random();
			}
		else if(f_Var->m_Action == MuAct_RandInt)
			{
			*(f_Var) = Cube::randomFac();
			}
		else if(f_Var->m_Action == MuAct_Start)
			{
			/* Do Nothing */
			}
		else
			{
#ifdef ECOIN_SECURE
			throw;
#endif
			}
		}

}
#endif

void Contract::ac_ClearVars(void)
{
	m_vec_Variable_Store.clear();
	m_vec_ClassVar_Store.clear();
}

#ifdef ESL_LOAD_VARS
void Contract::ac_LoadVars(void)
{
	m_vec_Variable_Store.push_back(m_System->Pos);
	m_vec_Variable_Store.push_back(m_System->Posx);
	m_vec_Variable_Store.push_back(m_System->Posy);
	m_vec_Variable_Store.push_back(m_System->Posz);
	m_vec_Variable_Store.push_back(m_System->Color);
	m_vec_Variable_Store.push_back(m_System->Matrix1);
	m_vec_Variable_Store.push_back(m_System->Matrix2);
	m_vec_Variable_Store.push_back(m_System->Matrix3);
	m_vec_Variable_Store.push_back(m_System->Matrix4);
	m_vec_Variable_Store.push_back(m_System->nonce);
}
#endif

void Contract::acWork(void)
{
	//Execute Work
	for(int f_XY = 0; f_XY < m_Frame_Function->m_vec_CodeLine.size(); f_XY++)
		{
		std::shared_ptr<CodeLine> f_CodeLine = m_Frame_Function->m_vec_CodeLine[f_XY];

		if(f_CodeLine->m_Execute == true)
			{
			f_CodeLine->ac_Execute();
			}
		}
}

};