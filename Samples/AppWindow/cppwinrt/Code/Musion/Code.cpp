/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code.h"

using namespace ecoin;

namespace ecoin
{

Code::Code() : MuType(MuTYPE_Code), m_Index(0)
{
	acClear();
}

Code::Code(std::string f_Line, uint* f_CHK, uint f_Index, uint f_CodeType, uint f_VarType, std::shared_ptr<Variable> f_PushVar) : MuType(MuTYPE_Code), m_Index(f_Index)
{
	   /////////////////////////////////
	  // Singular 'Code' Constructor //
	 // ESL Compiler Stage I        //
	/////////////////////////////////

	acClear();

	m_Final_CHK = 0;

	m_Code = f_CodeType;
	m_VarType = f_VarType;

	m_ContractID = -1;

	std::string f_StrCode = acBufreadCodeString(f_Line, f_CHK);

	const char f_Code_DigitA = f_StrCode.at(f_StrCode.length() - 2);
	const char f_Code_DigitB = f_StrCode.at(f_StrCode.length() - 1);

	//Digits
	m_Code_DigitA = f_Code_DigitA;
	m_Code_DigitB = f_Code_DigitB;

	//reduce strcode
	f_StrCode.pop_back();
	f_StrCode.pop_back();

	//Save main code piece TextString as m_MxName
	m_MxName = f_StrCode;

	if(f_Code_DigitA == '%')
		{
		//LHS Stage 'Var' Socket
		if(f_StrCode.compare("Var") == 0)
			{
			m_Code = MuCode_Var;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

			if(m_Type[0]->m_MxVar)
				{
				m_Type[0]->m_MxVar->m_MxName = m_Name[0]->m_MxName;
				}

			int f_str_Chk = *(f_CHK);

			bool f_Scan = true;
			while(f_Scan == true)
				{
				if(f_str_Chk < f_Line.length())
					{
					char f_Chr_A = f_Line.at(f_str_Chk);

					if(f_Chr_A == '&')
						{
						char f_Chr_B = f_Line.at(f_str_Chk + 1);

						if(f_Chr_B == '%')
							{
							//If 'Value' for Var then contruct code piece
							m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var, m_VarType, m_Type[0]->m_MxVar)); //enforce same base type

							f_Scan = false;
							}
						}
					else
						{
						if(f_Chr_A == '%')
							{
							f_Scan = false;
							}
						}

					f_str_Chk++;
					}
				else
					{
					f_Scan = false;
					}
				}

			m_Final_CHK += *(f_CHK);
			}
		else if(f_StrCode.compare("Sys") == 0)
			{
			m_Code = MuCode_System;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

			if(m_Type[0]->m_MxVar)
				{
				m_Type[0]->m_MxVar->m_MxName = m_Name[0]->m_MxName;
				}

			int f_str_Chk = *(f_CHK);

			bool f_Scan = true;
			while(f_Scan == true)
				{
				if(f_str_Chk < f_Line.length())
					{
					char f_Chr_A = f_Line.at(f_str_Chk);

					if(f_Chr_A == '&')
						{
						char f_Chr_B = f_Line.at(f_str_Chk + 1);

						if(f_Chr_B == '%')
							{
							//If 'Value' for Var then contruct code piece
							m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var, m_VarType, m_Type[0]->m_MxVar)); //enforce same base type

							f_Scan = false;
							}
						}
					else
						{
						if(f_Chr_A == '%')
							{
							f_Scan = false;
							}
						}

					f_str_Chk++;
					}
				else
					{
					f_Scan = false;
					}
				}

			m_Final_CHK += *(f_CHK);
			}
		else if(f_StrCode.compare("Con") == 0)
			{
			m_Code = MuCode_Constant;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Constant));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Constant, m_VarType));

			if(m_Type[0]->m_MxVar)
				{
				m_Type[0]->m_MxVar->m_MxName = m_Name[0]->m_MxName;
				}

			int f_str_Chk = *(f_CHK);

			bool f_Scan = true;
			while(f_Scan == true)
				{
				if(f_str_Chk < f_Line.length())
					{
					char f_Chr_A = f_Line.at(f_str_Chk);

					if(f_Chr_A == '&')
						{
						char f_Chr_B = f_Line.at(f_str_Chk + 1);

						if(f_Chr_B == '%')
							{
							//If 'Value' for Var then contruct code piece
							m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var, m_VarType, m_Type[0]->m_MxVar)); //enforce same base type

							f_Scan = false;
							}
						}
					else
						{
						if(f_Chr_A == '%')
							{
							f_Scan = false;
							}
						}

					f_str_Chk++;
					}
				else
					{
					f_Scan = false;
					}
				}

			m_Final_CHK += *(f_CHK);
			}
		else if((f_StrCode.compare("ClassVar") == 0) ||
				(f_StrCode.compare("CV") == 0))
			{
			m_Code = MuCode_ClassVar;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_ClassVar));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_ClassVar));

			m_Type[0]->m_MxVar->m_MxName = m_Name[0]->m_MxName;

			m_Type[0]->m_MxVar->m_lnk_ClassVar->m_Class->m_MxName = m_Name[0]->m_MxName;

			if(m_VarType == MuVar_ClassVar_Reflect)
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));
				}
			else
				{
				uint f_UInt = 0;
				while(*(f_CHK) < (f_Line.length() - 2)) //classvar contructor so continue adding CVar x
					{
					int f_ChkStorage = *(f_CHK);

					m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

					if((m_Number[f_UInt]->m_Type[0]->m_MxName.compare("Var") == 0) ||
						(m_Number[f_UInt]->m_Type[0]->m_MxName.compare("ClassVar") == 0))
						{
						*(f_CHK) = f_ChkStorage;

						m_Number.pop_back();
						}
					else // is number
						{
						if(m_Number[f_UInt]->m_Type[0]->m_MxVar)
							{
							m_Number[f_UInt]->m_Type[0]->m_MxVar->m_MxName = m_Number[f_UInt]->m_Name[0]->m_MxName;
							}
						}

					f_UInt++;
					}

				//Activate LHS of ClassVar
				m_Final_CHK += *(f_CHK);
				}
			}
		else if((f_StrCode.compare("For") == 0) ||
				(f_StrCode.compare("for") == 0))
			{
			m_Code = MuCode_For_Loop;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Operator)); //push name

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[0]->m_Type[0]->m_MxVar)
					{
					m_Number[0]->m_Type[0]->m_MxVar->m_MxName = m_Number[0]->m_Name[0]->m_MxName;
					}
				}

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[1]->m_Type[0]->m_MxVar)
					{
					m_Number[1]->m_Type[0]->m_MxVar->m_MxName = m_Number[1]->m_Name[0]->m_MxName;
					}
				}

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[2]->m_Type[0]->m_MxVar)
					{
					m_Number[2]->m_Type[0]->m_MxVar->m_MxName = m_Number[2]->m_Name[0]->m_MxName;
					}
				}
			}
		else if(f_StrCode.compare("Return") == 0)
			{
			m_Code = MuCode_Return;

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[0]->m_Type[0]->m_MxVar)
					{
					m_Number[0]->m_Type[0]->m_MxVar->m_MxName = m_Number[0]->m_Name[0]->m_MxName;
					}
				}
			}
		else if(f_StrCode.compare("Template") == 0)
			{
			m_Code = MuCode_Template;

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[0]->m_Type[0]->m_MxVar)
					{
					m_Number[0]->m_Type[0]->m_MxVar->m_MxName = m_Number[0]->m_Name[0]->m_MxName;
					}
				}
			}
		else if(f_StrCode.compare("Opr") == 0) //Operator Mid Stage
			{
			m_Code = MuCode_Operator;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Operator));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_ClassVar));

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Operator, m_VarType)); //enforce same base type

				if(m_Number[0]->m_Type[0]->m_MxVar)
					{
					m_Number[0]->m_Type[0]->m_MxVar->m_MxName = m_Number[0]->m_Name[0]->m_MxName;
					}
				}
			}
		else if((f_StrCode.compare("Ifs") == 0) ||
				(f_StrCode.compare("Cond") == 0) ||
				(f_StrCode.compare("Conditional") == 0)) //Conditional Mid Stage
			{
			m_Code = MuCode_Condition;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Condition));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_ClassVar));

			if(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Condition, m_VarType));

				if(m_Number[0]->m_Type[0]->m_MxVar)
					{
					m_Number[0]->m_Type[0]->m_MxVar->m_MxName = m_Number[0]->m_Name[0]->m_MxName;
					}
				}
			}
		else if((f_StrCode.compare("Fcn") == 0) ||
				(f_StrCode.compare("Func") == 0) ||
				(f_StrCode.compare("Call") == 0) ||
				(f_StrCode.compare("FunctionCall") == 0))  //Possible Function Call Mid Stage
			{
			m_Code = MuCode_Function;

			m_Type.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Function));

			m_VarType = m_Type[0]->m_VarType;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Function));

			uint f_UInt = 0;
			while(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[f_UInt]->m_Type[0]->m_MxVar)
					{
					m_Number[f_UInt]->m_Type[0]->m_MxVar->m_MxName = m_Number[f_UInt]->m_Name[0]->m_MxName;
					}

				f_UInt++;
				}
			}
		else if((f_StrCode.compare("Fus") == 0) ||
				(f_StrCode.compare("Def") == 0) ||
				(f_StrCode.compare("FuncDef") == 0) ||
				(f_StrCode.compare("Function") == 0) ||
				(f_StrCode.compare("FuncStart") == 0) ||
				(f_StrCode.compare("FunctionStart") == 0))  //Possible Function Definition Mid Stage
			{
			m_Code = MuCode_FunctionStart;

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Function));

			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Function));

			uint f_UInt = 0;
			while(*(f_CHK) < (f_Line.length() - 2))
				{
				m_Number.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode_Var));

				if(m_Number[f_UInt]->m_Type[0]->m_MxVar)
					{
					m_Number[f_UInt]->m_Type[0]->m_MxVar->m_MxName = m_Number[f_UInt]->m_Name[0]->m_MxName;
					}

				f_UInt++;
				}
			}
		else if((f_StrCode.compare("ClassStart") == 0) || (f_StrCode.compare("Class") == 0))   //Possible Class Definition Mid Stage
			{
			m_Code = MuCode_ClassStart;

			//namespace domain
			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode::MuCode_ClassStart));

			//class name
			m_Name.push_back(std::make_shared<Code>(f_Line, f_CHK, f_Index, MuCode::MuCode_ClassStart));
			}
		else
			{
			//ESL-Null name save...
			}
		}
	else if(f_Code_DigitA == '*' &&		// Verified as operator tag
			f_Code_DigitB == '*')
		{
		m_VarType = agFind_OprType(f_StrCode);
		}
	else if(f_Code_DigitA == '^' &&		// Verified as condition tag
			f_Code_DigitB == '^')
		{
		m_VarType = agFind_ConType(f_StrCode);
		}
	else if(f_Code_DigitA == '?' &&		// Verified as reflected function tag
			f_Code_DigitB == '?')
		{
		m_VarType = MuFunc_Reflection;

		std::string f_Str = m_MxName;
		m_MxName.clear();

		std::string f_Caddy = "";

		int f_HeadState = 0;

		for(int f_XY = 0; f_XY < f_Str.length(); f_XY++)
			{
			char f_C = f_Str.at(f_XY);

			switch(f_HeadState)
				{
				case 0:
					{
					if(f_C == '-')
						{
						m_Cvref_Name = f_Caddy;

						f_Caddy.clear();

						f_HeadState++;
						}
					else
						{
						f_Caddy.push_back(f_C);
						}
					}break;

				case 1:
					{
					if(f_C == '>')
						{
						f_Caddy.clear();

						f_HeadState++;
						}
					}break;

				default:
					{
					if(f_XY == f_Str.length() - 1)
						{
						m_Cvref_FuncName = f_Caddy;

						f_Caddy.clear();

						f_HeadState++;
						}
					else
						{
						f_Caddy.push_back(f_C);
						}
					}break;
				}
			}
		}
	else if(f_Code_DigitA == '&') //// '&' + ' '
		{
		if(f_Code_DigitB == '&')
			{
			m_VarType = agFind_Precision(f_StrCode);	 //find type of var

			//add variable
			m_MxVar = std::make_shared<Variable>("FreshVar", MuCode::MuCode_Var);
			}
		else if(f_Code_DigitB == '*')
			{
			m_VarType = agFind_FunctionType(f_StrCode);	 //any function call
			}
		else if(f_Code_DigitB == '%')
			{
#ifdef ECOIN_DEBUG_BREAKS
			if(!f_PushVar)
				{
				__debugbreak(); //add debug message
				}
#endif

			if(m_VarType == MuVar_Int ||
			   m_VarType == MuVar_UInt ||
			   m_VarType == MuVar_Int2 ||
			   m_VarType == MuVar_Int3 ||
			   m_VarType == MuVar_Int4 ||
			   m_VarType == MuVar_Bool ||
			   m_VarType == MuVar_Char ||
			   m_VarType == MuVar_UChar)
				{
				if(m_MxName.compare("Random") == 0)
					{
					f_PushVar->m_Action = MuAct_Random;
					}
				else if(m_MxName.compare("Rand") == 0)
					{
					f_PushVar->m_Action = MuAct_RandInt;
					}
				else
					{
					f_PushVar->m_Action = MuAct_Start;

					f_PushVar->set_Value(::atoi(m_MxName.c_str()));
					}
				}
			else if(m_VarType == MuVar_Float ||
					m_VarType == MuVar_Float2 ||
					m_VarType == MuVar_Float3 ||
					m_VarType == MuVar_Float4 ||
					m_VarType == MuVar_Double)
				{
				if(m_MxName.compare("Random") == 0)
					{
					f_PushVar->m_Action = MuAct_Random;
					}
				else if(m_MxName.compare("Rand") == 0)
					{
					f_PushVar->m_Action = MuAct_RandInt;
					}
				else
					{
					f_PushVar->m_Action = MuAct_Start;

					f_PushVar->set_Value((float)atof(m_MxName.c_str()));
					}
				}
			else if(m_VarType == MuVar_String)
				{
				f_PushVar->m_Action = MuAct_Start;

				f_PushVar->set_Value(m_MxName);
				}
			}
		else if(f_Code_DigitB == '?')	//classvar from reflection
			{
			m_VarType = MuVar_ClassVar_Reflect;
			}
		else if(f_Code_DigitB == '$')	//classvar from loaded dependencies
			{
			m_VarType = MuVar_ClassVar_Class;

			//add variable caddy for ClassVar
			m_MxVar = std::make_shared<Variable>("FreshClassCaddy", MuCode::MuCode_Var);
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			}
#endif
#if 0
		else if(f_Code_DigitB == '$')	//classvar vector or otherwise contained
			{
			m_VarType = MuVar_ClassVar_Typename;

			std::string f_VarTypeStr;

			f_VarTypeStr.clear();

			int f_HeadMode = 0;

			for(int f_Jet = 0; f_Jet < f_StrCode.length(); f_Jet++)
				{
				char f_c = f_StrCode.at(f_Jet);

				if(f_HeadMode == 0)
					{
					if(f_c == '<')
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();
						}
					else if(f_c == '>')
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();

						f_HeadMode = 1;
						}
					else
						{
						f_VarTypeStr.push_back(f_c);
						}

					if(f_Jet >= f_StrCode.length() - 1)
						{
						m_vec_Type.push_back(f_VarTypeStr);

						f_VarTypeStr.clear();
						}
					}
				}

			if(m_vec_Type.size() > 1) //vector
				{
				for(int f_XY = 0; f_XY < m_vec_Type.size(); f_XY++)
					{
					if((m_vec_Type[f_XY].compare("vector") == 0) ||
						(m_vec_Type[f_XY].compare("std::vector") == 0))
						{
						bool f_Found = false;

						for(int f_Jet = 0; f_Jet < g_Class.size() - 1; f_Jet++)
							{
							if(g_Class[f_Jet]->m_MxName.compare(m_vec_Type[f_XY + 1]) == 0)
								{
								f_Found = true;
								m_Class = g_Class[f_Jet];
								}
							}

						if(f_Found == true)
							{
							m_vec_VarType.push_back(f_XY);
							m_VarType = 1;
							}
						else
							{
							m_vec_VarType.push_back(-1);
							m_VarType = -1;
							}
						}
					}
				}
			else
				{
				bool f_Found = false;

				for(int f_XY = 0; f_XY < g_Class.size(); f_XY++)
					{
					if(g_Class[f_XY]->m_MxName.compare(m_vec_Type[f_XY]) == 0)
						{
						f_Found = true;
						m_Class = g_Class[f_XY];
						}
					}

				if(f_Found == true)
					{
					m_vec_VarType.push_back(0);
					m_VarType = 1;
					}
				else
					{
					m_vec_VarType.push_back(-1);
					m_VarType = -1;
					}
				}
			}
#endif
		}
	}

void Code::acPrepare_CallNames(void)
{
	std::vector<std::string> f_vec_ClassVarName;

	f_vec_ClassVarName.clear();

	if(m_Type.size() == 1)
		{
		if(m_Type[0]->m_MxVar)
			{
			f_vec_ClassVarName.push_back(m_Name[0]->m_MxName);
			}
		}

	for(int f_IDX = 0; f_IDX < m_Number.size(); f_IDX++)
		{
		if(m_Number[f_IDX]->m_Type.size() == 1)
			{
			if(m_Number[f_IDX]->m_Type[0]->m_MxVar)
				{
				f_vec_ClassVarName.push_back(m_Number[f_IDX]->m_Name[0]->m_MxName);
				}
			}
		}

	for(int f_XY = 0; f_XY < f_vec_ClassVarName.size(); f_XY++)
		{
		std::string f_ClassVarName = f_vec_ClassVarName[f_XY];

		int f_PointerClassMemberVar = 0;
		int f_IndexClassMemberVar = 0;

		std::vector<int> f_vec_PointerClassTypeMeM;
		std::vector<int> f_vec_IndexClassTypeMeM;

		f_vec_PointerClassTypeMeM.clear();
		f_vec_IndexClassTypeMeM.clear();

		std::string f_Carriage = "";

		m_vec_NameCall.clear();

		for(int f_Jet = 0; f_Jet < f_ClassVarName.length(); f_Jet++)
			{
			char f_c = f_ClassVarName.at(f_Jet);

			if(f_IndexClassMemberVar == 0)
				{
				if(f_PointerClassMemberVar == 0)
					{
					if(f_c == '-') //classvar-
						{
						f_PointerClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
						f_Carriage.clear();
						}
					else if(f_c == '[') //classvar[
						{
						throw; //add debug message no native vector error
						}
					else  //classv
						{
						f_Carriage.push_back(f_c);
						}

					if(f_Jet >= f_ClassVarName.length() - 1) //classvar
						{
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_VarVar);
						f_Carriage.clear();
						}
					}
				else if(f_PointerClassMemberVar == 1)
					{
					if(f_c == '>') //classvar->
						{
						f_PointerClassMemberVar = 2;
						}
					}
				else if(f_PointerClassMemberVar == 2)
					{
					if(f_c == '-') //classvar->classvar-
						{
						f_PointerClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
						f_Carriage.clear();
						}
					else if(f_c == '[') //classvar->membervar[ assume evector
						{
						f_IndexClassMemberVar = 1;
						f_PointerClassMemberVar = 0;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
						f_Carriage.clear();
						}
					else if(f_c == ']') //!!!classvar->classvar]
						{
						throw; //add debug message syntax error extra square close bracket
						}
					else
						{
						f_Carriage.push_back(f_c);
						}

					if(f_Jet >= f_ClassVarName.length() - 1) //classvar->membervar
						{
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
						}
					}
				}
			else if(f_IndexClassMemberVar == 1)
				{
				if(f_PointerClassMemberVar == 0)
					{
					if(f_c == '-') //classvar->classvar[f_adindex-   //after -//classvar->classvar[f_adindex->m_ad[f_Jet-
						{
						f_PointerClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
						f_Carriage.clear();
						}
					else if(f_c == '[') //!!!classvar->classvar[f_adindex[   //after -//!!!classvar->classvar[f_adindex->m_ad[f_Jet[
						{
						throw; //add debug message no native vector error
						}
					else if(f_c == ']') //classvar->classvar[f_adindex] check for win length   //after -//classvar->classvar[f_adindex->m_ad[f_Jet]
						{
						f_IndexClassMemberVar = 2;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_VarIndexInt);
						f_Carriage.push_back(f_c); //fixme check for native int at run-time
						}
					else
						{
						f_Carriage.push_back(f_c);
						}

					if((f_Jet >= f_ClassVarName.length() - 1) && (f_c != ']'))
						{
						throw;
						}
					}
				else if(f_PointerClassMemberVar == 1)
					{
					if(f_c == '>') //classvar->classvar[f_adindex->
						{
						f_PointerClassMemberVar = 2;
						f_Carriage.clear();
						}
					}
				else if(f_PointerClassMemberVar == 2)
					{
					if(f_c == '>') //!!!classvar->classvar[f_adindex->>
						{
						throw; //add debug message
						}
					if(f_c == '-') //classvar->classvar[f_adindex->m_ad-
						{
						f_PointerClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
						f_Carriage.clear();
						}
					else if(f_c == ']') //classvar->classvar[f_adindex->m_ad] check for win conditions
						{
						f_IndexClassMemberVar = 2;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberIndexInt);
						f_Carriage.clear();
						}
					else if(f_c == '[') //classvar->classvar[f_adindex->m_ad[
						{
						f_PointerClassMemberVar = 0;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
						f_Carriage.clear();
						}
					else
						{
						f_Carriage.push_back(f_c);
						}
									
					if((f_Jet >= f_ClassVarName.length() - 1) && (f_c != ']'))
						{
						throw; //add debugging message vector index syntax error
						}
					}
				else
					{
					throw; //add debug message
					}
				}
			else if(f_IndexClassMemberVar == 2)
				{
				if(f_PointerClassMemberVar == 0)
					{
					if(f_c == '-') //classvar->classvar[f_adindex]-
						{
						f_PointerClassMemberVar = 1;
						f_Carriage.clear();
						}
					else if(f_c == '[') //classvar->classvar[f_adindex][
						{
						f_IndexClassMemberVar = 1;
						f_Carriage.clear();
						}
					else
						{
						throw; //add debug message array index or close name only
						}
					}
				else if(f_PointerClassMemberVar == 1)
					{  //classvar->classvar[f_adindex]-
					if(f_c == '>')
						{
						f_PointerClassMemberVar = 2;
						}
					else
						{
						throw; //add debug message syntax error
						}
					}
				else if(f_PointerClassMemberVar == 2)
					{
					if(f_c == '-') //classvar->membervar[f_adindex]->m_var-
						{
						f_PointerClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_ClassVar);
						f_Carriage.clear();
						}
					else if(f_c == '[')  //classvar->membervar[f_adindex]->m_var[
						{
						f_IndexClassMemberVar = 1;
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
						f_Carriage.clear();
						}
					else if(f_c == ']')
						{
						throw; //add debug message syntax error vector array close symbol
						}
					else
						{
						f_Carriage.push_back(f_c);
						}

					if(f_Jet >= f_ClassVarName.length() - 1) //classvar->membervar[f_adindex]->m_membervar
						{
						m_vec_NameCall.push_back(f_Carriage);
						m_vec_NameCallType.push_back(MuNameCall_Type_MemberVar);
						f_Carriage.clear();
						}
					}
				}
			}
		}
}

};