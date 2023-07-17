/*

	unSegment - Memory Management
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "unSegmentExp.h"

using namespace UN;

namespace UN
{

DllExport managed_shared_memory *m_unSegment;

DllExport unSegmentMgr *m_unSegFrame;

void acSegmentInitialize(bool i_CFlag)
{
	if(i_CFlag)
		{
		shared_memory_object::remove("UnificationSPC");
		//m_unSegFrame = new unSegmentMgr();

		m_unSegment = new managed_shared_memory(create_only, "UnificationSPC", UN_SEGMENT_DEFAULT_SIZE);

		printf("UN:::--Memory Segment Manager--\n");
		}
	else
		{
		//m_unSegFrame = (unSegmentMgr*) new unSegmentFrame();
		printf("UN:::unSegmentFrame -Aquire-\n");
		}
};

};