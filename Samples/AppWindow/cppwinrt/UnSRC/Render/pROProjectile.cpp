#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROProjectile::update_bounding_box()
{
	if(m_mesh)
		m_bbox=m_mesh->bbox;
	else
	{
		float size_z = m_size_side_x > m_size_side_y ? m_size_side_x : m_size_side_y;
		m_bbox.max.vec( size_z);
		m_bbox.min.vec(-size_z);
	}
}

void pROProjectile::init(bool active)
{
	m_start_time=g_romanager->m_time;
	update_bounding_box();
}

void pROProjectile::step(const float elapsed_time,const pMatrix& global)
{
	if(m_mesh)
		update_transform(m_transform.get_translate(),m_transform.get_column3(2));
	else
		update_transform(m_transform.get_translate(),m_transform.get_column3(0));
	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROProjectile::draw()
{
#ifndef P_DISABLE_3D
	if(m_mesh)
	{
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);

		if(g_render->rendermode==P_RENDERMODE_TRANSP || g_render->rendermode==P_RENDERMODE_PASS)
			return;
		if(m_glow==0 && g_render->rendermode==P_RENDERMODE_GLOW)
			return;

		g_render->sel_tex(-1);
		glColor4fv(&m_color.x);
		glMultMatrixf(&m_transform_global.mf[0]);
		m_mesh->array_lock(0,g_render->vertbuffer);
		m_mesh->array_draw(g_render->vertbuffer);
		m_mesh->array_unlock();

		glPopAttrib();
	}
	else
	{
		float half_x=m_size_side_x*0.5f;
		float half_y=m_size_side_y*0.5f;
		float half=m_size_front*0.5f;

		if (m_blendadd)
		{
			if (g_render->fog)
			{
				pVector black(0);
				glFogfv(GL_FOG_COLOR,&black.x);
			}
			glBlendFunc(GL_ONE,GL_ONE);
			glColor3f(m_color.x*m_color.w,m_color.y*m_color.w,m_color.z*m_color.w);
		}
		else
		{
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glColor4fv(&m_color.x);
		}

		glDepthMask(GL_FALSE);

		// texture side
		if (m_tex_side!=-1)
		{
			// if necessary, do animation on texture coordinates
			m_si[0]=0.0f,m_sf[0]=1.0f;
			m_ti[0]=0.0f,m_tf[0]=1.0f;
			if(m_frame_rate[0]>0.0f)
			{
				m_num_frames[0]=0;
				if(m_tex_side!=-1 && m_frame_size_x[0]>0 && m_frame_size_y[0]>0)
				{
					m_num_frames_x[0]=g_render->pic[m_tex_side]->sx/m_frame_size_x[0];
					m_num_frames_y[0]=g_render->pic[m_tex_side]->sy/m_frame_size_y[0];
					m_num_frames[0]=m_num_frames_x[0]*m_num_frames_y[0];
				}

				if(m_num_frames[0]>1)
				{
					int frame=(int)(m_frame_rate[0]*(g_romanager->m_time-m_start_time));
					
					m_sf[0]=m_frame_size_x[0]/(float)g_render->pic[m_tex_side]->sx;
					m_ti[0]=m_frame_size_y[0]/(float)g_render->pic[m_tex_side]->sy;

					int current_frame=frame%m_num_frames[0];

					m_si[0]=m_sf[0]*(current_frame%m_num_frames_x[0]);
					m_sf[0]+=m_si[0];

					m_tf[0]=1.0f-(m_ti[0]*(current_frame/m_num_frames_x[0]));
					m_ti[0]=m_tf[0]-m_ti[0];
				}
			}
			// draw
			g_render->sel_tex(m_tex_side);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			pVector displace_x=-fabsf(half_x-half)*m_transform.get_column3(0);
			glPushMatrix();
				glTranslatef(displace_x.x,displace_x.y,displace_x.z);
				glMultMatrixf(m_transform.mf);
				//*glBegin(GL_QUADS);
					glTexCoord2f(m_si[0],m_ti[0]); glVertex3f(-half_x,-half_y,0.0f);
					glTexCoord2f(m_sf[0],m_ti[0]); glVertex3f( half_x,-half_y,0.0f);
					glTexCoord2f(m_sf[0],m_tf[0]); glVertex3f( half_x, half_y,0.0f);
					glTexCoord2f(m_si[0],m_tf[0]); glVertex3f(-half_x, half_y,0.0f);
				//*glEnd();
			glPopMatrix();	
		}

		// texture front
		if (m_tex_front!=-1)
		{
			// if necessary, do animation on texture coordinates
			m_si[1]=0.0f,m_sf[1]=1.0f;
			m_ti[1]=0.0f,m_tf[1]=1.0f;
			if(m_frame_rate[1]>0.0f)
			{
				m_num_frames[1]=0;
				if(m_tex_front!=-1 && m_frame_size_x[1]>0 && m_frame_size_y[1]>0)
				{
					m_num_frames_x[1]=g_render->pic[m_tex_front]->sx/m_frame_size_x[1];
					m_num_frames_y[1]=g_render->pic[m_tex_front]->sy/m_frame_size_y[1];
					m_num_frames[1]=m_num_frames_x[1]*m_num_frames_y[1];
				}

				if(m_num_frames[1]>1)
				{
					int frame=(int)(m_frame_rate[1]*(g_romanager->m_time-m_start_time));
					
					m_sf[1]=m_frame_size_x[1]/(float)g_render->pic[m_tex_front]->sx;
					m_ti[1]=m_frame_size_y[1]/(float)g_render->pic[m_tex_front]->sy;

					int current_frame=frame%m_num_frames[1];

					m_si[1]=m_sf[1]*(current_frame%m_num_frames_x[1]);
					m_sf[1]+=m_si[1];

					m_tf[1]=1.0f-(m_ti[1]*(current_frame/m_num_frames_x[1]));
					m_ti[1]=m_tf[1]-m_ti[1];
				}
			}
			// draw
			g_render->sel_tex(m_tex_front);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTranslatef(m_transform.mf[12],m_transform.mf[13],m_transform.mf[14]);
			glMultMatrixf(&g_render->camera.mat.mf[0]);
			//*glBegin(GL_QUADS);
				glTexCoord2f(m_si[1],m_ti[1]); glVertex3f(-half,-half,0.0f);
				glTexCoord2f(m_sf[1],m_ti[1]); glVertex3f( half,-half,0.0f);
				glTexCoord2f(m_sf[1],m_tf[1]); glVertex3f( half, half,0.0f);
				glTexCoord2f(m_si[1],m_tf[1]); glVertex3f(-half, half,0.0f);
			//*glEnd();
		}
	}
#endif
}

void pROProjectile::update_transform(const pVector& pos,const pVector& axis)
{
	// place billboard into world system coordinate
	m_transform.set_translate(pos);

	if(m_mesh)
	{
		pVector v(axis); v.normalize();
		m_transform.align_z(v);
	}
	else
	{
		// align billboard with camera
		pVector x(axis); x.normalize();
		pVector z(g_render->camera.Z);
		pVector y;
		y.cross(z,x);
		y.normalize();
		z.cross(x,y);
		z.normalize();
		m_transform.set_column3(0,x);
		m_transform.set_column3(1,y);
		m_transform.set_column3(2,z);
	}
}

int pROProjectile::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='b';
			pd->data=&m_blendadd;
			pd->name="blendadd";
			pd->comment="Additive blend flag";
		break;

		case 1:
			pd->type='f';
			pd->data=&m_size_front;
			pd->name="sizefront";
			pd->comment="Size of support quad of front texture";
		break;

		case 2:
			pd->type='f';
			pd->data=&m_size_side_x;
			pd->name="sizesidex";
			pd->comment="Width of support quad of side texture";
		break;

		case 3:
			pd->type='f';
			pd->data=&m_size_side_y;
			pd->name="sizesidey";
			pd->comment="Height of support quad of side texture";
		break;

		case 4:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Blend color";
		break;

		case 5:
			pd->type='p';
			pd->data=&m_tex_front;
			pd->name="texfront";
			pd->comment="Projectile's front texture file";
		break;

		case 6:
			pd->type='p';
			pd->data=&m_tex_side;
			pd->name="texside";
			pd->comment="Projectile's side texture file";
		break;

		case 7:
			pd->type='m';
			pd->data=&m_mesh;
			pd->name="mesh";
			pd->comment="Mesh's .P3D file";
		break;

		case 8:
			pd->type='b';
			pd->data=&m_glow;
			pd->name="glow";
			pd->comment="Turn on/off glow for this object";
		break;

		case 9:
			pd->type='f';
			pd->data=&m_frame_rate[1];
			pd->name="frame_rate_front";
			pd->comment="Frame rate to display animation maps";
		break;

		case 10:
			pd->type='i';
			pd->data=&m_frame_size_x[1];
			pd->name="frame_size_x_front";
			pd->comment="Frame size in the x direction";
			break;

		case 11:
			pd->type='i';
			pd->data=&m_frame_size_y[1];
			pd->name="frame_size_y_front";
			pd->comment="Frame size in the y direction";
			break;

		case 12:
			pd->type='f';
			pd->data=&m_frame_rate[0];
			pd->name="frame_rate_side";
			pd->comment="Frame rate to display animation maps";
		break;

		case 13:
			pd->type='i';
			pd->data=&m_frame_size_x[0];
			pd->name="frame_size_x_side";
			pd->comment="Frame size in the x direction";
			break;

		case 14:
			pd->type='i';
			pd->data=&m_frame_size_y[0];
			pd->name="frame_size_y_side";
			pd->comment="Frame size in the y direction";
			break;
	}

	return 15;
}

void pROProjectile::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 1:
		case 2:
		case 3:
			update_bounding_box();
		break;

		case 5:
		{
			m_num_frames[1]=0;
			if(m_tex_front!=-1 && m_frame_size_x[1]>0 && m_frame_size_y[1]>0)
			{
				m_num_frames_x[1]=g_render->pic[m_tex_front]->sx/m_frame_size_x[1];
				m_num_frames_y[1]=g_render->pic[m_tex_front]->sy/m_frame_size_y[1];
				m_num_frames[1]=m_num_frames_x[1]*m_num_frames_y[1];
			}
		}
		break;

		case 6:
		{
			m_num_frames[0]=0;
			if(m_tex_side!=-1 && m_frame_size_x[0]>0 && m_frame_size_y[0]>0)
			{
				m_num_frames_x[0]=g_render->pic[m_tex_side]->sx/m_frame_size_x[0];
				m_num_frames_y[0]=g_render->pic[m_tex_side]->sy/m_frame_size_y[0];
				m_num_frames[0]=m_num_frames_x[0]*m_num_frames_y[0];
			}
		}
		break;

		case 7:
			if(m_mesh)
				m_flags|=P_ROFLAGS_HASMESH;
			else
				m_flags&=~P_ROFLAGS_HASMESH;
			update_bounding_box();
		break;
	}
}

#endif
