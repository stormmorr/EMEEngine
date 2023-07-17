#include "pch.h"
#include "paralelo3d.h"

pRenderObject::pRenderObject() :
  m_type((unsigned int)-1),m_id(0),m_flags(3),m_source(0),m_parent(0),
	m_num_frustum_planes(5)
{
}

pRenderObject::~pRenderObject()
{
}

pRenderObject::pRenderObject(const pRenderObject& in) :
	m_type(in.m_type),m_flags(in.m_flags),
	m_transform(in.m_transform),
	m_transform_global(in.m_transform_global),
	m_num_frustum_planes(in.m_num_frustum_planes),
	m_bbox(in.m_bbox),
	m_bbox_global(in.m_bbox_global),
	m_bbox_global_childs(in.m_bbox_global_childs),
	m_name(in.m_name)
{
	int i;
	m_child.reserve(in.m_child.num);
	for( i=0;i<in.m_child.num;i++ )
		m_child.add(in.m_child.buf[i]);

	m_light.reserve(in.m_light.num);
	for( i=0;i<in.m_light.num;i++ )
		m_light.add(in.m_light.buf[i]);

	m_source=&in;
	m_parent=0;
	m_id=0;
}

int pRenderObject::get_common_param_desc(int i,pParamDesc *pd)
{
	if (pd==0)
		return P_RONUMDEFAULTPARAM+get_custom_param_desc(0,0);
	else
	{
		pd->comment="";
		if (i>=P_RONUMDEFAULTPARAM)
			get_custom_param_desc(i-P_RONUMDEFAULTPARAM,pd);
		else
		switch(i)
		{
			case 0:
				pd->type=-'o';
				pd->data=&m_child;
				pd->name="child";
				break;
			case 1:
				pd->type='i';
				pd->data=&m_flags;
				pd->name="flags";
				break;
			case 2:
				pd->type='r';
				pd->data=&m_transform;
				pd->name="transform";
				break;
		}
	}
	return P_RONUMDEFAULTPARAM;
}

int pRenderObject::get_custom_param_desc(int i,pParamDesc *pd)
{
	return 0;
}

void pRenderObject::init(bool active)
{
}

void pRenderObject::step(const float elapsed_time,const pMatrix& global)
{
	int i;
	m_transform_global=global;
	
	m_bbox_global.reset();
	m_bbox_global.add_bbox(m_bbox,global);
	m_bbox_global_childs=m_bbox_global;

	if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
	{
		for( i=0;i<m_child.num;i++ )
			if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			{
				g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_child.buf[i]->m_name));
				m_child.buf[i]->step(elapsed_time,global);
				m_bbox_global_childs.add_bbox(m_child.buf[i]->m_bbox_global_childs);
			}
	}
	else
	{
		for( i=0;i<m_child.num;i++ )
			if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			{
				m_child.buf[i]->step(elapsed_time,global);
				m_bbox_global_childs.add_bbox(m_child.buf[i]->m_bbox_global_childs);
			}
	}
}

#ifdef P_MANAGER_OBJ
void pRenderObject::step_huge_objects(const float elapsed_time,const pMatrix& global,const pDVector& pos,float *scale,bool *culled)
{
	int i;
	pVector bb_center;
	pDVector cam_pos(g_render->camera.pos);
	double farplane=g_render->farplane;

	if(culled)
		*culled=false;
	m_num_frustum_planes=5-g_render->hugeplaneflag; 
	if(scale)
		*scale=1.0f;

	// update transform global
	m_transform_global=global;

	// Find what region (see header of pROMeshHuge.h) contains mesh

	// get object's direction in relation to camera
	pDVector dir(pos-(cam_pos+g_romanager->m_world_origin));
	// get distance to camera
	double dist_cam=dir.length(); dir*=1.0/dist_cam;
	// verifies if mesh is after huge plane
	if(dist_cam>g_render->hugeplane)
	{
		if(culled)
			*culled=true;
		return;
	}
	// verifies if mesh is after far plane
	if(dist_cam>farplane)
	{
		// update object's position and size
		double f=(dist_cam-farplane)/(g_render->hugeplane-farplane);
		f=farplane+f*farplane;
		pDVector new_pos=cam_pos+dir*f;
		m_transform_global.set_translate(pVector(new_pos));
		if(scale)
			*scale=(float)(f/dist_cam);
	}
	else
		m_transform_global.set_translate(pVector(cam_pos+dir*dist_cam));

	// updates bounding box's position and size
	bb_center=m_bbox.get_center();
	m_bbox_global.max=m_transform_global.get_translate()+(m_bbox.max-bb_center)*(scale?(*scale):1.0f);
	m_bbox_global.min=m_transform_global.get_translate()+(m_bbox.min-bb_center)*(scale?(*scale):1.0f);
	m_bbox_global_childs=m_bbox_global;
	for( i=0;i<m_child.num;i++ )
		if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			m_bbox_global_childs.add_bbox(m_child.buf[i]->m_bbox_global_childs);

	// update all children
	if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
	{
		for( i=0;i<m_child.num;i++ )
			if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			{
				g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_child.buf[i]->m_name));
				m_child.buf[i]->step(elapsed_time,m_transform_global);
			}
	}
	else
	{
		for( i=0;i<m_child.num;i++ )
			if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
				m_child.buf[i]->step(elapsed_time,m_transform_global);
	}
}
#endif

void pRenderObject::draw()
{
}

void pRenderObject::draw_shadows(const pVector& lightpos)
{
}

void pRenderObject::post_draw()
{
}

void pRenderObject::draw2d()
{
}

void pRenderObject::on_pre_parameter_change(int i)
{
}

void pRenderObject::on_pos_parameter_change(int i)
{
}

int pRenderObject::get_attach_point(int i,pDummy **d)
{
	return 0;
}

int pRenderObject::get_obb(int i,pOrientedBoundBox **o)
{
	return 0;
}

bool pRenderObject::ray_intersect(pRayIntersectInfo *ri)
{
	bool ret=false;
	
	for( int i=0;i<m_child.num;i++ )
		if ((m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
			if (m_child.buf[i]->ray_intersect(ri))
				ret=true;

	return ret;
}

#ifdef P_MANAGER_OBJ
void pRenderObject::release_child(int i,pRenderObject *new_parent)
{
	if(m_source==0 || (new_parent && new_parent->m_source==0))
		return;
	
	if(i==-1)
		for(int j=m_child.num-1;j>=0;j--)
			release_child(j,new_parent);
	else
	{
		m_child[i]->m_parent=new_parent;
		if(new_parent)
			new_parent->m_child.add(m_child[i]);
		else
			g_romanager->m_active_root.add(m_child[i]);
		m_child.remove(i);
	}
}

void pRenderObject::link_child(pRenderObject *o)
{
	if(m_source==0 || o==0 || o->m_source==0)
		return;
	
	if(o->m_parent)
	{
		pRenderObject *p=o->m_parent;
		for(int i=0;i<p->m_child.num;i++)
			if(p->m_child[i]==o)
			{
				p->m_child.remove(i);
				break;
			}
	}

	o->m_parent=this;
	m_child.add(o);
}
#endif

void pRenderObject::translate_world(const pVector& t)
{
	if (m_parent==0)
	{
		m_transform.mf[12]+=t.x;
		m_transform.mf[13]+=t.y;
		m_transform.mf[14]+=t.z;
	}

	for( int i=0;i<m_child.num;i++ )
		m_child.buf[i]->translate_world(t);
}

void pRenderObject::setup_light()
{
	for(int i=0;i<m_child.num;i++)
		if(m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			m_child.buf[i]->setup_light();
}

pMesh *pRenderObject::get_mesh()
{
	return NULL;
}
