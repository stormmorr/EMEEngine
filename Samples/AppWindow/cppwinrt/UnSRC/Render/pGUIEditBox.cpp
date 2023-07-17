#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIEditBox::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	// draw window and backgound
	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	glColor4fv(&m_color.x);
	g_render->sel_tex(m_tex);
	//*glBegin(GL_QUADS);
	glTexCoord2i(0,1);
	glVertex2i(0,0);
	glTexCoord2i(0,0);
	glVertex2i(0,m_height);
	glTexCoord2i(1,0);
	glVertex2i(m_width,m_height);
	glTexCoord2i(1,1);
	glVertex2i(m_width,0);
	//*glEnd();

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glPopMatrix();

	// draw text
	int oldfont=g_render->sel_font(m_font);

	int textx=m_text_border_size;
	pString text=m_text;
	if(m_masked)
	{
		for(int i=0;i<text.length();i++)
			text.set_char(i,'*');
	}
	
	glColor4fv(&m_text_color.x);
	if(m_text_align==2) // center
	{
		textx=(int)(m_width/2.0f);
		g_render->draw_text_center(m_global_x+textx,(m_global_y+(int)((m_height-m_font_size)/2.0f)),(const char *)text,m_font_size);
		textx-=(int)(g_render->get_text_size((const char *)text,m_font_size)/2.0f);
	}
	else
	{
		if(m_text_align!=0) // right
		{
			int textsize=g_render->get_text_size((const char *)text,m_font_size);
			textx=m_width-textsize-m_text_border_size;
		}

		g_render->draw_text(m_global_x+textx,(m_global_y+(int)((m_height-m_font_size)/2.0f)),(const char *)text,m_font_size);
	}

	if(g_gomanager->m_input_focus==this)
	{
		// draw selection
		if(m_sel_start<m_sel_end)
		{
			int selstartx=	m_global_x+textx+g_render->get_text_size((const char *)text.left(m_sel_start),	m_font_size)+1;
			int selendx=	m_global_x+textx+g_render->get_text_size((const char *)text.left(m_sel_end),	m_font_size)+1;
			int sely=		m_global_y+(int)((m_height-m_font_size)/2.0f);

			g_render->sel_tex(-1);
			glColor4fv(&m_sel_bg_color.x);
			//*glBegin(GL_QUADS);
				glVertex2i(selstartx,sely);
				glVertex2i(selstartx,sely+m_font_size);
				glVertex2i(selendx,sely+m_font_size);
				glVertex2i(selendx,sely);
			//*glEnd();

			glColor4fv(&m_sel_text_color.x);
			g_render->draw_text(selstartx-1,sely,text.mid(m_sel_start,m_sel_end-m_sel_start),m_font_size);
		}

		// draw text cursor
		pVector blink_color;
		if(m_cursor_blink_func.m_type==P_PERIODICFUNC_NONE)
			blink_color=m_cursor_color1;
		else
		{
			float t=m_cursor_blink_func.eval(g_gomanager->m_time);
			blink_color=(1.0f-t)*m_cursor_color1+t*m_cursor_color2;
			blink_color.w=(1.0f-t)*m_cursor_color1.w+t*m_cursor_color2.w;
		}
		
		int cposx=m_global_x+textx+g_render->get_text_size((const char *)text.left(m_caret_pos),m_font_size)+1;
		int cposy=m_global_y+(int)((m_height-m_font_size)/2.0f);

		g_render->sel_tex(-1);
		glColor4fv(&blink_color.x);
		//*glBegin(GL_LINES);
			glVertex2i(cposx,cposy);
			glVertex2i(cposx,cposy+m_font_size);
		//*glEnd();
	}
	
	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIEditBox::process_mouse_input(pGUIEventHandler *event_handler)
{
	if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK)
	{
		int mx=g_gomanager->m_mouse_x;
		int my=g_gomanager->m_mouse_y;

		mx-=m_global_x;
		my-=m_global_y;

		int ty=(int)((m_height-m_font_size)/2.0f);
		if(mx>=0 && mx<=m_width && my>=ty && my<=ty+m_font_size)
		{
			int textx=m_text_border_size;
			pString text=m_text;
			if(m_masked)
			{
				for(int i=0;i<text.length();i++)
					text.set_char(i,'*');
			}
			
			int textsize=g_render->get_text_size((const char *)text,m_font_size);

			if(m_text_align==2) // center
			{
				textx=(int)(m_width/2.0f);
				textx-=(int)(g_render->get_text_size((const char *)text,m_font_size)/2.0f);
			}
			else
			{
				if(m_text_align!=0) // right
					textx=m_width-textsize-m_text_border_size;
			}

			if(mx<textx)
				m_caret_pos=0;
			if(mx>textx+textsize)
				m_caret_pos=text.length();
			else
			{
				int mp=mx-textx,cp;
				char ch[2];
				ch[1]=0;
				for(int i=0;i<text.length();i++)
				{
					ch[0]=text[i];
					cp=g_render->get_text_size(ch,m_font_size);
					if(mp<cp)
					{
						if(mp<=cp/2)
							m_caret_pos=i;
						else
							m_caret_pos=i+1;
						break;
					}

					mp-=cp;
				}
			}

			m_sel_start=m_sel_end=m_caret_pos;
		}
	}
}

void pGUIEditBox::process_keyboard_input(int keycode,int mod,unsigned char ch)
{
	bool change=false; // for on_change event

	if(ch>=32 && (m_valid_chars.length()==0 || m_valid_chars.find(ch)!=-1))
	{
		if(m_sel_end>m_sel_start)
		{
			pString s1=m_text.left(m_sel_start);
			pString s2=m_text.right(m_text.length()-m_sel_end);
			m_text.format("%s%c%s",(const char *)s1,ch,(const char *)s2);
			m_caret_pos=m_sel_start+1;
			change=true; // for on_change event
		}
		else if(m_text.length()<m_max_chars)
		{
			pString s1=m_text.left(m_caret_pos);
			pString s2=m_text.right(m_text.length()-m_caret_pos);
			m_text.format("%s%c%s",(const char *)s1,ch,(const char *)s2);
			m_caret_pos++;
			change=true; // for on_change event
		}

		m_sel_start=m_sel_end=m_caret_pos;
	}
	else
		switch(keycode)
		{
			case SDLK_LEFT:
			{
				if(mod&KMOD_SHIFT)
				{
					if(m_caret_pos==m_sel_start)
						m_sel_start--;
					else if(m_caret_pos==m_sel_end)
						m_sel_end--;
				}
				else
				{
					if(m_sel_end>m_sel_start)
						m_caret_pos++;
					m_sel_start=m_sel_end;
				}

				m_caret_pos--;

				if(m_sel_start==m_sel_end)
					m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
			case SDLK_RIGHT:
			{
				if(mod&KMOD_SHIFT)
				{
					if(m_caret_pos==m_sel_end)
						m_sel_end++;
					else if(m_caret_pos==m_sel_start)
						m_sel_start++;
				}
				else
				{
					if(m_sel_end>m_sel_start)
						m_caret_pos--;
					m_sel_start=m_sel_end;
				}

				m_caret_pos++;

				if(m_sel_start==m_sel_end)
					m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
			case SDLK_HOME:
			{
				if(mod&KMOD_SHIFT)
				{
					if(m_caret_pos==m_sel_end)
						m_sel_end=m_sel_start;
					m_sel_start=0;
				}
				else
					m_sel_start=m_sel_end;

				m_caret_pos=0;

				if(m_sel_start==m_sel_end)
					m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
			case SDLK_END:
			{
				if(mod&KMOD_SHIFT)
				{
					if(m_caret_pos==m_sel_start)
						m_sel_start=m_sel_end;
					m_sel_end=m_text.length();
				}
				else
					m_sel_start=m_sel_end;

				m_caret_pos=m_text.length();

				if(m_sel_start==m_sel_end)
					m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
			case SDLK_BACKSPACE:
			{
				if(m_sel_end>m_sel_start)
				{
					pString s1=m_text.left(m_sel_start);
					pString s2=m_text.right(m_text.length()-m_sel_end);
					m_text.format("%s%s",(const char *)s1,(const char *)s2);
					m_caret_pos=m_sel_start;
					change=true; // for on_change event
				}
				else if(m_caret_pos>0)
				{
					pString s1=m_text.left(m_caret_pos-1);
					pString s2=m_text.right(m_text.length()-m_caret_pos);
					m_text.format("%s%s",(const char *)s1,(const char *)s2);
					m_caret_pos--;
					change=true; // for on_change event
				}

				m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
			case SDLK_DELETE:
			{
				if(m_sel_end>m_sel_start)
				{
					pString s1=m_text.left(m_sel_start);
					pString s2=m_text.right(m_text.length()-m_sel_end);
					m_text.format("%s%s",(const char *)s1,(const char *)s2);
					m_caret_pos=m_sel_start;
					change=true; // for on_change event
				}
				else if(m_caret_pos<m_text.length())
				{
					pString s1=m_text.left(m_caret_pos);
					pString s2=m_text.right(m_text.length()-m_caret_pos-1);
					m_text.format("%s%s",(const char *)s1,(const char *)s2);
					change=true; // for on_change event
				}

				m_sel_start=m_sel_end=m_caret_pos;
			}
			break;
		}

	if(m_sel_start<0)
		m_sel_start=0;
	else 
	{
		int l=m_text.length();
		if(m_sel_start>l)
			m_sel_start=l;
	}

	if(m_sel_end<0)
		m_sel_end=0;
	else 
	{
		int l=m_text.length();
		if(m_sel_end>l)
			m_sel_end=l;
	}

	if(m_caret_pos<0)
		m_caret_pos=0;
	else 
	{
		int l=m_text.length();
		if(m_caret_pos>l)
			m_caret_pos=l;
	}

	pGUIObject::process_keyboard_input(keycode,mod,ch);

	// for on_change event
	if(change)
	{
		pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
		if(eh)
			eh->event_handler(P_GUI_MSG_ONCHANGE,m_id,0,0);
	}
}

void pGUIEditBox::on_get_focus()
{
	m_sel_start=0;
	m_caret_pos=m_sel_end=m_text.length();
}

int pGUIEditBox::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->comment="Object transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 2:
			pd->type='p';
			pd->data=&m_tex;
			pd->name="texture";
			pd->comment="Background texture";
			break;
		case 3:
			pd->type='s';
			pd->data=&m_text;
			pd->name="text";
			pd->comment="Object text";
			break;
		case 4:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Text font face";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Text font size";
			break;
		case 6:
			pd->type='c';
			pd->data=&m_text_color;
			pd->name="text_color";
			pd->comment="Face color for the text";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_text_color.w;
			pd->name="text_transp";
			pd->comment="Text transparency (0 = fully transparent, 1 = fully opaque)";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_text_align;
			pd->name="text_align";
			pd->comment="Horizontal text alignment|Left|Right|Center";
			break;
		case 9:
			pd->type='i';
			pd->data=&m_text_border_size;
			pd->name="text_border_size";
			pd->comment="Text border size";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_caret_pos;
			pd->name="caret_pos";
			pd->comment="Caret position (0: before 1st character)";
			break;
		case 11:
			pd->type='c';
			pd->data=&m_cursor_color1;
			pd->name="cursor_color1";
			pd->comment="Primary color for the blinking text cursor";
			break;
		case 12:
			pd->type='f';
			pd->data=&m_cursor_color1.w;
			pd->name="cursor_transp1";
			pd->comment="Primary transparency for the blinking text cursor";
			break;
		case 13:
			pd->type='c';
			pd->data=&m_cursor_color2;
			pd->name="cursor_color2";
			pd->comment="Secondary color for the blinking text cursor";
			break;
		case 14:
			pd->type='f';
			pd->data=&m_cursor_color2.w;
			pd->name="cursor_transp2";
			pd->comment="Secondary transparency for the blinking text cursor";
			break;
		case 15:
			pd->type='e';
			pd->data=&m_cursor_blink_func;
			pd->name="cursor_blink_func";
			pd->comment="Periodic function for cursor blinking color interpolation";
			break;
		case 16:
			pd->type='i';
			pd->data=&m_max_chars;
			pd->name="max_chars";
			pd->comment="Edit box maximum number of characters";
			break;
		case 17:
			pd->type='s';
			pd->data=&m_valid_chars;
			pd->name="valid_chars";
			pd->comment="String containing the set of acceptable characters";
			break;
		case 18:
			pd->type='b';
			pd->data=&m_masked;
			pd->name="masked";
			pd->comment="Edit box mask flag (for password fields)";
			break;
		case 19:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
			break;
		case 20:
			pd->type='b';
			pd->data=&m_focusable;
			pd->name="focusable";
			pd->comment="Focusable flag";
			break;
		case 21:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 22:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 23:
			pd->type='c';
			pd->data=&m_sel_bg_color;
			pd->name="sel_bg_color";
			pd->comment="Selected text background color";
			break;
		case 24:
			pd->type='f';
			pd->data=&m_sel_bg_color.w;
			pd->name="sel_bg_transp";
			pd->comment="Selected text background transparency";
			break;
		case 25:
			pd->type='c';
			pd->data=&m_sel_text_color;
			pd->name="sel_text_color";
			pd->comment="Selected text face color";
			break;
		case 26:
			pd->type='f';
			pd->data=&m_sel_text_color.w;
			pd->name="sel_text_transp";
			pd->comment="Selected text face transparency";
			break;
		case 27:
			pd->type='i';
			pd->data=&m_sel_start;
			pd->name="sel_start";
			pd->comment="Selection start position (0: before 1st character)";
			break;
		case 28:
			pd->type='i';
			pd->data=&m_sel_end;
			pd->name="sel_end";
			pd->comment="Selection end position (0: before 1st character)";
			break;
		case 29:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 30:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 31:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 32:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 33:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 34:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 35;
}

void pGUIEditBox::on_pos_parameter_change(int i)
{
	// base object
	switch(i)
	{
		case 3: // m_text
		{
			// for on_change event
			pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
			if(eh)
				eh->event_handler(P_GUI_MSG_ONCHANGE,m_id,0,0);
		}
		break;
	}
}

#endif
