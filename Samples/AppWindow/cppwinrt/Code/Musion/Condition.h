/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CONDITION_H
#define CONDITION_H

#include <vector>
#include <math.h>

#include "MuType.h"
#include "Variable.h"

namespace ecoin
{
	enum MuConditionType
	{
		MuCon_Equal,
		MuCon_NotEqual,
		MuCon_SmallThan,
		MuCon_GreatThan,
		MuCon_SmallThanorEqual,
		MuCon_GreatThanorEqual,
		MuCon_Total
	};

	class Condition : public MuType
	{
	public:
		Condition() { acClear(); };
		Condition(std::string f_Stg);
		~Condition() { acClear(); };

		void acClear(void);

		void ac_Execute(void);

		std::shared_ptr<Variable> leftHand;
		std::shared_ptr<Variable> rightHand;

		uint m_Condition;

		int m_VarType;

		uint m_Success_Contract_FunctionID;
		uint m_Failure_Contract_FunctionID;

		std::string m_MxName;
	};

	extern uint agFind_ConType(std::string f_String);

};

#endif
