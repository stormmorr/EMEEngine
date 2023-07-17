#include "pch.h"
#include "paralelo3d.h"

#ifndef P_DISABLE_3D

P3D_API bool pRenderRipple::test()
{
#if 0 // P_SUPPORT_CG
	const char *wglext="";
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if (wglGetExtensionsStringARB)
		wglext=wglGetExtensionsStringARB(wglGetCurrentDC());
	const char *glext=(const char *)glGetString(GL_EXTENSIONS);
	if (glext &&
		strstr(wglext,"WGL_ARB_pbuffer") &&
		strstr(wglext,"WGL_ARB_render_texture") &&
		(strstr(glext,"GL_ARB_fragment_program") ||
		strstr(glext,"GL_ARB_vertex_program")))
		return true;
#endif
	return false;
}

void pRenderRipple::init(int size,int prog)
{
	reset();
	if (size>0 && test() && load_program(prog))
	{
		m_size=size;
		m_ripplepb=new pPBuffer(size,size,32,false,true,false,true,false,false,false,true,0);

		m_ripplepb->Bind();
		glDrawBuffer(GL_FRONT);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		m_ripplepb->Unbind();

		if (m_prog==1)
			build_grid();

		glGenTextures(1,&m_tex);
		glBindTexture(GL_TEXTURE_2D,m_tex);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);
	}
}

void pRenderRipple::reset()
{
#if 0 // P_SUPPORT_CG
	if (m_ripple_prog)
		cgDestroyProgram(m_ripple_prog);
	m_ripple_prog=0;
	m_point_param=0;
	m_texture_param=0;
#endif
	if (m_tex)
		glDeleteTextures(1,&m_tex);
	m_tex=0;

	delete m_ripplepb;
	m_ripplepb=0;

	delete m_gridvert;
	m_gridvert=0;

	m_start_time=0.0f;
	m_duration=0.6f;
	m_radius=1.0f;
	m_intensity=0.2f;
	m_point.vec(0.5f,0.5f,0.0f,0.0f);
	m_prog=0;
}

bool pRenderRipple::load_program(int prog)
{
#if 0 // P_SUPPORT_CG
	const char *glext=(const char *)glGetString(GL_EXTENSIONS);

	m_prog=0;
	if (prog>=2 && glext && strstr(glext,"GL_ARB_fragment_program"))
	{
		m_prog=2;
		m_profile=CG_PROFILE_ARBFP1;
	}
	else
	if (prog>=1 && glext && strstr(glext,"GL_ARB_vertex_program"))
	{
		m_prog=1;
		m_profile=CG_PROFILE_ARBVP1;
	}

	if (m_prog==0)
		return false;

	char *programtext;
	pString str;
	char *mainfunc[3]={"","main_ripple_vert","main_ripple_frag"};

	CgCheckError();
	str=g_render->app_path+g_render->shader_path+"shaders/cg_ripple.cg";	
	programtext=LoadTextFile(str);
	if (programtext)
	{
		m_ripple_prog = cgCreateProgram(g_render->cgcontext, 
			CG_SOURCE, programtext, m_profile, mainfunc[m_prog],0);
		delete programtext;
		if (m_ripple_prog && CgCheckError()==false)
		{
			//*cgGLLoadProgram(m_ripple_prog);
			if (CgCheckError()==false)
			{
				m_point_param = cgGetNamedParameter(m_ripple_prog, "point");
				m_texture_param = cgGetNamedParameter(m_ripple_prog, "texture");
				return true;
			}
		}
	}
#endif	
	return false;
}

void pRenderRipple::draw()
{
#if 0 // P_SUPPORT_CG
	float t=g_render->curtimef-m_start_time;
	if (t>m_duration)
	{
		m_start_time=0;
		t=m_duration;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE,GL_ZERO);
	glColor4f(1,1,1,1);

	glActiveTextureARB(GL_TEXTURE0_ARB);

	glBindTexture(GL_TEXTURE_2D,m_tex);
	glEnable(GL_TEXTURE_2D);
	m_ripplepb->BindAsTexture(WGL_FRONT_LEFT_ARB);

	t/=m_duration;
	m_point.z=t*m_radius;
	m_point.w=(1.0f-t)*m_intensity;

	if (m_point_param)
		//*cgGLSetParameter4fv(m_point_param,&m_point.x);

	//*cgGLBindProgram(m_ripple_prog);
	//*cgGLEnableProfile(m_profile);
	
	draw_rect();

	//*cgGLDisableProfile(m_profile);
	m_ripplepb->ReleaseTexture(WGL_FRONT_LEFT_ARB);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,g_render->sizex,0,g_render->sizey,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,(float)g_render->sizey,0);
	glScalef(1,-1,1);
#endif
}

void pRenderRipple::build_grid()
{
	delete m_gridvert;
	m_gridvert=new float [2*(m_vertexgridsize+1)*(m_vertexgridsize+1)];

	float f=1.0f/m_vertexgridsize,*fp=m_gridvert;
	int i,j;

	for( j=0;j<=m_vertexgridsize;j++ )
	for( i=0;i<=m_vertexgridsize;i++ )
	{
		fp[0]=i*f;
		fp[1]=j*f;
		fp+=2;
	}
}

void pRenderRipple::draw_rect()
{
	if (m_prog==2)
	{
		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,0.0f);
			glTexCoord2f(1.0f,0.0f); glVertex2f(1.0f,0.0f);
			glTexCoord2f(1.0f,1.0f); glVertex2f(1.0f,1.0f);
			glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,1.0f);
		//*glEnd();
	}
	else
	{
		int i,j,k=0;
		if (m_vertexbuffer)
		{
			glVertexPointer(2,GL_FLOAT,sizeof(float)*2,m_gridvert);
			glTexCoordPointer(2,GL_FLOAT,sizeof(float)*2,m_gridvert);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);

			for( j=0;j<m_vertexgridsize;j++ )
			{
				//*glBegin(GL_QUAD_STRIP);
				for( i=0;i<=m_vertexgridsize;i++ )
				{
					glArrayElement(k+m_vertexgridsize+1);
					glArrayElement(k);
					k++;
				}
				//*glEnd();
			}

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else
			for( j=0;j<m_vertexgridsize;j++ )
			{
				//*glBegin(GL_QUAD_STRIP);
				for( i=0;i<=m_vertexgridsize;i++ )
				{
					glTexCoord2fv(&m_gridvert[k+(m_vertexgridsize+1)*2]);
					glVertex2fv(&m_gridvert[k+(m_vertexgridsize+1)*2]);
					glTexCoord2fv(&m_gridvert[k]);
					glVertex2fv(&m_gridvert[k]);
					k+=2;
				}
				//*glEnd();
			}
	}
}

void pRenderRipple::add_ripple(float posu,float posv,float radius,float duration,float intensity)
{
	m_start_time=g_render->curtimef;
	m_duration=duration;
	m_radius=radius;
	m_intensity=intensity;
	m_point.x=posu;
	m_point.y=posv;
	m_point.z=0;
	m_point.w=0;
}	

#endif
