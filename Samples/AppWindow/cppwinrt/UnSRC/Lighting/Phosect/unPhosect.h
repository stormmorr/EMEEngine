/*

	unPhosect
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef unPhosect_H
#define unPhosect_H

#include "pMath.h"

class unPhosect
{
public:
	unPhosect();
	~unPhosect();

	bool Scan(pVertex i_Vertex);

	unsigned int m_Eye[2];

protected:
	pVertex m_Vertex;
	bool m_Active;
};

#endif