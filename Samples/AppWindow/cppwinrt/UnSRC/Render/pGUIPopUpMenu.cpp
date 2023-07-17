#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIPopUpMenu::init()
{
	if(m_nitems>0)
		on_pos_parameter_change(P_GUINUMDEFAULTPARAM+17);

	g_gomanager->set_focus(m_id);
}

void pGUIPopUpMenu::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	int y1=0,y2,icon,cur_icon=-174;
	int oldfont=g_render->sel_font(m_font);
	float u1,u2,v1,v2;
	pVector text_color;
	
	for(int i=0;i<m_items.num;i++)
	{
		if(i>0)
			y1+=(m_items[i-1].m_separator?m_item_separator_height:m_item_height);

		y2=y1+(m_items[i].m_separator?m_item_separator_height:m_item_height);

		// select icon
		switch(m_items[i].m_state)
		{
			case 0:	 icon=m_item_icon_disabled; text_color=m_item_textcolor_disabled; break;
			case 1:	 icon=m_item_icon_normal;	text_color=m_item_textcolor_normal;	break;
			case 2:	 icon=m_item_icon_hover;	text_color=m_item_textcolor_hover;	break;
			case 3:	 icon=m_item_icon_pressed;	text_color=m_item_textcolor_pressed;	break;
			default: icon=m_item_icon_disabled;	text_color=m_item_textcolor_disabled; break;
		}

		// calculate texture coordinates
		if(icon!=cur_icon && icon>=0 && m_item_icon_grid.m_grid_pic!=-1)
			m_item_icon_grid.get_icon_tex_coord(icon,u1,v1,u2,v2);

		cur_icon=icon;

		if(m_items[i].m_separator)
		{
			g_render->sel_tex(m_item_separator_tex);
			
			glColor3fv(&m_color.x);
			//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex2i(0,y1);
			glTexCoord2f(0.0f,1.0f);
			glVertex2i(0,y2);
			glTexCoord2f(1.0f,1.0f);
			glVertex2i(m_width,y2);
			glTexCoord2f(1.0f,0.0f);
			glVertex2i(m_width,y1);
			//*glEnd();
		}
		else
		{
			g_render->sel_tex(m_item_icon_grid.m_grid_pic);

			glColor3fv(&m_color.x);
			//*glBegin(GL_QUADS);
			glTexCoord2f(u1,v1);
			glVertex2i(0,y1);
			glTexCoord2f(u1,v2);
			glVertex2i(0,y2);
			glTexCoord2f(u2,v2);
			glVertex2i(m_width,y2);
			glTexCoord2f(u2,v1);
			glVertex2i(m_width,y1);
			//*glEnd();
		}

		if(m_items[i].m_separator==0)
		{
			// calculate text position
			int text_size=g_render->get_text_size((const char *)(m_items[i].m_text),m_font_size);
			int text_x,text_y=(int)((m_item_height-m_font_size)/2.0f);
			if(m_item_text_align==2) // center
				text_x=(int)(m_width/2.0f);
			else if(m_item_text_align!=0) // right
				text_x=m_width-text_size-m_item_border;
			else // left
				text_x=m_item_border;

			// draw text
			glColor4fv(&text_color.x);
			if(m_item_text_align==2) // center
				g_render->draw_text_center(text_x,y1+text_y,(const char *)(m_items[i].m_text),m_font_size);
			else
				g_render->draw_text(text_x,y1+text_y,(const char *)(m_items[i].m_text),m_font_size);
		}
	}

	glPopMatrix();

	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIPopUpMenu::process_mouse_input(pGUIEventHandler *event_handler)
{
	int pushed_item=-1;
	
	if(is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y))
	{
		int y1=m_global_y,y2;
		
		for(int i=0;i<m_items.num;i++)
		{
			if(i>0)
				y1+=(m_items[i-1].m_separator?m_item_separator_height:m_item_height);
			
			y2=y1+(m_items[i].m_separator?m_item_separator_height:m_item_height);

			if(m_items[i].m_state!=0)
				if(g_gomanager->m_mouse_y>y1 && g_gomanager->m_mouse_y<y2)
				{
					if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK || g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
						m_items[i].m_state=3; // m_state=PRESSED
					else if(m_items[i].m_state!=3) // m_state!=PRESSED
						m_items[i].m_state=2; // m_state=HOVER

					if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTUNCLICK)
					{
						if(m_items[i].m_state==3) // m_state==PRESSED
							pushed_item=i;
						m_items[i].m_state=2; // m_state=HOVER
					}
				}
				else
					if(m_items[i].m_state>1)
						m_items[i].m_state=1;
		}
	}
	else
	{
		for(int i=0;i<m_items.num;i++)
			if(m_items[i].m_state>1)
				m_items[i].m_state=1;
	}
	
	if(pushed_item!=-1 && m_caller_event_handler)
	{
		m_caller_event_handler->event_handler(P_GUI_MSG_POPUPACTION,m_caller_id,m_items[pushed_item].m_cookie,0);
		g_gomanager->post_deactivate(m_id);
	}
}

void pGUIPopUpMenu::on_kill_mouse()
{
	for(int i=0;i<m_items.num;i++)
		if(m_items[i].m_state==2 || m_items[i].m_state==3)
			m_items[i].m_state=1;
}

void pGUIPopUpMenu::on_kill_focus()
{
	g_gomanager->deactivate(m_id);
}

int pGUIPopUpMenu::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="GUI object general-purpose color";
		break;
		case 1:
			pd->type='i';
			pd->data=&m_item_height;
			pd->name="item_height";
			pd->comment="Height of each pop-up menu item";
			break;
		case 2:
			pd->type='p';
			pd->data=&m_item_icon_grid.m_grid_pic;
			pd->name="item_tex";
			pd->comment="Icon grid texture for the items";
			break;
		case 3:
			pd->type='i';
			pd->data=&m_item_icon_grid.m_icon_width;
			pd->name="item_icon_width";
			pd->comment="Width of all icons in icon grid texture";
			break;
		case 4:
			pd->type='i';
			pd->data=&m_item_icon_grid.m_icon_height;
			pd->name="item_icon_height";
			pd->comment="Height of all icons in icon grid texture";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_item_icon_disabled;
			pd->name="item_icon_disabled";
			pd->comment="Item icon index for disabled state";
			break;
		case 6:
			pd->type='i';
			pd->data=&m_item_icon_normal;
			pd->name="item_icon_normal";
			pd->comment="Item icon index for normal state";
			break;
		case 7:
			pd->type='i';
			pd->data=&m_item_icon_hover;
			pd->name="item_icon_hover";
			pd->comment="Item icon index for hover state";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_item_icon_pressed;
			pd->name="item_icon_pressed";
			pd->comment="Item icon index for pressed state";
			break;
		case 9:
			pd->type='c';
			pd->data=&m_item_textcolor_disabled;
			pd->name="item_textcolor_disabled";
			pd->comment="Item text color for disabled state";
			break;
		case 10:
			pd->type='c';
			pd->data=&m_item_textcolor_normal;
			pd->name="item_textcolor_normal";
			pd->comment="Item text color for normal state";
			break;
		case 11:
			pd->type='c';
			pd->data=&m_item_textcolor_hover;
			pd->name="item_textcolor_hover";
			pd->comment="Item text color for hover state";
			break;
		case 12:
			pd->type='c';
			pd->data=&m_item_textcolor_pressed;
			pd->name="item_textcolor_pressed";
			pd->comment="Item text color for pressed state";
			break;
		case 13:
			pd->type='i';
			pd->data=&m_item_text_align;
			pd->name="item_text_align";
			pd->comment="Item text horizontal alignment|Left|Right|Center";
			break;
		case 14:
			pd->type='i';
			pd->data=&m_item_border;
			pd->name="item_border";
			pd->comment="Item border size";
			break;
		case 15:
			pd->type='i';
			pd->data=&m_item_separator_height;
			pd->name="item_separator_height";
			pd->comment="Height of separator items";
			break;
		case 16:
			pd->type='p';
			pd->data=&m_item_separator_tex;
			pd->name="item_separator_tex";
			pd->comment="Item separator texture, used only in separator items";
			break;
		case 17:
			pd->type='i';
			pd->data=&m_nitems;
			pd->name="num_items";
			pd->comment="Initial number of items";
			break;
		case 18:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 19:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 20:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 21:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
		case 22:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Text font face";
			break;
		case 23:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Text font size";
			break;
	}

	return 24;
}

void pGUIPopUpMenu::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
	case 17:
		{
			if(m_nitems<0)
				m_nitems=0;

			int a=m_items.num,b=m_nitems;

			int ib;
			for(ib=b;ib<a;ib++)
				remove_item(m_items.num-1);

			pString text;
			for(ib=b;ib>a;ib--)
			{
				text.format("item%d",m_items.num);
				add_item(text,0,1);
			}

			m_height=m_nitems*m_item_height;
		}
		break;
	}
}

void pGUIPopUpMenu::set_position_from_mouse()
{
	m_pos_x=g_gomanager->m_mouse_x;
	m_pos_y=g_gomanager->m_mouse_y;
}

void pGUIPopUpMenu::set_context_object(const unsigned int id)
{
	m_caller_id=id;
	m_caller_event_handler=g_gomanager->get_event_handler(id);
}

// item definition and manipulation
void pGUIPopUpMenu::add_item(const pString &text,const int cookie,const int state)
{
	pGUIPopUpMenuItem new_item;
	new_item.m_text=text;
	new_item.m_cookie=cookie;
	new_item.m_state=state;
	new_item.m_separator=0;

	m_items.add(new_item);

	m_nitems=m_items.num;
}

void pGUIPopUpMenu::add_separator()
{
	pGUIPopUpMenuItem new_item;
	new_item.m_separator=1;

	m_items.add(new_item);

	m_nitems=m_items.num;
}

void pGUIPopUpMenu::remove_item(const int ind)
{
	if(ind<0 || ind>=m_items.num)
		return;

	m_items.remove(ind);

	m_nitems=m_items.num;
}

void pGUIPopUpMenu::get_item_text(const int ind, pString &text)
{
	if(ind<0 || ind>=m_items.num)
		return;

	text=m_items[ind].m_text;
}

int pGUIPopUpMenu::get_item_cookie(const int ind)
{
	if(ind<0 || ind>=m_items.num)
		return -1;

	return m_items[ind].m_cookie;
}

int pGUIPopUpMenu::get_item_state(const int ind)
{
	if(ind<0 || ind>=m_items.num)
		return -1;

	return m_items[ind].m_state;
}

int pGUIPopUpMenu::get_item_separator(const int ind)
{
	if(ind<0 || ind>=m_items.num)
		return 0;

	return m_items[ind].m_separator;
}

void pGUIPopUpMenu::set_item_text(const int ind, const pString &text)
{
	if(ind<0 || ind>=m_items.num)
		return;

	m_items[ind].m_text=text;
}

void pGUIPopUpMenu::set_item_cookie(const int ind, const int cookie)
{
	if(ind<0 || ind>=m_items.num)
		return;

	m_items[ind].m_cookie=cookie;
}

void pGUIPopUpMenu::set_item_state(const int ind, const int state)
{
	if(ind<0 || ind>=m_items.num)
		return;

	m_items[ind].m_state=state;
}

void pGUIPopUpMenu::set_item_separator(const int ind, const int separator)
{
	if(ind<0 || ind>=m_items.num)
		return;

	m_items[ind].m_separator=separator;
}

#endif		
