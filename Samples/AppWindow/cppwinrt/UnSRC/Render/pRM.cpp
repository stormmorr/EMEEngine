#include "pch.h"
#include "paralelo3d.h"

#if 0 // P_SUPPORT_CG

//*CGprofile pRM::s_frag_profile[P_RM_PROFILES]={ CG_PROFILE_ARBFP1,CG_PROFILE_ARBFP1,CG_PROFILE_ARBFP1,CG_PROFILE_ARBFP1,CG_PROFILE_FP40 };
char *pRM::s_frag_ext[P_RM_PROFILES]={ "GL_ARB_fragment_program","GL_ARB_fragment_program","GL_ARB_fragment_program","GL_ARB_fragment_program","GL_NV_fragment_program2" };
char *pRM::s_frag_main[P_RM_PROFILES]={ "main_frag_normal","main_frag_parallax","main_frag_relief","main_frag_relief","main_frag_relief" };

pRM::pRM()
{
	m_shadows=0;
	m_doubleprec=0;
	m_depthcorrect=0;
	m_depthbias=0;
	m_borderclamp=0;
	m_curved=0;
	m_progmode=0;

	m_vert_prog=0;

	m_frag_prog=0;
	m_lightpos=0;
	m_lightspot=0;
	m_tile=0;
	m_depth=0;
	m_ambient=0;
	m_diffuse=0;
	m_specular=0;
	m_planes=0;
	m_viewinv_lightviewprojbias=0;

	m_frag_shadow_prog=0;
	m_tile_sh=0;
	m_depth_sh=0;
	m_planem_sh=0;
}

pRM::~pRM()
{
	free_programs();
}

bool pRM::load_programs(int progmode,bool shadows,bool doubleprec,bool depthcorrect,bool depthbias,bool borderclamp,bool curved)
{
	if (g_render==0)
		return false;
	
	free_programs();

	if (progmode<0) progmode=0;
	if (progmode>=P_RM_PROFILES) progmode=P_RM_PROFILES-1;

	pString str;
	char *glstr=(char *)glGetString(GL_EXTENSIONS);
	while(progmode>-1)
	{
		if (glstr && strstr(glstr,s_frag_ext[progmode]))
			break;
		progmode--;
	}

	m_progmode=progmode;
	m_shadows=shadows;
	m_doubleprec=doubleprec;
	m_depthcorrect=depthcorrect;
	m_depthbias=depthbias;
	m_borderclamp=borderclamp;
	m_curved=curved;

	if (progmode<0)
		return false;

	int i=0;
	char *m_frag_options[16];
	m_frag_options[0]=0;
	if (m_shadows)
	{
		m_frag_options[i]="-DRM_SHADOWS";
		m_frag_options[i+1]=0;
		i++;
	}
	if (m_doubleprec)
	{
		m_frag_options[i]="-DRM_DOUBLEPRECISION";
		m_frag_options[i+1]=0;
		i++;
	}
	if (m_depthcorrect)
	{
		m_frag_options[i]="-DRM_DEPTHCORRECT";
		m_frag_options[i+1]=0;
		i++;
	}
	if (m_depthbias)
	{
		m_frag_options[i]="-DRM_DEPTHBIAS";
		m_frag_options[i+1]=0;
		i++;
	}
	if (m_borderclamp)
	{
		m_frag_options[i]="-DRM_BORDERCLAMP";
		m_frag_options[i+1]=0;
		i++;
	}
	if (m_progmode==2)
	{
		m_frag_options[i]="-DRM_POM";
		m_frag_options[i+1]=0;
		i++;
	}

	int ret=0;
	
	str.format("%s%sshaders\\cg_relief_map%s.cg",
		(const char *)g_render->app_path,
		(const char *)g_render->shader_path,
		m_curved?"_curved":"_planar");
	char *programtext=LoadTextFile(str);
	if (programtext==0)
		OutputDebugString("pRM: Error loading fragment program!\n");
	else
	{
		m_vert_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBVP1,
				"view_space",
				0);
		if (m_vert_prog==0)
		{
			OutputDebugString("pRM vert: Compiler error:\n");
			OutputDebugString(cgGetErrorString(cgGetError()));
			OutputDebugString("\n");
		}
		else
			ret++;

		m_frag_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				s_frag_profile[m_progmode],
				s_frag_main[m_progmode],
				(const char **)m_frag_options);
		if (m_frag_prog==0)
		{
			OutputDebugString("pRM frag: Compiler error:\n");
			OutputDebugString(cgGetErrorString(cgGetError()));
			OutputDebugString("\n");
		}
		else 
			ret++;

		m_frag_shadow_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				s_frag_profile[m_progmode],
				"main_frag_relief_shadow",
				(const char **)m_frag_options);
		if (m_frag_shadow_prog==0)
		{
			OutputDebugString("pRM frag shadow: Compiler error:\n");
			OutputDebugString(cgGetErrorString(cgGetError()));
			OutputDebugString("\n");
		}
		else 
			ret++;

		if (ret>=2)
		{
			//*cgGLLoadProgram(m_vert_prog);
			CgCheckError();
			
			//*cgGLLoadProgram(m_frag_prog);
			CgCheckError();
			
			m_lightpos=cgGetNamedParameter(m_frag_prog,"lightpos");
			m_lightspot=cgGetNamedParameter(m_frag_prog,"lightspot");
			m_tile=cgGetNamedParameter(m_frag_prog,"tile");
			m_depth=cgGetNamedParameter(m_frag_prog,"depth");
			m_ambient=cgGetNamedParameter(m_frag_prog,"ambient");
			m_diffuse=cgGetNamedParameter(m_frag_prog,"diffuse");
			m_specular=cgGetNamedParameter(m_frag_prog,"specular");
			m_planes=cgGetNamedParameter(m_frag_prog,"planes");
			m_viewinv_lightviewprojbias=cgGetNamedParameter(m_frag_prog,"viewinv_lightviewprojbias");
			CgCheckError();

			if (ret>2)
			{
				//*cgGLLoadProgram(m_frag_shadow_prog);
				CgCheckError();
				
				m_tile_sh=cgGetNamedParameter(m_frag_shadow_prog,"tile");
				m_depth_sh=cgGetNamedParameter(m_frag_shadow_prog,"depth");
				m_planem_sh=cgGetNamedParameter(m_frag_shadow_prog,"planes");
				CgCheckError();
			}
		}
	
		delete programtext;
	}

	if (ret<2)
		free_programs();

	return ret>=2;
}

void pRM::free_programs()
{
	if (m_frag_prog)
		cgDestroyProgram(m_frag_prog);
	m_frag_prog=0;
	if (m_vert_prog)
		cgDestroyProgram(m_vert_prog);
	m_vert_prog=0;
	if (m_frag_shadow_prog)
		cgDestroyProgram(m_frag_shadow_prog);
	m_frag_shadow_prog=0;
}

void pRM::load(int progmode,bool shadows,bool doubleprec,bool depthcorrect,bool depthbias,bool borderclamp,bool curved)
{
	if (m_frag_prog==0 || m_progmode!=progmode || shadows!=m_shadows || 
		m_doubleprec!=doubleprec || m_depthcorrect!=depthcorrect || 
		m_depthbias!=depthbias || m_borderclamp!=borderclamp ||m_curved!=curved) 
		load_programs(progmode,shadows,doubleprec,depthcorrect,depthbias,borderclamp,curved);
}

void pRM::draw_shadows(pMesh *mesh,int relief_tex,unsigned int tile,float depth,float radius)
{
	if (m_frag_shadow_prog==0 || m_vert_prog==0 || mesh==0) 
		return;

	glActiveTextureARB(GL_TEXTURE0_ARB);
	g_render->sel_tex(relief_tex);
	if (tile==0)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	//*cgGLBindProgram(m_vert_prog);
	//*cgGLBindProgram(m_frag_shadow_prog);
	//*cgGLEnableProfile(s_frag_profile[m_progmode]);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (m_tile_sh)
		//*cgGLSetParameter1f(m_tile_sh,tile?(float)tile:1.0f);
	if (m_depth_sh)
		//*cgGLSetParameter1f(m_depth_sh,depth);

	if (m_planem_sh)
		//*cgGLSetParameter2f(m_planem_sh, 
			-radius/(radius-g_render->nearplane),
			-radius*g_render->nearplane/(radius-g_render->nearplane));

	mesh->array_lock(P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT|P_RENDERFLAG_CURVATURE,g_render->vertbuffer);
	mesh->array_draw(g_render->vertbuffer);
	mesh->array_unlock();

	//*cgGLDisableProfile(s_frag_profile[m_progmode]);
	//*cgGLDisableProfile(CG_PROFILE_ARBVP1);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	g_render->sel_tex(-1);
}

void pRM::draw(pMesh *mesh,
			int color_tex,int relief_tex,int dist_tex,
			unsigned int tile,float depth,
			const pVector& amb,const pVector& diff,const pVector& spec,
			pLight* light)
{
	if (m_frag_prog==0 || m_vert_prog==0 || mesh==0) 
		return;

	bool shadowmap = light->angle>0 && g_render->rs.m_shadow_buffer;

	if (shadowmap)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glBindTexture(GL_TEXTURE_2D,g_render->rs.m_shadow_map);
		glEnable(GL_TEXTURE_2D);
		if(pRenderShadowMap::s_support_NV_render_depth_texture)
			g_render->rs.m_shadow_buffer->BindAsTexture(WGL_DEPTH_COMPONENT_NV);
		if (GLEW_ARB_shadow)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,GL_NONE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		}
	}

	if (dist_tex!=-1)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glBindTexture(GL_TEXTURE_2D,g_render->picid[dist_tex]);
		if (tile==0)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	}

	glActiveTextureARB(GL_TEXTURE1_ARB);
	g_render->sel_tex(color_tex);
	if (tile==0)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glActiveTextureARB(GL_TEXTURE0_ARB);
	g_render->sel_tex(relief_tex);
	if (tile==0)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	//*cgGLBindProgram(m_vert_prog);
	//*cgGLBindProgram(m_frag_prog);
	//*cgGLEnableProfile(s_frag_profile[m_progmode]);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	if (shadowmap)
	{
		// necessary for shadow map
		pVector pos(light->pos.x,light->pos.y,light->pos.z);
		pVector view(pos-light->orientation.get_column3(2));
		pVector up(light->orientation.get_column3(1));
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.5f,0.5f,0.5f); // offset
		glScalef(0.5f,0.5f,0.5f); // bias
		gluPerspective(light->angle,1.0,g_render->nearplane,light->pos.w);
		gluLookAt(pos.x,pos.y,pos.z,view.x,view.y,view.z,up.x,up.y,up.z);
		pMatrix m;
		g_render->view_matrix.get_affine_inverse(m);
		glMultMatrixf(m.mf);
		//*cgGLSetStateMatrixParameter(m_viewinv_lightviewprojbias,CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_IDENTITY);
		glPopMatrix();
	}

	//*cgGLSetParameter1f(m_tile,tile?(float)tile:1.0f);
	//*cgGLSetParameter1f(m_depth,depth);

	//*cgGLSetParameter2f(m_planes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	pVector lightpos=g_render->view_matrix*light->pos;	// lightpos in view space
	pVector lightspot=g_render->view_matrix.multiply_rotation(light->orientation.get_column3(2));
	lightspot.w=light->angle==0.0f?1.0f:1.0f-cosf(0.5f*light->angle*PIOVER180);

	//*cgGLSetParameter4fv(m_lightpos,&lightpos.x);
	//*cgGLSetParameter4fv(m_lightspot,&lightspot.x);
	//*cgGLSetParameter4fv(m_ambient,&amb.x);
	//*cgGLSetParameter4fv(m_diffuse,&diff.x);
	//*cgGLSetParameter4fv(m_specular,&spec.x);

	mesh->array_lock(P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT|P_RENDERFLAG_CURVATURE,g_render->vertbuffer);
	mesh->array_draw(g_render->vertbuffer);
	mesh->array_unlock();

	//*cgGLDisableProfile(s_frag_profile[m_progmode]);
	//*cgGLDisableProfile(CG_PROFILE_ARBVP1);

	if (shadowmap)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		if (GLEW_ARB_shadow)
		{
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,GL_COMPARE_R_TO_TEXTURE);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		}
		if(pRenderShadowMap::s_support_NV_render_depth_texture)
			g_render->rs.m_shadow_buffer->ReleaseTexture(WGL_DEPTH_COMPONENT_NV);
	}
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glDisable(GL_TEXTURE_3D);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
}

#endif
