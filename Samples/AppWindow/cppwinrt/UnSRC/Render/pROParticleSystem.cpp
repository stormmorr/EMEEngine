#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROParticleSystem::init(bool active)
{
	if (m_total!=0) 
		m_part.resize(m_total);
}

void pColorParticle::step(const float elapsed_time)
{	
	m_pos+=elapsed_time*m_vel;
	m_life-=elapsed_time;
	m_time+=elapsed_time;
}

void pROParticleSystem::step(const float elapsed_time,const pMatrix& global)
{
	pMatrix m=m_transform*global;
	pVector pos=m.get_translate(),
			X=m.get_column3(0),
			Y=m.get_column3(1),
			Z=m.get_column3(2);

	if (m_models.num>0)
		m_flags|=P_ROFLAGS_HASMESH;
	else
		m_flags&=~P_ROFLAGS_HASMESH;

	// updates particles and its bounding box
	pBoundBox bb;
	bb.reset();
	bb.add_point(pos+m_radius);
	bb.add_point(pos-m_radius);
	int i;
	for(i=0;i<m_part.length();i++ )
	{
		m_part[i].step(elapsed_time);
		if (m_part[i].m_life<0)
			m_part.remove_begin();
		else 
		{
			// change color with periodic function
			if (m_func.m_type!=P_PERIODICFUNC_NONE)
			{
				float t=m_func.eval(m_part[i].m_life);
				m_part[i].m_color=(1.0f-t)*m_color+t*m_colorf;
			}
			if (m_blendadd)
				m_part[i].m_color*=m_color.w;
			else
				m_part[i].m_color.w=m_color.w;
			if (m_part[i].m_life<m_fade)
				if (m_blendadd)
					m_part[i].m_color*=m_part[i].m_life/m_fade;
				else
					m_part[i].m_color.w*=m_part[i].m_life/m_fade;

			if ((i&7)==0)
				bb.add_point(m_part[i].m_pos);
		}
	}

	// verifies if this particle is enabled
	if (m_enabled==0)
		return;

	m_totdt+=elapsed_time;
	int j;

	if(m_emission>0.0f) // particles are emitted during emission time
	{
		if(m_totdt<=m_emission)
		{
			j=(int)(m_totdt*m_total/m_emission);
			// if first time, it assures that the number of particles to be created is not zero
			if((j==0)&&(m_part.length()==0))
				j=1;
		}
		else
			j=0;
	}
	else // particles are emitted in loop
		j=(int)(m_totdt*m_total/m_life);

	// creates j particles
	if (j>0)
	{
		int rotflag=m_rot;
		if (m_velalign)
			rotflag=3;
		else
		if (m_rotvel.length2()+m_rotvelvar.length2()>0)
			rotflag=2;
		
		if(m_emission==0) 
			m_totdt=0;

		for( i=0;i<j;i++ )
		{
			if (m_part.is_full())
				break;

			pColorParticle new_p;

			new_p.m_pos=pos;
			new_p.m_life=m_life;
			new_p.m_size=m_radius+m_radiusvar*FRAND;
			new_p.m_color=m_color+m_colorvar*pVector(FRAND,FRAND,FRAND);
			if (m_blendadd)
				new_p.m_color*=m_color.w;
			else
				new_p.m_color.w=m_color.w;
			pVector v;
			if (m_ax==0 && m_ay==0) 
				v.vec(FRAND,FRAND,FRAND);
			else 
				v.vec(FRAND*m_ax,FRAND*m_ay,1);
			v=v.x*X+v.y*Y+v.z*Z;
			v.normalize();
			new_p.m_vel=v*(m_speed+m_speedvar*FRAND);
			new_p.m_rotflag=rotflag;
			if (rotflag>0)
				new_p.m_rotconst.vec(360*FABSRAND,360*FABSRAND,360*FABSRAND);
			if (rotflag==2)
				new_p.m_rotlin=m_rotvel+m_rotvelvar*pVector(FRAND,FRAND,FRAND);
			if (m_models.num)
				new_p.m_mesh=m_models.buf[rand()%m_models.num];

			m_part.add(new_p);
		}
	}

	pMatrix m2;
	m.get_affine_inverse(m2);
	m_bbox.reset();
	m_bbox.add_bbox(bb,m2);
	pRenderObject::step(elapsed_time,m);

	if(m_emission>0 && m_part.length()==0)
		g_romanager->post_deactivate(m_id);
}

void pColorParticle::draw(float s,float t)
{
#ifndef P_DISABLE_3D
	if (m_mesh)
	{
		glPushMatrix();
		    glTranslatef(m_pos.x, m_pos.y, m_pos.z);
			
			if (m_rotflag==1)
			{
				glRotatef(m_rotconst.x,1,0,0);
				glRotatef(m_rotconst.y,0,1,0);
				glRotatef(m_rotconst.z,0,0,1);
			}
			else
			if (m_rotflag==2)
			{
				glRotatef(m_rotconst.x+m_rotlin.x*m_time,1,0,0);
				glRotatef(m_rotconst.y+m_rotlin.y*m_time,0,1,0);
				glRotatef(m_rotconst.z+m_rotlin.z*m_time,0,0,1);
			}

			m_mesh->draw(g_render->renderflag,g_render->rendermode);
		glPopMatrix();
	}
	else
	{
		glColor4fv(&m_color.x);

		glPushMatrix();
			glTranslatef(m_pos.x, m_pos.y, m_pos.z);
			
			if (m_rotflag==1)
			{
				glRotatef(m_rotconst.x,1,0,0);
				glRotatef(m_rotconst.y,0,1,0);
				glRotatef(m_rotconst.z,0,0,1);
			}
			else
			if (m_rotflag==2)
			{
				glRotatef(m_rotconst.x+m_rotlin.x*m_time,1,0,0);
				glRotatef(m_rotconst.y+m_rotlin.y*m_time,0,1,0);
				glRotatef(m_rotconst.z+m_rotlin.z*m_time,0,0,1);
			}

			//*glBegin(GL_QUADS);
				glTexCoord2f(s,0.0f); glVertex3f(-m_size,-m_size,0.0f);
				glTexCoord2f(t,0.0f); glVertex3f( m_size,-m_size,0.0f);
				glTexCoord2f(t,1.0f); glVertex3f( m_size, m_size,0.0f);
				glTexCoord2f(s,1.0f); glVertex3f(-m_size, m_size,0.0f);
			//*glEnd();
		glPopMatrix();
	}
#endif
}

void pColorParticle::draw_viewalign(float s,float t)
{
#ifndef P_DISABLE_3D
	if (m_mesh)
	{
		glPushMatrix();
		    glTranslatef(m_pos.x, m_pos.y, m_pos.z);

			glMultMatrixf(&g_render->camera.mat.mf[0]);
			
			if (m_rotflag==1)
				glRotatef(m_rotconst.z,0,0,1);
			else
			if (m_rotflag==2)
				glRotatef(m_rotconst.z+m_rotlin.z*m_time,0,0,1);

			m_mesh->draw(g_render->renderflag,g_render->rendermode);
		glPopMatrix();
	}
	else
	{
		glColor4fv(&m_color.x);

		glPushMatrix();
			glTranslatef(m_pos.x, m_pos.y, m_pos.z);
			
			glMultMatrixf(&g_render->camera.mat.mf[0]);
			if (m_rotflag==1)
				glRotatef(m_rotconst.z,0,0,1);
			else
			if (m_rotflag==2)
				glRotatef(m_rotlin.z+m_rotlin.z*m_time,0,0,1);

			//*glBegin(GL_QUADS);
				glTexCoord2f(s,0.0f); glVertex3f(-m_size,-m_size,0.0f);
				glTexCoord2f(t,0.0f); glVertex3f( m_size,-m_size,0.0f);
				glTexCoord2f(t,1.0f); glVertex3f( m_size, m_size,0.0f);
				glTexCoord2f(s,1.0f); glVertex3f(-m_size, m_size,0.0f);
			//*glEnd();
		glPopMatrix();
	}
#endif
}

void pColorParticle::update_transform(const pVector& pos,const pVector& axis,pMatrix& m_transform,int m_viewalign)
{
	// place billboard into world system coordinate
	m_transform.set_translate(pos);

	// align billboard with camera
	pVector x,y,z;
	if (m_viewalign)
	{
		x=g_render->camera.X*VECDOT(axis,g_render->camera.X)+
			g_render->camera.Y*VECDOT(axis,g_render->camera.Y);
		x.normalize();
		z=g_render->camera.Z;
		y.cross(z,x);
	}
	else 
	{
		x=axis;
		x.normalize();
		z=g_render->camera.Z;
		y.cross(z,x);
		z.cross(x,y);
	}

	m_transform.set_column3(0,x);
	m_transform.set_column3(1,y);
	m_transform.set_column3(2,z);
}

void pColorParticle::draw_velalign(float s,float t,int m_viewalign)
{
#ifndef P_DISABLE_3D
	pMatrix transform;
	update_transform(m_pos,m_vel,transform,m_viewalign);
	glPushMatrix();
		glMultMatrixf(&transform.mf[0]);
		if (m_mesh)
			m_mesh->draw(g_render->renderflag,g_render->rendermode);
		else
		{
			glColor4fv(&m_color.x);

			//*glBegin(GL_QUADS);
				glTexCoord2f(s,0.0f); glVertex3f(-m_size,-m_size,0.0f);
				glTexCoord2f(t,0.0f); glVertex3f( m_size,-m_size,0.0f);
				glTexCoord2f(t,1.0f); glVertex3f( m_size, m_size,0.0f);
				glTexCoord2f(s,1.0f); glVertex3f(-m_size, m_size,0.0f);
			//*glEnd();
		}
	glPopMatrix();
#endif
}

void pROParticleSystem::draw()
{	
#ifndef P_DISABLE_3D
	if(m_pointsprite && GLEW_ARB_point_sprite)
	{
		g_render->sel_tex(m_texture);

		if (m_blendadd)
		{
			if (g_render->fog)
			{
				pVector black(0);
				glFogfv(GL_FOG_COLOR,&black.x);
			}
			glBlendFunc(GL_ONE,GL_ONE);
		}
		else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);

		glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB,GL_TRUE);
		glEnable(GL_POINT_SPRITE_ARB);
		glPointSize(m_radius);
		//*glBegin(GL_POINTS);
			for( int i=0;i<m_part.length();i++ )
			{
				glColor4fv(&(m_part[i].m_color.x));
				//*glVertex3fv(&(m_part[i].m_pos.x));
			}
		//*glEnd();
		glPointSize(1.0f);
		glDisable(GL_POINT_SPRITE_ARB);
	}
	else
	{
		if (m_models.num==0)
		{
			g_render->sel_tex(m_texture);

			if (m_blendadd)
			{
				if (g_render->fog)
				{
					pVector black(0);
					glFogfv(GL_FOG_COLOR,&black.x);
				}
				glBlendFunc(GL_ONE,GL_ONE);
			}
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);
		}

		if (m_velalign)
		{
			if (m_frame_rate > 0.0f)
			{
				if (m_texture!=-1)
					if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
						m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
					else
						m_num_frames=1;
				else
					m_num_frames=0;
				if (m_num_frames > 1)
				{
					float f,nf=1.0f/m_num_frames;
					int frame;
					for( int i=0;i<m_part.length();i++ )
					{
						frame=(int)(m_frame_rate*m_part[i].m_time);
						if (m_loop==0 && frame>=m_num_frames)
							frame=m_num_frames-1;
						else
							frame=frame%m_num_frames;

						f=nf*frame;
						m_part[i].draw_velalign(f,f+nf,m_viewalign);
					}
				}
			}
			else
				for( int i=0;i<m_part.length();i++ )
					m_part[i].draw_velalign(0,1,m_viewalign);
		}
		else
		if (m_viewalign)
		{
			if (m_frame_rate > 0.0f && m_num_frames > 1)
			{
				float f,nf=1.0f/m_num_frames;
				int frame;
				for( int i=0;i<m_part.length();i++ )
				{
					frame=(int)(m_frame_rate*m_part[i].m_time);
					if (m_loop==0 && frame>=m_num_frames)
						frame=m_num_frames-1;
					else
						frame=frame%m_num_frames;

					f=nf*frame;
					m_part[i].draw_viewalign(f,f+nf);
				}
			}
			else
				for( int i=0;i<m_part.length();i++ )
					m_part[i].draw_viewalign(0,1);
		}
		else
		{
			if (m_frame_rate > 0.0f && m_num_frames > 1)
			{
				float f,nf=1.0f/m_num_frames;
				int frame;
				for( int i=0;i<m_part.length();i++ )
				{
					frame=(int)(m_frame_rate*m_part[i].m_time);
					if (m_loop==0 && frame>=m_num_frames)
						frame=m_num_frames-1;
					else
						frame=frame%m_num_frames;

					f=nf*frame;
					m_part[i].draw(f,f+nf);
				}
			}
			else
				for( int i=0;i<m_part.length();i++ )
					m_part[i].draw(0,1);
		}
	}
#endif
}

int pROParticleSystem::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='b';
			pd->data=&m_blendadd;
			pd->name="blendadd";
			pd->comment="Additive blend flag";
			break;
		case 1:
			pd->type='b';
			pd->data=&m_viewalign;
			pd->name="viewalign";
			pd->comment="Turn on/off viewalign flag";
			break;
		case 2:
			pd->type='b';
			pd->data=&m_pointsprite;
			pd->name="pointsprite";
			pd->comment="Use or not point sprite ARB extension";
			break;
		case 3:
			pd->type='p';
			pd->data=&m_texture;
			pd->name="texture";
			pd->comment="Texture file used to each particle";
			break;
		case 4:
			pd->type=-'m';
			pd->data=&m_models;
			pd->name="models";
			pd->comment="P3D mesh files used by particles (it has priority over billboardf particle)";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_total;
			pd->name="total";
			pd->comment="Total number of particles";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_life;
			pd->name="life";
			pd->comment="Life of each particle (in seconds)";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_fade;
			pd->name="fade";
			pd->comment="Duration of fade effect to each particle (in seconds)";
			break;
		case 8:
			pd->type='f';
			pd->data=&m_emission;
			pd->name="emission";
			pd->comment="Duration of emission process of particles (if it is equals to 0(zero), particles are continuously emitted)";
			break;
		case 9:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Particle's initial color";
			break;
		case 10:
			pd->type='c';
			pd->data=&m_colorf;
			pd->name="colorf";
			pd->comment="Particle's final color";
			break;
		case 11:
			pd->type='c';
			pd->data=&m_colorvar;
			pd->name="colorvar";
			pd->comment="Variation of emmited particles' color";
			break;
		case 12:
			pd->type='e';
			pd->data=&m_func;
			pd->name="function";
			pd->comment="Function to combine initial and final colors";
			break;
		case 13:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Particle's transparency";
			break;
		case 14:
			pd->type='f';
			pd->data=&m_radius;
			pd->name="radius";
			pd->comment="Particle's radius";
			break;
		case 15:
			pd->type='f';
			pd->data=&m_radiusvar;
			pd->name="radiusvar";
			pd->comment="Variation of emmited particles' radius";
			break;
		case 16:
			pd->type='f';
			pd->data=&m_speed;
			pd->name="speed";
			pd->comment="Particle's speed";
			break;
		case 17:
			pd->type='f';
			pd->data=&m_speedvar;
			pd->name="speedvar";
			pd->comment="Variation of emmited particles' speed";
			break;
		case 18:
			pd->type='b';
			pd->data=&m_rot;
			pd->name="rotation";
			pd->comment="Particle's rotation flag";
			break;
		case 19:
			pd->type='v';
			pd->data=&m_rotvel;
			pd->name="rotvel";
			pd->comment="Particle's rotation velocity in degrees/sec";
			break;
		case 20:
			pd->type='v';
			pd->data=&m_rotvelvar;
			pd->name="rotvelvar";
			pd->comment="Variation of particle's rotation velocity in degrees/sec";
			break;
		case 21:
			pd->type='b';
			pd->data=&m_velalign;
			pd->name="velalign";
			pd->comment="Aligns particle with velocity direction";
			break;
		case 22:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate to display animation maps";
			break;
		case 23:
			pd->type='b';
			pd->data=&m_loop;
			pd->name="loop";
			pd->comment="Loop option for animation maps";
			break;
		case 24:
			pd->type='f';
			pd->data=&m_ax;
			pd->name="ax";
			break;
		case 25:
			pd->type='f';
			pd->data=&m_ay;
			pd->name="ay";
			break;
	}
	return 26;
}

void pROParticleSystem::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 3:
			if (m_texture!=-1)
				if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
					m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
				else
					m_num_frames=1;
			else
				m_num_frames=0;
		break;

		case 5:
			if (m_total!=0) m_part.resize(m_total);
		break;

		case 6:
			m_part.clear();
		break;
	};
}

void pROParticleSystem::translate_world(const pVector& t)
{
	int i=0,j=m_part.length();
	for( ;i<j;i++ )
		m_part[i].m_pos+=t;
	pRenderObject::translate_world(t);
}

void pROParticleSystem::setup_light()
{
	if (m_models.num)
	{
		m_light.clear();

		for(int i=0;i<g_render->light.num;i++)
			if(g_render->light[i]->update_objects_light(this))
				m_light.add(g_render->light[i]);
	}

	pRenderObject::setup_light();
}


#endif
