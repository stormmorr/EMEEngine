#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

void pGUIModelViewer::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	if (m_mesh)
	{
		glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT|GL_SCISSOR_BIT);
		glPushMatrix();

		glDepthMask(GL_TRUE);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);

		pVector center(m_global_x+m_width*0.5f,m_global_y+m_height*0.5f,0);
		glTranslatef(center.x,center.y,0);
		
		pLight l;
		l.pos=m_lightpos;
		l.pos.w=m_lightpos.w;
		l.color=m_lightcolor;
		l.flags=P_LIGHTFLAGS_ENABLED;
		l.turn_on(GL_LIGHT0);

		float m=(float)(m_width<m_height?m_width:m_height);
		float d=m_mesh->bbox.get_diagonal().length()*0.5f;
		float s=m*0.5f/d;
		glScalef(s,-s,s);

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		m_rot.x=fmodf(m_rot.x+m_rotvel.x*g_gomanager->m_elapsed_time,360.0f);
		m_rot.y=fmodf(m_rot.y+m_rotvel.y*g_gomanager->m_elapsed_time,360.0f);
		m_rot.z=fmodf(m_rot.z+m_rotvel.z*g_gomanager->m_elapsed_time,360.0f);
		glRotatef(m_rot.x,1,0,0);
		glRotatef(m_rot.y,0,1,0);
		glRotatef(m_rot.z,0,0,1);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,g_render->sizex,0,g_render->sizey,-m,m);

		m_mesh->draw(P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE,0,g_render->profile.buf[0]);

		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,g_render->sizex,0,g_render->sizey,-1,1);
		glMatrixMode(GL_MODELVIEW);

		glPopMatrix();
		glPopAttrib();
	}
	pGUIObject::draw(scissor_rect);
#endif
}

int pGUIModelViewer::get_custom_param_desc(int i,pParamDesc *pd)
{
	if(pd)
	switch(i)
	{
		case 0:
			pd->type='m';
			pd->data=&m_mesh;
			pd->name="model";
			pd->comment="3D model to view";
			break;
		case 1:
			pd->type='v';
			pd->data=&m_lightpos;
			pd->name="light_pos";
			pd->comment="Light position in screen space";
			break;
		case 2:
			pd->type='f';
			pd->data=&m_lightpos.w;
			pd->name="light_radius";
			pd->comment="Light radius in screen space";
			break;
		case 3:
			pd->type='c';
			pd->data=&m_lightcolor;
			pd->name="light_color";
			pd->comment="Light color";
			break;
		case 4:
			pd->type='c';
			pd->data=&m_lightambient;
			pd->name="light_ambient";
			pd->comment="Light ambient";
			break;
		case 5:
			pd->type='v';
			pd->data=&m_rot;
			pd->name="rot";
			pd->comment="Object rotation";
			break;
		case 6:
			pd->type='v';
			pd->data=&m_rotvel;
			pd->name="rotvel";
			pd->comment="Object rotation velocity (degrees per second)";
			break;
		case 7:
			pd->type='i';
			pd->data=&m_hotspot_x;
			pd->name="hotspot_x";
			pd->comment="Hotspot x position in screen coordinates";
			break;
		case 8:
			pd->type='i';
			pd->data=&m_hotspot_y;
			pd->name="hotspot_y";
			pd->comment="Hotspot y position in screen coordinates";
			break;
		case 9:
			pd->type='b';
			pd->data=&m_popup;
			pd->name="popup";
			pd->comment="Pop-up flag";
			break;
		case 10:
			pd->type='b';
			pd->data=&m_draggable;
			pd->name="draggable";
			pd->comment="Draggable flag";
			break;
		case 11:
			pd->type='b';
			pd->data=&m_droppable;
			pd->name="droppable";
			pd->comment="Droppable flag";
			break;
		case 12:
			pd->type='p';
			pd->data=&m_mouse_cursor_can_drop;
			pd->name="mouse_cursor_can_drop";
			pd->comment="Mouse cursor for when m_droppable equals to true";
			break;
		case 13:
			pd->type='p';
			pd->data=&m_mouse_cursor_cannot_drop;
			pd->name="mouse_cursor_cannot_drop";
			pd->comment="Mouse cursor for when m_droppable equals to false";
			break;
		case 14:
			pd->type='s';
			pd->data=&m_tooltip;
			pd->name="tooltip_text";
			pd->comment="Object tool tip text, blank for no tool tip";
			break;
	}
	return 15;
}

#endif
