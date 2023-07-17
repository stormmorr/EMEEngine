/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef QAMTRIGGER_H
#define QAMTRIGGER_H

#include <vector>
#include <math.h>

#include "qamType.h"
#include "qamVariable.h"

namespace ecoin
{

	class Condition_Element
	{
	public:
		Condition_Element() { acClear(); };
		~Condition_Element() { acClear(); }

		void acClear(void)
			{
			m_vec_NameGroup.clear();
			m_vec_Index.clear();
			m_qamPosition = 1;
			m_vec_Int.clear();
			m_vec_Condition.clear();
			}

		void add_NameGroup(std::string f_NameGroup, int f_Index)
			{
			m_vec_NameGroup.push_back(f_NameGroup);
			m_vec_Index.push_back(f_Index);
			}

		void add_Integer(int f_Int, char f_Condition)
			{
			m_vec_Int.push_back(f_Int);
			m_vec_Condition.push_back(f_Condition);
			}

		void add_Float(float f_Float, char f_Condition)
			{
			m_vec_Float.push_back(f_Float);
			m_vec_Condition.push_back(f_Condition);
			}

		std::vector<std::string> m_vec_NameGroup;
		std::vector<int> m_vec_Index;
		int m_qamPosition;
		std::vector<int> m_vec_Int;
		std::vector<float> m_vec_Float;
		std::vector<char> m_vec_Condition;
	};

	class qamTrigger : public qamType
	{
	public:
		qamTrigger() : qamType(MuTYPE_Code) { acClear(); m_ParentTriggerID = -1; };
		qamTrigger(int f_ID);
		~qamTrigger() { acClear(); }

		void acClear(void)
			{
			m_Int_At = 0;
			m_bool_Processed = false;
			m_Trigger = false;
			m_Updated = false;
			}

		void ac_Compute(void);

		bool ac_Process_Condition(void);

		Condition_Element* ac_Process_Condition_Element(void);

		std::string m_NameGroup;

		float m_X;
		float m_Y;
		float m_Z;

		float m_Xrot;
		float m_Yrot;
		float m_Zrot;

		int m_Order;
		int m_Type;
		int m_Repeat;

		int m_QamLevel;
		int m_QamID;

		int m_ID;

		bool m_Trigger;
		int m_ParentTriggerID;

		float m_Delay;

		std::string m_Condition;
		bool m_bool_Processed;

		int m_Int_At;

		bool m_Updated;

		std::vector<Condition_Element*> m_vec_ConElem;
	};

};

#endif