#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIListControl::init()
{
	if(m_col_count>0)
		on_pos_parameter_change(P_GUINUMDEFAULTPARAM+25);
}

void pGUIListControl::draw(pRect& scissor_rect)
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

	int cx=0,cy=0;
	if(m_draw_columns)
	{
		// draw column headers background
		
		//*glBegin(GL_QUADS);
		for(i=0;i<m_col.num;i++)
		{
			glColor4fv(&m_color_column.x);
			g_render->sel_tex(m_tex_column);

			glTexCoord2f(0.0f,1.0f);
			glVertex2i(cx,cy);
			glTexCoord2f(0.0f,0.0f);
			glVertex2i(cx,cy+m_item_height);
			glTexCoord2f(1.0f,0.0f);
			glVertex2i(cx+m_col[i]->m_width,cy+m_item_height);
			glTexCoord2f(1.0f,1.0f);
			glVertex2i(cx+m_col[i]->m_width,cy);

			cx+=m_col[i]->m_width;
			cy=0;
		}
		//*glEnd();

		// draw column headers text
		int tx;
		cx=0;

		glColor4fv(&m_color_column_text.x);
		for(i=0;i<m_col.num;i++)
		{
			if(m_col[i]->m_align==COL_ALIGN_CENTER)
			{
				tx=cx+(m_col[i]->m_width/2);
				g_render->draw_text_center(tx,m_item_height/2-m_font_size/2,(const char *)m_col[i]->m_name,m_font_size);
			}
			else
			{
				if(m_col[i]->m_align==COL_ALIGN_LEFT)
					tx=cx+m_column_text_border_size;
				else
					tx=cx+m_col[i]->m_width-g_render->get_text_size(m_col[i]->m_name,m_font_size)-m_column_text_border_size-1;

				g_render->draw_text(tx,m_item_height/2-m_font_size/2,(const char *)m_col[i]->m_name,m_font_size);
			}

			cx+=m_col[i]->m_width;
		}
	}

	// draw items background
	cx=0;

	for(i=0;i<m_col.num;i++)
	{
		if(m_draw_columns)
			cy=m_item_height;
		else
			cy=0;

		for(int j=0;j<m_item_count;j++)
		{
			if(m_sel_state[j]==ITEM_SEL_STATE_NORMAL)
			{
				glColor4fv(&m_custom_color_item[j].x);
				g_render->sel_tex(m_tex_item);
			}
			else
			{
				glColor4fv(&m_custom_color_item_sel[j].x);
				g_render->sel_tex(m_tex_item_sel);
			}

			//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f);
			glVertex2i(cx,cy);
			glTexCoord2f(0.0f,0.0f);
			glVertex2i(cx,cy+m_item_height);
			glTexCoord2f(1.0f,0.0f);
			glVertex2i(cx+m_col[i]->m_width,cy+m_item_height);
			glTexCoord2f(1.0f,1.0f);
			glVertex2i(cx+m_col[i]->m_width,cy);
			//*glEnd();

			cy+=m_item_height;
		}

		cx+=m_col[i]->m_width;
	}

	// draw items text
	cx=0;

	pGUIMultilineText *t;
	for(i=0;i<m_col.num;i++)
	{
		if(m_draw_columns)
			cy=m_item_height;
		else
			cy=0;

		for(int j=0;j<m_item_count;j++)
		{
			t=m_col[i]->m_text[j];
			t->m_global_x=cx;
			t->m_global_y=cy;
			t->m_width=m_col[i]->m_width;
			t->m_height=m_item_height;
			t->process_lines();
			if(m_sel_state[j]==ITEM_SEL_STATE_SELECTED)
				t->m_default_text_color=m_custom_color_item_sel_text[j];
			else
				t->m_default_text_color=m_custom_color_item_text[j];
			glColor4fv(&t->m_default_text_color.x);
			t->draw_multiline(0);

			cy+=m_item_height;
		}

		cx+=m_col[i]->m_width;
	}

	// draw grid lines
	if(m_draw_grid_lines)
	{
		g_render->sel_tex(-1);
		glColor4fv(&m_color_grid_lines.x);

		//*glBegin(GL_LINES);
		// vertical lines
		if(m_draw_columns)
			cy=m_item_height*(m_item_count+1);
		else
			cy=m_item_height*m_item_count;
		cx=0;
		for(i=0;i<=m_col.num;i++)
		{
			glVertex2i(cx,0);
			glVertex2i(cx,cy);

			if(i<m_col.num)
				cx+=m_col[i]->m_width;
		}
		// horizontal lines
		cy=0;
		for(i=0;i<=m_item_count+m_draw_columns;i++)
		{
			glVertex2i(0,cy);
			glVertex2i(cx,cy);
			cy+=m_item_height;
		}
		
		//*glEnd();
	}
	
	glPopMatrix();

	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIListControl::process_mouse_input(pGUIEventHandler *event_handler)
{
	if(	is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y) &&
		g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK)
	{
		int cx=m_global_x;
		int i;

		for(i=0;i<m_col.num;i++)
			cx+=m_col[i]->m_width;
		
		if(g_gomanager->m_mouse_x<=cx)
		{
			int cy=m_global_y;
			int selchange=0;

			if(m_draw_columns)
				cy+=m_item_height;

			for(i=0;i<=m_item_count;i++)
			{
				if(cy>g_gomanager->m_mouse_y)
				{
					if(m_sel_mode==LIST_SEL_MODE_MULTI && g_gomanager->m_modkeys&KMOD_SHIFT)
					{
						if(m_last_sel_item==-1)
							m_last_sel_item=0;

						if(!(g_gomanager->m_modkeys&KMOD_CTRL))
							unselect_all();

						if(m_last_sel_item>i-1)
							for(int j=i-1;j<=m_last_sel_item;j++)
								m_sel_state[j]=ITEM_SEL_STATE_SELECTED;
						else
							for(int j=m_last_sel_item;j<=i-1;j++)
								m_sel_state[j]=ITEM_SEL_STATE_SELECTED;
					}
					else if(m_sel_mode==LIST_SEL_MODE_MULTI && g_gomanager->m_modkeys&KMOD_CTRL)
					{
						m_sel_state[i-1]=!m_sel_state[i-1];
						if(m_sel_state[i-1]==ITEM_SEL_STATE_SELECTED)
							m_last_sel_item=i-1;
					}
					else
					{
						unselect_all();
						m_sel_state[i-1]=ITEM_SEL_STATE_SELECTED;
						m_last_sel_item=i-1;
					}

					selchange=1;

					break;
				}

				cy+=m_item_height;
			}

			pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
			if(eh && selchange)
				eh->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
		}
	}
}

int pGUIListControl::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='i';
			pd->data=&m_item_height;
			pd->name="item_height";
			pd->comment="Fixed height for each item, in pixels";
			break;
		case 3:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color_bg";
			pd->comment="Background color";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp_bg";
			pd->comment="Background transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 5:
			pd->type='p';
			pd->data=&m_tex_bg;
			pd->name="tex_bg";
			pd->comment="Texture for the list control background";
			break;
		case 6:
			pd->type='c';
			pd->data=&m_color_item;
			pd->name="color_item";
			pd->comment="Default background color for the item";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_color_item.w;
			pd->name="transp_item";
			pd->comment="Default background transparency for the item (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 8:
			pd->type='p';
			pd->data=&m_tex_item;
			pd->name="tex_item";
			pd->comment="Texture for the item background";
			break;
		case 9:
			pd->type='c';
			pd->data=&m_color_item_sel;
			pd->name="color_item_sel";
			pd->comment="Default background color for the selected item";
			break;
		case 10:
			pd->type='f';
			pd->data=&m_color_item_sel.w;
			pd->name="transp_item_sel";
			pd->comment="Default background transparency for the selected item (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 11:
			pd->type='p';
			pd->data=&m_tex_item_sel;
			pd->name="tex_item_sel";
			pd->comment="Texture for the selected item background";
			break;
		case 12:
			pd->type='c';
			pd->data=&m_color_item_text;
			pd->name="color_item_text";
			pd->comment="Default face color for the item text";
			break;
		case 13:
			pd->type='f';
			pd->data=&m_color_item_text.w;
			pd->name="transp_item_text";
			pd->comment="Default face transparency for the item text (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 14:
			pd->type='c';
			pd->data=&m_color_item_sel_text;
			pd->name="color_item_sel_text";
			pd->comment="Default face color for the selected item text";
			break;
		case 15:
			pd->type='f';
			pd->data=&m_color_item_sel_text.w;
			pd->name="transp_item_sel_text";
			pd->comment="Default face transparency for the selected item text (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 16:
			pd->type='b';
			pd->data=&m_draw_columns;
			pd->name="draw_columns";
			pd->comment="Columns drawing flag";
			break;
		case 17:
			pd->type='i';
			pd->data=&m_column_text_border_size;
			pd->name="column_text_border_size";
			pd->comment="Column text border size in pixels";
			break;
		case 18:
			pd->type='b';
			pd->data=&m_draw_grid_lines;
			pd->name="draw_grid_lines";
			pd->comment="Grid lines drawing flag";
			break;
		case 19:
			pd->type='c';
			pd->data=&m_color_column;
			pd->name="color_column";
			pd->comment="Column color";
			break;
		case 20:
			pd->type='f';
			pd->data=&m_color_column.w;
			pd->name="trasnp_column";
			pd->comment="Column transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 21:
			pd->type='c';
			pd->data=&m_color_column_text;
			pd->name="color_column_text";
			pd->comment="Face color for the column text";
			break;
		case 22:
			pd->type='f';
			pd->data=&m_color_column_text.w;
			pd->name="transp_column_text";
			pd->comment="Face transparency for the column text (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 23:
			pd->type='p';
			pd->data=&m_tex_column;
			pd->name="tex_column";
			pd->comment="Column texture";
			break;
		case 24:
			pd->type='c';
			pd->data=&m_color_grid_lines;
			pd->name="color_grid_lines";
			pd->comment="Grid lines color";
			break;
		case 25:
			pd->type='i';
			pd->data=&m_col_count;
			pd->name="num_columns";
			pd->comment="Initial number of columns";
			break;
		case 26:
			pd->type='i';
			pd->data=&m_sel_mode;
			pd->name="sel_mode";
			pd->comment="Selection mode|Single selection|Multi-selection";
			break;
		case 27:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 28:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 29:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 30:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 31:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 32:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 33;
}

void pGUIListControl::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 25: // col_count
		{
			if(m_col_count<0)
				return;
			
			if(m_col.num>m_col_count)
				while(!(m_col.num==m_col_count))
					remove_column(m_col.num-1);
			else if(m_col.num<m_col_count)
			{
				int n=m_col_count-m_col.num;
				for(int ib=0;ib<n;ib++)
				{
					pString str;
					str.format("col%i",m_col.num);
					insert_column((const char *)str);
				}
			}
		}
		break;
		case 26: // sel_mode
		{
			if(m_sel_mode==LIST_SEL_MODE_SINGLE)
				unselect_all();
		}
		break;
	}
}

// column operations
void pGUIListControl::insert_column(const char *name,const int width,const int align,const int pos)
{
	pGUIListControlColumn *c=new pGUIListControlColumn(name,width,align);

	pGUIMultilineText *t;
	for(int i=0;i<m_item_count;i++)
	{
		t=new pGUIMultilineText;
		t->m_text_horz_align=align;
		t->m_text_vert_align=2;
		c->m_text.add(t);
	}

	if(pos==-1)
		m_col.add(c);
	else
		m_col.insert(c,pos);
}

void pGUIListControl::remove_column(const int pos)
{
	if(pos<0 || pos>=m_col.num)
		return;

	pGUIListControlColumn *c=m_col[pos];
	m_col.remove(pos);
	delete c;
}

void pGUIListControl::remove_column(const char *name)
{
	pGUIListControlColumn *c;
	
	for(int i=0;i<m_col.num;i++)
		if(m_col[i]->m_name.compare(name)==0)
		{
			c=m_col[i];
			m_col.remove(i);
			delete c;
			break;
		}
}

void pGUIListControl::set_column_name(int pos,const char *name)
{
	if(pos<0 || pos>=m_col.num)
		return;

	m_col[pos]->m_name=name;
}

void pGUIListControl::set_column_width(int pos,const int width)
{
	if(pos<0 || pos>=m_col.num)
		return;

	m_col[pos]->m_width=width;
}

void pGUIListControl::set_column_align(int pos,const int align)
{
	if(pos<0 || pos>=m_col.num)
		return;

	m_col[pos]->m_align=align;
	for(int i=0;i<m_col[pos]->m_text.num;i++)
		m_col[pos]->m_text[i]->m_text_horz_align=align;
}

void pGUIListControl::get_column_name(int pos,char *name)
{
	if(pos<0 || pos>=m_col.num)
		return;
	
	strcpy(name,(const char *)m_col[pos]->m_name);
}

int pGUIListControl::get_column_width(int pos)
{
	if(pos<0 || pos>=m_col.num)
		return -1;
	
	return m_col[pos]->m_width;
}

int pGUIListControl::get_column_align(int pos)
{
	if(pos<0 || pos>=m_col.num)
		return -1;
	
	return m_col[pos]->m_align;
}

int pGUIListControl::get_column_count()
{
	return m_col.num;
}

// item operations
void pGUIListControl::reset_content()
{
	for(int i=0;i<m_col.num;i++)
	{
		pGUIMultilineText *t;
		for(int j=m_col[i]->m_text.num-1;j>=0;j--)
		{
			t=m_col[i]->m_text[j];
			m_col[i]->m_text.remove(j);
			delete t;
		}
	}

	m_item_count=0;
	m_sel_state.clear();

	m_last_sel_item=-1;

	m_custom_color_item.clear();
	m_custom_color_item_sel.clear();
	m_custom_color_item_text.clear();
	m_custom_color_item_sel_text.clear();
}

void pGUIListControl::insert_item(const char *text,const int pos)
{
	pGUIListControlColumn *c;
	pGUIMultilineText *t;
	
	for(int i=0;i<m_col.num;i++)
	{
		c=m_col[i];

		t=new pGUIMultilineText;
		t->m_text_horz_align=c->m_align;
		t->m_text_vert_align=2;
		if(i==0)
			t->m_text=text;
		else
			t->m_text="";

		t->m_width=c->m_width;
		t->process_lines();

		if(pos==-1)
			c->m_text.add(t);
		else
			c->m_text.insert(t,pos);
	}

	if(pos==-1)
	{
		m_sel_state.add(ITEM_SEL_STATE_NORMAL);

		m_custom_color_item.add(m_color_item);
		m_custom_color_item_sel.add(m_color_item_sel);
		m_custom_color_item_text.add(m_color_item_text);
		m_custom_color_item_sel_text.add(m_color_item_sel_text);
	}
	else
	{
		m_sel_state.insert(ITEM_SEL_STATE_NORMAL,pos);

		if(m_last_sel_item>pos)
			m_last_sel_item++;

		m_custom_color_item.insert(m_color_item,pos);
		m_custom_color_item_sel.insert(m_color_item_sel,pos);
		m_custom_color_item_text.insert(m_color_item_text,pos);
		m_custom_color_item_sel_text.insert(m_color_item_sel_text,pos);
	}

	m_item_count++;
}

void pGUIListControl::remove_item(const int pos)
{
	if(m_item_count<=0 || pos>=m_item_count)
		return;
	
	if(pos<0)
	{
		for(int i=0;i<m_col.num;i++)
			m_col[i]->m_text.remove(m_col[i]->m_text.num-1);

		m_sel_state.remove(m_sel_state.num-1);

		if(m_last_sel_item==m_col.num)
			m_last_sel_item=-1;

		m_custom_color_item.remove(m_custom_color_item.num-1);
		m_custom_color_item_sel.remove(m_custom_color_item_sel.num-1);
		m_custom_color_item_text.remove(m_custom_color_item_text.num-1);
		m_custom_color_item_sel_text.remove(m_custom_color_item_sel_text.num-1);
	}
	else
	{
		for(int i=0;i<m_col.num;i++)
			m_col[i]->m_text.remove(pos);

		m_sel_state.remove(pos);

		if(m_last_sel_item==pos)
			m_last_sel_item=-1;
		else if(m_last_sel_item>pos)
			m_last_sel_item--;

		m_custom_color_item.remove(pos);
		m_custom_color_item_sel.remove(pos);
		m_custom_color_item_text.remove(pos);
		m_custom_color_item_sel_text.remove(pos);
	}

	m_item_count--;
}

void pGUIListControl::set_item_text(const char *text,const int item,const int column)
{
	if(column<0 || column>=m_col.num || item<0 || item>=m_item_count)
		return;

	m_col[column]->m_text[item]->m_text=text;
	m_col[column]->m_text[item]->process_lines();
}

void pGUIListControl::get_item_text(char *text,const int item,const int column)
{
	if(column<0 || column>=m_col.num || item<0 || item>=m_item_count)
	{
		strcpy(text,"");
		return;
	}

	strcpy(text,(const char *)m_col[column]->m_text[item]->m_text);
}

void pGUIListControl::set_item_colors(const pVector color_bg,const pVector color_text,const pVector color_bg_sel,const pVector color_text_sel,const int item)
{
	if(item<0 || item>=m_item_count)
		return;

	m_custom_color_item[item]=color_bg;
	m_custom_color_item_text[item]=color_text;
	m_custom_color_item_sel[item]=color_bg_sel;
	m_custom_color_item_sel_text[item]=color_text_sel;
}

void pGUIListControl::get_item_colors(pVector &color_bg,pVector &color_text,pVector &color_bg_sel,pVector &color_text_sel,const int item)
{
	if(item<0 || item>=m_item_count)
		return;

	color_bg=m_custom_color_item[item];
	color_text=m_custom_color_item_text[item];
	color_bg_sel=m_custom_color_item_sel[item];
	color_text_sel=m_custom_color_item_sel_text[item];
}

int pGUIListControl::get_item_count()
{
	return m_item_count;
}

// selection
int pGUIListControl::get_first_selected_item()
{
	return get_next_selected_item(-1);
}

int pGUIListControl::get_next_selected_item(const int cur_item)
{
	for(int i=cur_item+1;i<m_item_count;i++)
		if(m_sel_state[i]==ITEM_SEL_STATE_SELECTED)
			return i;
	
	return -1;
}

void pGUIListControl::select_item(const int item)
{
	if(item<0 || item>=m_item_count)
		return;

	if(m_sel_mode==LIST_SEL_MODE_SINGLE)
		unselect_all();

	m_sel_state[item]=ITEM_SEL_STATE_SELECTED;

	pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
	if(eh)
		eh->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
}

void pGUIListControl::unselect_item(const int item)
{
	if(item<0 || item>=m_item_count)
		return;

	m_sel_state[item]=ITEM_SEL_STATE_NORMAL;

	pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
	if(eh)
		eh->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
}

void pGUIListControl::select_all()
{
	if(m_sel_mode==LIST_SEL_MODE_MULTI)
		for(int i=0;i<m_item_count;i++)
			m_sel_state[i]=ITEM_SEL_STATE_SELECTED;

	pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
	if(eh)
		eh->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
}

void pGUIListControl::unselect_all()
{
	for(int i=0;i<m_item_count;i++)
		m_sel_state[i]=ITEM_SEL_STATE_NORMAL;

	pGUIEventHandler *eh=g_gomanager->get_event_handler(m_id);
	if(eh)
		eh->event_handler(P_GUI_MSG_SELCHANGE,m_id,0,0);
}

#endif
