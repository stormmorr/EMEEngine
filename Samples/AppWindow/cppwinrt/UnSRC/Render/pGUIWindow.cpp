#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIWindow::update_num_frames()
{
	if (m_tex_bg!=-1)
	{
		if(g_render->pic[m_tex_bg]->sx>g_render->pic[m_tex_bg]->sy)
			m_num_frames=g_render->pic[m_tex_bg]->sx/g_render->pic[m_tex_bg]->sy;
		else 
			m_num_frames=1;
	}
	else
		m_num_frames=0;
}

void pGUIWindow::init()
{
	//update_num_frames();
	m_start_time=g_gomanager->m_time;
}

void pGUIWindow::step(const float elapsed_time,const int& global_x,const int& global_y)
{
	m_global_x=global_x+m_pos_x;
	m_global_y=global_y+m_pos_y;
	
	for(int i=0;i<m_child.num;i++)
		if (m_child.buf[i]->m_flags&P_GUIFLAGS_ENABLED)
			m_child.buf[i]->step(elapsed_time,m_global_x,m_global_y+m_title_height);
}

void pGUIWindow::draw(pRect& scissor_rect)
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

	// draw window and backgound
	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

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

	if (m_tex_stretch!=0)
	{
		glColor4fv(&m_color.x);
		g_render->sel_tex(m_tex_bg);
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
	else
	{
		int h,w;
		if(m_tex_bg==-1)
		{
			w=m_width;
			h=m_height;
		}
		else
		{
			w=g_render->pic[m_tex_bg]->sx;
			h=g_render->pic[m_tex_bg]->sy;
		}
		
		glColor4fv(&m_color.x);
		g_render->sel_tex(m_tex_bg);
		//*glBegin(GL_QUADS);
		glTexCoord2f(si,1.0f);
		glVertex2i(0,0);
		glTexCoord2f(si,0.0f);
		glVertex2i(0,h);
		glTexCoord2f(sf,0.0f);
		glVertex2i(w,h);
		glTexCoord2f(sf,1.0f);
		glVertex2i(w,0);
		//*glEnd();
	}

	// retores texture matrix
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	if(m_glow_func.m_type!=P_PERIODICFUNC_NONE)
	{
		float f=m_glow_func.eval(g_gomanager->m_time);
		pVector drawcolor=(1.0f-f)*m_glow_color1+f*m_glow_color0;
		drawcolor.w=(1.0f-f)*m_glow_color1.w+f*m_glow_color0.w;

		glColor4fv(&drawcolor.x);
		g_render->sel_tex(m_glow_tex);
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
	}

	int tx=m_title_border_size;
	int ty=m_title_border_size;
	int tw=m_width-2*m_title_border_size;

	int oldfont=g_render->sel_font(m_font);
		
	if(m_title_height>0)
	{
		// draw title
		glTranslatef((float)tx,(float)ty,0.0f);
		glColor4fv(&m_title_bg_color.x);
		int tsize=0;

		if(m_tex_title_start==-1 && m_tex_title_mid==-1 && m_tex_title_start==-1)
		{
			g_render->sel_tex(-1);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(0,0);
			glTexCoord2i(0,0);
			glVertex2i(0,m_title_height);
			glTexCoord2i(1,0);
			glVertex2i(tw,m_title_height);
			glTexCoord2i(1,1);
			glVertex2i(tw,0);
			//*glEnd();
		}
		else
		{
			// draw tiled mid texture
			if(m_tex_title_mid!=-1 && m_tex_title_mid<g_render->pic.num)
				tsize=g_render->pic[m_tex_title_mid]->sx;

			if(tsize)
			{
				g_render->sel_tex(m_tex_title_mid);
				//*glBegin(GL_QUADS);
				for(int i=tsize;i+tsize<tw;i+=tsize)
				{
					glTexCoord2i(0,1);
					glVertex2i(i,0);
					glTexCoord2i(0,0);
					glVertex2i(i,m_title_height);
					glTexCoord2i(1,0);
					glVertex2i(i+tsize,m_title_height);
					glTexCoord2i(1,1);
					glVertex2i(i+tsize,0);
				}
				//*glEnd();
			}

			// draw start texture
			tsize=0;
			if(m_tex_title_start!=-1 && m_tex_title_start<g_render->pic.num)
				tsize=g_render->pic[m_tex_title_start]->sx;

			g_render->sel_tex(m_tex_title_start);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(0,0);
			glTexCoord2i(0,0);
			glVertex2i(0,m_title_height);
			glTexCoord2i(1,0);
			glVertex2i(tsize,m_title_height);
			glTexCoord2i(1,1);
			glVertex2i(tsize,0);
			//*glEnd();

			// draw end texture
			tsize=0;
			if(m_tex_title_end!=-1 && m_tex_title_end<g_render->pic.num)
				tsize=g_render->pic[m_tex_title_end]->sx;

			g_render->sel_tex(m_tex_title_end);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(tw-tsize,0);
			glTexCoord2i(0,0);
			glVertex2i(tw-tsize,m_title_height);
			glTexCoord2i(1,0);
			glVertex2i(tw,m_title_height);
			glTexCoord2i(1,1);
			glVertex2i(tw,0);
			//*glEnd();
		}

		// draw close texture
		if(m_tex_close!=-1 && m_tex_close<g_render->pic.num)
		{
			tsize=g_render->pic[m_tex_close]->sx;

			if(m_close_button_align)
				glTranslatef((float)(tw-tsize),0.0f,0.0f);

			g_render->sel_tex(m_tex_close);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(0,0);
			glTexCoord2i(0,0);
			glVertex2i(0,m_title_height);
			glTexCoord2i(1,0);
			glVertex2i(tsize,m_title_height);
			glTexCoord2i(1,1);
			glVertex2i(tsize,0);
			//*glEnd();
		}

		glPopMatrix();

		// draw title text
		glColor4fv(&m_text_color.x);
		if(m_text_align==2) // center
		{
			int textx=tx+(int)(tw/2.0f);
			g_render->draw_text_center(m_global_x+textx,(m_global_y+ty+(int)((m_title_height-m_font_size)/2.0f)),(const char *)m_text,m_font_size);
		}
		else
		{
			int textx=tx+m_text_border_size;
			if(m_text_align!=0) // right
			{
				int textsize=g_render->get_text_size((const char *)m_text,m_font_size);
				textx=tw-textsize-m_text_border_size;
			}

			g_render->draw_text(m_global_x+textx,(m_global_y+ty+(int)((m_title_height-m_font_size)/2.0f)),(const char *)m_text,m_font_size);
		}
	}
	else
	{
		glPopMatrix();

		// draw text
		glColor4fv(&m_text_color.x);
		if(m_text_align==2) // center
			g_render->draw_text_center(m_global_x+(m_width/2),(m_global_y+((m_height-m_font_size)/2)),(const char *)m_text,m_font_size);
		else
		{
			int textx=m_text_border_size;
			if(m_text_align!=0) // right
			{
				int textsize=g_render->get_text_size((const char *)m_text,m_font_size);
				textx=m_width-textsize-m_text_border_size;
			}

			g_render->draw_text(m_global_x+textx,(m_global_y+((m_height-m_font_size)/2)),(const char *)m_text,m_font_size);
		}
	}

	draw_scroll_bar(scissor_rect);
	
	for(int i=0;i<m_child.num;i++)
		if(m_child.buf[i]->m_flags&P_GUIFLAGS_VISIBLE)
		{
			int ch=get_content_height();
			if(ch>m_height)
				m_child.buf[i]->m_global_y-=(int)(0.5f+m_scroll_y*(ch-(m_height-m_title_height))); // 0.5f corrects rounding error
		}

	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIWindow::draw_scroll_bar(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	int ch=get_content_height();
	if(ch>m_height)
	{
		scissor_rect.m_y+=m_title_height;
		scissor_rect.m_height-=m_title_height;

		if(m_scroll_bar_width>0)
		{
			int sbx=scissor_rect.m_x+scissor_rect.m_width-m_scroll_bar_width;
			int sby=scissor_rect.m_y;

			// draw up button
			glColor4fv(&m_scroll_button_color.x);
			g_render->sel_tex(m_scroll_tex_button);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(sbx,sby);
			glTexCoord2i(0,0);
			glVertex2i(sbx,sby+m_scroll_bar_width);
			glTexCoord2i(1,0);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby+m_scroll_bar_width);
			glTexCoord2i(1,1);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby);
			//*glEnd();

			// draw scroll bar background
			sby+=m_scroll_bar_width;

			glColor4fv(&m_scroll_bg_color.x);
			g_render->sel_tex(m_scroll_tex_bg);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(sbx,sby);
			glTexCoord2i(0,0);
			glVertex2i(sbx,scissor_rect.m_y+scissor_rect.m_height-m_scroll_bar_width);
			glTexCoord2i(1,0);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,scissor_rect.m_y+scissor_rect.m_height-m_scroll_bar_width);
			glTexCoord2i(1,1);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby);
			//*glEnd();

			// draw scroll bar
			int barsizey=(int)((scissor_rect.m_height-2*m_scroll_bar_width)*((float)scissor_rect.m_height/ch));
			sby+=(int)((m_scroll_y*(scissor_rect.m_height-barsizey-2*m_scroll_bar_width)));

			glColor4fv(&m_scroll_bar_color.x);
			g_render->sel_tex(m_scroll_tex_bar);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(sbx,sby);
			glTexCoord2i(0,0);
			glVertex2i(sbx,sby+barsizey);
			glTexCoord2i(1,0);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby+barsizey);
			glTexCoord2i(1,1);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby);
			//*glEnd();
			
			// draw down button
			sby=scissor_rect.m_y+scissor_rect.m_height-m_scroll_bar_width;

			glColor4fv(&m_scroll_button_color.x);
			g_render->sel_tex(m_scroll_tex_button);
			//*glBegin(GL_QUADS);
			glTexCoord2i(0,0);
			glVertex2i(sbx,sby);
			glTexCoord2i(0,1);
			glVertex2i(sbx,sby+m_scroll_bar_width);
			glTexCoord2i(1,1);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby+m_scroll_bar_width);
			glTexCoord2i(1,0);
			glVertex2i(scissor_rect.m_x+scissor_rect.m_width,sby);
			//*glEnd();
		}

		scissor_rect.m_width-=m_scroll_bar_width;

		glScissor(scissor_rect.m_x,g_render->sizey-(scissor_rect.m_y+scissor_rect.m_height),scissor_rect.m_width-m_scroll_bar_width,scissor_rect.m_height);
	}
#endif
}

int pGUIWindow::get_content_height()
{
	int cheight=0,h;
	for(int i=0;i<m_child.num;i++)
	{
		h=m_title_height+m_child[i]->m_pos_y+m_child[i]->m_height;
		if(h>cheight)
			cheight=h;
	}

	return m_content_height>m_height?m_content_height>cheight?m_content_height:cheight:m_height>cheight?m_height:cheight;
}

void pGUIWindow::process_mouse_input(pGUIEventHandler *event_handler)
{
	int ch=get_content_height();
	if(ch>m_height)
	{
		int x=m_global_x,y=m_global_y+m_title_height,w=m_width,h=m_height-m_title_height;

		int barsizey=(int)((h-2*m_scroll_bar_width)*((float)h/ch));

		float unit_factor=m_scroll_unit/(float)(ch-h);
		float barpixel_factor=1.0f/(h-(2*m_scroll_bar_width)-barsizey);
		float height_factor=h/(float)(ch-h);
			
		if(m_scroll_bar_drag)
		{
			m_scroll_y+=g_gomanager->m_mouse_drag_y*barpixel_factor;

			if(m_scroll_y<0.0f)
				m_scroll_y=0.0f;
			if(m_scroll_y>1.0f)
				m_scroll_y=1.0f;

			return;
		}

		int sbx=x+w-m_scroll_bar_width;
		int sby=y+m_scroll_bar_width;

		if(is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y) && g_gomanager->m_mouse_x>=sbx)
		{
			static float press_time=0.0f;
			int first_press=0;

			if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
			{
				if(press_time==0.0f)
					first_press=1;
				press_time+=g_gomanager->m_elapsed_time;
			}
			else
				press_time=0.0f;

			if(g_gomanager->m_mouse_y<=sby) // mouse inside up button
			{
				if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
				{
					if(first_press)
						m_scroll_y-=unit_factor;
					else if(press_time>m_scroll_timeout)
						m_scroll_y-=(press_time-m_scroll_timeout)*m_scroll_speed*unit_factor;
				}
			}
			else
			{
				if(g_gomanager->m_mouse_y>sby && g_gomanager->m_mouse_y<y+h-m_scroll_bar_width) // mouse inside scroll bar area
				{
					int barsizeyb=(int)((h-2*m_scroll_bar_width)*((float)h/ch));
					sby+=(int)((m_scroll_y*(h-barsizeyb-2*m_scroll_bar_width)));

					if(g_gomanager->m_mouse_y<sby || g_gomanager->m_mouse_y>sby+barsizeyb) // mouse on scroll bar background
					{
						if(g_gomanager->m_mouse_y<sby) // mouse above scroll bar
						{
							if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
							{
								if(first_press)
									m_scroll_y-=height_factor;
								else if(press_time>m_scroll_timeout)
									m_scroll_y-=(press_time-m_scroll_timeout)*m_scroll_speed*height_factor;
							}
						}
						else // mouse below scroll bar
						{
							if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
							{
								if(first_press)
									m_scroll_y+=height_factor;
								else if(press_time>m_scroll_timeout)
									m_scroll_y+=(press_time-m_scroll_timeout)*m_scroll_speed*height_factor;
							}
						}
					}
				}
				else
				{
					sby=y+h-m_scroll_bar_width;
					if(g_gomanager->m_mouse_y>=sby) // mouse inside down button
						if(g_gomanager->m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
						{
							if(first_press)
								m_scroll_y+=unit_factor;
							else if(press_time>m_scroll_timeout)
								m_scroll_y+=(press_time-m_scroll_timeout)*m_scroll_speed*unit_factor;
						}
				}
			}

			if(m_scroll_y<0.0f)
				m_scroll_y=0.0f;
			if(m_scroll_y>1.0f)
				m_scroll_y=1.0f;
		}
	}
}

void pGUIWindow::on_begin_drag()
{
	int ch=get_content_height();
	if(ch>m_height)
	{
		int sbx=m_global_x+m_width-m_scroll_bar_width;
		int sby=m_global_y+m_title_height+m_scroll_bar_width;

		if(is_inside(g_gomanager->m_mouse_x,g_gomanager->m_mouse_y) && g_gomanager->m_mouse_x>=sbx)
			if(g_gomanager->m_mouse_y>sby && g_gomanager->m_mouse_y<m_global_y+m_height-m_scroll_bar_width) // mouse inside scroll bar area
			{
				int barsizey=(int)(((m_height-m_title_height)-2*m_scroll_bar_width)*((float)(m_height-m_title_height)/ch));
				sby+=(int)((m_scroll_y*((m_height-m_title_height)-barsizey-2*m_scroll_bar_width)));

				if(g_gomanager->m_mouse_y>=sby && g_gomanager->m_mouse_y<=sby+barsizey) // mouse on scroll bar
					m_scroll_bar_drag=1;
			}
	}
}

void pGUIWindow::on_end_drag()
{
	m_scroll_bar_drag=0;
}

int pGUIWindow::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Window color, multiplied by the texture";
			break;
		case 1:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			pd->comment="Window transparency (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 2:
			pd->type='s';
			pd->data=&m_text;
			pd->name="text";
			pd->comment="Window text";
			break;
		case 3:
			pd->type='c';
			pd->data=&m_text_color;
			pd->name="text_color";
			pd->comment="Face color for the text";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_text_color.w;
			pd->name="text_transp";
			pd->comment="Text transparency (0 = fully transparent, 1 = fully opaque)";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_text_align;
			pd->name="text_align";
			pd->comment="Text alignment|Left|Right|Center";
			break;
		case 6:
			pd->type='i';
			pd->data=&m_text_border_size;
			pd->name="text_border_size";
			pd->comment="Text border size";
			break;
		case 7:
			pd->type='i';
			pd->data=&m_title_height;
			pd->name="title_height";
			pd->comment="Title bar height";
			break;
		case 8:
			pd->type='c';
			pd->data=&m_title_bg_color;
			pd->name="title_bg_color";
			pd->comment="Background color for the title bar";
			break;
		case 9:
			pd->type='f';
			pd->data=&m_title_bg_color.w;
			pd->name="title_bg_transp";
			pd->comment="Transparency of the title bar (0.0 = fully transparent, 1.0 = fully opaque)";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_title_border_size;
			pd->name="title_border_size";
			pd->comment="Title border size";
			break;
		case 11:
			pd->type='p';
			pd->data=&m_tex_title_start;
			pd->name="tex_title_start";
			pd->comment="Texture for the beginning part of the title bar";
			break;
		case 12:
			pd->type='p';
			pd->data=&m_tex_title_mid;
			pd->name="tex_title_mid";
			pd->comment="Texture for the middle part of the title bar, that will be tiled for the whole extension of the bar";
			break;
		case 13:
			pd->type='p';
			pd->data=&m_tex_title_end;
			pd->name="tex_title_end";
			pd->comment="Texture for the ending part of the title bar";
			break;
		case 14:
			pd->type='p';
			pd->data=&m_tex_close;
			pd->name="tex_close";
			pd->comment="Texture for the close button";
			break;
		case 15:
			pd->type='p';
			pd->data=&m_tex_bg;
			pd->name="tex_bg";
			pd->comment="Texture for the window background";
			break;
		case 16:
			pd->type='b';
			pd->data=&m_tex_stretch;
			pd->name="tex_stretch";
			pd->comment="Texture strech flag (if checked, texture will rescale to fit window size)";
			break;
		case 17:
			pd->type='i';
			pd->data=&m_close_button_align;
			pd->name="close_button_align";
			pd->comment="Close button alignment|Left|Right";
			break;
		case 18:
			pd->type='p';
			pd->data=&m_glow_tex;
			pd->name="glow_texture";
			pd->comment="Texture for the window glowing effect";
			break;
		case 19:
			pd->type='c';
			pd->data=&m_glow_color0;
			pd->name="glow_color0";
			pd->comment="Initial color for the window glowing effect";
			break;
		case 20:
			pd->type='f';
			pd->data=&m_glow_color0.w;
			pd->name="glow_transp0";
			pd->comment="Initial transparency for the window glowing effect";
			break;
		case 21:
			pd->type='c';
			pd->data=&m_glow_color1;
			pd->name="glow_color1";
			pd->comment="Final color for the window glowing effect";
			break;
		case 22:
			pd->type='f';
			pd->data=&m_glow_color1.w;
			pd->name="glow_transp1";
			pd->comment="Final transparency for the window glowing effect";
			break;
		case 23:
			pd->type='e';
			pd->data=&m_glow_func;
			pd->name="glow_func";
			pd->comment="Periodic function for controlling the window glowing effect";
			break;
		case 24:
			pd->type='n';
			pd->data=&m_font;
			pd->name="font";
			pd->comment="Font file for the window text";
			break;
		case 25:
			pd->type='i';
			pd->data=&m_font_size;
			pd->name="font_size";
			pd->comment="Font size for the window text";
			break;
		case 26:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
			break;
		case 27:
			pd->type='i';
			pd->data=&m_content_height;
			pd->name="content_height";
			pd->comment="Total content height, used for scrolling";
			break;
		case 28:
			pd->type='i';
			pd->data=&m_scroll_bar_width;
			pd->name="scroll_bar_width";
			pd->comment="Width in pixels of the scroll bar";
			break;
		case 29:
			pd->type='i';
			pd->data=&m_scroll_unit;
			pd->name="scroll_unit";
			pd->comment="Vertical scroll unit in pixels";
			break;
		case 30:
			pd->type='f';
			pd->data=&m_scroll_speed;
			pd->name="scroll_speed";
			pd->comment="Vertical scroll speed, in units per second";
			break;
		case 31:
			pd->type='f';
			pd->data=&m_scroll_timeout;
			pd->name="scroll_timeout";
			pd->comment="Vertical scroll timeout in seconds";
			break;
		case 32:
			pd->type='p';
			pd->data=&m_scroll_tex_button;
			pd->name="scroll_tex_button";
			pd->comment="Texture for the scroll bar up/down buttons";
			break;
		case 33:
			pd->type='p';
			pd->data=&m_scroll_tex_bg;
			pd->name="scroll_tex_bg";
			pd->comment="Texture for the scroll bar background";
			break;
		case 34:
			pd->type='p';
			pd->data=&m_scroll_tex_bar;
			pd->name="scroll_tex_bar";
			pd->comment="Texture for the scroll bar";
			break;
		case 35:
			pd->type='c';
			pd->data=&m_scroll_button_color;
			pd->name="scroll_button_color";
			pd->comment="Scroll bar up/down buttons color";
			break;
		case 36:
			pd->type='c';
			pd->data=&m_scroll_bg_color;
			pd->name="scroll_bg_color";
			pd->comment="Scroll bar background color";
			break;
		case 37:
			pd->type='c';
			pd->data=&m_scroll_bar_color;
			pd->name="scroll_bar_color";
			pd->comment="Scroll bar face color";
			break;
		case 38:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 39:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 40:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 41:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 42:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 43:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate to display animation maps";
			break;
		case 44:
			pd->type='i';
			pd->data=&m_command;
			pd->name="command";
			pd->comment="Animation command|Play|Play Once|Pause|Stop";
			break;
		case 45:
			pd->type='i';
			pd->data=&m_current_frame;
			pd->name="current_frame";
			pd->comment="Current frame in the animation. It can be edited only if";
			            " m_command equals to Stop";
			break;
		case 46:
			pd->type='f';
			pd->data=&m_rotation_vel;
			pd->name="rotation_vel";
			pd->comment="Rotation velocity in degrees peer second";
			break;
		case 47:
			pd->type='e';
			pd->data=&m_vert_stretch_func;
			pd->name="vert_stretch_func";
			pd->comment="Vertical stretch function";
			break;
		case 48:
			pd->type='e';
			pd->data=&m_horz_stretch_func;
			pd->name="horz_stretch_func";
			pd->comment="Horizontal stretch function";
			break;
		case 49:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 50;
}

void pGUIWindow::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 15:
		{
			update_num_frames();
		}
		break;

		case 44:
			if(m_command!=CMD_PAUSE)
				m_start_time=g_gomanager->m_time;
		break;
	}
}

#endif
