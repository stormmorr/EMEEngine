#include "pch.h"
#include "paralelo3d.h"
#ifndef P_DISABLE_3D

P3D_API bool pRenderGlow::test()
{
#if 0 // P_SUPPORT_CG
	const char *wglext="";
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if (wglGetExtensionsStringARB)
		wglext=wglGetExtensionsStringARB(wglGetCurrentDC());
	if (strstr(wglext,"WGL_ARB_pbuffer") &&
		strstr(wglext,"WGL_ARB_render_texture"))
		return true;
#endif
	return false;
}

void pRenderGlow::init(int size)
{
	reset();
	if (size>0 && test() && load_program())
	{
		m_size=size;
		m_glowpb[0]=new pPBuffer(size,size,32,false,true,false,true,false,false,false,true,0);
		m_glowpb[1]=new pPBuffer(size,size,32,false,true,false,true,false,false,false,true,0);

		for( int i=0;i<2;i++ )
		{
			m_glowpb[i]->Bind();
			glDrawBuffer(GL_FRONT);
			glClearColor(0,0,0,1);
			glClearDepth(1);
			glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_TRUE);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			m_glowpb[i]->Unbind();
		}
		
		glGenTextures(1,&m_tex);
		glBindTexture(GL_TEXTURE_2D,m_tex);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);
	}
}

void pRenderGlow::reset()
{
#if 0 // P_SUPPORT_CG
	//if (m_blur_prog)
	//	cgDestroyProgram(m_blur_prog);
	m_blur_prog=0;
	m_texture_param=0;
	m_dispuv_param=0;
#endif

	if (m_tex)
		glDeleteTextures(1,&m_tex);
	m_tex=0;

	delete m_glowpb[0];
	delete m_glowpb[1];
	m_glowpb[0]=0;
	m_glowpb[1]=0;
	m_curpb=0;
}

bool pRenderGlow::load_program()
{
#if 0 // P_SUPPORT_CG
	char *programtext;
	pString str;
	
	CgCheckError();
	str=g_render->app_path+g_render->shader_path+"shaders/cg_blur.cg";
	programtext=LoadTextFile(str);
	if (programtext)
	{
		m_blur_prog = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, CG_PROFILE_ARBFP1, "main_blur",0);
		delete programtext;
		if (m_blur_prog && CgCheckError()==false)
		{
			//*cgGLLoadProgram(m_blur_prog);
			if (CgCheckError()==false)
			{
				m_dispuv_param = cgGetNamedParameter(m_blur_prog, "dispuv");
				m_texture_param = cgGetNamedParameter(m_blur_prog, "texture");
				return true;
			}
		}
	}
#endif	
	return false;
}

void pRenderGlow::generate_glow()
{
#if 0 // P_SUPPORT_CG
	m_curpb=!m_curpb;
	int i,j,k;

	m_glowpb[m_curpb]->Bind();
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_ONE,GL_ZERO);
	glDepthFunc(GL_LEQUAL);
	g_render->set_camera();

	g_render->rendermode=P_RENDERMODE_GLOW;
	g_render->renderflag=P_RENDERFLAG_TEXTURE;
//#ifdef P_MANAGER_OBJ
	g_render->draw(g_romanager->m_active_visible);
//#endif
	g_render->rendermode=0;
	g_render->renderflag=0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_ONE,GL_ONE);
	
	glBindTexture(GL_TEXTURE_2D,m_tex);
	glEnable(GL_TEXTURE_2D);
	m_glowpb[!m_curpb]->BindAsTexture(WGL_FRONT_LEFT_ARB);
	glColor4f(m_blurfeedbackfact,m_blurfeedbackfact,m_blurfeedbackfact,1.0f);
	draw_rect(false);
	if (m_blurfeedbackfact>1.0f)
	{
		glColor4f(m_blurfeedbackfact-1.0f,m_blurfeedbackfact-1.0f,m_blurfeedbackfact-1.0f,1.0f);
		draw_rect(false);
	}
	m_glowpb[!m_curpb]->ReleaseTexture(WGL_FRONT_LEFT_ARB);

	m_glowpb[m_curpb]->Unbind();

	k=7;
	//*CGparameter param;
	float fp=1.33f/m_size,f=1.0f/k;

	for( i=0;i<(int)m_blurnumpass;i++ )
	{
		for( j=0;j<k;j++ )
		{
			param=cgGetArrayParameter(m_dispuv_param,j);
			//*cgGLSetParameter3f(param,(j-(k>>1))*fp,0,f);
		}

		m_glowpb[!m_curpb]->Bind();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,1,0,1,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDepthFunc(GL_ALWAYS);
		glBlendFunc(GL_ONE,GL_ZERO);
		glBindTexture(GL_TEXTURE_2D,m_tex);
		m_glowpb[m_curpb]->BindAsTexture(WGL_FRONT_LEFT_ARB);
		glColor4f(1,1,1,1);
		draw_rect(true);
		m_glowpb[m_curpb]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		m_glowpb[!m_curpb]->Unbind();
		m_curpb=!m_curpb;

		for( j=0;j<k;j++ )
		{
			param=cgGetArrayParameter(m_dispuv_param,j);
			//*cgGLSetParameter3f(param,0,(j-(k>>1))*fp,f);
		}

		m_glowpb[!m_curpb]->Bind();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0,1,0,1,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDepthFunc(GL_ALWAYS);
		glBlendFunc(GL_ONE,GL_ZERO);
		glBindTexture(GL_TEXTURE_2D,m_tex);
		m_glowpb[m_curpb]->BindAsTexture(WGL_FRONT_LEFT_ARB);
		glColor4f(1,1,1,1);
		draw_rect(true);
		m_glowpb[m_curpb]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		m_glowpb[!m_curpb]->Unbind();
		m_curpb=!m_curpb;

		printf("RR");
	}
#endif
}

void pRenderGlow::draw_glow()
{
#if 0 // P_SUPPORT_CG
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	g_render->sel_tex(-1);
	glBindTexture(GL_TEXTURE_2D,m_tex);
	glEnable(GL_TEXTURE_2D);
	m_glowpb[m_curpb]->BindAsTexture(WGL_FRONT_LEFT_ARB);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);

	glBlendFunc(GL_ONE,GL_ONE);
	glColor4f(1,1,1,1);
	draw_rect(false);
	m_glowpb[m_curpb]->ReleaseTexture(WGL_FRONT_LEFT_ARB);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,g_render->sizex,0,g_render->sizey,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,(float)g_render->sizey,0);
	glScalef(1,-1,1);
#endif
}

void pRenderGlow::draw_rect(bool blur)
{
#if 0 // P_SUPPORT_CG
	if (blur)
	{
		//*cgGLBindProgram(m_blur_prog);
		//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
	}

	//*glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,0.0f);
		glTexCoord2f(1.0f,0.0f); glVertex2f(1.0f,0.0f);
		glTexCoord2f(1.0f,1.0f); glVertex2f(1.0f,1.0f);
		glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,1.0f);
	//*glEnd();

	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
#endif
}


#endif
