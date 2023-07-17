/*

Variable - osirem.com
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

	Condition::Condition(std::string f_Stg) : m_MxName(f_Stg), MuType(MuTYPE_Condition)
		{
		acClear();
		}

	void Condition::acClear(void)
		{
		m_Success_Contract_FunctionID = -1;
		m_Failure_Contract_FunctionID = -1;
		}

	uint agFind_ConType(std::string f_String)
		{
		if((f_String.compare("==") == 0) ||
			(f_String.compare("eqs") == 0) ||
			(f_String.compare("equal") == 0))
			{
			return MuCon_Equal;
			}
		else if((f_String.compare("!=") == 0) ||
				 (f_String.compare("neq") == 0) ||
				 (f_String.compare("notequal") == 0))
			{
			return MuCon_NotEqual;
			}
		else if((f_String.compare("<<") == 0) ||
				 (f_String.compare("sml") == 0) ||
				 (f_String.compare("small") == 0) ||
				 (f_String.compare("SML") == 0) || 
				 (f_String.compare("Small") == 0))
			{
			return MuCon_SmallThan;
			}
		else if((f_String.compare(">>") == 0) ||
				 (f_String.compare("gtr") == 0) ||
				 (f_String.compare("greater") == 0) ||
				 (f_String.compare("GTR") == 0) ||
			 	 (f_String.compare("Greater") == 0))
			{
			return MuCon_GreatThan;
			}
		else if((f_String.compare("<=") == 0) ||
				 (f_String.compare("ste") == 0) ||
				 (f_String.compare("smallequal") == 0) ||
				 (f_String.compare("STE") == 0))
			{
			return MuCon_SmallThanorEqual;
			}
		else if((f_String.compare(">=") == 0) ||
				 (f_String.compare("gte") == 0) ||
				 (f_String.compare("greatequal") == 0) ||
				 (f_String.compare("GTE") == 0))
			{
			return MuCon_GreatThanorEqual;
			}

		return 0;
		}

	void Condition::ac_Execute(void)
		{
		switch(m_Condition)
			{
			case MuCon_Equal:
				{
				if(m_VarType == MuVar_Float)
					{
					if(leftHand == rightHand)
						{
						if(m_Success_Contract_FunctionID != -1)
							{
							g_Function[m_Success_Contract_FunctionID]->acExecute();
							}
						}
					else
						{
						if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
							{
							g_Function[m_Failure_Contract_FunctionID]->acExecute();
							}
						}
					}
				}break;

			case MuCon_NotEqual:
				{
				switch(m_VarType)
					{
					case MuVar_Float:
						{
						if(leftHand != rightHand)
							{
							if((m_Success_Contract_FunctionID > -1) && (m_Success_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Success_Contract_FunctionID]->acExecute();
								}
							}
						else
							{
							if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Failure_Contract_FunctionID]->acExecute();
								}
							}
						}break;
					}
				}break;

			case MuCon_SmallThan:
				{
				switch(m_VarType)
					{
					case MuVar_Float:
						{
						if(leftHand < rightHand)
							{
							if((m_Success_Contract_FunctionID > -1) && (m_Success_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Success_Contract_FunctionID]->acExecute();
								}
							}
						else
							{
							if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Failure_Contract_FunctionID]->acExecute();
								}
							}
						}break;
					}
				}break;

			case MuCon_GreatThan:
				{
				switch(m_VarType)
					{
					case MuVar_Float:
						{
						if(leftHand > rightHand)
							{
							if((m_Success_Contract_FunctionID > -1) && (m_Success_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Success_Contract_FunctionID]->acExecute();
								}
							}
						else
							{
							if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Failure_Contract_FunctionID]->acExecute();
								}
							}
						}break;
					}
				}break;

			case MuCon_SmallThanorEqual:
				{
				switch(m_VarType)
					{
					case MuVar_Float:
						{
						if(leftHand <= rightHand)
							{
							if((m_Success_Contract_FunctionID > -1) && (m_Success_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Success_Contract_FunctionID]->acExecute();
								}
							}
						else
							{
							if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Failure_Contract_FunctionID]->acExecute();
								}
							}
						}break;
					}
				}break;

			case MuCon_GreatThanorEqual:
				{
				switch(m_VarType)
					{
					case MuVar_Float:
						{
						if(leftHand >= rightHand)
							{
							if((m_Success_Contract_FunctionID > -1) && (m_Success_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Success_Contract_FunctionID]->acExecute();
								}
							}
						else
							{
							if((m_Failure_Contract_FunctionID >= 0) && (m_Failure_Contract_FunctionID < g_Function.size()))
								{
								g_Function[m_Failure_Contract_FunctionID]->acExecute();
								}
							}
						}break;
					}
				}break;
			}
		}

};