/*

	unCamera
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unCamera__
#define __unCamera__

#include "../ClassUtil/unClassCache.h"

class unCamera : public unClassCache
{
public:
	unCamera(int i_width, int i_height);
	~unCamera();

	void setFOV(float i_FOV);
	void setPosition(float i_pos);

	float getPos(void) { return m_pos; }
	float getFOV(void) { return m_FOV; }

private:
	float m_pos;
	float m_FOV;
	float m_width;
	float m_height;
};

#endif