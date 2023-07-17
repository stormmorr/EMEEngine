#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROMeshHuge::update_bound_box()
{
	if(m_mesh)
	{
		m_bbox=m_mesh->bbox;
		pVector bb_center=m_bbox.get_center();
		m_bbox.max=bb_center+(m_bbox.max-bb_center)*(float)m_size_scale;
		m_bbox.min=bb_center+(m_bbox.min-bb_center)*(float)m_size_scale;
	}
}

void pROMeshHuge::init(bool active)
{
	update_bound_box();
}

void pROMeshHuge::step(const float elapsed_time,const pMatrix& global)
{
	m_culled=false;
	if(m_mesh)
	{
		if(g_render->hugeplaneflag)
		{
			pRenderObject::step_huge_objects(elapsed_time,global,m_pos,&m_calc_scale,&m_culled);
			m_final_scale=(float)(m_calc_scale*m_size_scale);
		}
		else
		{
			pRenderObject::step(elapsed_time,m_transform*global);
			m_final_scale=(float)m_size_scale;
		}
	}
}

void pROMeshHuge::draw()
{
#ifndef P_DISABLE_3D
	if(m_culled)
		return;

	glEnable(GL_NORMALIZE);
	glMultMatrixf(&m_transform_global.mf[0]);
	if (g_render->hugeplaneflag)
		glScalef(m_calc_scale,m_calc_scale,m_calc_scale);
	glScaled(m_size_scale,m_size_scale,m_size_scale);
	
	if (m_mesh)
		m_mesh->draw(g_render->renderflag,g_render->rendermode);

	glDisable(GL_NORMALIZE);
#endif
}

int pROMeshHuge::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='m';
			pd->data=&m_mesh;
			pd->name="mesh";
			pd->comment="Mesh's .P3D file";
		break;
		case 1:
			pd->type='d';
			pd->data=&m_size_scale;
			pd->name="size_scale";
			pd->comment="Scale factor to resize mesh";
		break;
		case 2:
			pd->type='q';
			pd->data=&m_pos;
			pd->name="pos";
			pd->comment="Double-precision global position";
		break;
	}
	return 3;
}

void pROMeshHuge::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		case 1:
			update_bound_box();
		break;
	}
}

int pROMeshHuge::get_attach_point(int i,pDummy **d)
{
	if (m_mesh)
	{
		if (d)
			*d=&m_mesh->dummy[i];
		return m_mesh->ndummy;
	}
	return 0;
}

int pROMeshHuge::get_obb(int i,pOrientedBoundBox **o)
{
	if (m_mesh)
	{
		if (o)
			*o=&m_mesh->obb[i];
		return m_mesh->nobb;
	}
	return 0;
}

bool pROMeshHuge::ray_intersect(pRayIntersectInfo *ri)
{
	if(m_mesh==0)
		return false;
	
	bool ret=false;

	float t1,t2;
	if (m_bbox_global_childs.ray_intersect(ri->ro,ri->rd,t1,t2)==-1)
		ret=false;
	else
	{
		ret=pRenderObject::ray_intersect(ri);

		float dist;
		pVector ip;
		int face;
		
		pMatrix m;
		m_transform_global.get_affine_inverse(m);

		pVector ro=ri->ro*m;
		m.mf[12]=m.mf[13]=m.mf[14]=0;
		pVector rd=ri->rd*m;

		face=m_mesh->ray_intersect(ro,rd,ip,dist);
		if (face!=-1 && dist<ri->dist)
		{
			ri->ip=ip;
			ri->dist=dist;
			ri->obj=this;
			ri->mesh=m_mesh;
			ri->face=face;
			ret=true;
		}
	}

	return ret;
}

void pROMeshHuge::setup_light()
{
	if (m_mesh)
	{
		m_light.clear();
		if ((m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
		for(int i=0;i<g_render->light.num;i++)
			if(g_render->light[i]->update_objects_light(this))
				m_light.add(g_render->light[i]);
	}

	pRenderObject::setup_light();
}

#endif
