/*

	unClarity - General LOD
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include <vector>
#include "../Utility/SubscriberSlots.h"

class unRange
{
public:
	std::vector<int> pos;
	float interaction;
	float influences;
};

class unClarity
{
public:
	unClarity();
	~unClarity();

	void run(void);
	bool updateClarity(unRange i_range);

	std::vector<UN::SubscriberSlot> vec_ClaritySlot;

public:
	float m_claritylevel;
};