#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROMeshRelief::init(bool active)
{
#if 0 // P_SUPPORT_CG
	if (m_source==0)
	{
		if (m_rm==0)
			m_rm=new pRM;

		m_rm->load(m_progmode,m_shadows!=0,m_doubleprec!=0,m_depthcorrect!=0,m_depthbias!=0,m_borderclamp!=0,m_curved!=0);

		if (m_texture_null==-1)
			m_texture_null=g_render->build_onepixelmap(255,255,255);
	}
#endif
}

void pROMeshRelief::step(const float elapsed_time,const pMatrix& global)	
{
	if (m_mesh)
		m_bbox=m_mesh->bbox;
	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROMeshRelief::draw()
{
#if 0 // P_SUPPORT_CG
	if (m_rm && m_light.num)
	{
		glMultMatrixf(&m_transform_global.mf[0]);
		
		pLight l;
		if (m_light.num)
			l=*m_light.buf[0];

		int texturecolor=m_texture_color==-1?m_texture_null:m_texture_color;
		int texturerelief=m_texture_relief==-1?m_texture_null:m_texture_relief;

		if (g_render->rendermode==P_RENDERMODE_SHADOWS)
		{
			m_rm->draw_shadows(m_mesh,texturerelief,m_tile,m_depth,l.pos.w);
		}
		else
		if (g_render->rendermode<0)
		{
			pVector diff=m_diff*l.color;
			diff.w=m_diff.w;
			pVector spec=m_spec*l.color;
			spec.w=m_spec.w;

			m_rm->draw(m_mesh,texturecolor,texturerelief,-1,m_tile,m_depth,
				g_render->lightambient,diff,spec,&l);
		}
	}
#endif
}

void pROMeshRelief::draw_shadows(const pVector& lightpos)
{
	if (m_mesh)
	{
		pVector lpos=lightpos-m_transform_global.get_translate();
		lpos=m_transform_global.multiply_rotation_transpose(lpos);

		m_mesh->draw_faces_shadow(lpos);
	}
}

int pROMeshRelief::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='i';
			pd->data=&m_progmode;
			pd->name="progmode";
			pd->comment="Program mode|Normal Mapping|Parallax Mapping|Parallax Ocllusion Mapping|Relief Mapping";
		break;

		case 1:
			pd->type='m';
			pd->data=&m_mesh;
			pd->name="mesh";
			pd->comment="Mesh file for relief object";
		break;

 		case 2:
			pd->type='p';
			pd->data=&m_texture_color;
			pd->name="tex_color";
			pd->comment="Color texture map";
		break;

		case 3:
			pd->type='p';
			pd->data=&m_texture_relief;
			pd->name="tex_relief";
			pd->comment="Relief texture map";
		break;

		case 4:
			pd->type='i';
			pd->data=&m_tile;
			pd->name="tile";
			pd->comment="Relief tile factor";
		break;

		case 5:
			pd->type='f';
			pd->data=&m_depth;
			pd->name="depth";
			pd->comment="Relief depth factor";
		break;

		case 6:
			pd->type='c';
			pd->data=&m_diff;
			pd->name="diffuse";
			pd->comment="Diffuse color";
		break;

		case 7:
			pd->type='c';
			pd->data=&m_spec;
			pd->name="specular";
			pd->comment="Specular color";
		break;
		
		case 8:
			pd->type='f';
			pd->data=&m_spec.w;
			pd->name="specularpower";
			pd->comment="Specular power (bigger then 1)";
		break;

		case 9:
			pd->type='b';
			pd->data=&m_shadows;
			pd->name="shadows";
			pd->comment="Relief self shadows flag";
		break;

		case 10:
			pd->type='b';
			pd->data=&m_depthcorrect;
			pd->name="depthcorrect";
			pd->comment="Relief depth correct flag";
		break;

		case 11:
			pd->type='b';
			pd->data=&m_depthbias;
			pd->name="depthbias";
			pd->comment="Relief perspective depth bias flag";
		break;

		case 12:
			pd->type='b';
			pd->data=&m_doubleprec;
			pd->name="doubleprec";
			pd->comment="Relief double precision flag";
		break;

		case 13:
			pd->type='b';
			pd->data=&m_borderclamp;
			pd->name="doubleprec";
			pd->comment="Relief border clamp flag";
		break;

		case 14:
			pd->type='b';
			pd->data=&m_curved;
			pd->name="curved";
			pd->comment="Curved relief mapping flag";
		break;
	}
	
	return 15;
}

void pROMeshRelief::on_pos_parameter_change(int i)
{
#if 0 // P_SUPPORT_CG
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			init(m_source!=0);
			break;
	}
#endif
}

void pROMeshRelief::setup_light()
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
