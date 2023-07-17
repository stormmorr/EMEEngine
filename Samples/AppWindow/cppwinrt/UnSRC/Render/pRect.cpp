#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pRect::intersection(const pRect& r1,const pRect& r2)
{
	int tmp1,tmp2;

	m_x=(r1.m_x<r2.m_x)?r2.m_x:r1.m_x;
	m_y=(r1.m_y<r2.m_y)?r2.m_y:r1.m_y;
	tmp1=r1.m_x+r1.m_width;
	tmp2=r2.m_x+r2.m_width;
	m_width=(tmp1<tmp2)?tmp1-m_x:tmp2-m_x;
	tmp1=r1.m_y+r1.m_height;
	tmp2=r2.m_y+r2.m_height;
	m_height=(tmp1<tmp2)?tmp1-m_y:tmp2-m_y;
}

#endif
