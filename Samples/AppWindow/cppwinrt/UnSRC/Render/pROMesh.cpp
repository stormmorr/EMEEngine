#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROMesh::init(bool active)
{
	if (m_mesh)
		m_bbox=m_mesh->bbox;
}

void pROMesh::step(const float elapsed_time,const pMatrix& global)
{
	if (m_mesh)
		m_bbox=m_mesh->bbox;

	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROMesh::draw()
{
#ifndef P_DISABLE_3D
	if (m_mesh)
	{
		glMultMatrixf(&m_transform_global.mf[0]);
		m_mesh->draw(g_render->renderflag,g_render->rendermode);
	}
#endif
}

void pROMesh::draw_shadows(const pVector& lightpos)
{
	if (m_mesh)
	{
		pVector lpos=lightpos-m_transform_global.get_translate();
		lpos=m_transform_global.multiply_rotation_transpose(lpos);

		m_mesh->draw_faces_shadow(lpos);
	}
}

int pROMesh::get_custom_param_desc(int i,pParamDesc *pd)
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
	}
	return 1;
}

int pROMesh::get_attach_point(int i,pDummy **d)
{
	if (m_mesh)
	{
		if (d)
			*d=&m_mesh->dummy[i];
		return m_mesh->ndummy;
	}
	return 0;
}

int pROMesh::get_obb(int i,pOrientedBoundBox **o)
{
	if (m_mesh)
	{
		if (o)
			*o=&m_mesh->obb[i];
		return m_mesh->nobb;
	}
	return 0;
}

bool pROMesh::ray_intersect(pRayIntersectInfo *ri)
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

void pROMesh::setup_light()
{
	if (m_mesh)
	{
		m_light.clear();
		if ((m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
		for(int i=0;i<g_render->light.num;i++)
		{
			if(g_render->light[i]->update_objects_light(this))
				m_light.add(g_render->light[i]);
		}
	}

	pRenderObject::setup_light();
}

#endif
