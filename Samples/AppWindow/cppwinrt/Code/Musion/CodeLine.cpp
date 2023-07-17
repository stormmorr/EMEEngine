/*

CodeLine - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/Work/Contract.h"

using namespace ecoin;

namespace ecoin
{
std::shared_ptr<ClassVar> g_BaseNode;
std::vector<std::shared_ptr<ClassVar>> g_vec_BaseNode;

#ifdef SEPER_ANY_CAST
#ifndef HAS_BOOST_ANY_CAST
template<class T>
T ag_any_cast(boost::any f_Any)
{
	try
		{
		return boost::any_cast<T>(f_Any);
		}

	catch (boost::bad_any_cast &e)
		{

#if 0
		std::cerr << e.what() << '\n';
#endif

#if 1
		__debugbreak();
#endif

		return T(0);
		}
}
#else
#define ag_any_cast boost::any_cast
#endif
#endif

CodeLine::CodeLine(std::string f_Line, uint* f_CHK, System* f_System)
{
	acClear();

	m_CodeString = f_Line;
	m_System = f_System;

	int f_Size = f_Line.length();

	if(*(f_CHK) < f_Size - 2)
		{
		std::shared_ptr<Code> f_CodeLeft = std::make_shared<Code>(f_Line, f_CHK, 0);

		m_vec_Code.push_back(f_CodeLeft);

		if(f_CodeLeft->m_Final_CHK > 0) //if LHS provided
			{
			m_vec_Variable.push_back(f_CodeLeft->m_Type[0]->m_MxVar);
			}

		bool f_Scan = true;

		 ///////////////
		// Scan !END //
		if(f_Scan)
			{
			f_Scan = (*(f_CHK) < f_Size) ? true : false;

			if(f_Scan == true)
				{
				m_Returning = true;

				std::shared_ptr<Code> f_Code_MidRight = std::make_shared<Code>(f_Line, f_CHK, 0);

				m_vec_Code.push_back(f_Code_MidRight);
				}
			}
		}

	//One on if '\n'
	*(f_CHK) = *(f_CHK) + 1;

	    /////////////////////////////////////////////////////////////
	   /////////////////////////////////////////////////////////////
	  // Compiler Setup
	 // ESL Compiler Stage II Linear Assign Construction
	//
	uint f_CodeSize = m_vec_Code.size();

	//set initial value
	m_CodeLine = -1000;

	uint f_Count = 0;
	while(f_Count < f_CodeSize)
		{
		std::shared_ptr<Code> f_Code = m_vec_Code[f_Count];

		f_Code->acPrepare_CallNames();

		switch(f_Code->m_Code)
			{
			case MuCode_Var:	//var socket...accepts Variable stdptr from result of either
				{
				if(f_Count == 0) //position 0
					{
					if(f_CodeSize == 1)
						{
						if(f_Code->m_Code == MuCode_Return)
							{
							m_CodeLine = MuLine_Return;

							if(f_Code->m_Number.size() == 1)
								{
								m_Returning = true;

								m_vec_Variable.push_back(f_Code->m_Number[0]->m_Type[0]->m_MxVar);
								}
							else if(f_Code->m_Number.size() > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak(); //add debug msg
#endif
								}
							else
								{
								m_Returning = false;
								}
							}
						else
							{
							m_CodeLine = MuLine_Init_Var;
							}
						}
					else if(f_CodeSize == 2)
						{
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if(f_Code->m_Code == MuCode_Return)
							{
							m_CodeLine = MuLine_Return;

							if(f_Code->m_Number.size() == 1)
								{
								m_Returning = true;

								m_vec_Variable.push_back(f_Code->m_Number[0]->m_Type[0]->m_MxVar);
								}
							else if(f_Code->m_Number.size() > 1)
								{
#ifdef ECOIN_DEBUG_BREAKS
								__debugbreak(); //add debug msg
#endif
								}
							else
								{
								m_Returning = false;
								}
							}
						else if(f_Code->m_Code == MuCode_Template)
							{
							m_CodeLine = MuLine_Template; //not possible

#ifdef ECOIN_DEBUG_BREAKS
							__debugbreak(); //add debug msg
#endif
							}
						else if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType == MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function_Reflect;
								}
							else
								{
								m_CodeLine = MuLine_Function;
								}

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Function)
							{
							if(f_CodePositionOne->m_VarType == MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Operator)
							{
							m_CodeLine = MuLine_Assign_Opr;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else
							{
							m_CodeLine = MuLine_Assign;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					else // 'else' Any f_CodeSize //
						{
						std::shared_ptr<Code> f_Upper_CodePositionOne = m_vec_Code[1];

						if(f_Upper_CodePositionOne->m_Code == MuCode_Condition) //if line assign conditional can contain operators >>>>>
							{
							m_CodeLine = MuLine_Condition_Ajax;

							for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Upper_CodePositionOne->m_Code == MuCode_Operator) //if line assign operator can contain conditionals >>>>>
							{
							m_CodeLine = MuLine_Assign_Opr;

							for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Function) //function Code[0]
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Upper_CodePositionOne->m_Code == MuCode_Function) //function Code[1]
							{
							if(f_Upper_CodePositionOne->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Upper_CodePositionOne->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Upper_CodePositionOne->m_Code == MuCode_Operator)
							{
							m_CodeLine = MuLine_Assign_Opr;

							for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Upper_CodePositionOne->m_Code == MuCode_Condition)
							{
							m_CodeLine = MuLine_Condition_Ajax;

							for(int f_XY = 0; f_XY < f_Upper_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Upper_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					}
				else if(f_Count == 1) //position one [1]
					{
					if(f_CodeSize == 1)
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak(); //add debug msg
#endif
						}
					else if(f_CodeSize == 2)
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

						if(f_CodePositionZero->m_Code == MuCode_Template)
							{
							m_CodeLine = MuLine_Template; //not possible

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Function)
							{
							if(f_CodePositionZero->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Return)
							{
							m_CodeLine = MuLine_Return;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
#if 0
						else
							{
							m_CodeLine = MuLine_Assign;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
#endif
						}
					else if(f_CodeSize == 4)
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

						if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Function)
							{
							if(f_CodePositionZero->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Operator)
							{
							m_CodeLine = MuLine_Assign_Opr;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Condition)
							{
							m_CodeLine = MuLine_Condition_Ajax;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_For_Loop)
							{
							m_CodeLine = MuLine_For_Loop;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_ClassVar)
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						//else add long operator or condition
						}
					else // Unlimited size...
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

						if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Function)
							{
							if(f_CodePositionZero->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_ClassVar)
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Operator)
							{
							m_CodeLine = MuLine_Assign_Opr;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Condition)
							{
							m_CodeLine = MuLine_Condition_Ajax;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
#ifdef ECOIN_DEBUG_BREAKS
						else
							{
							__debugbreak(); //add debug msg
							}
#endif
						}
					}
#ifdef ECN_TRIPLE_ASSIGN_DEPTH
				else if(f_Count >= 2) //position 2
					{
					if(f_CodeSize == 1)
						{
						__debugbreak(); //add debug message impossible
						}
					else if(f_CodeSize == 2)
						{
						__debugbreak(); //add debug message impossible
						}
					else
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if(f_CodePositionOne->m_Code == MuCode_Condition)
							{
							m_CodeLine = MuLine_Condition_Ajax;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Function)
							{
							if(f_CodePositionZero->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Function)
							{
							if(f_CodePositionOne->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_ClassVar)
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_For_Loop)
							{
							m_CodeLine = MuLine_For_Loop;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					}
#else
#ifdef ECOIN_DEBUG_BREAKS
				else //if reached this point ESL_CodeLine unknown
					{
					__debugbreak(); //add debug message
					}
#endif
#endif
				}break;

			case MuCode_ClassVar:
				{
				if(f_Count == 0)
					{
					if(f_CodeSize == 1)
						{
						m_CodeLine = MuLine_Init_ClassVar;
						}
					else if(f_CodeSize == 2)
						{
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Function)
							{
							if(f_CodePositionOne->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_Code->m_Code == MuCode_Return)
							{
							m_CodeLine = MuLine_Return;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Var)
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_ClassVar)
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					else // Unlimited size
						{
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if(f_Code->m_Code == MuCode_Function)
							{
							if(f_Code->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_Code->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Function)
							{
							if(f_CodePositionOne->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else
							{
							m_CodeLine = MuLine_Init_ClassVar;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					}
				else if(f_Count == 1)
					{
					if(f_CodeSize <= 2)
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if(f_CodePositionZero->m_Code == MuCode_Return)
							{
							m_CodeLine = MuLine_Return;

							m_Returning = true;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Template)
							{
							m_CodeLine = MuLine_Template;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_Function)
							{
							if(f_CodePositionZero->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;

								for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							}
						else if(f_CodePositionZero->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionZero->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionZero->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_Function)
							{
							if(f_CodePositionOne->m_VarType != MuFunc_Reflection)
								{
								m_CodeLine = MuLine_Function;

								for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
									{
									m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
									}
								}
							else
								{
								m_CodeLine = MuLine_Function_Reflect;
								}
							}
						else if(f_CodePositionOne->m_Code == MuCode_FunctionStart)
							{
							m_CodeLine = MuLine_Function_Custom;

							for(int f_XY = 0; f_XY < f_CodePositionOne->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_CodePositionOne->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					else if(f_CodeSize == 3)
						{
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if((f_Code->m_Code == MuCode_Function) || (f_CodePositionOne->m_Code == MuCode_Function))
							{
							m_CodeLine = MuLine_Function;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					}
#ifdef ECN_TRIPLE_ASSIGN_DEPTH
				else if(f_Count == 2) //Count = 2
					{
					if(f_CodeSize == 2)
						{
						__debugbreak(); //add debug message impossible
						}
					else if(f_CodeSize == 3)
						{
						std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];
						std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

						if((f_CodePositionZero->m_Code == MuCode_Function) || (f_CodePositionOne->m_Code == MuCode_Function))
							{
							m_CodeLine = MuLine_Function;

							for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
								{
								m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
								}
							}
						}
					else if(f_CodeSize == 1)
						{
						__debugbreak(); //add debug message impossible
						}
					else if(f_CodeSize == 4)
						{
						m_CodeLine = MuLine_Function;

						for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
							{
							m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
							}
						}
					}
				else if(f_Count == 3)
					{
					if(f_CodeSize == 2)
						{
						__debugbreak(); //add debug message impossible
						}
					else if(f_CodeSize == 3)
						{
						__debugbreak(); //add debug message
						}
					else if(f_CodeSize == 1)
						{
						__debugbreak(); //add debug message impossible
						}
					else if(f_CodeSize == 4)
						{
						m_CodeLine = MuLine_Function;
						}
#else
#ifdef ECOIN_DEBUG_BREAKS
				else
					{
					__debugbreak();
					}
#endif
#endif
				}break;

			case MuCode_Function:
				{
				m_CodeLine = MuLine_Function;

				std::shared_ptr<Code> f_CodePositionZero = m_vec_Code[0];

				if(f_CodePositionZero->m_Type[0]->m_VarType == MuFunc_Custom)
					{ // Custom Function
					m_CodeLine = MuLine_Function_Custom;
					}
				else if(f_CodePositionZero->m_Type[0]->m_VarType == MuLine_Function)
					{  // Math, System and Other (already generated) Function Calls
					m_CodeLine = MuLine_Function;
					}
				else if(f_CodePositionZero->m_Type[0]->m_VarType == MuLine_Function_Reflect)
					{  // System and Other (reflection) Function Calls
					m_CodeLine = MuLine_Function_Reflect;
					}
				else if(m_vec_Code.size() > 1)
					{
					std::shared_ptr<Code> f_CodePositionOne = m_vec_Code[1];

					if(f_CodePositionOne->m_Type[0]->m_VarType == MuFunc_Custom)
						{ // Custom Function
						m_CodeLine = MuLine_Function_Custom;
						}
					else if(f_CodePositionOne->m_Type[0]->m_VarType == MuLine_Function)
						{  // Math, System and Other (already generated) Function Calls
						m_CodeLine = MuLine_Function;
						}
					else if(f_CodePositionOne->m_Type[0]->m_VarType == MuLine_Function_Reflect)
						{  // System and Other (reflection) Function Calls
						m_CodeLine = MuLine_Function_Reflect;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak(); //add debug msg
						}
#endif
					}

				for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
					{
					m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
					}
				}break;

			case MuCode_FunctionStart:
				{
				m_CodeLine = MuLine_Function_Custom;

				std::shared_ptr<Code> f_CodeA = m_vec_Code[0];
				std::shared_ptr<Code> f_CodeX = nullptr;

				if(f_CodeA->m_Code == MuCode_FunctionStart)
					{
					f_CodeX = f_CodeA;
					}
				else
					{
					if(m_vec_Code.size() > 1)
						{
						f_CodeA = m_vec_Code[1];

						if(f_CodeA->m_Code == MuCode_FunctionStart)
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

				for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
					{
					m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
					}
				}break;
					
			case MuCode_ClassStart:
				{
				m_CodeLine = MuLine_ClassStart;
				}break;

			case MuCode_System:
				{
				if(f_Count > 0)
					{
					if(f_Code->m_Number.size() == 1 && f_CodeSize == 1)
						{
						if((m_CodeLine != MuLine_Init_ClassVar) && 
							(m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Init_Var;
							}

						for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
							{
							m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
							}

						if(f_Code->m_Type.size() > 0)
							{
							m_vec_Variable.push_back(f_Code->m_Type[0]->m_MxVar);
							}
						}
					else
						{
						if((m_CodeLine != MuLine_Init_ClassVar) && 
							(m_CodeLine != MuLine_Assign_Opr) &&
							(m_CodeLine != MuLine_Function) &&
							(m_CodeLine != MuLine_Function_Custom) &&
							(m_CodeLine != MuLine_Condition_Ajax) &&
							(m_CodeLine != MuCode_For_Loop))
							{
							m_CodeLine = MuLine_Assign;
							}

						for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
							{
							m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
							}

						if(f_Code->m_Type.size() > 0)
							{
							m_vec_Variable.push_back(f_Code->m_Type[0]->m_MxVar);
							}
						}
					}
				else
					{
					if((m_CodeLine != MuLine_Init_ClassVar) && 
						(m_CodeLine != MuLine_Assign_Opr) &&
						(m_CodeLine != MuLine_Function) &&
						(m_CodeLine != MuLine_Function_Custom) &&
						(m_CodeLine != MuLine_Condition_Ajax) &&
						(m_CodeLine != MuCode_For_Loop))
						{
						m_CodeLine = MuLine_Init_Var;
						}

					m_vec_Variable.push_back(m_System->av_Var(f_Code->m_Name[0]->m_MxName));

					for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
						{
						m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
						}

					if(f_Code->m_Type.size() > 0)
						{
						m_vec_Variable.push_back(f_Code->m_Type[0]->m_MxVar);
						}
					}
				}break;

			case MuCode_Constant:
				{
				if((m_CodeLine != MuLine_Init_ClassVar) && 
					(m_CodeLine != MuLine_Assign_Opr) &&
					(m_CodeLine != MuLine_Function) &&
					(m_CodeLine != MuLine_Function_Custom) &&
					(m_CodeLine != MuLine_Condition_Ajax) &&
					(m_CodeLine != MuCode_For_Loop))
					{
					m_CodeLine = MuLine_Init_Var;
					}

#ifdef ECOIN_DEBUG_BREAKS
				if(f_Code->m_Number.size() != 1)
					{
					__debugbreak();
					}
#endif

				m_vec_Variable.push_back(f_Code->m_Number[0]->m_Type[0]->m_MxVar);
				}break;

			case MuCode_For_Loop:
				{
				m_CodeLine = MuLine_For_Loop;

				for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
					{
					m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
					}
				}break;

			case MuCode_Operator:
				{
				m_CodeLine = MuLine_Assign_Opr;

				int f_OpIntID = 0; // increment operator count

				std::shared_ptr<Code> f_LtCode = m_vec_Code[0];
				std::shared_ptr<Code> f_OpCode = m_vec_Code[1];
				std::shared_ptr<Code> f_RtCode = f_OpCode->m_Number[0];

				std::shared_ptr<Operator> f_Operator = std::make_shared<Operator>(f_OpCode->m_MxName);

				f_Operator->m_Operator = f_OpCode->m_Type[0]->m_VarType;

				std::string f_L_StrCode = f_LtCode->m_MxName;
				std::string f_R_StrCode = f_RtCode->m_MxName;
				std::string f_L_StrCodeName = f_LtCode->m_Name[0]->m_MxName;
				std::string f_R_StrCodeName = f_RtCode->m_Name[0]->m_MxName;

				if(f_LtCode->m_vec_NameCall.size() == 1)
					{
					if(f_L_StrCode.compare("Sys") == 0)
						{
						if(f_L_StrCodeName.compare("Pos") == 0)
							{
							f_Operator->leftHand = m_System->Pos;
							}
						if(f_L_StrCodeName.compare("Posx") == 0)
							{
							f_Operator->leftHand = m_System->Posx;
							}
						if(f_L_StrCodeName.compare("Posy") == 0)
							{
							f_Operator->leftHand = m_System->Posy;
							}
						if(f_L_StrCodeName.compare("Posz") == 0)
							{
							f_Operator->leftHand = m_System->Posz;
							}
						else if(f_L_StrCodeName.compare("Color") == 0)
							{
							f_Operator->leftHand = m_System->Color;
							}
						}
					else if(f_L_StrCode.compare("Var") == 0) //standard var slot pass on variable
						{
						f_Operator->leftHand = f_LtCode->m_Type[0]->m_MxVar;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak();
						}
#endif
					}
				else if(f_LtCode->m_vec_NameCall.size() == 2) //assign to classvar var
					{
					if(f_L_StrCode.compare("Var") == 0)
						{
						f_Operator->leftHand = f_LtCode->m_Number[0]->m_Type[0]->m_MxVar;
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

				if(f_OpCode->m_vec_NameCall.size() == 1)
					{
					if(f_R_StrCode.compare("Sys") == 0)
						{
						if(f_R_StrCodeName.compare("Pos") == 0)
							{
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_Type[0]->m_MxVar;
							}
						else if(f_R_StrCodeName.compare("Posx") == 0)
							{
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_Type[0]->m_MxVar;
							}
						else if(f_R_StrCodeName.compare("Posy") == 0)
							{
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_Type[0]->m_MxVar;
							}
						else if(f_R_StrCodeName.compare("Posz") == 0)
							{
							f_Operator->rightHand = f_RtCode->m_Number[0]->m_Type[0]->m_MxVar;
							}
						else if(f_R_StrCodeName.compare("Color") == 0)
							{
							f_Operator->rightHand = f_RtCode->m_MxVar;
							}
						else
							{
							__debugbreak(); //add system not found
							}
						}
					else if(f_R_StrCode.compare("Var") == 0)
						{
						f_Operator->rightHand = f_OpCode->m_Number[0]->m_Type[0]->m_MxVar;
						}
#ifdef ECOIN_DEBUG_BREAKS
					else
						{
						__debugbreak();
						}
#endif
					}
				else if(f_OpCode->m_vec_NameCall.size() == 2) //assign to classvar var
					{
					if(f_R_StrCode.compare("Var") == 0)
						{
						f_Operator->rightHand = f_OpCode->m_Number[0]->m_Type[0]->m_MxVar;
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

				//Oper Push
				m_vec_Operator.push_back(f_Operator);
				}break;

			case MuCode_Condition:
				{
				m_CodeLine = MuLine_Condition_Ajax;
				}break;

			case MuCode_Return:
				{
				m_CodeLine = MuLine_Return;

				for(int f_XY = 0; f_XY < f_Code->m_Number.size(); f_XY++)
					{
					m_vec_Variable.push_back(f_Code->m_Number[f_XY]->m_Type[0]->m_MxVar);
					}
				}break;

			case MuCode_Override:
				{ /////////////
				 /// Pause ///
				/////////////
				}break;
			}

		f_Count++;
		} //END While(f_Count < f_CodeSize)
}

CodeLine::~CodeLine()
{
	acClear();
}

int CodeLine::acSearch_CodeType(uint f_TYPE)
{
	for(uint f_CT = 0; f_CT < m_vec_Code.size(); f_CT++)
		{
		std::shared_ptr<Code> f_Code = m_vec_Code[f_CT];

		if(f_Code->m_Code == f_TYPE)
			{
			return f_CT;
			}
		}

	return -5;
}

std::shared_ptr<Variable> Code::acCodeCall_Var(int f_Index, int f_MaxIndex, std::shared_ptr<Variable> f_Variable, std::shared_ptr<Contract> f_Contract, int f_FindIndexInt)
{
	switch(m_vec_NameCallType[f_Index])
		{
		case MuNameCall_Type_VarVar:
			{
			if(f_FindIndexInt == 0)
				{
				std::shared_ptr<Variable> f_Var = ag_Find_Var(m_vec_NameCall[f_Index], f_Variable, f_Contract);

				return f_Var;  //win!
				}
#ifdef ECOIN_DEBUG_BREAKS
			else  //is array index varint check for integer
				{
				__debugbreak();
				}
#endif
			}break;

		case MuNameCall_Type_VarIndexInt:
			{
			if(f_FindIndexInt == 0)
				{
#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //add debug message integer index var out of position
#endif
				}
			else if(f_FindIndexInt == 1)  //is array index varint check for integer
				{
				std::shared_ptr<Variable> f_VarIndexInt = ag_Find_Var(m_vec_NameCall[f_Index], f_Variable, f_Contract);

				if(f_VarIndexInt == nullptr)
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //add debug message var not found
#endif

					return nullptr;
					}
				else
					{
					f_FindIndexInt--;

					if(f_Index >= f_MaxIndex)	//win conditions!
						{
						int f_Ind = ag_any_cast<int>(f_VarIndexInt->m_Var);

#ifdef ECOIN_DEBUG_BREAKS
						if((f_Ind < 0) || (f_Ind >= g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable.size()))
							{
							__debugbreak(); //add debug message array index out of bounds
							}
#endif

						return g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable[f_Ind];
						}
					else
						{
						int f_Ind = ag_any_cast<int>(f_VarIndexInt->m_Var);

#ifdef ECOIN_DEBUG_BREAKS
						if((f_Ind < 0) || (f_Ind >= g_BaseNode->m_Class->m_vec_ClassVar.size()))
							{
							__debugbreak(); //add debug message classvar array index out of bounds
							}
#endif

						g_BaseNode = g_BaseNode->m_Class->m_vec_ClassVar[ag_any_cast<int>(f_VarIndexInt->m_Var)];

						g_vec_BaseNode.push_back(g_BaseNode);

						return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Variable, f_Contract, f_FindIndexInt + 1);
						}

					return f_VarIndexInt;
					}
				}
			else
				{
				__debugbreak(); //no native vector error
				}
			}break;

		case MuNameCall_Type_MemberVar:
			{
#ifdef ECOIN_DEBUG_BREAKS
			if(f_Index == 0)	//1 place classvar
				{
				__debugbreak(); //add debug message membervar not found
				}
#endif
			
			if(f_Index >= f_MaxIndex) //win conditions race winner
				{
				std::shared_ptr<Variable> f_Var = g_BaseNode->m_Class->acFindVar(m_vec_NameCall[f_Index]);

				if(f_Var == nullptr)
					{
					f_Var = ag_Find_Var(m_vec_NameCall[f_Index], f_Variable, f_Contract);

					return f_Var;
					}
				}
			else  //'assume' evector calculate number of indices
				{
				g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

				if(g_BaseNode != nullptr)
					{
					g_vec_BaseNode.push_back(g_BaseNode);

					return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Variable, f_Contract, f_FindIndexInt + 1);
					}

				return nullptr;
				}
			}break;

		case MuNameCall_Type_MemberIndexInt:
			{
			if(f_FindIndexInt == 0)
				{
#ifdef ECOIN_DEBUG_BREAKS
				__debugbreak(); //add debug message integer index var out of position
#endif
				}
			else if(f_FindIndexInt == 1)  //is array index varint check for integer member var
				{
				std::shared_ptr<Variable> f_MemberVarIndexInt = g_BaseNode->m_Class->acFindVar(m_vec_NameCall[f_Index]);

				if(f_MemberVarIndexInt == nullptr)
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //add debug message var not found
#endif

					return nullptr;
					}
				else
					{
					f_FindIndexInt--;

					if(f_Index >= f_MaxIndex) //win conditions!
						{
						return g_vec_BaseNode[g_vec_BaseNode.size() - 1]->m_Class->m_vec_Variable[ag_any_cast<int>(f_MemberVarIndexInt->m_Var)];
						}
					else
						{
						g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

						if(g_BaseNode != nullptr)
							{
							g_vec_BaseNode.push_back(g_BaseNode);

							return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Variable, f_Contract, f_FindIndexInt);
							}
						else
							{
							return nullptr;
							}
						}
					}
				}
#ifdef ECOIN_DEBUG_BREAKS
			else //findindexint runaway vector assignment error
				{
				__debugbreak(); //add debug message no native array
				}
#endif
			}break;

		case MuNameCall_Type_ClassVar:
			{
			if(f_Index == 0)	//1 place classvar
				{
				std::shared_ptr<ClassVar> f_ClassVar = ag_Find_ClassVar(m_vec_NameCall[f_Index], f_Variable->m_lnk_ClassVar, f_Contract);

				if(f_ClassVar == nullptr)
					{
#ifdef ECOIN_DEBUG_BREAKS
					__debugbreak(); //add debug message classvar not found
#endif

					return nullptr;
					}
				else
					{
					g_BaseNode = f_ClassVar;
					}
				}
			
			if(f_Index >= f_MaxIndex) //!!!win conditions!
				{
#ifdef ECOIN_DEBUG_BREAKS
				if(f_FindIndexInt == 1)
					{
					__debugbreak(); //add debuging message currently classvar at var socket syntax error
					}
				else if(f_FindIndexInt > 1)
					{
					__debugbreak(); //add debuging message currently classvar at var socket syntax error
					}
#endif
				}
			else
				{
				if(f_FindIndexInt == 0)
					{
					g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

					if(g_BaseNode != nullptr)
						{
						return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Variable, f_Contract, f_FindIndexInt);
						}
					else
						{
						return nullptr;
						}
					}
				if(f_FindIndexInt == 1)
					{
					g_BaseNode = g_BaseNode->m_Class->acFindClassVar(m_vec_NameCall[f_Index]);

					if(g_BaseNode != nullptr)
						{
						return acCodeCall_Var(f_Index + 1, f_MaxIndex, f_Variable, f_Contract, f_FindIndexInt);
						}
					else
						{
						return nullptr;
						}
					}
#ifdef ECOIN_DEBUG_BREAKS
				else
					{
					__debugbreak(); //add debuging message find index int above 1
					}
#endif
				}
			}break;
		}

	return nullptr;
}

//Contract Function
void CodeLine::ac_Contract_Function(std::shared_ptr<Contract> f_Contract, std::shared_ptr<Function> f_Function)
{
	m_Contract = f_Contract;
	m_Function = f_Function;
}

void CodeLine::ac_Compile_Execute(void)
{
	    //////////////////////
	   //////////////////////
	  // Setup /////////////
	 //
	//
	std::string f_ref_CurrentPath = g_ref_flow_reset + "CodeLine::ac_Compile_Execute";

	uint f_VarSize = m_vec_Code.size();

	  //////////////////
	 // Operator //////
	//
	if(m_CodeLine == MuLine_Assign_Opr)
		{
		if(m_vec_Operator.size() > 0)
			{
			if(f_VarSize == 2)
				{
				uint f_OpSize = m_vec_Operator.size();
				uint f_Count = 0;
				while(f_Count < f_OpSize)
					{
					std::shared_ptr<Operator> f_Operator = m_vec_Operator[f_Count];

					f_Operator->leftHand = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Operator->leftHand, m_Contract);
					f_Operator->rightHand = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Operator->rightHand, m_Contract);

#if 0
					f_Operator->ac_Execute();
#endif

					f_Count++;
					}
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak(); //add debug message variable assignation var count out of range
				}
#endif
			}
#ifdef ECOIN_DEBUG_BREAKS
		else
			{
			__debugbreak();
			} 	 /////////////
#endif		    // Assign ///
		}	   /////////////
	else if(m_CodeLine == MuLine_Assign)
		{
		if(f_VarSize == 2)
			{
			m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
			m_vec_Variable[1] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[1], m_Contract);
			}
		else
			{
			if(f_VarSize == 3)
				{
				m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
				m_vec_Variable[1] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[1], m_Contract);
				m_vec_Variable[2] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[2], m_Contract);
				}
#ifdef ECOIN_DEBUG_BREAKS
			else
				{
				__debugbreak();
				}
#endif
			}
		}
	else if(m_CodeLine == MuLine_Condition_Ajax)
		{
		std::shared_ptr<Condition> f_Condition = m_vec_Code[1]->m_Condition[0];

		f_Condition->leftHand = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Condition->leftHand, m_Contract);
		f_Condition->rightHand = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), f_Condition->rightHand, m_Contract);
		}
	else if(m_CodeLine == MuLine_Init_Var)
		{
		if(f_VarSize == 1)
			{
			m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
			}
		else
			{
			if(f_VarSize == 2)
				{
				m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
				m_vec_Variable[1] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[1], m_Contract);
				}
			else
				{
				if(f_VarSize == 3)
					{
					m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
					m_vec_Variable[1] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[1], m_Contract);
					m_vec_Variable[2] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[2], m_Contract);
					}
#ifdef ECOIN_SECURE
				else
					{
					__debugbreak();
					}
#endif
				}
			}
		}
	else if(m_CodeLine == MuLine_Function)
		{
		if(m_vec_Code[0]->m_Code == MuCode_Function) //non-returning function
			{
			//function code [0] 'Fcn'
			std::shared_ptr<Code> f_ArgCodeFunc = m_vec_Code[0];

			//Specific Case [0] Return
			if(f_ArgCodeFunc->m_VarType == MuVar_ClassVar_Reflect)
				{
#ifdef ECOIN_DEBUG_BREAKS
				if(f_ArgCodeFunc->m_Type[0]->m_MxName.compare("eslbase") != 0)
					{
					__debugbreak(); //add debug msg
					}
				if(f_ArgCodeFunc->m_Number.size() != 3)
					{
					__debugbreak(); //add debug msg7
					}
#endif

				std::string f_InstanceName = f_ArgCodeFunc->m_Type[0]->m_Cvref_Name;

				std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>();

				f_ClassVar->m_MxName = f_InstanceName;

				f_ArgCodeFunc->m_FunctionLink->m_Inst_ClassVar = f_ClassVar;
				}

			//manage variables
			for(int f_XYZ = 0; f_XYZ < m_vec_Variable.size(); f_XYZ++)
				{
				std::shared_ptr<Code> f_ArgCode = f_ArgCodeFunc->m_Number[f_XYZ];

				std::shared_ptr<Variable> f_FlipVar = m_vec_Variable[f_XYZ];

				if(f_ArgCode->m_VarType == MuVar_ClassVar_Reflect)
					{
#ifdef ECOIN_DEBUG_BREAKS
					if(f_ArgCode->m_Type[0]->m_MxName.compare("eslbase") != 0)
						{
						__debugbreak(); //add debug msg
						}

					if(f_ArgCode->m_Number.size() != 3)
						{
						__debugbreak(); //add debug msg
						}
#endif

					std::string f_ClassPath = f_ArgCode->m_Number[0]->m_MxName;

					std::string f_ClassName = f_ArgCode->m_Number[1]->m_MxName;

					int f_InstanceCount = ag_any_cast<int>(f_ArgCode->m_Number[2]->m_MxVar->m_Var);

					ecom_base::base_type f_ecom_base = ag_SharpenBase(f_ClassPath, f_ClassName, f_InstanceCount);

					std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ecom_base, f_ClassPath, f_ClassName);

					f_FlipVar->m_lnk_ClassVar = f_ClassVar;

					f_ClassVar->m_ecom_base = f_ecom_base;
					}
				else if(f_ArgCode->m_VarType == MuVar_ClassVar_Class)
					{
					std::string f_ClassTypeName = f_ArgCode->m_Type[0]->m_MxName;

					std::shared_ptr<Class> f_ClassChoice = nullptr;

					for(int f_Jet = 0; f_Jet < g_Class.size(); f_Jet++)
						{
						std::shared_ptr<Class> f_TestClass = g_Class[f_Jet];

						if(f_TestClass->m_MxName.compare(f_ClassTypeName) == 0)
							{
							f_ClassChoice = f_TestClass;
							}
						}

					if(!f_ClassChoice)
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak(); //add debuging message variable assignation result hand class not found
#endif						   //class not found // add debug message
						}
					else
						{
						std::string f_ClassVarName = f_ArgCode->m_Name[0]->m_MxName;

						std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ClassChoice);

						f_ClassVar->m_MxName = f_ClassVarName;

						f_ClassVar->acCall_Constructor();

						f_FlipVar->m_lnk_ClassVar = f_ClassVar;
						}
					}
				else
					{
					m_vec_Variable[f_XYZ] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[f_XYZ], m_Contract);

#ifdef ECOIN_DEBUG_BREAKS
					if(m_vec_Variable[f_XYZ] == nullptr)
						{
						__debugbreak(); //add debuging message variable assignation result hand variable not found
						}
#endif
					}
				}
			}
		else if(m_vec_Code[1]->m_Code == MuCode_Function) //returning function compile execute
			{
			//manage variables for function code [1] 'Fcn'
			for(int f_XYZ = 0; f_XYZ < m_vec_Variable.size(); f_XYZ++)
				{
				int f_Index = 0;

				std::shared_ptr<Code> f_ArgCode = nullptr;

				if(f_XYZ == 0)
					{
					f_Index = 0;

					f_ArgCode = m_vec_Code[0]->m_Type[0];
					}
				else
					{
					f_Index = f_XYZ + 1;

					f_ArgCode = m_vec_Code[1]->m_Number[f_XYZ - 1]->m_Type[0];
					}

				std::shared_ptr<Variable> f_FlipVar = m_vec_Variable[f_XYZ];

				if(f_ArgCode->m_VarType == MuVar_ClassVar_Reflect)
					{
#ifdef ECOIN_DEBUG_BREAKS
					if(f_ArgCode->m_Type[0]->m_MxName.compare("eslbase") != 0)
						{
						__debugbreak(); //add debug msg
						}
					if(f_ArgCode->m_Number.size() != 3)
						{
						__debugbreak(); //add debug msg
						}
#endif

					std::string f_ClassPath = f_ArgCode->m_Number[0]->m_MxName;

					std::string f_ClassName = f_ArgCode->m_Number[1]->m_MxName;

					int f_InstanceCount = ag_any_cast<int>(f_ArgCode->m_Number[2]->m_MxVar->m_Var);

					ecom_base::base_type f_ecom_base = ag_SharpenBase(f_ClassPath, f_ClassName, f_InstanceCount);

					std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ecom_base, f_ClassPath, f_ClassName);

					f_FlipVar->m_lnk_ClassVar = f_ClassVar;

					f_ClassVar->m_ecom_base = f_ecom_base;
					}
				else if(f_ArgCode->m_VarType == MuVar_ClassVar_Class)
					{
					std::string f_ClassTypeName = f_ArgCode->m_Type[0]->m_MxName;

					std::shared_ptr<Class> f_ClassChoice = nullptr;

					for(int f_Jet = 0; f_Jet < g_Class.size(); f_Jet++)
						{
						std::shared_ptr<Class> f_TestClass = g_Class[f_Jet];

						if(f_TestClass->m_MxName.compare(f_ClassTypeName) == 0)
							{
							f_ClassChoice = f_TestClass;
							}
						}

					if(!f_ClassChoice)
						{
#ifdef ECOIN_DEBUG_BREAKS
						__debugbreak(); //add debuging message variable assignation result hand class not found
#endif									//class not found // add debug message
						}
					else
						{
						std::string f_ClassVarName = f_ArgCode->m_Name[0]->m_MxName;

						std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ClassChoice);

						f_ClassVar->m_MxName = f_ClassVarName;

						f_ClassVar->acCall_Constructor();

						f_FlipVar->m_lnk_ClassVar = f_ClassVar;
						}
					}
				else
					{
					m_vec_Variable[f_XYZ] = m_vec_Code[0]->acCodeCall_Var(f_XYZ, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[f_XYZ], m_Contract);

#ifdef ECOIN_SECURE
					if(m_vec_Variable[f_XYZ] == nullptr)
						{
						__debugbreak(); //add debuging message variable assignation result hand variable not found
						}
#endif
					}
				}
			}
#ifdef ECOIN_SECURE
		else
			{
			__debugbreak();
			}
#endif
		}
	else if(m_CodeLine == MuLine_Return)
		{
		m_vec_Variable[0] = m_vec_Code[0]->acCodeCall_Var(0, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[0], m_Contract);
		}
	else if(m_CodeLine == MuLine_For_Loop)
		{
		for(int f_Jet = 0; f_Jet < m_vec_Variable.size(); f_Jet++)
			{
			m_vec_Variable[f_Jet] = m_vec_Code[0]->acCodeCall_Var(f_Jet, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[f_Jet], m_Contract);
			}
		}
	else if(m_CodeLine == MuLine_Init_ClassVar)
		{
		std::shared_ptr<Code> f_CodeZero = m_vec_Code[0];

		if(f_CodeZero->m_VarType == MuVar_ClassVar_Class || f_CodeZero->m_VarType == MuVar_ClassVar_Reflect)
			{
			std::string f_VarName = f_CodeZero->m_MxName;

			std::shared_ptr<Variable> f_FlipVar = m_vec_Variable[0];

			std::shared_ptr<Class> f_ClassChoice = nullptr;

			if(f_CodeZero->m_VarType == MuVar_ClassVar_Reflect)
				{
#ifdef ECOIN_DEBUG_BREAKS
				if(f_CodeZero->m_Type[0]->m_MxName.compare("eslbase") != 0)
					{
					__debugbreak(); //add debug msg
					}
				if(f_CodeZero->m_Number.size() != 3)
					{
					__debugbreak(); //add debug msg
					}
#endif

				std::string f_ClassPath = f_CodeZero->m_Number[0]->m_MxName;

				std::string f_ClassName = f_CodeZero->m_Number[1]->m_MxName;

				int f_InstanceCount = ag_any_cast<int>(f_CodeZero->m_Number[2]->m_MxVar->m_Var);

				ecom_base::base_type f_ecom_base = ag_SharpenBase(f_ClassPath, f_ClassName, f_InstanceCount);

				std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ecom_base, f_ClassPath, f_ClassName);

				f_FlipVar->m_lnk_ClassVar = f_ClassVar;

				f_ClassVar->m_ecom_base = f_ecom_base;
				}
			else
				{
				for(int f_Jet = 0; f_Jet < g_Class.size(); f_Jet++)
					{
					std::shared_ptr<Class> f_TestClass = g_Class[f_Jet];

					if(f_TestClass->m_MxName.compare(m_vec_Code[0]->m_MxName) == 0)
						{
						f_ClassChoice = f_TestClass;
						}
					}

				//manage variables
				for(int f_XYZ = 0; f_XYZ < m_vec_Variable.size(); f_XYZ++)
					{
					m_vec_Variable[f_XYZ] = m_vec_Code[0]->acCodeCall_Var(f_XYZ, m_vec_Code[0]->m_vec_NameCall.size(), m_vec_Variable[f_XYZ], m_Contract);

#ifdef ECOIN_SECURE
					if(m_vec_Variable[f_XYZ] == nullptr)
						{
						__debugbreak(); //add debuging message variable assignation left hand variable not found
						}
#endif
					}

				std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ClassChoice);

				f_ClassVar->acCall_Constructor();

				f_FlipVar->m_lnk_ClassVar = f_ClassVar;
				}
			}
		}

#if 0
	else if(f_CodeZero->m_VarType == MuVar_ClassVar_Typename)
		{
		std::string f_VarName = f_CodeZero->m_MxName;

		std::shared_ptr<Variable> f_FlipVar = std::make_shared<Variable>(f_VarName, MuCode_Var);

		std::shared_ptr<Class> f_ClassChoice = nullptr;

		for(int f_Jet = 0; f_Jet < g_Class.size(); f_Jet++)
			{
			std::shared_ptr<Class> f_TestClass = g_Class[f_Jet];

#pragma message("Warning add debugability messages according to m_Type = result")

			if(f_TestClass->m_MxName.compare(m_vec_Code[0]->m_MxName) == 0)
				{
				f_ClassChoice = f_TestClass;
				}
			}

		if(!f_ClassChoice)
			{
#ifdef ECOIN_SECURE
			__debugbreak(); //add debuging message variable assignation result hand class not found
#endif				  //class not found // add debug message
			}
		else
			{
			//manage variables
			for(int f_XYZ = 0; f_XYZ < m_vec_Variable.size(); f_XYZ++)
				{
				m_vec_Variable[f_XYZ] = m_vec_Code[f_XYZ + 1]->acCodeCall_Var(0, m_vec_Code[f_XYZ + 1]->m_vec_NameCall.size(), m_Function);

				if(m_vec_Variable[f_XYZ] == nullptr)
					{
#ifdef ECOIN_SECURE
					__debugbreak(); //add debuging message variable assignation left hand variable not found
#endif
					}
				}

			std::shared_ptr<ClassVar> f_ClassVar = std::make_shared<ClassVar>(f_ClassChoice);

			f_ClassVar->acCall_Constructor();

			f_FlipVar->m_lnk_ClassVar = f_ClassVar;

			m_vec_Variable.push_back(f_FlipVar);
			}
		}
#endif
}

void CodeLine::ac_Execute(void)
{
	    //////////////////////
	   //////////////////////
	  // Execute
	 //
	//
	uint f_VarSize = m_vec_Code.size();

	  //////////////////
	 // Operator
	//
	if(m_CodeLine == MuLine_Assign_Opr)
		{
		m_vec_Operator[0]->ac_Execute();
		}      //// Assign ////
	else if(m_CodeLine == MuLine_Assign)
		{
		if(f_VarSize == 2)
			{
			m_vec_Variable[0]->CloneVar(m_vec_Variable[1]);
			}
		else
			{
			if(f_VarSize == 3)
				{
				m_vec_Variable[0]->CloneVar(m_vec_Variable[1]);
				m_vec_Variable[1]->CloneVar(m_vec_Variable[2]);
				}
			}
		}
	else if(m_CodeLine == MuLine_Condition_Ajax)
		{
		m_vec_Code[1]->m_Condition[0]->ac_Execute();
		}
	else if(m_CodeLine == MuLine_Init_Var)
		{
		if(f_VarSize == 2)
			{
			m_vec_Variable[0]->CloneVar(m_vec_Variable[1]);
			}
		else
			{
			m_vec_Variable[0]->CloneVar(m_vec_Variable[1]);
			m_vec_Variable[1]->CloneVar(m_vec_Variable[2]);
			}
		}
	else if(m_CodeLine == MuLine_Function)
		{
		if(m_vec_Code[0]->m_Code == MuCode_Function) // non returning
			{
			std::shared_ptr<Code> f_FuncCode = m_vec_Code[0];

			if((f_FuncCode->m_Type[0]->m_VarType > MuFunc_Custom) && (f_FuncCode->m_Type[0]->m_VarType < MuFunc::MuFunc_MAX_)) //mostly math functions
				{
				std::shared_ptr<Function> f_FunctionB = f_FuncCode->m_FunctionLink;

				if(m_vec_Variable.size() == 1)
					{
					f_FunctionB->acExecute(m_vec_Variable[0]);
					}
				else if(m_vec_Variable.size() == 3)
					{
					f_FunctionB->acExecute(m_vec_Variable[0], m_vec_Variable[1]);
					}
				}
			else if(f_FuncCode->m_Type[0]->m_VarType == MuFunc_Custom)
				{
				std::shared_ptr<Function> f_FunctionB = f_FuncCode->m_FunctionLink;

				f_FunctionB->acExecute();
				}
			else if(f_FuncCode->m_Type[0]->m_VarType == MuFunc_Reflection)
				{
				std::shared_ptr<Function> f_Func = f_FuncCode->m_FunctionLink;

				f_Func->m_Inst_ClassVar->m_ecom_base->ac_Attach_Void(f_Func->m_MxName, (std::shared_ptr<CodeLine>)this);
				}
			}
		else if(m_vec_Code[1]->m_Code == MuCode_Function) // returning variable
			{
			std::shared_ptr<Code> f_FuncCode = m_vec_Code[1];

			if((f_FuncCode->m_Type[0]->m_VarType > MuFunc_Custom) && (f_FuncCode->m_Type[0]->m_VarType < MuFunc::MuFunc_MAX_)) //mostly math functions
				{
				std::shared_ptr<Function> f_FunctionB = f_FuncCode->m_FunctionLink;

				if(m_vec_Variable.size() == 2)
					{
					m_vec_Variable[0]->CloneVar(f_FunctionB->acExecute(m_vec_Variable[1]));
					}
				else if(m_vec_Variable.size() == 3)
					{
					m_vec_Variable[0]->CloneVar(f_FunctionB->acExecute(m_vec_Variable[0], m_vec_Variable[1]));
					}
				}
			else if(f_FuncCode->m_Type[0]->m_VarType == MuFunc_Custom)
				{
				std::shared_ptr<Function> f_FunctionB = f_FuncCode->m_FunctionLink;

				m_vec_Variable[0]->CloneVar(f_FunctionB->acExecute());
				}
			else if(f_FuncCode->m_Type[0]->m_VarType == MuFunc_Reflection)
				{
				std::shared_ptr<Code> f_CodeZero = m_vec_Code[0];

				if(f_CodeZero->m_Code == MuCode_ClassVar)
					{
					if(f_CodeZero->m_VarType == MuVar_ClassVar_Reflect)	//classvar from reflection
						{
						std::shared_ptr<Variable> f_flip_Var_asClassVar = m_vec_Variable[0];

						std::shared_ptr<Function> f_FunctionRCV = m_vec_Code[1]->m_FunctionLink;

						f_flip_Var_asClassVar->m_lnk_ClassVar->m_ecom_base = f_FunctionRCV->m_Inst_ClassVar->m_ecom_base->ac_Attach_Base(f_FunctionRCV->m_MxName, (std::shared_ptr<CodeLine>)this);
						}
					else if(f_CodeZero->m_VarType == MuVar_ClassVar_Class)	//classvar from loaded dependencies
						{
						std::shared_ptr<Variable> f_flip_Var_asClassVar = m_vec_Variable[0];

						std::shared_ptr<Function> f_FunctionRCV = m_vec_Code[1]->m_FunctionLink;

						f_flip_Var_asClassVar = f_FunctionRCV->acExecute(); //imp** returns classvar as link pointer inside variable container
						}
					}
				else if(f_CodeZero->m_Code == MuCode_Var)
					{
					std::shared_ptr<Variable> f_flip_Var_asClassVar = m_vec_Variable[0];

					std::shared_ptr<Function> f_FunctionVar = m_vec_Code[1]->m_FunctionLink;

					f_flip_Var_asClassVar->CloneVar(f_FunctionVar->m_Inst_ClassVar->m_ecom_base->ac_Attach_Var(f_FunctionVar->m_MxName, (std::shared_ptr<CodeLine>)this));
					}
				}
			}
		}
	else if(m_CodeLine == MuLine_Return)
		{
#ifdef ECOIN_SECURE
		if(m_vec_Variable.size() != 1)
			{
			__debugbreak();
			}
#endif
		}
	else if(m_CodeLine == MuLine_For_Loop)
		{
		int f_ParamCount = m_vec_Code[0]->m_Number.size();

		if(f_ParamCount == 1)
			{
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[0];

			int f_Count = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_Count = ag_any_cast<int>(f_VarCount->m_Var);
				}
#ifdef ECOIN_SECURE
			else
				{
				__debugbreak();
				}

			if(f_Count < 0)
				{
				__debugbreak();
				}
#endif

			std::shared_ptr<Function> f_FunctionB = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = 0; f_XY < f_Count; f_XY++)
				{
				f_FunctionB->acExecute();
				}
			}
		else if(f_ParamCount == 2)
			{
			std::shared_ptr<Variable> f_VarCountVar = m_vec_Variable[0];
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[1];

			int f_StartCount = ag_any_cast<int>(f_VarCountVar->m_Var);
			int f_Count = 0;

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_Count = ag_any_cast<int>(f_VarCount->m_Var);
				}
#ifdef ECOIN_SECURE
			else
				{
				__debugbreak(); //add debug message
				}
#endif

#ifdef ECOIN_SECURE
			if(f_Count < 0)
				{
				__debugbreak(); //add debug message
				}
#endif

			std::shared_ptr<Function> f_FunctionB = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = 0; f_XY < f_Count; f_XY++)
				{
				f_VarCountVar->set_Value(f_XY);

				f_FunctionB->acExecute();
				}
			}
		else if(f_ParamCount == 3)
			{
			std::shared_ptr<Variable> f_VarStart = m_vec_Variable[0];
			std::shared_ptr<Variable> f_VarCount = m_vec_Variable[1];
			std::shared_ptr<Variable> f_VarMax = m_vec_Variable[2];

			int f_StartCount = ag_any_cast<int>(f_VarStart->m_Var);
			int f_Count = 0;

			if(f_VarStart->m_Var.type() == typeid(int))
				{
				f_StartCount = ag_any_cast<int>(f_VarStart->m_Var);
				}
#ifdef ECOIN_SECURE
			else
				{
				__debugbreak(); //add debug message
				}
#endif

#ifdef ECOIN_SECURE
			if(f_VarCount < 0)
				{
				__debugbreak(); //add debug message
				}
#endif

			if(f_VarCount->m_Var.type() == typeid(int))
				{
				f_Count = ag_any_cast<int>(f_VarCount->m_Var);
				}
#ifdef ECOIN_SECURE
			else
				{
				__debugbreak(); //add debug message
				}
#endif

#ifdef ECOIN_SECURE
			if(f_Count < 0)
				{
				__debugbreak(); //add debug message
				}
#endif

			int f_CountMax = 0;

			if(f_VarMax->m_Var.type() == typeid(int))
				{
				f_CountMax = ag_any_cast<int>(f_VarMax->m_Var);
				}
#ifdef ECOIN_SECURE
			else
				{
				__debugbreak(); //add debug message
				}
#endif

#ifdef ECOIN_SECURE
			if(f_CountMax < 0)
				{
				__debugbreak(); //add debug message
				}
#endif

			std::shared_ptr<Function> f_FunctionB = g_Function[m_vec_Code[0]->m_ContractID];

			for(int f_XY = f_StartCount; f_XY < f_Count; f_XY += f_CountMax)
				{
				f_VarStart->set_Value(f_XY);

				f_FunctionB->acExecute();
				}
			}
#ifdef ECOIN_SECURE
		else
			{
			__debugbreak();
			}
#endif
		}
	else if(m_CodeLine == MuLine_Init_ClassVar)
		{
		if(m_vec_Code[0]->m_VarType == MuVar_ClassVar_Reflect)	//classvar from reflection
			{
			std::shared_ptr<Variable> f_flip_Var_asClassVar = m_vec_Variable[0];

			//clone up
			std::shared_ptr<Variable> f_NewFlipVar = std::make_shared<Variable>(*f_flip_Var_asClassVar);
			std::shared_ptr<ClassVar> f_NewClassVar = std::make_shared<ClassVar>(*f_flip_Var_asClassVar->m_lnk_ClassVar);

			f_NewFlipVar->m_lnk_ClassVar = f_NewClassVar;

			ag_New_Var(f_NewFlipVar, m_Contract);
			ag_New_ClassVar(f_NewFlipVar->m_lnk_ClassVar, m_Contract);
			}
		else if(m_vec_Code[0]->m_VarType == MuVar_ClassVar_Class)	//classvar from loaded dependencies
			{
			std::shared_ptr<Variable> f_flip_Var_asClassVar = m_vec_Variable[0];

			//clone up
			std::shared_ptr<Variable> f_NewFlipVar = std::make_shared<Variable>(*f_flip_Var_asClassVar);
			std::shared_ptr<ClassVar> f_NewClassVar = std::make_shared<ClassVar>(*f_flip_Var_asClassVar->m_lnk_ClassVar);

			f_NewFlipVar->m_lnk_ClassVar = f_NewClassVar;

			//constructor required
			f_NewClassVar->acCall_Constructor();

			ag_New_Var(f_NewFlipVar, m_Contract);
			ag_New_ClassVar(f_NewFlipVar->m_lnk_ClassVar, m_Contract);
			}
		}
}

};