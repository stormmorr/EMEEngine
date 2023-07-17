#include "paralelo3d.h"
#include "unRenderer.h"

#include "../tgaload.h"

#include <string>

#define BLOOM_SCALE 2

QAGE::QActiveFramewrk *QActiveFrameWork;
UN::UNprocessor *unProcessor;

using namespace GVARS;

#if 0
#define CAL_ARB 1
#endif

unRenderer::unRenderer()
{
	m_vert_prog=0;
	m_vtile=0;
	m_vdepth=0;

	m_vert_mesh=0;
	m_meshtile=0;
	m_meshvertices=0;
	m_meshdepth=0;
	m_meshmatrix=0;
	m_meshtranslation=0;
	m_meshcolormap = 0;
	m_meshrotationMatrices = 0;
	m_meshtranslationVectors = 0;
	m_meshmatcount = 0;

	m_frag_mesh=0;

	m_frag_prog_normal=0;
	m_ndiffuse=0;
	m_nspecular=0;
	m_nplanes=0;

	m_frag_prog_relief=0;
	m_rdiffuse=0;
	m_rspecular=0;
	m_rplanes=0;

	m_frag_prog_light=0;
	m_lplanes=0;
	m_lpos=0;
	m_lcolor=0;

	m_frag_prog_blur=0;
	m_bdisp=0;

	m_frag_prog_antialias=0;
	m_apixelsize=0;
	m_aweight=0;

	m_fb[0]=0;
	m_fb[1]=0;
	m_fb[2]=0;
	m_fb[3]=0;
	m_fbtex[0]=0;
	m_fbtex[1]=0;
	m_fbtex[2]=0;
	m_fbtex[4]=0;

	m_mrt=0;
	m_mrttex[0]=0;
	m_mrttex[1]=0;
	m_mrttex[2]=0;
	m_mrttex[3]=0;

	m_null_color=0;
	m_null_normal=0;

	m_sizex=m_sizey=0;

	m_num_lights_drawn=0;
	m_percent_pixel_drawn=0;

	m_nv_render_depth_texture=false;
	m_depth_bias=false;
	m_Activate = true;
}

unRenderer::~unRenderer()
{
	mrt_destroy();
	free_programs();
}

void unRenderer::mrt_create(int sx,int sy)
{
	gl_buffers[0]=GL_FRONT_LEFT;
	gl_buffers[1]=GL_AUX0;
	gl_buffers[2]=GL_AUX1;
	gl_buffers[3]=GL_AUX2;
	
    wgl_buffers[0]=WGL_FRONT_LEFT_ARB;
    wgl_buffers[1]=WGL_AUX0_ARB;
    wgl_buffers[2]=WGL_AUX1_ARB;
	wgl_buffers[3]=m_nv_render_depth_texture?WGL_DEPTH_COMPONENT_NV:WGL_AUX2_ARB;

	m_sizex=sx;
	m_sizey=sy;

	m_mrt=new pPBuffer(sx,sy,32,false,true,false,true,true,false,false,true,m_nv_render_depth_texture?2:3);

	glGenTextures(4,m_mrttex);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);
	if (m_nv_render_depth_texture)
		glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,sx,sy,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,NULL);
	else
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	m_fb[0]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
	m_fb[1]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glGenTextures(4,m_fbtex);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	sx/=BLOOM_SCALE;
	sy/=BLOOM_SCALE;
	m_fb[2]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
	m_fb[3]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[3]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::mrt_destroy()
{
	glDeleteTextures(4,m_mrttex);
	m_mrttex[0]=0;
	m_mrttex[1]=0;
	m_mrttex[2]=0;
	m_mrttex[3]=0;

	glDeleteTextures(3,m_fbtex);
	m_fbtex[0]=0;
	m_fbtex[1]=0;
	m_fbtex[2]=0;

	delete m_fb[0];
	delete m_fb[1];
	delete m_fb[2];
	m_fb[0]=0;
	m_fb[1]=0;
	m_fb[2]=0;

	delete m_mrt;
	m_mrt=0;
}

void unRenderer::set_program_params(bool depth_bias,bool nv_render_depth_texture)
{
	m_depth_bias=depth_bias;
	m_nv_render_depth_texture=(nv_render_depth_texture&&WGLEW_NV_render_depth_texture);
}

bool unRenderer::load_programs()
{
	if (g_render==0)
		return false;
	
	free_programs();

	int i=0;
	char *m_vert_options[8];
	m_vert_options[0]="-posinv";
	m_vert_options[1]=0;
	char *m_frag_options[8];
	if (m_nv_render_depth_texture)
		m_frag_options[i++]="-DNV_RENDER_DEPTH_TEXTURE";
	if (m_depth_bias)
		m_frag_options[i++]="-DDEPTH_BIAS";
	m_frag_options[i]=0;

	bool ret=false;
	int count=0;
	pString str;
	str.format("%s%s..\\shaders\\Cg\\cg_relief_map_ds.cg",
		(const char *)g_render->app_path,
		(const char *)g_render->shader_path);
	char *programtext=LoadTextFile(str);
	if (programtext)
	{
		m_vert_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBVP1,
				"view_space",
				(const char **)m_vert_options);
		if (m_vert_prog)
			count++;

		checkError("view_space", "cgCreateProgram");

		vertexProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
		//*cgGLSetOptimalOptions(vertexProfile);
		checkError("Get Profile", "selecting vertex profile");

		m_vert_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				vertexProfile,
				"view_mesh",
				0);

		checkError("view_mesh", "cgCreateProgram");

		m_frag_prog_normal = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal",
				(const char **)m_frag_options);
		if (m_frag_prog_normal)
			count++;

		checkError("mrt_normal", "cgCreateProgram");

		m_frag_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_mesh",
				(const char **)m_frag_options);

		checkError("mrt_normal_mesh", "cgCreateProgram");

		m_frag_prog_relief = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_relief",
				(const char **)m_frag_options);
		if (m_frag_prog_relief)
			count++;

		checkError("mrt_relief_relaxed", "cgCreateProgram");

		m_frag_prog_light = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_light",
				(const char **)m_frag_options);
		if (m_frag_prog_light)
			count++;

		checkError("mrt_light", "cgCreateProgram");

		m_frag_prog_blur = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"blur",
				0);
		if (m_frag_prog_blur)
			count++;

		checkError("blur", "cgCreateProgram");

		m_frag_prog_antialias = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"anti_alias",
				0);
		if (m_frag_prog_antialias)
			count++;

		checkError("anti_alias", "cgCreateProgram");

		ret=(count==6);
		
		if (ret)
		{
			//*cgGLLoadProgram(m_vert_prog);
			CgCheckError();

			//*cgGLLoadProgram(m_vert_mesh);
			CgCheckError();
			
			//*cgGLLoadProgram(m_frag_prog_normal);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_mesh);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_relief);
			CgCheckError();
			
			//*cgGLLoadProgram(m_frag_prog_light);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_blur);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_antialias);
			CgCheckError();
			
			m_vtile=cgGetNamedParameter(m_vert_prog,"tile");
			m_vdepth=cgGetNamedParameter(m_vert_prog,"depth");

			//m_meshvertices=cgGetNamedParameter(m_vert_mesh,"pos");

			m_meshtile=cgGetNamedParameter(m_vert_mesh,"tile");
			m_meshdepth=cgGetNamedParameter(m_vert_mesh,"depth");
			m_meshmatrix=cgGetNamedParameter(m_vert_mesh,"meshmatrix");
			m_meshtranslation=cgGetNamedParameter(m_vert_mesh,"meshtranslation");
			m_meshrotationMatrices=cgGetNamedParameter(m_vert_mesh,"rotationMatrices");
			m_meshtranslationVectors=cgGetNamedParameter(m_vert_mesh,"translationVectors");
			m_meshmatcount=cgGetNamedParameter(m_vert_mesh,"matcount");
			m_meshcolormap=cgGetNamedParameter(m_frag_mesh,"colortex");

			//if(!m_meshvertices) printf("ERROR:::LoadPrograms m_meshvertices parameter not found\n");

			if(!m_meshtile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_meshdepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_meshmatrix) printf("ERROR:::LoadPrograms m_meshmatrix parameter not found\n");
			if(!m_meshtranslation) printf("ERROR:::LoadPrograms meshtranslation parameter not found\n");
			if(!m_meshrotationMatrices) printf("ERROR:::LoadPrograms rotationMatrices parameter not found\n");
			if(!m_meshtranslationVectors) printf("ERROR:::LoadPrograms translationVectors parameter not found\n");
			if(!m_meshcolormap) printf("ERROR:::LoadPrograms m_meshcolormap parameter not found\n");
			if(!m_meshmatcount) printf("ERROR:::LoadPrograms m_meshmatcount parameter not found\n");

			m_ndiffuse=cgGetNamedParameter(m_frag_prog_normal,"diffuse");
			m_nspecular=cgGetNamedParameter(m_frag_prog_normal,"specular");
			m_nplanes=cgGetNamedParameter(m_frag_prog_normal,"planes");
			m_rdiffuse=cgGetNamedParameter(m_frag_prog_relief,"diffuse");
			m_rspecular=cgGetNamedParameter(m_frag_prog_relief,"specular");
			m_rplanes=cgGetNamedParameter(m_frag_prog_relief,"planes");
			m_stepmap=cgGetNamedParameter(m_frag_prog_relief,"stepmap");
			m_lplanes=cgGetNamedParameter(m_frag_prog_light,"planes");
			m_lpos=cgGetNamedParameter(m_frag_prog_light,"lightpos");
			m_lcolor=cgGetNamedParameter(m_frag_prog_light,"lightcolor");
			m_bdisp=cgGetNamedParameter(m_frag_prog_blur,"disp");
			m_apixelsize=cgGetNamedParameter(m_frag_prog_antialias,"pixel_size");
			m_aweight=cgGetNamedParameter(m_frag_prog_antialias,"weight");

			CgCheckError();
		}
	
		delete programtext;
	}

	if (ret==false)
		free_programs();
	
	int tex;
	tex=g_render->build_onepixelmap(255,255,255);
	m_null_color=g_render->picid[tex];
	tex=g_render->build_onepixelmap(128,128,255);
	m_null_normal=g_render->picid[tex];

	///// Reflective Shadow Mapping /////
	//m_RSM = new RSM();

	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk;


	//m_mrt->Bind();

	QActiveFrameWork->acActiveInit();

	//m_mrt->Unbind();

	unProcessor = new UN::UNprocessor();

	return ret;
}

void unRenderer::free_programs()
{
	if (m_vert_prog)
		cgDestroyProgram(m_vert_prog);
	m_vert_prog=0;

	if (m_vert_mesh)
		cgDestroyProgram(m_vert_mesh);
	m_vert_mesh=0;

	if (m_frag_prog_normal)
		cgDestroyProgram(m_frag_prog_normal);
	m_frag_prog_normal=0;

	if (m_frag_mesh)
		cgDestroyProgram(m_frag_mesh);
	m_frag_mesh=0;

	if (m_frag_prog_relief)
		cgDestroyProgram(m_frag_prog_relief);
	m_frag_prog_relief=0;

	if (m_frag_prog_light)
		cgDestroyProgram(m_frag_prog_light);
	m_frag_prog_light=0;

	if (m_frag_prog_antialias)
		cgDestroyProgram(m_frag_prog_antialias);
	m_frag_prog_antialias=0;
}

void unRenderer::bind_vertex()
{
	//*cgGLBindProgram(m_vert_prog);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);
}

void unRenderer::unbind_vertex()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBVP1);
}

void unRenderer::bind_mesh_vertex()
{
	//*cgGLBindProgram(m_vert_mesh);
	//*cgGLEnableProfile(vertexProfile);
}

void unRenderer::unbind_mesh_vertex()
{
	//*cgGLDisableProfile(vertexProfile);
}

void unRenderer::bind_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_mesh_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_mesh_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_relief()
{
	//*cgGLBindProgram(m_frag_prog_relief);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_relief()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_mesh_relief()
{
	//*cgGLBindProgram(m_frag_prog_relief);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_mesh_relief()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_light()
{
	//*cgGLBindProgram(m_frag_prog_light);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_light()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::bind_blur()
{
	//*cgGLBindProgram(m_frag_prog_blur);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_blur()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::bind_antialias()
{
	//*cgGLBindProgram(m_frag_prog_antialias);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_antialias()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_nspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_relief_params_mesh(const float& diffuse,const float& specular,float tile,float depth,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_rspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_light_params(const pVector& lightpos,const pVector& lightcolor)
{
	//*cgGLSetParameter4fv(m_lpos,&lightpos.x);
	//*cgGLSetParameter3fv(m_lcolor,&lightcolor.x);

	//*cgGLSetParameter2f(m_lplanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));
}

void unRenderer::set_blur_params(bool vertical_flag)
{
	//*CGparameter param;

	int i,j=7,k=(j>>1);

	if (vertical_flag==false)
	{
		float fp=1.25/(m_sizex/BLOOM_SCALE);
		for( i=0;i<j;i++ )
		{
			param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,(i-k)*fp,0);
		}
	}
	else
	{
		float fp=1.25/(m_sizey/BLOOM_SCALE);
		for( i=0;i<j;i++ )
		{
			param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,0,(i-k)*fp);
		}
	}
}

void unRenderer::fb_bind_render(int buffer)
{
	if (m_fb)
		m_fb[buffer]->Bind();
}

void unRenderer::fb_unbind_render(int buffer)
{
	if (m_fb)
		m_fb[buffer]->Unbind();
}

void unRenderer::fb_bind_texture(int buffer,int texunit)
{
	if (m_fb[buffer])
	{
		glActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
		m_fb[buffer]->BindAsTexture(WGL_FRONT_LEFT_ARB);
		glEnable(GL_TEXTURE_2D);
	}
}

void unRenderer::fb_unbind_texture(int buffer,int texunit)
{
	if (m_fb[buffer])
	{
		glActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
		m_fb[buffer]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
	}
}

void unRenderer::mrt_bind_render()
{
	if (m_mrt)
	{
		m_mrt->Bind();
		glDrawBuffersATI(m_nv_render_depth_texture?3:4,gl_buffers);
	}
}

void unRenderer::mrt_unbind_render()
{
	if (m_mrt)
		m_mrt->Unbind();
}

void unRenderer::mrt_bind_texture(int target)
{
	if (m_mrt)
	{
		if (target>=0)
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[target]);
			m_mrt->BindAsTexture(wgl_buffers[target]);
			glEnable(GL_TEXTURE_2D);
		}
		else
		{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);
			m_mrt->BindAsTexture(wgl_buffers[3]);

			glActiveTextureARB(GL_TEXTURE2_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
			m_mrt->BindAsTexture(wgl_buffers[2]);

			glActiveTextureARB(GL_TEXTURE1_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
			m_mrt->BindAsTexture(wgl_buffers[1]);

			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
			m_mrt->BindAsTexture(wgl_buffers[0]);
		}
	}
}

void unRenderer::mrt_unbind_texture(int target)
{
	if (m_mrt)
	{
		if (target>=0)
		{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			m_mrt->ReleaseTexture(wgl_buffers[target]);
			glBindTexture(GL_TEXTURE_2D,0);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			m_mrt->ReleaseTexture(wgl_buffers[3]);
			glBindTexture(GL_TEXTURE_2D,0);

			glActiveTextureARB(GL_TEXTURE2_ARB);
			m_mrt->ReleaseTexture(wgl_buffers[2]);
			glBindTexture(GL_TEXTURE_2D,0);

			glActiveTextureARB(GL_TEXTURE1_ARB);
			m_mrt->ReleaseTexture(wgl_buffers[1]);
			glBindTexture(GL_TEXTURE_2D,0);

			glActiveTextureARB(GL_TEXTURE0_ARB);
			m_mrt->ReleaseTexture(wgl_buffers[0]);
			glBindTexture(GL_TEXTURE_2D,0);
		}
	}
}

void unRenderer::draw_rect(int x,int y,int sx,int sy,bool vpos,bool flipy)
{
	if (vpos)
	{
		pVector f[4];
		double d[3];
		int pixels[4][2]={ { 0,0 },{0,sy},{sx,sy},{sx,0} };
		int viewport[4]={ 0,0,sx,sy };

		pMatrix view_rot=g_render->view_matrix;
		view_rot.set_translate(0);
		for( int i=0;i<4;i++ )
		{
			gluUnProject(
				pixels[i][0],pixels[i][1],10,
				g_render->cam_model_mat,g_render->cam_proj_mat,
				viewport,&d[0],&d[1],&d[2]);
			f[i].vec((float)d[0],(float)d[1],(float)d[2]);
			f[i]-=g_render->camera.pos;
			f[i].normalize();
			f[i]=f[i]*view_rot;
		}

		glBegin(GL_QUADS);
			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[0].x);
			glVertex2i(x,y);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,1);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[1].x);
			glVertex2i(x,y+sy);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,1,1);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[2].x);
			glVertex2i(x+sx,y+sy);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,1,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[3].x);
			glVertex2i(x+sx,y);

			glMultiTexCoord2f(GL_TEXTURE0_ARB,0,0);
			glMultiTexCoord3fv(GL_TEXTURE1_ARB,&f[0].x);
			glVertex2i(x,y);
		glEnd();
	}
	else
	if (flipy)
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex2i(x,y);

			glTexCoord2f(0,0);
			glVertex2i(x,y+sy);

			glTexCoord2f(1,0);
			glVertex2i(x+sx,y+sy);

			glTexCoord2f(1,1);
			glVertex2i(x+sx,y);

			glTexCoord2f(0,1);
			glVertex2i(x,y);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2i(x,y);

			glTexCoord2f(0,1);
			glVertex2i(x,y+sy);

			glTexCoord2f(1,1);
			glVertex2i(x+sx,y+sy);

			glTexCoord2f(1,0);
			glVertex2i(x+sx,y);

			glTexCoord2f(0,0);
			glVertex2i(x,y);
		glEnd();
	}

}

void unRenderer::draw_depth(pMesh *m)
{
	int va=0,vb=1;
	m->array_lock(va,vb);

	m->array_draw(vb);

	m->array_unlock();
}

void unRenderer::draw_depth_avatars(void)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	//glEnable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	//glMatrixMode(GL_MODELVIEW);

#if 0	/// MESH RENDERING LOOP START
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV.Xform.Translation.x, playerAV.Xform.Translation.y, playerAV.Xform.Translation.z);
	glMultMatrixf(playerAV.Xform.Matrix.mf);
#endif

	Qpo->Player_SetMatrix();

	bind_mesh_vertex();
	////*cgGLBindProgram(m_frag_mesh);
	////*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	//Vertex Array - Position

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	//Normal Array - Normals

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	//Vertex Array - Texture Coords

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - Weights

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - MatrixIndex

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[5]);
	//Elements Array - Face Indices

#if 1

	///// Per Mesh Settings /////
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			//glActiveTextureARB(GL_TEXTURE0_ARB);
			//glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

#endif

	unbind_mesh_vertex();

	////*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glClientActiveTextureARB(GL_TEXTURE0_ARB);

	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    //glDisable(GL_DEPTH_TEST);
	//glDisable(GL_VERTEX_PROGRAM_ARB);

	//glDisable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	//glMatrixMode(GL_PROJECTION);
}

void unRenderer::draw_depth_player(void)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	//glEnable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	//glMatrixMode(GL_MODELVIEW);

#if 0	/// MESH RENDERING LOOP START
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV.Xform.Translation.x, playerAV.Xform.Translation.y, playerAV.Xform.Translation.z);
	glMultMatrixf(playerAV.Xform.Matrix.mf);
#endif

	Qpo->Player_SetMatrix();

	bind_mesh_vertex();
	////*cgGLBindProgram(m_frag_mesh);
	////*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	//Vertex Array - Position

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	//Normal Array - Normals

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	//Vertex Array - Texture Coords

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - Weights

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - MatrixIndex

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[5]);
	//Elements Array - Face Indices

#if 1

	///// Per Mesh Settings /////
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			//glActiveTextureARB(GL_TEXTURE0_ARB);
			//glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

#endif

	unbind_mesh_vertex();

	////*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	glClientActiveTextureARB(GL_TEXTURE0_ARB);

	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    //glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    //glDisable(GL_DEPTH_TEST);
	//glDisable(GL_VERTEX_PROGRAM_ARB);

	//glDisable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	//glMatrixMode(GL_PROJECTION);
}

void unRenderer::draw_material(pMesh *m,bool relief)
{
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock(va,vb);

	int i,j=m->nfacemat,k;
	pMaterial *mat;
	
	bind_vertex();

	bind_normal();

	k=0;
	for( i=0;i<j;i++ )
	{
		mat=&m->mat[m->face[k].material];
		if (relief==false || mat->bump==0 || mat->texnormalid==-1)
		{
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
#ifdef P_MESH_SHORT_FACE
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(k*3*sizeof(unsigned short)):&m->facevert[k*3]);
#else
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&m->facevert[k*3]);
#endif
		}
		k+=m->facemat[i];
	}

	unbind_normal();

	bind_relief();

	k=0;
	if (relief==true)
	for( i=0;i<j;i++ )
	{
		mat=&m->mat[m->face[k].material];
		if (!(mat->bump==0 || mat->texnormalid==-1))
		{
			//set_relief_params(mat->diffuse,mat->specular,1,mat->bump,mat->texid,mat->texnormalid);
			set_relief_params(mat->diffuse,mat->specular,1,1,mat->texid,mat->texnormalid);
#ifdef P_MESH_SHORT_FACE
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_SHORT,vb?(void *)(k*3*sizeof(unsigned short)):&m->facevert[k*3]);
#else
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&m->facevert[k*3]);
#endif
		}
		k+=m->facemat[i];
	}

	unbind_relief();
	
	unbind_vertex();

	m->array_unlock();
}

void unRenderer::draw_material_player(bool relief)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glEnable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	glMatrixMode(GL_MODELVIEW);

#if 0	/// MESH RENDERING LOOP START
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV.Xform.Translation.x, playerAV.Xform.Translation.y, playerAV.Xform.Translation.z);
	glMultMatrixf(playerAV.Xform.Matrix.mf);
#endif

	Qpo->Player_SetMatrix();

	bind_mesh_vertex();
	//*cgGLBindProgram(m_frag_mesh);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	//Vertex Array - Position

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	//Normal Array - Normals

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//Vertex Array - Texture Coords

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - Weights

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - MatrixIndex

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[5]);
	//Elements Array - Face Indices

	///// Per Mesh Settings /////
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			//glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	//unbind_normal();
	//bind_mesh_relief();

#if 0
	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3,&transformation[0]);
			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+1,&transformation[4]);
			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+2,&transformation[8]);

			//*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[0]);

			float index[4];
			index[0] = boneId*3;
			index[1] = boneId*3+1;
			index[2] = boneId*3+2;
			index[3] = 0;

			//*cgGLSetParameter4fv(m_meshindex,&index[0]);

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_relief_params(mat->diffuse,mat->specular,1,5,mat->texid,mat->texnormalid);
			}

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}
#endif

	//unbind_mesh_relief();
	//unbind_mesh_vertex();

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_VERTEX_PROGRAM_ARB);
}

void unRenderer::draw_material_avatars(bool relief)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glEnable(GL_DEPTH_TEST);

	///// Set Mesh Drawing Rendering Position /////
	glMatrixMode(GL_MODELVIEW);

#if 0	/// MESH RENDERING LOOP START
	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV.Xform.Translation.x, playerAV.Xform.Translation.y, playerAV.Xform.Translation.z);
	glMultMatrixf(playerAV.Xform.Matrix.mf);
#endif

	Qpo->Player_SetMatrix();

	bind_mesh_vertex();
	//*cgGLBindProgram(m_frag_mesh);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	//Vertex Array - Position

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	//Normal Array - Normals

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//Vertex Array - Texture Coords

	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - Weights

	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
	//Vertex Array - MatrixIndex

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV.Avatar.Mesh->m_bufferObject[5]);
	//Elements Array - Face Indices

	///// Per Mesh Settings /////
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			//glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	//unbind_normal();
	//bind_mesh_relief();

#if 0
	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV.Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3,&transformation[0]);
			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+1,&transformation[4]);
			//glProgramLocalParameter4fvARB(GL_VERTEX_PROGRAM_ARB,boneId*3+2,&transformation[8]);

			//*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[0]);

			float index[4];
			index[0] = boneId*3;
			index[1] = boneId*3+1;
			index[2] = boneId*3+2;
			index[3] = 0;

			//*cgGLSetParameter4fv(m_meshindex,&index[0]);

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_relief_params(mat->diffuse,mat->specular,1,5,mat->texid,mat->texnormalid);
			}

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}
#endif

	//unbind_mesh_relief();
	//unbind_mesh_vertex();

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
	glDisable(GL_VERTEX_PROGRAM_ARB);
}

GLint unRenderer::getVertexUniformIndex(//*CGparameter parameter)
{
	const std::vector<float> zeroes(m_VertexMaxUniforms * 4, 0);

	glProgramParameters4fvNV(GL_VERTEX_PROGRAM_NV, 0, m_VertexMaxUniforms, &zeroes[0]);

	const float ones[4] = {1, 1, 1, 1};
        
	//*cgGLSetParameterArray4f(parameter, 0, 1, ones);

	for (GLint i = 0; i < m_VertexMaxUniforms; ++i)
		{
		float modified[4];

		glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV, i, GL_PROGRAM_PARAMETER_NV, modified);

		if (modified[0] > 0.0f) return i;
		}

	return -1;
}

void unRenderer::project(const pVector& p_obj,pVector& p_win)
{
	pVector t=p_obj*g_render->view_matrix;
	t=g_render->proj_matrix.multiply_full(t);
	p_win.x=512*(t.x/t.w+1.0f)*0.5f;
	p_win.y=512*(t.y/t.w+1.0f)*0.5f;
	p_win.z=(t.z/t.w+1.0f)*0.5f;
}

void unRenderer::unproject(const pVector& p_win,pVector& p_obj)
{
}

int unRenderer::set_light_scissor(const pVector& lightpos,int sx,int sy)
{
	int rect[4]={ 0,0,sx,sy };
	float d;

	float r=lightpos.w;
	float r2=r*r;

	pVector l=lightpos;
	pVector l2=lightpos*lightpos;

	float e1=1.2f;
	float e2=1.2f*g_render->aspect;

	d=r2*l2.x - (l2.x+l2.z)*(r2-l2.z);
	if (d>=0)
	{
		d=sqrtf(d);

		float nx1=(r*l.x + d)/(l2.x+l2.z);
		float nx2=(r*l.x - d)/(l2.x+l2.z);

		float nz1=(r-nx1*l.x)/l.z;
		float nz2=(r-nx2*l.x)/l.z;

		float e=1.25f;
		float a=g_render->aspect;

		float pz1=(l2.x+l2.z-r2)/(l.z-(nz1/nx1)*l.x);
		float pz2=(l2.x+l2.z-r2)/(l.z-(nz2/nx2)*l.x);

		if (pz1<0)
		{
			float fx=nz1*e1/nx1;
			int ix=(int)((fx+1.0f)*sx*0.5f);

			float px=-pz1*nz1/nx1;
			if (px<l.x)
				rect[0]=max(rect[0],ix);
			else
				rect[2]=min(rect[2],ix);
		}

		if (pz2<0)
		{
			float fx=nz2*e1/nx2;
			int ix=(int)((fx+1.0f)*sx*0.5f);

			float px=-pz2*nz2/nx2;
			if (px<l.x)
				rect[0]=max(rect[0],ix);
			else
				rect[2]=min(rect[2],ix);
		}
	}

	d=r2*l2.y - (l2.y+l2.z)*(r2-l2.z);
	if (d>=0)
	{
		d=sqrtf(d);

		float ny1=(r*l.y + d)/(l2.y+l2.z);
		float ny2=(r*l.y - d)/(l2.y+l2.z);

		float nz1=(r-ny1*l.y)/l.z;
		float nz2=(r-ny2*l.y)/l.z;

		float pz1=(l2.y+l2.z-r2)/(l.z-(nz1/ny1)*l.y);
		float pz2=(l2.y+l2.z-r2)/(l.z-(nz2/ny2)*l.y);

		if (pz1<0)
		{
			float fy=nz1*e2/ny1;
			int iy=(int)((fy+1.0f)*sy*0.5f);

			float py=-pz1*nz1/ny1;
			if (py<l.y)
				rect[1]=max(rect[1],iy);
			else
				rect[3]=min(rect[3],iy);
		}

		if (pz2<0)
		{
			float fy=nz2*e2/ny2;
			int iy=(int)((fy+1.0f)*sy*0.5f);
			
			float py=-pz2*nz2/ny2;
			if (py<l.y)
				rect[1]=max(rect[1],iy);
			else
				rect[3]=min(rect[3],iy);
		}
	}

	int n=(rect[2]-rect[0])*(rect[3]-rect[1]);
	if (n<=0)
		return 0;
	if (n==sx*sy)
	{
		glDisable(GL_SCISSOR_TEST);
		return sx*sy;
	}

	glScissor(rect[0],rect[1],rect[2]-rect[0],rect[3]-rect[1]);
	glEnable(GL_SCISSOR_TEST);

	return n;
}

void unRenderer::draw_lights(pMesh *m,bool scissor)
{
	fb_bind_render(0);

	// 2D ortho porjection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,m_sizex,0,m_sizey,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glBlendFunc(GL_ONE,GL_ONE);
	glDisable(GL_BLEND);

	// draw ambient pass
	glColor4fv(&m->ambient.x);
	mrt_bind_texture(1);	// bind diffuse mrt texture
	draw_rect(0,0,m_sizex,m_sizey,false,false);
	mrt_unbind_texture(1);
	glColor4f(1,1,1,1);

	mrt_bind_texture(-1); // bind all mrt textures

	bind_light();

	pVector lightpos;
	int i,j=m->nlight,n,p;

	m_num_lights_drawn=0;
	m_percent_pixel_drawn=0;

	glEnable(GL_BLEND);

	for( i=0;i<j;i++ )
	{
		for( p=0;p<5;p++ )
		{
			float d=VECDOT(m->light[i].pos,g_render->view.planes[p])-g_render->view.planes[p].w;
			if (d<-m->light[i].pos.w)
				break;
		}
		if (p<5)
			continue;

		lightpos=m->light[i].pos*g_render->view_matrix;
		lightpos.w=m->light[i].pos.w;
		n=set_light_scissor(lightpos,m_sizex,m_sizey);
		if (n>0 && scissor==false)
		{
			n=m_sizex*m_sizey;
			glDisable(GL_SCISSOR_TEST);
		}
		if (n)
		{
			set_light_params(lightpos,m->light[i].color);

			draw_rect(0,0,m_sizex,m_sizey,true,false);

			m_num_lights_drawn++;
			m_percent_pixel_drawn+=n;
		}
	}

	glDisable(GL_SCISSOR_TEST);
	
	unbind_light();
	
	mrt_unbind_texture(-1);
	fb_unbind_render(0);

	m_percent_pixel_drawn=(m_num_lights_drawn?100*m_percent_pixel_drawn/(m_sizex*m_sizey*m_num_lights_drawn):0);
}

void unRenderer::draw_bloom()
{
	int bloom_sx=m_sizex/BLOOM_SCALE;
	int bloom_sy=m_sizey/BLOOM_SCALE;

	// blur horizontaly
	fb_bind_render(2);
	fb_bind_texture(0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glDisable(GL_BLEND);

	set_blur_params(false);
	bind_blur();
	draw_rect(0,0,bloom_sx,bloom_sy,false,false);
	unbind_blur();
	fb_unbind_texture(0,0);
	fb_unbind_render(2);

	// blur verticaly
	fb_bind_render(3);
	fb_bind_texture(2,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glDisable(GL_BLEND);

	set_blur_params(true);
	bind_blur();
	draw_rect(0,0,bloom_sx,bloom_sy,false,false);
	unbind_blur();
	fb_unbind_texture(2,0);
	fb_unbind_render(3);

	// add bloom to main scene
	fb_bind_render(0);
	fb_bind_texture(3,0);
	glBlendFunc(GL_ONE,GL_ONE);
	glEnable(GL_BLEND);
	draw_rect(0,0,m_sizex,m_sizey,false,false);
	fb_unbind_texture(3,0);
	fb_unbind_render(0);
}

void unRenderer::draw_geometry(pMesh *m,bool relief)
{
	mrt_bind_render();

	g_render->set_camera();

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f(1,1,1,1);
	glClearColor(g_render->bgcolor.x,g_render->bgcolor.y,g_render->bgcolor.z,1);
	glClearDepth(1);
	glDisable(GL_TEXTURE_2D);

	glColorMask(true,true,true,true);
	glDepthMask(true);

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glColorMask(false,false,false,false);
	glDepthMask(true);

	draw_depth_avatars();

	g_render->set_camera();

	draw_depth(m);

	glColorMask(true,true,true,true);
	glDepthMask(false);

	draw_material(m,relief);

	draw_material_avatars(relief);

	QActiveFrameWork->QFrame();
	//unProcessor->acPrintName(0);

	mrt_unbind_render();
}

void unRenderer::draw_debug(int sx,int sy)
{
	sx/=4;
	sy/=4;

	int x=0;
	int y=0;

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glDepthMask(false);
	glColorMask(true,true,true,true);

	// draw all mrt textures at top of screen
	for( int i=0;i<4;i++ )
	{
		mrt_bind_texture(i);
		draw_rect(x,y,sx,sy,false,true);
		mrt_unbind_texture(i);
		x+=sx;
	}
}

void unRenderer::draw_antialias()
{
	fb_bind_render(1);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);

	fb_bind_texture(0,1);
	mrt_bind_texture(0);

	//*cgGLSetParameter2f(m_apixelsize,1.0f/m_sizex,1.0f/m_sizey); 
	//*cgGLSetParameter1f(m_aweight,0.8f); 

	bind_antialias();

	draw_rect(0,0,m_sizex,m_sizey,false,false);

	unbind_antialias();

	fb_unbind_texture(0,1);
	mrt_unbind_texture(0);

	fb_unbind_render(1);

	pPBuffer *tmp;
	tmp=m_fb[0];
	m_fb[0]=m_fb[1];
	m_fb[1]=tmp;
}

void unRenderer::draw_final(int sx,int sy)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask(false);

	fb_bind_texture(0,0);

	draw_rect(0,0,sx,sy,false,true);

	fb_unbind_texture(0,0);
}

void unRenderer::checkError(const char *name, const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);
  
	if (error != CG_NO_ERROR)
		{
		if (error == CG_COMPILER_ERROR)
			{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s\n\n"
			"Cg compiler output...\n%s",
			name, situation, string,
			cgGetLastListing(g_render->cgcontext));*/

			std::string errorstr;
			errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG Compile ERROR", MB_OK);
			printf("CG:::Compile Error:::%s:::%s:::\n %s\n", name, situation, errorstr.c_str());
			for(;;) {};
			}
		else
			{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s",
			name, situation, string);*/

			//std::string errorstr("ERROR::: ");
			//errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG ERROR", MB_OK);
			}
		//while(1) { /* Infinite Loop */ }
		//exit(1);
		}
}

void unRenderer::GLEnable2D(void)
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

void unRenderer::GLDisable2D(void)
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void unRenderer::DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley)
{
	int m_x[4];
	int m_y[4];

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

	glEnable(GL_TEXTURE_2D);

	glBindTexture( GL_TEXTURE_2D, i_texture );

	glBegin( GL_QUADS );

	for(size_t id=0; id < 4; id++)
		{
		glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
		glVertex2d(m_x[id], m_y[id]);
		}

	glEnd();

	GLDisable2D();
}

#if 0
int DrawGLSceneRelief(GLvoid)										// Here's Where We Do All The Drawing
{
	g_render->set_camera();
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glBindTexture(GL_TEXTURE_2D, 1);			// Select Our Texture

	for (int loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
		{
		if (particle[loop].active)							// If The Particle Is Active
			{
				float x=particle[loop].x;						// Grab Our Particle X Position
				float y=particle[loop].y;						// Grab Our Particle Y Position
				float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				//glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);
				glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

				glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
					glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
					glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
					glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
					glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				glEnd();										// Done Building Triangle Strip

				particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
				particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
				particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

				particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
				particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

				if (particle[loop].life<0.0f)					// If Particle Is Burned Out
				{
					particle[loop].life=1.0f;					// Give It New Life
					particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
					particle[loop].x=0.0f;						// Center On X Axis
					particle[loop].y=0.0f;						// Center On Y Axis
					particle[loop].z=0.0f;						// Center On Z Axis
					particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
					particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
					particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
					particle[loop].r=colors[col][0];			// Select Red From Color Table
					particle[loop].g=colors[col][1];			// Select Green From Color Table
					particle[loop].b=colors[col][2];			// Select Blue From Color Table
				}
			}
		}

	return TRUE;											// Everything Went OK
}

#endif

inline void unRenderer::testfunction(void)
	{

	}