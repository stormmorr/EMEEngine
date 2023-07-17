#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIImage::update_num_frames()
{
	if (m_tex!=-1)
	{
		if(g_render->pic[m_tex]->sx>g_render->pic[m_tex]->sy)
			m_num_frames=g_render->pic[m_tex]->sx/g_render->pic[m_tex]->sy;
		else 
			m_num_frames=1;
	}
	else
		m_num_frames=0;
}

void pGUIImage::init()
{
	//update_num_frames();
	m_start_time=g_gomanager->m_time;
}

void pGUIImage::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	if(m_frame_rate>0.0f)
		update_num_frames();
	// if necessary, do animation on texture coordinates
	float si=0.0f,sf=1.0f;
	if(m_command==CMD_PLAY && m_frame_rate>0.0f && m_num_frames>1)
	{
		int frame=(int)(m_frame_rate*(g_gomanager->m_time-m_start_time));
		sf=1.0f/m_num_frames;
		m_current_frame=frame%m_num_frames;
		si=sf*m_current_frame;
		sf+=si;
	}
	else if(m_command==CMD_PLAY_ONCE && m_frame_rate>0.0f && m_num_frames>1)
	{
		int frame=(int)(m_frame_rate*(g_gomanager->m_time-m_start_time));
		sf=1.0f/m_num_frames;
		if(frame>=m_num_frames)
		{
			m_current_frame=0;
			si=0.0f;
		}
		else
		{
			m_current_frame=frame%m_num_frames;
			si=sf*m_current_frame;
			sf+=si;
		}
	}
	else if(m_command==CMD_PAUSE && m_current_frame<m_num_frames && m_num_frames>1)
	{
		sf=1.0f/m_num_frames;
		si=sf*m_current_frame;
		sf+=si;
	}
	else if(m_command==CMD_STOP && m_frame_rate>0.0f && m_num_frames>1)
	{
		sf=1.0f/m_num_frames;
		si=sf*0;
		sf+=si;
	}

	// stretch and rotate in texture space
	float scale_x=1.0f,scale_y=1.0f;
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f,0.5f,0.0f);
	glRotatef(fmodf(m_rotation_vel*g_gomanager->m_time,360.0f),0.0f,0.0f,1.0f);
	if(m_horz_stretch_func.m_type!=P_PERIODICFUNC_NONE)
		scale_x=m_horz_stretch_func.eval(g_gomanager->m_time);
	if(m_vert_stretch_func.m_type!=P_PERIODICFUNC_NONE)
		scale_y=m_vert_stretch_func.eval(g_gomanager->m_time);
	glScalef(scale_x,scale_y,1.0f);
	glTranslatef(-0.5f,-0.5f,0.0f);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	g_render->sel_tex(m_tex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	if (m_addblend)
		glBlendFunc(GL_ONE, GL_ONE);
	else
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	pVector color=m_color;
	if (m_color_func.m_type!=P_PERIODICFUNC_NONE)
		color*=m_color_func.eval(g_render->curtimef);
	if (m_transp_func.m_type!=P_PERIODICFUNC_NONE)
		color.w*=m_transp_func.eval(g_render->curtimef);
	glColor4fv(&color.x);
	if(m_rescale_tex_flag)
	{
		//*glBegin(GL_QUADS);
			glTexCoord2f(si,1.0f);
			glVertex2i(0,0);
			glTexCoord2f(si,0.0f);
			glVertex2i(0,m_height);
			glTexCoord2f(sf,0.0f);
			glVertex2i(m_width,m_height);
			glTexCoord2f(sf,1.0f);
			glVertex2i(m_width,0);
		//*glEnd();
	}
	else if(m_tex!=-1)
	{
		float ss=(m_width/((float)g_render->pic[m_tex]->sx))*0.5f;
		float tt=(m_height/((float)g_render->pic[m_tex]->sy))*0.5f;
		float ssi=0.5f-ss;
		float ssf=0.5f+ss;
		float tti=0.5f-tt;
		float ttf=0.5f+tt;
		
		//*glBegin(GL_QUADS);
			glTexCoord2f(ssi,ttf);
			glVertex2i(0,0);
			glTexCoord2f(ssi,tti);
			glVertex2i(0,m_height);
			glTexCoord2f(ssf,tti);
			glVertex2i(m_width,m_height);
			glTexCoord2f(ssf,ttf);
			glVertex2i(m_width,0);
		//*glEnd();
	}

	glPopMatrix();

	// retores texture matrix
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pGUIObject::draw(scissor_rect);
#endif
}

int pGUIImage::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Object color, multiplied by the texture";
			break;
		case 1:
			pd->type='e';
			pd->data=&m_color_func;
			pd->name="color_func";
			pd->comment="Object color function";
			break;
		case 2:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Object transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 3:
			pd->type='e';
			pd->data=&m_transp_func;
			pd->name="transp_func";
			pd->comment="Object transp function";
			break;
		case 4:
			pd->type='b';
			pd->data=&m_addblend;
			pd->name="addblend";
			pd->comment="Additive blend flag";
			break;
		case 5:
			pd->type='p';
			pd->data=&m_tex;
			pd->name="tex";
			pd->comment="Texture for the image object";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate to display animation maps";
			break;
		case 7:
			pd->type='i';
			pd->data=&m_command;
			pd->name="command";
			pd->comment="Animation command|Play|Play Once|Pause|Stop";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_current_frame;
			pd->name="current_frame";
			pd->comment="Current frame in the animation. It can be edited only if";
			            " m_command equals to Stop";
			break;
		case 9:
			pd->type='f';
			pd->data=&m_rotation_vel;
			pd->name="rotation_vel";
			pd->comment="Rotation velocity in degrees peer second";
			break;
		case 10:
			pd->type='e';
			pd->data=&m_vert_stretch_func;
			pd->name="vert_stretch_func";
			pd->comment="Vertical stretch function";
			break;
		case 11:
			pd->type='e';
			pd->data=&m_horz_stretch_func;
			pd->name="horz_stretch_func";
			pd->comment="Horizontal stretch function";
			break;
		case 12:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 13:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 14:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 15:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when droppable equals to true";
			break;
		case 16:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when droppable equals to false";
			break;
		case 17:
			pd->type='b';
			pd->data=&m_rescale_tex_flag;
			pd->name="rescale_tex_flag";
			pd->comment="Rescale texture flag";
			break;
		case 18:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 19;
}

void pGUIImage::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 5:
		{
			update_num_frames();
		}
		break;

		case 7:
			if(m_command!=CMD_PAUSE)
				m_start_time=g_gomanager->m_time;
		break;
	}
}

#endif
