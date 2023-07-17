#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROBillboard::init(bool active)
{
	m_start_time=g_romanager->m_time;
}

void pROBillboard::step(const float elapsed_time,const pMatrix& global)
{
	// if necessary, do animation on texture coordinates
	m_si=0.0f,m_sf=1.0f;
	if(m_frame_rate>0.0f)
	{
		if(m_texture!=-1)
			if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
				m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
			else
				m_num_frames=1;
		else
			m_num_frames=0;

		if(m_num_frames>1)
		{
			int frame=(int)(m_frame_rate*(g_romanager->m_time-m_start_time));
			if(!m_loop && frame>=m_num_frames)
			{
				m_sf=1.0f/m_num_frames;
				m_si=m_sf*(m_num_frames-1);
				m_sf+=m_si;
				m_deactivate=true;
			}
			else
			{
				m_sf=1.0f/m_num_frames;
				m_si=m_sf*(frame%m_num_frames);
				m_sf+=m_si;
			}
		}
	}

	if (m_deactivate)
		g_romanager->post_deactivate(m_id);

	float size_z=(m_cursize_x>m_cursize_y)?m_cursize_x:m_cursize_y;
	m_bbox.max.vec( size_z);
	m_bbox.min.vec(-size_z);

	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROBillboard::draw()
{
#ifndef P_DISABLE_3D
	// store billboard's color for manipulation
	pVector color(m_color);

	float elapsed_time=g_romanager->m_time-m_start_time;

	// change size with periodic function
	if(m_size_func.m_type!=P_PERIODICFUNC_NONE)
	{
		float func_eval=m_size_func.eval(elapsed_time);
		m_cursize_x=m_size_x*func_eval;
		m_cursize_y=m_size_y*func_eval;
		if(m_loop==0 && elapsed_time>(1.0f/m_size_func.m_args[3])) // m_size_func.m_args[3]: rate parameter
			m_deactivate=1;
	}
	else
	{
		m_cursize_x=m_size_x;
		m_cursize_y=m_size_y;
	}

	// change color with periodic function
	if(m_color_func.m_type!=P_PERIODICFUNC_NONE)
	{
		float func_eval=m_color_func.eval(elapsed_time);
		color=(1.0f-func_eval)*m_color+func_eval*m_colorf;
	}

	// change transparency with periodic function
	if(m_transp_func.m_type!=P_PERIODICFUNC_NONE)
		color.w*=m_transp_func.eval(elapsed_time);

	// aplly transformation accordingly to allignment type
	switch(m_alignment)
	{
		case AXIS_ALIGNED:
		{
			// place billboard into world system coordinate
			pVector pos=m_transform_global.get_translate();
			glTranslatef(pos[0],pos[1],pos[2]);

			// align billboard with camera considering global z-axis as fixed axis
			pVector x(m_transform_global.get_column3(2)); x.normalize();
			pVector z(g_render->camera.Z);
			pVector y;
			y.cross(z,x);
			y.normalize();
			z.cross(x,y);
			z.normalize();
			pMatrix rot;
			rot.set_column3(0,x);
			rot.set_column3(1,y);
			rot.set_column3(2,z);
			glMultMatrixf(rot.mf);
		}
		break;

		case VIEW_ALIGNED:
		{
			// place billboard into world system coordinate
			pVector pos=m_transform_global.get_translate();
			glTranslatef(pos[0],pos[1],pos[2]);

			// align billboard with camera
			glMultMatrixf(&g_render->camera.mat.mf[0]);
		}
		break;

		case NONE_ALIGNED:
		{
			// no alignment: a common quadrilateral
			glMultMatrixf(&m_transform_global.mf[0]);
		}
		break;
	}

	// draw billboard
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	// do blending
	if(m_blendadd)
	{
		if (g_render->fog)
		{
			pVector black(0);
			glFogfv(GL_FOG_COLOR,&black.x);
		}
		glBlendFunc(GL_ONE,GL_ONE);
		glColor3f(color.x*color.w,color.y*color.w,color.z*color.w);
	}
	else
	{
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4fv(&color.x);
	}
	// consider alpha test
	if(m_alphatest && m_texture!=-1 && g_render->pic[m_texture] && g_render->pic[m_texture]->bytespixel==4)
	{
		glDepthMask(GL_TRUE);
		glEnable(GL_ALPHA_TEST);
	}
	// set current texture
	g_render->sel_tex(m_texture);
	// draw quad
	//*glBegin(GL_QUADS);
		glTexCoord2f(m_si,0.0f); glVertex3f(-m_cursize_x,-m_cursize_y,0.0f);
		glTexCoord2f(m_sf,0.0f); glVertex3f( m_cursize_x,-m_cursize_y,0.0f);
		glTexCoord2f(m_sf,1.0f); glVertex3f( m_cursize_x, m_cursize_y,0.0f);
		glTexCoord2f(m_si,1.0f); glVertex3f(-m_cursize_x, m_cursize_y,0.0f);
	//*glEnd();
#endif
}

void pROBillboard::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 6:
		{
			if (m_texture!=-1)
				if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
					m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
				else
					m_num_frames=1;
			else
				m_num_frames=0;
		}
		break;
	}
}

int pROBillboard::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='b';
			pd->data=&m_alphatest;
			pd->name="alphatest";
			pd->comment="";
		break;

		case 2:
			pd->type='i';
			pd->data=&m_alignment;
			pd->name="alignment";
			pd->comment="Billboard alignment|None|Axis-Aligned|View-Aligned";
		break;

		case 3:
			pd->type='f';
			pd->data=&m_size_x;
			pd->name="sizex";
			pd->comment="Billboard's width";
		break;

		case 4:
			pd->type='f';
			pd->data=&m_size_y;
			pd->name="sizey";
			pd->comment="Billboard's height";
		break;

		case 5:
			pd->type='e';
			pd->data=&m_size_func;
			pd->name="size_function";
			pd->comment="Function to animate dimensions (width and height) of billboard";
		break;

		case 6:
			pd->type='p';
			pd->data=&m_texture;
			pd->name="texture";
			pd->comment="Billboard's texture file";
		break;

		case 7:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Billboard's initial color";
		break;

		case 8:
			pd->type='c';
			pd->data=&m_colorf;
			pd->name="colorf";
			pd->comment="Billboard's final color";
		break;

		case 9:
			pd->type='e';
			pd->data=&m_color_func;
			pd->name="color_function";
			pd->comment="Function to combine initial and final colors";
		break;
		
		case 10:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Billboard's transparency";
		break;

		case 11:
			pd->type='e';
			pd->data=&m_transp_func;
			pd->name="transp_function";
			pd->comment="Function to animate transparency of billboard";
		break;

		case 12:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate to display animation maps";
		break;

		case 13:
			pd->type='b';
			pd->data=&m_loop;
			pd->name="loop";
			pd->comment="Loop flag (die after last frame if not on loop)";
		break;
	}

	return 14;
}

#endif
