#include "pch.h"
#include "paralelo3d.h"

#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG

int pRenderProfileFragmentMP::test() const
{
	if (GLEW_ARB_vertex_program && GLEW_ARB_fragment_program)
		return 1;
	else 
		return 0;
}

int pRenderProfileFragmentMP::get_caps() const
{
	return P_RENDERCAPS_MULTI_PASS|P_RENDERCAPS_SHADOWS|P_RENDERCAPS_PIXEL_LIGHTING;
}

void pRenderProfileFragmentMP::print(pString& str) const
{
	str.format("%s",(const char *)name);
}

void pRenderProfileFragmentMP::reset()
{
	if (cgprog_vert_ambient)
		cgDestroyProgram(cgprog_vert_ambient);
	cgprog_vert_ambient=0;

	if (cgprog_vert_light)
		cgDestroyProgram(cgprog_vert_light);
	cgprog_vert_light=0;

	if (cgprog_frag_light)
		cgDestroyProgram(cgprog_frag_light);
	cgprog_frag_light=0;

	if (cgprog_vert_shadow)
		cgDestroyProgram(cgprog_vert_shadow);
	cgprog_vert_shadow=0;

	cgparam_vert_shadow_modelviewproj=0;
	cgparam_vert_shadow_lightpos=0;

	cgparam_vert_viewinverse=0;
	cgparam_vert_lightviewprojbias=0;
	cgparam_vert_farplane=0;
	cgparam_vert_camerapos=0;
	cgparam_vert_lightpos=0;
	cgparam_vert_lightspot=0;

	cgparam_frag_camerapos=0;
	cgparam_frag_specular=0;
	cgparam_frag_skincolor=0;
	cgparam_frag_lightcolor=0;
	cgparam_frag_lightpos=0;
	cgparam_frag_lightspot=0;
	cgparam_frag_shadowmapflag=0;
	cgparam_frag_bump=0;
}

void pRenderProfileFragmentMP::load()
{
	char *programtext;
	pString str;

	bool ati=false;
	if (glGetString(GL_VENDOR))
		ati=(strstr((char *)glGetString(GL_VENDOR),"ATI Technologies")!=0);

	char *options[16];
	options[0]="-posinv";
	options[1]=0;

	str=g_render->app_path+g_render->shader_path+"shaders/cg_vert_shadow.cg";
	programtext=LoadTextFile(str);
	if (programtext)
	{
		cgprog_vert_shadow = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, vert_profile, g_render->svtype?"main_vert_shadow_edge":"main_vert_shadow",(const char **)options);
		CgCheckError();
		delete programtext;

		if (cgprog_vert_shadow)
		{
			//*cgGLLoadProgram(cgprog_vert_shadow);
			CgCheckError();

			cgparam_vert_shadow_modelviewproj = cgGetNamedParameter(cgprog_vert_shadow, "modelviewproj");
			cgparam_vert_shadow_lightpos = cgGetNamedParameter(cgprog_vert_shadow, "lightpos");
		}
	}

	str=g_render->app_path+g_render->shader_path+"shaders/cg_vert_ambient.cg";
	programtext=LoadTextFile(str);
	if (programtext)
	{
		cgprog_vert_ambient = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, vert_profile, "main_vert_ambient",(const char **)options);
		CgCheckError();
		delete programtext;

		if (cgprog_vert_ambient)
		{
			//*cgGLLoadProgram(cgprog_vert_ambient);
			CgCheckError();
		}
	}

	if (full)
		str=g_render->app_path+g_render->shader_path+"shaders/cg_frag_light_full.cg";
	else
		str=g_render->app_path+g_render->shader_path+"shaders/cg_frag_light.cg";
	programtext=LoadTextFile(str);
	if (programtext)
	{
		if(g_render->shadowflag)
		{
			options[1]="-DSHADOW_MAP";
			options[2]=0;
		}
		cgprog_vert_light = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, vert_profile, "main_vert",(const char **)options);
		CgCheckError();
		
		if (cgprog_vert_light)
		{
			//*cgGLLoadProgram(cgprog_vert_light);
			CgCheckError();

			cgparam_vert_viewinverse=cgGetNamedParameter(cgprog_vert_light, "viewinverse");
			cgparam_vert_lightviewprojbias=cgGetNamedParameter(cgprog_vert_light, "lightviewprojbias");
			cgparam_vert_farplane=cgGetNamedParameter(cgprog_vert_light, "farplane");
			cgparam_vert_camerapos=cgGetNamedParameter(cgprog_vert_light, "camerapos");
			cgparam_vert_lightpos=cgGetNamedParameter(cgprog_vert_light, "lightpos");
			cgparam_vert_lightspot=cgGetNamedParameter(cgprog_vert_light, "lightspot");
		}

		int i=0;
		options[i]=0;
		if(g_render->shadowflag)
		{
			options[i++]="-DSHADOW_MAP";
			options[i]=0;
		}
		if(GLEW_ARB_shadow && !ati)
		{
			options[i++]="-DARB_SHADOW";
			options[i]=0;
		}
#ifdef P_TONY
		options[i++]="-DTONY";
		options[i]=0;
#endif
		cgprog_frag_light = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, frag_profile, "main_frag",(const char **)options);
		CgCheckError();

		if (cgprog_frag_light)
		{
			//*cgGLLoadProgram(cgprog_frag_light);
			CgCheckError();

			cgparam_frag_camerapos=cgGetNamedParameter(cgprog_frag_light, "camerapos");
			cgparam_frag_specular=cgGetNamedParameter(cgprog_frag_light, "specular");
			cgparam_frag_skincolor=cgGetNamedParameter(cgprog_frag_light, "skincolor");
			cgparam_frag_lightcolor=cgGetNamedParameter(cgprog_frag_light, "lightcolor");
			cgparam_frag_lightpos=cgGetNamedParameter(cgprog_frag_light, "lightpos");
			cgparam_frag_lightspot=cgGetNamedParameter(cgprog_frag_light, "lightspot");
			cgparam_frag_shadowmapflag=cgGetNamedParameter(cgprog_frag_light, "shadowmapflag");
			cgparam_frag_bump=cgGetNamedParameter(cgprog_frag_light, "bump");
		}

		delete programtext;
	}
	null_normalmap=g_render->build_onepixelmap(127,127,255);
	null_texturemap=g_render->build_onepixelmap(255,255,255);
}

void pRenderProfileFragmentMP::draw_mp(pLight *l)
{
	//*cgGLEnableProfile(vert_profile);
	//*cgGLEnableProfile(frag_profile);
	//*cgGLBindProgram(cgprog_vert_light);
	//*cgGLBindProgram(cgprog_frag_light);

	// necessary for shadow map
	pVector pos(l->pos.x,l->pos.y,l->pos.z);
	pVector view(pos-l->orientation.get_column3(2));
	pVector up(l->orientation.get_column3(1));
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.5f,0.5f,0.5f); // offset
	glScalef(0.5f,0.5f,0.5f); // bias
	gluPerspective(l->angle,1.0,g_render->nearplane,l->pos.w);
	gluLookAt(pos.x,pos.y,pos.z,view.x,view.y,view.z,up.x,up.y,up.z);
	//*cgGLSetStateMatrixParameter(cgparam_vert_lightviewprojbias,CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_IDENTITY);
	glPopMatrix();

	// necessary for shadow map
	bool shadow_map_flag=
		g_render->rs.m_shadow_buffer &&
		g_render->shadowflag && 
		(l->flags&P_LIGHTFLAGS_NOSHADOW)==0 && 
		l->type_shadow==pLight::SHADOW_MAP &&
		l->angle>0.0f;
	if(shadow_map_flag)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		//*cgGLSetParameter1f(cgparam_frag_shadowmapflag,1.0f);
		glBindTexture(GL_TEXTURE_2D,g_render->rs.m_shadow_map);
		glEnable(GL_TEXTURE_2D);
		g_render->rs.bind_pbuffer_as_texture();
		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
	else
		//*cgGLSetParameter1f(cgparam_frag_shadowmapflag,0.0f);

	pVector lightspot=-l->orientation.get_column3(2);
	lightspot.w=l->angle==0.0f?1.0f:1.0f-cosf(0.5f*l->angle*PIOVER180);
	//*cgGLSetParameter3fv(cgparam_frag_camerapos,&g_render->camera.pos.x);
	//*cgGLSetParameter3fv(cgparam_vert_camerapos,&g_render->camera.pos.x);
	//*cgGLSetParameter4fv(cgparam_frag_lightcolor,&l->color.x);
	//*cgGLSetParameter4fv(cgparam_frag_lightpos,&l->pos.x);
	//*cgGLSetParameter4fv(cgparam_vert_lightpos,&l->pos.x);
	//*cgGLSetParameter4fv(cgparam_frag_lightspot,&lightspot.x);
	//*cgGLSetParameter4fv(cgparam_vert_lightspot,&lightspot.x);
	//*cgGLSetParameter1f(cgparam_vert_farplane,g_render->fog?g_render->farplane:0.0f);

	glPushMatrix();
	glLoadMatrixf(g_render->view_matrix.mf);
	//*cgGLSetStateMatrixParameter(cgparam_vert_viewinverse,CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_INVERSE);
	glPopMatrix();

	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT;
	
	g_render->draw(l->objlistlight);

	// necessary for shadow map
	if(shadow_map_flag)
	{
		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		g_render->rs.release_pbuffer_texture();
		glActiveTextureARB(GL_TEXTURE0_ARB);
	}

	//*cgGLDisableProfile(vert_profile);
	//*cgGLDisableProfile(frag_profile);

	g_render->reset_tex_state();
}

void pRenderProfileFragmentMP::draw_mp(pArray<pRenderObject *>& o)
{
	int i,j;
	pMesh *m=NULL;

	// activate vertex and fragment programs
	//*cgGLEnableProfile(vert_profile);
	//*cgGLEnableProfile(frag_profile);
	//*cgGLBindProgram(cgprog_vert_light);
	//*cgGLBindProgram(cgprog_frag_light);

	// set shadow map flag Cg parameter
	//*cgGLSetParameter1f(cgparam_frag_shadowmapflag,0.0f);

	// set camera position Cg parameter
	//*cgGLSetParameter3fv(cgparam_vert_camerapos,&g_render->camera.pos.x);
	//*cgGLSetParameter3fv(cgparam_frag_camerapos,&g_render->camera.pos.x);

	// set far plane Cg parameter
	//*cgGLSetParameter1f(cgparam_vert_farplane,g_render->fog?g_render->farplane:0.0f);

	// set inverse view matrix Cg parameter
	glPushMatrix();
	glLoadMatrixf(g_render->view_matrix.mf);
	//*cgGLSetStateMatrixParameter(cgparam_vert_viewinverse,CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_INVERSE);
	glPopMatrix();

	// for each object
	for( i=0;i<o.num;i++ )
	{
		// get object's mesh
		m=o[i]->get_mesh();
		
		// set render flag
		g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT;

		// for each object's light
		for( j=0;j<o[i]->m_light.num;j++)
		{
			// get object's light
			pLight *l=o[i]->m_light[j];

			// set light attributes to Cg programs
			pVector lightspot=-l->orientation.get_column3(2);
			lightspot.w=l->angle==0.0f?1.0f:1.0f-cosf(0.5f*l->angle*PIOVER180);
			//*cgGLSetParameter4fv(cgparam_frag_lightcolor,&l->color.x);
			//*cgGLSetParameter4fv(cgparam_vert_lightpos,&l->pos.x);
			//*cgGLSetParameter4fv(cgparam_frag_lightpos,&l->pos.x);
			//*cgGLSetParameter4fv(cgparam_vert_lightspot,&lightspot.x);
			//*cgGLSetParameter4fv(cgparam_frag_lightspot,&lightspot.x);

			// draw object
			glPushAttrib(GL_FOG_BIT|GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			o[i]->draw();
			glPopMatrix();
			glPopAttrib();
		}
	}

	// disable Cg programs
	//*cgGLDisableProfile(vert_profile);
	//*cgGLDisableProfile(frag_profile);

	g_render->reset_tex_state();
}

void pRenderProfileFragmentMP::draw_shadows(pLight *l)
{
	if(l)
	{
		pVector lpos;	
		
		//*cgGLBindProgram(cgprog_vert_shadow);
		//*cgGLEnableProfile(vert_profile);

		for(int i=0;i<l->objlistlight.num;i++)
		{
			lpos=l->pos-l->objlistlight[i]->m_transform_global.get_translate();
			lpos=l->objlistlight[i]->m_transform_global.multiply_rotation_transpose(lpos);
			lpos.w=l->pos.w;

			//*cgGLSetParameter4fv(cgparam_vert_shadow_lightpos,&lpos.x);

			glPushMatrix();
			glMultMatrixf(&l->objlistlight.buf[i]->m_transform_global.mf[0]);
			//*cgGLSetStateMatrixParameter(cgparam_vert_shadow_modelviewproj,CG_GL_MODELVIEW_PROJECTION_MATRIX,CG_GL_MATRIX_IDENTITY);
			g_render->draw_shadows(l,l->objlistlight.buf[i]);
			glPopMatrix();
		}

		//*cgGLDisableProfile(vert_profile);
	}
}


void pRenderProfileFragmentMP::draw_sp(pArray<pRenderObject *>& o)
{
}

void pRenderProfileFragmentMP::load_mat(const pMaterial *mat,int rendermode)
{
	if (mat->texid!=-1 && 
		g_render->pic.buf[mat->texid] &&
		g_render->pic.buf[mat->texid]->bytespixel==4)
	{
		glAlphaFunc(GL_GREATER,g_render->alphatestval);
		glEnable(GL_ALPHA_TEST);
	}

	if (mat->flags&P_MATFLAGS_TWOSIDE)
		glDisable(GL_CULL_FACE);

	if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
	{
		glDisable(GL_FOG);
		//*cgGLSetParameter1f(cgparam_vert_farplane,0.0f);
	}

	if(rendermode&P_RENDERMODE_AMBIENT) // ambient pass
	{
		if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			g_render->sel_tex(mat->texselfillumid);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}
		if ((mat->flags&P_MATFLAGS_NOENVMAP)==false && g_render->maxtextureunits>2)
		{
			if (g_render->env_map_mode==P_ENVMODE_CUBE_MAPPING && g_render->cube_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glBindTexture(GL_TEXTURE_CUBE_MAP,g_render->cube_map_tex);
				glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_REPEAT);
				glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
				glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
				glTexGenf(GL_R,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
				glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
				glEnable(GL_TEXTURE_GEN_R);
				glEnable(GL_TEXTURE_CUBE_MAP);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else if (g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glBindTexture(GL_TEXTURE_2D,g_render->sph_map_tex);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
				glTexGenf(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
				glTexGenf(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
				glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
				glEnable(GL_TEXTURE_2D);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
		}
		g_render->sel_tex(mat->texid);
		
		pVector v=mat->diffuse*g_render->lightambient+mat->selfillum;
		glColor4f(v.x,v.y,v.z,mat->opacity);
	}
	else
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		if (mat->texnormalid==-1)
			g_render->sel_tex(null_normalmap);
		else
			g_render->sel_tex(mat->texnormalid);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		if (mat->texid==-1)
			g_render->sel_tex(null_texturemap);
		else
			g_render->sel_tex(mat->texid);

		glColor4f(mat->diffuse.x,mat->diffuse.y,mat->diffuse.z,mat->opacity);
		//*cgGLSetParameter4fv(cgparam_frag_specular,&mat->specular.x);
		//*cgGLSetParameter3fv(cgparam_frag_skincolor,&mat->skincolor.x);
#ifdef P_TONY
		//*cgGLSetParameter1f(cgparam_frag_bump,mat->bump);
#endif
	}
}

void pRenderProfileFragmentMP::unload_mat(const pMaterial *mat,int rendermode)
{
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);

	if(rendermode&P_RENDERMODE_AMBIENT) // ambient pass
	{
		if ((mat->flags&P_MATFLAGS_NOENVMAP)==false && g_render->maxtextureunits>2)
		{
			if (g_render->env_map_mode==P_ENVMODE_CUBE_MAPPING && g_render->cube_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_GEN_R);
				glDisable(GL_TEXTURE_CUBE_MAP);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else if (g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
		}
		if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glDisable(GL_TEXTURE_2D);
		}
	}

	if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
	{
		glEnable(GL_FOG);
		//*cgGLSetParameter1f(cgparam_vert_farplane,g_render->farplane);
	}
}

#endif
#endif
