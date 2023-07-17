#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUICheckBox::init()
{
	select_curr_icon();
	//calc_tex_coords();
}

void pGUICheckBox::select_curr_icon()
{
	switch(m_state)
	{
		case 0: m_curr_icon=m_icon_unchecked; break;
		case 1: m_curr_icon=m_icon_checked; break;
		case 2: m_curr_icon=m_icon_indeterminate; break;
	}
}

void pGUICheckBox::calc_tex_coords()
{
	if(m_icon_grid.m_grid_pic!=-1&&m_curr_icon>=0)
		m_icon_grid.get_icon_tex_coord(m_curr_icon,m_u0,m_v0,m_u1,m_v1);
}

void pGUICheckBox::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	calc_tex_coords();

	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	// draw background
	glColor4fv(&m_color.x);
	g_render->sel_tex(m_tex);
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

	// draw box
	int boxy1=m_border_size;
	int boxy2=m_height-m_border_size;
	
	g_render->sel_tex(m_icon_grid.m_grid_pic);
#ifdef P_TONY
	glColor4f(m_color.x,m_color.y,m_color.z,1.0f);
#endif
	//*glBegin(GL_QUADS);
	glTexCoord2f(m_u0,m_v1);
	glVertex2i(boxy1,boxy1);
	glTexCoord2f(m_u0,m_v0);
	glVertex2i(boxy1,boxy2);
	glTexCoord2f(m_u1,m_v0);
	glVertex2i(boxy2,boxy2);
	glTexCoord2f(m_u1,m_v1);
	glVertex2i(boxy2,boxy1);
	//*glEnd();

	glPopMatrix();

	// calculate text position
	int textx=boxy2+m_text_spacing;
	int texty=(m_height/2)-(m_font_size/2);

	// draw text
	int oldfont=g_render->sel_font(m_font);

	glColor4fv(&m_text_color.x);
	g_render->draw_text(m_global_x+textx,m_global_y+texty,(const char *)m_text,m_font_size);
	
	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUICheckBox::process_mouse_input(pGUIEventHandler *event_handler)
{
	if(	is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y) &&
		g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK	)
	{
		if(m_state==0) // if unchecked
			m_state=1; // set checked
		else
			m_state=0; // else, set unchecked

		if(event_handler)
			event_handler->event_handler(P_GUI_MSG_CHECKBOXCLICK,m_id,0,0);

		select_curr_icon();
		calc_tex_coords();
	}
}

int pGUICheckBox::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->comment="Background transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 2:
			pd->type='s';
			pd->data=&m_text;
			pd->name="text";
			pd->comment="Check box text";
			break;
		case 3:
			pd->type='c';
			pd->data=&m_text_color;
			pd->name="text_color";
			pd->comment="Face color for the text being drawn";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_text_color.w;
			pd->name="text_transp";
			pd->comment="Transparency of the text being drawn (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_state;
			pd->name="state";
			pd->comment="Check box state|Unchecked|Checked|Indeterminate";
		break;
		case 6:
			pd->type='i';
			pd->data=&m_border_size;
			pd->name="border_size";
			pd->comment="Border size for box drawing";
		break;
		case 7:
			pd->type='i';
			pd->data=&m_text_spacing;
			pd->name="text_spacing";
			pd->comment="Distance in pixels between the box and the text";
		break;
		case 8:
			pd->type='p';
			pd->data=&m_tex;
			pd->name="tex";
			pd->comment="Backgroung texture";
			break;
		case 9:
			pd->type='p';
			pd->data=&m_icon_grid.m_grid_pic;
			pd->name="icons";
			pd->comment="Icon grid texture for the check box";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_icon_grid.m_icon_width;
			pd->name="icon_width";
			pd->comment="Width of all icons in icon grid texture";
			break;
		case 11:
			pd->type='i';
			pd->data=&m_icon_grid.m_icon_height;
			pd->name="icon_height";
			pd->comment="Height of all icons in icon grid texture";
			break;
		case 12:
			pd->type='i';
			pd->data=&m_icon_unchecked;
			pd->name="icon_unchecked";
			pd->comment="Icon index for the unchecked state of the check box";
			break;
		case 13:
			pd->type='i';
			pd->data=&m_icon_checked;
			pd->name="icon_checked";
			pd->comment="Icon index for the checked state of the check box";
			break;
		case 14:
			pd->type='i';
			pd->data=&m_icon_indeterminate;
			pd->name="icon_indeterminate";
			pd->comment="Icon index for the indeterminate state of the check box";
			break;
		case 15:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Font file for the check box text";
			break;
		case 16:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Font size for the check box text";
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

	return 23;
}

void pGUICheckBox::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 9:case 10:case 11:
			calc_tex_coords();
		break;

		case 5:case 12:case 13:case 14:
			select_curr_icon();
			calc_tex_coords();
		break;
	}
}

#endif
