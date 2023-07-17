#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

pGUIProgressDisk::pGUIProgressDisk() :
	m_slices(16),
	m_inner_radius(32),
	m_outer_radius(40),
	m_start_angle(0),
	m_end_angle(180),
	m_percent(0.5f),
	m_fill_color(1.0f,0.0f,0.0f,1.0f),
	m_vertex_array(0),
	m_index_array(0),
	m_vertex_buffer(0),
	m_index_buffer(0)
{
	m_type=TYPE_GUI_PROGRESSDISK;
}

pGUIProgressDisk::pGUIProgressDisk(const pGUIProgressDisk& in) :
	pGUIObject(in),
	m_slices(in.m_slices),
	m_inner_radius(in.m_inner_radius),
	m_outer_radius(in.m_outer_radius),
	m_start_angle(in.m_start_angle),
	m_end_angle(in.m_end_angle),
	m_percent(in.m_percent),
	m_fill_color(in.m_fill_color),
	m_color_func(in.m_color_func)
{
	int i;
	int num=4*m_slices+4;
	m_vertex_array=new float[num];
	for(i=0;i<num;i++)
		m_vertex_array[i]=in.m_vertex_array[i];
	
	num=2*m_slices+2;
	m_index_array=new int[num];
	for(i=0;i<num;i++)
		m_index_array[i]=in.m_index_array[i];

	m_vertex_buffer=0;
	m_index_buffer=0;
	update_vbo();
}

pGUIProgressDisk::~pGUIProgressDisk()
{
	reset();
}

void pGUIProgressDisk::update_vbo()
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object==0 || g_render->vertbuffer==0)
		return;

	if(m_vertex_array)
	{
		if(m_vertex_buffer==0)
			glGenBuffersARB(1,&m_vertex_buffer);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,m_vertex_buffer);
		glBufferDataARB(GL_ARRAY_BUFFER_ARB,(4*m_slices+4)*sizeof(float),m_vertex_array,GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
	}
	if(m_index_array)
	{
		if(m_index_buffer==0)
			glGenBuffersARB(1,&m_index_buffer);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,m_index_buffer);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,(2*m_slices+2)*sizeof(int),m_index_array,GL_STATIC_DRAW_ARB);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}
#endif
}

void pGUIProgressDisk::push_data() const
{
#ifndef P_DISABLE_3D
	if(g_render->vertbuffer && m_vertex_buffer)
	{
		if(GLEW_ARB_vertex_buffer_object)
		{
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,m_vertex_buffer);
			glVertexPointer(2,GL_FLOAT,2*sizeof(float),0);
		}
	}
	else
	{
		if(GLEW_ARB_vertex_buffer_object)
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
		glVertexPointer(2,GL_FLOAT,2*sizeof(float),&m_vertex_array[0]);
	}

	if(g_render->vertbuffer && m_index_buffer)
	{
		if (GLEW_ARB_vertex_buffer_object)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,m_index_buffer);
	}
	else
	{
		if (GLEW_ARB_vertex_buffer_object)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	if(GLEW_ARB_multitexture && g_render->maxtextureunits>2)
	{
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
#endif
}

void pGUIProgressDisk::pop_data() const
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_vertex_buffer_object)
	{
		if(m_vertex_buffer)
			glBindBufferARB(GL_ARRAY_BUFFER_ARB,0);
		if(m_index_buffer)
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB,0);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
}

void pGUIProgressDisk::reset()
{
	delete[] m_index_array;
	delete[] m_vertex_array;

	m_vertex_array=0;
	m_index_array=0;

#ifndef P_DISABLE_3D
	if(GLEW_ARB_vertex_buffer_object)
	{
		if(m_vertex_buffer)
			glDeleteBuffersARB(1,&m_vertex_buffer);
		if(m_index_buffer)
			glDeleteBuffersARB(1,&m_index_buffer);
	}
#endif
	m_vertex_buffer=0;
	m_index_buffer=0;
}

void pGUIProgressDisk::init()
{
	build(m_slices,m_inner_radius,m_outer_radius,m_start_angle,m_end_angle);
}

void pGUIProgressDisk::build(int ns,float ir,float _or,float sa,float fa)
{
	int i,p,j; // auxiliary variables

	reset();

	m_slices=ns;
	m_inner_radius=ir;
	m_outer_radius=_or;
	m_start_angle=sa;
	m_end_angle=fa;

	m_vertex_array=new float[4*m_slices+4];
	m_index_array=new int[2*m_slices+2];

	// calculate vertices
	float half_width=float(m_width)*0.5f;
	float half_height=float(m_height)*0.5f;
	float inc_angle=PIOVER180*((m_end_angle-m_start_angle)/float(m_slices));
	float angle=PIOVER180*m_start_angle;
	p=0;
	for(i=0;i<m_slices;i++)
	{
		m_vertex_array[p++]=sinf(angle)*m_inner_radius+half_width;
		m_vertex_array[p++]=-cosf(angle)*m_inner_radius+half_height;
		m_vertex_array[p++]=sinf(angle)*m_outer_radius+half_width;
		m_vertex_array[p++]=-cosf(angle)*m_outer_radius+half_height;

		angle+=inc_angle;
	}
	m_vertex_array[p++]=sinf(angle)*m_inner_radius+half_width;
	m_vertex_array[p++]=-cosf(angle)*m_inner_radius+half_height;
	m_vertex_array[p++]=sinf(angle)*m_outer_radius+half_width;
	m_vertex_array[p  ]=-cosf(angle)*m_outer_radius+half_height;

	// calculate quad strip
	p=0;
	for(i=0;i<m_slices;i++)
	{
		j=i*2;
		m_index_array[p++]=j;
		m_index_array[p++]=j+1;
	}
	j=i*2;
	m_index_array[p++]=j;
	m_index_array[p  ]=j+1;

	update_vbo();
}

void pGUIProgressDisk::draw(pRect& scissor_rect)
{
#ifndef P_DISABLE_3D
	if(!m_vertex_array || !m_index_array)
		return;

	int i=int(m_slices*m_percent);

	push_data();

	// store progess disk's fill color for manipulation
	pVector color(m_fill_color);

	// change fill color with periodic function
	if(m_color_func.m_type!=P_PERIODICFUNC_NONE)
	{
		float func_eval=m_color_func.eval(g_gomanager->m_time);
		color=(1.0f-func_eval)*m_fill_color+func_eval*m_color;
	}

	g_render->sel_tex(-1);
	glPushMatrix();
		glTranslatef((float)m_global_x,(float)m_global_y,0.0f);
		// draw fill disk
		if(i!=0)
		{
			glColor4fv(&color.x);
			glDrawElements(GL_QUAD_STRIP,2*i+2,GL_UNSIGNED_INT,g_render->vertbuffer?0:m_index_array);
		}
		// draw rest of disk
		int j=m_slices-i;
		if(j!=0)
		{
			glColor4fv(&m_color.x);
			glDrawElements(GL_QUAD_STRIP,2*j+2,GL_UNSIGNED_INT,g_render->vertbuffer?(void *)(sizeof(int)*(i*2)):&m_index_array[i*2]);
		}
	glPopMatrix();

	pop_data();

	pGUIObject::draw(scissor_rect);
#endif
}

int pGUIProgressDisk::get_custom_param_desc(int i,pParamDesc *pd)
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
			pd->type='c';
			pd->data=&m_fill_color;
			pd->name="fill_color";
			pd->comment="Fill color";
			break;
		case 3:
			pd->type='e';
			pd->data=&m_color_func;
			pd->name="color_function";
			pd->comment="Function to combine fill color and background color";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_fill_color.w;
			pd->name="fill_transp";
			pd->comment="Transparent of fill color";
			break;
		case 5:
			pd->type='i';
			pd->data=&m_slices;
			pd->name="slices";
			pd->comment="The number of quads";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_inner_radius;
			pd->name="inner_radius";
			pd->comment="The inner radius of the progress disk";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_outer_radius;
			pd->name="outer_radius";
			pd->comment="The outer radius of the progress disk";
			break;
		case 8:
			pd->type='f';
			pd->data=&m_start_angle;
			pd->name="start_angle";
			pd->comment="Start angle (in degrees)";
			break;
		case 9:
			pd->type='f';
			pd->data=&m_end_angle;
			pd->name="end_angle";
			pd->comment="End angle (in degrees)";
			break;
		case 10:
			pd->type='f';
			pd->data=&m_percent;
			pd->name="percent";
			pd->comment="Represents the number of slices that will be filled with fill color (0 to 1 range)";
			break;
		case 11:
			pd->type='b';
			pd->data=&m_clickable;
			pd->name="clickable";
			pd->comment="Clickable flag";
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

void pGUIProgressDisk::on_pos_parameter_change(int i)
{
	// base object
	switch(i)
	{
		case 5: // m_width
		case 6: // m_height
			build(m_slices,m_inner_radius,m_outer_radius,m_start_angle,m_end_angle);
		break;
	}

	// this object
	switch(i-P_GUINUMDEFAULTPARAM)
	{
		case 5:case 6:case 7:case 8:case 9:
			build(m_slices,m_inner_radius,m_outer_radius,m_start_angle,m_end_angle);
		break;

		case 10:
			if(m_percent>1.0f)
				m_percent=1.0f;
			if(m_percent<0.0f)
				m_percent=0.0f;
		break;
	}
}

#endif
