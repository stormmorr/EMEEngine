#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROMeshSkeleton::init(bool active)
{
	if (active && m_mesh)
	{
		m_mesh->reset_ani();
		m_mesh->reset_mtg();
		m_mesh->reset_mtgani();
		int i;
		for(i=0;i<m_ani.num;i++)
			m_mesh->load_ani(g_render->app_path+m_ani.buf[i]);
		for(i=0;i<m_mtg.num;i++)
			m_mesh->load_mtg(g_render->app_path+m_mtg.buf[i]);
		for(i=0;i<m_mtgani.num;i++)
			m_mesh->load_mtgani(g_render->app_path+m_mtgani.buf[i]);
		if (m_mesh->check_data())
		{
			m_mesh->set_ani(m_curani,m_time_ani,m_blendtime);
			for( i=0;i<P_MSMAXMTGANI;i++ )
				if (m_curmtgani[i]!=-1)
					m_mesh->set_mtgani(i,m_curmtgani[i],m_time_mtg[i],m_mtgani_blendtime[i]);
		}
	}
}

void pROMeshSkeleton::step(const float elapsed_time,const pMatrix& global)
{
	if (m_mesh)
	{
		m_time_ani+=elapsed_time*m_timefactor_ani;
		for( int i=0;i<P_MSMAXMTGANI;i++ )
		{
			m_time_mtg[i]+=elapsed_time*m_timefactor_mtg[i];
			m_mesh->set_mtgani_weight(i,m_mtgani_weight[i]);
		}
		m_mesh->update(m_time_ani,m_time_mtg);
		m_bbox=m_mesh->bbox;
	}

	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROMeshSkeleton::draw()
{
#ifndef P_DISABLE_3D
	if (m_mesh)
	{
		const pMesh *m=m_mesh->get_draw_mesh();
		if (m)
		{
			glMultMatrixf(&m_transform_global.mf[0]);
			m->draw(g_render->renderflag,g_render->rendermode);

			int i,j,k=m_mesh->get_numbones();
			j=m_attach_mesh.num;
			if (m_attach_bone.num<j)
				j=m_attach_bone.num;
			for( i=0;i<j;i++ )
				if (m_attach_bone.buf[i]<k)
				{
					glPushMatrix();
					glMultMatrixf(&m_mesh->get_bone(m_attach_bone.buf[i]).mf[0]);
					m_attach_mesh.buf[i]->draw(g_render->renderflag,g_render->rendermode);
					glPopMatrix();
				}
		}
	}
#endif
}
	
void pROMeshSkeleton::draw_shadows(const pVector& lightpos)
{
	if (m_mesh)
	{
		const pMesh *m=m_mesh->get_draw_mesh();
		if (m)
		{
			pVector lpos=lightpos-m_transform_global.get_translate();
			lpos=m_transform_global.multiply_rotation_transpose(lpos);

			m->draw_faces_shadow(lpos);
		}
	}
}

int pROMeshSkeleton::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='k';
			pd->data=&m_mesh;
			pd->name="mesh";
			pd->comment="Geometry .P3D file for skeleton mesh";
		break;
		
		case 1:
			pd->type=-'s';
			pd->data=&m_ani;
			pd->name="ani";
			pd->comment="Animation .ANI files|Skeleton animation files (*.ani)|*.ani||";
		break;

		case 2:
			pd->type=-'s';
			pd->data=&m_mtg;
			pd->name="mtg";
			pd->comment="Morph traget .MTG files|Morph target files (*.mtg)|*.mtg||";
		break;

		case 3:
			pd->type=-'s';
			pd->data=&m_mtgani;
			pd->name="mtgani";
			pd->comment="Morph traget animations .MAN files|Morph target animation files (*.man)|*.man||";
		break;

		case 4:
			pd->type='f';
			pd->data=&m_timefactor_ani;
			pd->name="timefactor";
			pd->comment="Factor to multiply animation time (1.0 mean normal time and 1.2 is 20% faster than normal)";
		break;

		case 5:
			pd->type='i';
			pd->data=&m_curani;
			pd->name="curani";
			pd->comment="Currently selected animation";
		break;
		
		case 6:
			pd->type='f';
			pd->data=&m_blendtime;
			pd->name="blendtime";
			pd->comment="Animation blending duration in seconds";
		break;

		case 7:
			pd->type='i';
			pd->data=&m_curmtgani[0];
			pd->name="mtg_ani0";
			pd->comment="Morpth target animation for channel 0";
		break;

		case 8:
			pd->type='f';
			pd->data=&m_mtgani_blendtime[0];
			pd->name="mtg_blendtime0";
			pd->comment="Blend time for changes in morpth target animation channel 0";
		break;

		case 9:
			pd->type='f';
			pd->data=&m_mtgani_weight[0];
			pd->name="mtg_weight0";
			pd->comment="Weight for morpth target animation channel 0";
		break;
		
		case 10:
			pd->type='f';
			pd->data=&m_timefactor_mtg[0];
			pd->name="mtg_timefactor0";
			pd->comment="Factor to multiply mtg animation time on channel 0";
		break;

		case 11:
			pd->type='i';
			pd->data=&m_curmtgani[1];
			pd->name="mtg_ani1";
			pd->comment="Morpth target animation for chanel 1";
		break;

		case 12:
			pd->type='f';
			pd->data=&m_mtgani_blendtime[1];
			pd->name="mtg_blendtime1";
			pd->comment="Blend time for changes in morpth target animation channel 1";
		break;

		case 13:
			pd->type='f';
			pd->data=&m_mtgani_weight[1];
			pd->name="mtg_weight1";
			pd->comment="Weight for morpth target animation channel 1";
		break;

		case 14:
			pd->type='f';
			pd->data=&m_timefactor_mtg[1];
			pd->name="mtg_timefactor1";
			pd->comment="Factor to multiply mtg animation time on channel 1";
		break;

		case 15:
			pd->type='i';
			pd->data=&m_curmtgani[2];
			pd->name="mtg_ani2";
			pd->comment="Morpth target animation for chanel 2";
		break;

		case 16:
			pd->type='f';
			pd->data=&m_mtgani_blendtime[2];
			pd->name="mtg_blendtime2";
			pd->comment="Blend time for changes in morpth target animation channel 2";
		break;

		case 17:
			pd->type='f';
			pd->data=&m_mtgani_weight[2];
			pd->name="mtg_weight2";
			pd->comment="Weight for morpth target animation channel 2";
		break;

		case 18:
			pd->type='f';
			pd->data=&m_timefactor_mtg[2];
			pd->name="mtg_timefactor2";
			pd->comment="Factor to multiply mtg animation time on channel 2";
		break;

		case 19:
			pd->type='i';
			pd->data=&m_curmtgani[3];
			pd->name="mtg_ani3";
			pd->comment="Morpth target animation for chanel 3";
		break;

		case 20:
			pd->type='f';
			pd->data=&m_mtgani_blendtime[3];
			pd->name="mtg_blendtime3";
			pd->comment="Blend time for changes in morpth target animation channel 3";
		break;

		case 21:
			pd->type='f';
			pd->data=&m_mtgani_weight[3];
			pd->name="mtg_weight3";
			pd->comment="Weight for morpth target animation channel 3";
		break;

		case 22:
			pd->type='f';
			pd->data=&m_timefactor_mtg[3];
			pd->name="mtg_timefactor3";
			pd->comment="Factor to multiply mtg animation time on channel 3";
		break;

		case 23:
			pd->type=-'m';
			pd->data=&m_attach_mesh;
			pd->name="attach_mesh";
			pd->comment="Meshes attached to skeleton";
		break;

		case 24:
			pd->type=-'i';
			pd->data=&m_attach_bone;
			pd->name="attach_bone";
			pd->comment="Attach meshes skeleton bone indices";
		break;
	}
	
	return 25;
}

void pROMeshSkeleton::on_pos_parameter_change(int i)
{
	if (m_source)
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			init(m_source!=0);
			break;

		case 5:
			if (m_mesh && m_mesh->check_data())
				m_mesh->set_ani(m_curani,m_time_ani,m_blendtime);
			break;
		case 7:
			if (m_mesh && m_mesh->check_data())
				m_mesh->set_mtgani(0,m_curmtgani[0],m_time_mtg[0],m_mtgani_blendtime[0]);
			break;
		case 11:
			if (m_mesh && m_mesh->check_data())
				m_mesh->set_mtgani(1,m_curmtgani[1],m_time_mtg[1],m_mtgani_blendtime[1]);
			break;
		case 15:
			if (m_mesh && m_mesh->check_data())
				m_mesh->set_mtgani(2,m_curmtgani[2],m_time_mtg[2],m_mtgani_blendtime[2]);
			break;
		case 19:
			if (m_mesh && m_mesh->check_data())
				m_mesh->set_mtgani(3,m_curmtgani[3],m_time_mtg[3],m_mtgani_blendtime[3]);
			break;
	}
}

void pROMeshSkeleton::setup_light()
{
	if (m_mesh)
	{
		m_light.clear();
		if ((P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
		for(int i=0;i<g_render->light.num;i++)
			if(g_render->light[i]->update_objects_light(this))
				m_light.add(g_render->light[i]);
	}

	pRenderObject::setup_light();
}

#endif
