#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROObfuscatingPoint::init(bool active)
{
	m_bbox.min.vec(-m_far_attenuation);
	m_bbox.max.vec(m_far_attenuation);

	m_start_time=g_romanager->m_time;
}

void pROObfuscatingPoint::step(const float elapsed_time,const pMatrix& global)
{
	static pRayIntersectInfo s_ri;

	pRenderObject::step(elapsed_time,m_transform*global);

	pVector pos=m_transform_global.get_translate();
	s_ri.ro=g_render->camera.pos;
	s_ri.rd=pos-s_ri.ro;
	s_ri.rd.normalize();
	if(!g_romanager->ray_intersect(&s_ri))
	{
		if(m_min_angle<1.0f)
		{
			float factor=1.0f;
			if(m_func.m_type!=P_PERIODICFUNC_NONE)
				factor=m_func.eval(g_romanager->m_time-m_start_time);

			pVector v=m_transform_global.get_translate()-g_render->camera.pos;
			float dist=v.length();
			v/=dist;

			if(dist<=m_far_attenuation)
			{
				if(dist>m_near_attenuation)
					factor*=1.0f-((dist-m_near_attenuation)/(m_far_attenuation-m_near_attenuation));

				float c=VECDOT(v,-g_render->camera.Z);

				if(c>m_min_angle)
				{
					g_render->const_blink(pVector(m_color.x,m_color.y,m_color.z,factor*(c-m_min_angle)/(1.0f-m_min_angle)));
					return;
				}
			}
		}
	}

	g_render->const_blink(pVector(0.0f,0.0f,0.0f,0.0f));
}

void pROObfuscatingPoint::draw()
{
}

int pROObfuscatingPoint::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
	case 0:
		pd->type='c';
		pd->name="color";
		pd->data=&m_color;
		pd->comment="Obfuscating color";
		break;
	case 1:
		pd->type='a';
		pd->name="min_angle";
		pd->data=&m_min_angle;
		pd->comment="Minimum obfuscating angle";
		break;
	case 2:
		pd->type='f';
		pd->name="near_attenuation";
		pd->data=&m_near_attenuation;
		pd->comment="Near attenuation radius";
		break;
	case 3:
		pd->type='f';
		pd->name="far_attenuation";
		pd->data=&m_far_attenuation;
		pd->comment="Far attenuation radius";
		break;
	case 4:
		pd->type='e';
		pd->name="func";
		pd->data=&m_func;
		pd->comment="Periodic fuction for opacity modulation";
		break;
	}
	return 5;
}

#endif
