#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIProgressBar::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	float w,h,u,v,a=m_color.w;

	// change tex color with periodic function
	if(m_tex_func.m_type!=P_PERIODICFUNC_NONE)
		a*=m_tex_func.eval(g_gomanager->m_time);

	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	if(m_orientation==1) // horizontal
	{
		u=get_percent();//m_percent;
		v=0.0f;
		w=(float)m_width*get_percent();//m_percent;
		h=(float)m_height;
	}
	else // vertical
	{
		u=0.0f;
		v=get_percent();//m_percent;
		w=0.0f;
		h=float(m_height)-float(m_height)*get_percent();//m_percent;
	}

	// background part
	if(m_tex_bg!=-1)
	{
		glColor4fv(&m_color.x);
		g_render->sel_tex(m_tex_bg);
		//*glBegin(GL_QUADS);
			glTexCoord2f(u,1.0f);    glVertex2f(w,0.0f);
			glTexCoord2f(u,v);       glVertex2f(w,h);
			glTexCoord2f(1.0f,v);    glVertex2f((float)m_width,h);
			glTexCoord2f(1.0f,1.0f); glVertex2i(m_width,0);
		//*glEnd();
	}

	if(m_orientation==1) // horizontal
	{
		v=1.0f;
		h=0.0f;
	}
	else // vertical
	{
		u=1.0f;
		w=(float)m_width;
	}

	// background part
	if(m_tex_bg!=-1)
	{
		glColor4fv(&m_color.x);
		g_render->sel_tex(m_tex_bg);
		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,v);    glVertex2f(0.0f,h);
			glTexCoord2f(0.0f,0.0f); glVertex2i(0,m_height);
			glTexCoord2f(u,0.0f);    glVertex2f(w,(float)m_height);
			glTexCoord2f(u,v);       glVertex2f(w,h);
		//*glEnd();
	}

	// filled part
	glColor4f(m_color.x,m_color.y,m_color.z,a);
	g_render->sel_tex(m_tex_fill);
	//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,v);    glVertex2f(0.0f,h);
		glTexCoord2f(0.0f,0.0f); glVertex2i(0,m_height);
		glTexCoord2f(u,0.0f);    glVertex2f(w,(float)m_height);
		glTexCoord2f(u,v);       glVertex2f(w,h);
	//*glEnd();

	glPopMatrix();

	pGUIObject::draw(scissor_rect);
#endif
}

int pGUIProgressBar::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Background color";
			break;
		case 1:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Object transparency (0.0: fully transparent, 1.0: fully opaque)";
			break;
		case 2:
			pd->type='i';
			pd->data=&m_orientation;
			pd->name="orientation";
			pd->comment="The progress bar orientation|Vertical|Horizontal";
			break;
		case 3:
			pd->type='p';
			pd->data=&m_tex_bg;
			pd->name="tex_bg";
			pd->comment="Texture for the background part of the progress bar";
			break;
		case 4:
			pd->type='p';
			pd->data=&m_tex_fill;
			pd->name="tex_fill";
			pd->comment="Texture for the filled part of the progress bar";
			break;
		case 5:
			pd->type='f';
			pd->data=&m_percent;
			pd->name="percent";
			pd->comment="Represents the filled part of the progress bar (0 to 1 range)";
			break;
		case 6:
			pd->type='e';
			pd->data=&m_tex_func;
			pd->name="tex_function";
			pd->comment="Function to combine fill texture and background texture";
			break;
		case 7:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 9:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 10:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 11:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 12:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 13:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 14:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 15:
			pd->type='f';
			pd->data=&m_min_range;
			pd->name="min_range";
			pd->comment="Minimum range";
			break;
		case 16:
			pd->type='f';
			pd->data=&m_max_range;
			pd->name="max_range";
			pd->comment="Maximum range";
			break;
		case 17:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}
	return 18;
}

void pGUIProgressBar::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 5:
			if(m_percent>1.0f)
				m_percent=1.0f;
			if(m_percent<0.0f)
				m_percent=0.0f;
		break;
	}
}

float pGUIProgressBar::get_percent() const
{
	return (m_max_range-m_min_range)*m_percent+m_min_range;
}

#endif
