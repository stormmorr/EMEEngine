/*

	unSegmentContainer - Memory Container Vessel Base Class
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef SEGMENTCONTAINER_H
#define SEGMENTCONTAINER_H

namespace UN
{

class unSegmentContainer
{
public:
	unSegmentContainer() {};
	~unSegmentContainer() {};

	void acSync(void);
	void acReset(void);
};

};

#endif