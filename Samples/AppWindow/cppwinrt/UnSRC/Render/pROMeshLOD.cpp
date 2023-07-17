#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROMeshLOD::init(bool active)
{
	if(m_mesh.num>0)
	{
		m_selmesh=g_render->loddetail<m_mesh.num?g_render->loddetail:0;
		m_bbox=m_mesh.buf[m_selmesh]->bbox;
	}
}

void pROMeshLOD::step(const float elapsed_time,const pMatrix& global)
{
	pMatrix m=m_transform*global;
	pVector v=m.get_translate()-g_render->camera.pos;
	float dist=v.length();

	int i=g_render->loddetail<m_mesh.num?g_render->loddetail:m_mesh.num;
	if (m_mesh.num==m_dist.num)
	for(;i<m_mesh.num;i++)
		if(dist<=m_dist.buf[i])
			break;
	m_selmesh=i;
	if(i==m_mesh.num)
		if(m_draw_after_maxdist)
			m_selmesh=i-1;
		else
			m_selmesh=-1;
	
	if(m_selmesh>=0 && m_selmesh<m_mesh.num)
		m_bbox=m_mesh.buf[m_selmesh]->bbox;

	pRenderObject::step(elapsed_time,m);
}

void pROMeshLOD::draw()
{
#ifndef P_DISABLE_3D
	if(m_selmesh>=0 && m_selmesh<m_mesh.num)
	{
		glMultMatrixf(&m_transform_global.mf[0]);
		m_mesh.buf[m_selmesh]->draw(g_render->renderflag,g_render->rendermode);
	}
#endif
}

int pROMeshLOD::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
		{
			pd->type=-'f';
			pd->data=&m_dist;
			pd->name="dist";
			pd->comment="LOD distances";
		}
		break;
		case 1:
		{
			pd->type=-'m';
			pd->data=&m_mesh;
			pd->name="meshes";
			pd->comment="Array of meshes' .P3D file";
		}
		break;
		case 2:
		{
			pd->type='b';
			pd->data=&m_draw_after_maxdist;
			pd->name="draw_after_maxdist";
			pd->comment="If enabled, mesh can be drawn after maxdist";
		}
		break;
	}

	return 3;
}

int pROMeshLOD::get_attach_point(int i,pDummy **d)
{
	if (m_mesh.num)
	{
		if (d)
			*d=&m_mesh.buf[0]->dummy[i];
		return m_mesh.buf[0]->ndummy;
	}
	return 0;
}

int pROMeshLOD::get_obb(int i,pOrientedBoundBox **o)
{
	if (m_mesh.num)
	{
		if (o)
			*o=&m_mesh.buf[0]->obb[i];
		return m_mesh.buf[0]->nobb;
	}
	return 0;
}

void pROMeshLOD::setup_light()
{
	if(m_selmesh>=0 && m_selmesh<m_mesh.num)
	{
		m_light.clear();
		if ((m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
		for(int i=0;i<g_render->light.num;i++)
			if(g_render->light[i]->update_objects_light(this))
				m_light.add(g_render->light[i]);
	}

	pRenderObject::setup_light();
}

bool pROMeshLOD::ray_intersect(pRayIntersectInfo *ri)
{
	pMesh *msh=get_mesh();
	
	if(msh==0)
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

		face=msh->ray_intersect(ro,rd,ip,dist);
		if (face!=-1 && dist<ri->dist)
		{
			ri->ip=ip;
			ri->dist=dist;
			ri->obj=this;
			ri->mesh=msh;
			ri->face=face;
			ret=true;
		}
	}

	return ret;
}

#endif
