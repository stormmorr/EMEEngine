/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Variable.h"
#include "Code.h"
#include "CodeLine.h"

using namespace ecoin;

namespace ecoin
{

	Operator::Operator(std::string f_Stg) : m_MxName(f_Stg), MuType(MuTYPE_Operator)
		{
		//...
		}

	uint agFind_OprType(std::string f_String)
		{
		if (f_String.compare("plus") == 0 ||
			f_String.compare("Plus") == 0 ||
			f_String.compare("=+") == 0)
			{
			return MuOpr_Plus;
			}
		else if (f_String.compare("minus") == 0 ||
				 f_String.compare("Minus") == 0 ||
				 f_String.compare("=-") == 0)
			{
			return MuOpr_Minus;
			}
		else if (f_String.compare("mul") == 0 ||
				 f_String.compare("mult") == 0 ||
				 f_String.compare("multiply") == 0 ||
				 f_String.compare("Mul") == 0 ||
				 f_String.compare("MUL") == 0 ||
				 f_String.compare("Mull") == 0 ||
				 f_String.compare("MULL") == 0 ||
				 f_String.compare("Mult") == 0 ||
				 f_String.compare("Multiply") == 0 ||
				 f_String.compare("=*") == 0 ||
				 f_String.compare("**") == 0 ||
				 f_String.compare("Mul**") == 0)
			{
			return MuOpr_Multiply;
			}
		else if (f_String.compare("div") == 0 ||
				 f_String.compare("divide") == 0 ||
				 f_String.compare("Div") == 0 ||
				 f_String.compare("Divide") == 0 ||
				 f_String.compare("DIV") == 0 ||
				 f_String.compare("=/") == 0)
			{
			return MuOpr_Divide;
			}
		else if (f_String.compare("bitleft") == 0 ||
				 f_String.compare("bitl") == 0 ||
				 f_String.compare("bit") == 0 ||
				 f_String.compare("<<") == 0)
			{
			return MuOpr_Bitleft;
			}
		else if (f_String.compare("bitright") == 0 ||
				 f_String.compare("bitr") == 0 ||
				 f_String.compare(">>") == 0)
			{
			return MuOpr_Bitright;
			}
		else if (f_String.compare("mod") == 0 ||
				 f_String.compare("MOD") == 0 ||
				 f_String.compare("Mod") == 0 ||
				 f_String.compare("modulus") == 0 || 
				 f_String.compare("Modulus") == 0 ||
				 f_String.compare("=%") == 0)
			{
			return MuOpr_Modulus;
			}
		else if (f_String.compare("**") == 0 ||
				 f_String.compare("Copy") == 0 ||
				 f_String.compare("copy") == 0)
			{
			return MuOpr_Copy;
			}
		else if (f_String.compare("rand") == 0 ||
				 f_String.compare("random") == 0 ||
				 f_String.compare("Rand") == 0 ||
				 f_String.compare("Random") == 0)
			{
			return MuOpr_Random;
			}
		else
			{
			return MuOpr_Equals;
			}

		return 0;
		}

	void Operator::ac_Execute(void)
		{
		switch(m_Operator)
			{
			case MuOpr_Plus:
				{
				leftHand = leftHand + rightHand;
				}break;
			case MuOpr_Minus:
				{
				leftHand = leftHand - rightHand;
				}break;
			case MuOpr_Multiply:
				{
				leftHand = leftHand * rightHand;
				}break;
			case MuOpr_Divide:
				{
				leftHand = leftHand / rightHand;
				}break;
			case MuOpr_Bitleft:
				{
				leftHand = leftHand << rightHand;
				}break;
			case MuOpr_Bitright:
				{
				leftHand = leftHand >> rightHand;
				}break;
			case MuOpr_Modulus:
				{
				leftHand = leftHand % rightHand;
				}break;
			case MuOpr_Copy:
				{
				leftHand = rightHand;
				}break;
			case MuOpr_Equals:
				{
				leftHand = leftHand->CloneVar(rightHand);
				}break;
			case MuOpr_Random:
				{
				*(leftHand) = Cube::random();
				}break;
			}
		}

};