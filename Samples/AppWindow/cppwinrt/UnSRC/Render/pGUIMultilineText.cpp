#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

pGUIMultilineText::pGUIMultilineText() :
	m_tex(-1),
	m_text_horz_align(0),
	m_text_vert_align(0),
	m_default_text_color(0.0f),
	m_text_border_size(0),
	m_add_blend(0)
{
	m_type=TYPE_GUI_MULTILINE_TEXT;
}

pGUIMultilineText::pGUIMultilineText(const pGUIMultilineText& in) :
	pGUIObject(in),
	m_tex(in.m_tex),
	m_text_horz_align(in.m_text_horz_align),
	m_text_vert_align(in.m_text_vert_align),
	m_default_text_color(in.m_default_text_color),
	m_custom_text_colors(in.m_custom_text_colors),
	m_text_border_size(in.m_text_border_size),
	m_add_blend(in.m_add_blend),
	m_lines(in.m_lines)
{

}

void pGUIMultilineText::init()
{
	process_lines();
}

void pGUIMultilineText::process_lines()
{
	m_lines.clear();

	pString linetext,aux;
	
	pString ltext;
	pString rtext=m_text;
	if(rtext[rtext.length()-1]!=' ')
		rtext+=" ";
	
	int n;
	int p1=rtext.find(' ');
	int p2=rtext.find('\n');
	if(p2==-1)
		p2=rtext.find('|');

	while(p1!=-1)
	{
		n=rtext.length();
		
		ltext=rtext.left((p2>=0 && p2<p1)?p2:p1);

		if(aux.length()>0)
			aux+=" ";
		aux+=ltext;

		if(linetext.length()>0 && get_text_size_without_colors((const char *)aux,m_font_size)>=(m_width-(2*m_text_border_size)))
		{
			m_lines.add(linetext);
			aux=aux.right(aux.length()-linetext.length()-1);
			linetext="";
		}

		linetext=aux;
		rtext=rtext.right((p2>=0 && p2<p1)?n-p2-1:n-p1-1);

		if(p2>=0 && p2<p1)
		{
			m_lines.add(linetext);
			aux="";
			linetext="";
		}

		p1=rtext.find(' ');
		p2=rtext.find('\n');
		if(p2==-1)
			p2=rtext.find('|');
	}

	if(linetext.length()>0)
		m_lines.add(linetext);
}

int pGUIMultilineText::get_text_size_without_colors(const char *text,int fontsize) const
{
	if (g_render->cur_font==0) 
		return 0;
	const unsigned char *utext=(unsigned char *)text;
	int ret=0,i=0,j=strlen(text);
	for( ;i<j;i++ )
	{
		if(utext[i]=='^')
			i++;
		else
			ret+=g_render->cur_font->width[utext[i]]*fontsize/g_render->cur_font->charsize;
	}
	return ret;
}

void pGUIMultilineText::draw_text(int x,int y,const char *text,int fontsize,int n) const
{
#ifdef P_INIT_OGL
	if (g_render->hrc==0)
		return;
#endif

#ifndef P_DISABLE_3D
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	const unsigned char *utext=(unsigned char *)text;
	if (g_render->cur_font==0 || g_render->cur_font->pic==-1)
		return;

	int len=(n==-1?strlen(text):n);
	g_render->sel_tex(g_render->cur_font->pic);
	
	int cursorx=x;
	int cursory=y;

	//*glBegin(GL_QUADS);
	float xx,yy;
	for( int i=0;i<len;i++ )
		if(utext[i]=='\n')
		{
			cursory+=fontsize;
			y+=fontsize;
			x=cursorx;
		}
		else if(utext[i]=='^')
		{
			i++;
			int color=int(utext[i])-48;
			if(utext[i]=='d' || color>(m_custom_text_colors.num-1) || color<0)
				glColor4fv(&m_default_text_color.x);
			else
			{
				glColor4f(
					m_custom_text_colors[color].x,m_custom_text_colors[color].y,m_custom_text_colors[color].z,
					m_default_text_color.w
				);
			}
		}
		else
		{
			xx=(utext[i]%P_FONTS_NUM)*P_FONTS_FACTOR;
			yy=1.0f-(utext[i]/P_FONTS_NUM)*P_FONTS_FACTOR;

			glTexCoord2f(xx+P_FONTS_FACTOR,yy);
			glVertex2i(x+fontsize,y);

			glTexCoord2f(xx+P_FONTS_FACTOR,yy-P_FONTS_FACTOR);
			glVertex2i(x+fontsize,y+fontsize);

			glTexCoord2f(xx,yy-P_FONTS_FACTOR);
			glVertex2i(x,y+fontsize);

			glTexCoord2f(xx,yy);
			glVertex2i(x,y);

			x+=g_render->cur_font->width[utext[i]]*fontsize/g_render->cur_font->charsize;
		}
	//*glEnd();
#endif
}

void pGUIMultilineText::draw_text_center(int x,int y,const char *text,int fontsize) const
{
#ifdef P_INIT_OGL
	if (g_render->hrc==0)
		return;
#endif
	if (g_render->cur_font==0)
		return;

	const unsigned char *utext=(unsigned char *)text;
	int s=0;

	unsigned char* c=(unsigned char*)strchr(text,'\n');
	if(c==0)
	{
		s=get_text_size_without_colors(text,fontsize);
		draw_text(x-(s/2),y,text,fontsize);
	}
	else
	{
		const unsigned char *t=utext;
		for( ;utext!=c;utext++ )
			s+=g_render->cur_font->width[*utext]*fontsize/g_render->cur_font->charsize;

		draw_text(x-(s/2),y,(char *)t,fontsize,utext-t);
		draw_text_center(x,y+fontsize,(char *)++utext,fontsize);
	}
}

void pGUIMultilineText::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	// draw window and background
	glPushMatrix();
	
	glTranslatef((float)m_global_x,(float)m_global_y,0.0f);

	if(m_add_blend)
		glBlendFunc(GL_ONE,GL_ONE);
	
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

	int oldfont=g_render->sel_font(m_font);

	glColor4fv(&m_default_text_color.x);
	
	if(m_lines.num)
		if(m_lines.num==1)
			draw_line(0);
		else
			draw_multiline(0);

	pGUIObject::draw(scissor_rect);

	g_render->sel_font(oldfont);
#endif
}

void pGUIMultilineText::draw_multiline(int i)
{
	if(i<0 || i>=m_lines.num)
		return;

	draw_line(i);
	draw_multiline(++i);
}

void pGUIMultilineText::draw_line(int i)
{
#ifndef P_DISABLE_3D
	if(i<0 || i>=m_lines.num)
		return;

	if(m_lines[i].length()<1)
		return;

	int texty;
	if(m_text_vert_align==0) // top
		texty=m_global_y+m_text_border_size+(m_font_size*i);
	else if(m_text_vert_align==1) // bottom
	{
		float th=(float)(m_font_size*(m_lines.num-i));
		texty=(int)(m_global_y+m_height-m_text_border_size-(th));
	}
	else // center
	{
		float fac=(i/(m_lines.num*0.5f))-1;
		float hth=(m_font_size*(m_lines.num)/2.0f);
		texty=(int)(m_global_y+(m_height/2)+(hth*fac));
	}

	if(m_text_horz_align==2) // center
		draw_text_center(m_global_x+(m_width/2),texty,(const char *)m_lines[i],m_font_size);
	else
	{
		int textx=m_text_border_size;
		if(m_text_horz_align!=0) // right
		{
			int textsize=get_text_size_without_colors((const char *)m_lines[i],m_font_size);
			textx=m_width-textsize-m_text_border_size;
		}

		draw_text(m_global_x+textx,texty,(const char *)m_lines[i],m_font_size);
	}
#endif
}

int pGUIMultilineText::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='b';
			pd->data=&m_add_blend;
			pd->name="add_blend";
			pd->comment="Additive blending flag";
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
			pd->data=&m_default_text_color;
			pd->name="text_color";
			pd->comment="Face color for the text";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_default_text_color.w;
			pd->name="text_transp";
			pd->comment="Text transparency (0 = fully transparent, 1 = fully opaque)";
			break;
		case 8:
			pd->type=-'c';
			pd->data=&m_custom_text_colors;
			pd->name="custom_text_colors";
			pd->comment="Other face colors for the text";
			break;
		case 9:
			pd->type='i';
			pd->data=&m_text_horz_align;
			pd->name="text_horz_align";
			pd->comment="Horizontal text alignment|Left|Right|Center";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_text_vert_align;
			pd->name="text_vert_align";
			pd->comment="Vertical text alignment|Top|Bottom|Center";
			break;
		case 11:
			pd->type='i';
			pd->data=&m_text_border_size;
			pd->name="text_border_size";
			pd->comment="Text border size";
			break;
		case 12:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
			break;
		case 13:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 14:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 15:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 16:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 17:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 18:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 19:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 20:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
		case 21:
			pd->type='p';
			pd->data=&m_tex;
			pd->name="tex";
			pd->comment="Texture for the object";
			break;
	}

	return 22;
}

void pGUIMultilineText::on_pos_parameter_change(int i)
{
	// base object
	switch(i)
	{
		case 5:  // m_width
		case 6:  // m_height
		case 9:  // m_text
		case 11: // m_font_size
			process_lines();
		return;
	}

	// this object
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 3:  // m_text
		case 5:  // m_font_size
		case 11: // m_text_border_size
			process_lines();
		break;

		case 8: // m_custom_text_colors
		{
			// verifies if the maximum allowed quantity is violated
			if(m_custom_text_colors.num > 10)
				m_custom_text_colors.remove(10,m_custom_text_colors.num-10);
		}
		break;
	}
}

#endif
	