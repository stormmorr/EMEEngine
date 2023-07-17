/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef OPERATOR_H
#define OPERATOR_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Variable.h"

namespace ecoin
{
	enum MuOperatorType
	{
		MuOpr_Plus,
		MuOpr_Minus,
		MuOpr_Multiply,
		MuOpr_Divide,
		MuOpr_Bitleft,
		MuOpr_Bitright,
		MuOpr_Modulus,
		MuOpr_Copy,
		MuOpr_Equals,
		MuOpr_Random,
		MuOpr_Total
	};

	class Operator : public MuType
	{
	public:
		Operator() { };
		Operator(std::string f_Stg);

		~Operator() { };

		void ac_Execute(void);

		std::shared_ptr<Variable> leftHand;
		std::shared_ptr<Variable> rightHand;

		uint m_Operator;

		std::string m_MxName;
	};

	extern uint agFind_OprType(std::string f_String);

};

#endif
