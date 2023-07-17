#include "paralelo3d.h"
#include "unRenderer.h"

#include "../../Texture/tgaload.h"
#include "../../Utility/unConsole.h"

#include "../../Base/UNcompiler.h"

#include <string>

#include "Q-NET-ProtoMap.h"

#if 0
	#define QAGEMODE_SURGERY
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#if 0
Q_Network *QNetwork;
#endif

//Temporary
float m_Xangle = 0;
float m_Yangle = 0;
float m_Zangle = 0;
float m_Wangle = 0;

using namespace GVARS;

int vectrans[32];
int vecvar[5];
bool vecvarDpress[16];
float vecvalue[4];
float valueX;
float valueY;
float valueZ;
bool rendswitchP = false;
bool rendswitchA = false;
bool physxswitchA = false;

float valuepose = 0;
int valueswitch = 0;

int vecrag = 0;

/// Construction vars ///
float gMouseDepth = 150;
bool gPickStay = false;

PxVec3 i_LocalBonePosition;
unsigned int i_BoneIter = 0;

CalVector _PositioningOffset;

int m_VehicleCount;

#if 0
#define CAL_ARB 1
#endif

#if 0
QSharedStruct<QAGE::QActiveFramewrk> QActiveFrameWork("GlobalQActiveFrameWork");

QSharedStruct<Digi::DigiMassCore> DigiMass("GlobalDigiMass");

QSharedStruct<UN::unMessageCore> unProcessor("GlobalunProcessor");

QSharedStruct<trr::unTerrainCell> QActiveFrameWork->m_trrCell("GlobaltrrCell");
QSharedStruct<trr::unTrrBank> QActiveFrameWork->i_TrrBank("GlobalTrrBank");

QSharedStruct<UN::unShapeBank> i_ShapeBank("GlobalShapeBank");
QSharedStruct<UN::unShape> i_shape("Globalshape");

QSharedStruct<OSI::OsirusCore> i_OsirusCore("GlobalOsirus");
#endif

#if 0
QSharedStruct<QAGE::QActiveFramewrk> QActiveFrameWork;

Digi::DigiMassCore* DigiMass;

QSharedStruct<UN::unMessageCore> unProcessor;

QSharedStruct<trr::unTerrainCell> QActiveFrameWork->m_trrCell;
QSharedStruct<trr::unTrrBank> QActiveFrameWork->i_TrrBank;

QSharedStruct<UN::unShapeBank> i_ShapeBank;
QSharedStruct<UN::unShape> i_shape;

QSharedStruct<OSI::OsirusCore> i_OsirusCore;
#endif

extern QAGE::QActiveFramewrk* QActiveFrameWork;

//Digi::DigiMassCore* DigiMass;

//trr::unTerrainCell* QActiveFrameWork->m_trrCell;
//trr::unTrrBank* QActiveFrameWork->i_TrrBank;

extern UN::unMessageCore* unProcessor;

extern UN::unShapeBank* i_ShapeBank;
extern UN::unShape* i_shape;

unRenderer::unRenderer()
{
	m_vert_prog=0;
	m_vtile=0;
	m_vdepth=0;

	m_vert_mesh=0;
	m_meshtile=0;
	m_meshdepth=0;
	m_meshrotationMatrices = 0;
	m_meshcolormap = 0;

	m_vert_terrain=0;
	m_terraintile=0;
	m_terraindepth=0;
	//m_terrainrotationMatrices = 0;
	m_terraincolormap = 0;

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

	ClothLocator.x = 0;
	ClothLocator.y = 0;
	ClothLocator.z = 0;
	m_PointLocator = new unPointLocator();
	m_PointLocator->setPos(0, 0, 0);
	m_SurgeryMode = 0;
	m_keyPress = 0;

#if 0
	_->SurgeryFocus.x = 0;
	_->SurgeryFocus.y = 0;
	_->SurgeryFocus.z = 0;
#endif

	vecvarDpress[0] = false;
	vecvarDpress[1] = false;
	vecvarDpress[2] = false;
	vecvarDpress[3] = false;
	vecvarDpress[4] = false;
	vecvarDpress[5] = false;
	vecvarDpress[6] = false;
	vecvarDpress[7] = false;
	vecvarDpress[8] = false;
	vecvarDpress[9] = false;
	vecvarDpress[10] = false;
	vecvarDpress[11] = false;
	vecvarDpress[12] = false;

	valueX = -0.14;
	valueY = 10.05;
	valueZ = 2.55;

	_PositioningOffset.x = 0;
	_PositioningOffset.y = 0;
	_PositioningOffset.z = 0;

#if 0
	//###-- - Sense Vector - --###//
	if(KEY_DOWN(QIN_KP7))
		{
		valueX += 0.01;

		printf("Sense Vector Left - %f\n", valueX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		valueX -= 0.01;

		printf("Sense Vector Left - %f\n", valueX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		valueY += 0.01;

		printf("Sense Vector Up - %f\n", valueY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		valueY -= 0.01;

		printf("Sense Vector Up - %f\n", valueY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		valueZ += 0.01;

		printf("Sense Vector In - %f\n", valueZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		valueZ -= 0.01;

		printf("Sense Vector In - %f\n", valueZ);
		}
#endif
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

	sx/=UNREND_BLOOM_SCALE;
	sy/=UNREND_BLOOM_SCALE;
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

#ifdef UNRENDER_FRAMEMEMORY
	m_Fcursor = 0;
	m_FcurCounter = 0;
	for(i = 0; i < UNREND_FRAMEMEMSIZE; i++)
		{
		if(m_FrameMemory[i])
			{
			glDeleteTextures(1, &m_FrameMemory[i]);
			m_FrameMemory[i] = CreateEmptyTexture(sx, sy);
			}
		else m_FrameMemory[i] = CreateEmptyTexture(sx, sy);
		}
#endif
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

#ifdef UNRENDER_FRAMEMEMORY
	glDeleteTextures(UNREND_FRAMEMEMSIZE,m_FrameMemory);
	for(i = 0; i < UNREND_FRAMEMEMSIZE; i++) m_FrameMemory[i] = 0;
#endif

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
	if (g_render == 0)
		return false;

	free_programs();

	unConsoleAttribute(CONSOLE_ERROR);

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

	if(programtext)
		{
		m_vert_prog = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBVP1,
				"view_space",
				(const char **)m_vert_options);
		if(m_vert_prog) count++;

		checkError("view_space", "cgCreateProgram");

		vertexProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
		//*cgGLSetOptimalOptions(vertexProfile);
		checkError("Get Profile", "selecting vertex profile");

		vertterrainProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
		//*cgGLSetOptimalOptions(vertterrainProfile);
		checkError("Get Profile", "selecting vertex profile");

		m_vert_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				vertexProfile,
				"view_mesh",
				0);

		checkError("view_mesh", "cgCreateProgram");

		m_vert_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				vertterrainProfile,
				"view_terrain",
				0);

		checkError("view_terrain", "cgCreateProgram");

		m_frag_prog_normal = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal",
				(const char **)m_frag_options);
		if(m_frag_prog_normal) count++;

		checkError("mrt_normal", "cgCreateProgram");

		m_frag_mesh = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_mesh",
				(const char **)m_frag_options);

		checkError("mrt_normal_mesh", "cgCreateProgram");

		m_frag_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_terrain",
				(const char **)m_frag_options);

		checkError("mrt_normal_terrain", "cgCreateProgram");

		m_frag_prog_relief = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_relief",
				(const char **)m_frag_options);
		if(m_frag_prog_relief) count++;

		checkError("mrt_relief_relaxed", "cgCreateProgram");

		m_frag_prog_light = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_light",
				(const char **)m_frag_options);
		if(m_frag_prog_light) count++;

		checkError("mrt_light", "cgCreateProgram");

		m_frag_prog_blur = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"blur",
				0);
		if (m_frag_prog_blur) count++;

		checkError("blur", "cgCreateProgram");

		m_frag_prog_antialias = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"anti_alias",
				0);
		if(m_frag_prog_antialias) count++;

		checkError("anti_alias", "cgCreateProgram");

		ret=(count==6);

		if(ret)
			{
			//*cgGLLoadProgram(m_vert_prog);
			CgCheckError();

			//*cgGLLoadProgram(m_vert_mesh);
			CgCheckError();

			//*cgGLLoadProgram(m_vert_terrain);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_prog_normal);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_mesh);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_terrain);
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

			m_meshtile=cgGetNamedParameter(m_vert_mesh,"tile");
			m_meshdepth=cgGetNamedParameter(m_vert_mesh,"depth");
			m_meshrotationMatrices=cgGetNamedParameter(m_vert_mesh,"rotationMatrices");

			m_terraintile=cgGetNamedParameter(m_vert_terrain,"tile");
			m_terraindepth=cgGetNamedParameter(m_vert_terrain,"depth");
			//m_terrainrotationMatrices=cgGetNamedParameter(m_vert_terrain,"rotationMatrices");

			m_meshcolormap=cgGetNamedParameter(m_frag_mesh,"colortex");
			m_meshAmbient=cgGetNamedParameter(m_frag_mesh,"i_Ambient");
			m_meshDiffuse=cgGetNamedParameter(m_frag_mesh,"i_Diffuse");
			m_meshSpecular=cgGetNamedParameter(m_frag_mesh,"i_Specular");
			m_meshLightVec=cgGetNamedParameter(m_frag_mesh,"i_LightVec");
			m_meshEyeVec=cgGetNamedParameter(m_frag_mesh,"i_EyeVec");
			m_meshAlpha=cgGetNamedParameter(m_frag_mesh,"i_Alpha");

			m_terraincolormap=cgGetNamedParameter(m_frag_terrain,"colortex");
			m_terrainAmbient=cgGetNamedParameter(m_frag_terrain,"i_Ambient");
			m_terrainDiffuse=cgGetNamedParameter(m_frag_terrain,"i_Diffuse");
			m_terrainSpecular=cgGetNamedParameter(m_frag_terrain,"i_Specular");
			m_terrainLightVec=cgGetNamedParameter(m_frag_terrain,"i_LightVec");
			m_terrainEyeVec=cgGetNamedParameter(m_frag_terrain,"i_EyeVec");
			m_terrainAlpha=cgGetNamedParameter(m_frag_terrain,"i_Alpha");

			if(!m_meshtile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_meshdepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_meshrotationMatrices) printf("ERROR:::LoadPrograms rotationMatrices parameter not found\n");

			if(!m_meshcolormap) printf("ERROR:::LoadPrograms m_meshcolormap parameter not found\n");
			if(!m_meshAmbient) printf("ERROR:::LoadPrograms m_meshAmbient parameter not found\n");
			if(!m_meshDiffuse) printf("ERROR:::LoadPrograms m_meshDiffuse parameter not found\n");
			if(!m_meshSpecular) printf("ERROR:::LoadPrograms m_meshSpecular parameter not found\n");
			if(!m_meshLightVec) printf("ERROR:::LoadPrograms m_meshLightVec parameter not found\n");
			if(!m_meshEyeVec) printf("ERROR:::LoadPrograms m_meshEyeVec parameter not found\n");
			if(!m_meshAlpha) printf("ERROR:::LoadPrograms m_meshAlpha parameter not found\n");

			if(!m_terraincolormap) printf("ERROR:::LoadPrograms m_terraincolormap parameter not found\n");
			if(!m_terrainAmbient) printf("ERROR:::LoadPrograms m_terrainAmbient parameter not found\n");
			if(!m_terrainDiffuse) printf("ERROR:::LoadPrograms m_terrainDiffuse parameter not found\n");
			if(!m_terrainSpecular) printf("ERROR:::LoadPrograms m_terrainSpecular parameter not found\n");
			if(!m_terrainLightVec) printf("ERROR:::LoadPrograms m_terrainLightVec parameter not found\n");
			if(!m_terrainEyeVec) printf("ERROR:::LoadPrograms m_terrainEyeVec parameter not found\n");
			if(!m_terrainAlpha) printf("ERROR:::LoadPrograms m_terrainAlpha parameter not found\n");

			if(!m_terraintile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_terraindepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			//if(!m_terrainrotationMatrices) printf("ERROR:::LoadPrograms rotationMatrices parameter not found\n");

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

	unConsoleReset();

	///// Reflective Shadow Mapping /////
#if 0
	m_RSM = new RSM();
#endif

	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk();
	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	//DigiMass.Acquire("GlobalDigiMass");
	//DigiMass = new Digi::DigiMassCore();

#if 0
	QActiveFrameWork->DigiMass = new Digi::DigiMassCore();
	QActiveFrameWork->DigiMass->Start();
#endif

	playerAV.Acquire("playerAV");

#if 1
	QActiveFrameWork->acDataInit();
#endif

#if 0
	//for(int i = 0; i < 500; i++) Digi::CreateCube(PxVec3(((rand()%50)-25), ((rand()%50)-25), ((rand()%50)-25)),1);
	//for(int i = 0; i < 200; i++) QActiveFrameWork->DigiMass->acCreateCube(PxVec3(((rand()%500)-250), 125, ((rand()%500)-250)), 1);

	//i_OsirusCore.Acquire("GlobalOsirus");
	i_OsirusCore = new OSI::OsirusCore();
	//i_OsirusCore->acTest();
	//for(;;) {}

	//unProcessor.Acquire("GlobalunProcessor");

#if 1
	unProcessor = new UN::unMessageCore(g_render->hwnd);
#endif

	//unProcessor = new UN::unMessageCore(g_render->hwnd);

	//unProcessor->m_memorymanager->acLockModule("Unification.exe");

	//unProcessor->m_memorymanager->acSetPriority();

	// Test Engine Dynamic Shapes
	//i_ShapeBank.Acquire("GlobalShapeBank");
	i_ShapeBank = new UN::unShapeBank();

#if 1
	i_ShapeBank->acCreateShape(UN_SHAPE_SPHERE, 50);
#endif
	//i_ShapeBank->acAddInstance(0, 0, -355.446411, 0);

	i_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
	//i_shape.Acquire("Globalshape");

#if 0
	while(QActiveFrameWork->DigiMass->getInternalState() < 1)
		{
#endif

#if 1
		//QActiveFrameWork->m_trrCell.Acquire("GlobaltrrCell");
		QActiveFrameWork->m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
		//QActiveFrameWork->m_trrCell->acAllocate(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
		//QActiveFrameWork->m_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");
		QActiveFrameWork->m_trrCell->acLoad(0, 0, NULL);
#endif

#if 1
		//QActiveFrameWork->i_TrrBank.Acquire("GlobalTrrBank");
		QActiveFrameWork->i_TrrBank = new trr::unTrrBank();
		QActiveFrameWork->i_TrrBank->acSetDimensions(QActiveFrameWork->m_trrCell->m_fdim);
#if 0
		QActiveFrameWork->i_TrrBank->m_TerrainCell.push_back(QActiveFrameWork->m_trrCell);
		QActiveFrameWork->i_TrrBank->acAddInstance(0, 0, -355.446411, 0);
#else
		QActiveFrameWork->i_TrrBank->acServeBank(QActiveFrameWork->m_trrCell, 12, false);
		QActiveFrameWork->i_TrrBank->acAddInstance(0, 0, -355.446411, 0);
#endif

		float i_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

		QActiveFrameWork->i_TrrBank->acAddClone(0, i_gridincrement, -355.446411, 0, 13);
		QActiveFrameWork->i_TrrBank->acAddClone(0, -i_gridincrement, -355.446411, 0, 11);
		QActiveFrameWork->i_TrrBank->acAddClone(0, 0, -355.446411, i_gridincrement, 7);
		QActiveFrameWork->i_TrrBank->acAddClone(0, 0, -355.446411, -i_gridincrement, 17);
		QActiveFrameWork->i_TrrBank->acAddClone(0, i_gridincrement, -355.446411, i_gridincrement, 6);
		QActiveFrameWork->i_TrrBank->acAddClone(0, -i_gridincrement, -355.446411, i_gridincrement, 8);
		QActiveFrameWork->i_TrrBank->acAddClone(0, i_gridincrement, -355.446411, -i_gridincrement, 16);
		QActiveFrameWork->i_TrrBank->acAddClone(0, -i_gridincrement, -355.446411, -i_gridincrement, 18);

#if 0
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), i_gridincrement, -355.446411, 0);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), -i_gridincrement, -355.446411, 0);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), 0, -355.446411, i_gridincrement);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), 0, -355.446411, -i_gridincrement);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), i_gridincrement, -355.446411, i_gridincrement);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), -i_gridincrement, -355.446411, i_gridincrement);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), i_gridincrement, -355.446411, -i_gridincrement);
		QActiveFrameWork->i_TrrBank->acAddInstance(QActiveFrameWork->i_TrrBank->acClone(0), -i_gridincrement, -355.446411, -i_gridincrement);
#endif
#if 0
		}
#endif
#endif

	QActiveFrameWork->DigiMass->incInternalState();
#endif

	return ret;
}

void unRenderer::sync_PhysicsMemory(void)
{
	m_VehicleCount = QActiveFrameWork->DigiMass->getVehicleCount();

	//PxMat34 i_matrix;
	for(SCRAM = 0; SCRAM < m_VehicleCount; SCRAM++)
		{
		//vec_VehiclePos.push_back(i_matrix);
		}
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

void unRenderer::bind_terrain_vertex()
{
	//*cgGLBindProgram(m_vert_terrain);
	//*cgGLEnableProfile(vertterrainProfile);
}

void unRenderer::unbind_terrain_vertex()
{
	//*cgGLDisableProfile(vertterrainProfile);
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

void unRenderer::set_normal_params_static(const pVector& diffuse,const pVector& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
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
	glBindTexture(GL_TEXTURE_2D,texcolor);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_relief_params_static(const pVector& diffuse,const pVector& specular,float tile,float depth,GLuint texcolor,GLuint texnormal)
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
	glBindTexture(GL_TEXTURE_2D,texcolor);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal);
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
		float fp=1.25/(m_sizex/UNREND_BLOOM_SCALE);
		for( i=0;i<j;i++ )
		{
			param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,(i-k)*fp,0);
		}
	}
	else
	{
		float fp=1.25/(m_sizey/UNREND_BLOOM_SCALE);
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

void unRenderer::draw_depth_meshes(void)
{
	int va=0,vb=1;

	for(unsigned int i = 0; i < _->NomSEnergy; i++)
		{
		for(unsigned int k = 0; k < 5; k++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.z);
			glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

			glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);

			if(Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar < 2)
				{
				pMesh* i_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar]->m_submesh[0];
				i_mesh->array_lock(va,vb);

				i_mesh->array_draw(vb);

				i_mesh->array_unlock();
				}
			}
		}

	if(player->WeaponStatus > 1)
		{
		glLoadIdentity();

		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		Qpo->AvatarView_GetBoneTransform(playerAV.operator ->(), "BIP01 R HAND", &player->RFistPosV, true);

		glTranslatef(player->RFistPosV.Translation.x, player->RFistPosV.Translation.y, player->RFistPosV.Translation.z);
		glMultMatrixf(player->RFistPosV.Matrix.mf);

		glTranslatef(valueX, valueY, valueZ);

		glScalef(player->Weapon.Scale.x, player->Weapon.Scale.y, player->Weapon.Scale.z);

		pMesh* f_mesh;
		for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[player->Weapon.Avatar]->m_submesh.num; f_meshcnt++)
			{
			f_mesh = QActiveFrameWork->meshstaticTemplates[player->Weapon.Avatar]->m_submesh[f_meshcnt];

			f_mesh->array_lock(va,vb);

			f_mesh->array_draw(vb);

			f_mesh->array_unlock();
			}
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int i_vehicleiter = 0; i_vehicleiter < m_VehicleCount; i_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[i_vehicleiter].getColumnMajor44(glMat);
		glMultMatrixf(glMat);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);				// Rotate X, Y, Z
		glRotatef(-90, 0.0f, 0.0f, 1.0f);
		//glRotatef(radToDeg(-Q_Forge->Forge[AIcount].AJAngles.y), 0.0f, 0.0f, 1.0f);

		//glTranslatef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.z);
		//glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

		//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
		glScalef(0.007, 0.007, 0.007);

		for(int i = 0; i < QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh.num; i++)
			{
			pMesh* i_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh[i];

			i_mesh->array_lock(va,vb);

			i_mesh->array_draw(vb);

			i_mesh->array_unlock();
			}
		}
#endif
}

void unRenderer::draw_depth_avatars(void)
{
#if 0
	//// DEBUG: CLOTH SIM
	static CalVector spherePosition;
	spherePosition.set(playerAV->Avatar.Mesh->Sphere.x, playerAV->Avatar.Mesh->Sphere.y, playerAV->Avatar.Mesh->Sphere.z);
	static float sphereRadius = 15.0f;

	playerAV->Avatar.Mesh->m_calModel->getSpringSystem()->setSphere(spherePosition.x, spherePosition.y, spherePosition.z, sphereRadius);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(spherePosition.x + sphereRadius, spherePosition.y, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y + sphereRadius, spherePosition.z);
	glVertex3f(spherePosition.x - sphereRadius, spherePosition.y, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y - sphereRadius, spherePosition.z);

	glVertex3f(spherePosition.x + sphereRadius, spherePosition.y, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y, spherePosition.z + sphereRadius);
	glVertex3f(spherePosition.x - sphereRadius, spherePosition.y, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y, spherePosition.z - sphereRadius);

	glVertex3f(spherePosition.x + sphereRadius, spherePosition.y, spherePosition.z);

	glVertex3f(spherePosition.x, spherePosition.y + sphereRadius, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y, spherePosition.z + sphereRadius);
	glVertex3f(spherePosition.x, spherePosition.y - sphereRadius, spherePosition.z);
	glVertex3f(spherePosition.x, spherePosition.y, spherePosition.z - sphereRadius);
	glVertex3f(spherePosition.x, spherePosition.y + sphereRadius, spherePosition.z);
	glEnd();
	//// DEBUG END
#endif

  //CalSkeleton *pCalSkeleton = playerAV->Avatar.Mesh->m_calModel->getSkeleton();

  // Note :
  // You have to call coreSkeleton.calculateBoundingBoxes(calCoreModel)
  // during the initialisation (before calModel.create(calCoreModel))
  // if you want to use bounding boxes.

#if 0
  playerAV->Avatar.Mesh->m_calModel->getSkeleton()->calculateBoundingBoxes();
#endif

	// Note:
	// Uncomment the next lines if you want to test the experimental collision system.
	// Also remember that you need to call calculateBoundingBoxes()

	//playerAV->Avatar.Mesh->m_calModel->getSpringSystem()->setForceVector(CalVector(0.0f,0.0f,0.0f));
	//playerAV->Avatar.Mesh->m_calModel->getSpringSystem()->setCollisionDetection(true);  

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
if(player->AirJinkRotFG == 1)
	{
	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Viewform.mf);
	}
else
	{
	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
	}
#endif

	///// Mesh Settings /////
	bool i_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		/*if(playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}*/

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

			//if(playerAV->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
			//{
			//printf("Treace no error\n");
			//}

			if(playerAV->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
				}
			else
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
				}

#if 0
				
			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif


#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	//////////////////////////////////////
	////// Render Player Shadows /////////

	///// Mesh Settings /////
	if(player->ShadowsOn)
		{
		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player->Shadows[SCRAM].Xform.Translation.x, player->Shadows[SCRAM].Xform.Translation.y, player->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player->Shadows[SCRAM].Xform.Matrix.mf);

			for(hardwareMeshId=0;hardwareMeshId<player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					CalQuaternion rotationBoneSpace = player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, player->Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());
					CalVector translationBoneSpace = player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, player->Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());

					CalMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}
			}
		}


	//////////////////////////////////////
	////// Render NON-Player Meshes //////

	for(i = 0; i < _->NomAI; i++)
		{
		////// Set Camera //////
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		if(Q_Forge->Forge[i].AirJinkRotFG == 1)
			{
			glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
			glMultMatrixf(Q_Forge->Forge[i].AV.Viewform.mf);
			}
		else
			{
			glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
			glMultMatrixf(Q_Forge->Forge[i].AV.Xform.Matrix.mf);
			}

		int hardwareMeshId = 0;
		for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
			{
			Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
				{
				CalQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calModel->getSkeleton());
				CalVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calModel->getSkeleton());

				CalMatrix rotationMatrix = rotationBoneSpace;

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
				pMaterial *mat;
				mat=&mesh->mat[mesh->face[0].material];
				set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
				glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
				}

			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

			if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
			else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
			}

		//////////////////////////////////////
		////// Render AI Shadows /////////////

		///// Mesh Settings /////
		if(Q_Forge->Forge[i].ShadowsOn)
			{
			for(SCRAM = 1; SCRAM < 4; SCRAM++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.x, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.y, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.z);
				glMultMatrixf(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);

				int hardwareMeshId = 0;
				for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}
				}
			}
		}

	unbind_mesh_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void unRenderer::draw_depth_terrain_old(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int i_iterator;
	int i_layer;
	int i_instance;
	int i_index;

#if 0
	for(i_iterator = 0; i_iterator < QActiveFrameWork->i_TrrBank->m_TerrainCell.size(); i_iterator++)
#else
	for(i_iterator = 0; i_iterator < TCELL_RENDER_MAX; i_iterator++)
#endif
		{
		i_index = QActiveFrameWork->i_TrrBank->m_CellRender[i_iterator];

		for(i_layer = 0; i_layer < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer.size(); i_layer++)
			{
			///// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);
				}
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);

#if 0	// Trace Instance Count
	printf("%i Instances\n", QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->m_Instance.size());
#endif
#endif
}

void unRenderer::draw_depth_shapes(void)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	//bind_terrain_vertex();
	bind_terrain_vertex();

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
	//glDrawElements(GL_TRIANGLES, i_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

	//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	//glMultMatrixf(playerAV->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, i_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void unRenderer::draw_depth_shape_instances(void)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int i_iterator;
	int i_instance;
	for(i_iterator = 0; i_iterator < i_ShapeBank->m_Shape.size(); i_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[5]);

		for(i_instance = 0; i_instance < i_ShapeBank->m_Shape[i_iterator]->m_Instance.size(); i_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->x, i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->y, i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, i_ShapeBank->m_Shape[i_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
					CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

					CalMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}*/
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void unRenderer::draw_material(pMesh *m,bool relief)
{
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock(va,vb);

	int i,j=_->mesh->nfacemat,k;
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

void unRenderer::draw_material_mesh(pMesh *m,bool relief)
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
		//mat=&m->mat[m->face[k].material];
		//mat=&mesh->mat[mesh->face[k].material];
		mat=&m->mat[0];
		//if (relief==false || mat->bump==0 || mat->texnormalid==-1)
		//	{
			set_normal_params_static(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&m->facevert[k*3]);
		//	}
		k+=m->facemat[i];
		}

	unbind_normal();

	bind_relief();

	k=0;
	if (relief==true)
	for( i=0;i<j;i++ )
		{
		//mat=&m->mat[m->face[k].material];
		mat=&m->mat[0];
		//if (!(mat->bump==0 || mat->texnormalid==-1))
		//	{
			//set_relief_params(mat->diffuse,mat->specular,1,mat->bump,mat->texid,mat->texnormalid);
			set_relief_params_static(mat->diffuse,mat->specular,1,0,mat->texid,mat->texnormalid);
			glDrawElements(GL_TRIANGLES,3*m->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&m->facevert[k*3]);
		//	}
		k+=m->facemat[i];
		}

	unbind_relief();

	unbind_vertex();

	m->array_unlock();
}

void unRenderer::draw_material_meshes(void)
{
	bool relief = true;

	for(unsigned int i_Iter = 0; i_Iter < _->NomSEnergy; i_Iter++)
		{
		for(unsigned int l = 0; l < 5; l++)
			{
			if(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Avatar < 2)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.x, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.y, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.z);
				glMultMatrixf(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Viewform.Matrix.mf);

				glScalef(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Scale.x, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Scale.y, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Scale.z);

				pMesh* i_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Avatar]->m_submesh[0];

				int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
				i_mesh->array_lock(va,vb);

				int i,j=i_mesh->nfacemat,k;
				pMaterial *mat;
				
				bind_vertex();

				bind_normal();

				k=0;
				for( i=0;i<j;i++ )
					{
					//mat=&i_mesh->mat[i_mesh->face[k].material];
					//mat=&mesh->mat[mesh->face[k].material];
					mat=&i_mesh->mat[0];
					//if (relief==false || mat->bump==0 || mat->texnormalid==-1)
					//	{
						set_normal_params_static(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glDrawElements(GL_TRIANGLES,3*i_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&i_mesh->facevert[k*3]);
					//	}
					k+=i_mesh->facemat[i];
					}

				unbind_normal();

				bind_relief();

				k=0;
				if (relief==true)
				for( i=0;i<j;i++ )
					{
					//mat=&i_mesh->mat[i_mesh->face[k].material];
					mat=&i_mesh->mat[0];
					//if (!(mat->bump==0 || mat->texnormalid==-1))
					//	{
						//set_relief_params(mat->diffuse,mat->specular,1,mat->bump,mat->texid,mat->texnormalid);
						//set_relief_params_static(mat->diffuse,mat->specular,1,1,Media->expandro1,Media->expandro1);
						set_relief_params_static(mat->diffuse,mat->specular,1,1,mat->texid,mat->texnormalid);
						glDrawElements(GL_TRIANGLES,3*i_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&i_mesh->facevert[k*3]);
					//	}
					k+=i_mesh->facemat[i];
					}

				unbind_relief();
				
				unbind_vertex();

				i_mesh->array_unlock();
				}
			}
		}

	if(player->WeaponStatus > 1)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		glTranslatef(player->RFistPosV.Translation.x, player->RFistPosV.Translation.y, player->RFistPosV.Translation.z);
		glMultMatrixf(player->RFistPosV.Matrix.mf);

		glTranslatef(valueX, valueY, valueZ);

		glScalef(player->Weapon.Scale.x, player->Weapon.Scale.y, player->Weapon.Scale.z);

		pMesh* f_mesh;
		for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[player->Weapon.Avatar]->m_submesh.num; f_meshcnt++)
			{
			f_mesh = QActiveFrameWork->meshstaticTemplates[player->Weapon.Avatar]->m_submesh[f_meshcnt];

			int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
			f_mesh->array_lock(va,vb);

			int i,j=f_mesh->nfacemat,k;
			pMaterial *mat;
		
			bind_vertex();

			bind_normal();

			k=0;
			for( i=0;i<j;i++ )
				{
				//mat=&f_mesh->mat[f_mesh->face[k].material];
				//mat=&mesh->mat[mesh->face[k].material];
				mat=&f_mesh->mat[0];
				//if (relief==false || mat->bump==0 || mat->texnormalid==-1)
				//	{
					set_normal_params_static(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glDrawElements(GL_TRIANGLES,3*f_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&f_mesh->facevert[k*3]);
				//	}
				k+=f_mesh->facemat[i];
				}

			unbind_normal();

			bind_relief();

			k=0;
			if (relief==true)
			for( i=0;i<j;i++ )
				{
				//mat=&f_mesh->mat[f_mesh->face[k].material];
				mat=&f_mesh->mat[0];
				//if (!(mat->bump==0 || mat->texnormalid==-1))
				//	{
					//set_relief_params(mat->diffuse,mat->specular,1,mat->bump,mat->texid,mat->texnormalid);
					//set_relief_params_static(mat->diffuse,mat->specular,1,1,Media->expandro1,Media->expandro1);
					set_relief_params_static(mat->diffuse,mat->specular,1,1,mat->texid,mat->texnormalid);
					glDrawElements(GL_TRIANGLES,3*f_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&f_mesh->facevert[k*3]);
				//	}
				k+=f_mesh->facemat[i];
				}

			unbind_relief();
		
			unbind_vertex();

			f_mesh->array_unlock();
			}
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int i_vehicleiter = 0; i_vehicleiter < m_VehicleCount; i_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[i_vehicleiter].getColumnMajor44(glMat);
		glMultMatrixf(glMat);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(-90, 0.0f, 0.0f, 1.0f);

		//glTranslatef(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.x, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.y, Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Xform.Translation.z);
		//glMultMatrixf(Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Viewform.Matrix.mf);

		//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
		glScalef(0.007, 0.007, 0.007);

		for(int iter = 0; iter < QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh.num; iter++)
			{
			pMesh* i_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i_Iter].AvatarFlag[l].Avatar*/]->m_submesh[iter];

			int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
			i_mesh->array_lock(va,vb);

			int i,j=i_mesh->nfacemat,k;
			pMaterial *mat;
			
			bind_vertex();

			bind_normal();

			k=0;
			for( i=0;i<j;i++ )
				{
				//mat=&i_mesh->mat[i_mesh->face[k].material];
				//mat=&mesh->mat[mesh->face[k].material];
				mat=&i_mesh->mat[0];
				//if (relief==false || mat->bump==0 || mat->texnormalid==-1)
				//	{
					set_normal_params_static(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glDrawElements(GL_TRIANGLES,3*i_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&i_mesh->facevert[k*3]);
				//	}
				k+=i_mesh->facemat[i];
				}

			unbind_normal();

			bind_relief();

			k=0;
			if (relief==true)
			for( i=0;i<j;i++ )
				{
				//mat=&i_mesh->mat[i_mesh->face[k].material];
				mat=&i_mesh->mat[0];
				//if (!(mat->bump==0 || mat->texnormalid==-1))
				//	{
					//set_relief_params(mat->diffuse,mat->specular,1,mat->bump,mat->texid,mat->texnormalid);
					//set_relief_params_static(mat->diffuse,mat->specular,1,1,Media->expandro1,Media->expandro1);
					set_relief_params_static(mat->diffuse,mat->specular,1,1,mat->texid,mat->texnormalid);
					glDrawElements(GL_TRIANGLES,3*i_mesh->facemat[i],GL_UNSIGNED_INT,vb?(void *)(k*3*sizeof(unsigned int)):&i_mesh->facevert[k*3]);
				//	}
				k+=i_mesh->facemat[i];
				}

			unbind_relief();
			
			unbind_vertex();

			i_mesh->array_unlock();
			}
		}
#endif
}

void unRenderer::draw_material_avatars(bool relief)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	
	// Bind CG programs
	bind_mesh_vertex();
	//*cgGLBindProgram(m_frag_mesh);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	static GLfloat lightPosition[] = {0.2, 1.0, 0.3, 1.0};
	static GLfloat lightColor[] = {0.8, 1.0, 0.8, 1.0}; /* green-tinted */

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
if(player->AirJinkRotFG == 1)
	{
	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Viewform.mf);
	}
else
	{
	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);
	}
#endif

	/// Player Mesh Settings ///
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		//glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

#if 0
			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

			if(playerAV->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
				}
			else
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
				}

#if 0
			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

			//glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
		diffuseColor[0] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
		diffuseColor[1] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
		diffuseColor[2] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
#endif

		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

		//pVector lightpos;
		//lightpos.x = mesh->light[1].pos.x - playerAV->Xform.Translation.x;
		//lightpos.y = mesh->light[1].pos.y - playerAV->Xform.Translation.y;
		//lightpos.z = mesh->light[1].pos.z - playerAV->Xform.Translation.z;

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	////////////////////////////////////
	////// Render Player Shadows ///////

	if(player->ShadowsOn)
		{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player->Shadows[SCRAM].Xform.Translation.x, player->Shadows[SCRAM].Xform.Translation.y, player->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player->Shadows[SCRAM].Xform.Matrix.mf);

			glDisable(GL_DEPTH_TEST);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable(GL_BLEND);

			/// Player Mesh Settings ///
			for(hardwareMeshId=0;hardwareMeshId<player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
				// set the material diffuse color
				player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
				// set the material specular color
				player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					CalQuaternion rotationBoneSpace = player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, player->Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());
					CalVector translationBoneSpace = player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, player->Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());

					CalMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

					//glActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(GL_TEXTURE_2D,(GLuint)player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
				diffuseColor[0] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
				diffuseColor[1] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
				diffuseColor[2] = player->BFO.CharDATA[player->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
#endif

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, player->Shadows[SCRAM].Avatar.m_Alpha);

				//pVector lightpos;
				//lightpos.x = mesh->light[1].pos.x - playerAV->Xform.Translation.x;
				//lightpos.y = mesh->light[1].pos.y - playerAV->Xform.Translation.y;
				//lightpos.z = mesh->light[1].pos.z - playerAV->Xform.Translation.z;

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

				if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ player->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}
			}

		glDisable(GL_BLEND);
		}


	////////////////////////////////////
	////// Render NON-Player Mesh //////

	for(i = 0; i < _->NomAI; i++)
		{
		////// Set Camera //////
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		if(Q_Forge->Forge[i].AirJinkRotFG == 1)
			{
			glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
			glMultMatrixf(Q_Forge->Forge[i].AV.Viewform.mf);
			}
		else
			{
			glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
			glMultMatrixf(Q_Forge->Forge[i].AV.Xform.Matrix.mf);
			}

		for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
			{
			Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

			unsigned char meshColor[4];
			float materialColor[4];
			float diffuseColor[4];
			float specularColor[4];

			// set the material ambient color
			Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
			
			// set the material diffuse color
			Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
			
			// set the material specular color
			Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
			specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
			
			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
				{
				CalQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calModel->getSkeleton());
				CalVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calModel->getSkeleton());

				CalMatrix rotationMatrix = rotationBoneSpace;

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
				pMaterial *mat;
				mat=&mesh->mat[mesh->face[0].material];
				set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
				glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

				//glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				}

			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

			if(hardwareMeshId < 38)
				{
				diffuseColor[0] = player->BFO.CharDATA[player->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.RED[hardwareMeshId] / 255;
				diffuseColor[1] = player->BFO.CharDATA[player->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
				diffuseColor[2] = player->BFO.CharDATA[player->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
				}
			else
				{
				diffuseColor[0] = 0;
				diffuseColor[1] = 0;
				diffuseColor[2] = 0;
				}

			//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
			//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
			//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
			//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].AV.Avatar.m_Alpha);

			if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
			else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
			}

		////////////////////////////////////
		////// Render AI Shadows ///////////

		if(Q_Forge->Forge[i].ShadowsOn)
			{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			for(SCRAM = 1; SCRAM < 4; SCRAM++)
				{
				////// Set Camera //////
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.x, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.y, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.z);
				glMultMatrixf(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);

				glColor4f(1.0f, 1.0f, 1.0f, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha);

				for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
					
					// set the material diffuse color
					Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
					
					// set the material specular color
					Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
					
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

						//glActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
					//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}
				}

			glDisable(GL_BLEND);
			}
		}

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

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

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    //glDisable(GL_DEPTH_TEST);
	//glDisable(GL_VERTEX_PROGRAM_ARB);
}

void unRenderer::draw_material_terrain_old(bool relief)
{
#if 0
//~~// Original Relief Material Draw //~~//
#if 0
int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
m->array_lock(va,vb);

int i,j=mesh->nfacemat,k;
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
#endif

//~~// ~~ //~~//
//~~// ~~ //~~//

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();

#if 0
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
#else
	bind_normal();

	pMaterial *mat=&_->mesh->mat[_->mesh->face[50].material];
	
	set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
#endif

	int i_iterator;
	int i_layer;
	int i_instance;
	int i_index;

#if 0
	for(i_iterator = 0; i_iterator < QActiveFrameWork->i_TrrBank->m_TerrainCell.size(); i_iterator++)
#else
	for(i_iterator = 0; i_iterator < TCELL_RENDER_MAX; i_iterator++)
#endif
		{
		i_index = QActiveFrameWork->i_TrrBank->m_CellRender[i_iterator];

		for(i_layer = 0; i_layer < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer.size(); i_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
	
#if 0
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)Media->QAEFF07A);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/

#if 0
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
#endif
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
	
#if 0
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)Media->QAEFF07A);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

	//unbind_terrain_vertex();
	////*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

	//unbind_normal();
	//bind_mesh_relief();

	unbind_normal();
	bind_relief();

	mat=&_->mesh->mat[_->mesh->face[50].material];
	
	set_relief_params(mat->diffuse,mat->specular,1,1,mat->texid,mat->texnormalid);

#if 0
	for(i_iterator = 0; i_iterator < QActiveFrameWork->i_TrrBank->m_TerrainCell.size(); i_iterator++)
#else
	for(i_iterator = 0; i_iterator < TCELL_RENDER_MAX; i_iterator++)
#endif
		{
		i_index = QActiveFrameWork->i_TrrBank->m_CellRender[i_iterator];

		for(i_layer = 0; i_layer < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer.size(); i_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
	
#if 0
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				//glBindTexture(GL_TEXTURE_2D, (GLuint)mesh->mat[0]->texid);
				glBindTexture(GL_TEXTURE_2D, (GLuint)Media->QAEFF07A);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(i_instance = 0; i_instance < QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance.size(); i_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->x, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->y, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->m_Instance[i_instance]->z);
	
#if 0
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
				//glMultMatrixf(playerAV->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)Media->hudRadarA);

				glDrawElements(GL_TRIANGLES, QActiveFrameWork->i_TrrBank->m_TerrainCell[i_index]->veclayer[i_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
						CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

						CalMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

#if 0
	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

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

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);

#endif
}

void unRenderer::draw_material_shapes(bool relief)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	//static GLfloat lightPosition[] = {0.2, 1.0, 0.3, 1.0};
	//static GLfloat lightColor[] = {0.8, 1.0, 0.8, 1.0}; /* green-tinted */

	//glEnable(GL_LIGHTING);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	//glEnable(GL_LIGHT0);

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glMultMatrixf(playerAV->Xform.Matrix.mf);

	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,(GLuint)1);

#if 0
	//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
	//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
	//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
	//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

	pVector eyepos;
	eyepos.x = g_render->camera.pos.x;
	eyepos.y = g_render->camera.pos.y;
	eyepos.z = g_render->camera.pos.z;

	//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
	//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

	//glDrawElements(GL_TRIANGLES, i_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

	//glTranslatef(playerAV->Xform.Translation.x + 15, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	//glMultMatrixf(playerAV->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, i_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

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

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
}

void unRenderer::draw_material_shape_instances(bool relief)
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	int i_iterator;
	int i_instance;
	for(i_iterator = 0; i_iterator < i_ShapeBank->m_Shape.size(); i_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, i_ShapeBank->m_Shape[i_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(i_instance = 0; i_instance < i_ShapeBank->m_Shape[i_iterator]->m_Instance.size(); i_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
			glTranslatef(i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->x, i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->y, i_ShapeBank->m_Shape[i_iterator]->m_Instance[i_instance]->z);
			//glMultMatrixf(playerAV->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, i_ShapeBank->m_Shape[i_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
					CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

					CalMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}*/
			}
		}

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		//glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			CalQuaternion rotationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());
			CalVector translationBoneSpace = playerAV->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV->Avatar.Mesh->m_calModel->getSkeleton());

			CalMatrix rotationMatrix = rotationBoneSpace;

			float transformation[12];

			transformation[0]=rotationMatrix.dxdx;transformation[1]=rotationMatrix.dxdy;transformation[2]=rotationMatrix.dxdz;transformation[3]=translationBoneSpace.x;
			transformation[4]=rotationMatrix.dydx;transformation[5]=rotationMatrix.dydy;transformation[6]=rotationMatrix.dydz;transformation[7]=translationBoneSpace.y;
			transformation[8]=rotationMatrix.dzdx;transformation[9]=rotationMatrix.dzdy;transformation[10]=rotationMatrix.dzdz;transformation[11]=translationBoneSpace.z;

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

		if(sizeof(CalIndex)==2) glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((CalIndex *)NULL)+ playerAV->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
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

		float Px1=(r*l.x + d)/(l2.x+l2.z);
		float Px2=(r*l.x - d)/(l2.x+l2.z);

		float nz1=(r-Px1*l.x)/l.z;
		float nz2=(r-Px2*l.x)/l.z;

		float e=1.25f;
		float a=g_render->aspect;

		float pz1=(l2.x+l2.z-r2)/(l.z-(nz1/Px1)*l.x);
		float pz2=(l2.x+l2.z-r2)/(l.z-(nz2/Px2)*l.x);

		if (pz1<0)
		{
			float fx=nz1*e1/Px1;
			int ix=(int)((fx+1.0f)*sx*0.5f);

			float px=-pz1*nz1/Px1;
			if (px<l.x)
				rect[0]=max(rect[0],ix);
			else
				rect[2]=min(rect[2],ix);
		}

		if (pz2<0)
		{
			float fx=nz2*e1/Px2;
			int ix=(int)((fx+1.0f)*sx*0.5f);

			float px=-pz2*nz2/Px2;
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

void unRenderer::draw_lights(pMesh *m,bool scissor, int f_AOGI, int f_whiteout, int f_FAAB_Camera)
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
		if(m->light[i].m_Live)
			{
			/*for( p=0;p<5;p++ )
			{
				float d=VECDOT(m->light[i].pos,g_render->view.planes[p])-g_render->view.planes[p].w;
				if (d<-m->light[i].pos.w)
					break;
			}
			if (p<5)
				continue;*/

			lightpos=m->light[i].pos*g_render->view_matrix;
			lightpos.w=m->light[i].pos.w;
			n=set_light_scissor(lightpos,m_sizex,m_sizey);

			glColor4f(1,1,1,0.075);

			n = 1;
			if (n>0 && scissor==false)
				{
				n=m_sizex*m_sizey;
				glDisable(GL_SCISSOR_TEST);
				}

			n = 1;

			if (n)
				{
				set_light_params(lightpos,m->light[i].color);

				draw_rect(0,0,m_sizex,m_sizey,true,false);

				m_num_lights_drawn++;
				m_percent_pixel_drawn+=n;
				}
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
	int bloom_sx=m_sizex/UNREND_BLOOM_SCALE;
	int bloom_sy=m_sizey/UNREND_BLOOM_SCALE;

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

	if(KEY_DOWN(QIN_F9))
		{
		//#### Initialise One Particle ####//
		Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
		Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
		Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.15;		//0.025f//0.002f
		Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 2;

		Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
		Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x = playerAV->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y = playerAV->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z = playerAV->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.x = playerAV->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.y = playerAV->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.z = playerAV->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5)*3;

		Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

		_->NomPntSprite++;
		if(_->NomPntSprite > 499) _->NomPntSprite = 0;

		Q.WriteNEWCharacterDataV2(&player->BFO);
		}

	if(KEY_DOWN(QIN_F11))
		{
		jet = 0;
		while(jet < 25)
			{
			//# Effect Type
			Q_HHSpike->HHSpike[_->NomSpikes].EffectType = 0;

			//## Speed
			Q_HHSpike->HHSpike[_->NomSpikes].Speed = 15;

			//### Width
			Q_HHSpike->HHSpike[_->NomSpikes].Width = 1;

			//#### Gravity
			Q_HHSpike->HHSpike[_->NomSpikes].Gravity = 0;

			//##### Alpha Level
			Q_HHSpike->HHSpike[_->NomSpikes].AlpFade = 0;
			Q_HHSpike->HHSpike[_->NomSpikes].FadeDir = 0;

			//###### Center Position
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV->Xform.Translation;
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos.y += 53;
			Q_HHSpike->HHSpike[_->NomSpikes].FrontPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;
			Q_HHSpike->HHSpike[_->NomSpikes].TailPos = Q_HHSpike->HHSpike[_->NomSpikes].CenterPos;

			//####### Create Trajectory Vector From Random Numbers
			Q_HHSpike->HHSpike[_->NomSpikes].TraVec.x = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].TraVec.y = (((float)rand() / 32767)-0.5)*2;
			Q_HHSpike->HHSpike[_->NomSpikes].TraVec.z = (((float)rand() / 32767)-0.5)*2;

			//######## Set Timers
			Q_HHSpike->HHSpike[_->NomSpikes].Timer = 0;
			Q_HHSpike->HHSpike[_->NomSpikes].MoveTail = 0;

			//######### Make Live
			Q_HHSpike->HHSpike[_->NomSpikes].Live = 1;

			_->NomSpikes++;
			if(_->NomSpikes > 99) _->NomSpikes = 0;

			jet++;
			}
		}

	float steering = 0;
	float acceleration = 0;
	bool handbrake = false;
	bool i_press = false;

	if(KEY_DOWN(QIN_KP4))
		{
		steering = -1;
		i_press = true;
		}

	if(KEY_DOWN(QIN_KP6))
		{
		steering = 1;
		i_press = true;
		}

	if(KEY_DOWN(QIN_KP8))
		{
		acceleration = 1;
		i_press = true;
		}

	if(KEY_DOWN(QIN_KP5))
		{
		acceleration = -1;
		i_press = true;
		}

	if(i_press)
		{
		QActiveFrameWork->DigiMass->ControlVehicle(steering, acceleration, handbrake);
		}

#if 0	//Positioned for lighting
	if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
#endif

#if 0
	QActiveFrameWork->QFrame();

	if(KEY_DOWN(QIN_u)) unProcessor->acPrintName(0);
#endif

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

	//QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->acPxRender(0, false);
	//QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->acBuffer();

	//QpoTransform i_transform;
	//Qpo->Avatar_GetBoneTransform(playerAV->operator ->(), "BIP01 R HAND", &i_transform);

	//i_ShapeBank->m_Shape[0]->m_Instance[0]->x = i_transform.Translation.x;
	//i_ShapeBank->m_Shape[0]->m_Instance[0]->y = i_transform.Translation.y;
	//i_ShapeBank->m_Shape[0]->m_Instance[0]->z = i_transform.Translation.z;

#ifdef QAGEMODE_SURGERY
	playerAV->Avatar.Mesh->m_calModel->getMixer()->ClearAnim();
	//playerAV->Avatar.Mesh->BlendAnim(35, valuepose, 1);
	//playerAV->Avatar.Mesh->BlendAnimPhysics(35, valuepose, 1);

	if(valueswitch == 0)
		{
		valuepose += 0.0025;
		if(valuepose > 2.13)
			{
			valuepose = 2.13;
			valueswitch = 1;
			}
		}
	else
		{
		valuepose -= 0.0025;
		if(valuepose < 0)
			{
			valuepose = 0;
			valueswitch = 0;
			}
		}
#endif

#if 0
	Qpo->Camera_SetPlayer();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	Qpo->Player_RenderBoundingBoxes();
#endif

#if 0
	if(KEY_DOWN(QIN_g)) QActiveFrameWork->i_TrrBank->acAddInstance(0, playerAV->Xform.Translation.x + ((((float)rand() / 32767) * 300)-150), playerAV->Xform.Translation.y + ((((float)rand() / 32767) * 300)-150), playerAV->Xform.Translation.z + ((((float)rand() / 32767) * 300)-150));
#endif

	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress[1])
			{
			vecvarDpress[1] = true;

			QpoVec3d i_playerin;
			Qpo->Transform_GetRight(&player->Camrot,&i_playerin);
			PxVec3 i_force(i_playerin.x * -35, i_playerin.y * -35, i_playerin.z * -35);
			QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y + 60, playerAV->Xform.Translation.z), 5, &i_force);
			//QActiveFrameWork->DigiMass->acCreateCubeV2(PxVec3(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y + 60, playerAV->Xform.Translation.z), 10, &i_force);
			}
		}
	else vecvarDpress[1] = false;

	if(KEY_DOWN(QIN_h))
		{
		if(!vecvarDpress[2])
			{
			vecvarDpress[2] = true;
#if 1
			QpoVec3d i_playerin;
			Qpo->Transform_GetRight(&player->Camrot,&i_playerin);
			PxVec3 i_force(i_playerin.x * -35, i_playerin.y * -35, i_playerin.z * -35);
#if 0
			QActiveFrameWork->DigiMass->acCreateSphere(PxVec3(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y + 60, playerAV->Xform.Translation.z), 5.0f, 1.0f);
#endif
			//QActiveFrameWork->DigiMass->acCreateCubeV3(PxVec3(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y + 60, playerAV->Xform.Translation.z), 10, &i_force);
			QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y + 105, playerAV->Xform.Translation.z), 17, &i_force);
#endif

#if 0
			playerAV->Avatar.Mesh->m_calModel->getMixer()->ClearAnim();

			// get the skeleton we need to update
			CalSkeleton *pSkeleton;
			pSkeleton = playerAV->Avatar.Mesh->m_calModel->getSkeleton();

			// clear the skeleton state
			//pSkeleton->clearState();

			// get the bone vector of the skeleton
			std::vector<CalBone *>& vectorBone = pSkeleton->getVectorBone();

			// lock the skeleton state
			//pSkeleton->lockState();

			//CalBone *pBone = vectorBone[8];

			playerAV->Avatar.Mesh->m_RagDoll = Digi::DigiMassCore::instance()->acSkeletonPose(playerAV->Avatar.Mesh->m_calModel->getSkeleton(), vectorBone);
			printf("Physics Ragdoll created %i\n", playerAV->Avatar.Mesh->m_RagDoll);

			// lock the skeleton state
			pSkeleton->lockState();

			// let the skeleton calculate its final state
			pSkeleton->calculateState();
#endif

			//Digi::DigiMassCore::instance()->CreateRagdoll();
			}
		}
	else vecvarDpress[2] = false;

	//###==-- Q-Network Tape Recording --==###//

	if(KEY_DOWN(QIN_F9))
		{
		Q.CreateAvatarItem(0, 1);
		}

	if(QNetwork.m_Recording) QNetwork.RecordWorld(1.0f);

	if(KEY_DOWN(QIN_F6))
		{
		if(!vecvarDpress[6] && vecrag < 2)
			{
			vecvarDpress[6] = true;

			if(QNetwork.m_Recording) QNetwork.FinalizeTapeBuffer();
			else
				{
				char casecntbuf[100];
				std::string strFilename;
				FILE* i_filecheck;
				bool fileSwit = true;

				while(fileSwit)
					{
					int random = rand()%55000;

					itoa(random, casecntbuf, 10);

					std::string strname = "Recording";
					std::string strnumber = casecntbuf;
					strFilename = strname + strnumber;

					FILE* i_filecheck = fopen(strFilename.c_str(), "rb");
					if(i_filecheck == 0) fileSwit = false;
					}
				fclose(i_filecheck);

				QNetwork.CreateTapeBuffer(strFilename.c_str());
				}
			}
		}
	else vecvarDpress[6] = false;

	if(KEY_DOWN(QIN_F7))	// Exper
		{
		if(!vecvarDpress[7])
			{
			vecvarDpress[7] = true;

			if(QNetwork.m_Playing)
				{
				QNetwork.CloseTapeBuffer();
				_->NetworkOption = 0;
				}
			else
				{
				//QNetwork.OpenTapeBuffer("Recording15830.txt");
				//QNetwork.OpenTapeBuffer("Recording19348.txt");
				//QNetwork.OpenTapeBuffer("Recording24251.txt");
				//QNetwork.OpenTapeBuffer("Recording26908.txt");
				//QNetwork.OpenTapeBuffer("Recording9002.txt");
				QNetwork.OpenTapeBuffer("Recording9034.txt");
				//QNetwork.OpenTapeBuffer("Recording7719.txt");
				_->NetworkOption = 1;
				}
			}
		}
	else vecvarDpress[7] = false;

#if 0
	draw_depth_shapes();
#endif

#if 0	//@#@
	draw_depth_shape_instances();
#endif

#if 1	//@#@
	draw_depth_terrain_old();
#endif

	

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_depth_avatars();
#else
	draw_depth_avatars();
#endif

	g_render->set_camera();

	//glTranslatef(0, -356, 0);
	//if(KEY_DOWN(QIN_0)) QActiveFrameWork->DigiMass->acSimulate();
	/*if(KEY_DOWN(QIN_9))*/ //QActiveFrameWork->DigiMass->acRender(true);
	//glTranslatef(0, 356, 0);

	//Item Positioning
	/*if(KEY_DOWN(QIN_KP5))
		{
		printf("_PositioningOffset x %f y %f z %f\n", _PositioningOffset.x, _PositioningOffset.y, _PositioningOffset.z);
		}

	if(KEY_DOWN(QIN_KP4))
		{
		_PositioningOffset.z -= 0.15;
		}

	if(KEY_DOWN(QIN_KP6))
		{
		_PositioningOffset.z += 0.15;
		}

	if(KEY_DOWN(QIN_KP8))
		{
		_PositioningOffset.y -= 0.15;
		}

	if(KEY_DOWN(QIN_KP2))
		{
		_PositioningOffset.y += 0.15;
		}

	if(KEY_DOWN(QIN_KP7))
		{
		_PositioningOffset.x += 0.15;
		}

	if(KEY_DOWN(QIN_KP1))
		{
		_PositioningOffset.x -= 0.15;
		}*/


#if 1
	draw_depth_meshes();
#endif

	g_render->set_camera();

#if 0	//Weapon Testing
	draw_depth(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0]);
#endif

	g_render->set_camera();

#if 0
	draw_depth(m);
#endif

	glColorMask(true,true,true,true);
	glDepthMask(false);

#if 0
	draw_material(m,relief);
#endif

#if 1
	draw_material_meshes();
#endif

	g_render->set_camera();

#if 0
	draw_material_mesh(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0], true);
#endif

#if 1	//@#@
	draw_material_terrain_old(relief);
#endif

	//glTranslatef(0, -356, 0);
	//QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->acRender(0, false);
	//QActiveFrameWork->DigiMass->acRender();
	//glTranslatef(0, 356, 0);

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_material_avatars(relief);
#else
	draw_material_avatars(relief);
#endif

// OLD POSITION

#if 0	//@#@
	draw_material_shape_instances(relief);
#endif

#if 0
	draw_material_shapes(relief);
#endif
	
	//QActiveFrameWork->i_TrrBank->m_TerrainCell[0]->acPxRender(0, false);

	//unProcessor->acPrintName(0);

#if 0
	Qpo->Player_RenderBoneBoundingBox("BIP01 R HAND");
	Qpo->Player_GetBoneBoxes("BIP01 R HAND", &pCorner, &DX, &DY, &DZ, &ColldetBox);

	Qpo->Transform_New_LeftUpIn(&player->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player->LimPosBox);

	player->LimPosBox.Matrix = playerAV->Xform.Matrix * player->LimPosBox.Matrix;
	coldetresult = playerAV->Xform.Matrix.multiply_rotation(pCorner);

	player->LimPosBox.Translation.x = coldetresult.x + playerAV->Xform.Translation.x;
	player->LimPosBox.Translation.y = coldetresult.y + playerAV->Xform.Translation.y;
	player->LimPosBox.Translation.z = coldetresult.z + playerAV->Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&Box, xScale, yScale, zScale, &player->LimPosBox);
	Qpo->Box_Render(Box);

	Qpo->Camera_Set();

	ColldetBox.Min = playerAV->Xform.Matrix.multiply_rotation(ColldetBox.Min);
	ColldetBox.Max = playerAV->Xform.Matrix.multiply_rotation(ColldetBox.Max);

	glColor3f(0.25f, 0.25f, 1.0f);
	glBegin(GL_LINES);

		glVertex3f(ColldetBox.Min.x + playerAV->Xform.Translation.x, ColldetBox.Min.y + playerAV->Xform.Translation.y, ColldetBox.Min.z + playerAV->Xform.Translation.z);
		glVertex3f(ColldetBox.Max.x + playerAV->Xform.Translation.x, ColldetBox.Max.y + playerAV->Xform.Translation.y, ColldetBox.Max.z + playerAV->Xform.Translation.z);

	glEnd();

	Qpo->Avatar_RenderBoneBoundingBox(0, "BIP01 HEAD");
	Qpo->Avatar_GetBoneBoundingBox(0, "BIP01 HEAD", &pCorner, &DX, &DY, &DZ);

	Qpo->Transform_New_LeftUpIn(&player->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player->LimPosBox);

	player->LimPosBox.Matrix = Q_Forge->Forge[0].AV.Xform.Matrix * player->LimPosBox.Matrix;
	coldetresult = Q_Forge->Forge[0].AV.Xform.Matrix.multiply_rotation(pCorner);

	player->LimPosBox.Translation.x = coldetresult.x + Q_Forge->Forge[0].AV.Xform.Translation.x;
	player->LimPosBox.Translation.y = coldetresult.y + Q_Forge->Forge[0].AV.Xform.Translation.y;
	player->LimPosBox.Translation.z = coldetresult.z + Q_Forge->Forge[0].AV.Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &player->LimPosBox);
	Qpo->Box_Render(_->KokBox);

	if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &Box)) printf("Trace Collision\n");
	else printf("Trace...\n");
#endif

#if 1
	if(KEY_DOWN(QIN_UP))
		{
		if(!KeyCheck)
			{
			if(TimeAlter) TimeAlter = false;
			else TimeAlter = true;
			}
		KeyCheck = true;
		}
	else KeyCheck = false;

	if(TimeAlter) _->TimeScale = 0.065;
#endif

#if 0
	Qpo->Camera_Set();

	glColor3f(1.0f, 1.0f, 0.25f);
	glBegin(GL_LINES);

		glVertex3f(0,-297,0);
		glVertex3f(500, -297, 0);

	glEnd();
#endif

#if 0
	Qpo->Camera_Set();
	Qpo->Player_RenderBoneBoundingBox("BIP01");
	Qpo->Player_RenderBoneBoundingBox("BIP01 PELVIS");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE1");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE2");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE3");
	Qpo->Player_RenderBoneBoundingBox("BIP01 NECK");
	Qpo->Player_RenderBoneBoundingBox("BIP01 HEAD");

	Qpo->Player_RenderBoneBoundingBox("BIP01 L CLAVICLE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L UPPERARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L FOREARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L HAND");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R CLAVICLE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R UPPERARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R FOREARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R HAND");

	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	Qpo->Player_RenderBoneBoundingBox("BIP01 L THIGH");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L CALF");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L FOOT");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R THIGH");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R CALF");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R FOOT");
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV->Xform,&playerAV->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glVertex3f(playerAV->Xform.Translation.x + (playerAV->Up.x * 250), playerAV->Xform.Translation.y + (playerAV->Up.y * 250), playerAV->Xform.Translation.z + (playerAV->Up.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV->Xform,&playerAV->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glVertex3f(playerAV->Xform.Translation.x + (playerAV->Up.x * 250), playerAV->Xform.Translation.y + (playerAV->Up.y * 250), playerAV->Xform.Translation.z + (playerAV->Up.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Transform_GetUp(&playerAV->Xform,&playerAV->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glVertex3f(playerAV->Xform.Translation.x + (playerAV->Up.x * 250), playerAV->Xform.Translation.y + (playerAV->Up.y * 250), playerAV->Xform.Translation.z + (playerAV->Up.z * 250));
	glEnd();
#endif

#if 0
	Qpo->Transform_GetIn(&playerAV->Xform,&playerAV->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glVertex3f(playerAV->Xform.Translation.x + (playerAV->Up.x * 250), playerAV->Xform.Translation.y + (playerAV->Up.y * 250), playerAV->Xform.Translation.z + (playerAV->Up.z * 250));
	glEnd();
#endif


#ifdef QAGEMODE_SURGERY
	playerAV->Xform.Translation = Origin;
#endif

	glLoadIdentity();

#ifdef QAGEMODE_SURGERY
	SurgeryFocus = m_PointLocator->getPos();
#endif

#if 0	// Trails Pose Reset
	playerAV->Avatar.Mesh->m_calModel->getMixer()->ClearAnim();
#endif

#if 0
	/////////////////////////////////////////////
	////// Render Player Cloth Attachments //////

	Qpo->Camera_Set();

	glDisable(GL_BLEND);

	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glColorMask(false,false,false,false);
	glDepthMask(true);

	for(SCRAM = 0; SCRAM < playerAV->Avatar.Mesh->m_ClothAttachment.size(); SCRAM++)
		{
		playerAV->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);

		glColorMask(true,true,true,true);
		glDepthMask(false);

		playerAV->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);
		}
#endif

	glEnable(GL_BLEND);

#if 1	// Positioned for after effects
	QActiveFrameWork->acWorldFrame();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV->Xform,&playerAV->Up);
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(playerAV->Xform.Translation.x, playerAV->Xform.Translation.y, playerAV->Xform.Translation.z);
	glVertex3f(playerAV->Xform.Translation.x + (playerAV->Up.x * 250), playerAV->Xform.Translation.y + (playerAV->Up.y * 250), playerAV->Xform.Translation.z + (playerAV->Up.z * 250));
	glVertex3f(0, 0, 0);
	glVertex3f(0, -250, 0);
	glEnd();
#endif

	//for(int test = 0; test < _->NomAI; test++) Q_Forge->Forge[test].AV.Xform.Translation = Origin;

	//*----Reset Positions / Heart Beat ~~~ single player and server only----*
	if(KEY_DOWN(QIN_k))
		{
		helly = 0;
		while(helly < _->NomAI)
			{
			if(Q_Forge->Forge[helly].LIVE == 1)
				{
				//Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].ORIGSTARTPOINT, &Q_Forge->Forge[helly].Xform.Translation);
				Qpo->Vec3d_Copy(&Origin, &Q_Forge->Forge[helly].AV.Xform.Translation);

				Q_Forge->Forge[helly].AirJinkRotFG = 0;
				Q_Forge->Forge[helly].ROTATEMatrix = Q_Forge->Forge[helly].STOREMatrix;
				Qpo->Vec3d_Copy(&Q_Forge->Forge[helly].Xform.Translation, &Q_Forge->Forge[helly].ROTATEMatrix.Translation);
				Q_Forge->Forge[helly].Xform = Q_Forge->Forge[helly].ROTATEMatrix;

				Q_Forge->Forge[helly].HB_Health = Q_Forge->Forge[helly].HB_MaxHealth;
				Q_Forge->Forge[helly].HB_Energy = Q_Forge->Forge[helly].HB_MaxEnergy;
				Q_Forge->Forge[helly].HB_Dead = 0;
				Q_Forge->Forge[helly].HB_RecoverMode = 0;

				aero=0;
				while(aero < _->NomAI)
					{
					Q_Forge->Forge[helly].AvatarDMGSTORE[aero] = 0;
					aero++;
					}
				}
			
			helly++;
			}

		aero=0;
		while(aero < _->NomAI)
			{
			player->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		player->HB_Health = player->HB_MaxHealth;
		player->HB_Energy = player->HB_MaxEnergy;
		player->HB_Dead = 0;
		}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();

	QActiveFrameWork->trrcursor->acRender();

#if 0
	QpoVec3d i_start;
	QpoVec3d i_end;

	i_start.x = playerAV->Xform.Translation.x;
	i_start.y = playerAV->Xform.Translation.x;
	i_start.z = playerAV->Xform.Translation.x;
	i_end.x = playerAV->Xform.Translation.x + (playerAV->Up.x * 250);
	i_end.y = playerAV->Xform.Translation.y + (playerAV->Up.y * 250);
	i_end.z = playerAV->Xform.Translation.z + (playerAV->Up.z * 250);

	Q.ShowLine(&i_start, &i_end, &player->ViewXForm.Translation, 5, Media->BulletCount, 255, 255, 255, 255, 0);
#endif

#ifdef QAGEMODE_SURGERY
	//playerAV->Avatar.Mesh->m_calModel->getMixer()->ClearAnim();
	//Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//Qpo->Player_RenderBoundingBoxes();
	//Player_RenderBoneBoundingBox("BIP01 L THIGH");

	Qpo->Camera_Set();

	glTranslatef(ClothLocator.x, ClothLocator.y, ClothLocator.z);
#endif

#if 0
	Qpo->Camera_Set();

	glDisable(GL_BLEND);

	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	glColorMask(false,false,false,false);
	glDepthMask(true);

	playerAV->Avatar.Mesh->m_ClothAttachment[0]->draw(true);

	glColorMask(true,true,true,true);
	glDepthMask(false);

#if 1	//HERE
	playerAV->Avatar.Mesh->m_ClothAttachment[0]->draw(true);
#endif

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
#endif

#if 0
	if(KEY_DOWN(QIN_UP)) playerAV->Avatar.Mesh->m_ClothAttachment[0]->getPxCloth()->addForceAtPos(PxVec3(0,-250,0), PxVec3(1,0,0), 500);
#endif

#ifdef QAGEMODE_SURGERY
	if(KEY_DOWN(QIN_1))
		{
		if(!vecvarDpress[8])
			{
			vecvarDpress[8] = true;

			if(rendswitchP) rendswitchP = false;
			else rendswitchP = true;
			}
		}
	else vecvarDpress[8] = false;

	if(physxswitchA) QActiveFrameWork->DigiMass->acSimulate();
	if(rendswitchP) QActiveFrameWork->DigiMass->acRenderScene(true);

	if(KEY_DOWN(QIN_2))
		{
		if(!vecvarDpress[9])
			{
			vecvarDpress[9] = true;

			if(rendswitchA) rendswitchA = false;
			else rendswitchA = true;
			}
		}
	else vecvarDpress[9] = false;

	if(KEY_DOWN(QIN_3))
		{
		if(!vecvarDpress[10])
			{
			vecvarDpress[10] = true;

			if(physxswitchA) physxswitchA = false;
			else physxswitchA = true;
			}
		}
	else vecvarDpress[10] = false;

	//if(KEY_DOWN(QIN_2))
		//{
		//QActiveFrameWork->DigiMass->incShapeRot(1, 0, 0, -0.1);
		///QActiveFrameWork->DigiMass->acRenderScene(true);
		//}
#endif

#ifdef QAGEMODE_SURGERY
	if(KEY_DOWN(QIN_MINUS))
		{
		if(m_keyPress == 0)
			{
			if(m_SurgeryMode == 0)
				{
#if 0
				m_PointLocator->setPos(0, 0, 0);
#endif
				m_SurgeryMode = 1;
				printf("Surgery Mode - Location Finder\n");
				}
			else
				{
				if(m_SurgeryMode == 1)
					{
					m_SurgeryMode = 2;
					printf("Surgery Mode - Cloth Locator\n");
					}
				else
					{
					m_SurgeryMode = 0;
					printf("Surgery Mode - Bone Placement\n");
					}
				}
			}
		m_keyPress = 1;
		}
	else m_keyPress = 0;

	if(m_SurgeryMode == 0)
		{
		if(KEY_DOWN(QIN_KP5))
			{
			if(!vecvarDpress[7])
				{
				vecvarDpress[7] = true;

				PxVec3 i_position = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
				printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
				}
			}
		else vecvarDpress[7] = false;

		if(KEY_DOWN(QIN_KP4))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.z -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP6))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.z += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP8))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.y -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP2))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.y += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP7))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.x += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP1))
			{
			i_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, i_BoneIter);
			i_LocalBonePosition.x -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, i_BoneIter, i_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", i_BoneIter, i_LocalBonePosition.x, i_LocalBonePosition.y, i_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP9))
			{
			if(!vecvarDpress[5])
				{
				vecvarDpress[5] = true;

				if(i_BoneIter < 14) i_BoneIter++;
				printf("i_BoneIter %i\n", i_BoneIter);
				}
			}
		else vecvarDpress[5] = false;

		if(KEY_DOWN(QIN_KP3))
			{
			if(!vecvarDpress[6])
				{
				vecvarDpress[6] = true;

				if(i_BoneIter > 0) i_BoneIter--;
				printf("i_BoneIter %i\n", i_BoneIter);
				}
			}
		else vecvarDpress[6] = false;
		}
	else
		{
		if(KEY_DOWN(QIN_KP4))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.x -= 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(-0.2, 0, 0));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(-0.1, 0, 0);
				m_PointLocator->acPrintLocation();
				}
			}

		if(KEY_DOWN(QIN_KP6))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.x += 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0.2, 0, 0));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(0.1, 0, 0);
				m_PointLocator->acPrintLocation();
				}
			}

		if(KEY_DOWN(QIN_KP8))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.y += 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0.2, 0));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(0, 0.1, 0);
				m_PointLocator->acPrintLocation();
				}
			}

		if(KEY_DOWN(QIN_KP2))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.y -= 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, -0.2, 0));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(0, -0.1, 0);
				m_PointLocator->acPrintLocation();
				}
			}

		if(KEY_DOWN(QIN_KP7))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.z += 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, 0.2));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(0, 0, 0.1);
				m_PointLocator->acPrintLocation();
				}
			}

		if(KEY_DOWN(QIN_KP1))
			{
			if(m_SurgeryMode == 2)
				{
				ClothLocator.z -= 0.2;
				playerAV->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, -0.2));
				printf("ClothLocator x %f y %f z %f\n", ClothLocator.x, ClothLocator.y, ClothLocator.z);
				}
			else
				{
				m_PointLocator->incPos(0, 0, -0.1);
				m_PointLocator->acPrintLocation();
				}
			}

		m_PointLocator->acRender();

		if(KEY_DOWN(QIN_8))
			{
			if(KEY_DOWN(QIN_1))
				{
				//QActiveFrameWork->DigiMass->incShapePos(-0.1, 0, 0);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}

			if(KEY_DOWN(QIN_2))
				{
				//QActiveFrameWork->DigiMass->incShapePos(0.1, 0, 0);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}

			if(KEY_DOWN(QIN_3))
				{
				//QActiveFrameWork->DigiMass->incShapePos(0, 0, -0.1);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}

			if(KEY_DOWN(QIN_4))
				{
				//QActiveFrameWork->DigiMass->incShapePos(0, 0, 0.1);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}

			if(KEY_DOWN(QIN_5))
				{
				//QActiveFrameWork->DigiMass->incShapePos(0, -0.1, 0);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}

			if(KEY_DOWN(QIN_6))
				{
				//QActiveFrameWork->DigiMass->incShapePos(0, 0.1, 0);
				QActiveFrameWork->DigiMass->acRenderScene(true);
				}
			}
		}
#else

	if(KEY_DOWN(QIN_1))
		{
		if(!vecvarDpress[8])
			{
			vecvarDpress[8] = true;

			if(rendswitchP) rendswitchP = false;
			else rendswitchP = true;
			}
		}
	else vecvarDpress[8] = false;

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glDisable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();

	//QActiveFrameWork->DigiMass->acSimulate();
	//QActiveFrameWork->DigiMass->acRenderBoxes();

	if(rendswitchP)//Px_BF_ENERGY_SLEEP_TEST
		{
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		g_render->set_camera();

		QActiveFrameWork->DigiMass->acRenderScene(true);
		}

	for(SCRAM = 0; SCRAM < m_VehicleCount; SCRAM++)
		{
		//vec_VehiclePos[SCRAM] = QActiveFrameWork->DigiMass->getVehiclePos(SCRAM);
		}

#if 0
	if(KEY_DOWN(QIN_2))
		{
		if(!vecvarDpress[9])
			{
			vecvarDpress[9] = true;

			if(rendswitchA) rendswitchA = false;
			else rendswitchA = true;
			}
		}
	else vecvarDpress[9] = false;
#endif
#endif

#if 0
	Qpo->Player_RenderBoneBoundingBox("BIP01");
	Qpo->Player_RenderBoneBoundingBox("BIP01 PELVIS");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE1");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE2");
	Qpo->Player_RenderBoneBoundingBox("BIP01 SPINE3");
	Qpo->Player_RenderBoneBoundingBox("BIP01 NECK");
	Qpo->Player_RenderBoneBoundingBox("BIP01 HEAD");

	Qpo->Player_RenderBoneBoundingBox("BIP01 L CLAVICLE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L UPPERARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L FOREARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L HAND");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R CLAVICLE");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R UPPERARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R FOREARM");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R HAND");

	Qpo->Player_RenderBoneBoundingBox("BIP01 L THIGH");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L CALF");
	Qpo->Player_RenderBoneBoundingBox("BIP01 L FOOT");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R THIGH");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R CALF");
	Qpo->Player_RenderBoneBoundingBox("BIP01 R FOOT");
#endif

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();

#if 0
	QActiveFrameWork->DigiMass->acSimulate();
	QActiveFrameWork->DigiMass->acRender();
#endif

#if 0
	QActiveFrameWork->DigiMass->acRenderScene(true);
#endif

	QActiveFrameWork->acNetFrame();

	//=== Render Position Locators ===//
	g_render->set_camera();

	//QpoVec3d i_pos = m_PointLocator->getPos();
	//if(i_pos.x != 0 && i_pos.y != 0 && i_pos.z != 0) m_PointLocator->acRender();

	//i_pos = QActiveFrameWork->trrcursor->getPos();
	//if(i_pos.x != 0 && i_pos.y != 0 && i_pos.z != 0) QActiveFrameWork->trrcursor->acRender();

	mrt_unbind_render();

	QActiveFrameWork->acGameEventsFrame();

#if 0
	if(KEY_DOWN(QIN_RBUTTON) && !KEY_DOWN(QIN_SHIFT) && !g_render->fullscreen)
		{
		if(!vecvarDpress[4])
			{
			vecvarDpress[4] = true;

			PxVec3 i_vecpoint;
			/*if(g_render->fullscreen) i_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x, temppos.y);
			else*/ i_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x - 8, temppos.y - 48);

			m_PointLocator->setPos(i_vecpoint.x, i_vecpoint.y, i_vecpoint.z);
			QActiveFrameWork->trrcursor->setPos(i_vecpoint.x, i_vecpoint.y, i_vecpoint.z);
			if(gPickStay) QActiveFrameWork->DigiMass->PickSetPosition(i_vecpoint);
			}
		}
	else vecvarDpress[4] = false;

	if(KEY_DOWN(QIN_MBUTTON))
		{
		QActiveFrameWork->DigiMass->PickActor(gMouseDepth, temppos.x - 8, temppos.y - 48);

		if(KEY_DOWN(QIN_RBUTTON))
			{
			if(!vecvarDpress[3])
				{
				vecvarDpress[3] = true;

				if(gPickStay) gPickStay = false;
				else gPickStay = true;
				}
			}
		else vecvarDpress[3] = false;
		}
	else
		{
		if(!gPickStay) QActiveFrameWork->DigiMass->PickRelease();
		}
#endif

#if 0
	if(KEY_DOWN(QIN_f))
		{
		gMouseDepth += 1;
		printf("Trace mouse depth %f\n", gMouseDepth);
		}

	if(KEY_DOWN(QIN_h))
		{
		gMouseDepth -= 1;
		printf("Trace mouse depth %f\n", gMouseDepth);
		}
#endif
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

	/////////////////////////
	///// RECORD FRAMES /////
	//glClearColor( 1, 0, 0, 0 );
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//#ifdef UNRENDER_FRAMEMEMORY
#if 0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_FrameMemory[m_Fcursor]);					// Bind To The Blur Texture
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, g_render->sizex, g_render->sizey, 0);
	m_Fcursor++;
	if(m_Fcursor >= UNREND_FRAMEMEMSIZE) m_Fcursor = 0;

	int i_cursor = m_Fcursor - UNREND_FRAMEMEMSIZE;
	if(i_cursor < 0) i_cursor = UNREND_FRAMEMEMSIZE + i_cursor;
	for(int mm = 0; mm < UNREND_FRAMEMEMSIZE; mm++)
		{
		glBindTexture(GL_TEXTURE_2D, m_FrameMemory[i_cursor]);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

		if(g_render->fullscreen)
			{
			glBegin(GL_QUADS);
				glTexCoord2f(0, 1);
				glVertex2i(0, 0);

				glTexCoord2f(0, 0);
				glVertex2i(0, g_render->sizey);

				glTexCoord2f(1, 0);
				glVertex2i(g_render->sizex, g_render->sizey);

				glTexCoord2f(1, 1);
				glVertex2i(g_render->sizex, 0);

				glTexCoord2f(0, 1);
				glVertex2i(0, 0);
			glEnd();
			}
		else
			{
			glBegin(GL_QUADS);
				glTexCoord2f(0,1);
				glVertex2i(0,0);

				glTexCoord2f(0, 0);
				glVertex2i(0, g_render->sizey);

				glTexCoord2f(1, 0);
				glVertex2i(g_render->sizex, g_render->sizey);

				glTexCoord2f(1, 1);
				glVertex2i(g_render->sizex, 0);

				glTexCoord2f(0, 1);
				glVertex2i(0, 0);
			glEnd();
			}

		i_cursor++;
		if(i_cursor >= UNREND_FRAMEMEMSIZE) i_cursor = 0;
		}
#endif

	QActiveFrameWork->m_GUI->acFrame();
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
			printf("CG:::General Execution Error");
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

GLuint unRenderer::CreateEmptyTexture(int i_x, int i_y)
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((i_x * i_y)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((i_x * i_y)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, i_x, i_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}