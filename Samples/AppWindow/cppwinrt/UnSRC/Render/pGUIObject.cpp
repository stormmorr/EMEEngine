#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

pGUIObject::pGUIObject(pGUIObject *parent) :
	m_type((unsigned int)-1),m_id(0),m_flags(P_GUIFLAGS_ENABLED_VISIBLE),m_clickable(1),m_focusable(0),m_modal(0),m_popup(0),
	m_draggable(0),m_droppable(0),m_pos_x(0),m_pos_y(0),m_width(100),m_height(100),m_hotspot_x(0),m_hotspot_y(0),
	m_content_height((unsigned int)-1),m_parent(parent),m_color(1.0f),m_font((unsigned int)-1),m_font_size(16),
	m_mouse_cursor((unsigned int)-1),m_mouse_cursor_can_drop((unsigned int)-1),m_mouse_cursor_cannot_drop((unsigned int)-1),
	m_tooltip_flag(0),m_tooltip_x(0),m_tooltip_y(0)
{}

pGUIObject::pGUIObject(const pGUIObject& in) :
	m_type(in.m_type),m_flags(in.m_flags),m_clickable(in.m_clickable),m_focusable(in.m_focusable),m_modal(in.m_modal),m_popup(in.m_popup),
	m_draggable(in.m_draggable),m_droppable(in.m_droppable),m_pos_x(in.m_pos_x),m_pos_y(in.m_pos_y),m_width(in.m_width),m_height(in.m_height),
	m_hotspot_x(in.m_hotspot_x),m_hotspot_y(in.m_hotspot_y),m_content_height(in.m_content_height),m_color(in.m_color),m_font(in.m_font),
	m_font_size(in.m_font_size),m_mouse_cursor(in.m_mouse_cursor),m_mouse_cursor_can_drop(in.m_mouse_cursor_can_drop),m_mouse_cursor_cannot_drop(in.m_mouse_cursor_cannot_drop),
	m_tooltip_flag(in.m_tooltip_flag),m_tooltip_x(in.m_tooltip_x),m_tooltip_y(in.m_tooltip_y)
{
	m_name=in.m_name;
	m_text=in.m_text;
	int i;
	m_child.reserve(in.m_child.num);
	for(i=0;i<in.m_child.num;i++ )
		m_child.add(in.m_child.buf[i]);
	m_id=0;
	m_parent=0;

	m_tooltip=in.m_tooltip;
}

pGUIObject::~pGUIObject()
{}

int pGUIObject::get_common_param_desc(int i,pParamDesc *pd)
{
	if (pd==0)
		return P_GUINUMDEFAULTPARAM+get_custom_param_desc(0,0);
	else
	{
		pd->comment="";
		if (i>=P_GUINUMDEFAULTPARAM)
			get_custom_param_desc(i-P_GUINUMDEFAULTPARAM,pd);
		switch(i)
		{
			case 0:
				pd->type=-'g';
				pd->data=&m_child;
				pd->name="child";
				pd->comment="GUI object children";
				break;
			case 1:
				pd->type='i';
				pd->data=&m_flags;
				pd->name="flags";
				pd->comment="GUI object flags|Enabled|Visible|Transparent";
				break;
			case 2:
				pd->type='b';
				pd->data=&m_clickable;
				pd->name="clickable";
				pd->comment="Clickable flag";
				break;
			case 3:
				pd->type='i';
				pd->data=&m_pos_x;
				pd->name="pos_x";
				pd->comment="GUI object x position in screen pixels (from left)";
				break;
			case 4:
				pd->type='i';
				pd->data=&m_pos_y;
				pd->name="pos_y";
				pd->comment="GUI object y position in screen pixels (from bottom)";
				break;
			case 5:
				pd->type='i';
				pd->data=&m_width;
				pd->name="width";
				pd->comment="GUI object width in screen pixels";
				break;
			case 6:
				pd->type='i';
				pd->data=&m_height;
				pd->name="height";
				pd->comment="GUI object height in screen pixels";
				break;
			case 7:
				pd->type='c';
				pd->data=&m_color;
				pd->name="color";
				pd->comment="GUI object general-purpose color";
				break;
			case 8:
				pd->type='f';
				pd->data=&m_color.w;
				pd->name="transp";
				pd->comment="GUI object transparency (0.0 = fully transparent, 1.0 = fully opaque)";
				break;
			case 9:
				pd->type='s';
				pd->data=&m_text;
				pd->name="text";
				pd->comment="GUI object general-purpose text";
				break;
			case 10:
				pd->type='n';
				pd->data=&m_font;
				pd->name="font";
				pd->comment="GUI object font file";
				break;
			case 11:
				pd->type='i';
				pd->data=&m_font_size;
				pd->name="font_size";
				pd->comment="GUI object font size";
				break;
			case 12:
				pd->type='p';
				pd->data=&m_mouse_cursor;
				pd->name="mouse_cursor";
				pd->comment="Mouse cursor for when mouse is over this object";
				break;
			case 13:
				pd->type='i';
				pd->data=&m_content_height;
				pd->name="content_height";
				pd->comment="Total content height, used for scrolling";
				break;
			case 14:
				pd->type='i';
				pd->data=&m_hotspot_x;
				pd->name="hotspot_x";
				pd->comment="Hotspot x position in screen coordinates";
				break;
			case 15:
				pd->type='i';
				pd->data=&m_hotspot_y;
				pd->name="hotspot_y";
				pd->comment="Hotspot y position in screen coordinates";
				break;
			case 16:
				pd->type='b';
				pd->data=&m_focusable;
				pd->name="focusable";
				pd->comment="Focusable flag";
				break;
			case 17:
				pd->type='b';
				pd->data=&m_popup;
				pd->name="popup";
				pd->comment="Pop-up flag";
				break;
			case 18:
				pd->type='b';
				pd->data=&m_draggable;
				pd->name="draggable";
				pd->comment="Draggable flag";
				break;
			case 19:
				pd->type='b';
				pd->data=&m_droppable;
				pd->name="droppable";
				pd->comment="Droppable flag";
				break;
			case 20:
				pd->type='p';
				pd->data=&m_mouse_cursor_can_drop;
				pd->name="mouse_cursor_can_drop";
				pd->comment="Mouse cursor for when m_droppable equals to true";
				break;
			case 21:
				pd->type='p';
				pd->data=&m_mouse_cursor_cannot_drop;
				pd->name="mouse_cursor_cannot_drop";
				pd->comment="Mouse cursor for when m_droppable equals to false";
				break;
			case 22:
				pd->type='s';
				pd->data=&m_tooltip;
				pd->name="tooltip_text";
				pd->comment="Object tool tip text, blank for no tool tip";
				break;
		}
	}
	return P_GUINUMDEFAULTPARAM;
}

int pGUIObject::get_custom_param_desc(int i,pParamDesc *pd)
{
	return 0;
}

void pGUIObject::init()
{
}

void pGUIObject::step(const float elapsed_time,const int& global_x,const int& global_y)
{
	m_global_x=global_x+m_pos_x;
	m_global_y=global_y+m_pos_y;

	if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
	{
		for(int i=0;i<m_child.num;i++)
			if (m_child.buf[i]->m_flags&P_GUIFLAGS_ENABLED)
			{
				g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_child.buf[i]->m_name));
				m_child.buf[i]->step(elapsed_time,m_global_x,m_global_y);
			}
	}
	else
	{
		for(int i=0;i<m_child.num;i++)
			if (m_child.buf[i]->m_flags&P_GUIFLAGS_ENABLED)
				m_child.buf[i]->step(elapsed_time,m_global_x,m_global_y);
	}
}

void pGUIObject::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	pRect r;
	if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
	{
		for(int i=0;i<m_child.num;i++)
			if(m_child.buf[i]->m_flags&P_GUIFLAGS_VISIBLE)
			{
				r.m_translate_x=scissor_rect.m_translate_x; // to do scrolling of scissors
				r.m_translate_y=scissor_rect.m_translate_y; // to do scrolling of scissors
				r.m_x=m_child.buf[i]->m_global_x+r.m_translate_x;
				r.m_y=m_child.buf[i]->m_global_y+r.m_translate_y;
				r.m_width=m_child.buf[i]->m_width;
				r.m_height=m_child.buf[i]->m_height;
				r.intersection(r,scissor_rect);
				
				glScissor(r.m_x,g_render->sizey-(r.m_y+r.m_height),r.m_width,r.m_height);
				g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(m_child.buf[i]->m_name));
				m_child.buf[i]->draw(r);
			}
	}
	else
	{
		for(int i=0;i<m_child.num;i++)
			if(m_child.buf[i]->m_flags&P_GUIFLAGS_VISIBLE)
			{
				r.m_translate_x=scissor_rect.m_translate_x; // to do scrolling of scissors
				r.m_translate_y=scissor_rect.m_translate_y; // to do scrolling of scissors
				r.m_x=m_child.buf[i]->m_global_x+r.m_translate_x;
				r.m_y=m_child.buf[i]->m_global_y+r.m_translate_y;
				r.m_width=m_child.buf[i]->m_width;
				r.m_height=m_child.buf[i]->m_height;
				r.intersection(r,scissor_rect);
				
				glScissor(r.m_x,g_render->sizey-(r.m_y+r.m_height),r.m_width,r.m_height);
				m_child.buf[i]->draw(r);
			}
	}

	// draw tooltip
	if(m_tooltip_flag && m_tooltip.length()>0)
	{
		int oldfont;
		if(g_render->tooltip_font==-1)
			oldfont=g_render->sel_font(0);
		else
			oldfont=g_render->sel_font(g_render->tooltip_font);
		g_render->sel_tex(g_render->tooltip_tex);

		glDisable(GL_SCISSOR_TEST);

		int text_px=g_render->get_text_size((const char *)m_tooltip,g_render->tooltip_fontsize);
		int x1=m_tooltip_x+text_px+2*g_render->tooltip_border;
		int y1=m_tooltip_y+g_render->tooltip_fontsize+2*g_render->tooltip_border;

		glColor4fv(&g_render->tooltip_bgcolor.x);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2i(m_tooltip_x,m_tooltip_y);
		glTexCoord2f(0.0f,0.0f);
		glVertex2i(m_tooltip_x,y1);
		glTexCoord2f(1.0f,0.0f);
		glVertex2i(x1,y1);
		glTexCoord2f(1.0f,1.0f);
		glVertex2i(x1,m_tooltip_y);
		//*glEnd();

		glColor4fv(&g_render->tooltip_textcolor.x);
		g_render->draw_text(m_tooltip_x,m_tooltip_y,(const char *)m_tooltip,g_render->tooltip_fontsize);
		
		glEnable(GL_SCISSOR_TEST);

		g_render->sel_font(oldfont);
	}
#endif
}

void pGUIObject::on_pre_parameter_change(int i)
{
}

void pGUIObject::on_pos_parameter_change(int i)
{
}

int pGUIObject::get_content_height()
{
	return m_height>m_content_height?m_height:m_content_height;
}

void pGUIObject::process_mouse_input(pGUIEventHandler *event_handler)
{

}
		
void pGUIObject::process_keyboard_input(int keycode,int mod,unsigned char ch)
{

}

void pGUIObject::on_get_mouse()
{

}

void pGUIObject::on_kill_mouse()
{

}

void pGUIObject::on_get_focus()
{

}

void pGUIObject::on_kill_focus()
{

}

void pGUIObject::on_begin_drag()
{

}

void pGUIObject::on_end_drag()
{

}

void pGUIObject::update_vbo()
{ }

#endif
