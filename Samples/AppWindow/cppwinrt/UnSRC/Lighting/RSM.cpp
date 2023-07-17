/*

	Reflective Shadow Maps - Raw GL
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "RSM.h"
//#include "windows.h"
//#include "stdio.h"

//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
//#include <gl\glext.h>       // Header File For OpenGL Extensions

bool RSM::s_support_NV_render_depth_texture=false;

const int SHADOW_MAP_RES = 1024;

const unsigned int texxcoordsnew[] =
{
1, 0,
0, 0,
0, 1,
1, 1
};

const unsigned int texxreversednew[] =
{
1, 1,
0, 1,
0, 0,
1, 0
};

RSM::RSM() :
m_shadow_buffer(NULL),
m_size(512),
m_shadow_map(0)
{
#if 0
	/// Alternate Constructor
	//wglMakeCurrent(m_hdc, m_hRC);
	//wglShareLists(m_hRC, g_render->hrc);

	//glEnable(GL_TEXTURE_2D);

	//glGenTextures(1, &m_map[0]);

	//printf("RSM:::Initialize Create Textures ID = %u\n", m_map[0]);

	//// Create First Hemisphere
	/*glBindTexture(GL_TEXTURE_2D, m_map[0]);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//// Create Second Hemisphere
	glBindTexture(GL_TEXTURE_2D, m_map[1]);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);*/
#endif

	pVector white(1.0f,1.0f,1.0f,1.0f);

	// initialize p-buffer only for render to depth
	m_shadow_buffer=new pPBuffer(m_size,m_size,0,false,true,false,true,s_support_NV_render_depth_texture,false,false,true,0);
	m_shadow_buffer->Bind();
		glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
		glDepthMask(GL_TRUE);
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
	m_shadow_buffer->Unbind();

	// initialize a texture for store z-buffer content
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&m_shadow_map);
	glBindTexture(GL_TEXTURE_2D,m_shadow_map);
	glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,m_size,m_size,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER_COLOR,&white.x);
	if (GLEW_ARB_shadow)
		{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,GL_COMPARE_R_TO_TEXTURE);
//			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC_ARB,GL_LEQUAL);
//			glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE_ARB,GL_INTENSITY);
		}
	else
		{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		}
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
}

RSM::~RSM()
{
/// Destructor

}

#if 0
// Render Z buffer
void RSM::StartZbuffer(void)
{
/*
	glEnable(GL_TEXTURE_2D);
	
	glViewport(0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glEnable(GL_ALPHA_TEST);
	
	glLoadIdentity();

	glAlphaFunc(GL_GEQUAL, 0.5);
*/

	// Setup GL States
/*	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
	glEnable( GL_TEXTURE_2D );									// Enable Textures
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );				// Set The Color To White
*/

/*
	glBindTexture(GL_TEXTURE_2D, m_Eye[0]);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);

	// Second hemisphere:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glAlphaFunc(GL_LEQUAL, 0.5);

	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 2, 0, 0, 1, 1);
	glTranslatef(-i_Vertex.pos[0], -i_Vertex.pos[1], -i_Vertex.pos[2]);

	////// ACCESS SCENE OBJECTS //////
	//draw_scene();

	glBindTexture(GL_TEXTURE_2D, m_Eye[1]);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);
*/
}
#endif

// Render Z buffer
void RSM::StartZbuffer(void)
{
if(m_shadow_buffer)
	{
	m_shadow_buffer->Bind();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	//?
	//glPolygonOffset(m_shadow_offset_factor,m_shadow_offset_units);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	}
else printf("RSM:::ERROR:::Buffer not setup\n");
}

#if 0
void RSM::StopZbuffer(void)
{
	glBindTexture( GL_TEXTURE_2D, m_map[0] );
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);
	glDisable(GL_ALPHA_TEST);
}
#endif

void RSM::StopZbuffer(void)
{
if(m_shadow_buffer)
	{
	glDisable(GL_POLYGON_OFFSET_FILL);
	if(s_support_NV_render_depth_texture==false)
		{
		// read the depth buffer into the shadow map texture
		glBindTexture(GL_TEXTURE_2D,m_shadow_map);
		glEnable(GL_TEXTURE_2D);
		glCopyTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,0,0,m_size,m_size,0);
		}
	m_shadow_buffer->Unbind();
	}
else printf("RSM:::ERROR:::Buffer not setup\n");
};

void RSM::PrintZBuffer(void)
{
	glEnable(GL_TEXTURE_2D);
	DrawPane(m_shadow_map, 0, 0, 512, 512);
}

void GLEnable2D(void)
{
   int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();

   glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
}

void GLDisable2D(void)
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void RSM::DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley)
{
	int m_x[4];
	int m_y[4];
	int VID_WIDTH = 800;
	int VID_HEIGHT = 600;

	int strendX = i_x + i_scalex;
	int strendY = VID_HEIGHT - (i_y + i_scaley);

	m_x[0] = strendX;
	m_y[0] = VID_HEIGHT - i_y;
	m_x[1] = i_x;
	m_y[1] = VID_HEIGHT - i_y;
	m_x[2] = i_x;
	m_y[2] = strendY;
	m_x[3] = strendX;
	m_y[3] = strendY;

	GLEnable2D();

	glBindTexture( GL_TEXTURE_2D, i_texture );

	glBegin( GL_QUADS );

	for(size_t id=0; id < 4; id++)
		{
		glTexCoord2i(texxcoordsnew[id*2], texxcoordsnew[(id*2)+1]);
		glVertex2d(m_x[id], m_y[id]);
		}

	glEnd();

	GLDisable2D();
}