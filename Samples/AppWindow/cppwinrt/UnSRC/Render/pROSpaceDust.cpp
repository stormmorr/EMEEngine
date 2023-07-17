#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROSpaceDust::init(bool active)
{
	if (active)
	{
		m_points.clear();
		m_points.reserve(m_count);
		pVector p;
		for( int i=0;i<m_count;i++) 
		{
			p.vec(FABSRAND*m_size,FABSRAND*m_size,FABSRAND*m_size);
			m_points.add(p);
		}
		m_lastcampos=g_render->camera.pos;

		m_initflag=0;
	}
}

void pROSpaceDust::step(const float elapsed_time,const pMatrix& global)
{
	m_bbox.max.vec(m_size);
	m_bbox.min.vec(-m_size);
	m_transform.load_identity();
	m_transform.set_translate(g_render->camera.pos);
	pRenderObject::step(elapsed_time,m_transform);
}

void pROSpaceDust::draw()
{
	if(m_initflag)
		g_romanager->post_draw(this);
	else
	{
		m_initflag=1;
		m_lastcampos=g_render->camera.pos;
	}
}

void pROSpaceDust::post_draw()
{
#ifndef P_DISABLE_3D	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	pVector p=g_render->camera.pos;
	pVector d((float)fmod(p.x,m_size),(float)fmod(p.y,m_size),(float)fmod(p.z,m_size));
	if (d.x<0) d.x+=m_size;
	if (d.y<0) d.y+=m_size;
	if (d.z<0) d.z+=m_size;

	float size2=m_size*0.5f;
	float size3=m_size+size2;
	float size4=size2*size2;

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	g_render->sel_tex(-1);

	if (m_line)
	{
		pVector s=(p-m_lastcampos)*m_line_scale;
		if (s.length2()>0.01)
		{
			m_lastcampos=g_render->camera.pos;
			glLineWidth(m_linewidth);
			//*glBegin(GL_LINES);
			for( int i=0;i<m_count;i++ )
			{
				p.x=fmodf(m_points.buf[i].x-d.x+size3,m_size)-size2;
				p.y=fmodf(m_points.buf[i].y-d.y+size3,m_size)-size2;
				p.z=fmodf(m_points.buf[i].z-d.z+size3,m_size)-size2;

				glColor4f(m_color.x,m_color.y,m_color.z,m_color.w*(1.0f-VECDOT(p,p)/size4));
				//*glVertex3fv(&p.x);
				
				p+=s;
				glColor4f(m_color.x,m_color.y,m_color.z,0);
				//*glVertex3fv(&p.x);
			}
			//*glEnd();
		}
	}
	glPointSize(m_pointsize);
	//*glBegin(GL_POINTS);
	for( int i=0;i<m_count;i++ )
	{
		p.x=fmodf(m_points.buf[i].x-d.x+size3,m_size)-size2;
		p.y=fmodf(m_points.buf[i].y-d.y+size3,m_size)-size2;
		p.z=fmodf(m_points.buf[i].z-d.z+size3,m_size)-size2;
		glColor4f(m_color.x,m_color.y,m_color.z,m_color.w*(1.0f-VECDOT(p,p)/size4));
		//*glVertex3fv(&p.x);
	}
	//*glEnd();
	glPointSize(1.0);
#endif
}

void pROSpaceDust::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		case 1:
			init(m_source!=0);
		break;
		case 6:
			m_lastcampos=g_render->camera.pos;
			break;
	}
}	

int pROSpaceDust::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='i';
			pd->data=&m_count;
			pd->name="count";
			pd->comment="Number of space dust particles in volume";
			break;
		case 1:
			pd->type='f';
			pd->data=&m_size;
			pd->name="size";
			pd->comment="Size of the space dust volume to be tiled";
			break;
		case 2:
			pd->type='f';
			pd->data=&m_pointsize;
			pd->name="pixelsize";
			pd->comment="Pixel size for space dust particles (in screen space pixels)";
			break;
		case 3:
			pd->type='f';
			pd->data=&m_linewidth;
			pd->name="linewidth";
			pd->comment="Line width for space dust particles (in screen space pixels)";
			break;
		case 4:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Particle's main color";
			break;
		case 5:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Particle's main transparency (0:fully transparend, 1:fully opaque)";
			break;
		case 6:
			pd->type='b';
			pd->data=&m_line;
			pd->name="line";
			pd->comment="Line mode flag draws a line from current particle position to last frame particle position";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_line_scale;
			pd->name="line_scale";
			pd->comment="Line scale factor";
			break;
	}

	return 8;
}

void pROSpaceDust::translate_world(const pVector& t)
{
	m_lastcampos+=t;

	for( int i=0;i<m_points.num;i++ )
	{
		m_points.buf[i].x=fmodf(m_points.buf[i].x+t.x,m_size);
		m_points.buf[i].y=fmodf(m_points.buf[i].y+t.y,m_size);
		m_points.buf[i].z=fmodf(m_points.buf[i].z+t.z,m_size);
	}

	pRenderObject::translate_world(t);
}

#endif
