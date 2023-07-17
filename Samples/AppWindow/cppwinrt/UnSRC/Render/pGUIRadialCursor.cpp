#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIRadialCursor::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	if (m_pic==-1)
		return;

	float half_x=(float)(g_render->pic[m_pic]->sx>>1);
	float half_y=(float)(g_render->pic[m_pic]->sy>>1);
		
	float x=m_dist*sinf(m_cur_angle*PIOVER180)+(m_global_x+(m_width>>1));
	float y=-m_dist*cosf(m_cur_angle*PIOVER180)+(m_global_y+(m_height>>1));

	g_render->sel_tex(m_pic);
	glColor4fv(&m_color.x);

	glPushMatrix();
		glTranslatef(x,y,0);
		if (m_rotatepic)
			glRotatef(m_cur_angle,0,0,1);
		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); glVertex2f(-half_x,-half_y);
			glTexCoord2f(1.0f,1.0f); glVertex2f( half_x,-half_y);
			glTexCoord2f(1.0f,0.0f); glVertex2f( half_x, half_y);
			glTexCoord2f(0.0f,0.0f); glVertex2f(-half_x, half_y);
		//*glEnd();
	glPopMatrix();

	pGUIObject::draw(scissor_rect);
#endif
}

int pGUIRadialCursor::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='p';
			pd->data=&m_pic;
			pd->name="pic";
			pd->comment="Texture that representes the cursor";
			break;
		case 3:
			pd->type='f';
			pd->data=&m_dist;
			pd->name="dist";
			pd->comment="Radial distance for cursor";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_angle_start;
			pd->name="angle_start";
			pd->comment="Angle start (in degrees)";
			break;
		case 5:
			pd->type='f';
			pd->data=&m_angle_end;
			pd->name="angle_end";
			pd->comment="Angle end (in degrees)";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_percent;
			pd->name="percent";
			pd->comment="Cursor position (0 to 1 range)";
			break;
		case 7:
			pd->type='b';
			pd->data=&m_rotatepic;
			pd->name="rotatepic";
			pd->comment="Should picture be rotated?";
			break;
		case 8:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
			break;
		case 9:
			pd->type='f';
			pd->data=&m_cur_angle;
			pd->name="cur_angle";
			pd->comment="Current angle";
			break;
		case 10:
			pd->type='i';
			pd->data=&m_point_target_x;
			pd->name="point_target_x";
			pd->comment="Pointing target x in screen coordinates";
			break;
		case 11:
			pd->type='i';
			pd->data=&m_point_target_y;
			pd->name="point_target_y";
			pd->comment="Pointing target y in screen coordinates";
			break;
		case 12:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 13:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 14:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 15:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 16:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 17:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 18:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 19:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}

	return 20;
}

void pGUIRadialCursor::on_pos_parameter_change(int i)
{
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 6:
		{
			if(m_percent>1.0f)
				m_percent=1.0f;
			if(m_percent<0.0f)
				m_percent=0.0f;

			m_cur_angle=m_angle_start+m_percent*(m_angle_end-m_angle_start);
		}
		break;
		case 10:
		case 11:
		{
			int cx,cy;
			g_gomanager->get_object_center(m_id,cx,cy);
			m_cur_angle=g_gomanager->get_angle_2d((float)(m_point_target_x-cx),(float)(m_point_target_y-cy));
		}
		break;
	}
}

#endif
