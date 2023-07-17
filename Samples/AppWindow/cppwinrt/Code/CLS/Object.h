/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef CODE_H
#define CODE_H

#include <vector>
#include <math.h>

#include "../Musion/MuType.h"
#include "../Musion/Variable.h"

namespace ecoin
{
#if 0
	enum MuCode
	{
		MuCode_Var,
		MuCode_System,
		MuCode_Constant,
		MuCode_Operator,
		MuCode_Function,
		MuCode_Parameter,
		MuCode_Override
	};
#endif

#if 0
	class Code : public MuType
	{
	public:
		Code() : MuType(MuTYPE_Code) {};
		Code(std::shared_ptr<Code> f_Code) : MuType(MuTYPE_Code)
			{
			*this = f_Code;
			};
		Code(std::string f_Line, uint f_CHK, uint f_Index, uint f_CodeType = MuCode_Var, uint f_VarType = MuVar_Full);

		uint acName_MAX(void);
		uint acNumber_MAX(void);
		uint acType_MAX(void);
		uint acName_END(void);
		uint acNumber_END(void);
		uint acType_END(void);
		uint acDecide_MAX(void);
		uint acDecide_END(void);

		uint m_Code;
		uint m_END;
		uint m_Chk;

		int m_VarType;

		std::string m_MxName;
		Variable *m_MxVar;

		uint m_Index;

		char m_Code_DigitA;
		char m_Code_DigitB;
		char m_Code_DigitC;

		std::vector<std::shared_ptr<Code>> m_Name;
		std::vector<std::shared_ptr<Code>> m_Number;
		std::vector<std::shared_ptr<Code>> m_Type;
		std::vector<std::shared_ptr<Code>> m_Param;
	};
#endif

};

#endif