#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

#if 0 // P_SUPPORT_CG
int pROParticleSystemGPU::s_ps_refcount=0;

//*CGprogram pROParticleSystemGPU::s_ps_prog_pos=0;
//*CGparameter pROParticleSystemGPU::s_ps_elapsed_time_pos=0;

//*CGprogram pROParticleSystemGPU::s_ps_prog_vel=0;
//*CGparameter pROParticleSystemGPU::s_ps_elapsed_time_vel=0;
//*CGparameter pROParticleSystemGPU::s_ps_veldamp_vel=0;
//*CGparameter pROParticleSystemGPU::s_ps_rotfact_vel=0;

//*CGprogram pROParticleSystemGPU::s_ps_prog_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_modelview_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_modelviewproj_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_color0_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_color1_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_fade_vert=0;
//*CGparameter pROParticleSystemGPU::s_ps_psize_vert=0;
#endif

#if 0
void pROParticleSystemGPU::init(bool active)
{
#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG
	if (GLEW_ARB_vertex_program && GLEW_ARB_fragment_program && GLEW_EXT_pixel_buffer_object)
	if (active)
	{
		m_pb_pos[0]=new pPBuffer(m_texsize,m_texsize,128,true,false,false,true,false,false,false,true,0);
		m_pb_pos[1]=new pPBuffer(m_texsize,m_texsize,128,true,false,false,true,false,false,false,true,0);
		m_rva_pos=new pRenderVertexBuffer(m_texsize*m_texsize,4,GL_FLOAT);
		glGenTextures(1,&m_pb_pos_tex);

		int i,j=m_texsize*m_texsize*4;
		float r,*f1,*f2;

		rand2_c=0;
		f1=new float[j];
		if (m_radius.length2()<0.001f)
			for( i=0;i<j;i+=4 )
			{
				f1[i]=FRAND;
				f1[i+1]=FRAND;
				f1[i+2]=FRAND;
				r=f1[i]*f1[i]+f1[i+1]*f1[i+1]+f1[i+2]*f1[i+2];
				if (r>1.0f)
					continue;
				f1[i+3]=m_life-m_lifevar*FABSRAND;
			}
		else
			for( i=0;i<j;i+=4 )
			{
				f1[i]=FRAND;
				f1[i+1]=FRAND;
				r=f1[i]*f1[i]+f1[i+1]*f1[i+1];
				r=1.0f/sqrtf(r);
				f1[i]=f1[i]*r*m_radius.x+FRAND*m_radiusvar.x;
				f1[i+1]=f1[i+1]*r*m_radius.y+FRAND*m_radiusvar.y;
				f1[i+2]=f1[i+2]*r*m_radius.z+FRAND*m_radiusvar.z;
				f1[i+3]=m_life-m_lifevar*FABSRAND;
			}

		m_rva_pos->LoadData(f1);

		m_pb_pos[0]->Bind();
		setup_pbuffer();
//		m_rva_pos->Write(GL_FRONT,m_texsize,m_texsize,f1);
		m_pb_pos[0]->Unbind();

		m_pb_pos[1]->Bind();
		setup_pbuffer();
		m_rva_pos->Write(GL_FRONT,m_texsize,m_texsize,f1);
		m_pb_pos[1]->Unbind();

		m_pb_vel[0]=new pPBuffer(m_texsize,m_texsize,128,true,false,false,true,false,false,false,true,0);
		m_pb_vel[1]=new pPBuffer(m_texsize,m_texsize,128,true,false,false,true,false,false,false,true,0);
		m_rva_vel=new pRenderVertexBuffer(m_texsize*m_texsize,4,GL_FLOAT);
		glGenTextures(1,&m_pb_vel_tex);

		rand2_c=0;
		f2=new float[j];
		for( i=0;i<j;i+=4 )
		{
			f2[i]=FRAND;
			f2[i+1]=FRAND;
			f2[i+2]=FRAND;
			r=f2[i]*f2[i]+f2[i+1]*f2[i+1]+f2[i+2]*f2[i+2];
			r=1.0f/sqrtf(r)*(m_vel+m_velvar*FRAND);
			f2[i]*=r;
			f2[i+1]*=r;
			f2[i+2]*=r;
			f2[i+3]=f1[i+3];
		}

		m_rva_vel->LoadData(f2);

		m_pb_vel[0]->Bind();
		setup_pbuffer();
//		m_rva_vel->Write(GL_FRONT,m_texsize,m_texsize,f2);
		m_pb_vel[0]->Unbind();

		m_pb_vel[1]->Bind();
		setup_pbuffer();
		m_rva_vel->Write(GL_FRONT,m_texsize,m_texsize,f2);
		m_pb_vel[1]->Unbind();

		glBindTexture(GL_TEXTURE_2D,m_pb_pos_tex);
		glTexImage2D( GL_TEXTURE_2D, 0, m_rva_pos->GetSize(), m_texsize, m_texsize, 0, m_rva_pos->GetFormat(), m_rva_pos->GetType(), 0 );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);

		glBindTexture(GL_TEXTURE_2D,m_pb_vel_tex);
		glTexImage2D( GL_TEXTURE_2D, 0, m_rva_vel->GetSize(), m_texsize, m_texsize, 0, m_rva_vel->GetFormat(), m_rva_vel->GetType(), 0 );
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE_EXT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE_EXT);
		
		glBindTexture(GL_TEXTURE_2D,0);

		delete f1;
		delete f2;
	}
	else
	{
		s_ps_refcount++;
		if (s_ps_refcount==1)
		{
			char *programtext;
			pString str;
			CgCheckError();
			str=g_render->app_path+g_render->shader_path+"shaders/cg_particle_system.cg";	
			programtext=LoadTextFile(str);
			if (programtext)
			{
				s_ps_prog_pos = cgCreateProgram(g_render->cgcontext, 
					CG_SOURCE, programtext, CG_PROFILE_ARBFP1, "main_particle_system_pos",0);
				if (s_ps_prog_pos && CgCheckError()==false)
				{
					//*cgGLLoadProgram(s_ps_prog_pos);
					if (CgCheckError()==false)
					{
						s_ps_elapsed_time_pos = cgGetNamedParameter(s_ps_prog_pos, "elapsed_time");
					}
				}
				
				CgCheckError();
				s_ps_prog_vel = cgCreateProgram(g_render->cgcontext, 
					CG_SOURCE, programtext, CG_PROFILE_ARBFP1, "main_particle_system_vel",0);
				if (s_ps_prog_vel && CgCheckError()==false)
				{
					//*cgGLLoadProgram(s_ps_prog_vel);
					if (CgCheckError()==false)
					{
						s_ps_elapsed_time_vel = cgGetNamedParameter(s_ps_prog_vel, "elapsed_time");
						s_ps_veldamp_vel = cgGetNamedParameter(s_ps_prog_vel, "veldamp");
						s_ps_rotfact_vel = cgGetNamedParameter(s_ps_prog_vel, "rotfact");
					}
				}

				CgCheckError();
				s_ps_prog_vert = cgCreateProgram(g_render->cgcontext, 
					CG_SOURCE, programtext, CG_PROFILE_ARBVP1, "main_particle_system_vert",0);
				if (s_ps_prog_vert && CgCheckError()==false)
				{
					//*cgGLLoadProgram(s_ps_prog_vert);
					if (CgCheckError()==false)
					{
						s_ps_modelview_vert = cgGetNamedParameter(s_ps_prog_vert, "modelview");
						s_ps_modelviewproj_vert = cgGetNamedParameter(s_ps_prog_vert, "modelviewproj");
						s_ps_color0_vert = cgGetNamedParameter(s_ps_prog_vert, "color0");
						s_ps_color1_vert = cgGetNamedParameter(s_ps_prog_vert, "color1");
						s_ps_fade_vert = cgGetNamedParameter(s_ps_prog_vert, "fade");
						s_ps_psize_vert = cgGetNamedParameter(s_ps_prog_vert, "psize");
					}
				}

				delete programtext;
			}
		}
	}
#endif
#endif

	m_bbox.max=m_radius+m_radiusvar;
	m_bbox.min=-m_bbox.max;
}

		//! Default constructor.
pROParticleSystemGPU::pROParticleSystemGPU() :
	m_texsize(64),
	m_texmap(-1),
	m_blendadd(1),
	m_psize(1,0,1,32),
	m_life(2),
	m_lifevar(0.2f),
	m_fade(0.2f),
	m_vel(2.0f),
	m_veldamp(0.0f),
	m_velvar(0.0f),
	m_rotflag(0),
	m_color0(1,1,0),
	m_color1(1,0,0),
	m_radius(0),
	m_radiusvar(0),
	m_current(1)
{
	m_type=TYPE_RO_PARTICLE_SYSTEM_GPU;
#ifndef P_DISABLE_3D
	m_rva_pos=0;
	m_rva_vel=0;
	m_pb_pos[0]=0;
	m_pb_pos[1]=0;
	m_pb_vel[0]=0;
	m_pb_vel[1]=0;
	m_pb_pos_tex=0;
	m_pb_vel_tex=0;
#endif
}

pROParticleSystemGPU::pROParticleSystemGPU(const pROParticleSystemGPU& in) :
	pRenderObject(in),
	m_texsize(in.m_texsize),
	m_texmap(in.m_texmap),
	m_blendadd(in.m_blendadd),
	m_psize(in.m_psize),
	m_life(in.m_life),
	m_lifevar(in.m_lifevar),
	m_fade(in.m_fade),
	m_vel(in.m_vel),
	m_veldamp(in.m_veldamp),
	m_velvar(in.m_velvar),
	m_rotflag(in.m_rotflag),
	m_color0(in.m_color0),
	m_color1(in.m_color1),
	m_radius(in.m_radius),
	m_radiusvar(in.m_radiusvar),
	m_current(in.m_current)
{ 
#ifndef P_DISABLE_3D
	m_rva_pos=in.m_rva_pos;
	m_rva_vel=in.m_rva_vel;
	m_pb_pos[0]=in.m_pb_pos[0];
	m_pb_pos[1]=in.m_pb_pos[1];
	m_pb_vel[0]=in.m_pb_vel[0];
	m_pb_vel[1]=in.m_pb_vel[1];
	m_pb_pos_tex=in.m_pb_pos_tex;
	m_pb_vel_tex=in.m_pb_vel_tex;
#endif
}

pROParticleSystemGPU::~pROParticleSystemGPU()
{
	reset();
}

void pROParticleSystemGPU::reset()
{
	if (m_source)
	{
#ifndef P_DISABLE_3D
		delete m_pb_pos[0];
		delete m_pb_pos[1];
		delete m_pb_vel[0];
		delete m_pb_vel[1];
		delete m_rva_pos;
		delete m_rva_vel;
		glDeleteTextures(1,&m_pb_pos_tex);
		glDeleteTextures(1,&m_pb_vel_tex);
#endif
	}
	else
	{
#if 0 // P_SUPPORT_CG
		s_ps_refcount--;
		if (s_ps_refcount<=0)
		{
			cgDestroyProgram(s_ps_prog_pos);
			cgDestroyProgram(s_ps_prog_vel);
			cgDestroyProgram(s_ps_prog_vert);
			s_ps_prog_pos=0;
			s_ps_prog_vel=0;
			s_ps_prog_vert=0;
			s_ps_elapsed_time_pos=0;
			s_ps_elapsed_time_vel=0;
			s_ps_veldamp_vel=0;
			s_ps_rotfact_vel=0;
			s_ps_modelview_vert=0;
			s_ps_modelviewproj_vert=0;
			s_ps_color0_vert=0;
			s_ps_color1_vert=0;
			s_ps_fade_vert=0;
			s_ps_psize_vert=0;
			s_ps_refcount=0;
		}
#endif
	}
}
void pROParticleSystemGPU::step(const float elapsed_time,const pMatrix& global)
{
	m_life-=elapsed_time;
	if (m_life<0)
		g_romanager->post_deactivate(m_id);
#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG
	else
	if (m_pb_pos && m_pb_vel && m_rva_pos && m_rva_vel)
	{
		float s=(float)m_texsize;
		int other=m_current;
		m_current=!m_current;

		// update vel
		m_pb_vel[m_current]->Bind();

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glBindTexture(GL_TEXTURE_2D,m_pb_vel_tex);
		glEnable(GL_TEXTURE_2D);
		m_pb_vel[other]->BindAsTexture(WGL_FRONT_LEFT_ARB);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glBindTexture(GL_TEXTURE_2D,m_pb_pos_tex);
		glEnable(GL_TEXTURE_2D);
		m_pb_pos[other]->BindAsTexture(WGL_FRONT_LEFT_ARB);

		//*cgGLSetParameter1f(s_ps_elapsed_time_vel,elapsed_time);
		//*cgGLSetParameter1f(s_ps_veldamp_vel,m_veldamp);
		//*cgGLSetParameter1f(s_ps_rotfact_vel,m_rotflag?1.0f:0.0f);
		//*cgGLBindProgram(s_ps_prog_vel);
		//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

		glDrawBuffer(GL_FRONT_LEFT);

		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex2f(0,0);
			glTexCoord2f(1.0f,0.0f); glVertex2f(s,0);
			glTexCoord2f(1.0f,1.0f); glVertex2f(s,s);
			glTexCoord2f(0.0f,1.0f); glVertex2f(0,s);
		//*glEnd();

		//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		m_pb_vel[other]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		m_pb_pos[other]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);

		m_rva_vel->Read(GL_FRONT,m_texsize,m_texsize);
		m_pb_vel[m_current]->Unbind();
		
		// update pos
		m_pb_pos[m_current]->Bind();

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glBindTexture(GL_TEXTURE_2D,m_pb_vel_tex);
		glEnable(GL_TEXTURE_2D);
		m_pb_vel[m_current]->BindAsTexture(WGL_FRONT_LEFT_ARB);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glBindTexture(GL_TEXTURE_2D,m_pb_pos_tex);
		glEnable(GL_TEXTURE_2D);
		m_pb_pos[other]->BindAsTexture(WGL_FRONT_LEFT_ARB);

		//*cgGLSetParameter1f(s_ps_elapsed_time_pos,elapsed_time);
		//*cgGLBindProgram(s_ps_prog_pos);
		//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
	
		glDrawBuffer(GL_FRONT_LEFT);

		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex2f(0,0);
			glTexCoord2f(1.0f,0.0f); glVertex2f(s,0);
			glTexCoord2f(1.0f,1.0f); glVertex2f(s,s);
			glTexCoord2f(0.0f,1.0f); glVertex2f(0,s);
		//*glEnd();

		//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		m_pb_vel[other]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		m_pb_pos[other]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);

		m_rva_pos->Read(GL_FRONT,m_texsize,m_texsize);
		m_pb_pos[m_current]->Unbind();

	}
#endif
	pRenderObject::step(elapsed_time,m_transform*global);
#endif
}

void pROParticleSystemGPU::setup_pbuffer()
{
#ifndef P_DISABLE_3D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,m_texsize,0,m_texsize,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);
	glColor4f(1,1,1,1);
#endif
}

void pROParticleSystemGPU::draw()
{
#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG
	if (m_rva_pos && m_rva_vel)
	{
		glMultMatrixf(&m_transform_global.mf[0]);
		g_render->sel_tex(m_texmap);

		if (m_blendadd)
		{
			if (g_render->fog)
			{
				pVector black(0);
				glFogfv(GL_FOG_COLOR,&black.x);
			}
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
			glDepthMask(GL_FALSE);
		}
		else
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glAlphaFunc(GL_GREATER,g_render->alphatestval);
			glEnable(GL_ALPHA_TEST);
		}

		glPointParameterfARB(GL_POINT_SIZE_MIN_ARB, 1.0f);
		glPointParameterfARB(GL_POINT_SIZE_MAX_ARB, 128.0f);
		glPointParameterfARB(GL_POINT_FADE_THRESHOLD_SIZE_ARB,1.0f);
		glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB,GL_TRUE);
		glEnable(GL_POINT_SPRITE_ARB);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_NV);
		glPointSize(m_psize.w);

		m_rva_pos->SetVertexPointer();
		m_rva_vel->SetTexcoordPointer();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//*cgGLSetParameter1f(s_ps_fade_vert,m_fade);
		//*cgGLSetParameter4fv(s_ps_psize_vert,&m_psize.x);
		//*cgGLSetParameter4fv(s_ps_color0_vert,&m_color0.x);
		//*cgGLSetParameter4fv(s_ps_color1_vert,&m_color1.x);
		//*cgGLSetStateMatrixParameter(s_ps_modelviewproj_vert,CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
		//*cgGLSetStateMatrixParameter(s_ps_modelview_vert,CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
		//*cgGLBindProgram(s_ps_prog_vert);
		//*cgGLEnableProfile(CG_PROFILE_ARBVP1);
		
		glDrawArrays(GL_POINTS, 0, m_texsize*m_texsize);
		
		//*cgGLDisableProfile(CG_PROFILE_ARBVP1);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_POINT_SPRITE_ARB);
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_NV);
		glPointSize(1.0f);
	}
#endif
#endif
}

int pROParticleSystemGPU::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='u';
			pd->data=&m_texsize;
			pd->name="texsize";
			pd->comment="Float texture size in pixels (num partciles=size*size)";
		break;

		case 1:
			pd->type='f';
			pd->data=&m_life;
			pd->name="life";
			pd->comment="Life in seconds";
		break;

		case 2:
			pd->type='f';
			pd->data=&m_lifevar;
			pd->name="lifevar";
			pd->comment="Life variance in seconds";
		break;

		case 3:
			pd->type='f';
			pd->data=&m_fade;
			pd->name="fade";
			pd->comment="fade time in seconds";
		break;

		case 4:
			pd->type='v';
			pd->data=&m_radius;
			pd->name="radius";
			pd->comment="Initial position radius in each axis (use 0,0,0 for point emission)";
		break;

		case 5:
			pd->type='v';
			pd->data=&m_radiusvar;
			pd->name="radiusvar";
			pd->comment="Variance for initial position";
		break;

		case 6:
			pd->type='b';
			pd->data=&m_rotflag;
			pd->name="rotflag";
			pd->comment="Rotation flag (check for circular rotation movement)";
		break;

		case 7:
			pd->type='f';
			pd->data=&m_vel;
			pd->name="vel";
			pd->comment="Velocity in units/sec";
		break;

		case 8:
			pd->type='f';
			pd->data=&m_velvar;
			pd->name="velvar";
			pd->comment="Velocity variance in units/seconds";
		break;

		case 9:
			pd->type='f';
			pd->data=&m_veldamp;
			pd->name="veldamp";
			pd->comment="Velocity dampening factor in units/sec";
		break;

		case 10:
			pd->type='v';
			pd->data=&m_psize;
			pd->name="pszie_att";
			pd->comment="Point size attenuation factors (constant, linear, quadrdatic)";
		break;

		case 11:
			pd->type='f';
			pd->data=&m_psize.w;
			pd->name="pszie";
			pd->comment="Maximum point size in pixels";
		break;

		case 12:
			pd->type='p';
			pd->data=&m_texmap;
			pd->name="texmap";
			pd->comment="Particle texture map";
		break;

		case 13:
			pd->type='b';
			pd->data=&m_blendadd;
			pd->name="blendadd";
			pd->comment="Additive blend flag";
		break;

		case 14:
			pd->type='c';
			pd->data=&m_color0;
			pd->name="color0";
			pd->comment="Initial color";
		break;

		case 15:
			pd->type='f';
			pd->data=&m_color0.w;
			pd->name="color0_transp";
			pd->comment="Initial color transparency";
		break;

		case 16:
			pd->type='c';
			pd->data=&m_color1;
			pd->name="color1";
			pd->comment="Final color";
		break;

		case 17:
			pd->type='f';
			pd->data=&m_color1.w;
			pd->name="color1_transp";
			pd->comment="Final color transparency";
		break;
	}
	
	return 18;
}

void pROParticleSystemGPU::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
			reset();
			init(m_source!=0);
		break;
	};
}

#endif
#endif