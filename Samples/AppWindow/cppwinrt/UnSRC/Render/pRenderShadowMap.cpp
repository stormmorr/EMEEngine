#include "pch.h"
#include "paralelo3d.h"

#ifndef P_DISABLE_3D

bool pRenderShadowMap::s_support_NV_render_depth_texture=false;

pRenderShadowMap::pRenderShadowMap() :
	m_shadow_buffer(NULL),
	m_size(512),
	m_shadow_map(0),
	m_shadow_offset_factor(2.0f),
	m_shadow_offset_units(4.0f)
{ }

pRenderShadowMap::~pRenderShadowMap()
{
	reset();
}

void pRenderShadowMap::init(int size)
{
	reset();
	if (size>0 && test())
	{
		pVector white(1.0f,1.0f,1.0f,1.0f);

		// initialize p-buffer only for render to depth
		m_shadow_buffer=new pPBuffer(size,size,0,false,true,false,true,s_support_NV_render_depth_texture,false,false,true,0);
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
}

void pRenderShadowMap::reset()
{
	if(m_shadow_map)
	{
		glDeleteTextures(1,&m_shadow_map);
		m_shadow_map=0;
	}

	if(m_shadow_buffer)
	{
		delete m_shadow_buffer;
		m_shadow_buffer=NULL;
	}
}

void pRenderShadowMap::setup_camera(pLight *light)
{
	// setup a camera of view point light
	if(light)
	{
		pVector pos(light->pos.x,light->pos.y,light->pos.z);
		pVector view(pos-light->orientation.get_column3(2));
		pVector up(light->orientation.get_column3(1));

		glViewport(0,0,m_size,m_size);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(light->angle,1.0,g_render->nearplane,light->pos.w);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(pos.x,pos.y,pos.z,view.x,view.y,view.z,up.x,up.y,up.z);
	}
}

void pRenderShadowMap::generate_shadow_map(pLight *light)
{
	if(m_shadow_buffer && light)
	{
		m_shadow_buffer->Bind();
			glEnable(GL_DEPTH_TEST);
			glClear(GL_DEPTH_BUFFER_BIT);
			glPolygonOffset(m_shadow_offset_factor,m_shadow_offset_units);
			glEnable(GL_POLYGON_OFFSET_FILL);
			
			// setup camera to light view point 
			setup_camera(light);

			// draw all objects affected by current light
			g_render->draw(light->objlistlight);

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
}

void pRenderShadowMap::bind_shadow_map(pLight *light) const
{
 	if(m_shadow_buffer && light)
	{
		pVector pos(light->pos.x,light->pos.y,light->pos.z);
		pVector view(pos-light->orientation.get_column3(2));
		pVector up(light->orientation.get_column3(1));
		pVector v;

		// clean some texture units 0, 1 and 2
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);

		// select texture unit 3
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glBindTexture(GL_TEXTURE_2D,m_shadow_map);
		glEnable(GL_TEXTURE_2D);
		if(s_support_NV_render_depth_texture)
			m_shadow_buffer->BindAsTexture(WGL_DEPTH_COMPONENT_NV);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glEnable(GL_TEXTURE_GEN_R);
		glEnable(GL_TEXTURE_GEN_Q);

		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
		glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
		glTexGeni(GL_Q,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);

		// it works only if current modelview is equals to current view
		v.vec(1.0f,0.0f,0.0f,0.0f);
		glTexGenfv(GL_S,GL_EYE_PLANE,&v.x);
		v.vec(0.0f,1.0f,0.0f,0.0f);
		glTexGenfv(GL_T,GL_EYE_PLANE,&v.x);
		v.vec(0.0f,0.0f,1.0f,0.0f);
		glTexGenfv(GL_R,GL_EYE_PLANE,&v.x);
		v.vec(0.0f,0.0f,0.0f,1.0f);
		glTexGenfv(GL_Q,GL_EYE_PLANE,&v.x);

		// set up the depth texture projection
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glTranslatef(0.5f,0.5f,0.5f); // offset
		glScalef(0.5f,0.5f,0.5f); // bias
		gluPerspective(light->angle,1.0,g_render->nearplane,light->pos.w);
		gluLookAt(pos.x,pos.y,pos.z,view.x,view.y,view.z,up.x,up.y,up.z);
		glMatrixMode(GL_MODELVIEW);

		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
}

void pRenderShadowMap::unbind_shadow_map() const
{
	if(m_shadow_buffer)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		if(s_support_NV_render_depth_texture)
			m_shadow_buffer->ReleaseTexture(WGL_DEPTH_COMPONENT_NV);
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_GEN_Q);
		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
}

void pRenderShadowMap::draw() const
{
    glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_ONE,GL_ZERO);
	glColor4f(1,1,1,1);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glBindTexture(GL_TEXTURE_2D,m_shadow_map);
	glEnable(GL_TEXTURE_2D);
	if(s_support_NV_render_depth_texture)
		m_shadow_buffer->BindAsTexture(WGL_DEPTH_COMPONENT_NV);
	//*glBegin(GL_QUADS);
		glMultiTexCoord2f(GL_TEXTURE2_ARB,0.0f,0.0f); glVertex2f(0.0f,0.0f);
		glMultiTexCoord2f(GL_TEXTURE2_ARB,1.0f,0.0f); glVertex2f(1.0f,0.0f);
		glMultiTexCoord2f(GL_TEXTURE2_ARB,1.0f,1.0f); glVertex2f(1.0f,1.0f);
		glMultiTexCoord2f(GL_TEXTURE2_ARB,0.0f,1.0f); glVertex2f(0.0f,1.0f);
	//*glEnd();
	glDisable(GL_TEXTURE_2D);
	if(s_support_NV_render_depth_texture)
		m_shadow_buffer->ReleaseTexture(WGL_DEPTH_COMPONENT_NV);
	glActiveTextureARB(GL_TEXTURE0_ARB);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}

void pRenderShadowMap::bind_pbuffer_as_texture() const
{
	if(m_shadow_buffer && s_support_NV_render_depth_texture)
		m_shadow_buffer->BindAsTexture(WGL_DEPTH_COMPONENT_NV);
}

void pRenderShadowMap::release_pbuffer_texture() const
{
	if(m_shadow_buffer && s_support_NV_render_depth_texture)
		m_shadow_buffer->ReleaseTexture(WGL_DEPTH_COMPONENT_NV);
}

P3D_API bool pRenderShadowMap::test()
{
	const char *wglext="";
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if (wglGetExtensionsStringARB)
		wglext=wglGetExtensionsStringARB(wglGetCurrentDC());
	const char *glext=(const char *)glGetString(GL_EXTENSIONS);

	if(glext && strstr(wglext,"WGL_NV_render_depth_texture"))
		s_support_NV_render_depth_texture=true;
	else
		s_support_NV_render_depth_texture=false;

	if (glext && strstr(wglext,"WGL_ARB_pbuffer") &&
		strstr(wglext,"WGL_ARB_render_texture") &&
		strstr(glext,"GL_ARB_depth_texture") &&
		strstr(glext,"GL_ARB_shadow"))
		return true;

	return false;
}

#endif
