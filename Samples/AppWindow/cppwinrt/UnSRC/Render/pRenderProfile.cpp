#include "pch.h"
#include "paralelo3d.h"

#ifndef P_DISABLE_3D

// pRenderProfile

void pRenderProfile::ambient_pass(pArray<pRenderObject *>& o)
{
	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TEXTURE2;
	g_render->draw(o);
	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE;
}

void pRenderProfile::draw_mp(pArray<pRenderObject *>& o)
{ }

// pRenderProfileStandardSP

int pRenderProfileStandardSP::test() const
{
	return 1;
}

int pRenderProfileStandardSP::get_caps() const
{
	return 0;
}

void pRenderProfileStandardSP::print(pString& str) const
{
	str.format("%s",(const char *)name);
}

void pRenderProfileStandardSP::reset()
{ }

void pRenderProfileStandardSP::load()
{
	m_max_lights=0;
	glGetIntegerv(GL_MAX_LIGHTS,&m_max_lights);
}

void pRenderProfileStandardSP::draw_mp(pLight *l)
{
}

void pRenderProfileStandardSP::draw_mp(pArray<pRenderObject *>& o)
{
}

void pRenderProfileStandardSP::draw_shadows(pLight *l)
{
}

void pRenderProfileStandardSP::draw_sp(pArray<pRenderObject *>& o)
{
	int i,j,k,n;
	pVector v;
	glEnable(GL_LIGHTING);

	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TEXTURE2;

	// do diffuse and specular pass for each object
	for( i=0;i<o.num;i++ )
	{
		// add ambient
		v.vec(1);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&g_render->lightambient.x);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&v.x);

		if((g_render->rendermode&P_RENDERMODE_TRANSP)==0)
			glBlendFunc(GL_ONE,GL_ZERO);
		else
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		j=o.buf[i]->m_light.num;
		do
		{
			n=j>m_max_lights?m_max_lights:j;
			for( k=0;k<n;k++ )
				o.buf[i]->m_light.buf[j-k-1]->turn_on(GL_LIGHT0+k);

			for( ;k<m_max_lights;k++ )
				glDisable(GL_LIGHT0+k);

			// LOG
			if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
				g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(o.buf[i]->m_name));

			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			o.buf[i]->draw();
			glPopMatrix();
			glPopAttrib();

			if((g_render->rendermode&P_RENDERMODE_TRANSP)==0)
				glBlendFunc(GL_ONE,GL_ONE);
			else
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);

			// restore ambient state
			v.vec(0);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&v.x);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&v.x);

			j-=n;
		} while(j>0);
	}

	// restore lighting state
	for( i=0;i<m_max_lights;i++ )
		glDisable(GL_LIGHT0+i);
	glDisable(GL_LIGHTING);
}

void pRenderProfileStandardSP::load_mat(const pMaterial *mat,int rendermode)
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
		glDisable(GL_FOG);

	if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		g_render->sel_tex(mat->texselfillumid);
		glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);
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
		else if(g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
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
	
#ifdef P_TONY
	pVector v=0;
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
#else
	pVector v=mat->specular;
	v.w=1.0f;
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,mat->specular.w);
#endif
	v=mat->selfillum;
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,&v.x);
	glColor4f(mat->diffuse.x,mat->diffuse.y,mat->diffuse.z,mat->opacity);
}

void pRenderProfileStandardSP::unload_mat(const pMaterial *mat,int rendermode)
{
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);
	if ((mat->flags&P_MATFLAGS_NOENVMAP)==false && g_render->maxtextureunits>2)
	{
		if (g_render->env_map_mode==P_ENVMODE_CUBE_MAPPING && g_render->cube_map_tex!=0)
		{
			glActiveTextureARB(GL_TEXTURE2_ARB);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_GEN_R);
			glDisable(GL_TEXTURE_CUBE_MAP);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}
		else if (g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
		{
			glActiveTextureARB(GL_TEXTURE2_ARB);
			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}
	}
	if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glDisable(GL_TEXTURE_2D);
		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
	if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
		glEnable(GL_FOG);
}

// pRenderProfileStandardMP

int pRenderProfileStandardMP::test() const
{
	return 1;
}

int pRenderProfileStandardMP::get_caps() const
{
	return P_RENDERCAPS_MULTI_PASS|P_RENDERCAPS_SHADOWS;
}

void pRenderProfileStandardMP::print(pString& str) const
{
	str.format("%s",(const char *)name);
}

void pRenderProfileStandardMP::reset()
{
#if 0 // P_SUPPORT_CG
	if (cgprog_vert_shadow)
		cgDestroyProgram(cgprog_vert_shadow);
	cgprog_vert_shadow=0;
	cgparam_vert_shadow_modelviewproj=0;
	cgparam_vert_shadow_lightpos=0;
#endif
}

void pRenderProfileStandardMP::load()
{
	m_max_lights=0;
	glGetIntegerv(GL_MAX_LIGHTS,&m_max_lights);

#if 0 // P_SUPPORT_CG
	char *programtext;

	pString str=g_render->app_path+g_render->shader_path+"shaders/cg_vert_shadow.cg";
	programtext=LoadTextFile(str);
	if (programtext)
	{
		cgprog_vert_shadow = cgCreateProgram(g_render->cgcontext, CG_SOURCE, programtext, vert_profile, g_render->svtype?"main_vert_shadow_edge":"main_vert_shadow",0);
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

#endif
}

void pRenderProfileStandardMP::draw_mp(pLight *l)
{
	glEnable(GL_LIGHTING);
	l->turn_on(GL_LIGHT0);

	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE;
	g_render->draw(l->objlistlight);
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void pRenderProfileStandardMP::draw_mp(pArray<pRenderObject *>& o)
{
	int i,j,k,n;
	pVector v;
	glEnable(GL_LIGHTING);

	g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TEXTURE2;

	// do diffuse and specular pass for each object
	for( i=0;i<o.num;i++ )
	{
		// add ambient
		v.vec(1);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&g_render->lightambient.x);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&v.x);

		if((g_render->rendermode&P_RENDERMODE_TRANSP)==0)
			glBlendFunc(GL_ONE,GL_ZERO);
		else
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		j=o.buf[i]->m_light.num;
		do
		{
			n=j>m_max_lights?m_max_lights:j;
			for( k=0;k<n;k++ )
				o.buf[i]->m_light.buf[j-k-1]->turn_on(GL_LIGHT0+k);

			for( ;k<m_max_lights;k++ )
				glDisable(GL_LIGHT0+k);

			// LOG
			if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
				g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(o.buf[i]->m_name));

			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			o.buf[i]->draw();
			glPopMatrix();
			glPopAttrib();

			if((g_render->rendermode&P_RENDERMODE_TRANSP)==0)
				glBlendFunc(GL_ONE,GL_ONE);
			else
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);

			// restore ambient state
			v.vec(0);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&v.x);
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&v.x);

			j-=n;
		} while(j>0);
	}

	// restore lighting state
	for( i=0;i<m_max_lights;i++ )
		glDisable(GL_LIGHT0+i);
	glDisable(GL_LIGHTING);

/*	int i,j;
	pMesh *m=NULL;

	glEnable(GL_LIGHTING);

	// for each object
	for( i=0;i<o.num;i++ )
	{
		// get object's mesh
		m=o[i]->get_mesh();
		
		// set render flag
		g_render->renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE;

		// for each object's light
		for( j=0;j<o[i]->m_light.num;j++)
		{
			// turn on current light
			o[i]->m_light[j]->turn_on(GL_LIGHT0);

			// draw object
			glPushAttrib(GL_FOG_BIT|GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			o[i]->draw();
			glPopMatrix();
			glPopAttrib();
		}
	}

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	g_render->reset_tex_state();*/
}

void pRenderProfileStandardMP::draw_shadows(pLight *l)
{
#if 0 // P_SUPPORT_CG
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
#endif
}


void pRenderProfileStandardMP::draw_sp(pArray<pRenderObject *>& o)
{
	
}

void pRenderProfileStandardMP::load_mat(const pMaterial *mat,int rendermode)
{
	if (g_render->shadowflag)
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
		
		if(mat->flags&P_MATFLAGS_TWOSIDE)
			glDisable(GL_CULL_FACE);
		
		if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
			glDisable(GL_FOG);

		if(rendermode&P_RENDERMODE_AMBIENT) // ambient pass
		{
			pVector v=mat->diffuse*g_render->lightambient+mat->selfillum;
			glColor4f(v.x,v.y,v.z,mat->opacity);

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
		}
		else // diffuse and specular pass
		{
			g_render->sel_tex(mat->texid);

#ifdef P_TONY
			pVector v=0;
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
#else
			pVector v=mat->specular;
			v.w=1.0f;
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,mat->specular.w);
#endif
			v.vec(0);
			glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,&v.x);
			glColor4f(mat->diffuse.x,mat->diffuse.y,mat->diffuse.z,mat->opacity);
		}
	}
	else
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
			glDisable(GL_FOG);

		if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			g_render->sel_tex(mat->texselfillumid);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
			glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);
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
			else if(g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
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
		
#ifdef P_TONY
		pVector v=0;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,1);
#else
		pVector v=mat->specular;
		v.w=1.0f;
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,&v.x);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,mat->specular.w);
#endif
		v=mat->selfillum;
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,&v.x);
		glColor4f(mat->diffuse.x,mat->diffuse.y,mat->diffuse.z,mat->opacity);
	}
}

void pRenderProfileStandardMP::unload_mat(const pMaterial *mat,int rendermode)
{
	if (g_render->shadowflag)
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
			}
		}
		if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
			glEnable(GL_FOG);
	}
	else
	{
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_CULL_FACE);
		if ((mat->flags&P_MATFLAGS_NOENVMAP)==false && g_render->maxtextureunits>2)
		{
			if (g_render->env_map_mode==P_ENVMODE_CUBE_MAPPING && g_render->cube_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_GEN_R);
				glDisable(GL_TEXTURE_CUBE_MAP);
				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
			else if (g_render->env_map_mode==P_ENVMODE_SPHERE_MAPPING && g_render->sph_map_tex!=0)
			{
				glActiveTextureARB(GL_TEXTURE2_ARB);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
				glDisable(GL_TEXTURE_2D);
				glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
				glActiveTextureARB(GL_TEXTURE0_ARB);
			}
		}
		if (mat->texselfillumid!=-1 && g_render->maxtextureunits>1)
		{
			glActiveTextureARB(GL_TEXTURE1_ARB);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glDisable(GL_TEXTURE_2D);
			glActiveTextureARB(GL_TEXTURE0_ARB);
		}
		if (g_render->fog && mat->flags&P_MATFLAGS_NOFOG)
			glEnable(GL_FOG);
	}
}

#endif
