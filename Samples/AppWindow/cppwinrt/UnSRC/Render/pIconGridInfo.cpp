#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

bool pIconGridInfo::get_icon_tex_coord(int i,float &u0,float &v0,float &u1,float &v1) const
{
	if(m_grid_pic!=-1 && m_icon_width!=0 && m_icon_height!=0 && g_render->pic[m_grid_pic]->sx!=0 && g_render->pic[m_grid_pic]->sy!=0)
	{
		float width=(float)m_icon_width/(1<<g_render->texdetail);
		float height=(float)m_icon_height/(1<<g_render->texdetail);
		if (width==0 || height==0)
			u0=v0=u1=v1=0.5f;
		else
		{
			int icons_per_row=(int)(g_render->pic[m_grid_pic]->sx/width);
			float row=float(i/icons_per_row);
			float col=float(i%icons_per_row);

			float inc_u=width/float(g_render->pic[m_grid_pic]->sx);
			float inc_v=height/float(g_render->pic[m_grid_pic]->sy);
			
			u0=col*inc_u;
			u1=u0+inc_u;
			v1=1.0f-row*inc_v;
			v0=v1-inc_v;
		}

		return true;
	}

	return false;
}

#endif
