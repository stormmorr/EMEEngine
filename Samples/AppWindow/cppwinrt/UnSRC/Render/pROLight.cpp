#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROLight::init(bool active)
{
}

void pROLight::step(const float elapsed_time,const pMatrix& global)
{
	m_light.objlistlight.clear();

	m_bbox.min.vec(-m_radius);
	m_bbox.max.vec(m_radius);
	
	pMatrix m=m_transform*global;

	m_light.pos=m.get_translate();
	m_light.pos.w=m_radius;
	m_light.angle=m_angle;
	if(m_angle>0.0f)
	{
		m_light.orientation.set_column3(0,m.get_column3(0));
		m_light.orientation.set_column3(1,m.get_column3(1));
		m_light.orientation.set_column3(2,m.get_column3(2));
		m_light.build_frustum();
	}
	else
	{
		m_light.bbox.max=m_bbox.max+m_light.pos;
		m_light.bbox.min=m_bbox.min+m_light.pos;
	}

	m_light.flags=m_enabled;
	if(m_shadow==0)
		m_light.flags+=P_LIGHTFLAGS_NOSHADOW;
	else if(m_shadow==1) // shadow volume
		m_light.type_shadow=0;
	else if(m_shadow==2) // shadow map
		m_light.type_shadow=1;
	if (m_global)
		m_light.flags+=P_LIGHTFLAGS_GLOBAL;

	if (m_func.m_type!=P_PERIODICFUNC_NONE)
	{
		float f=m_func.eval(g_romanager->m_time);
		if (f>0)
			m_light.color=m_color*m_multiplier*f;
		else
			m_light.flags=0;
	}
	else
		m_light.color=m_color*m_multiplier;

	pRenderObject::step(elapsed_time,m_transform*global);

	if (m_light.flags&P_LIGHTFLAGS_ENABLED &&
		g_render->view.clip_bbox(m_bbox_global,m_num_frustum_planes))
			g_render->light.add(&m_light);
}

void pROLight::draw()
{
}

int pROLight::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
	case 0:
		pd->type='b';
		pd->name="enabled";
		pd->data=&m_enabled;
		pd->comment="Turn on/off source light";
		break;
	case 1:
		pd->type='f';
		pd->name="radius";
		pd->data=&m_radius;
		pd->comment="Light's radius";
		break;
	case 2:
		pd->type='f';
		pd->name="multiplier";
		pd->data=&m_multiplier;
		pd->comment="Multiplier of light's intensity";
		break;
	case 3:
		pd->type='c';
		pd->name="color";
		pd->data=&m_color;
		pd->comment="Light's color";
		break;
	case 4:
		pd->type='e';
		pd->data=&m_func;
		pd->name="function";
		pd->comment="Function to animate color of light";
		break;
	case 5:
		pd->type='f';
		pd->data=&m_angle;
		pd->name="angle";
		pd->comment="Angle in degrees (for spot lights)";
		break;
	case 6:
		pd->type='i';
		pd->data=&m_shadow;
		pd->name="shadow";
		pd->comment="Shadow-casting flag|No Shadow|Shadow Volume|Shadow Map";
		break;
	case 7:
		pd->type='b';
		pd->data=&m_global;
		pd->name="global";
		pd->comment="Light global flag (illuminates all objects)";
		break;
	}
	return 8;
}

#endif
