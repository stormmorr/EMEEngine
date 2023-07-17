#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

pROPanorama::~pROPanorama()
{
#ifndef P_DISABLE_3D
	if (m_stars)
		glDeleteLists(m_stars,1);
#endif
}

void pROPanorama::init(bool active)
{
#ifndef P_DISABLE_3D
	if(active)
	{
		int i;

		// generates randomized points
		m_points.clear();
		m_points.reserve(m_count);
		pVector p;
		for(i=0;i<m_count;i++) 
		{
			p.vec(FRAND*m_size_volume,FRAND*m_size_volume,FRAND*m_size_volume);
			m_points.add(p);
		}

		// use a display list to draw all points 
		if (m_stars)
			glDeleteLists(m_stars,1);
		m_stars=glGenLists(1);
		glNewList(m_stars,GL_COMPILE);
			for(i=0;i<m_count;i++)
			{
				glPointSize(m_point_size*FABSRAND);
				//*glBegin(GL_POINTS);
				//*glVertex3fv(&m_points.buf[i].x);
				//*glEnd();
			}
			glPointSize(1.0);
		//*glEndList();
	}
#endif
}

void pROPanorama::step(const float elapsed_time,const pMatrix& global)
{
	m_bbox.max.vec(m_size);
	m_bbox.min.vec(-m_size);
	m_transform.load_identity();
	m_transform.set_translate(g_render->camera.pos);
	pRenderObject::step(elapsed_time,m_transform);
}

void pROPanorama::draw()
{
#ifndef P_DISABLE_3D
	if (addblend)
		glBlendFunc(GL_ONE, GL_ONE);
	else
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glRotatef(m_rot.x,1,0,0);
	glRotatef(m_rot.y,0,1,0);
	glRotatef(m_rot.z,0,0,1);
	
	if(m_mesh)
	{
		glColor4fv(&m_color.x);
		glScalef(m_size,m_size,m_size);
		glMatrixMode(GL_TEXTURE);

		if(tex2!=-1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glScalef(tile_u,tile_v,1);
			g_render->sel_tex(tex2);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
		}

		glActiveTextureARB(GL_TEXTURE0_ARB);
		g_render->sel_tex(tex1);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);

		m_mesh->array_lock(P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TEXTURE2,g_render->vertbuffer);
		m_mesh->array_draw(g_render->vertbuffer);
		m_mesh->array_unlock();

		if(tex2!=-1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glLoadIdentity();
			glDisable(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
	}
	else
		draw_cube();

	if(m_detail_mesh)
	{
		g_render->sel_tex(m_detail_tex);
		m_detail_mesh->array_lock(P_RENDERFLAG_TEXTURE,g_render->vertbuffer);
		m_detail_mesh->array_draw(g_render->vertbuffer);
		m_detail_mesh->array_unlock();
	}

	if(m_stars_flag==STARS_WITH_GL_POINTS)
	{
		g_render->sel_tex(-1);
		glColor4fv(&m_color.x);
		glCallList(m_stars);
	}
	else if(m_stars_flag==STARS_WITH_POINT_SPRITES)
	{
		if(GLEW_ARB_point_sprite)
		{
			glColor4fv(&m_color.x);
			g_render->sel_tex(m_sprite);
			glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB,GL_TRUE);
			glEnable(GL_POINT_SPRITE_ARB);
			glCallList(m_stars);
			glPointSize(1.0f);
			glDisable(GL_POINT_SPRITE_ARB);
		}
	}
#endif
}

void pROPanorama::draw_cube()
{
#ifndef P_DISABLE_3D
	pVector m1(-m_size),m2(m_size);
	glColor4fv(&m_color.x);

	unsigned int txclamp=(m_tile==1?GL_CLAMP_TO_EDGE_EXT:GL_REPEAT);

	if (m_img[0]!=-1)
	{
		g_render->sel_tex(m_img[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m1.x,m1.y,m2.z);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m1.x,m2.y,m2.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m2.x,m2.y,m2.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m2.x,m1.y,m2.z);
		//*glEnd();
	}

	if (m_img[1]!=-1)
	{
		g_render->sel_tex(m_img[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m1.x,m2.y,m1.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m1.x,m1.y,m1.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m2.x,m1.y,m1.z);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m2.x,m2.y,m1.z);
		//*glEnd();
	}

	if (m_img[2]!=-1)
	{
		g_render->sel_tex(m_img[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m2.x,m2.y,m1.z);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m2.x,m2.y,m2.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m1.x,m2.y,m2.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m1.x,m2.y,m1.z);
		//*glEnd();
	}

	if (m_img[3]!=-1)
	{
		g_render->sel_tex(m_img[3]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m1.x,m1.y,m1.z);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m1.x,m1.y,m2.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m2.x,m1.y,m2.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m2.x,m1.y,m1.z);
		//*glEnd();
	}

	if (m_img[4]!=-1)
	{
		g_render->sel_tex(m_img[4]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m2.x,m1.y,m1.z);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m2.x,m1.y,m2.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m2.x,m2.y,m2.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m2.x,m2.y,m1.z);
		//*glEnd();
	}

	if (m_img[5]!=-1)
	{
		g_render->sel_tex(m_img[5]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,txclamp);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(m1.x,m2.y,m1.z);
		glTexCoord2f(0.0f,m_tile);
		glVertex3f(m1.x,m2.y,m2.z);
		glTexCoord2f(m_tile,m_tile);
		glVertex3f(m1.x,m1.y,m2.z);
		glTexCoord2f(m_tile,0.0f);
		glVertex3f(m1.x,m1.y,m1.z);
		//*glEnd();
	}
#endif
}

int pROPanorama::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='b';
			pd->data=&addblend;
			pd->name="addblend";
			break;
		case 1:
			pd->type='f';
			pd->data=&m_size;
			pd->name="size";
			break;
		case 2:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			break;
		case 3:
			pd->type='f';
			pd->data=&m_color.w;
			pd->name="transp";
			break;
		case 4:
			pd->type='f';
			pd->data=&m_tile;
			pd->name="tile";
			break;
		case 5:
			pd->type='p';
			pd->data=&m_img[0];
			pd->name="up";
			break;
		case 6:
			pd->type='p';
			pd->data=&m_img[1];
			pd->name="down";
			break;
		case 7:
			pd->type='p';
			pd->data=&m_img[2];
			pd->name="left";
			break;
		case 8:
			pd->type='p';
			pd->data=&m_img[3];
			pd->name="right";
			break;
		case 9:
			pd->type='p';
			pd->data=&m_img[4];
			pd->name="front";
			break;
		case 10:
			pd->type='p';
			pd->data=&m_img[5];
			pd->name="back";
			break;
		case 11:
			pd->type='m';
			pd->data=&m_mesh;
			pd->name="mesh";
			pd->comment="Adding a mesh to a pROPanorama object disables the default "
						"6-image cubic panorama and renders the specified mesh instead.";
			break;
		case 12:
			pd->type='p';
			pd->data=&tex1;
			pd->name="tex1";
			pd->comment="Mesh panorama first texture (no tiling and using clamp)";
			break;
		case 13:
			pd->type='p';
			pd->data=&tex2;
			pd->name="tex2";
			pd->comment="Mesh panorama second texture";
			break;
		case 14:
			pd->type='f';
			pd->data=&tile_u;
			pd->name="tex2_tile_u";
			pd->comment="Mesh panorama second texture tile factor in u direction";
			break;
		case 15:
			pd->type='f';
			pd->data=&tile_v;
			pd->name="tex2_tile_v";
			pd->comment="Mesh panorama second texture tile factor in v direction";
			break;
		case 16:
			pd->type='i';
			pd->data=&m_stars_flag;
			pd->name="stars_flag";
			pd->comment="Flag to control stars draw mode|No stars|Stars with points|Stars with point sprites";
			break;
		case 17:
			pd->type='p';
			pd->data=&m_sprite;
			pd->name="sprite";
			pd->comment="Texture for point sprites";
			break;
		case 18:
			pd->type='i';
			pd->data=&m_count;
			pd->name="count";
			pd->comment="Number of stars";
			break;
		case 19:
			pd->type='f';
			pd->data=&m_size_volume;
			pd->name="size_volume";
			pd->comment="Size of the volume where points will be created";
			break;
		case 20:
			pd->type='f';
			pd->data=&m_point_size;
			pd->name="point_size";
			pd->comment="Size of points";
			break;
		case 21:
			pd->type='m';
			pd->data=&m_detail_mesh;
			pd->name="detail_mesh";
			pd->comment="Detail mesh";
			break;
		case 22:
			pd->type='p';
			pd->data=&m_detail_tex;
			pd->name="detail_tex";
			pd->comment="Detail mesh panorama texture";
			break;
		case 23:
			pd->type='v';
			pd->data=&m_rot;
			pd->name="rotation";
			pd->comment="Constant rotation for better panorma orientation in scene";
			break;
	}

	return 24;
}

void pROPanorama::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 18:
		case 19:
		case 20:
			init(m_source!=0);
		break;
	}
}

#endif
