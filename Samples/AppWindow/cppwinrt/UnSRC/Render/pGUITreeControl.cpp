#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUITreeControl::init()
{
}

void pGUITreeControl::draw_node_rec(pGUITreeControlItem *cur_item,int &posx,int &posy)
{
	if(cur_item)
	{
		int icon,width=m_item_border_size*2+m_item_height*2+g_render->get_text_size(cur_item->m_text,m_font_size)+1;
		float u1,v1,u2,v2;
		int px=posx+m_item_border_size;

		// draw background
		if(cur_item==m_sel)
		{
			if(m_transparent_sel==0)
			{
				g_render->sel_tex(m_tex_item_sel);
				//*glColor4fv(&cur_item->m_custom_color_bg_sel.x);
				//*glBegin(GL_QUADS);
				//*glVertex2i(posx,posy);
				//*glVertex2i(posx,posy+m_item_height);
				//*glVertex2i(posx+width,posy+m_item_height);
				//*glVertex2i(posx+width,posy);
				//*glEnd();
			}
			else
			{
				g_render->sel_tex(-1);
				//*glColor4f(1.0f,1.0f,1.0f,1.0f);
			}
		}
		else if(m_transparent_items==0)
		{
			g_render->sel_tex(m_tex_item);
			//*glColor4fv(&cur_item->m_custom_color_bg.x);
			//*glBegin(GL_QUADS);
			//*glVertex2i(posx,posy);
			//*glVertex2i(posx,posy+m_item_height);
			//*glVertex2i(posx+width,posy+m_item_height);
			//*glVertex2i(posx+width,posy);
			//*glEnd();
		}
		else
		{
			g_render->sel_tex(-1);
			//*glColor4f(1.0f,1.0f,1.0f,1.0f);
		}
		
		// draw expanded/retracted box
		if(cur_item->m_child.num>0 && m_item_box_grid.m_grid_pic!=-1)
		{
			// select box icon
			switch(cur_item->m_state)
			{
				case NODE_STATE_NORMAL:		icon=m_item_box_normal;		break;
				case NODE_STATE_EXPANDED:	icon=m_item_box_expanded;	break;
				default:					icon=m_item_box_normal;		break;
			}

			// calculate box texture coordinates
			if(icon>=0)
				m_item_box_grid.get_icon_tex_coord(icon,u1,v1,u2,v2);

			g_render->sel_tex(m_item_box_grid.m_grid_pic);
			//*glBegin(GL_QUADS);
			//*glTexCoord2f(u1,v1);
			//*glVertex2i(px,posy);
			//*glTexCoord2f(u1,v2);
			//*glVertex2i(px,posy+m_item_height);
			//*glTexCoord2f(u2,v2);
			//*glVertex2i(px+m_item_height,posy+m_item_height);
			//*glTexCoord2f(u2,v1);
			//*glVertex2i(px+m_item_height,posy);
			//*glEnd();
		}

		px+=m_item_height;

		// draw icon
		if(m_item_icon_grid.m_grid_pic!=-1)
		{
			// select icon
			switch(cur_item->m_sel_state)
			{
				case NODE_SEL_STATE_NORMAL:		icon=cur_item->m_icon_normal;	break;
				case NODE_SEL_STATE_SELECTED:	icon=cur_item->m_icon_selected;	break;
				default:						icon=cur_item->m_icon_normal;	break;
			}

			// calculate box texture coordinates
			if(icon>=0)
				m_item_icon_grid.get_icon_tex_coord(icon,u1,v1,u2,v2);

			g_render->sel_tex(m_item_icon_grid.m_grid_pic);
			//*glBegin(GL_QUADS);
			//*glTexCoord2f(u1,v1);
			//*glVertex2i(px,posy);
			//*glTexCoord2f(u1,v2);
			//*glVertex2i(px,posy+m_item_height);
			//*glTexCoord2f(u2,v2);
			//*glVertex2i(px+m_item_height,posy+m_item_height);
			//*glTexCoord2f(u2,v1);
			//*glVertex2i(px+m_item_height,posy);
			//*glEnd();
		}

		px+=m_item_height;
		//*if(cur_item==m_sel)
		//*	glColor4fv(&cur_item->m_custom_color_text_sel.x);
		//*else
		//*	glColor4fv(&cur_item->m_custom_color_text.x);
		g_render->draw_text(px,posy+(int)((m_item_height-m_font_size)*0.5f),(const char *)cur_item->m_text,m_font_size);

		posy+=m_item_height;

		if(cur_item->m_state==NODE_STATE_EXPANDED)
		{
			posx+=m_item_indent;
			for(int i=0;i<cur_item->m_child.num;i++)
				draw_node_rec(cur_item->m_child[i],posx,posy);
			posx-=m_item_indent;
		}
	}
}

void pGUITreeControl::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	int i;
	
	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	// draw control background
	glColor4fv(&m_color.x);
	g_render->sel_tex(m_tex_bg);
	//*glBegin(GL_QUADS);
	glTexCoord2f(0.0f,1.0f);
	glVertex2i(0,0);
	glTexCoord2f(0.0f,0.0f);
	glVertex2i(0,m_height);
	glTexCoord2f(1.0f,0.0f);
	glVertex2i(m_width,m_height);
	glTexCoord2f(1.0f,1.0f);
	glVertex2i(m_width,0);
	//*glEnd();

	int oldfont=g_render->sel_font(m_font);
//	glColor4fv(&m_color_item_text.x);

	if(m_root.num==0 && m_show_dummy_items)
	{
		int n=add_node("Dummy Item",ROOT_NODE_ID,INVALID_COOKIE);
		add_node("Son of a Dummy",n,INVALID_COOKIE);
		add_node("Another Child",n,INVALID_COOKIE);
		n=add_node("Retracted Item",ROOT_NODE_ID,INVALID_COOKIE);
		n=add_node("Expand Me",n,INVALID_COOKIE);
		add_node("Found Me!",n,INVALID_COOKIE);
		add_node("Me Too!",n,INVALID_COOKIE);

		m_root[1]->m_state=NODE_STATE_NORMAL;
		m_root[1]->m_child[0]->m_state=NODE_STATE_NORMAL;
	}
	
	int posx=0,posy=0;
	for(i=0;i<m_root.num;i++)
		draw_node_rec(m_root[i],posx,posy);

	glPopMatrix();

	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);

#endif
}

void pGUITreeControl::process_mouse_input(pGUIEventHandler *event_handler)
{
	if(	is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y) &&
		g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK	 || 
		g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDCLICK	 )
	{
		unselect_all();
		m_sel=0;
		int cury=m_global_y;
		for(int i=0;i<m_root.num;i++)
			if(process_mouse_rec(m_root[i],m_sel,cury,g_gomanager->m_mouse_y))
				break;

		if(m_sel)
		{
			pGUITreeControlItem *item=m_sel;
			while(item)
			{
				item->m_sel_state=NODE_SEL_STATE_SELECTED;
				item=item->m_parent;
				if(event_handler)
					event_handler->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
			}

			if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDCLICK)
				m_sel->m_state=!m_sel->m_state;
		}
	}
}

int pGUITreeControl::process_mouse_rec(pGUITreeControlItem *cur_item,pGUITreeControlItem *&item,int &cury,const int mousey)
{
	if(cur_item==0)
		return 0;
	
	if(mousey>=cury && mousey<=cury+m_item_height)
	{
		item=cur_item;
		return 1;
	}

	cury+=m_item_height;
	if(cur_item->m_state==NODE_STATE_EXPANDED)
		for(int i=0;i<cur_item->m_child.num;i++)
			if(process_mouse_rec(cur_item->m_child[i],item,cury,mousey))
				return 1;

	return 0;
}

int pGUITreeControl::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Font file for the check box text";
			break;
		case 1:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Font size for the check box text";
			break;
		case 2:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color_bg";
			pd->comment="Background color";
			break;
		case 3:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp_bg";
			pd->comment="Background transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 4:
			pd->type='p';
			pd->data=&m_tex_bg;
			pd->name="tex_bg";
			pd->comment="Texture for the tree control background";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_item_height;
			pd->name="item_height";
			pd->comment="Fixed height for each item, in pixels";
			break;
		case 6:
			pd->type='i';
			pd->data=&m_item_indent;
			pd->name="item_indent";
			pd->comment="Fixed height for item indentation, in pixels";
			break;
		case 7:
			pd->type='b';
			pd->data=&m_transparent_items;
			pd->name="transparent_items";
			pd->comment="Transparent items flag, does not draw item texture or background if set";
			break;
		case 8:
			pd->type='b';
			pd->data=&m_transparent_sel;
			pd->name="transparent_sel";
			pd->comment="Transparent selection flag, does not draw selected item texture or background if set";
			break;
		case 9:
			pd->type='p';
			pd->data=&m_tex_item;
			pd->name="tex_item";
			pd->comment="Texture for the item background";
			break;
		case 10:
			pd->type='p';
			pd->data=&m_tex_item_sel;
			pd->name="tex_item_sel";
			pd->comment="Texture for the selected item background";
			break;
		case 11:
			pd->type='c';
			pd->data=&m_color_item;
			pd->name="color_item";
			pd->comment="Face color for the item background";
			break;
		case 12:
			pd->type='f';
			pd->data=&m_color_item.w;
			pd->name="transp_item";
			pd->comment="Face transparency for the item background (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 13:
			pd->type='c';
			pd->data=&m_color_item_sel;
			pd->name="color_item_sel";
			pd->comment="Face color for the selected item background";
			break;
		case 14:
			pd->type='f';
			pd->data=&m_color_item_sel.w;
			pd->name="transp_item_sel";
			pd->comment="Face transparency for the selected item background (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 15:
			pd->type='c';
			pd->data=&m_color_item_text;
			pd->name="color_item_text";
			pd->comment="Face color for the item text";
			break;
		case 16:
			pd->type='f';
			pd->data=&m_color_item_text.w;
			pd->name="transp_item_text";
			pd->comment="Face transparency for the item text (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 17:
			pd->type='c';
			pd->data=&m_color_item_sel_text;
			pd->name="color_item_sel_text";
			pd->comment="Face color for the selected item text";
			break;
		case 18:
			pd->type='f';
			pd->data=&m_color_item_sel_text.w;
			pd->name="transp_item_sel_text";
			pd->comment="Face transparency for the selected item text (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 19:
			pd->type='p';
			pd->data=&m_item_box_grid.m_grid_pic;
			pd->name="item_box_tex";
			pd->comment="Grid texture for item normal/expanded boxes";
			break;
		case 20:
			pd->type='i';
			pd->data=&m_item_box_grid.m_icon_width;
			pd->name="item_box_width";
			pd->comment="Width of all boxes in the box grid texture";
			break;
		case 21:
			pd->type='i';
			pd->data=&m_item_box_grid.m_icon_height;
			pd->name="item_box_height";
			pd->comment="Height of all boxes in the box grid texture";
			break;
		case 22:
			pd->type='i';
			pd->data=&m_item_box_normal;
			pd->name="item_box_normal";
			pd->comment="Item box index for normal state";
			break;
		case 23:
			pd->type='i';
			pd->data=&m_item_box_expanded;
			pd->name="item_box_expanded";
			pd->comment="Item box index for expanded state";
			break;
		case 24:
			pd->type='p';
			pd->data=&m_item_icon_grid.m_grid_pic;
			pd->name="item_icon_tex";
			pd->comment="Grid texture for item icons";
			break;
		case 25:
			pd->type='i';
			pd->data=&m_item_icon_grid.m_icon_width;
			pd->name="item_icon_width";
			pd->comment="Width of all icons in the icon grid texture";
			break;
		case 26:
			pd->type='i';
			pd->data=&m_item_icon_grid.m_icon_height;
			pd->name="item_icon_height";
			pd->comment="Height of all icons in the icon grid texture";
			break;
		case 27:
			pd->type='i';
			pd->data=&m_item_default_icon_normal;
			pd->name="item_default_icon_normal";
			pd->comment="Default item icon index for normal state";
			break;
		case 28:
			pd->type='i';
			pd->data=&m_item_default_icon_selected;
			pd->name="item_default_icon_selected";
			pd->comment="Default item icon index for selected state";
			break;
		case 29:
			pd->type='i';
			pd->data=&m_item_border_size;
			pd->name="item_border_size";
			pd->comment="Item border size in pixels";
			break;
		case 30:
			pd->type='b';
			pd->data=&m_show_dummy_items;
			pd->name="show_dummy_items";
			pd->comment="If set, shows dummy items when item count = 0";
			break;
		case 31:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 32:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 33:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 34:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 35:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 36:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 37;
}

void pGUITreeControl::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 30:
			if(m_show_dummy_items==0)
				if(m_root.num>=2 && m_root[0]->m_text.compare("Dummy Item")==0)
				{
					remove_node(m_root[1]->m_id);
					remove_node(m_root[0]->m_id);
				}
		break;
	}
}

// item manipulation
int pGUITreeControl::add_node(const pString name,const unsigned int parent,const int cookie)
{
	pGUITreeControlItem *item = new pGUITreeControlItem(m_nextid++,name,cookie,m_item_default_icon_normal,m_item_default_icon_selected,m_color_item,m_color_item_text,m_color_item_sel,m_color_item_sel_text);
	
	if(parent==ROOT_NODE_ID)
	{
		m_root.add(item);
		item->m_parent=0;
		return m_nextid-1;
	}

	pGUITreeControlItem *parent_item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],parent_item,parent))
		{
			if(parent_item)
			{
				parent_item->m_child.add(item);
				item->m_parent=parent_item;
				return m_nextid-1;
			}
		}

	return ROOT_NODE_ID;
}

void pGUITreeControl::remove_node(const unsigned int id)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
		{
			if(item)
			{
				if(item->m_parent)
				{
					for(int j=0;j<item->m_parent->m_child.num;j++)
						if(item->m_parent->m_child[j]==item)
							item->m_parent->m_child.remove(j);
				}
				else
					for(int j=0;j<m_root.num;j++)
						if(m_root[j]==item)
							m_root.remove(j);

				delete item;
				return;
			}
		}
}

void pGUITreeControl::remove_all()
{
	pGUITreeControlItem *item;
	for(int i=m_root.num-1;i>=0;i--)
	{
		item=m_root[i];
		m_root.remove(i);
		delete item;
	}
}

void pGUITreeControl::set_icons(const unsigned int id,const int icon_normal,const int icon_selected)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
		{
			if(item)
			{
				item->m_icon_normal=icon_normal;
				item->m_icon_selected=icon_selected;
				return;
			}
		}
}

void pGUITreeControl::set_colors(const unsigned int id,const pVector color_bg,const pVector color_text,const pVector color_bg_sel,const pVector color_text_sel)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
		{
			if(item)
			{
				item->m_custom_color_bg=color_bg;
				item->m_custom_color_text=color_text;
				item->m_custom_color_bg_sel=color_bg_sel;
				item->m_custom_color_text_sel=color_text_sel;
				return;
			}
		}
}

void pGUITreeControl::set_cur_sel(const unsigned int id)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
			{
				unselect_all();
				m_sel=item;

				while(item)
				{
					item->m_sel_state=NODE_SEL_STATE_SELECTED;
					item=item->m_parent;
				}
			}
}

unsigned int pGUITreeControl::get_cur_sel()
{
	if(m_sel)
		return m_sel->m_id;
	return ROOT_NODE_ID;
}

int pGUITreeControl::get_cur_sel_cookie()
{
	if(m_sel)
		return m_sel->m_cookie;
	return INVALID_COOKIE;
}

void pGUITreeControl::expand_all()
{
	for(int i=0;i<m_root.num;i++)
		expand_retract_unselect_rec(m_root[i],0);
}

void pGUITreeControl::retract_all()
{
	for(int i=0;i<m_root.num;i++)
		expand_retract_unselect_rec(m_root[i],1);
}

void pGUITreeControl::unselect_all()
{
	for(int i=0;i<m_root.num;i++)
		expand_retract_unselect_rec(m_root[i],2);
}

void pGUITreeControl::get_name(const unsigned int id,pString& name)
{
	name="";
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
				name=item->m_text;
}

int pGUITreeControl::get_cookie(const unsigned int id)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
				return item->m_cookie;
			else
				return INVALID_COOKIE;

	return INVALID_COOKIE;
}

void pGUITreeControl::set_name(const unsigned int id,const pString name)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
				item->m_text=name;
}

void pGUITreeControl::set_cookie(const unsigned int id,const int cookie)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
				item->m_cookie=cookie;
}

bool pGUITreeControl::has_child(const unsigned int id)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item)
				return (item->m_child.num>0);
			else
				return false;

	return false;
}

unsigned int pGUITreeControl::get_first_child(const unsigned int id)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(item && item->m_child.num && item->m_child[0])
				return item->m_child[0]->m_id;
			else
				return ROOT_NODE_ID;
				

	return ROOT_NODE_ID;
}

unsigned int pGUITreeControl::get_next_child(const unsigned int id,const unsigned int child)
{
	pGUITreeControlItem *item=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
		{
			if(item && item->m_child.num)
			{
				for(int j=0;j<item->m_child.num;j++)
					if(item->m_child[j]->m_id==child)
					{
						if(item->m_child.num>j+1 && item->m_child[j+1])
							return item->m_child[j+1]->m_id;
						else
							return ROOT_NODE_ID;
					}
			}
			else
				return ROOT_NODE_ID;
		}
				

	return ROOT_NODE_ID;
}

unsigned int pGUITreeControl::get_node_at(const int x, const int y)
{
	unsigned int id=ROOT_NODE_ID;
	int cury=m_global_y;

	if(is_inside(x,y))
		for(int i=0;i<m_root.num;i++)
		{
			id=get_node_at_rec(x,y,cury,m_root[i]);
			if(id!=ROOT_NODE_ID)
				break;
		}

	return id;
}

void pGUITreeControl::move_node(const unsigned int id,const unsigned int new_parent_id)
{
	pGUITreeControlItem *item=0;
	pGUITreeControlItem *new_parent=0;
	pGUITreeControlItem *foo=0;

	for(int i=0;i<m_root.num;i++)
		if(find_node_rec(m_root[i],item,id))
			if(new_parent_id==ROOT_NODE_ID)
			{
				remove_node(item);
				add_node(item,0);
			}
			else
			{
				for(int j=0;j<m_root.num;j++)
					if(find_node_rec(m_root[j],new_parent,new_parent_id))
					{
						// test if new_parent is in item's sub-tree
						if(find_node_rec(item,foo,new_parent_id))
							return;
						
						remove_node(item);
						add_node(item,new_parent);
					}
			}
}

void pGUITreeControl::add_node(pGUITreeControlItem *item,pGUITreeControlItem *parent)
{
	if(parent==0)
	{
		m_root.add(item);
		item->m_parent=0;
	}
	else
	{
		parent->m_child.add(item);
		item->m_parent=parent;
	}
}

void pGUITreeControl::remove_node(pGUITreeControlItem *item)
{
	if(item)
	{
		if(item->m_parent)
		{
			for(int j=0;j<item->m_parent->m_child.num;j++)
				if(item->m_parent->m_child[j]==item)
					item->m_parent->m_child.remove(j);
		}
		else
			for(int j=0;j<m_root.num;j++)
				if(m_root[j]==item)
					m_root.remove(j);
	}
}

int pGUITreeControl::find_node_rec(pGUITreeControlItem *cur_item,pGUITreeControlItem *&item,const unsigned int id)
{
	if(cur_item==0)
		return 0;
	
	if(cur_item->m_id==id)
	{
		item=cur_item;
		return 1;
	}

	for(int i=0;i<cur_item->m_child.num;i++)
		if(find_node_rec(cur_item->m_child[i],item,id))
			return 1;

	return 0;
}

void pGUITreeControl::expand_retract_unselect_rec(pGUITreeControlItem *cur_item,const int mode)
{
	if(cur_item==0)
		return;
	
	if(mode<2)
		cur_item->m_state=mode==0?NODE_STATE_EXPANDED:NODE_STATE_NORMAL;
	else
		cur_item->m_sel_state=NODE_SEL_STATE_NORMAL;

	for(int i=0;i<cur_item->m_child.num;i++)
		expand_retract_unselect_rec(cur_item->m_child[i],mode);
}

unsigned int pGUITreeControl::get_node_at_rec(const int x, const int y,int &cury,pGUITreeControlItem *cur_item)
{
	if(cur_item)
	{
		cury+=m_item_height;
		if(y<=cury)
			return cur_item->m_id;

		if(cur_item->m_state==NODE_STATE_EXPANDED)
		{
			unsigned int id=ROOT_NODE_ID;
			for(int i=0;i<cur_item->m_child.num;i++)
			{
				id=get_node_at_rec(x,y,cury,cur_item->m_child[i]);
				if(id!=ROOT_NODE_ID)
					return id;
			}
		}
	}

	return ROOT_NODE_ID;
}

#endif
