#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIButton::init()
{
	m_start_time=g_gomanager->m_time;
	//update_num_frames();
	select_curr_icon();
	//calc_tex_coords();
}

void pGUIButton::update_num_frames()
{
	if (m_background_tex!=-1)
	{
		if(g_render->pic[m_background_tex]->sx>g_render->pic[m_background_tex]->sy)
			m_num_frames=g_render->pic[m_background_tex]->sx/g_render->pic[m_background_tex]->sy;
		else 
			m_num_frames=1;
	}
	else
		m_num_frames=0;
}

void pGUIButton::select_curr_icon()
{
	switch(m_state)
	{
		case 0: m_curr_icon=m_icon_disabled; break;
		case 1: m_curr_icon=m_icon_enabled; break;
		case 2: m_curr_icon=m_icon_hover; break;
		case 3: m_curr_icon=m_icon_pressed; break;
	}
}

void pGUIButton::calc_tex_coords()
{
	if(m_icon_grid.m_grid_pic!=-1&&m_curr_icon>=0)
		m_icon_grid.get_icon_tex_coord(m_curr_icon,m_u0,m_v0,m_u1,m_v1);
}

void pGUIButton::process_mouse_input(pGUIEventHandler *event_handler)
{
	int push=0;
	
	if(m_state!=0) // m_state!=DISABLED
	{
		if(is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y))
		{
			if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK || g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
				m_state=3; // m_state=PRESSED
			else if(m_state!=3) // m_state!=PRESSED
				m_state=2; // m_state=HOVER

			if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTUNCLICK)
			{
				if(m_state==3) // m_state==PRESSED
					push=1;
				m_state=2; // m_state=HOVER
			}
		}
		else if(m_state==2)
			m_state=1; // m_state=ENABLED

		if(push && event_handler)
			event_handler->event_handler(P_GUI_MSG_BUTTONCLICK,m_id,0,0);
		
		select_curr_icon();
		calc_tex_coords();
	}
}

void pGUIButton::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	calc_tex_coords();

	// if necessary, do animation on texture coordinates
	if(m_frame_rate>0.0f)
		update_num_frames();
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

	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	// background button
	glColor4fv(&m_color.x);
	if(m_background_tex==-1 && m_icon_grid.m_grid_pic==-1) // no bg or icon grid, draw a rect
	{
		g_render->sel_tex(-1);
		//*glBegin(GL_QUADS);
		glVertex2i(0,0);
		glVertex2i(0,m_height);
		glVertex2i(m_width,m_height);
		glVertex2i(m_width,0);
		//*glEnd();
	}
	else
	{
		if(m_background_tex!=-1)
		{
			glColor4fv(&m_color.x);
			g_render->sel_tex(m_background_tex);
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
		if(m_icon_grid.m_grid_pic!=-1)
		{
			g_render->sel_tex(m_icon_grid.m_grid_pic);
			//*glBegin(GL_QUADS);
			glTexCoord2f(m_u0,m_v1);
			glVertex2i(0,0);
			glTexCoord2f(m_u0,m_v0);
			glVertex2i(0,m_height);
			glTexCoord2f(m_u1,m_v0);
			glVertex2i(m_width,m_height);
			glTexCoord2f(m_u1,m_v1);
			glVertex2i(m_width,0);
			//*glEnd();
		}
	}

	// calculate text position
	int text_size=g_render->get_text_size((const char *)m_text,m_font_size);
	int text_x,text_y=(int)((m_height-m_font_size)/2.0f);
	if(m_text_align==2) // center
		text_x=(int)(m_width/2.0f);
	else if(m_text_align!=0) // right
		text_x=m_width-text_size-m_text_border_size;
	else // left
		text_x=m_text_border_size;

	// calculate second icon position
	if(m_icon2_tex!=-1)
	{
		float center_text;
		float icon2_x_min=0.0f;
		float icon2_x_max;
		float icon2_y_min=(m_height-m_font_size)*0.5f;
		float icon2_y_max=icon2_y_min+m_font_size;
		if(m_text_align==2) // center
		{
			center_text=text_x+1.0f;
			if(m_icon2_align==2) // center
				icon2_x_min=center_text-m_font_size*0.5f;
			else if(m_icon2_align==0) // left
				icon2_x_min=center_text-m_font_size-text_size*0.5f-m_text_border_size;
			else // right
				icon2_x_min=center_text+text_size*0.5f+m_text_border_size;
		}
		else if(m_text_align==0) // left
		{
			center_text=text_x+text_size*0.5f;
			if(m_icon2_align==2) // center
				icon2_x_min=center_text-m_font_size*0.5f;
			else if(m_icon2_align==0) // left
				icon2_x_min=center_text-m_font_size-text_size*0.5f-m_text_border_size;
			else // right
				icon2_x_min=center_text+text_size*0.5f+m_text_border_size+1;

			if(icon2_x_min<0)
			{
				text_x+=(int)(-icon2_x_min-1.0f);
				icon2_x_min=0;
			}
		}
		else // right
		{
			center_text=text_x+text_size*0.5f;
			if(m_icon2_align==2) // center
				icon2_x_min=center_text+1-m_font_size*0.5f;
			else if(m_icon2_align==0) // left
				icon2_x_min=center_text-m_font_size-text_size*0.5f-m_text_border_size;
			else // right
				icon2_x_min=center_text+1+text_size*0.5f+m_text_border_size;

			if(icon2_x_min+m_font_size>m_width)
			{
				float t=icon2_x_min+m_font_size-m_width;
				text_x-=(int)t;
				icon2_x_min-=t;
			}
		}
		icon2_x_max=icon2_x_min+m_font_size;
		
		// draw second icon
		glColor4f(1.0f,1.0f,1.0f,1.0f);
		g_render->sel_tex(m_icon2_tex);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2f(icon2_x_min,icon2_y_min);
		glTexCoord2f(0.0f,0.0f);
		glVertex2f(icon2_x_min,icon2_y_max);
		glTexCoord2f(1.0f,0.0f);
		glVertex2f(icon2_x_max,icon2_y_max);
		glTexCoord2f(1.0f,1.0f);
		glVertex2f(icon2_x_max,icon2_y_min);
		//*glEnd();
	}

	glPopMatrix();

	// draw text
	int oldfont=g_render->sel_font(m_font);

	glColor4fv(&m_text_color.x);
	if(m_text_align==2) // center
		g_render->draw_text_center(m_global_x+text_x,m_global_y+text_y,(const char *)m_text,m_font_size);
	else
		g_render->draw_text(m_global_x+text_x,m_global_y+text_y,(const char *)m_text,m_font_size);
	
	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIButton::on_kill_mouse()
{
	if(m_state==2 || m_state==3)
	{
		m_state=1;
		select_curr_icon();
		calc_tex_coords();
	}
}

int pGUIButton::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="GUI object transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 2:
			pd->type='s';
			pd->data=&m_text;
			pd->name="text";
			pd->comment="GUI object general-purpose text";
			break;
		case 3:
			pd->type='i';
			pd->data=&m_text_align;
			pd->name="text_align";
			pd->comment="Text alignment|Left|Right|Center";
			break;
		case 4:
			pd->type='i';
			pd->data=&m_text_border_size;
			pd->name="text_border_size";
			pd->comment="Text border size in screen pixels";
			break;
		case 5:
			pd->type='c';
			pd->data=&m_text_color;
			pd->name="text_color";
			pd->comment="Face color for the text being drawn";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_text_color.w;
			pd->name="text_transp";
			pd->comment="Transparency of the text being drawn (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 7:
			pd->type='p';
			pd->data=&m_icon_grid.m_grid_pic;
			pd->name="tex";
			pd->comment="Icon grid texture for the button";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_icon_grid.m_icon_width;
			pd->name="icon_width";
			pd->comment="Width of all icons into icon grid texture";
			break;
		case 9:
			pd->type='i';
			pd->data=&m_icon_grid.m_icon_height;
			pd->name="icon_height";
			pd->comment="Height of all icons into icon grid texture";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_icon_disabled;
			pd->name="icon_disabled";
			pd->comment="Icon index for the disabled state of the button";
			break;
		case 11:
			pd->type='i';
			pd->data=&m_icon_enabled;
			pd->name="icon_enabled";
			pd->comment="Icon index for the enabled state of the button";
			break;
		case 12:
			pd->type='i';
			pd->data=&m_icon_hover;
			pd->name="icon_hover";
			pd->comment="Icon index for the hover state of the button";
			break;
		case 13:
			pd->type='i';
			pd->data=&m_icon_pressed;
			pd->name="icon_pressed";
			pd->comment="Icon index for the pressed state of the button";
			break;
		case 14:
			pd->type='i';
			pd->data=&m_state;
			pd->name="state";
			pd->comment="Button state|Disabled|Enabled|Hover|Pressed";
			break;
		case 15:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Font file for the button text";
			break;
		case 16:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Font size for the button text";
			break;
		case 17:
			pd->type='i';
			pd->data=&m_icon2_align;
			pd->name="icon2_align";
			pd->comment="Icon2 alignment|Left|Right|Center";
			break;
		case 18:
			pd->type='p';
			pd->data=&m_icon2_tex;
			pd->name="icon2_tex";
			pd->comment="Icon2 texture";
			break;
		case 19:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 20:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 21:
			pd->type='b';
			pd->data=&m_default;
			pd->name="default";
			pd->comment="Default button flag";
			break;
		case 22:
			pd->type='b';
			pd->data=&m_cancel;
			pd->name="cancel";
			pd->comment="Cancel button flag";
			break;
		case 23:
			pd->type='b';
			pd->data=&m_focusable;
			pd->name="focusable";
			pd->comment="Focusable flag";
			break;
		case 24:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 25:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 26:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 27:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 28:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 29:
			pd->type='p';
			pd->data=&m_background_tex;
			pd->name="bg_tex";
			pd->comment="Background texture for button";
			break;
		case 30:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate to display animation maps";
			break;
		case 31:
			pd->type='i';
			pd->data=&m_command;
			pd->name="command";
			pd->comment="Animation command|Play|Play Once|Pause|Stop";
			break;
		case 32:
			pd->type='i';
			pd->data=&m_current_frame;
			pd->name="current_frame";
			pd->comment="Current frame in the animation. It can be edited only if";
			            " m_command equals to Stop";
			break;
		case 33:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 34;
}

void pGUIButton::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 7:case 8:case 9:
			calc_tex_coords();
		break;

		case 10:case 11:case 12:case 13:case 14:
			select_curr_icon();
			calc_tex_coords();
		break;

		case 29:
			update_num_frames();
		break;

		case 31:
			if(m_command!=CMD_PAUSE)
				m_start_time=g_gomanager->m_time;
		break;
	}
}

#endif
