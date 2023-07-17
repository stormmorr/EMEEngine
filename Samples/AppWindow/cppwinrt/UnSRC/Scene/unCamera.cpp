/*

	unCamera
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "unCamera.h"

unCamera::unCamera(int i_width, int i_height)
{
	m_width = i_width;
	m_height = i_height;
}

unCamera::~unCamera()
{

}

void unCamera::setFOV(float i_FOV)
{
	m_FOV = i_FOV;
}

void unCamera::setPosition(float i_pos)
{
	m_pos = i_pos;
}