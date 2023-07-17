#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

pROExplodeObject::~pROExplodeObject()
{
	if(m_source!=0)
	{
		restore_opacity();
		if(m_obj)
			deactivate(m_activeid);
	}
}

void pROExplodeObject::init(bool active)
{
	m_save_life=m_life;
	if(m_obj==this)
		m_obj=0;
	else if(m_obj && active)
	{
		if(m_obj->m_flags&P_ROFLAGS_HASMESH)
			m_flags|=P_ROFLAGS_HASMESH;
		else
			m_flags&=~P_ROFLAGS_HASMESH;

		m_activeid=activate(m_obj);
}
}

void pROExplodeObject::step(const float elapsed_time,const pMatrix& global)
{
	m_life-=elapsed_time;

	if(m_life<=0.0f)
	{
		g_romanager->post_deactivate(m_id);
		return;
	}

	// set position back to origin, rotate according to angular velocity...
	pVector pos=m_transform.get_translate();
	m_transform.set_translate(pVector(0.0f,0.0f,0.0f));
	m_transform.rotate(m_ang_vel.w,m_ang_vel);
	// ... and update position according to linear velocity
	pos+=elapsed_time*m_lin_vel;
	m_transform.set_translate(pos);

	pMatrix m=m_transform*global;

	if (m_obj)
	{
		pRenderObject *obj=m_active.get_object(m_activeid);
		if(obj)
		{
			obj->step(elapsed_time,m);
			pMatrix mi;
			m.get_affine_inverse(mi);
			m_bbox.reset();
			m_bbox.add_bbox(obj->m_bbox_global_childs,mi);
		}
	}

	pRenderObject::step(elapsed_time,m);

	if(m_obj)
	{
		// Split objects into: mesh, non-mesh opaque and non-mesh transparent
		m_active_visible.clear();
		m_active_visible_mesh.clear();
		m_active_visible_transp.clear();
		pRenderObject *obj=m_active.get_next_object(1);
		while(obj)
		{
			if((obj->m_flags&P_ROFLAGS_HASMESH)==0)
			{
				if((obj->m_flags&P_ROFLAGS_TRANSP)==0)
					m_active_visible.add(obj);
				else
					m_active_visible_transp.add(obj);
			}
			else
				m_active_visible_mesh.add(obj);
			obj=m_active.get_next_object();
		}

		// Updates opacity and life of each object

		m_opac=1.0f;
		m_restore=true;

		// elapsed life
		float dlife=m_save_life-m_life;

		// do fade in or fade out
		if(m_fade_in>dlife)
		{
			m_flags|=P_ROFLAGS_TRANSP;
			m_opac=(fabsf(m_fade_in-0.0f)<EPSILON)?1.0f:dlife/m_fade_in;
			m_restore=false;
		}
		else if(m_life<m_fade_out)
		{
			m_flags|=P_ROFLAGS_TRANSP;
			m_opac=(fabsf(m_fade_out-0.0f)<EPSILON)?1.0f:m_life/m_fade_out;
			m_restore=false;
		}
		else
			m_flags&=~P_ROFLAGS_TRANSP;
	}
}

void set_opacity(pRenderObject *obj,float opac,bool restore=false)
{
	if(obj->m_type==TYPE_RO_MESH)
	{
		pROMesh *msh=(pROMesh *)obj;

		if(msh->m_mesh)
		if(restore)
		{
			for(int i=0;i<msh->m_mesh->nmat;i++)
				msh->m_mesh->mat[i].opacity=1.0f;
		}
		else 
		{
			for(int i=0;i<msh->m_mesh->nmat;i++)
				msh->m_mesh->mat[i].opacity=opac;
		}
	}
	else if(obj->m_type==TYPE_RO_MESH_LOD)
	{
		pROMeshLOD *msh=(pROMeshLOD *)obj;

		if(msh->m_selmesh!=-1)
		if(restore)
		{
			for(int i=0;i<msh->m_mesh.buf[msh->m_selmesh]->nmat;i++)
				msh->m_mesh.buf[msh->m_selmesh]->mat[i].opacity=1.0f;
		}
		else 
		{
			for(int i=0;i<msh->m_mesh.buf[msh->m_selmesh]->nmat;i++)
				msh->m_mesh.buf[msh->m_selmesh]->mat[i].opacity=opac;
		}
	}
	else if(obj->m_type==TYPE_RO_BILLBOARD)
	{
		pROBillboard *bill=(pROBillboard *)obj;
		pROBillboard *src_bill=(pROBillboard *)obj->m_source;

		if(!restore)
			bill->m_color.w=src_bill->m_color.w*opac;
	}
	else if(obj->m_type==TYPE_RO_PARTICLE_SYSTEM)
	{
		pROParticleSystem *ps=(pROParticleSystem *)obj;
		pROParticleSystem *src_ps=(pROParticleSystem *)obj->m_source;

		if(ps->m_models.num)
		{
			int i,j;
			if(restore)
			{
				for(j=0;j<ps->m_models.num;j++ )
				for(i=0;i<ps->m_models.buf[j]->nmat;i++)
					ps->m_models.buf[j]->mat[i].opacity=1.0f;
			}
			else 
			{
				for(j=0;j<ps->m_models.num;j++ )
				for(i=0;i<ps->m_models.buf[j]->nmat;i++)
					ps->m_models.buf[j]->mat[i].opacity=opac;
			}
		}
		else
		{
			if(!restore)
				ps->m_color.w=src_ps->m_color.w*opac;
		}
	}
}

void pROExplodeObject::draw()
{
	if(m_life<=0.0f)
		return;

	if(g_render->rendermode==-1) // render non-mesh opaque objects
		draw(m_active_visible);
	else if(g_render->rendermode==-2)
		draw(m_active_visible_transp);
	else
		draw(m_active_visible_mesh);
}

int pROExplodeObject::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
		{
			pd->type='f';
			pd->data=&m_life;
			pd->name="life";
			pd->comment="Life of explode object (in seconds)";
		}
		break;
		case 1:
		{
			pd->type='f';
			pd->data=&m_fade_in;
			pd->name="fade_in";
			pd->comment="Duration of fade in effect (in seconds)";
		}
		break;
		case 2:
		{
			pd->type='f';
			pd->data=&m_fade_out;
			pd->name="fade";
			pd->comment="Duration of fade out effect (in seconds)";
		}
		break;
		case 3:
		{
			pd->type='o';
			pd->data=&m_obj;
			pd->name="object";
			pd->comment="Associated render object that will be through away";
		}
		break;
	}
	return 4;
}

void pROExplodeObject::on_pre_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 3:
		{
			if(m_source!=0)
			{
				restore_opacity();
				if(m_obj)
					deactivate(m_activeid);
			}
		}
		break;
	}
}

void pROExplodeObject::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		{
			m_save_life=m_life;
		}
		break;

		case 3:
		{
			if(m_obj==this)
				m_obj=0;
			else if(m_obj && (m_source!=0))
			{
				if(m_obj->m_flags&P_ROFLAGS_HASMESH)
					m_flags|=P_ROFLAGS_HASMESH;
				else
					m_flags&=~P_ROFLAGS_HASMESH;

				m_activeid=activate(m_obj);
		}
		}
		break;
	}
}

unsigned int pROExplodeObject::activate(pRenderObject *stockobj)
{
	static int objcount_active=0;
	pRenderObject *o,*obj=stockobj;

	if(obj)
	{
		o=obj->clone();
		objcount_active++;
		m_active.add(objcount_active,o);
		o->m_id=objcount_active;

		int i,j;
		// activate children
		for(i=0;i<o->m_child.num;i++)
		{
			j=activate(o->m_child.buf[i]);
			o->m_child.buf[i]=m_active.get_object(j);
			o->m_child.buf[i]->m_parent=o;
		}
		o->init(1);
		return o->m_id;
	}
	return 0;
}

void pROExplodeObject::deactivate(unsigned int activeobj)
{
	pRenderObject *obj=m_active.remove(activeobj);
	
	if(obj)
	{
		// free memory of children
		for (int i=0;i<obj->m_child.num;i++)
			deactivate(obj->m_child.buf[i]->m_id);

		delete obj;
	}
}

void pROExplodeObject::restore_opacity()
{
	pRenderObject *obj=m_active.get_next_object(1);
	while(obj)
	{
		set_opacity(obj,1.0f,true);
		obj=m_active.get_next_object();
	}
}

void pROExplodeObject::draw(pArray<pRenderObject *>& objects)
{
#ifndef P_DISABLE_3D
	int i;
	for( i=0;i<objects.num;i++ )
	{
		glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
		set_opacity(objects.buf[i],m_opac,m_restore);
		glPushMatrix();
		objects.buf[i]->draw();
		glPopMatrix();
		// to not affect another object that uses same mesh
		if(!m_restore)
			set_opacity(objects.buf[i],1.0f,true);
		glPopAttrib();
	}
#endif
}

#endif
