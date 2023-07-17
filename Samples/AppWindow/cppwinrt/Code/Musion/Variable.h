/*

Variable - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <math.h>

#include "MuType.h"

#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

#include <boost/any.hpp>

namespace ecoin
{
	    ///////////////////////////
	   // ecoin::Variable
	  // MainLine Base Super Types
	 //..VarType
	enum VarType
		{
		ECN_VAR_FLOAT,
		ECN_VAR_INT,
		ECN_VAR_STRING,
		ECN_VAR_UINT,
		ECN_VAR_CHAR,
		ECN_VAR_UCHAR,
		ECN_VAR_DOUBLE,
		ECN_VAR_BOOL
		};

	//Possible Contention Precision
	enum Variable_Precision
		{
		MuVar_Float,
		MuVar_Int,
		MuVar_String,
		MuVar_UInt,
		MuVar_Char,
		MuVar_UChar,
		MuVar_Double,
		MuVar_Bool,
		MuVar_Float2,
		MuVar_Float3,
		MuVar_Float4,
		MuVar_Int2,
		MuVar_Int3,
		MuVar_Int4,
		MuVar_Float_Reflect,
		MuVar_Int_Reflect,
		MuVar_String_Reflect,
		MuVar_UInt_Reflect,
		MuVar_Char_Reflect,
		MuVar_UChar_Reflect,
		MuVar_Double_Reflect,
		MuVar_Bool_Reflect,
		MuVar_ClassVar_Class, //transient type
		MuVar_ClassVar_Typename,
		MuVar_ClassVar_Typename_Reflect,
		MuVar_ClassVar_Reflect, //transient type
		MuVar_Custom,
		MuVar_Full,
		MuVar_Total
		};

	enum Variable_Action
		{
		MuAct_Start,
		MuAct_Random,
		MuAct_RandInt,
		MuAct_Reset,
		MuAct_Inc,
		MuAct_Dec,
		MuAct_Double,
        MuAct_Finish,
		MuAct_Total
		};

	//Central MuType Elevated
	enum MuCode
		{
		MuCode_Var,
		MuCode_ClassVar,
		MuCode_System,
		MuCode_Constant,
		MuCode_Operator,
		MuCode_Condition,
		MuCode_For_Loop,
		MuCode_Function,
		MuCode_FunctionStart,
		MuCode_Parameter,
		MuCode_ClassStart,
		MuCode_Return,
		MuCode_Template,
		MuCode_Total,
		MuCode_Override
		};

#ifndef ECN_DEFAULT_INTEGER
#define ECN_VAR_DEFAULT (int)VarType::ECN_VAR_FLOAT
#define ECN_VAR_DEFAULT_PRECISION (int)Variable_Precision::MuVar_Float
typedef float ECN_default_type;
#else
#define ECN_VAR_DEFAULT (int)VarType::ECN_VAR_INT
#define ECN_VAR_DEFAULT_PRECISION (int)Variable_Precision::MuVar_Int
typedef int ECN_default_type;
#endif

    typedef struct
        {
        float m_X;
        float m_Y;
        float m_Z;
        } float3;

    typedef struct
        {
        float m_X;
        float m_Y;
        float m_Z;
        float m_W;
        } float4;

	class Class;
	class ClassVar;

	class Variable : public MuType
		{
		public:
            Variable();

			//Active Constructors
			Variable(uint f_PrecType);
			Variable(std::string f_Stg, uint f_CodeType);
            Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType);
			Variable(std::string f_Stg, uint f_CodeType, uint f_PrecType, uint f_Variable);
			Variable(std::string f_Stg, uint f_CodeType, boost::any f_a);

            ~Variable();

            void acClear(void)
                {
                m_Action = MuAct_Start;
                m_MxName.clear();
				m_lnk_Class = nullptr;
				m_lnk_ClassVar = nullptr;
                }

			//Get Value
            boost::any get_Value(void);

			//Set Value
			void set_Value(boost::any f_Value);

			//Copy Function
            std::shared_ptr<Variable> CloneVar(std::shared_ptr<Variable> v1);

			//Variable_Precision
			uint m_PrecType;

			//CodeType
			uint m_CodeType;

			//VarType
			uint m_Variable;

			boost::any m_Var;

			std::shared_ptr<Class> m_lnk_Class;
			std::shared_ptr<ClassVar> m_lnk_ClassVar;

			std::string m_MxName;
            std::vector<std::string> m_vec_NameCall;

			unsigned char m_Action;
			bool m_RefVar; //is Reference Pointer?
		};

	extern bool ag_Value_Check(std::string f_Input);

	extern bool ag_CVar_Check(std::string f_Input);

	extern int agFind_Precision(std::string f_String);

	extern int agFind_VarType_from_Precision(int f_CurrentSpec);

	extern std::shared_ptr<Variable> av_Identity(uint f_PrecType);

	extern std::shared_ptr<ecom_base> ag_SharpenBase(std::string f_ClassPath, std::string f_ClassName, int f_instanceCount);

	extern std::shared_ptr<Variable> ag_ReturnAnyVar(std::string f_StringName, int f_PrecType, std::string f_MainClassStringPath, std::string f_MainClassStringType, std::string f_MemberVarStringName, int f_instanceCount);

    std::shared_ptr<Variable> operator+ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator- (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator* (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator/ (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator<< (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator>> (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    std::shared_ptr<Variable> operator% (const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator==(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
    bool operator!=(const std::shared_ptr<Variable>& v1, const std::shared_ptr<Variable>& v2);
};


#endif