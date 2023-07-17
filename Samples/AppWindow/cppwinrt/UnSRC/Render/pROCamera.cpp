#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROCamera::step(const float elapsed_time,const pMatrix& global)
{
	m_bbox.min.vec(-m_radius);
	m_bbox.max.vec(m_radius);

	if(m_parent)
	{
		pVector tx=m_parent->m_transform_global.get_column3(0);
		pVector ty=m_parent->m_transform_global.get_column3(1);
		pVector tz=m_parent->m_transform_global.get_column3(2);

		pVector tt=m_parent->m_transform_global.get_translate();
		pVector target=tt+(tx*(m_target_trans.x)+
					ty*(m_target_trans.y)+tz*(m_target_trans.z));

		float cosa=cosf(m_angle_x*PIOVER180);
		float cosb=cosf(m_angle_y*PIOVER180);
		float sina=sinf(m_angle_x*PIOVER180);
		float sinb=sinf(m_angle_y*PIOVER180);
		
		pVector to(	cosa*cosb,
					sina*cosb,
					sinb);
		to.normalize();
		
		pVector t=tx*to.y+ty*to.x+tz*to.z;
		t.normalize();

		target+=m_dist*t;

		pVector pos=m_transform.get_translate();
		pVector totarget=target-pos;
		if (m_follow_speed>=0)
			totarget*=m_follow_speed*elapsed_time;

		m_transform.set_translate(pos+totarget);

		pRenderObject::step(elapsed_time,m_transform);
	}
	else
		pRenderObject::step(elapsed_time,m_transform*global);

	if(m_source)
		set_render_camera();
}

void pROCamera::set_render_camera()
{
	pVector pos=m_transform_global.get_translate();
	g_render->camera.pos=pos;
	g_render->camera.fov=m_fov;
	if(m_parent)
	{
		pVector dir=pos-m_parent->m_transform_global.get_translate();
		dir.normalize();
		pVector up=m_parent->m_transform_global.get_column3(2);
		up.normalize();
		g_render->camera.align_z(dir,up);
	}
	else
	{
		pVector dir=m_transform_global.get_column3(2);
		dir.normalize();
		pVector up=m_transform_global.get_column3(1);
		up.normalize();
		g_render->camera.align_z(dir,up);
	}
}

void pROCamera::set_target(pRenderObject *o)
{
	if(m_parent)
	{
		for(int i=0;i<m_parent->m_child.num;i++)
			if(m_parent->m_child[i]==this)
			{
				m_parent->m_child.remove(i);
				break;
			}
	}

	if(o)
		o->m_child.add(this);

	m_parent=o;
}

void pROCamera::draw()
{
	
}

int pROCamera::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&m_radius;
			pd->name="radius";
		break;
		case 1:
			pd->type='f';
			pd->data=&m_fov;
			pd->name="fov";
		break;
		case 2:
			pd->type='v';
			pd->data=&m_target_trans;
			pd->name="target_trans";
		break;
		case 3:
			pd->type='f';
			pd->data=&m_dist;
			pd->name="dist";
		break;
		case 4:
			pd->type='f';
			pd->data=&m_angle_x;
			pd->name="angle_x";
		break;
		case 5:
			pd->type='f';
			pd->data=&m_angle_y;
			pd->name="angle_y";
		break;
		case 6:
			pd->type='f';
			pd->data=&m_follow_speed;
			pd->name="follow_speed";
		break;
	}

	return 7;
}

void pROCamera::on_pos_parameter_change(int i)
{
	switch(i)
	{
		case 6: // follow_speed
			m_follow_speed=(m_follow_speed>1.0f)?1.0f:(m_follow_speed<0.0f)?0.0f:m_follow_speed;
		break;
	}
}

#endif
