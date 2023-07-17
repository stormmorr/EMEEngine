/*

    unRenderer - Unification Renderer
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain the
	rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include <string>

#include "unRenderer.h"

#include "../../Texture/tgaload.h"
#include "../../Utility/unConsole.h"

#include "Q-NET-ProtoMap.h"

#if 0
#include "../../Process/unPatchBank.h"
#endif

#if 0
#define QAGE_OPMOD_B 1
#endif

#if 1
#define QAGE_OPMOD_SAFE 1
#endif

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

#define STRING(s) #s

//Temporary
float m_Xangle = 0;
float m_Yangle = 0;
float m_Zangle = 0;
float m_Wangle = 0;

using namespace GVARS;

#ifdef OSIRUS_CORE
using namespace OSI;
#endif

int vectrans[32];
int vecvar[5];
bool vecvarDpress[18];
float vecvalue[4];
float WeaponvalueX;
float WeaponvalueY;
float WeaponvalueZ;
float WeaponvalueW;
float WeaponvalueshtX;
float WeaponvalueshtY;
float WeaponvalueshtZ;
bool rendswitchP = false;
bool rendswitchA = false;
bool physxswitchA = false;

float valuepose = 0;
int valueswitch = 0;
int vecrag = 0;

/// Construction vars ///
float gMouseDepth = 150;
bool gPickStay = false;

unsigned int f_BoneIter = 0;

QunVector _PositioningOffset;

//std::vector<PxMat34Legacy> vec_VehiclePos;
int m_VehicleCount;

//###===- Angel Effects -===###//
float		angle;												// Used To Rotate The Helix
float		vertexes[4][3];										// Holds Float Info For 4 Sets Of Vertices
float		normal[3];											// An Array To Store The Normal Data
GLuint		BlurTexture;										// An Unsigned Int To Store The Texture Number

/////-Heaven-/////
#if 1
std::string meshfilehe("\\data\\Heaven.P3D");	// geometry file	
#endif

#if 1 //Original Main
std::string meshfile1("\\data\\Gas_FactoryBU2.P3D");	// geometry file
#endif

#if 1 //p3dscene3
std::string meshfile2("\\data\\Faction_Meat.P3D");	// geometry file
#endif

#if 1 //Heknoblock
std::string meshfile3("\\data\\Gas_Factory.P3D");	// geometry file
#endif

#if 1 //Faction_Meat
std::string meshfile4("\\data\\Heknoblock.P3D");	// geometry file
#endif

#if 1 //Play_Pen		//p3dscene3
std::string meshfile5("\\data\\p3dscene3main.P3D");	// geometry file
#endif

#if 1 //Gas_Factory
std::string meshfile6("\\data\\p3dscene3main.P3D");	// geometry file
#endif

pMesh* m_TestModel;
std::string m_Testmeshfile("\\data\\soap.p3d");

#if 0
#define CAL_ARB 1
#endif

#if 0
QSharedStruct<QAGE::QActiveFramewrk> QActiveFrameWork("GlobalQActiveFrameWork");

QSharedStruct<Digi::DigiMassCore> DigiMass("GlobalDigiMass");

QSharedStruct<UN::unMessageCore> UNMessageCore("GlobalunMessageCore");

QSharedStruct<trr::unTerrainCell> m_trrCell("GlobaltrrCell");
QSharedStruct<trr::unTrrBank> f_TrrBank("GlobalTrrBank");

QSharedStruct<UN::unShapeBank> f_ShapeBank("GlobalShapeBank");
QSharedStruct<UN::unShape> f_shape("Globalshape");

QSharedStruct<OSI::OsirusCore> f_OsirusCore("GlobalOsirus");
#endif

QAGE::QActiveFramewrk* QActiveFrameWork;

//Digi::DigiMassCore* DigiMass;

//trr::unTerrainCell* QActiveFrameWork->m_trrCell;
//trr::unTrrBank* QActiveFrameWork->f_TrrBank;

//UN::unMessageCore* UNMessageCore;

//*UN::unShapeBank* f_ShapeBank;
//*UN::unShape* f_shape;

#ifdef OSIRUS_CORE
CSpeechDlg *f_CSpeechDlg;

OSI::OsirusCore* f_OsirusCore;
#endif

float g_LightPos[40];
float g_LightColor[40];
float g_LightNom = 0.0f;

float g_LightonX = 500.0f;
float g_LightonY = 80.0f;
float g_LightonZ = 0.0f;

int g_LightonXDir = 1;
int g_LightonZDir = 0;

float g_LightonRadius = 2000.0f;

float g_LightonR = 0.80f;
float g_LightonG = 0.4f;
float g_LightonB = 0.3f;

void ag_Calc_Light(BiVector f_CalcPos)
{
	  /////////////////
	 // Q_Light
	//
	float f_LightDist[NOM_LIGHT];
	bool f_LightTest[NOM_LIGHT];
	bool f_LightSelect[NOM_LIGHT];
	int f_LightIndex[NOM_LIGHT];

	g_LightNom = 0.0f;

	for(int f_Helly = 0; f_Helly < 10; f_Helly++)
		{
		f_LightSelect[f_Helly] = false;
		f_LightTest[f_Helly] = true;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightPos[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		g_LightColor[f_Helly] = 0;
		}

	int f_Count = 0;
	int f_CountIndex = 0;
	for(int f_Point = 0; f_Point < Q_Nom_Light_Orig; f_Point++)
		{
		if((f_Count < Q_Nom_Light))
			{
			while((g_Light[f_Count].m_ON == false) || (g_Light[f_Count].m_Radius <= 0.0f))
				{
				f_Count++;
				}

			if(f_Count < NOM_LIGHT)
				{
				if(f_LightSelect[f_CountIndex] == false)
					{
					BiVector f_Pos(g_Light[f_Count].m_Pos.x, g_Light[f_Count].m_Pos.y, g_Light[f_Count].m_Pos.z);
					BiVector f_VecTo = f_Pos - f_CalcPos;

					float f_Dist = f_VecTo.acLength();
					f_LightDist[f_CountIndex] = f_Dist;
					f_LightIndex[f_CountIndex] = f_Count;
					f_LightTest[f_CountIndex] = true;
					f_LightSelect[f_CountIndex] = true;
					f_CountIndex++;
					}
				}
			}
		else
			{
			f_Point = Q_Nom_Light_Orig;
			}

		f_Count++;
		}

	int f_NewLightNom = f_CountIndex;

	for(int f_F = 0; f_F < 10; f_F++)
		{
		float f_Max = 10000.0f;
		int f_Shortest = 0;
		bool f_Any = false;
		for(int f_L = 0; f_L < f_NewLightNom; f_L++)
			{
			if(f_LightTest[f_L])
				{
				if(f_LightDist[f_L] < f_Max)
					{
					f_Max = f_LightDist[f_L];
					f_Shortest = f_L;
					f_Any = true;
					}
				}
			}

			//////////
			// Light
		//
		if(f_Any)
			{
			f_LightTest[f_Shortest] = false;
						
			g_LightPos[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Pos.x;
			g_LightPos[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Pos.y;
			g_LightPos[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Pos.z;
			g_LightPos[(f_F * 4) + 3] = g_Light[f_LightIndex[f_Shortest]].m_Radius;

			//g_Light[f_LightIndex[f_Shortest]].m_Radius -= 50.0f;

			g_LightColor[f_F * 4] = g_Light[f_LightIndex[f_Shortest]].m_Color.red / 255;
			g_LightColor[(f_F * 4) + 1] = g_Light[f_LightIndex[f_Shortest]].m_Color.green / 255;
			g_LightColor[(f_F * 4) + 2] = g_Light[f_LightIndex[f_Shortest]].m_Color.blue / 255;
			g_LightColor[(f_F * 4) + 3] = g_Light[f_LightIndex[f_Shortest]].m_Color.alpha * g_Light[f_LightIndex[f_Shortest]].m_Radius;
			g_LightNom += 1.0f;
			}
		else
			{
			g_LightPos[f_F * 4] = 0.0f;
			g_LightPos[(f_F * 4) + 1] = 0.0f;
			g_LightPos[(f_F * 4) + 2] = 0.0f;
			g_LightPos[(f_F * 4) + 3] = 0.0f;
			g_LightColor[f_F * 4] = 0.0f;
			g_LightColor[(f_F * 4) + 1] = 0.0f;
			g_LightColor[(f_F * 4) + 2] = 0.0f;
			g_LightColor[(f_F * 4) + 3] = 0.0f;
			}
		}
}

#if 0
unRenderer::unRenderer()
{
	/*m_vert_prog=0;
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
	m_rtdepth=0;

	m_frag_prog_light=0;
	m_lplanes=0;
	m_lpos=0;
	m_lcolor=0;

	m_frag_prog_blur=0;
	m_bdisp=0;

	m_frag_prog_antialias=0;
	m_apixelsize=0;
	m_aweight=0;*/

	//m_fb[0]=0;
	//m_fb[1]=0;
	//m_fb[2]=0;
	//m_fb[3]=0;
	m_fbtex[0]=0;
	m_fbtex[1]=0;
	m_fbtex[2]=0;
	m_fbtex[4]=0;

	//m_mrt=0;
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
	m_PatchBank = new Point::unPatchBank();
	m_PatchBank->acPush("Patch\\unPat00001_MidShift");

	for(;;) {}
#endif

#if 0
	_->SurgeryFocus.x = 0;
	_->SurgeryFocus.y = 0;
	_->SurgeryFocus.z = 0;
#endif

	//*f_GlobalAxisVector.x = 0;
	//*f_GlobalAxisVector.y = 0;
	//*f_GlobalAxisVector.z = 0;

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
	vecvarDpress[13] = false;
	vecvarDpress[14] = false;
	vecvarDpress[15] = false;

	WeaponvalueX = -0.14;
	WeaponvalueY = 10.05;
	WeaponvalueZ = 2.55;

	//WeaponvalueX = -7.050066;
	//WeaponvalueY = 10.05;
	//WeaponvalueZ = 2.55;
	WeaponvalueW = 0;
	WeaponvalueshtX = 0;
	WeaponvalueshtY = 0;
	WeaponvalueshtZ = 0;

	_PositioningOffset.x = 0;
	_PositioningOffset.y = 0;
	_PositioningOffset.z = 0;

	//m_mutex_Mesh = SDL_CreateMutex();

#if 0
	//###-- - Sense Vector - --###//
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueX += 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueX -= 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueY += 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueY -= 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueZ += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueZ -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}
#endif
}

unRenderer::~unRenderer()
{
	mrt_destroy();
	free_programs();
}

GLuint unRenderer::CompileShader(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if (compileResult == 0)
		{
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

#if 1
#if 1
		std::string f_ErrorString = to_string(errorMessage);
		printf("unRenderer::CompileShader:::%s", f_ErrorString.c_str());
#else
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
#if 1
		for(;;) {}
#endif
#endif
		}

    return shader;
}

GLuint unRenderer::CompileProgram(const std::string &vsSource, const std::string &fsSource)
{
    GLuint program = glCreateProgram();

    if (program == 0)
		{
#if 1
#if 1
		printf("unRenderer Program creation failed\n");
#else
        throw Exception::CreateException(E_FAIL, L"Program creation failed");
#endif
#if 1
		for (;;) {}
#endif
#endif
		}

    GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource);

    if (vs == 0 || fs == 0)
		{
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);
        return 0;
		}

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

#if 0
#if 1
		std::string f_ErrorString = to_string(errorMessage);
		printf("unRenderer::CompileProgram:::%s", f_ErrorString.c_str());
#else
        throw Exception::CreateException(E_FAIL, ref new Platform::String(errorMessage.c_str()));
#endif
#if 1
		for(;;) {}
#endif
#endif
		}

    return program;
}

void unRenderer::Shutdown(void)
{
	QActiveFrameWork->acShutdown();
}

void unRenderer::mrt_create(int sx,int sy)
{
	//gl_buffers[0]=GL_FRONT_LEFT;
	//gl_buffers[1]=GL_AUX0;
	//gl_buffers[2]=GL_AUX1;
	/*gl_buffers[3]=GL_AUX2;
	
    wgl_buffers[0]=WGL_FRONT_LEFT_ARB;
    wgl_buffers[1]=WGL_AUX0_ARB;
    wgl_buffers[2]=WGL_AUX1_ARB;
	wgl_buffers[3]=m_nv_render_depth_texture?WGL_DEPTH_COMPONENT_NV:WGL_AUX2_ARB;

	m_sizex=sx;
	m_sizey=sy;

	//m_mrt=new pPBuffer(sx,sy,32,false,true,false,true,true,false,false,true,m_nv_render_depth_texture?2:3);

	glGenTextures(4,m_mrttex);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);
	if (m_nv_render_depth_texture)
		glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,sx,sy,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,NULL);
	else
		glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

//	m_fb[0]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
//	m_fb[1]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glGenTextures(4,m_fbtex);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	sx/=UNREND_BLOOM_SCALE;
	sy/=UNREND_BLOOM_SCALE;
//	m_fb[2]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
//	m_fb[3]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[3]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
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
#endif*/
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

	for(int i = 0; i < UNREND_FRAMEMEMSIZE; i++)
		{
		m_FrameMemory[i] = 0;
		}
#endif

	//delete m_fb[0];
	//delete m_fb[1];
	//delete m_fb[2];
	//m_fb[0]=0;
	//m_fb[1]=0;
	//m_fb[2]=0;

	//delete m_mrt;
	//m_mrt=0;
}

void unRenderer::set_program_params(bool depth_bias,bool nv_render_depth_texture)
{
	m_depth_bias=depth_bias;
	//m_nv_render_depth_texture=(nv_render_depth_texture&&WGLEW_NV_render_depth_texture);
}

bool unRenderer::load_programs()
{
	const std::string vs = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 rotationMatrices[56];
		uniform vec4 avatarTrans;
		uniform vec4 cameraTrans;
		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;
		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		void main()
		{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			int matrix_x = int(aMatrixIndices.x);
			int matrix_y = int(aMatrixIndices.y);
			int matrix_z = int(aMatrixIndices.z);
			int matrix_w = int(aMatrixIndices.w);

			pos = (rotationMatrices[matrix_x] * tempPos) * aWeight.x;
			pos += (rotationMatrices[matrix_y] * tempPos) * aWeight.y;
			pos += (rotationMatrices[matrix_z] * tempPos) * aWeight.z;
			pos += (rotationMatrices[matrix_w] * tempPos) * aWeight.w;

			pos.xyz *= cameraTrans.w;

			mat3 m;

			m[0].xyz = rotationMatrices[matrix_x][0].xyz;
			m[1].xyz = rotationMatrices[matrix_x][1].xyz;
			m[2].xyz = rotationMatrices[matrix_x][2].xyz;

			normal += (m * tempNor) * aWeight.x;

			m[0].xyz = rotationMatrices[matrix_y][0].xyz;
			m[1].xyz = rotationMatrices[matrix_y][1].xyz;
			m[2].xyz = rotationMatrices[matrix_y][2].xyz;

			normal += (m * tempNor)* aWeight.y;

			vec4 f_interim = uModelMatrix * pos;

			f_interim.x += avatarTrans.x;
			f_interim.y += avatarTrans.y;
			f_interim.z += avatarTrans.z;

			vPosition = f_interim.xyz;

			gl_Position = uProjMatrix * uViewMatrix * f_interim;

			vNormal = normalize(normal);
			vec4 f_Norm = vec4(vNormal.xyz, 1.0);
			f_Norm = uModelMatrix * f_Norm;
			vNormal = f_Norm.xyz;
            vColor = vec4(1,1,1,1);
			vPos = cameraTrans.xyz;
        }
    );

    // Fragment Shader source
    const std::string fs = STRING
		(
		precision mediump float;

		float rand(vec3 co)
			{
			float f_result = fract(sin(dot(co, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
			return f_result;
			}

        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		uniform vec4 uTeam;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform float uLightNom;
		uniform float uSeed;
		uniform sampler2D f_texture;
        void main()
			{
			float f_SunLightNom = 0.0;
			float f_LightNom = 0.0;

			vec3 vnNormal = normalize(vNormal);

			vec4 f_Color = texture2D(f_texture, vTexCoord);
			vec4 f_AmbientColor = f_Color;
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			float f_qsX = rand(vec3(uSeed * vPosition.x * vPosition.y * vPosition.z));
			//float f_qsY = rand(vec3(f_qsX));
			//float f_qsZ = rand(vec3(f_qsY));

			vec4 randElement = vec4(f_qsX * 0.2, f_qsX * 0.2, f_qsX * 0.2, 1.0);

			vec3 f_SunLightPos = vec3(300.0, 30000.0, 1850.0);
			vec4 f_SunLightColor = vec4(0.93, 0.88, 0.80, 1.0);

			f_SunLightColor = (f_SunLightColor * 0.95) + (randElement * 0.05);

			float f_SunRadius = 100000.0;

			vec3 f_L = (f_SunLightPos + vPos) - vPosition;
			vec3 L = normalize(f_L);
			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(vnNormal, L), 0.0), 1.0);
			Idiff = clamp(Idiff, 0.0, 1.0);
			Idiff *= 0.03;

			float f_SunDistanceL = sqrt(dot(f_L, f_L));

			vec4 f_SunAccumulationBuffer = (Idiff * ((f_SunRadius) / f_SunDistanceL)) * 20.0;
			f_SunLightNom += 1.0;

			float f_ProcCount = 0.0;
			for(int f_i = 0; f_i < 10; f_i++)
				{
				if(f_ProcCount < uLightNom)
					{
					if(uLightPos[f_i].w > 0.0)
						{
						vec3 f_LightPos = uLightPos[f_i].xyz;

						vec3 f_Li = (f_LightPos + vPos) - vPosition;
						vec3 Li = normalize(f_Li);
						vec4 Idiffi = vec4(uLightColor[f_i].rgb * max(dot(vnNormal, Li), 0.0), 1.0);
						Idiffi = clamp(Idiffi, 0.0, 1.0);

						float f_LightDistance = 0.01;
						float f_Lengthi = sqrt(dot(f_Li, f_Li));

						float f_Diffi = uLightPos[f_i].w - (f_Lengthi / uLightColor[f_i].a);
						f_Diffi = f_Diffi * f_LightDistance;
						Idiffi = Idiffi * f_Diffi;

						f_AccumulationBuffer += Idiffi;

						float f_Intensity = 0.4;
						float f_IntenseInvert = (1.0 - f_Intensity) * 5.0;

						f_LightNom += 1.0 * f_IntenseInvert;
						}
					}

				f_ProcCount += 1.0;
				}

			vec4 f_Result = vec4(0.0, 0.0, 0.0, 0.0);
			float f_sunamp = 0.5;
			float f_amp = 0.5;

			f_Result.r += (f_SunAccumulationBuffer.r / (f_SunLightNom)) * f_sunamp;
			f_Result.g += (f_SunAccumulationBuffer.g / (f_SunLightNom)) * f_sunamp;
			f_Result.b += (f_SunAccumulationBuffer.b / (f_SunLightNom)) * f_sunamp;
			f_Result.a += (f_SunAccumulationBuffer.a / (f_SunLightNom)) * f_sunamp;


			if(f_LightNom >= 1.0)
				{
				f_Result.r += (f_AccumulationBuffer.r / (f_LightNom)) * f_amp;
				f_Result.g += (f_AccumulationBuffer.g / (f_LightNom)) * f_amp;
				f_Result.b += (f_AccumulationBuffer.b / (f_LightNom)) * f_amp;
				f_Result.a += (f_AccumulationBuffer.a / (f_LightNom)) * f_amp;
				}

			f_Result.a = 1.0;

			gl_FragColor = (f_AmbientColor * f_Result) + (uTeam / 3.0);
			gl_FragColor.a = 1.0;
			}
		);

	const std::string vs_mesh = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 avatarTrans;
		uniform vec4 cameraTrans;
		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;
		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		void main()
		{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			pos = aPosition;
			//pos.xyz *= cameraTrans.w;

			vec4 f_interim = uModelMatrix * pos;

			f_interim.x += avatarTrans.x;
			f_interim.y += avatarTrans.y;
			f_interim.z += avatarTrans.z;

			vPosition = f_interim.xyz;

			gl_Position = uProjMatrix * uViewMatrix * f_interim;

			vNormal = normalize(normal);
			vec4 f_Norm = vec4(vNormal.xyz, 1.0);
			f_Norm = uModelMatrix * f_Norm;
			vNormal = f_Norm.xyz;
            vColor = vec4(1,1,1,1);
			vPos = cameraTrans.xyz;
        }
    );

    // Fragment Shader source
    const std::string fs_mesh = STRING
		(
        precision mediump float;
        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		uniform vec4 uTeam;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform sampler2D f_texture;
        void main()
			{
			vec4 f_Color = texture2D(f_texture, vTexCoord);
			vec4 f_AmbientColor = f_Color * 0.4;
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			vec3 f_SunLightPos = vec3(-50.0, 700.0, 50.0);
			vec4 f_SunLightColor = vec4(0.83, 0.65, 0.33, 9.0);
			float f_SunRadius = 1025.0;
			float f_SunDistance = 0.001;

			vec3 f_L = (f_SunLightPos + vPos) - vPosition;
			vec3 L = normalize(f_L);
			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(vNormal, L), 0.0), 1.0);
			Idiff = clamp(Idiff, 0.0, 1.0);

			float f_Length = sqrt(dot(f_L, f_L));
			float f_Diff = f_SunRadius - (f_Length / f_SunLightColor.a);
			f_Diff = f_Diff * f_SunDistance;
			Idiff = Idiff * f_Diff;

			float f_LightNom = 0.0;

			if(f_Diff > 0.0)
				{
				f_AccumulationBuffer += Idiff;
				f_LightNom += 1.0;
				}

			for(int f_i = 0; f_i < 10; f_i++)
				{
				vec3 f_LightPos = uLightPos[f_i].xyz;
				vec3 f_Li = (f_LightPos - vPos) - vPosition;
				vec3 Li = normalize(f_Li);
				vec4 Idiffi = vec4(uLightColor[f_i].rgb * max(dot(vNormal, Li), 0.0), 1.0);
				Idiffi = clamp(Idiffi, 0.0, 1.0);

				float f_LightDistance = 0.01;
				float f_Lengthi = sqrt(dot(f_Li, f_Li));
				float f_Diffi = uLightPos[f_i].w - (f_Lengthi / uLightColor[f_i].a);
				f_Diffi = f_Diffi * f_LightDistance;
				Idiffi = Idiffi * f_Diffi;

				if(f_Diffi > 0.0)
					{
					f_AccumulationBuffer += Idiffi;
					f_LightNom += 1.0;
					}
				}

			vec4 f_Result = vec4(0.0, 0.0, 0.0, 0.0);
			f_Result.r = (f_AccumulationBuffer.r / (f_LightNom + 1.0));
			f_Result.g = (f_AccumulationBuffer.g / (f_LightNom + 1.0));
			f_Result.b = (f_AccumulationBuffer.b / (f_LightNom + 1.0));
			f_Result.a = (f_AccumulationBuffer.a / (f_LightNom + 1.0));
			gl_FragColor = ((f_AmbientColor * 0.75) + (f_Result * 2.8)) + uTeam;
			}
		);

	const std::string vsslot = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 rotationMatrices[56];
		uniform vec3 avatarTrans;
		uniform vec3 cameraTrans;
		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;
		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;
		void main()
		{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			int matrix_x = int(aMatrixIndices.x);
			int matrix_y = int(aMatrixIndices.y);
			int matrix_z = int(aMatrixIndices.z);
			int matrix_w = int(aMatrixIndices.w);

			pos = (rotationMatrices[matrix_x] * tempPos) * aWeight.x;
			pos += (rotationMatrices[matrix_y] * tempPos) * aWeight.y;
			pos += (rotationMatrices[matrix_z] * tempPos) * aWeight.z;
			pos += (rotationMatrices[matrix_w] * tempPos) * aWeight.w;
			
			pos.xyz *= cameraTrans.z;
			pos.y -= avatarTrans.y;

			mat3 m;

			m[0].xyz = rotationMatrices[matrix_x][0].xyz;
			m[1].xyz = rotationMatrices[matrix_x][1].xyz;
			m[2].xyz = rotationMatrices[matrix_x][2].xyz;

			normal += (m * tempNor) * aWeight.x;

			m[0].xyz = rotationMatrices[matrix_y][0].xyz;
			m[1].xyz = rotationMatrices[matrix_y][1].xyz;
			m[2].xyz = rotationMatrices[matrix_y][2].xyz;

			normal += (m * tempNor)* aWeight.y;

			vec4 f_interim = uModelMatrix * pos;
			f_interim.x += cameraTrans.x;

			gl_Position = uProjMatrix * uViewMatrix * f_interim;

			gl_Position.y += cameraTrans.y - 15.0;

			vNormal = normalize(normal);
			vec4 f_Norm = vec4(vNormal.xyz, 1.0);
			f_Norm = uModelMatrix * f_Norm;
			vNormal = f_Norm.xyz;
            vColor = vec4(1,1,1,1);
			vPosition = gl_Position.xyz;
        }
    );

	// Fragment Shader source
    const std::string fsslot = STRING
    (
        precision mediump float;
        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;
		uniform vec4 uTeam;
		uniform sampler2D f_texture;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
        void main()
        {
			vec4 f_Color = texture2D(f_texture, vTexCoord);
			vec4 f_AmbientColor = f_Color * 0.2;

			vec4 fLightPos = uLightPos[1];

			vec4 f_LightColor = uLightColor[1];

			vec3 L = normalize(fLightPos.xyz - vPosition);
			vec4 Idiff = f_LightColor * max(dot(vNormal, L), 0.0);
			Idiff = clamp(Idiff, 0.0, 1.0);

			gl_FragColor = f_AmbientColor + (f_Color * Idiff) + uTeam;
			gl_FragColor.a = 0.2;
			//gl_FragColor = vec4(vNormal, 0.3);
        }
    );

    // Set up the shader and its uniform/attribute locations.
    mProgram = CompileProgram(vs, fs);

    m0AttribLocation = glGetAttribLocation(mProgram, "aPosition");
    m1AttribLocation = glGetAttribLocation(mProgram, "aWeight");
	m2AttribLocation = glGetAttribLocation(mProgram, "aNormal");
	m3AttribLocation = glGetAttribLocation(mProgram, "aMatrixIndices");
	m4AttribLocation = glGetAttribLocation(mProgram, "aTexCoord");

    mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
    mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
    mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");

	mMatricesUniformLocation = glGetUniformLocation(mProgram, "rotationMatrices");
	mTextureUniformLocation = glGetUniformLocation(mProgram, "f_texture");

	mTeamUniformLocation = glGetUniformLocation(mProgram, "uTeam");

	mLightPosUniformLocation = glGetUniformLocation(mProgram, "uLightPos");
	mLightColorUniformLocation = glGetUniformLocation(mProgram, "uLightColor");

	mLightNomUniformLocation = glGetUniformLocation(mProgram, "uLightNom");

	mTimeUniformLocation = glGetUniformLocation(mProgram, "uSeed");

	mAvatarTranslationUniformLocation = glGetUniformLocation(mProgram, "avatarTrans");
	mCameraTranslationUniformLocation = glGetUniformLocation(mProgram, "cameraTrans");

#ifdef QAGE_SLOT
	// Set up the shader and its uniform/attribute locations.
    mProgramSlot = CompileProgram(vsslot, fsslot);

    m0AttribLocationSlot = glGetAttribLocation(mProgramSlot, "aPosition");
    m1AttribLocationSlot = glGetAttribLocation(mProgramSlot, "aWeight");
	m2AttribLocationSlot = glGetAttribLocation(mProgramSlot, "aNormal");
	m3AttribLocationSlot = glGetAttribLocation(mProgramSlot, "aMatrixIndices");
	m4AttribLocationSlot = glGetAttribLocation(mProgramSlot, "aTexCoord");

    mModelUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uModelMatrix");
    mViewUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uViewMatrix");
    mProjUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uProjMatrix");

	mMatricesUniformLocationSlot = glGetUniformLocation(mProgramSlot, "rotationMatrices");
	mTextureUniformLocationSlot = glGetUniformLocation(mProgramSlot, "f_texture");

	mTeamUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uTeam");

	mLightPosUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uLightPos");
	mLightColorUniformLocationSlot = glGetUniformLocation(mProgramSlot, "uLightColor");

	mAvatarTranslationUniformLocationSlot = glGetUniformLocation(mProgramSlot, "avatarTrans");
	mCameraTranslationUniformLocationSlot = glGetUniformLocation(mProgramSlot, "cameraTrans");
#endif

	const std::string elvs = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 uLightPos;
		attribute vec3 aPosition;
		attribute vec4 aColor;
		attribute vec2 aTexCoord;
		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;
		void main()
		{
			vec4 pos = vec4(aPosition, 1.0);

			vNormal = vec3(0.0, 0.0, -1.0);

			gl_Position = pos; // uProjMatrix * uViewMatrix * pos;
			//gl_Position.z = 0.0;
			vLightPos = uLightPos;
            vColor = aColor;
			//vPosition = gl_Position.xyz;
        }
    );

    // Fragment Shader source
    const std::string elfs = STRING
    (
        precision mediump float;
        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;
		uniform sampler2D f_texture;
        void main()
        {
			vec4 f_Color = texture2D(f_texture, vTexCoord);

			f_Color.r += vColor.r;
			f_Color.g += vColor.g;
			f_Color.b += vColor.b;
			f_Color.a += vColor.a;

			vec4 f_AmbientColor = f_Color * 0.4;

			vec4 fLightPos = vLightPos;

			vec4 f_LightColor = vec4(10.3, 17.7, 10.1, 1.0);

			vec3 L = normalize(fLightPos.xyz - vPosition);
			vec4 Idiff = f_LightColor * max(dot(vNormal, L), 0.0);
			Idiff = clamp(Idiff, 0.0, 1.0);

			gl_FragColor = f_AmbientColor + (f_Color * Idiff);
			gl_FragColor.a *= vColor.a;

			gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    );

#if 0
	g_ElementBank = new unElementBank();

    // Set up the shader and its uniform/attribute locations.
    g_ElementBank->mElProgram = CompileProgram(elvs, elfs);

	g_ElementBank->m0ElVertexAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aPosition");
	g_ElementBank->m1ElColorAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aColor");
	g_ElementBank->m2ElTexCoordAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aTexCoord");

	g_ElementBank->mElModelUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uModelMatrix");
	g_ElementBank->mElViewUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uViewMatrix");
	g_ElementBank->mElProjUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uProjMatrix");

	g_ElementBank->mElTextureUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "f_texture");
	g_ElementBank->mElLightPosUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uLightPos");
#endif

    // Then set up the cube geometry.
    GLfloat vertexPositions[] =
    {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
    };

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
    };

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#if 0
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

		m_frag_shadow = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"normal_mesh",
				(const char **)m_frag_options);

		checkError("normal_mesh", "cgCreateProgram");

		m_frag_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_terrain",
				(const char **)m_frag_options);

		checkError("mrt_normal_terrain", "cgCreateProgram");

		m_frag_alpha = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"alpha_avatar",
				(const char **)m_frag_options);

		checkError("alpha_avatar", "cgCreateProgram");

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

			//*cgGLLoadProgram(m_frag_shadow);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_terrain);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_alpha);
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
			m_terrainsampler=cgGetNamedParameter(m_vert_terrain,"PhysicsSamp");
			m_terrainwidth=cgGetNamedParameter(m_vert_terrain,"texwidth");

			m_meshcolormap=cgGetNamedParameter(m_frag_mesh,"colortex");
			m_meshAmbient=cgGetNamedParameter(m_frag_mesh,"f_Ambient");
			m_meshDiffuse=cgGetNamedParameter(m_frag_mesh,"f_Diffuse");
			m_meshSpecular=cgGetNamedParameter(m_frag_mesh,"f_Specular");
			m_meshLightVec=cgGetNamedParameter(m_frag_mesh,"f_LightVec");
			m_meshEyeVec=cgGetNamedParameter(m_frag_mesh,"f_EyeVec");
			m_meshAlpha=cgGetNamedParameter(m_frag_mesh,"f_Alpha");

			m_shadowcolormap=cgGetNamedParameter(m_frag_shadow,"colortex");
			m_shadowAmbient=cgGetNamedParameter(m_frag_shadow,"f_Ambient");
			m_shadowDiffuse=cgGetNamedParameter(m_frag_shadow,"f_Diffuse");
			m_shadowSpecular=cgGetNamedParameter(m_frag_shadow,"f_Specular");
			m_shadowLightVec=cgGetNamedParameter(m_frag_shadow,"f_LightVec");
			m_shadowEyeVec=cgGetNamedParameter(m_frag_shadow,"f_EyeVec");
			m_shadowAlpha=cgGetNamedParameter(m_frag_shadow,"f_Alpha");

			m_terraincolormap=cgGetNamedParameter(m_frag_terrain,"colortex");
			m_terrainAmbient=cgGetNamedParameter(m_frag_terrain,"f_Ambient");
			m_terrainDiffuse=cgGetNamedParameter(m_frag_terrain,"f_Diffuse");
			m_terrainSpecular=cgGetNamedParameter(m_frag_terrain,"f_Specular");
			m_terrainLightVec=cgGetNamedParameter(m_frag_terrain,"f_LightVec");
			m_terrainEyeVec=cgGetNamedParameter(m_frag_terrain,"f_EyeVec");
			m_terrainAlpha=cgGetNamedParameter(m_frag_terrain,"f_Alpha");

#if 0
			m_alphadepthmap=cgGetNamedParameter(m_frag_alpha,"depthtex");
			m_alphacolormap=cgGetNamedParameter(m_frag_alpha,"colortex");
#endif

			m_alphaAmbient=cgGetNamedParameter(m_frag_alpha,"f_Ambient");
			m_alphaDiffuse=cgGetNamedParameter(m_frag_alpha,"f_Diffuse");
			m_alphaSpecular=cgGetNamedParameter(m_frag_alpha,"f_Specular");
			m_alphaLightVec=cgGetNamedParameter(m_frag_alpha,"f_LightVec");
			m_alphaEyeVec=cgGetNamedParameter(m_frag_alpha,"f_EyeVec");
			m_alphaAlpha=cgGetNamedParameter(m_frag_alpha,"f_Alpha");
			m_alphaPlanes=cgGetNamedParameter(m_frag_alpha,"f_Planes");
			m_alphaView=cgGetNamedParameter(m_frag_alpha,"f_View");

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

			if(!m_shadowcolormap) printf("ERROR:::LoadPrograms m_shadowcolormap parameter not found\n");
			if(!m_shadowAmbient) printf("ERROR:::LoadPrograms m_shadowAmbient parameter not found\n");
			if(!m_shadowDiffuse) printf("ERROR:::LoadPrograms m_shadowDiffuse parameter not found\n");
			if(!m_shadowSpecular) printf("ERROR:::LoadPrograms m_shadowSpecular parameter not found\n");
			if(!m_shadowLightVec) printf("ERROR:::LoadPrograms m_shadowLightVec parameter not found\n");
			if(!m_shadowEyeVec) printf("ERROR:::LoadPrograms m_shadowEyeVec parameter not found\n");
			if(!m_shadowAlpha) printf("ERROR:::LoadPrograms m_shadowAlpha parameter not found\n");

			if(!m_terraincolormap) printf("ERROR:::LoadPrograms m_terraincolormap parameter not found\n");
			if(!m_terrainAmbient) printf("ERROR:::LoadPrograms m_terrainAmbient parameter not found\n");
			if(!m_terrainDiffuse) printf("ERROR:::LoadPrograms m_terrainDiffuse parameter not found\n");
			if(!m_terrainSpecular) printf("ERROR:::LoadPrograms m_terrainSpecular parameter not found\n");
			if(!m_terrainLightVec) printf("ERROR:::LoadPrograms m_terrainLightVec parameter not found\n");
			if(!m_terrainEyeVec) printf("ERROR:::LoadPrograms m_terrainEyeVec parameter not found\n");
			if(!m_terrainAlpha) printf("ERROR:::LoadPrograms m_terrainAlpha parameter not found\n");

			if(!m_alphadepthmap) printf("ERROR:::LoadPrograms m_alphadepthmap parameter not found\n");
			if(!m_alphacolormap) printf("ERROR:::LoadPrograms m_alphacolormap parameter not found\n");
			if(!m_alphaAmbient) printf("ERROR:::LoadPrograms m_alphaAmbient parameter not found\n");
			if(!m_alphaDiffuse) printf("ERROR:::LoadPrograms m_alphaDiffuse parameter not found\n");
			if(!m_alphaSpecular) printf("ERROR:::LoadPrograms m_alphaSpecular parameter not found\n");
			if(!m_alphaLightVec) printf("ERROR:::LoadPrograms m_alphaLightVec parameter not found\n");
			if(!m_alphaEyeVec) printf("ERROR:::LoadPrograms m_alphaEyeVec parameter not found\n");
			if(!m_alphaAlpha) printf("ERROR:::LoadPrograms m_alphaAlpha parameter not found\n");
			if(!m_alphaPlanes) printf("ERROR:::LoadPrograms m_alphaPlanes parameter not found\n");
			if(!m_alphaView) printf("ERROR:::LoadPrograms m_alphaView parameter not found\n");

			if(!m_terraintile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_terraindepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_terrainsampler) printf("ERROR:::LoadPrograms terrain sampler parameter not found\n");
			if(!m_terrainwidth) printf("ERROR:::LoadPrograms terrain physics texture width parameter not found\n");

			m_ndiffuse=cgGetNamedParameter(m_frag_prog_normal,"diffuse");
			m_nspecular=cgGetNamedParameter(m_frag_prog_normal,"specular");
			m_nplanes=cgGetNamedParameter(m_frag_prog_normal,"planes");
			m_rdiffuse=cgGetNamedParameter(m_frag_prog_relief,"diffuse");
			m_rspecular=cgGetNamedParameter(m_frag_prog_relief,"specular");
			m_rplanes=cgGetNamedParameter(m_frag_prog_relief,"planes");
			m_stepmap=cgGetNamedParameter(m_frag_prog_relief,"stepmap");
			m_rtdepth=cgGetNamedParameter(m_frag_prog_relief,"rtdepth");

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

	//AST-
	//////- SHADER AROUND ALOT -/////
	pString f_Shader_Around_Vertex_PATH;
	pString f_Shader_Around_Fragment_PATH;
	f_Shader_Around_Vertex_PATH.format("shaders\\Cg\\cg_ssao_vert.cg",
										(const char *)g_render->app_path,
										(const char *)g_render->shader_path);
	f_Shader_Around_Fragment_PATH.format("shaders\\Cg\\cg_around_agi_frag.cg",
										(const char *)g_render->app_path,
										(const char *)g_render->shader_path);
	char *f_Shader_Around_Vertex_ProgramText = LoadTextFile(f_Shader_Around_Vertex_PATH);
	char *f_Shader_Around_Fragment_ProgramText = LoadTextFile(f_Shader_Around_Fragment_PATH);

	if(f_Shader_Around_Vertex_ProgramText)
		{
		//aroundVertProfile = cgGetProfile("glslv");
		aroundVertProfile = CG_PROFILE_ARBVP1;
		//aroundVertProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
 
		// Validate Our Profile Determination Was Successful
		if (aroundVertProfile == CG_PROFILE_UNKNOWN)
			{
		//	MessageBox(NULL, "Invalid profile type ref vertex ssao", "Error", MB_OK);
			return FALSE;                               // We Cannot Continue
			}

		////*cgGLSetOptimalOptions(ssaoVertProfile);

		checkError("Get Profile", "selecting aroundVertProfile profile");

		m_vert_around_agi = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE, f_Shader_Around_Vertex_ProgramText,
				aroundVertProfile,
				"view_ssao",
				(const char **)m_vert_options);

		checkError("view_ssao", "cgCreateProgram");

		if(m_vert_around_agi)
			{
			//*cgGLLoadProgram(m_vert_around_agi);
			CgCheckError();
			}
		}

	count = 0;
	if(f_Shader_Around_Fragment_ProgramText)
		{
		//aroundFragProfile = cgGetProfile("glslf");
		aroundFragProfile = CG_PROFILE_ARBFP1;
		//aroundFragProfile = //*cgGLGetLatestProfile(CG_GL_FRAGMENT);
 
		// Validate Our Profile Determination Was Successful
		if(aroundFragProfile == CG_PROFILE_UNKNOWN)
			{
//			MessageBox(NULL, "Invalid profile type aroundFragProfile", "Error", MB_OK);
			return FALSE;                               // We Cannot Continue
			}

		//*cgGLSetOptimalOptions(aroundFragProfile);

		checkError("Get Profile", "selecting aroundFragProfile profile");

		m_frag_around_agi = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE, f_Shader_Around_Fragment_ProgramText,
				aroundFragProfile,
				"mrt_around_agi",
				(const char **)m_frag_options);

		checkError("m_frag_around_agi", "cgCreateProgram");

		if(m_frag_around_agi)
			{
			//*cgGLLoadProgram(m_frag_around_agi);
			CgCheckError();

			m_around_sampoints = cgGetNamedParameter(m_frag_around_agi, "points");
			m_around_white_out = cgGetNamedParameter(m_frag_around_agi, "whiteout");
			m_around_seedst = cgGetNamedParameter(m_frag_around_agi, "seedst");
			m_around_ScreenWidth = cgGetNamedParameter(m_frag_around_agi, "g_ScreenWidth");
			m_around_ScreenHeight = cgGetNamedParameter(m_frag_around_agi, "g_ScreenHeight");
			m_around_ScreenDepth = cgGetNamedParameter(m_frag_around_agi, "g_ScreenDepth");
			m_around_var_Final_Attenuation = cgGetNamedParameter(m_frag_around_agi, "var_Final_Attenuation");
			m_around_var_Radius123_Boost = cgGetNamedParameter(m_frag_around_agi, "var_Radius123_Boost");
			m_around_var_Cutoff_Threshold = cgGetNamedParameter(m_frag_around_agi, "var_Cutoff_Threshold");

			if(!m_around_sampoints) printf("ERROR:::LoadPrograms m_around_sampoints parameter not found\n");
			if(!m_around_white_out) printf("ERROR:::LoadPrograms m_around_white_out parameter not found\n");
			if(!m_around_seedst) printf("ERROR:::LoadPrograms m_around_seedst parameter not found\n");
			if(!m_around_ScreenWidth) printf("ERROR:::LoadPrograms m_around_ScreenWidth parameter not found\n");
			if(!m_around_ScreenHeight) printf("ERROR:::LoadPrograms m_around_ScreenHeight parameter not found\n");
			if(!m_around_ScreenDepth) printf("ERROR:::LoadPrograms m_around_ScreenDepth parameter not found\n");
			if(!m_around_var_Final_Attenuation) printf("ERROR:::LoadPrograms m_around_var_Final_Attenuation parameter not found\n");
			if(!m_around_var_Radius123_Boost) printf("ERROR:::LoadPrograms m_around_var_Radius123_Boost parameter not found\n");
			if(!m_around_var_Cutoff_Threshold) printf("ERROR:::LoadPrograms m_around_var_Cutoff_Threshold parameter not found\n");
			}
		}

	int tex;
	tex=g_render->build_onepixelmap(255,255,255);
	m_null_color=g_render->picid[tex];
	tex=g_render->build_onepixelmap(128,128,255);
	m_null_normal=g_render->picid[tex];
#endif
#if 0
	unConsoleReset();

	///// Reflective Shadow Mapping /////
#if 0
	m_RSM = new RSM();
#endif

	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk();

	//QActiveFrameWork.Acquire("GlobalQActiveFrameWork");
	//QActiveFrameWork = new QAGE::QActiveFramewrk();

	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	//DigiMass.Acquire("GlobalDigiMass");
	//DigiMass = new Digi::DigiMassCore();

	//*QActiveFrameWork->DigiMass = new DigiMassCore();
	//*QActiveFrameWork->DigiMass->Start();

	playerAV.Allocate("playerAV");//, Q_PlacementMarker->m_Count);

	QActiveFrameWork->acActiveInit();

	//for(int i = 0; i < 500; i++) Digi::CreateCube(PxVec3(((rand()%50)-25), ((rand()%50)-25), ((rand()%50)-25)),1);
	//for(int i = 0; i < 200; i++) DigiMass->acCreateCube(PxVec3(((rand()%500)-250), 125, ((rand()%500)-250)), 1);

#ifndef QAGE_OPMOD_B

	//f_CSpeechDlg = new CSpeechDlg();
	//f_CSpeechDlg->acInit();

	//f_OsirusCore = new OSI::OsirusCore();

#if 0
	f_OsirusCore->acTest();
#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

	//UNMessageCore->m_memorymanager->acLockModule("Unification.exe");

	//UNMessageCore->m_memorymanager->acSetPriority();

	// Test Engine Dynamic Shapes
	//f_ShapeBank.Acquire("GlobalShapeBank");

#if 0
	f_ShapeBank = new UN::unShapeBank();

#if 1
	f_ShapeBank->acCreateShape(UN_SHAPE_SPHERE, 50);
#endif
#endif

	//f_ShapeBank->acAddInstance(0, 0, 0, 0);

	//f_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
	//f_shape.Acquire("Globalshape");

#if 0
#if 1
	QActiveFrameWork->m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);

#if 0
	QActiveFrameWork->m_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");
#endif
	QActiveFrameWork->m_trrCell->acLoad(0, 0, 0, 0, 0, NULL);

#if 1
	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->m_trrCell, 12, false);
	QActiveFrameWork->f_TrrBank->acAddInstance(0, 0, 0, 0);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif
#endif

	QActiveFrameWork->DigiMass->incInternalState();
#endif

	//*QActiveFrameWork->DigiMass->acWait(DIGI_START);

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridTwo(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

#if 0
	QActiveFrameWork->DigiMass->acStartEngine();

	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[1]);
	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[2]);
	QActiveFrameWork->DigiMass->m_Engine.acCloseModels();

	QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
	QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
#endif

	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 12, false);

	//### Load Center Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridOne(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 13, false);

#if 0
	QActiveFrameWork->f_TrrBank->acAddInstance(1, 0, 0, 0);
#endif

	//### Load Empty Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridThree(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 14, false);

	//### Load Hut Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridFour(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 15, false);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(1, 0, 0, 0, 12);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif

#if 0
	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);
	float f_xslt;
	float f_zslt;
	int f_value = 5;
	int f_ins = 18;
	int f_counter = 1;

	/// ----- Rings in the Dirt ----- ///
	for(int f_count = 2; f_count < 7; f_count++)
		{
		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -(f_gridincrement * f_count);

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = f_gridincrement * f_count;

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = f_gridincrement * f_count;
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 10;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_value += 2;
		}
#endif

	//*QActiveFrameWork->DigiMass->incInternalState();

	//*QActiveFrameWork->DigiMass->m_Engine.acSetState(2, 3);


	////////====-- Set Shadow Effect Scales --====////////
								// 11
	player[g_Player]->ShadowEffect_Counter = 11;
								//  2.0
	player[g_Player]->ShadowEffect_Scale[0] = 2.0;
	player[g_Player]->ShadowEffect_Scale[1] = 1.9;
	player[g_Player]->ShadowEffect_Scale[2] = 1.8;
	player[g_Player]->ShadowEffect_Scale[3] = 1.7;
	player[g_Player]->ShadowEffect_Scale[4] = 1.6;
	player[g_Player]->ShadowEffect_Scale[5] = 1.5;
	player[g_Player]->ShadowEffect_Scale[6] = 1.4;
	player[g_Player]->ShadowEffect_Scale[7] = 1.3;
	player[g_Player]->ShadowEffect_Scale[8] = 1.2;
	player[g_Player]->ShadowEffect_Scale[9] = 1.1;
	player[g_Player]->ShadowEffect_Scale[10] = 1;

#if 0
#if 0
	m_TestModel = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]);
#else
	m_TestModel = g_render->load_mesh(meshfile);
#endif

	m_TestModel->nlight = 0;
#endif

	TCHAR szDirectory[255];
	if(!::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory))
		{
		printf("GetDirectoryERROR Cant find current directory\n");
		for(;;) {}
		}

	std::cout << "Current Directory ::: " << szDirectory << "'..." << std::endl;
	//TCHAR pstrDirName[PATH_STR] = "C:\Projects Base\Rapid3DRenderer";
	//SetCurrentDirectory(pstrDirName);

	// Set App Path
	//g_render->set_app_path(szDirectory);
	
	//_->mesh = g_render->load_mesh(meshfilehe, 8.0f);

	for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
		{
		_->mesh->cam[f_gap].pos.y += 705;
		}

#if 0
	_->mesh = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]);
#endif

	//_->mesh->nlight = 0;

#if 0
	terrainMaterial = &_->mesh->mat[_->mesh->face[5].material];
#endif

	//BlurTexture = EmptyTexture();
#endif

	return true;
}

void unRenderer::acInit(void)
{
	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk();

	//QActiveFrameWork.Acquire("GlobalQActiveFrameWork");
	//QActiveFrameWork = new QAGE::QActiveFramewrk();

	QNetwork.Initialize();

	mDrawCount = 0;
	mDrawCountDIR = 0;

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	//DigiMass.Acquire("GlobalDigiMass");
	//DigiMass = new Digi::DigiMassCore();

	//*QActiveFrameWork->DigiMass = new DigiMassCore();
	//*QActiveFrameWork->DigiMass->Start();

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	playerAV[g_Player].Allocate("playerAV");//, Q_PlacementMarker->m_Count);
	}

	g_Player = 0;

	QActiveFrameWork->acActiveInit();

	//for(int i = 0; i < 500; i++) Digi::CreateCube(PxVec3(((rand()%50)-25), ((rand()%50)-25), ((rand()%50)-25)),1);
	//for(int i = 0; i < 200; i++) DigiMass->acCreateCube(PxVec3(((rand()%500)-250), 125, ((rand()%500)-250)), 1);

#ifndef QAGE_OPMOD_B

	//f_CSpeechDlg = new CSpeechDlg();
	//f_CSpeechDlg->acInit();

	//f_OsirusCore = new OSI::OsirusCore();

#if 0
	f_OsirusCore->acTest();
#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

	//UNMessageCore->m_memorymanager->acLockModule("Unification.exe");

	//UNMessageCore->m_memorymanager->acSetPriority();

	// Test Engine Dynamic Shapes
	//f_ShapeBank.Acquire("GlobalShapeBank");

#if 0
	f_ShapeBank = new UN::unShapeBank();

#if 1
	f_ShapeBank->acCreateShape(UN_SHAPE_SPHERE, 50);
#endif
#endif

	//f_ShapeBank->acAddInstance(0, 0, 0, 0);

	//f_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
	//f_shape.Acquire("Globalshape");

#if 0
#if 1
	QActiveFrameWork->m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);

#if 0
	QActiveFrameWork->m_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");
#endif
	QActiveFrameWork->m_trrCell->acLoad(0, 0, 0, 0, 0, NULL);

#if 1
	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->m_trrCell, 12, false);
	QActiveFrameWork->f_TrrBank->acAddInstance(0, 0, 0, 0);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif
#endif

	QActiveFrameWork->DigiMass->incInternalState();
#endif

	//*QActiveFrameWork->DigiMass->acWait(DIGI_START);

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridTwo(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

#if 0
	QActiveFrameWork->DigiMass->acStartEngine();

	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[1]);
	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[2]);
	QActiveFrameWork->DigiMass->m_Engine.acCloseModels();

	QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
	QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
#endif

	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 12, false);

	//### Load Center Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridOne(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 13, false);

#if 0
	QActiveFrameWork->f_TrrBank->acAddInstance(1, 0, 0, 0);
#endif

	//### Load Empty Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridThree(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 14, false);

	//### Load Hut Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridFour(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 15, false);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(1, 0, 0, 0, 12);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif

#if 0
	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);
	float f_xslt;
	float f_zslt;
	int f_value = 5;
	int f_ins = 18;
	int f_counter = 1;

	/// ----- Rings in the Dirt ----- ///
	for(int f_count = 2; f_count < 7; f_count++)
		{
		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -(f_gridincrement * f_count);

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = f_gridincrement * f_count;

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = f_gridincrement * f_count;
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 10;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_value += 2;
		}
#endif

	//*QActiveFrameWork->DigiMass->incInternalState();

	//*QActiveFrameWork->DigiMass->m_Engine.acSetState(2, 3);


	////////====-- Set Shadow Effect Scales --====////////
								// 11
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
	{
	g_Player = f_CountPlayer;

	player[g_Player]->ShadowEffect_Counter = 11;
	//  2.0
	player[g_Player]->ShadowEffect_Scale[0] = 2.0;
	player[g_Player]->ShadowEffect_Scale[1] = 1.9;
	player[g_Player]->ShadowEffect_Scale[2] = 1.8;
	player[g_Player]->ShadowEffect_Scale[3] = 1.7;
	player[g_Player]->ShadowEffect_Scale[4] = 1.6;
	player[g_Player]->ShadowEffect_Scale[5] = 1.5;
	player[g_Player]->ShadowEffect_Scale[6] = 1.4;
	player[g_Player]->ShadowEffect_Scale[7] = 1.3;
	player[g_Player]->ShadowEffect_Scale[8] = 1.2;
	player[g_Player]->ShadowEffect_Scale[9] = 1.1;
	player[g_Player]->ShadowEffect_Scale[10] = 1;
	}

	g_Player = 0;

#if 0
#if 0
	m_TestModel = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]);
#else
	m_TestModel = g_render->load_mesh(meshfile);
#endif

	m_TestModel->nlight = 0;
#endif

#if 0
	TCHAR szDirectory[255];
	if(!::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory))
		{
		printf("GetDirectoryERROR Cant find current directory\n");
		for(;;) {}
		}

	std::cout << "Current Directory ::: " << szDirectory << "'..." << std::endl;
	//TCHAR pstrDirName[PATH_STR] = "C:\Projects Base\Rapid3DRenderer";
	//SetCurrentDirectory(pstrDirName);

	// Set App Path
	//g_render->set_app_path(szDirectory);
	
	//_->mesh = g_render->load_mesh(meshfilehe, 8.0f);
#endif

#if 0
	for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
		{
		_->mesh->cam[f_gap].pos.y += 705;
		}
#endif

#if 0
	_->mesh = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]);
#endif

	//_->mesh->nlight = 0;

#if 0
	terrainMaterial = &_->mesh->mat[_->mesh->face[5].material];
#endif

	//BlurTexture = EmptyTexture();
}

//Issue Start Command
void unRenderer::sync_PhysicsMemory(void)
{
	//*m_VehicleCount = QActiveFrameWork->DigiMass->getVehicleCount();

	//printf("trace m_VehicleCount %i\n", m_VehicleCount);

	printf("--//  User loaded...       //\n");
	printf("-//  Issue Start Command  //-\n");
	printf("// Start Command!        //--\n");

	g_LOAD = true;
}

void unRenderer::free_programs()
{
	/*if (m_vert_prog)
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
	m_frag_prog_antialias=0;*/
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

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,0);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_mesh_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_mesh_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

//AST-
void unRenderer::bind_around(void)
{
	//*cgGLBindProgram(m_frag_around_agi);
	//*cgGLEnableProfile(aroundFragProfile);

#if 0
	//*cgGLBindProgram(m_vert_around_agi);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);
#endif
}

void unRenderer::unbind_around(void)
{
#if 1
	//*cgGLDisableProfile(aroundFragProfile);
#endif

#if 0
	//*cgGLDisableProfile(aroundVertProfile);
#endif
}
//AST-

void unRenderer::set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_nspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_normal_params_static(const pVector& diffuse,const pVector& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);
	//*cgGLSetParameter1f(m_rtdepth,1);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_relief_params_terrain(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse, &diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular, &specular.x);
	//*cgGLSetParameter1f(m_terraintile, tile);
	//*cgGLSetParameter1f(m_terraindepth, depth);
	//*cgGLSetParameter1f(m_rtdepth, 1);

	//*cgGLSetParameter2f(m_rplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
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
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
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
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_light_params(const pVector& lightpos,const pVector& lightcolor)
{
	//*cgGLSetParameter4fv(m_lpos,&lightpos.x);
	//*cgGLSetParameter3fv(m_lcolor,&lightcolor.x);

	//*cgGLSetParameter2f(m_lplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));
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
			//*param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,(i-k)*fp,0);
		}
	}
	else
	{
		float fp=1.25/(m_sizey/UNREND_BLOOM_SCALE);
		for( i=0;i<j;i++ )
		{
			//*param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,0,(i-k)*fp);
		}
	}
}

void unRenderer::fb_bind_render(int buffer)
{
	//if (m_fb)
	//	m_fb[buffer]->Bind();
}

void unRenderer::fb_unbind_render(int buffer)
{
	//if (m_fb)
	//	m_fb[buffer]->Unbind();
}

void unRenderer::fb_bind_texture(int buffer,int texunit)
{
	//if (m_fb[buffer])
	//{
		//QDglActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
	//	m_fb[buffer]->BindAsTexture(WGL_FRONT_LEFT_ARB);
		glEnable(GL_TEXTURE_2D);
	//}
}

void unRenderer::fb_unbind_texture(int buffer,int texunit)
{
	//if (m_fb[buffer])
	//{
		//QDglActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
	//	m_fb[buffer]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
	//}
}

void unRenderer::mrt_bind_render()
{
	//if (m_mrt)
	//{
	//	m_mrt->Bind();
	//	glDrawBuffersATI(m_nv_render_depth_texture?3:4,gl_buffers);
	//}
}

void unRenderer::mrt_unbind_render()
{
	//if (m_mrt)
	//	m_mrt->Unbind();
}

void unRenderer::mrt_bind_texture(int target)
{
	//if (m_mrt)
	//{
		if (target>=0)
		{
	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[target]);
	//		m_mrt->BindAsTexture(wgl_buffers[target]);
			glEnable(GL_TEXTURE_2D);
		}
		else
		{
	//		//QDglActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);
	//		m_mrt->BindAsTexture(wgl_buffers[3]);

	//		//QDglActiveTextureARB(GL_TEXTURE2_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
	//		m_mrt->BindAsTexture(wgl_buffers[2]);

	//		//QDglActiveTextureARB(GL_TEXTURE1_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
	//		m_mrt->BindAsTexture(wgl_buffers[1]);

	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
	//		m_mrt->BindAsTexture(wgl_buffers[0]);
		}
	//}
}

void unRenderer::mrt_unbind_texture(int target)
{
	//if (m_mrt)
	//{
		if (target>=0)
		{
	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[target]);
			glBindTexture(GL_TEXTURE_2D,0);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
	//		//QDglActiveTextureARB(GL_TEXTURE3_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[3]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE2_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[2]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[1]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[0]);
			glBindTexture(GL_TEXTURE_2D,0);
		}
	//}
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
			/*gluUnProject(
				pixels[i][0],pixels[i][1],10,
				g_render->cam_model_mat,g_render->cam_proj_mat,
				viewport,&d[0],&d[1],&d[2]);*/
			f[i].vec((float)d[0],(float)d[1],(float)d[2]);
			f[i]-=g_render->camera.pos;
			f[i].normalize();
			f[i]=f[i]*view_rot;
		}

		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
	else
	if (flipy)
	{
		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
	else
	{
		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
}

void unRenderer::ViewOrtho(void)								// Set Up An Ortho View
{
	/*glMatrixMode(GL_PROJECTION);								// Select Projection
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();											// Reset The Matrix
	glOrtho( 0, 640 , 480 , 0, -1, 1 );							// Select Ortho Mode (640x480)
	glMatrixMode(GL_MODELVIEW);									// Select Modelview Matrix
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();											// Reset The Matrix*/
}

void unRenderer::ViewPerspective(void)							// Set Up A Perspective View
{
	//glMatrixMode( GL_PROJECTION );								// Select Projection
	//glPopMatrix();												// Pop The Matrix
	//glMatrixMode( GL_MODELVIEW );								// Select Modelview
	//glPopMatrix();												// Pop The Matrix
}

void unRenderer::RenderToTexture_Prep(void)          // Renders To A Texture
{
	//glColorMask(true,true,true,true);
	//glDepthMask(false);

	//mrt_unbind_texture(-1);
	//mrt_unbind_render();

	//glLoadIdentity();

    //glViewport(0, 0, 128, 128);                    // Set Our Viewport (Match Texture Size)
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
}

void unRenderer::RenderToTexture_Tex(void)          // Renders To A Texture
{
    // Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
    //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);

	// compute lighting
	//draw_lights(_->mesh,false);

	// draw antialias (blur edges)
	//if (1) draw_antialias();

	// compute bloom
	//if (1) draw_bloom();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask(false);

	fb_bind_texture(0,0);

	draw_rect(0, 0, g_render->sizex/4, g_render->sizey/4, false, true);

	glBindTexture(GL_TEXTURE_2D, BlurTexture);           // Bind To The Blur Texture

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, g_render->sizex/4, g_render->sizey/4, 0);

	fb_unbind_texture(0,0);
 
    //glClearColor(0.0f, 0.0f, 0.5f, 0.5);                // Set The Clear Color To Medium Blue
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And Depth Buffer
 
	//glViewport(0, 0, g_render->sizex, g_render->sizey);                 // Set Viewport (0,0 to 640x480)

	//glColorMask(false,false,false,false);
	//glDepthMask(true);

	//mrt_bind_texture(-1);
	//mrt_bind_render();
}

GLuint unRenderer::EmptyTexture(void)							// Create An Empty Texture
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((g_render->sizex * g_render->sizey)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((g_render->sizex * g_render->sizey)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, g_render->sizex, g_render->sizey, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}

void unRenderer::ClearBlur(void)					// Draw The Blurred Image
{
#if 0
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alpha = 0;											// Starting Alpha Value

	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
	glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Set Blending Mode
	glEnable(GL_BLEND);											// Enable Blending
	glBindTexture(GL_TEXTURE_2D, BlurTexture);					// Bind To The Blur Texture
	ViewOrtho();												// Switch To An Ortho View

	//*glBegin(GL_QUADS);											// Begin Drawing Quads
	glColor4f(0, 0, 0, alpha);					// Set The Alpha Value (Starts At 0.2)
	glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
	glVertex2f(0,0);									// First Vertex		(   0,   0 )

	glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
	glVertex2f(0,480);									// Second Vertex	(   0, 480 )

	glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
	glVertex2f(640,480);								// Third Vertex		( 640, 480 )

	glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
	glVertex2f(640,0);									// Fourth Vertex	( 640,   0 )
	//*glEnd();													// Done Drawing Quads

	ViewPerspective();											// Switch To A Perspective View

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
	glDisable(GL_BLEND);										// Disable Blending
	glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
#endif
}

void unRenderer::DrawBlur(int times, float inc)					// Draw The Blurred Image
{
#if 0
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alphainc = 0.9f / times;								// Fade Speed For Alpha Blending
	float alpha = 0.2f;											// Starting Alpha Value

	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
	glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Set Blending Mode
	glEnable(GL_BLEND);											// Enable Blending
	glBindTexture(GL_TEXTURE_2D, BlurTexture);					// Bind To The Blur Texture
	ViewOrtho();												// Switch To An Ortho View

	alphainc = alpha / times;									// alphainc=0.2f / Times To Render Blur

	//*glBegin(GL_QUADS);											// Begin Drawing Quads
	for (int num = 0; num < times; num++)						// Number Of Times To Render Blur
		{
		glColor4f(1.0f, 1.0f, 1.0f, alpha);					// Set The Alpha Value (Starts At 0.2)
		glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
		glVertex2f(0,0);									// First Vertex		(   0,   0 )

		glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
		glVertex2f(0,g_render->sizey);									// Second Vertex	(   0, 480 )

		glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
		glVertex2f(g_render->sizex,g_render->sizey);								// Third Vertex		( 640, 480 )

		glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
		glVertex2f(g_render->sizex,0);									// Fourth Vertex	( 640,   0 )

		spost += inc;										// Gradually Increase spost (Zooming Closer To Texture Center)
		alpha = alpha - alphainc;							// Gradually Decrease alpha (Gradually Fading Image Out)
		}
	//*glEnd();													// Done Drawing Quads

	ViewPerspective();											// Switch To A Perspective View

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
	glDisable(GL_BLEND);										// Disable Blending
	glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
#endif
}

void unRenderer::draw_depth(pMesh *m)
{
	int va=0,vb=1;

	//glScalef(1.9f,1.9f,1.9f);

	m->array_lock(va,vb);

	m->array_draw(vb);

	m->array_unlock();
}

void unRenderer::draw_depth_terrain(pMesh *m)
{
#if 0
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock_physics(va, vb, true);

	bind_terrain_vertex();

	//*cgGLSetParameter1f(m_terrainwidth, m->m_PhysicsTextureWidth);

	//*cgGLSetTextureParameter(m_terrainsampler, m->m_PhysicsTexture);
	//*cgGLEnableTextureParameter(m_terrainsampler);
	cgSetSamplerState(m_terrainsampler);

	glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

	unbind_vertex();

	m->array_unlock();
#endif
}

void unRenderer::draw_depth_meshes(void)
{
#if 0
	int va=0,vb=1;
	pVector PosTest;

	for(int i = 0; i < _->NomSEnergy; i++)
		{
		if(i > 0 && i < _->MaxNomSEnergy)
			{
			for(int k = 0; k < 5; k++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.z);
				glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

				glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);

				if(Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar < 2)
					{
					pMesh* f_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar]->m_submesh[0];
					f_mesh->array_lock(va,vb);

					f_mesh->array_draw(vb);

					f_mesh->array_unlock();
					}
				}
			}
		}

	for(unsigned int i = 0; i < _->MaxNomLEnergy; i++)
		{
		if(Q_LEnergy->LEnergy[i].EnergyBall.m_Alpha > 0)
			{
			for(unsigned int k = 0; k < 5; k++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.z);

				/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[0] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[1] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[2] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[3]= (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[4] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[5] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[6] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[7] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[8] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[9] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[10] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[11] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[12] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[13] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[14] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[15] = (((float)rand() / 32767)-0.5);*/

				Qpo->Transform_New_XRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);
				Qpo->Transform_New_YRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);
				Qpo->Transform_New_ZRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);

				glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

				//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
				glScalef(Q_LEnergy->LEnergy[i].EnergyBall.Scale.x, Q_LEnergy->LEnergy[i].EnergyBall.Scale.y, Q_LEnergy->LEnergy[i].EnergyBall.Scale.z);

				pMesh* f_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar]->m_submesh[0];
				f_mesh->array_lock(va,vb);

				f_mesh->array_draw(vb);

				f_mesh->array_unlock();
				}
			}
		}

	if(player[g_Player]->WeaponStatus > 1)
		{
		glLoadIdentity();

		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
		playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
		playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

		/*if(player[g_Player]->AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);
		else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV, true);

		//##### MiniGUN Rotation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
			Ange.y = -0.87; //WeaponvalueshtY;//PI;
			Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

			// Set the actor's angle
			Qpo->Transform_RotateY(&player[g_Player]->RFistPosV, Ange.y);
			Qpo->Transform_RotateX(&player[g_Player]->RFistPosV, Ange.x);
			Qpo->Transform_RotateZ(&player[g_Player]->RFistPosV, Ange.z);
			//#####
			}

		glTranslatef(player[g_Player]->RFistPosV.Translation.x, player[g_Player]->RFistPosV.Translation.y, player[g_Player]->RFistPosV.Translation.z);
		glMultMatrixf(player[g_Player]->RFistPosV.Matrix.mf);

		//##### MiniGUN Translation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			//glTranslatef(19.24, 71.057, 14.87);
			//glTranslatef(10.65, -83.68, 26.31);
			glTranslatef(10.98, -71.22, 22.12);
			//glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
			}
		else
			{
			glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
			}

		pMesh* f_mesh;
		for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_submesh.num; f_meshcnt++)
			{											 //player[g_Player]->Weapon.Avatar
			f_mesh = QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_submesh[f_meshcnt];

			f_mesh->array_lock(va,vb);

			f_mesh->array_draw(vb);

			f_mesh->array_unlock();
			}
		}

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].WeaponStatus > 1)
				{
				PosTest.x = Q_Forge->Forge[SCRAM].AV.Xform.Translation.x;
				PosTest.y = Q_Forge->Forge[SCRAM].AV.Xform.Translation.y;
				PosTest.z = Q_Forge->Forge[SCRAM].AV.Xform.Translation.z;

				if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[SCRAM].HB_DeadTimer > 0)
					{
					glLoadIdentity();

					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.x = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.y = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.z = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
						{
						Qpo->AvatarView_GetBoneTransform(&Q_Forge->Forge[SCRAM].AV, "BIP01 R HAND", &player[g_Player]->RFistPosV, false);

						Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
						Ange.y = -0.87; //WeaponvalueshtY;//PI;
						Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

						// Set the actor's angle
						Qpo->Transform_RotateY(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.y);
						Qpo->Transform_RotateX(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.x);
						Qpo->Transform_RotateZ(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.z);
						//#####
						}
					else Qpo->Avatar_GetBoneTransformMP(Q_Forge->Forge[SCRAM].AV, "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV);

					glTranslatef(Q_Forge->Forge[SCRAM].RFistPosV.Translation.x, Q_Forge->Forge[SCRAM].RFistPosV.Translation.y, Q_Forge->Forge[SCRAM].RFistPosV.Translation.z);
					glMultMatrixf(Q_Forge->Forge[SCRAM].RFistPosV.Matrix.mf);

					//##### MiniGUN Translation
					if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
						{
						//glTranslatef(19.24, 71.057, 14.87);
						//glTranslatef(10.65, -83.68, 26.31);
						glTranslatef(10.98, -71.22, 22.12);
						//glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
						}
					else
						{
						glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
						}

					pMesh* f_mesh;
					for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_submesh.num; f_meshcnt++)
						{
						f_mesh = QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_submesh[f_meshcnt];

						f_mesh->array_lock(va,vb);

						f_mesh->array_draw(vb);

						f_mesh->array_unlock();
						}
					}
				}
			}

		SCRAM++;
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int f_vehicleiter = 0; f_vehicleiter < m_VehicleCount; f_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[f_vehicleiter].getColumnMajor44(glMat);
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
			pMesh* f_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh[i];

			f_mesh->array_lock(va,vb);

			f_mesh->array_draw(vb);

			f_mesh->array_unlock();
			}
		}
#endif
#endif
}

void unRenderer::draw_depth_avatars(void)
{
#if 0
	//// DEBUG: CLOTH SIM
	static QunVector spherePosition;
	spherePosition.set(playerAV[g_Player]->Avatar.Mesh->Sphere.x, playerAV[g_Player]->Avatar.Mesh->Sphere.y, playerAV[g_Player]->Avatar.Mesh->Sphere.z);
	static float sphereRadius = 15.0f;

	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setSphere(spherePosition.x, spherePosition.y, spherePosition.z, sphereRadius);

	glColor3f(1.0f, 1.0f, 1.0f);
	//*glBegin(GL_LINE_STRIP);
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
	//*glEnd();
	//// DEBUG END
#endif

  //QunSkeleton *pQunSkeleton = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton();

  // Note :
  // You have to call coreSkeleton.calculateBoundingBoxes(calCoreModel)
  // during the initialisation (before qunModel.create(calCoreModel))
  // if you want to use bounding boxes.

#if 0
  playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->calculateBoundingBoxes();
#endif

	// Note:
	// Uncomment the next lines if you want to test the experimental collision system.
	// Also remember that you need to call calculateBoundingBoxes()

	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setForceVector(QunVector(0.0f,0.0f,0.0f));
	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setCollisionDetection(true);  
#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}*/

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

			//if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
			//{
			//printf("Treace no error\n");
			//}

			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	//////////////////////////////////////
	////// Render Player Shadows /////////

	///// Mesh Settings /////
	if(player[g_Player]->ShadowsOn)
		{
		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(&player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(&player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			for(hardwareMeshId=0;hardwareMeshId<player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}
			}
		}


	//////////////////////////////////////
	////// Render NON-Player Meshes //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		// Decrement on death timer
		if(Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].HB_Dead == 1) 
			{
			Q_Forge->Forge[i].HB_DeadTimer--;
			}

		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(Q_Forge->Forge[i].LIVE == 1 && g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0)
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
					QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

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

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			//////////////////////////////////////
			////// Render AI Shadows /////////////

			///// Mesh Settings /////
			if(Q_Forge->Forge[i].ShadowsOn && 0)
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
							QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

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

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	unbind_mesh_vertex();

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}*/

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

			//if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
			//{
			//printf("Treace no error\n");
			//}

			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}
#endif
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_avatars_shell(void)
{
	/*glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	//glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

	glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

	std::vector<QunBone *>& vectorBone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
		{
#if 0
		if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}
#endif

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
			{
			QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
			QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				/*transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

#if 0
			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
#endif

			/*transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
		else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
		}

	//////////////////////////////////////
	////// Render Player Shadows /////////

#if 0
	///// Mesh Settings /////
	if(player[g_Player]->ShadowsOn)
		{
		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(&player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(&player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			for(hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				}
			}
		}
#endif


	//////////////////////////////////////
	////// Render NON-Player Meshes //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		// Decrement on death timer
		if(Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].HB_Dead == 1)
			{
			Q_Forge->Forge[i].HB_DeadTimer--;
			}

		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].LIVE == 1)
			{
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);
			
			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

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

			Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

			glScalef(Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)),Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)));

			std::vector<QunBone *>& vectorBoneAI = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			int hardwareMeshId = 0;
			for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

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

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));

#if 0
				printf("glDrawElements %f", Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh);
#endif
				}

			//////////////////////////////////////
			////// Render AI Shadows /////////////

#if 0
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

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					int hardwareMeshId = 0;
					for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
						float transformation[500];

						int boneId;
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}
				}
#endif
			}
		}

	unbind_mesh_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);*/
}

void unRenderer::draw_depth_terrain_old(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_vertex();

	int f_iterator;
	int f_layer;
	int f_instance;
	int f_index;

	trr::unTerrainCell* f_Cell;

	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			///// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, f_Cell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, f_Cell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);
				}
			}
		}

	unbind_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif

#if 0	// Trace Instance Count
	printf("%i Instances\n", f_Cell[0]->m_Instance.size());
#endif
}

void unRenderer::draw_depth_shapes(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	//bind_terrain_vertex();
	bind_terrain_vertex();

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
	//glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

	//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_shape_instances(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

		for(f_instance = 0; f_instance < f_ShapeBank->m_Shape[f_iterator]->m_Instance.size(); f_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->x, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->y, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->z);
			//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[f_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}*/
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_shape_energy(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				//glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_material(pMesh *m,bool relief)
{
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock(va,vb);

	int i, j = m->nfacemat, k;
	pMaterial *mat;
	
	bind_vertex();

	bind_normal();

	//glScalef(1.9f,1.9f,1.9f);

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

	//bind_blur();

	//glScalef(1.9f,1.9f,1.9f);

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

	//unbind_relief();

	unbind_vertex();

	m->array_unlock();
}

void unRenderer::draw_material_terrain(pMesh *m, bool relief)
{
#if 0
	int va = P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT, vb = 1;
	m->array_lock_physics(va, vb, true);

	pMaterial *mat = &m->mat[0];

	bind_terrain_vertex();

	//*cgGLSetParameter1f(m_terrainwidth, m->m_PhysicsTextureWidth);

	//*cgGLSetTextureParameter(m_terrainsampler, m->m_PhysicsTexture);
	//*cgGLEnableTextureParameter(m_terrainsampler);
	cgSetSamplerState(m_terrainsampler);

	if(!relief)
		{
		bind_normal();

		set_normal_params(mat->diffuse, mat->specular, 5, mat->texid, mat->texnormalid);

		glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

		unbind_normal();
		}

	if(relief)
		{
		bind_relief();

		set_relief_params_terrain(mat->diffuse, mat->specular, 1, 5, mat->texid, mat->texnormalid);

		glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

		unbind_relief();
		}

	unbind_vertex();

	m->array_unlock();
#endif
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
#if 1
	int va=0,vb=1;
	bool relief = true;
	pVector PosTest;
	QpoVec3d Anf;

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	if(mProgram == 0)
		{
		printf("unRenderer:::draw_material_avatars slot mProgram is not loaded\n");
		for (;;) {}
		}

	glUseProgram(mProgram);

	pFrustum f_View;

	float cameraDistance = (((750.0f / g_Zoom) * (1 - g_ZoomFactor)) + 300.0f) * g_ArenaSize;

	float fov = 115.0f;
	float aspect = float(1280.0f) / float(1080.0f);
	float farplane = 10000.0f;
	pVector f_camX(1.0f, 0.0f, 0.0f);
	pVector f_camY(0.0f, 1.0f, 0.5f);
	pVector f_camZ(0.0f, -1.0f, 1.0f);

	pVector f_PlayerPos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	f_camX.normalize();
	f_camY.normalize();
	f_camZ.normalize();

	pVector f_CamPos = f_PlayerPos + (f_camZ * (cameraDistance * 2));

	f_View.build(f_CamPos,
		f_camX,
		f_camY,
		f_camZ,
		fov / aspect,
		aspect,
		farplane);

#if 0
	f_View.draw();
#endif

	float f_Transport[4];
	
	if(_->NomSEnergy > 0)
		{
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[0]);
		glEnableVertexAttribArray(m0AttribLocation);
		glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Array - Normals
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[2]);
		glEnableVertexAttribArray(m2AttribLocation);
		glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Texture Coords
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[4]);
		glEnableVertexAttribArray(m4AttribLocation);
		glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Weights
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[1]);
		glEnableVertexAttribArray(m1AttribLocation);
		glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - MatrixIndex
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[3]);
		glEnableVertexAttribArray(m3AttribLocation);
		glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Elements Array - Face Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[5]);
#endif

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

#if 0
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

		for(unsigned int f_Iter = 0; f_Iter < _->NomSEnergy; f_Iter++)
			{
			if(f_Iter > 0 && f_Iter < _->MaxNomSEnergy)
				{
				PosTest.x = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x;
				PosTest.y = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.y;
				PosTest.z = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z;

				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Matrix.mf);

				if(f_View.is_inside(PosTest))
					{
					if(g_Player == 0)
						{
						f_Transport[0] = 0.0f;
						f_Transport[1] = 0.0f;
						f_Transport[2] = 0.0f;
						f_Transport[3] = 0.0f;
						}
					else
						{
						f_Transport[0] = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1;
						f_Transport[3] = 0.0f;
						}

					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					f_Transport[0] = -Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x;
					f_Transport[1] = 0;
					f_Transport[2] = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z;

					f_Transport[3] = Q_SEnergy->SEnergy[f_Iter].Scale;

					glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					int hardwareMeshId = 0;
					for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
						{
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

						// set the material diffuse color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

						// set the material specular color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getBoneCount(); boneId++)
							{
							////QDglActiveTextureARB(GL_TEXTURE0_ARB);
							glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getMapUserData(0));
							}

						glUniform1i(mTextureUniformLocation, 0);

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

						if (hardwareMeshId < 38)
							{
							diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						if (diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						ag_Calc_Light(BiVector(f_Transport[0], f_Transport[1], f_Transport[2]));

						glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
						glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
						glUniform1f(mLightNomUniformLocation, g_LightNom);

						glUniform1f(mTimeUniformLocation, (float)rand() / 32767);


						if(sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	if(player[g_Player]->WeaponStatus > 1)
		{
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[0]);
		glEnableVertexAttribArray(m0AttribLocation);
		glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Array - Normals
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[2]);
		glEnableVertexAttribArray(m2AttribLocation);
		glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Texture Coords
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[4]);
		glEnableVertexAttribArray(m4AttribLocation);
		glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Weights
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[1]);
		glEnableVertexAttribArray(m1AttribLocation);
		glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - MatrixIndex
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[3]);
		glEnableVertexAttribArray(m3AttribLocation);
		glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Elements Array - Face Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[5]);

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

#if 0
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

		/*if(player[g_Player]->AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);
		else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV, true);

		//##### MiniGUN Rotation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
			Ange.y = -0.87; //WeaponvalueshtY;//PI;
			Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

			// Set the actor's angle
			Qpo->Transform_RotateY(&player[g_Player]->RFistPosV, Ange.y);
			Qpo->Transform_RotateX(&player[g_Player]->RFistPosV, Ange.x);
			Qpo->Transform_RotateZ(&player[g_Player]->RFistPosV, Ange.z);
			//#####
			}

		glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, player[g_Player]->RFistPosV.Matrix.mf);

		//##### MiniGUN Translation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Anf.x = player[g_Player]->RFistPosV.Translation.x + 10.98;
			Anf.y = player[g_Player]->RFistPosV.Translation.y - 71.22;
			Anf.z = player[g_Player]->RFistPosV.Translation.z + 22.12;
			}
		else
			{
			Anf.x = player[g_Player]->RFistPosV.Translation.x + WeaponvalueX;
			Anf.y = player[g_Player]->RFistPosV.Translation.x + WeaponvalueY;
			Anf.z = player[g_Player]->RFistPosV.Translation.x + WeaponvalueZ;
			}

		PosTest.x = Anf.x;
		PosTest.y = Anf.y;
		PosTest.z = Anf.z;

		if(f_View.is_inside(PosTest))
			{
			if(g_Player == 0)
				{
				f_Transport[0] = 0.0f;
				f_Transport[1] = 0.0f;
				f_Transport[2] = 0.0f;
				f_Transport[3] = 0.0f;
				}
			else
				{
				f_Transport[0] = Anf.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = Anf.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (Anf.z - playerAV[0]->Xform.Translation.z) * -1;
				f_Transport[3] = 0.0f;
				}

			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

			f_Transport[0] = -Anf.x;
			f_Transport[1] = 0;
			f_Transport[2] = Anf.z;

			f_Transport[3] = player[g_Player]->Weapon.Scale.x;

			glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
			for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
				{
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

				// set the material diffuse color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

				// set the material specular color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[896];

				int boneId;
				for (boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getBoneCount(); boneId++)
					{
					////QDglActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getMapUserData(0));
					}

				glUniform1i(mTextureUniformLocation, 0);

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

				diffuseColor[0] = 1;
				diffuseColor[1] = 1;
				diffuseColor[2] = 1;

				ag_Calc_Light(BiVector(f_Transport[0], f_Transport[1], f_Transport[2]));

				glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
				glUniform1f(mLightNomUniformLocation, g_LightNom);

				glUniform1f(mTimeUniformLocation, (float)rand() / 32767);

				if (sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
				}
			}
		}

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].WeaponStatus > 1)
				{
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[0]);
				glEnableVertexAttribArray(m0AttribLocation);
				glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				//Normal Array - Normals
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[2]);
				glEnableVertexAttribArray(m2AttribLocation);
				glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - Texture Coords
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[4]);
				glEnableVertexAttribArray(m4AttribLocation);
				glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - Weights
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[1]);
				glEnableVertexAttribArray(m1AttribLocation);
				glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - MatrixIndex
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[3]);
				glEnableVertexAttribArray(m3AttribLocation);
				glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				//Elements Array - Face Indices
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[5]);

				MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

		#if 0
				glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
		#else
				glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
		#endif

				MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
				glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

				/*if(Q_Forge->Forge[SCRAM].AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV);
				else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV, true);

				//##### MiniGUN Rotation
				if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
					{
					Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
					Ange.y = -0.87; //WeaponvalueshtY;//PI;
					Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

					// Set the actor's angle
					Qpo->Transform_RotateY(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.y);
					Qpo->Transform_RotateX(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.x);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.z);
					//#####
					}

				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[SCRAM].RFistPosV.Matrix.mf);

				//##### MiniGUN Translation
				if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
					{
					Anf.x = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + 10.98;
					Anf.y = Q_Forge->Forge[SCRAM].RFistPosV.Translation.y - 71.22;
					Anf.z = Q_Forge->Forge[SCRAM].RFistPosV.Translation.z + 22.12;
					}
				else
					{
					Anf.x = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueX;
					Anf.y = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueY;
					Anf.z = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueZ;
					}

				PosTest.x = Anf.x;
				PosTest.y = Anf.y;
				PosTest.z = Anf.z;

				if(f_View.is_inside(PosTest))
					{
					if(g_Player == 0)
						{
						f_Transport[0] = 0.0f;
						f_Transport[1] = 0.0f;
						f_Transport[2] = 0.0f;
						f_Transport[3] = 0.0f;
						}
					else
						{
						f_Transport[0] = Anf.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = Anf.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (Anf.z - playerAV[0]->Xform.Translation.z) * -1;
						f_Transport[3] = 0.0f;
						}

					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					f_Transport[0] = -Anf.x;
					f_Transport[1] = 0;
					f_Transport[2] = Anf.z;

					f_Transport[3] = Q_Forge->Forge[SCRAM].Weapon.Scale.x;

					glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					int hardwareMeshId = 0;
					for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
						{
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

						// set the material diffuse color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

						// set the material specular color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getBoneCount(); boneId++)
							{
							////QDglActiveTextureARB(GL_TEXTURE0_ARB);
							glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getMapUserData(0));
							}

						glUniform1i(mTextureUniformLocation, 0);

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;

						ag_Calc_Light(BiVector(f_Transport[0], f_Transport[1], f_Transport[2]));

						glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
						glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
						glUniform1f(mLightNomUniformLocation, g_LightNom);

						glUniform1f(mTimeUniformLocation, (float)rand() / 32767);

						if (sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}

		SCRAM++;
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int f_vehicleiter = 0; f_vehicleiter < m_VehicleCount; f_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[f_vehicleiter].getColumnMajor44(glMat);
		glMultMatrixf(glMat);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(-90, 0.0f, 0.0f, 1.0f);

		//glTranslatef(Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.x, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.y, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.z);
		//glMultMatrixf(Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Viewform.Matrix.mf);

		//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
		glScalef(0.007, 0.007, 0.007);

		for(int iter = 0; iter < QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh.num; iter++)
			{
			pMesh* f_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Avatar*/]->m_submesh[iter];

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
					//set_relief_params_static(mat->diffuse,mat->specular,1,1,Medias->expandro1,Medias->expandro1);
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
#endif
}

void unRenderer::draw_material_avatars(int f_Index, bool relief, MathHelper::Matrix4 f_Model, MathHelper::Matrix4 f_View, float f_X, float f_Y, float f_Z)
{
	g_Player = f_Index;

	float f_LightPos[40];
	float f_LightColor[40];

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	if(mProgramSlot == 0)
		{
		printf("unRenderer:::draw_material_avatars mProgramSlot is not loaded\n");
		for(;;) {}
		}

	glUseProgram(mProgramSlot);

	float f_Transport[3];
	float f_Team[4];

	//Vertex Array - Position
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glEnableVertexAttribArray(m0AttribLocationSlot);
	glVertexAttribPointer(m0AttribLocationSlot, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normal Array - Normals
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glEnableVertexAttribArray(m2AttribLocationSlot);
	glVertexAttribPointer(m2AttribLocationSlot, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - Texture Coords
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glEnableVertexAttribArray(m4AttribLocationSlot);
	glVertexAttribPointer(m4AttribLocationSlot, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - Weights
    glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glEnableVertexAttribArray(m1AttribLocationSlot);
	glVertexAttribPointer(m1AttribLocationSlot, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Vertex Array - MatrixIndex
	glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glEnableVertexAttribArray(m3AttribLocationSlot);
	glVertexAttribPointer(m3AttribLocationSlot, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//Elements Array - Face Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glUniformMatrix4fv(mModelUniformLocationSlot, 1, GL_FALSE, &f_Model.m[0][0]);
	glUniformMatrix4fv(mViewUniformLocationSlot, 1, GL_FALSE, &f_View.m[0][0]);

	MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
	glUniformMatrix4fv(mProjUniformLocationSlot, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

	if(player[g_Player]->Team == 0)
		{
		f_Team[0] = 0.0;
		f_Team[1] = 0.0;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 1)
		{
		f_Team[0] = 0.08;
		f_Team[1] = 0.0;
		f_Team[2] = 0.2;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 2)
		{
		f_Team[0] = 0.18;
		f_Team[1] = 0.0;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 3)
		{
		f_Team[0] = 0.25;
		f_Team[1] = 0.0;
		f_Team[2] = 0.25;
		f_Team[3] = 1.0;
		}
	else if(player[g_Player]->Team == 4)
		{
		f_Team[0] = 0.23;
		f_Team[1] = 0.20;
		f_Team[2] = 0.0;
		f_Team[3] = 1.0;
		}

	glUniform4fv(mTeamUniformLocationSlot, 1, &(f_Team[0]));

	f_Transport[0] = 0;
	f_Transport[1] = 65.0;
	f_Transport[2] = f_Z;

	glUniform3fv(mAvatarTranslationUniformLocationSlot, 1, &(f_Transport[0]));

	f_Transport[0] = f_X;
	f_Transport[1] = f_Y;
	f_Transport[2] = 0.21;

	glUniform3fv(mCameraTranslationUniformLocationSlot, 1, &(f_Transport[0]));

	/// Player Mesh Settings ///
	int hardwareMeshId = 0;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f;

		float transformation[896];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
			transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
			transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
			transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;

			glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			}

		glUniform1i(mTextureUniformLocationSlot, 0);
		glUniformMatrix4fv(mMatricesUniformLocationSlot, 56, GL_FALSE, &(transformation[0]));

		if(hardwareMeshId < 38)
			{
			diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
			diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
			diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
			}
		else
			{
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;
			}

		if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
			{
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;
			}

		f_LightPos[0] = mDrawCount;
		f_LightPos[1] = mDrawCount;
		f_LightPos[2] = 190;
		f_LightPos[3] = 1.0;
		f_LightColor[0] = 0.8;
		f_LightColor[1] = 0.8;
		f_LightColor[2] = 0.65;
		f_LightColor[3] = 1.0;

		int f_Start = 0;
		if(Q_Nom_Light - 10 < 0)
			{
			f_Start = 50 + (Q_Nom_Light - 10);
			}
		else
			{
			f_Start = Q_Nom_Light - 10;
			}

		int f_Count = f_Start;
		for(int f_Point = 4; f_Point < 40; f_Point += 4)
			{
			f_LightPos[f_Point] = g_Light[f_Count].m_Pos.x;
			f_LightPos[f_Point + 1] = g_Light[f_Count].m_Pos.z + g_Light[f_Count].m_Pos.y;
			f_LightPos[f_Point + 2] = 0.0;
			f_LightPos[f_Point + 3] = 1.0;
			f_LightColor[f_Point] = g_Light[f_Count].m_Color.red / 255;
			f_LightColor[f_Point + 1] = g_Light[f_Count].m_Color.green / 255;
			f_LightColor[f_Point + 2] = g_Light[f_Count].m_Color.blue / 255;
			f_LightColor[f_Point + 3] = g_Light[f_Count].m_Color.alpha / 255;
			}

		if(Q_Nom_Light > 0)
			{
			f_LightPos[4] = g_Light[Q_Nom_Light - 1].m_Pos.x;
			f_LightPos[5] = g_Light[Q_Nom_Light - 1].m_Pos.y;
			f_LightPos[6] = g_Light[Q_Nom_Light - 1].m_Pos.z;
			f_LightPos[7] = 1.0;
			f_LightColor[4] = g_Light[Q_Nom_Light - 1].m_Color.red;
			f_LightColor[5] = g_Light[Q_Nom_Light - 1].m_Color.green;
			f_LightColor[6] = g_Light[Q_Nom_Light - 1].m_Color.blue;
			f_LightColor[7] = g_Light[Q_Nom_Light - 1].m_Color.alpha;
			}

		glUniform4fv(mLightPosUniformLocationSlot, 10, &(f_LightPos[0]));
		glUniform4fv(mLightColorUniformLocationSlot, 10, &(f_LightColor[0]));

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	if(mDrawCountDIR == 0)
		{
		if(mDrawCount > 400)
			{
			mDrawCountDIR = 1;
			}
		else
			{
			mDrawCount++;
			}
		}
	else
		{
		if(mDrawCount < -400)
			{
			mDrawCountDIR = 0;
			}
		else
			{
			mDrawCount--;
			}
		}
}

void unRenderer::draw_material_avatars(bool relief)
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	if(mProgram == 0)
		{
		printf("unRenderer:::draw_material_avatars slot mProgram is not loaded\n");
		for(;;) {}
		}

	glUseProgram(mProgram);

	pFrustum f_View;

	float cameraDistance = (((750.0f / g_Zoom) * (1 - g_ZoomFactor)) + 300.0f) * g_ArenaSize;

	float fov = 115.0f;
	float aspect = float(1280.0f) / float(1080.0f);
	float farplane = 10000.0f;
	pVector f_camX(1.0f, 0.0f, 0.0f);
	pVector f_camY(0.0f, 1.0f, 0.5f);
	pVector f_camZ(0.0f, -1.0f, 1.0f);

	pVector f_PlayerPos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	f_camX.normalize();
	f_camY.normalize();
	f_camZ.normalize();

	pVector f_CamPos = f_PlayerPos + (f_camZ * (cameraDistance * 2));

	f_View.build(f_CamPos,
		f_camX,
		f_camY,
		f_camZ,
		fov / aspect,
		aspect,
		farplane);

#if 0
	f_View.draw();
#endif

	float f_Transport[4];
	float f_Team[4];

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(f_View.is_inside(pVector(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z)))
			{
			//Vertex Array - Position
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
			glEnableVertexAttribArray(m0AttribLocation);
			glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Normal Array - Normals
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
			glEnableVertexAttribArray(m2AttribLocation);
			glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Texture Coords
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
			glEnableVertexAttribArray(m4AttribLocation);
			glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Weights
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
			glEnableVertexAttribArray(m1AttribLocation);
			glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - MatrixIndex
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
			glEnableVertexAttribArray(m3AttribLocation);
			glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Elements Array - Face Indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

			 ////////////////////////////////
			////// Render Player Mesh //////
		
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, playerAV[g_Player]->Xform.Matrix.mf);
			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			if(player[g_Player]->Team == 0)
				{
				f_Team[0] = 0.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 1)
				{
				f_Team[0] = 0.08;
				f_Team[1] = 0.0;
				f_Team[2] = 0.2;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 2)
				{
				f_Team[0] = 0.18;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 3)
				{
				f_Team[0] = 0.25;
				f_Team[1] = 0.0;
				f_Team[2] = 0.25;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 4)
				{
				f_Team[0] = 0.23;
				f_Team[1] = 0.20;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}

			glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

			QpoVec3d f_Diff;
			float f_Length = 150.0f;
			bool f_Touch = false;
			int f_Index = 0;

			for(int f_Count = 0; f_Count < _->NomAI; f_Count++)
				{
				if(Q_Forge->Forge[f_Count].LIVE)
					{
					if (Q_Forge->Forge[f_Count].Team != player[g_Player]->Team)
						{
						if(Q_Forge->Forge[f_Count].HB_Dead == 0)
							{
							Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[f_Count].AV.Xform.Translation, &f_Diff);

							float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

							if(f_AvatarLength < f_Length)
								{
								f_Length = f_AvatarLength;
								f_Index = f_Count;
								f_Touch = true;
								}
							}
						}
					}
				}

			if(f_Touch && player[g_Player]->attackon && !player[g_Player]->HB_Dead)
				{
				float f_X = (Q_Forge->Forge[f_Index].AV.Xform.Translation.x - playerAV[g_Player]->Xform.Translation.x) * 0.2;
				float f_Y = (Q_Forge->Forge[f_Index].AV.Xform.Translation.z - playerAV[g_Player]->Xform.Translation.z) * 0.2;

				if(f_X > 2.9)
					{
					f_X = 2.9;
					}

				if(f_Y > 2.9)
					{
					f_Y = 2.9;
					}

				playerAV[g_Player]->Xform.Translation.x += f_X * _->TimeScale;
				playerAV[g_Player]->Xform.Translation.z += f_Y * _->TimeScale;
				}

#if 0
			if(_->TimeHole == 0)
				{
				g_ZoomFactor -= 0.05;

				if(g_ZoomFactor <= 0.0)
					{
					g_ZoomFactor = 0.0;
					}
				}
			else
				{
				g_ZoomFactor += 0.09;

				if(g_ZoomFactor >= 1.0)
					{
					g_ZoomFactor = 1.0;
					}
				}
#endif

			if(g_Player == 0)
				{
				f_Transport[0] = 0.0f;
				f_Transport[1] = 0.0f;
				f_Transport[2] = 0.0f;
				}
			else
				{
				f_Transport[0] = playerAV[g_Player]->Xform.Translation.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = playerAV[g_Player]->Xform.Translation.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (playerAV[g_Player]->Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1;
				}

			f_Transport[3] = 0.0f;

			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));


			f_Transport[0] = -playerAV[0]->Xform.Translation.x;
			f_Transport[1] = 0;
			f_Transport[2] = playerAV[0]->Xform.Translation.z;
			f_Transport[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2));

			glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
				// set the material diffuse color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
				// set the material specular color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[896];

				int boneId;
				for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#if 0
					if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
						{
#endif
						transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
						transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
						transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
						transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
						//transformation[(boneId * 16) + 12] = rotationMatrix.dzdx; transformation[(boneId * 16) + 13] = rotationMatrix.dzdy; transformation[(boneId * 16) + 14] = rotationMatrix.dzdz; transformation[(boneId * 16) + 15] = translationBoneSpace.z;

#if 0
						}
					else
						{
						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
						}
#endif

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
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

					////QDglActiveTextureARB(GL_TEXTURE0_ARB);
					//glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					}

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, (GLuint)::playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				glUniform1i(mTextureUniformLocation, 0);

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

#if 1
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				else
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}

				if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}
#endif

				ag_Calc_Light(Cube::BiVector(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 45, playerAV[g_Player]->Xform.Translation.z));

				glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
				glUniform1f(mLightNomUniformLocation, g_LightNom);

				glUniform1f(mTimeUniformLocation, (float)rand() / 32767);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			////////////////////////////////////
			////// Render Player Shadows ///////

			if(player[g_Player]->ShadowsOn)
				{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glEnable(GL_BLEND);

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
			#if 0
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mDrawCount / 50.0f);
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

					MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

					MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));
				#else
				#if 0
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix(25.0f / 50.0f);
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));
				#else
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);
				#endif

					viewMatrix = MathHelper::SimpleViewMatrix();

				#if 0
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
				#else
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
				#endif

					projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

					if(player[g_Player]->Team == 0)
						{
						f_Team[0] = 0.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 1)
						{
						f_Team[0] = 0.08;
						f_Team[1] = 0.0;
						f_Team[2] = 0.2;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 2)
						{
						f_Team[0] = 0.18;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 3)
						{
						f_Team[0] = 0.25;
						f_Team[1] = 0.0;
						f_Team[2] = 0.25;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 4)
						{
						f_Team[0] = 0.23;
						f_Team[1] = 0.20;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}

					glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

					if(g_Player == 0)
						{
						f_Transport[0] = 0.0f;
						f_Transport[1] = 0.0f;
						f_Transport[2] = 0.0f;
						f_Transport[3] = 0.0f;
						}
					else
						{
	#ifdef QAR
						f_Transport[0] = playerAV[g_Player]->Xform.Translation.x - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
						f_Transport[1] = playerAV[g_Player]->Xform.Translation.y;
						f_Transport[2] = (playerAV[g_Player]->Xform.Translation.z - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z) * -1;
	#else
						f_Transport[0] = playerAV[g_Player]->Xform.Translation.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = playerAV[g_Player]->Xform.Translation.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (playerAV[g_Player]->Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1;
	#endif
						f_Transport[3] = 0.0f;
						}
				
					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

	#ifdef QAR
					f_Transport[0] = -Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
					f_Transport[1] = 0;
					f_Transport[2] = Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z;
	#else
					f_Transport[0] = -playerAV[0]->Xform.Translation.x;
					f_Transport[1] = 0;
					f_Transport[2] = playerAV[0]->Xform.Translation.z;
	#endif
					f_Transport[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2));

					glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					hardwareMeshId = 0;
					for(hardwareMeshId=0;hardwareMeshId<player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
						{
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
						// set the material diffuse color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
						// set the material specular color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
							{
							QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

				#if 0
							transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
							transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
							transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
				#endif

				#if 0
							if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
								{
				#endif
								transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
								transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
								transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
								transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
								//transformation[(boneId * 16) + 12] = rotationMatrix.dzdx; transformation[(boneId * 16) + 13] = rotationMatrix.dzdy; transformation[(boneId * 16) + 14] = rotationMatrix.dzdz; transformation[(boneId * 16) + 15] = translationBoneSpace.z;

				#if 0
								}
							else
								{
								transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
								transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
								transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
								}
				#endif

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
							glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

							//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							cgSetSamplerState(m_meshcolormap);

							////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
				#endif

							////QDglActiveTextureARB(GL_TEXTURE0_ARB);
							glBindTexture(GL_TEXTURE_2D,(GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							}

						glUniform1i(mTextureUniformLocation, 0);

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

				#if 1
						if(hardwareMeshId < 38)
							{
							diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
	#endif

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	////////////////////////////////////
	////// Render NON-Player Mesh //////
#endif

	pVector PosTest;
	for(int i = 0; i < _->NomAI; i++)
		{
#if 0
		QpoVec3d f_VecTo;
		float f_Length;
		Qpo->Vec3d_Subtract(&Q_Forge->Forge[i].AV.Xform.Translation, &playerAV[0]->Xform.Translation, &f_VecTo);
		f_Length = Qpo->Vec3d_Length(&f_VecTo);
#endif

		if((f_View.is_inside(pVector(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z))) && (Q_Forge->Forge[i].HB_DeadTimer > 0) && (Q_Forge->Forge[i].LIVE == 1))
			{
#if 0
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
			glDisable(GL_BLEND);

			if(mProgram == 0)
				{
				printf("unRenderer:::draw_material_avatars mProgram is not loaded\n");
				for(;;) {}
				}

			glUseProgram(mProgram);

			//Vertex Array - Position
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glEnableVertexAttribArray(m0AttribLocation);
			glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Normal Array - Normals
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glEnableVertexAttribArray(m2AttribLocation);
			glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Texture Coords
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glEnableVertexAttribArray(m4AttribLocation);
			glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Weights
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glEnableVertexAttribArray(m1AttribLocation);
			glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - MatrixIndex
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glEnableVertexAttribArray(m3AttribLocation);
			glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Elements Array - Face Indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

			////////////////////////////////
			////// Render Player Mesh //////

			//*glLoadIdentity();
			//*glMultMatrixf((float *)&g_render->camera.mat_t);
			//*glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mDrawCount / 50.0f);
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));
		#else
		#if 0
			MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix(25.0f / 50.0f);
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));
		#else
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[i].AV.Xform.Matrix.mf);
		#endif

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

		#if 0
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
		#else
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
		#endif

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			if(Q_Forge->Forge[i].Team == 0)
				{
				f_Team[0] = 0.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 1)
				{
				f_Team[0] = 0.08;
				f_Team[1] = 0.0;
				f_Team[2] = 0.2;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 2)
				{
				f_Team[0] = 0.18;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 3)
				{
				f_Team[0] = 0.25;
				f_Team[1] = 0.0;
				f_Team[2] = 0.25;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 4)
				{
				f_Team[0] = 0.23;
				f_Team[1] = 0.20;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}

			glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

#if 0
			if(Q_Forge->Forge[i].AV.Xform.Translation.x > 900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.x = 900 * g_ArenaSize;
				}
			if(Q_Forge->Forge[i].AV.Xform.Translation.y > 900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.y = 900 * g_ArenaSize;
				}
			if(Q_Forge->Forge[i].AV.Xform.Translation.z > 900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.z = 900 * g_ArenaSize;
				}

			if(Q_Forge->Forge[i].AV.Xform.Translation.x < -900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.x = -900 * g_ArenaSize;
				}
			if(Q_Forge->Forge[i].AV.Xform.Translation.y < -900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.y = -900 * g_ArenaSize;
				}
			if(Q_Forge->Forge[i].AV.Xform.Translation.z < -900 * g_ArenaSize)
				{
				Q_Forge->Forge[i].AV.Xform.Translation.z = -900 * g_ArenaSize;
				}
#endif

			if(g_ZoomFactor == 0 || 1)
				{
#ifdef QAR
				f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
				f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y;
				f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z) * -1;
#else
				f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1;
#endif
				f_Transport[3] = 0.0f;
				}
			else
				{
				f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - (playerAV[g_Player]->Xform.Translation.x * g_ZoomFactor);
				f_Transport[1] = (Q_Forge->Forge[i].AV.Xform.Translation.z + Q_Forge->Forge[i].AV.Xform.Translation.y) - ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y) * g_ZoomFactor);
				f_Transport[2] = 0.0f;
				f_Transport[3] = 0.0f;
				}

#if 1
			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));
#endif
#if 0
			glUniform3fv(mAvatarTranslationUniformLocation, 1, &(Q_Forge->Forge[i].AV.Xform.Translation.x));
#endif
#if 0
			glUniform3fv(mCameraTranslationUniformLocation, 1, &(g_render->camera.pos.x));
#else

#ifdef QAR
			f_Transport[0] = -Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
			f_Transport[1] = 0;
			f_Transport[2] = Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z;
#else
			f_Transport[0] = -playerAV[0]->Xform.Translation.x;
			f_Transport[1] = 0;
			f_Transport[2] = playerAV[0]->Xform.Translation.z;
#endif
			f_Transport[3] = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2));

			glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));
#endif
#endif

#ifndef QAGEMODE_SURGERY
			//*if(Q_Forge->Forge[i].AirJinkRotFG == 1)
			//*	{
			//*	glTranslatef(Q_Forge->Forge[i].AV->Xform.Translation.x, Q_Forge->Forge[i].AV->Xform.Translation.y, Q_Forge->Forge[i].AV->Xform.Translation.z);
			//*	glMultMatrixf(Q_Forge->Forge[i].AV->Viewform.mf);
			//*	}
			//*else
			//*	{
			//*	glTranslatef(Q_Forge->Forge[i].AV->Xform.Translation.x, Q_Forge->Forge[i].AV->Xform.Translation.y, Q_Forge->Forge[i].AV->Xform.Translation.z);
			//*	glMultMatrixf(Q_Forge->Forge[i].AV->Xform.Matrix.mf);
			//*	}
#endif

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
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
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
				// set the material diffuse color
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
				// set the material specular color
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[896];

				int boneId;
				for(boneId = 0; boneId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

		#if 0
					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
		#endif

		#if 0
					if(Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
						{
		#endif
						transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
						transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
						transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
						transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
						//transformation[(boneId * 16) + 12] = rotationMatrix.dzdx; transformation[(boneId * 16) + 13] = rotationMatrix.dzdy; transformation[(boneId * 16) + 14] = rotationMatrix.dzdz; transformation[(boneId * 16) + 15] = translationBoneSpace.z;

		#if 0
						}
					else
						{
						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
						}
		#endif

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
					glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
		#endif

					////QDglActiveTextureARB(GL_TEXTURE0_ARB);
					glBindTexture(GL_TEXTURE_2D,(GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					}

				glUniform1i(mTextureUniformLocation, 0);

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

		#if 1

				if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}
		#endif

				glDisable(GL_BLEND);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			//###- Render avatar shadows
			if(Q_Forge->Forge[i].ShadowsOn)
				{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glEnable(GL_BLEND);

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
#if 0
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix((float)mDrawCount / 50.0f);
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));

					MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

					MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(mWindowWidth) / float(mWindowHeight));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));
#endif
#if 0
					MathHelper::Matrix4 modelMatrix = MathHelper::SimpleModelMatrix(25.0f / 50.0f);
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, &(modelMatrix.m[0][0]));
#else
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);
#endif

					viewMatrix = MathHelper::SimpleViewMatrix();

#if 0
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

					projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));

					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

					if(Q_Forge->Forge[i].Team == 0)
						{
						f_Team[0] = 0.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 1)
						{
						f_Team[0] = 0.08;
						f_Team[1] = 0.0;
						f_Team[2] = 0.2;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 2)
						{
						f_Team[0] = 0.18;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 3)
						{
						f_Team[0] = 0.25;
						f_Team[1] = 0.0;
						f_Team[2] = 0.25;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 4)
						{
						f_Team[0] = 0.23;
						f_Team[1] = 0.20;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}

					glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

					if (g_ZoomFactor == 0 || 1)
						{
#ifdef QAR
						f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
						f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y;
						f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z) * -1;
#else
						f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1;
#endif
						f_Transport[3] = 0.0f;
						}
					else
						{
						f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - (playerAV[g_Player]->Xform.Translation.x * g_ZoomFactor);
						f_Transport[1] = (Q_Forge->Forge[i].AV.Xform.Translation.z + Q_Forge->Forge[i].AV.Xform.Translation.y) - ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y) * g_ZoomFactor);
						f_Transport[2] = 0.0f;
						f_Transport[3] = 0.0f;
						}

#if 1
					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));
#endif
#if 0
					glUniform3fv(mAvatarTranslationUniformLocation, 1, &(Q_Forge->Forge[i].AV.Xform.Translation.x));
#endif
#ifdef QAR
					f_Transport[0] = -Q_Forge->Forge[g_CamLock].AV.Xform.Translation.x;
					f_Transport[1] = 0;
					f_Transport[2] = Q_Forge->Forge[g_CamLock].AV.Xform.Translation.z;
#else
					f_Transport[0] = -playerAV[0]->Xform.Translation.x;
					f_Transport[1] = 0;
					f_Transport[2] = playerAV[0]->Xform.Translation.z;
#endif
					f_Transport[3] = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2));

					glUniform4fv(mCameraTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Avatar Mesh Settings ///
					hardwareMeshId = 0;
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
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
						// set the material diffuse color
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
						// set the material specular color
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
							{
							QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
							transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
							transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
							transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#if 0
							if(Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
								{
#endif
								transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
								transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
								transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
								transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
								//transformation[(boneId * 16) + 12] = rotationMatrix.dzdx; transformation[(boneId * 16) + 13] = rotationMatrix.dzdy; transformation[(boneId * 16) + 14] = rotationMatrix.dzdz; transformation[(boneId * 16) + 15] = translationBoneSpace.z;

#if 0
								}
							else
								{
								transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x+ _PositioningOffset.x;
								transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y+ _PositioningOffset.y;
								transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z+ _PositioningOffset.z;
								}
#endif

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
							glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

							//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							cgSetSamplerState(m_meshcolormap);

							////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

							////QDglActiveTextureARB(GL_TEXTURE0_ARB);
							glBindTexture(GL_TEXTURE_2D,(GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							}

						glUniform1i(mTextureUniformLocation, 0);

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));

#if 0
						if(hardwareMeshId < 38)
							{
							diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
#endif

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    //*glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	//*glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    //*glDisable(GL_LIGHTING);
    //glDisable(GL_LIGHT0);
    //glDisable(GL_DEPTH_TEST);
	//glDisable(GL_VERTEX_PROGRAM_ARB);
}

void unRenderer::draw_material_avatars_shell(bool relief)
{
#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

	glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

	std::vector<QunBone *>& vectorBone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

	if(!player[g_Player]->ShadowsOn)
		{
		/// Player Mesh Settings ///
		int hardwareMeshId = 0;
		for(hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
			{
			unsigned char meshColor[4];
			float materialColor[4];
			float diffuseColor[4];
			float specularColor[4];

			// set the material ambient color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
			// set the material diffuse color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
			// set the material specular color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
			specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
				{
				QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
				QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

				QunMatrix rotationMatrix = rotationBoneSpace;

	#if 0
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
	#endif

	#if 0
				if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
	#endif

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

				////QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
				}

			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 0 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 1 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 2 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 9 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 10)
				{
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				}
			else
				{
				diffuseColor[0] = 0;
				diffuseColor[1] = 0;
				diffuseColor[2] = 0;
				}

			if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
				{
				diffuseColor[0] = 1;
				diffuseColor[1] = 1;
				diffuseColor[2] = 1;
				}
	#endif

			//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
			//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
			//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
			//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

			//pVector lightpos;
			//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
			//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
			//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

			pVector eyepos;
			eyepos.x = g_render->camera.pos.x;
			eyepos.y = g_render->camera.pos.y;
			eyepos.z = g_render->camera.pos.z;

			//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
			//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

			if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			}
		}
	else // Shadows ON
		{
		//glDisable(GL_DEPTH_TEST);
		//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		//glEnable(GL_BLEND);

		/// Player Mesh Settings ///
		int hardwareMeshId = 0;
		for(hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
			{
			unsigned char meshColor[4];
			float materialColor[4];
			float diffuseColor[4];
			float specularColor[4];

			// set the material ambient color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
			// set the material diffuse color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
			// set the material specular color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
			specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
				{
				QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
				QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

				QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#if 0
				if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
#endif

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

				////QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
				}
		
			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 0 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 1 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 2 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 9 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 10)
				{
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				else
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}
				}

			if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
				{
				diffuseColor[0] = 1;
				diffuseColor[1] = 1;
				diffuseColor[2] = 1;
				}

#if 0
			diffuseColor[0] += 5;
			diffuseColor[1] += 5;
			diffuseColor[2] += 5;
#endif
#endif

			//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
			//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
			//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
			//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

			//pVector lightpos;
			//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
			//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
			//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

			pVector eyepos;
			eyepos.x = g_render->camera.pos.x;
			eyepos.y = g_render->camera.pos.y;
			eyepos.z = g_render->camera.pos.z;

			//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
			//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

			//glPushMatrix();
			//RenderToTexture_Prep();

			if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));

			//RenderToTexture_Tex();
			//glPopMatrix();

			//if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			//else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			}
		}

	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

	////////////////////////////////////
	////// Render Player Shadows ///////

#if 0
	if(player[g_Player]->ShadowsOn)
		{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(&player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(&player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			glDisable(GL_DEPTH_TEST);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable(GL_BLEND);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
				{
				/// Player Mesh Settings ///
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
					diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
					diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
	#endif

					diffuseColor[0] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
					diffuseColor[1] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
					diffuseColor[2] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
					//*cgGLSetParameter1f(m_meshAlpha, player[g_Player]->Shadows[SCRAM].Avatar.m_Alpha/255);

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			}
		}

	glDisable(GL_BLEND);
#endif

	////////////////////////////////////
	////// Render NON-Player Mesh //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(Q_Forge->Forge[i].LIVE == 1 && g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0)
			{
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

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

			Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

			glScalef(Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)),Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)));

			std::vector<QunBone *>& vectorBoneAI = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			if(!Q_Forge->Forge[i].ShadowsOn)
				{
					/// Avatar Mesh Settings ///
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
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
					for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

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

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(Q_Forge->Forge[i].CharDATA.BDataID == 0 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 1 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 2 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 9 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 10)
						{
						if(hardwareMeshId < 38 && hardwareMeshId != 24 && hardwareMeshId != 18 && hardwareMeshId != 0 && hardwareMeshId != 2 && hardwareMeshId != 3 && hardwareMeshId != 4 && hardwareMeshId != 5 && hardwareMeshId != 6 && hardwareMeshId != 7 && hardwareMeshId != 8 && hardwareMeshId != 9 && hardwareMeshId != 10 && hardwareMeshId != 11 &&
							hardwareMeshId != 17 && hardwareMeshId != 19 && hardwareMeshId != 20 && hardwareMeshId != 21 && hardwareMeshId != 22 && hardwareMeshId != 23 && hardwareMeshId != 28 && hardwareMeshId != 29 && hardwareMeshId != 30 && hardwareMeshId != 31)
							{
							diffuseColor[0] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

#if 0
					if(hardwareMeshId < 38)
						{
						diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
						diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
						diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}
#endif

					if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
					//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].AV.Avatar.m_Alpha);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			else //Shadows ON
				{
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount ; hardwareMeshId++)
					{
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
					for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

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

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(Q_Forge->Forge[i].CharDATA.BDataID == 0 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 1 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 2 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 9 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 10)
						{
						if(hardwareMeshId < 38 && hardwareMeshId != 24 && hardwareMeshId != 18 && hardwareMeshId != 0 && hardwareMeshId != 2 && hardwareMeshId != 3 && hardwareMeshId != 4 && hardwareMeshId != 5 && hardwareMeshId != 6 && hardwareMeshId != 7 && hardwareMeshId != 8 && hardwareMeshId != 9 && hardwareMeshId != 10 && hardwareMeshId != 11 &&
							hardwareMeshId != 17 && hardwareMeshId != 19 && hardwareMeshId != 20 && hardwareMeshId != 21 && hardwareMeshId != 22 && hardwareMeshId != 23 && hardwareMeshId != 28 && hardwareMeshId != 29 && hardwareMeshId != 30 && hardwareMeshId != 31)
							{
							diffuseColor[0] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

	#if 0
					if(hardwareMeshId < 38)
						{
						diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
						diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
						diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}
	#endif

					if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

#if 0
					diffuseColor[0] *= 5;
					diffuseColor[1] *= 5;
					diffuseColor[2] *= 5;
#endif

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
					//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].AV.Avatar.m_Alpha);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}

			//glDisable(GL_BLEND);
			//glEnable(GL_DEPTH_TEST);

			////////////////////////////////////
			////// Render AI Shadows ///////////

#if 0
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

					glColor4f(1.0f, 1.0f, 1.0f, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha/255);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
						{
						int hardwareMeshId = 0;
						for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
							{
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
							for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
								{
								QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
								QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

								QunMatrix rotationMatrix = rotationBoneSpace;

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

								////QDglActiveTextureARB(GL_TEXTURE0_ARB);
								glBindTexture(GL_TEXTURE_2D,(GLuint)(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
								}

							for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
								{
								transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
								}

							//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

							if(hardwareMeshId < 38)
								{
								diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.RED[hardwareMeshId] / 255;
								diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
								diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
								}
							else
								{
								diffuseColor[0] = 0;
								diffuseColor[1] = 0;
								diffuseColor[2] = 0;
								}

							diffuseColor[0] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
							diffuseColor[1] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
							diffuseColor[2] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];

							//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
							//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
							//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
							//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha);

							if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
							else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
							}
						}
					}
#endif
				}
				
			glDisable(GL_BLEND);
			}

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
#endif
}

void unRenderer::draw_alpha_shadows(void)
{
#if 0
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Bind CG programs
	bind_mesh_vertex();
	bind_blur();
	////*cgGLBindProgram(m_frag_alpha);
	////*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	//*cgGLSetParameter3fv(m_alphaView, &g_render->camera.pos.x);

	//*cgGLSetParameter2f(m_alphaPlanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////////////////////////////////////
	////// Player Shadow Amount  ///////

	if(player[g_Player]->ShadowsOn)
		{
		player[g_Player]->ShadowsAMT += 0.1;
		if(player[g_Player]->ShadowsAMT > 1) player[g_Player]->ShadowsAMT = 1;
		}
	else
		{
		player[g_Player]->ShadowsAMT -= 0.1;
		if(player[g_Player]->ShadowsAMT <= 0) player[g_Player]->ShadowsAMT = 0;
		}

	////////////////////////////////////
	////// Render Player Shadows ///////
	if(player[g_Player]->ShadowsAMT > 0)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

		std::vector<QunBone *>& vectorBonePS = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

		std::vector<QunBone *>& vectorBoneSS = player[g_Player]->Shadows[1].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

		for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
			glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

			glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

			if(player[g_Player]->Aposestate == 73) //JSRUSH
				{
				/// Player Mesh Settings ///
				for(int hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneSS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneSS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

						////QDglActiveTextureARB(GL_TEXTURE4_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * player[g_Player]->ShadowsAMT * playerAV[g_Player]->Avatar.Scale.y;
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					//diffuseColor[0] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
					//diffuseColor[1] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
					//diffuseColor[2] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
	#endif

					//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
					//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
					////*cgGLSetParameter1f(m_alphaAlpha, (float)((((player[g_Player]->ShadowEffect_Scale[f_MeshCnt] - 1) * 0.95) * 0.5) + 0.05));
					//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			else
				{
				/// Player Mesh Settings ///
				for(int hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBonePS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBonePS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

						////QDglActiveTextureARB(GL_TEXTURE4_ARB);
						glBindTexture(GL_TEXTURE_2D,(GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * player[g_Player]->ShadowsAMT * playerAV[g_Player]->Avatar.Scale.y;
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					diffuseColor[0] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
					diffuseColor[1] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
					diffuseColor[2] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
	#endif

					//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
					//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
					////*cgGLSetParameter1f(m_alphaAlpha, (float)((((player[g_Player]->ShadowEffect_Scale[f_MeshCnt] - 1) * 0.95) * 0.5) + 0.05));
					//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			}


		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(&player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(&player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

			glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			/// Player Mesh Settings ///
			for(int hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
				// set the material diffuse color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
				// set the material specular color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

					////QDglActiveTextureARB(GL_TEXTURE4_ARB);
					glBindTexture(GL_TEXTURE_2D,(GLuint)(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
				diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
				diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
				diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
#endif

				//diffuseColor[0] /= 2;
				//diffuseColor[1] /= 2;
				//diffuseColor[2] /= 2;

				//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
				//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
				//*cgGLSetParameter1f(m_alphaAlpha, (float)(&player[g_Player]->Shadows[SCRAM].Avatar.m_Alpha/255));

				//pVector lightpos;
				//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
				//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
				//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				}
			}
		}

	////////////////////////////////////
	////// Render AI Shadows ///////////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		if(Q_Forge->Forge[i].ShadowsOn && Q_Forge->Forge[i].HB_Dead == 0)
			{
			Q_Forge->Forge[i].ShadowsAMT += 0.1;
			if(Q_Forge->Forge[i].ShadowsAMT > 1) Q_Forge->Forge[i].ShadowsAMT = 1;
			}
		else
			{
			Q_Forge->Forge[i].ShadowsAMT -= 0.1;
			if(Q_Forge->Forge[i].ShadowsAMT <= 0) Q_Forge->Forge[i].ShadowsAMT = 0;
			}

		if(Q_Forge->Forge[i].ShadowsAMT > 0)
			{
			PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
			PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
			PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

			if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].LIVE == 1)
				{
				//Vertex Array - Position
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glEnableClientState(GL_VERTEX_ARRAY);

				//Normal Array - Normals
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
				glNormalPointer(GL_FLOAT, 0, 0);
				glEnableClientState(GL_NORMAL_ARRAY);

				//Vertex Array - Texture Coords
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				//Vertex Array - Weights
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
				glTexCoordPointer(4, GL_FLOAT, 0, 0);

				//Vertex Array - MatrixIndex
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
				glTexCoordPointer(4, GL_FLOAT, 0, 0);

				//Elements Array - Face Indices
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

				for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
					{
					////// Set Camera //////
					glLoadIdentity();
					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
					glMultMatrixf(Q_Forge->Forge[i].AV.Xform.Matrix.mf);

					Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					glScalef(Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
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
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

							////QDglActiveTextureARB(GL_TEXTURE4_ARB);
							glBindTexture(GL_TEXTURE_2D,(GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
							}

						for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
							{
							transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * Q_Forge->Forge[i].ShadowsAMT * Q_Forge->Forge[i].AV.Avatar.Scale.y;
							}

						//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
						diffuseColor[0] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
						diffuseColor[1] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
						diffuseColor[2] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
#endif

						//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
						//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
						//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
						////*cgGLSetParameter1f(m_alphaAlpha, (float)Q_Forge->Forge[i].AV.Avatar.m_Alpha/255);
						//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

						//pVector lightpos;
						//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
						//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
						//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

						pVector eyepos;
						eyepos.x = g_render->camera.pos.x;
						eyepos.y = g_render->camera.pos.y;
						eyepos.z = g_render->camera.pos.z;

						//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
						//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
					////// Set Camera //////
					glLoadIdentity();
					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					glTranslatef(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.x, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.y, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.z);
					glMultMatrixf(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);

					Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					glScalef(Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
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
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

							////QDglActiveTextureARB(GL_TEXTURE4_ARB);
							glBindTexture(GL_TEXTURE_2D,(GLuint)(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
							}

						//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
						diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.RED[hardwareMeshId] / 255;
						diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
						diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
	#endif

						//diffuseColor[0] /= 2;
						//diffuseColor[1] /= 2;
						//diffuseColor[2] /= 2;

						//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
						//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
						//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
						//*cgGLSetParameter1f(m_alphaAlpha, (float)(Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha/255));

						//pVector lightpos;
						//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
						//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
						//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

						pVector eyepos;
						eyepos.x = g_render->camera.pos.x;
						eyepos.y = g_render->camera.pos.y;
						eyepos.z = g_render->camera.pos.z;

						//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
						//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}
				}
			}
		}

	glDisable(GL_BLEND);

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
#endif
}

void unRenderer::draw_alpha_energy(void)
{
#if 0
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_BLEND);

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_alpha);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	//*cgGLSetParameter3fv(m_alphaView, &g_render->camera.pos.x);

	//*cgGLSetParameter2f(m_alphaPlanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glBindTexture(GL_TEXTURE_2D,(GLuint)1);

	unsigned char meshColor[4];
	float materialColor[4];
	float diffuseColor[4];
	float specularColor[4];

	meshColor[0] = 1;
	meshColor[1] = 1;
	meshColor[2] = 1;
	meshColor[3] = 1;

	materialColor[0] = 1;
	materialColor[1] = 1;
	materialColor[2] = 1;
	materialColor[3] = 1;

	diffuseColor[0] = 1;
	diffuseColor[1] = 1;
	diffuseColor[2] = 1;
	diffuseColor[3] = 1;

	specularColor[0] = 1;
	specularColor[1] = 1;
	specularColor[2] = 1;
	specularColor[3] = 1;

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0/* && Q_LEnergy->LEnergy[f_instance].Live == 1*/)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
				//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
				//*cgGLSetParameter1f(m_alphaAlpha, (float)Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha/255);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);
				}
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	//bind_terrain_vertex();

	terrainMaterial->diffuse.x = 1;
	terrainMaterial->diffuse.y = 1;
	terrainMaterial->diffuse.z = 1;

	terrainMaterial->specular.x = 1;
	terrainMaterial->specular.y = 1;
	terrainMaterial->specular.z = 1;

	bind_vertex();

#if 0
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
#else
	bind_normal();

	set_normal_params(terrainMaterial->diffuse, terrainMaterial->specular, 1, terrainMaterial->texid, terrainMaterial->texnormalid);
#endif

	int f_iterator;
	int f_layer;
	int f_instance;
	int f_index;

	trr::unTerrainCell* f_Cell;

#if 0
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_TerrainCell.size(); f_iterator++)
#else
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
#endif
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texnormalid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/

#if 0
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
#endif
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texnormalid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	
	set_relief_params(terrainMaterial->diffuse,terrainMaterial->specular,1,1,terrainMaterial->texid,terrainMaterial->texnormalid);

#if 0
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_TerrainCell.size(); f_iterator++)
#else
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
#endif
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				//glBindTexture(GL_TEXTURE_2D, (GLuint)mesh->mat[0]->texid);
				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D,(GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

#if 0
	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	unbind_vertex();
	unbind_relief();

    ///// clear light //////
    glDisable(GL_LIGHTING);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_material_shapes(bool relief)
{
#if 0
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
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,(GLuint)1);

#if 0
	//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
	//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
	//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
	//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

	pVector eyepos;
	eyepos.x = g_render->camera.pos.x;
	eyepos.y = g_render->camera.pos.y;
	eyepos.z = g_render->camera.pos.z;

	//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
	//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

	//glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

	//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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

void unRenderer::draw_material_shape_instances(bool relief)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < f_ShapeBank->m_Shape[f_iterator]->m_Instance.size(); f_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
			glTranslatef(f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->x, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->y, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->z);
			//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[f_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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

void unRenderer::draw_material_shape_energy(bool relief)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				glBindTexture(GL_TEXTURE_2D, (GLuint)Medias->flame[Q_LEnergy->LEnergy[f_instance].BmpCountSP]);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
	//glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

GLint unRenderer::getVertexUniformIndex(void)//*CGparameter parameter)
{
	const std::vector<float> zeroes(m_VertexMaxUniforms * 4, 0);

	//glProgramParameters4fvNV(GL_VERTEX_PROGRAM_NV, 0, m_VertexMaxUniforms, &zeroes[0]);

	const float ones[4] = {1, 1, 1, 1};
        
	//*cgGLSetParameterArray4f(parameter, 0, 1, ones);

	for (GLint i = 0; i < m_VertexMaxUniforms; ++i)
		{
		float modified[4];

		//glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV, i, GL_PROGRAM_PARAMETER_NV, modified);

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

void unRenderer::draw_lights(pMesh *m, bool scissor, int f_AOGI, int f_whiteout, int f_FAAB_Camera)
{
	fb_bind_render(0);

	// 2D ortho porjection
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,m_sizex,0,m_sizey,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glBlendFunc(GL_ONE,GL_ONE);
	glDisable(GL_BLEND);

	// draw ambient pass
	if(f_AOGI == AOGI_AROUND)
		{
		glDisable(GL_BLEND);

		mrt_bind_texture(-1); // bind all mrt textures

		bind_around();

		draw_rect(0, 0, m_sizex, m_sizey, false, false);
	
		unbind_around();
		}
	else
		{
#if 0
		glColor4fv(&m->ambient.x);
		printf("m->ambient.x %f m->ambient.y %f m->ambient.z %f m->ambient.w %f\n", m->ambient.x, m->ambient.y, m->ambient.z, m->ambient.w);
#else
		//glColor4f(0.45, 0.45 ,0.45, 0.45);
#endif

		glDisable(GL_BLEND);

		mrt_bind_texture(1);	// bind diffuse mrt texture
		draw_rect(0, 0, m_sizex, m_sizey, false,false);
		mrt_unbind_texture(1);
		//glColor4f(1, 1, 1, 1);
		
		mrt_bind_texture(-1); // bind all mrt textures
		}

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

			//glColor4f(1,1,1,0.075);

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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
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

void unRenderer::draw_avatars(void)
{
	try
		{
		draw_material_avatars(true);
		}
	catch (...)
		{
		int i = 1;
		}
}

void unRenderer::draw_geometry(pMesh *m,bool relief)
{
	//*mrt_bind_render();

	if(KEY_DOWN(QIN_F9) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
		{
		//#### Initialise One Particle ####//
		Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
		Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
		Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.15;		//0.025f//0.002f
		Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 2;

		Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
		Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x = playerAV[g_Player]->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y = playerAV[g_Player]->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z = playerAV[g_Player]->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.x = playerAV[g_Player]->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.y = playerAV[g_Player]->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.z = playerAV[g_Player]->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5)*3;

		Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

		_->NomPntSprite++;

		Q.WriteNEWCharacterDataV3(&player[g_Player]->BFO);
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
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
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
			if(_->NomSpikes > 750) _->NomSpikes = 0;

			jet++;
			}
		}

	float steering = 0;
	float acceleration = 0;
	bool handbrake = false;
	bool f_press = false;

	if(KEY_DOWN(QIN_KP4))
		{
		steering = -1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP6))
		{
		steering = 1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP8))
		{
		acceleration = 1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP5))
		{
		acceleration = -1;
		f_press = true;
		}

	//*//SDL_mutexP(m_mutex_Mesh);

#if 1
	//###-- - Sense Vector - --###//
if(KEY_DOWN(QIN_KP4))
	{
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueshtX += 0.01;

		printf("Sense Vector Left WeaponvalueshtX - %f\n", WeaponvalueshtX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueshtX -= 0.01;

		printf("Sense Vector Left WeaponvalueshtX - %f\n", WeaponvalueshtX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueshtY += 0.01;

		printf("Sense Vector Up WeaponvalueshtY - %f\n", WeaponvalueshtY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueshtY -= 0.01;

		printf("Sense Vector Up WeaponvalueshtY - %f\n", WeaponvalueshtY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueshtZ += 0.01;

		printf("Sense Vector In WeaponvalueshtZ - %f\n", WeaponvalueshtZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueshtZ -= 0.01;

		printf("Sense Vector In WeaponvalueshtZ - %f\n", WeaponvalueshtZ);
		}
	}
else
	{
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueX += 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueX -= 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueY += 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueY -= 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueZ += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueZ -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP6))
		{
		WeaponvalueW += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP5))
		{
		WeaponvalueW -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}
	}
#endif

	if(f_press)
		{
		//*QActiveFrameWork->DigiMass->ControlVehicle(steering, acceleration, handbrake);
		}

#if 1	//Positioned for lighting
	if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
#endif

#if 0
	QActiveFrameWork->acQFrame();

	//*if(KEY_DOWN(QIN_u)) UNMessageCore->acPrintName(0);
#endif

	/**g_render->set_camera();

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//glColor4f(1,1,1,1);
	glClearColor(g_render->bgcolor.x,g_render->bgcolor.y,g_render->bgcolor.z,1);
	//glClearDepth(1);
	glDisable(GL_TEXTURE_2D);

	glColorMask(true,true,true,true);
	glDepthMask(true);

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);*/

	//*ClearBlur();

	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acNxRender(0, false);
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acBuffer();

	//QpoTransform f_transform;
	//Qpo->Avatar_GetBoneTransform(playerAV[g_Player]->operator ->(), "BIP01 R HAND", &f_transform);

	//f_ShapeBank->m_Shape[0]->m_Instance[0]->x = f_transform.Translation.x;
	//f_ShapeBank->m_Shape[0]->m_Instance[0]->y = f_transform.Translation.y;
	//f_ShapeBank->m_Shape[0]->m_Instance[0]->z = f_transform.Translation.z;

#ifdef QAGEMODE_SURGERY
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
	//playerAV[g_Player]->Avatar.Mesh->BlendAnim(35, valuepose, 1);
	//playerAV[g_Player]->Avatar.Mesh->BlendAnimPhysics(35, valuepose, 1);

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
	if(KEY_DOWN(QIN_g)) QActiveFrameWork->f_TrrBank->acAddInstance(0, playerAV[g_Player]->Xform.Translation.x + ((((float)rand() / 32767) * 300)-150), playerAV[g_Player]->Xform.Translation.y + ((((float)rand() / 32767) * 300)-150), playerAV[g_Player]->Xform.Translation.z + ((((float)rand() / 32767) * 300)-150));
#endif

	//f_CSpeechDlg->m_pVoice->GetStatus(&f_CSpeechDlg->m_VoiceStatus, NULL);
	//if(f_CSpeechDlg->m_VoiceStatus.dwRunningState == 1) f_CSpeechDlg->acVoice();

	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress[1])
			{
			vecvarDpress[1] = true;

			QpoVec3d f_playerin;
			Qpo->Transform_GetRight(&player[g_Player]->Camrot,&f_playerin);
			//*PxVec3 f_force(f_playerin.x * -35, f_playerin.y * -35, f_playerin.z * -35);
			//*QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 5, &f_force);
			//QActiveFrameWork->DigiMass->acCreateCubeV2(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 10, &f_force);
			}
		}
	else vecvarDpress[1] = false;

	if(KEY_DOWN(QIN_h) && 0)
		{
		if(!vecvarDpress[2])
			{
			vecvarDpress[2] = true;
#if 1
			QpoVec3d f_playerin;
			Qpo->Transform_GetRight(&player[g_Player]->Camrot,&f_playerin);
			//*PxVec3 f_force(f_playerin.x * -35, f_playerin.y * -35, f_playerin.z * -35);
#if 0
			QActiveFrameWork->DigiMass->acCreateSphere(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 5.0f, 1.0f);
#endif
			//QActiveFrameWork->DigiMass->acCreateCubeV3(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 10, &f_force);
			//*QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 105, playerAV[g_Player]->Xform.Translation.z), 17, &f_force);
#endif

#if 0
			playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();

			// get the skeleton we need to update
			QunSkeleton *pSkeleton;
			pSkeleton = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton();

			// clear the skeleton state
			//pSkeleton->clearState();

			// get the bone vector of the skeleton
			std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

			// lock the skeleton state
			//pSkeleton->lockState();

			//QunBone *pBone = vectorBone[8];

			playerAV[g_Player]->Avatar.Mesh->m_RagDoll = Digi::DigiMassCore::instance()->acSkeletonPose(playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton(), vectorBone);
			printf("Physics Ragdoll created %i\n", playerAV[g_Player]->Avatar.Mesh->m_RagDoll);

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

#if 1
	if(KEY_DOWN(QIN_h))
		{
		Q_ItemRef f_ItemREF = Q.CreatePlayerItem(150, 0, 17.25);
		}
#endif

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
				FILE* f_filecheck = nullptr;
				bool fileSwit = true;

				while(!f_filecheck)
					{
					int random = rand()%55000;

					itoa(random, casecntbuf, 10);

					std::string strname = "Recording";
					std::string strnumber = casecntbuf;
					strFilename = strname + strnumber;

					f_filecheck = fopen(strFilename.c_str(), "rb");
					}
				fclose(f_filecheck);

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
				//QNetwork.OpenTapeBuffer("Recording9034.txt");//
				//QNetwork.OpenTapeBuffer("Recording7719.txt");
				//QNetwork.OpenTapeBuffer("Recording26835.txt");

				//6
				//QNetwork.OpenTapeBuffer("Recording25554.txt");
				//QNetwork.OpenTapeBuffer("Recording8532.txt");
				QNetwork.OpenTapeBuffer("Recording3441.txt");

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

	//*g_render->set_camera();

#if 0	//@#@
	draw_depth_shape_energy();
#endif

	

#if 0	//@#@
	draw_depth_terrain_old();
#endif

	// DigiMass Player Character
	/*QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb.empty();
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[0] = playerAV[g_Player]->Xform.Translation.x - 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[1] = playerAV[g_Player]->Xform.Translation.y - 5;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[2] = playerAV[g_Player]->Xform.Translation.z - 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[0] = playerAV[g_Player]->Xform.Translation.x + 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[1] = playerAV[g_Player]->Xform.Translation.y + 95;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[2] = playerAV[g_Player]->Xform.Translation.z + 50;*/

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb.visualization();
#endif

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_depth_avatars();
#endif

#if 0
	//#### _ PLAYER FINAL COLLDET _ ####//
	player[g_Player]->finalcolldet_oldposCRT = player[g_Player]->finalcolldet_oldpos;
	player[g_Player]->finalcolldet_oldposCRT.y += 40;
	player[g_Player]->finalcolldet_Trans_CRT = playerAV[g_Player]->Xform.Translation;
	player[g_Player]->finalcolldet_Trans_CRT.y += 40;

	if(Qpo->Collision_RayTest(/*&playerAV[g_Player]->Mins, &playerAV[g_Player]->Maxs*/ NULL, NULL, &player[g_Player]->finalcolldet_oldposCRT, &player[g_Player]->finalcolldet_Trans_CRT, 0xffffffff, NULL, NULL, &player[g_Player]->Collision))
		{
		playerAV[g_Player]->Xform.Translation.x += (player[g_Player]->finalcolldet_oldpos.x - playerAV[g_Player]->Xform.Translation.x) * 15;
		playerAV[g_Player]->Xform.Translation.y += (player[g_Player]->finalcolldet_oldpos.y - playerAV[g_Player]->Xform.Translation.y) * 15;
		playerAV[g_Player]->Xform.Translation.z += (player[g_Player]->finalcolldet_oldpos.z - playerAV[g_Player]->Xform.Translation.z) * 15;
		}
	else
		{
		player[g_Player]->finalcolldet_oldpos = playerAV[g_Player]->Xform.Translation;
		}
#endif

#if 0
#if 1
	draw_depth_avatars();
#else
	draw_depth_avatars_shell();
#endif
#endif

	//*g_render->set_camera();


	//if(KEY_DOWN(QIN_0)) QActiveFrameWork->DigiMass->acSimulate();
	/*if(KEY_DOWN(QIN_9))*/ //QActiveFrameWork->DigiMass->acRender(true);
	//glTranslatef(0, 356, 0);

	//Item Positioning
	/*if(KEY_DOWN(QIN_d))
		{
		if(!vecvarDpress[16])
			{
			4++;
			if(4 > 11) 4 = 11;
			}

		vecvarDpress[16] = true;
		}
	else vecvarDpress[16] = false;

	if(KEY_DOWN(QIN_a))
		{
		if(!vecvarDpress[17])
			{
			4--;
			if(4 < 1) 4 = 1;
			}

		vecvarDpress[17] = true;
		}
	else vecvarDpress[17] = false;*/

	/*if(KEY_DOWN(QIN_KP6))
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


#if 0
	draw_depth_meshes();
#endif

	//*g_render->set_camera();

#if 0	//Weapon Testing
	draw_depth(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0]);
#endif

	//*g_render->set_camera();

	//draw_depth_terrain(m_TestModel);

#if 0
#if 1	//Trheight
	glTranslatef(0, +654.446411, 0);
#else
	glTranslatef(0, +2438.339233, 0);
#endif
#endif

#if 0
	draw_depth(m);
#endif

	//*glColorMask(true,true,true,true);
	//*glDepthMask(false);

#if 0
	draw_material(m, relief);
#endif

	//*g_render->set_camera();

#if 0
	//draw_material_terrain(m_TestModel, relief);
#endif

#if 0
	draw_material_meshes();
#endif

#if 0
	draw_material_mesh(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0], true);
#endif

#if 0	//@#@
	draw_material_terrain_old(relief);
#endif

	//glTranslatef(0, -356, 0);
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acRender(0, false);
	//QActiveFrameWork->DigiMass->acRender();
	//glTranslatef(0, 356, 0);

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_material_avatars(relief);
#endif

	//*g_render->set_camera();

#if 1
#if 1
	draw_material_avatars(relief);
#else
	draw_material_avatars_shell(relief);
#endif
#endif

	//printf("player[g_Player]->HB_Energy %f player[g_Player]->HB_MaxEnergy %f\n", player[g_Player]->HB_Energy, player[g_Player]->HB_MaxEnergy);
	if(KEY_DOWN(QIN_b)) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

// OLD POSITION

#if 0	//@#@
	draw_material_shape_instances(relief);
#endif

#if 0	//@#@
	draw_material_shape_energy(relief);
#endif

#if 0
	draw_material_shapes(relief);
#endif
	
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acNxRender(0, false);

	//UNMessageCore->acPrintName(0);

#if 0
	Qpo->Player_RenderBoneBoundingBox("BIP01 R HAND");
	Qpo->Player_GetBoneBoxes("BIP01 R HAND", &pCorner, &DX, &DY, &DZ, &ColldetBox);

	Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

	player[g_Player]->LimPosBox.Matrix = playerAV[g_Player]->Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
	coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

	player[g_Player]->LimPosBox.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
	player[g_Player]->LimPosBox.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
	player[g_Player]->LimPosBox.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&Box, xScale, yScale, zScale, &player[g_Player]->LimPosBox);
	Qpo->Box_Render(Box);

	Qpo->Camera_Set();

	ColldetBox.Min = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Min);
	ColldetBox.Max = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Max);

	glColor3f(0.25f, 0.25f, 1.0f);
	//*glBegin(GL_LINES);

		glVertex3f(ColldetBox.Min.x + playerAV[g_Player]->Xform.Translation.x, ColldetBox.Min.y + playerAV[g_Player]->Xform.Translation.y, ColldetBox.Min.z + playerAV[g_Player]->Xform.Translation.z);
		glVertex3f(ColldetBox.Max.x + playerAV[g_Player]->Xform.Translation.x, ColldetBox.Max.y + playerAV[g_Player]->Xform.Translation.y, ColldetBox.Max.z + playerAV[g_Player]->Xform.Translation.z);

	//*glEnd();

	Qpo->Avatar_RenderBoneBoundingBox(0, "BIP01 HEAD");
	Qpo->Avatar_GetBoneBoundingBox(0, "BIP01 HEAD", &pCorner, &DX, &DY, &DZ);

	Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

	player[g_Player]->LimPosBox.Matrix = Q_Forge->Forge[0].AV.Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
	coldetresult = Q_Forge->Forge[0].AV.Xform.Matrix.multiply_rotation(pCorner);

	player[g_Player]->LimPosBox.Translation.x = coldetresult.x + Q_Forge->Forge[0].AV.Xform.Translation.x;
	player[g_Player]->LimPosBox.Translation.y = coldetresult.y + Q_Forge->Forge[0].AV.Xform.Translation.y;
	player[g_Player]->LimPosBox.Translation.z = coldetresult.z + Q_Forge->Forge[0].AV.Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &player[g_Player]->LimPosBox);
	Qpo->Box_Render(_->KokBox);

	if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &Box)) printf("Trace Collision\n");
	else printf("Trace...\n");
#endif

#if 0
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

	//if(TimeAlter) _->TimeScale = 0.065;

	QActiveFrameWork->DigiMass->acSetTimeScale(_->TimeScale);
#endif

#if 0
	Qpo->Camera_Set();

	glColor3f(1.0f, 1.0f, 0.25f);
	//*glBegin(GL_LINES);

		glVertex3f(0,-297,0);
		glVertex3f(500, -297, 0);

	//*glEnd();
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
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetUp(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetIn(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif


#ifdef QAGEMODE_SURGERY
	playerAV[g_Player]->Xform.Translation = Origin;
#endif

	//glLoadIdentity();

#ifdef QAGEMODE_SURGERY
	SurgeryFocus = m_PointLocator->getPos();
#endif

#if 0	// Trails Pose Reset
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
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

	for(SCRAM = 0; SCRAM < playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment.size(); SCRAM++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);

		glColorMask(true,true,true,true);
		glDepthMask(false);

		playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);
		}
#endif

	/**glEnable(GL_BLEND);

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping*/

#if 0
	mrt_bind_texture(-1); // bind all mrt textures

	draw_alpha_shadows();

	draw_alpha_energy();

	mrt_unbind_texture(-1);
#endif

	//*Qpo->resetExecMode();

#if 0
	QActiveFrameWork->acQFrame();

	if(KEY_DOWN(QIN_u))
		{
		QActiveFrameWork->m_QSpawnPntController->m_SpawnON = true;
#if 0
		UNMessageCore->acPrintName(0);
#endif
		}
#endif

	//*Qpo->resetExecMode();

#if 0	// Positioned for after effects
	QActiveFrameWork->acWorldFrame();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 0.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	glVertex3f(0, 0, 0);
	glVertex3f(0, -250, 0);
	//*glEnd();
#endif

#if 0
	for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
		{
		//printf("CAM %i x %f y %f z %f\n", f_gap, _->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		Qpo->Camera_Set();
		//glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
		////*glBegin(GL_LINES);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y + 175, _->mesh->cam[f_gap].pos.z);
		////*glEnd();
		//glColor3f(0.0f, 1.0f, 1.0f);	//GREEN
		////*glBegin(GL_LINES);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		//glVertex3f(_->mesh->cam[f_gap].pos.x + (_->mesh->cam[f_gap].Z.x * 100), _->mesh->cam[f_gap].pos.y + (_->mesh->cam[f_gap].Z.y * 100), _->mesh->cam[f_gap].pos.z + (_->mesh->cam[f_gap].Z.z * 100));
		////*glEnd();
		}
#endif

	//for(int test = 0; test < _->NomAI; test++) Q_Forge->Forge[test].AV.Xform.Translation = Origin;

#if 0
#if 0
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
			player[g_Player]->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &Origin);
		player[g_Player]->MoveReactSpeed = 0;

		player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
		player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
		player[g_Player]->HB_Dead = 0;
		}
#else
	if(KEY_DOWN(QIN_k))
		{
		aero=0;
		while(aero < _->NomAI)
			{
			player[g_Player]->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &Origin);
		player[g_Player]->MoveReactSpeed = 0;

		player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
		player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
		player[g_Player]->HB_Dead = 0;
		}
#endif
#endif

#if 0
	if(KEY_DOWN(QIN_KP4))
		{
		f_GlobalAxisVector.x -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP5))
		{
		f_GlobalAxisVector.y -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP6))
		{
		f_GlobalAxisVector.z -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP7))
		{
		f_GlobalAxisVector.x += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		f_GlobalAxisVector.y += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		f_GlobalAxisVector.z += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP0))
		{
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}
#endif

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	/**glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();

	QActiveFrameWork->trrcursor->acRender();*/

	//QActiveFrameWork->DigiMass->m_Engine.acDraw(0, 1);

	//QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acRenderFloor(0, 1);

#if 0
	QpoVec3d f_start;
	QpoVec3d f_end;

	f_start.x = playerAV[g_Player]->Xform.Translation.x;
	f_start.y = playerAV[g_Player]->Xform.Translation.x;
	f_start.z = playerAV[g_Player]->Xform.Translation.x;
	f_end.x = playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250);
	f_end.y = playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250);
	f_end.z = playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250);

	Q.ShowLine(&f_start, &f_end, &player[g_Player]->ViewXForm.Translation, 5, Medias->BulletCount, 255, 255, 255, 255, 0);
#endif

#ifdef QAGEMODE_SURGERY
	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
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

	playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->draw(true);

	glColorMask(true,true,true,true);
	glDepthMask(false);

#if 1	//HERE
	playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->draw(true);
#endif

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
#endif

#if 0
	if(KEY_DOWN(QIN_UP)) playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->getNxCloth()->addForceAtPos(PxVec3(0,-250,0), PxVec3(1,0,0), 500);
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

				PxVec3 f_position = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
				printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
				}
			}
		else vecvarDpress[7] = false;

		if(KEY_DOWN(QIN_KP4))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.z -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP6))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.z += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP8))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.y -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP2))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.y += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP7))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.x += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP1))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.x -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP9))
			{
			if(!vecvarDpress[5])
				{
				vecvarDpress[5] = true;

				if(f_BoneIter < 14) f_BoneIter++;
				printf("f_BoneIter %i\n", f_BoneIter);
				}
			}
		else vecvarDpress[5] = false;

		if(KEY_DOWN(QIN_KP3))
			{
			if(!vecvarDpress[6])
				{
				vecvarDpress[6] = true;

				if(f_BoneIter > 0) f_BoneIter--;
				printf("f_BoneIter %i\n", f_BoneIter);
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(-0.2, 0, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0.2, 0, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0.2, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, -0.2, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, 0.2));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, -0.2));
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

	//#### Test Instancing ### 
	if(KEY_DOWN(QIN_k))
		{
		if(!vecvarDpress[13])
			{
			vecvarDpress[13] = true;

			//### Test 01
			int f_CharacterSelect = 0;
			int f_CharacterTeam = 1;
			int f_CharacterBoneStructure = 0;
			QpoVec3d f_PosVector;
			helly = 0;
			while(helly < _->NomAI)
				{
				f_CharacterBoneStructure = Q_Forge->Forge[helly].AV.Avatar.Mesh->m_BoneStructure;

				f_PosVector.x = (((float)rand() / 32767)-0.5)*750;
				f_PosVector.y = -350;
				f_PosVector.z = (((float)rand() / 32767)-0.5)*750;

				if((rand() % 11) >= 5) f_CharacterSelect = 0;
				else f_CharacterSelect = 11;

				int f_BDATID = (int)rand() % 10;

#ifdef QAGE_OPMOD_B
				f_BDATID = 0;
#endif

				float f_finger = ((float)rand() / 32767);
				if(f_finger < 0.5) f_CharacterTeam = 0;
				else f_CharacterTeam = 1;

				//QActiveFrameWork->acSpawnAvatar(helly, rand() % 11, f_BDATID, f_CharacterTeam, f_PosVector, f_CharacterBoneStructure, 255, 255, 255, 255, 255, 255);

				helly++;
				}
			}
		}
	else vecvarDpress[13] = false;

	if(KEY_DOWN(QIN_MINUS))
		{
		if(!vecvarDpress[14])
			{
			vecvarDpress[14] = true;

			player[g_Player]->BFO.BDATID--;
			if(player[g_Player]->BFO.BDATID < 0) player[g_Player]->BFO.BDATID = 11;
			//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.BDATID);
			helly = 0;
			while(helly <= 2)
				{
				helly++;
				//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);
				}
			}
		}
	else vecvarDpress[14] = false;

	if(KEY_DOWN(QIN_PLUS))
		{
		if(!vecvarDpress[15])
			{
			vecvarDpress[15] = true;

			player[g_Player]->BFO.BDATID++;
			if(player[g_Player]->BFO.BDATID > 11) player[g_Player]->BFO.BDATID = 11;
			//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.BDATID);
			helly = 0;
			while(helly <= 2)
				{
				helly++;
				//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);
				}
			}
		}
	else vecvarDpress[15] = false;

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//*glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	//glDisable(GL_BLEND);									// Enable Blending
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	//*g_render->set_camera();

	//QActiveFrameWork->DigiMass->acSimulate(_->TimeScale);
	//QActiveFrameWork->DigiMass->acRenderBoxes();

	if(rendswitchP)//NX_BF_ENERGY_SLEEP_TEST
		{
		//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		//glClearDepth(1.0f);									// Depth Buffer Setup
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		//*g_render->set_camera();

		//*QActiveFrameWork->DigiMass->acRenderScene(true);
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

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	/**glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();*/

#if 1
	//QActiveFrameWork->DigiMass->acSimulate();
	//*QActiveFrameWork->DigiMass->acRender();
#endif

#if 0
	QActiveFrameWork->DigiMass->acRenderScene(true);
#endif

	//=== Render Position Locators ===//
	//*g_render->set_camera();

	//QpoVec3d f_pos = m_PointLocator->getPos();
	//if(f_pos.x != 0 && f_pos.y != 0 && f_pos.z != 0) m_PointLocator->acRender();

	//f_pos = QActiveFrameWork->trrcursor->getPos();
	//if(f_pos.x != 0 && f_pos.y != 0 && f_pos.z != 0) QActiveFrameWork->trrcursor->acRender();

	//*mrt_unbind_render();

	//*QActiveFrameWork->acGameEventsFrame();

#if 0
	if(KEY_DOWN(QIN_RBUTTON) && !KEY_DOWN(QIN_SHIFT) && !g_render->fullscreen)
		{
		if(!vecvarDpress[4])
			{
			vecvarDpress[4] = true;

			PxVec3 f_vecpoint;
			/*if(g_render->fullscreen) f_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x, temppos.y);
			else*/ f_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x - 8, temppos.y - 48);

			m_PointLocator->setPos(f_vecpoint.x, f_vecpoint.y, f_vecpoint.z);
			QActiveFrameWork->trrcursor->setPos(f_vecpoint.x, f_vecpoint.y, f_vecpoint.z);
			if(gPickStay) QActiveFrameWork->DigiMass->PickSetPosition(f_vecpoint);
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

	//*//SDL_mutexV(m_mutex_Mesh);
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

	//pPBuffer *tmp;
	//tmp=m_fb[0];
	//m_fb[0]=m_fb[1];
	//m_fb[1]=tmp;
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

	//Frame Memory
//#ifdef UNRENDER_FRAMEMEMORY
#if 1
	if(g_render->framememory)
		{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_FrameMemory[m_Fcursor]);					// Bind To The Blur Texture
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, g_render->sizex, g_render->sizey, 0);
		m_Fcursor++;
		if(m_Fcursor >= UNREND_FRAMEMEMSIZE) m_Fcursor = 0;

		int f_cursor = m_Fcursor - UNREND_FRAMEMEMSIZE;
		if(f_cursor < 0) f_cursor = UNREND_FRAMEMEMSIZE + f_cursor;
		for(int mm = 0; mm < UNREND_FRAMEMEMSIZE; mm++)
			{
			glBindTexture(GL_TEXTURE_2D, m_FrameMemory[f_cursor]);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);

			//glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

			if(g_render->fullscreen)
				{
				////*glBegin(GL_QUADS);
					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);

					//glTexCoord2f(0, 0);
					//glVertex2i(0, g_render->sizey);

					//glTexCoord2f(1, 0);
					//glVertex2i(g_render->sizex, g_render->sizey);

					//glTexCoord2f(1, 1);
					//glVertex2i(g_render->sizex, 0);

					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);
				////*glEnd();
				}
			else
				{
				////*glBegin(GL_QUADS);
					//glTexCoord2f(0,1);
					//glVertex2i(0,0);

					//glTexCoord2f(0, 0);
					//glVertex2i(0, g_render->sizey);

					//glTexCoord2f(1, 0);
					//glVertex2i(g_render->sizex, g_render->sizey);

					//glTexCoord2f(1, 1);
					//glVertex2i(g_render->sizex, 0);

					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);
				////*glEnd();
				}

			f_cursor++;
			if(f_cursor >= UNREND_FRAMEMEMSIZE) f_cursor = 0;
			}
		}
#endif
}

void unRenderer::checkError(const char *name, const char *situation)
{
	//*CGerror error;
	//*const char *string = cgGetLastErrorString(&error);
  
	//*if (error != CG_NO_ERROR)
	//*	{
	//*	if (error == CG_COMPILER_ERROR)
	//*		{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s\n\n"
			"Cg compiler output...\n%s",
			name, situation, string,
			cgGetLastListing(g_render->cgcontext));*/

			//*		std::string errorstr;
			//*errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG Compile ERROR", MB_OK);
			//*printf("CG:::Compile Error:::%s:::%s:::\n %s\n", name, situation, errorstr.c_str());
			//*for(;;) {};
			//*}
			//*else
			//*{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s",
			name, situation, string);*/

			//std::string errorstr("ERROR::: ");
			//errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG ERROR", MB_OK);
			//*printf("CG:::General Execution Error");
			//*}
		//while(1) { /* Infinite Loop */ }
		//exit(1);
		//*}
}

void unRenderer::GLEnable2D(void)
{
   int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   //glMatrixMode(GL_PROJECTION);
   //glPushMatrix();
   //glLoadIdentity();

   //glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   //glMatrixMode(GL_MODELVIEW);
   //glPushMatrix();
   //glLoadIdentity();
}

void unRenderer::GLDisable2D(void)
{
   //glMatrixMode(GL_PROJECTION);
   //glPopMatrix();
   //glMatrixMode(GL_MODELVIEW);
   //glPopMatrix();
}

void unRenderer::DrawPane(unsigned int f_texture, int f_x, int f_y, int f_scalex, int f_scaley)
{
	int m_x[4];
	int m_y[4];

	int strendX = f_x + f_scalex;
	int strendY = VID_HEIGHT - (f_y + f_scaley);

	m_x[0] = strendX;
	m_y[0] = VID_HEIGHT - f_y;
	m_x[1] = f_x;
	m_y[1] = VID_HEIGHT - f_y;
	m_x[2] = f_x;
	m_y[2] = strendY;
	m_x[3] = strendX;
	m_y[3] = strendY;

	GLEnable2D();

	glEnable(GL_TEXTURE_2D);

	glBindTexture( GL_TEXTURE_2D, f_texture );

	////*glBegin( GL_QUADS );

	for(size_t id=0; id < 4; id++)
		{
		//glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
		//glVertex2d(m_x[id], m_y[id]);
		}

	////*glEnd();

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

				//*glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
					glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
					glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
					glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
					glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				//*glEnd();										// Done Building Triangle Strip

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

	return true;											// Everything Went OK
}

#endif

inline void unRenderer::testfunction(void)
	{

	}

GLuint unRenderer::CreateEmptyTexture(int f_x, int f_y)
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((f_x * f_y)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((f_x * f_y)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, f_x, f_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}
#else
unRenderer::unRenderer()
{
	/*m_vert_prog=0;
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
	m_rtdepth=0;

	m_frag_prog_light=0;
	m_lplanes=0;
	m_lpos=0;
	m_lcolor=0;

	m_frag_prog_blur=0;
	m_bdisp=0;

	m_frag_prog_antialias=0;
	m_apixelsize=0;
	m_aweight=0;*/

	//m_fb[0]=0;
	//m_fb[1]=0;
	//m_fb[2]=0;
	//m_fb[3]=0;

	m_fbtex[0]=0;
	m_fbtex[1]=0;
	m_fbtex[2]=0;
	m_fbtex[3]=0;

	//m_mrt=0;
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
	vecvarDpress[13] = false;
	vecvarDpress[14] = false;
	vecvarDpress[15] = false;

	WeaponvalueX = -0.14;
	WeaponvalueY = 10.05;
	WeaponvalueZ = 2.55;

	//WeaponvalueX = -7.050066;
	//WeaponvalueY = 10.05;
	//WeaponvalueZ = 2.55;

	WeaponvalueW = 0;

	WeaponvalueshtX = 0;
	WeaponvalueshtY = 0;
	WeaponvalueshtZ = 0;

	_PositioningOffset.x = 0;
	_PositioningOffset.y = 0;
	_PositioningOffset.z = 0;

#if 0
	//###-- - Sense Vector - --###//
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueX += 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueX -= 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueY += 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueY -= 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueZ += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueZ -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}
#endif
}

unRenderer::~unRenderer()
{
	free_programs();

#if 0
	mrt_destroy();
#endif

	Shutdown();
}

GLuint unRenderer::acShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);

    const char *sourceArray[1] = { source.c_str() };
    glShaderSource(shader, 1, sourceArray, NULL);
    glCompileShader(shader);

    GLint compileResult;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if(compileResult == 0)
		{
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Shader compilation failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end()); 

		std::string f_ErrorString = to_string(errorMessage);

#if 0
		printf("unRenderer::CompileShader:::%s", f_ErrorString.c_str());
#endif
#if 0
        throw;
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}

    return shader;
}

GLuint unRenderer::acProgram(const std::string& vsSource, const std::string& fsSource)
{
    GLuint program = glCreateProgram();

    if(program == 0)
		{
#if 0
		printf("unRenderer Program creation failed\n");
#endif
#if 0
        throw Exception::CreateException(E_FAIL, L"Program creation failed");
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}

    GLuint vs = acShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = acShader(GL_FRAGMENT_SHADER, fsSource);

    if(vs == 0 || fs == 0)
		{
        glDeleteShader(fs);
        glDeleteShader(vs);
        glDeleteProgram(program);

        return 0;
		}

    glAttachShader(program, vs);
    glDeleteShader(vs);

    glAttachShader(program, fs);
    glDeleteShader(fs);

    glLinkProgram(program);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if(linkStatus == 0)
		{
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(program, (GLsizei)infoLog.size(), NULL, infoLog.data());

        std::wstring errorMessage = std::wstring(L"Program link failed: ");
        errorMessage += std::wstring(infoLog.begin(), infoLog.end());

		std::string f_ErrorString = to_string(errorMessage);

#if 0
		printf("unRenderer::CompileProgram:::%s", f_ErrorString.c_str());
#endif
#if 0
        throw;
#endif
#ifdef ECOIN_DEBUG_BREAKS
		__debugbreak();
#endif
		}

    return program;
}

void unRenderer::Shutdown(void)
{
	QActiveFrameWork->acShutdown();
}

void unRenderer::mrt_create(int sx,int sy)
{
	//gl_buffers[0]=GL_FRONT_LEFT;
	//gl_buffers[1]=GL_AUX0;
	//gl_buffers[2]=GL_AUX1;
	/*gl_buffers[3]=GL_AUX2;
	
    wgl_buffers[0]=WGL_FRONT_LEFT_ARB;
    wgl_buffers[1]=WGL_AUX0_ARB;
    wgl_buffers[2]=WGL_AUX1_ARB;
	wgl_buffers[3]=m_nv_render_depth_texture?WGL_DEPTH_COMPONENT_NV:WGL_AUX2_ARB;

	m_sizex=sx;
	m_sizey=sy;

	//m_mrt=new pPBuffer(sx,sy,32,false,true,false,true,true,false,false,true,m_nv_render_depth_texture?2:3);

	glGenTextures(4,m_mrttex);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);

	if(m_nv_render_depth_texture)
		{
		glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,sx,sy,0,GL_DEPTH_COMPONENT,GL_UNSIGNED_INT,NULL);
		}
	else
		{
		glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
		}

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	//m_fb[0]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
	//m_fb[1]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glGenTextures(4,m_fbtex);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[1]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	sx/=UNREND_BLOOM_SCALE;
	sy/=UNREND_BLOOM_SCALE;

	//m_fb[2]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);
	//m_fb[3]=new pPBuffer(sx,sy,32,false,false,false,true,false,false,false,true,0);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[2]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,m_fbtex[3]);
	glTexImage2D( GL_TEXTURE_2D, 0, 4, sx, sy, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
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
#endif*/
}

void unRenderer::mrt_destroy()
{
	glDeleteTextures(4, m_mrttex);

	m_mrttex[0]=0;
	m_mrttex[1]=0;
	m_mrttex[2]=0;
	m_mrttex[3]=0;

	glDeleteTextures(3, m_fbtex);

	m_fbtex[0]=0;
	m_fbtex[1]=0;
	m_fbtex[2]=0;

#ifdef UNRENDER_FRAMEMEMORY
	glDeleteTextures(UNREND_FRAMEMEMSIZE, m_FrameMemory);

	for(int i = 0; i < UNREND_FRAMEMEMSIZE; i++)
		{
		m_FrameMemory[i] = 0;
		}
#endif

	//delete m_fb[0];
	//delete m_fb[1];
	//delete m_fb[2];
	
	//m_fb[0]=0;
	//m_fb[1]=0;
	//m_fb[2]=0;

	//delete m_mrt;
	
	//m_mrt=0;
}

void unRenderer::set_program_params(bool depth_bias,bool nv_render_depth_texture)
{
	m_depth_bias = depth_bias;

	//m_nv_render_depth_texture = (nv_render_depth_texture && WGLEW_NV_render_depth_texture);
}

bool unRenderer::load_programs()
{
#if 1
	const std::string vs = STRING
		(
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 rotationMatrices[56];
		uniform vec4 avatarTrans;

		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;

		varying vec2 vTexCoord;
		varying vec3 vNormal;
		varying vec3 vPosition;

		void main()
			{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			int matrix_x = int(aMatrixIndices.x);
			int matrix_y = int(aMatrixIndices.y);
			int matrix_z = int(aMatrixIndices.z);
			int matrix_w = int(aMatrixIndices.w);

			pos = (rotationMatrices[matrix_x] * tempPos) * aWeight.x;
			pos += (rotationMatrices[matrix_y] * tempPos) * aWeight.y;
			pos += (rotationMatrices[matrix_z] * tempPos) * aWeight.z;
			pos += (rotationMatrices[matrix_w] * tempPos) * aWeight.w;

			pos.xyz *= avatarTrans.w; //wk \/ ?

			mat3 m;

			m[0].xyz = rotationMatrices[matrix_x][0].xyz;
			m[1].xyz = rotationMatrices[matrix_x][1].xyz;
			m[2].xyz = rotationMatrices[matrix_x][2].xyz;

			normal += (m * tempNor) * aWeight.x;

			m[0].xyz = rotationMatrices[matrix_y][0].xyz;
			m[1].xyz = rotationMatrices[matrix_y][1].xyz;
			m[2].xyz = rotationMatrices[matrix_y][2].xyz;

			normal += (m * tempNor) * aWeight.y;

			//vec4 f_normal = vec4(normal, 1.0);

			//vec4 f_WOPlayVec = uProjMatrix * uViewMatrix * uModelMatrix * pos;
			//vec4 f_WOPlayNorm = uProjMatrix * uViewMatrix * uModelMatrix * f_normal;

			vec4 f_interim = uModelMatrix * pos;

			vec4 f_interim_normal = uModelMatrix * vec4(normal, 1.0);

			f_interim.x += avatarTrans.x;
			f_interim.y += avatarTrans.y;
			f_interim.z += avatarTrans.z;

			vec4 f_WOPlayVec = uProjMatrix * uViewMatrix * f_interim;

			vec3 f_WOPlayNorm = normalize(f_interim_normal.xyz); //wk unnormalize

			vNormal = f_WOPlayNorm;
			vPosition = f_WOPlayVec.xyz;
			vTexCoord = aTexCoord;

			gl_Position = f_WOPlayVec;
			}
		);

    // Fragment Shader source
    const std::string fs = STRING
		(
		precision mediump float;

		vec3 g_seed_store;

		void seed(vec3 co)
			{
			g_seed_store = co;
			}

		float rand(void)
			{
			float f_result = fract(sin(dot(g_seed_store, vec3(332.13268, 2348.16578345, 13.12353))) * 34128.1893);

			seed(vec3(f_result, f_result, f_result));

			return f_result;
			}

		uniform sampler2D uTexture;

		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform vec4 uTeam;
		uniform float uLightNom;
		uniform float uSeed;

		varying vec2 vTexCoord;
		varying vec3 vNormal;
		varying vec3 vPosition;

        void main()
			{
			// initially seed the psuedo random generator with absolute position
			seed(vec3(uSeed * vPosition.x, uSeed * vPosition.y, uSeed * vPosition.z));

			// normalise normal
			vec3 f_vNormal = normalize(vNormal);

			// pull ambient from current texture
			vec4 f_AmbientColor = texture2D(uTexture, vTexCoord.xy);

			// call for fragment
			float f_qsX = rand();
			float f_qsY = rand();
			float f_qsZ = rand();

			// sun effect
			vec3 f_SunLightPos = vec3(5000.0, 10500.0, 5850.0);
			vec4 f_SunLightColor = vec4(0.92, 0.87, 0.79, 1.0);

			float f_SunRadius = 1250.0;

			vec4 randElement = vec4(f_qsX * f_SunLightColor.x, f_qsY * f_SunLightColor.y, f_qsZ * f_SunLightColor.z, 1.0);

			f_SunLightColor = (f_SunLightColor * 0.8) + (randElement * 0.2); //wk

			vec3 f_L = normalize(f_SunLightPos);

			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(f_vNormal, f_L), 0.0), 1.0);

			Idiff = clamp(Idiff, 0.0, 1.0);
			//Idiff *= 0.03;
			Idiff *= 0.07; //wk

			float f_SunDistanceL = sqrt(dot(f_SunLightPos, f_SunLightPos));

			vec4 f_AccumulationBuffer = (Idiff * (f_SunRadius / (f_SunDistanceL / 655.3))); //750 //650 //800? //wk

			// Main Lights Loop
			float f_ProcCount = 0.0;
			for(int f_i = 0; f_i < 10; f_i++)
				{
				if(f_ProcCount < uLightNom)
					{
					if(uLightPos[f_i].w > 0.0)
						{
						vec3 f_LightPos = uLightPos[f_i].xyz;
						float f_LightRadius = uLightColor[f_i].w;

						vec3 to_light = f_LightPos - vPosition;
						vec3 to_light_norm = normalize(to_light);

						// Scale the color of this fragment based on its angle to the light.
						vec4 Idiffi = vec4(uLightColor[f_i].rgb * max(dot(f_vNormal, to_light_norm), 0.0), 1.0);

						Idiffi = clamp(Idiffi, 0.0, 1.0);
						//Idiffl *= 0.03;
						Idiffi *= 0.07; //wk

						// Scale the power of this fragment based on its distance to the light.
						float f_constant_dist = sqrt(to_light.x * to_light.x + to_light.y * to_light.y + to_light.z * to_light.z);

						f_AccumulationBuffer += (Idiffi * (f_LightRadius / 5.0)) * (1.0 - (f_constant_dist / 750.0)); //wk
						}

					f_ProcCount += 1.0;
					}
				}

			// add sun
			f_ProcCount += 1.0;

			// compile resultance division
			vec4 f_Result = f_AccumulationBuffer / f_ProcCount;

			f_Result.a = 1.0;

			// set pixel color
			gl_FragColor = ((f_AmbientColor * f_Result) * 0.8) + (uTeam * 0.34); //wk 0.44
			}
		);
#endif

#if 0
    const std::string vs = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform mat4 rotationMatrices[56];
		uniform vec4 avatarTrans;
		uniform vec4 cameraTrans;
		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;
		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		void main()
		{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			int matrix_x = int(aMatrixIndices.x);
			int matrix_y = int(aMatrixIndices.y);
			int matrix_z = int(aMatrixIndices.z);
			int matrix_w = int(aMatrixIndices.w);

			pos = (rotationMatrices[matrix_x] * tempPos) * aWeight.x;
			pos += (rotationMatrices[matrix_y] * tempPos) * aWeight.y;
			pos += (rotationMatrices[matrix_z] * tempPos) * aWeight.z;
			pos += (rotationMatrices[matrix_w] * tempPos) * aWeight.w;

			pos.xyz *= cameraTrans.w;

			mat3 m;

			m[0].xyz = rotationMatrices[matrix_x][0].xyz;
			m[1].xyz = rotationMatrices[matrix_x][1].xyz;
			m[2].xyz = rotationMatrices[matrix_x][2].xyz;

			normal += (m * tempNor) * aWeight.x;

			m[0].xyz = rotationMatrices[matrix_y][0].xyz;
			m[1].xyz = rotationMatrices[matrix_y][1].xyz;
			m[2].xyz = rotationMatrices[matrix_y][2].xyz;

			normal += (m * tempNor)* aWeight.y;

			vec4 f_interim = uModelMatrix * pos;

			f_interim.x += avatarTrans.x;
			f_interim.y += avatarTrans.y;
			f_interim.z += avatarTrans.z;

			vPosition = f_interim.xyz;

			gl_Position = uProjMatrix * uViewMatrix * f_interim;

			vNormal = normalize(normal);
			vec4 f_Norm = vec4(vNormal.xyz, 1.0);
			f_Norm = uModelMatrix * f_Norm;
			vNormal = f_Norm.xyz;
            vColor = vec4(1,1,1,1);
			vPos = vec3(0, 0, 0);// cameraTrans.xyz;
        }
    );

    // Fragment Shader source
    const std::string fs = STRING
		(
		precision mediump float;

		float rand(vec3 co)
			{
			float f_result = fract(sin(dot(co, vec3(12.9898, 78.233, 45.5432))) * 43758.5453);
			return f_result;
			}

        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;
		uniform vec4 uTeam;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];
		uniform float uLightNom;
		uniform float uSeed;
		uniform sampler2D uTexture;
        void main()
			{
			float f_SunLightNom = 0.0;
			float f_LightNom = 0.0;

			vec3 vnNormal = normalize(vNormal);

			vec4 f_Color = texture2D(uTexture, vTexCoord);
			vec4 f_AmbientColor = f_Color;
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			float f_qsX = rand(vec3(uSeed * vPosition.x * vPosition.y * vPosition.z));
			//float f_qsY = rand(vec3(f_qsX));
			//float f_qsZ = rand(vec3(f_qsY));

			vec4 randElement = vec4(f_qsX * 0.2, f_qsX * 0.2, f_qsX * 0.2, 1.0);

			vec3 f_SunLightPos = vec3(300.0, 30000.0, 1850.0);
			vec4 f_SunLightColor = vec4(0.93, 0.88, 0.80, 1.0);

			f_SunLightColor = (f_SunLightColor * 0.95) + (randElement * 0.05);

			float f_SunRadius = 100000.0;

			vec3 f_L = (f_SunLightPos + vPos) - vPosition;
			vec3 L = normalize(f_L);
			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(vnNormal, L), 0.0), 1.0);
			Idiff = clamp(Idiff, 0.0, 1.0);
			Idiff *= 0.03;

			float f_SunDistanceL = sqrt(dot(f_L, f_L));

			vec4 f_SunAccumulationBuffer = (Idiff * ((f_SunRadius) / f_SunDistanceL)) * 20.0;
			f_SunLightNom += 1.0;

			float f_ProcCount = 0.0;
			for(int f_i = 0; f_i < 10; f_i++)
				{
				if(f_ProcCount < uLightNom)
					{
					if(uLightPos[f_i].w > 0.0)
						{
						vec3 f_LightPos = uLightPos[f_i].xyz;

						vec3 f_Li = (f_LightPos + vPos) - vPosition;
						vec3 Li = normalize(f_Li);
						vec4 Idiffi = vec4(uLightColor[f_i].rgb * max(dot(vnNormal, Li), 0.0), 1.0);
						Idiffi = clamp(Idiffi, 0.0, 1.0);

						float f_LightDistance = 0.01;
						float f_Lengthi = sqrt(dot(f_Li, f_Li));

						float f_Diffi = uLightPos[f_i].w - (f_Lengthi / uLightColor[f_i].a);
						f_Diffi = f_Diffi * f_LightDistance;
						Idiffi = Idiffi * f_Diffi;

						f_AccumulationBuffer += Idiffi;

						float f_Intensity = 0.4;
						float f_IntenseInvert = (1.0 - f_Intensity) * 5.0;

						f_LightNom += 1.0 * f_IntenseInvert;
						}
					}

				f_ProcCount += 1.0;
				}

			vec4 f_Result = vec4(0.0, 0.0, 0.0, 0.0);
			float f_sunamp = 0.5;
			float f_amp = 0.5;

			f_Result.r += (f_SunAccumulationBuffer.r / (f_SunLightNom)) * f_sunamp;
			f_Result.g += (f_SunAccumulationBuffer.g / (f_SunLightNom)) * f_sunamp;
			f_Result.b += (f_SunAccumulationBuffer.b / (f_SunLightNom)) * f_sunamp;
			f_Result.a += (f_SunAccumulationBuffer.a / (f_SunLightNom)) * f_sunamp;


			if(f_LightNom >= 1.0)
				{
				f_Result.r += (f_AccumulationBuffer.r / (f_LightNom)) * f_amp;
				f_Result.g += (f_AccumulationBuffer.g / (f_LightNom)) * f_amp;
				f_Result.b += (f_AccumulationBuffer.b / (f_LightNom)) * f_amp;
				f_Result.a += (f_AccumulationBuffer.a / (f_LightNom)) * f_amp;
				}

			f_Result.a = 1.0;

			gl_FragColor = (f_AmbientColor * f_Result) + (uTeam / 3.0);
			gl_FragColor.a = 1.0;
			}
		);
#endif

#if 0
	const std::string vs_mesh = STRING
		(
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 avatarTrans;
		uniform vec4 cameraTrans;

		attribute vec4 aPosition;
		attribute vec4 aNormal;
		attribute vec2 aTexCoord;
		attribute vec4 aWeight;
		attribute vec4 aMatrixIndices;

		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;

		void main()
			{
			vec4 tempPos = aPosition;
			vec3 tempNor = aNormal.xyz;

			vec4 pos;
			vec3 normal;

			pos = aPosition;
			//pos.xyz *= cameraTrans.w;

			vec4 f_interim = uModelMatrix * pos;

			f_interim.x += avatarTrans.x;
			f_interim.y += avatarTrans.y;
			f_interim.z += avatarTrans.z;

			vPosition = f_interim.xyz;

			gl_Position = uProjMatrix * uViewMatrix * f_interim;

			vNormal = normalize(normal);
			vec4 f_Norm = vec4(vNormal.xyz, 1.0);
			f_Norm = uModelMatrix * f_Norm;
			vNormal = f_Norm.xyz;
            vColor = vec4(1,1,1,1);
			vPos = cameraTrans.xyz;
			}
		);

    // Fragment Shader source
    const std::string fs_mesh = STRING
		(
        precision mediump float;

		uniform sampler2D f_texture;

        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec3 vPos;

		uniform vec4 uTeam;
		uniform vec4 uLightPos[10];
		uniform vec4 uLightColor[10];

        void main()
			{
			vec4 f_Color = texture2D(f_texture, vTexCoord);
			vec4 f_AmbientColor = f_Color * 0.4;
			vec4 f_AccumulationBuffer = vec4(0.0, 0.0, 0.0, 0.0);

			vec3 f_SunLightPos = vec3(-50.0, 700.0, 50.0);
			vec4 f_SunLightColor = vec4(0.83, 0.65, 0.33, 9.0);
			float f_SunRadius = 1025.0;
			float f_SunDistance = 0.001;

			vec3 f_L = (f_SunLightPos + vPos) - vPosition;
			vec3 L = normalize(f_L);
			vec4 Idiff = vec4(f_SunLightColor.rgb * max(dot(vNormal, L), 0.0), 1.0);
			Idiff = clamp(Idiff, 0.0, 1.0);

			float f_Length = sqrt(dot(f_L, f_L));
			float f_Diff = f_SunRadius - (f_Length / f_SunLightColor.a);
			f_Diff = f_Diff * f_SunDistance;
			Idiff = Idiff * f_Diff;

			float f_LightNom = 0.0;

			if(f_Diff > 0.0)
				{
				f_AccumulationBuffer += Idiff;
				f_LightNom += 1.0;
				}

			for(int f_i = 0; f_i < 10; f_i++)
				{
				vec3 f_LightPos = uLightPos[f_i].xyz;
				vec3 f_Li = (f_LightPos - vPos) - vPosition;
				vec3 Li = normalize(f_Li);
				vec4 Idiffi = vec4(uLightColor[f_i].rgb * max(dot(vNormal, Li), 0.0), 1.0);
				Idiffi = clamp(Idiffi, 0.0, 1.0);

				float f_LightDistance = 0.01;
				float f_Lengthi = sqrt(dot(f_Li, f_Li));
				float f_Diffi = uLightPos[f_i].w - (f_Lengthi / uLightColor[f_i].a);
				f_Diffi = f_Diffi * f_LightDistance;
				Idiffi = Idiffi * f_Diffi;

				if(f_Diffi > 0.0)
					{
					f_AccumulationBuffer += Idiffi;
					f_LightNom += 1.0;
					}
				}

			vec4 f_Result = vec4(0.0, 0.0, 0.0, 0.0);
			f_Result.r = (f_AccumulationBuffer.r / (f_LightNom + 1.0));
			f_Result.g = (f_AccumulationBuffer.g / (f_LightNom + 1.0));
			f_Result.b = (f_AccumulationBuffer.b / (f_LightNom + 1.0));
			f_Result.a = (f_AccumulationBuffer.a / (f_LightNom + 1.0));
			gl_FragColor = ((f_AmbientColor * 0.75) + (f_Result * 2.8)) + uTeam;
			}
		);
#endif

    // Set up the shader and its uniform/attribute locations.
    mProgram = acProgram(vs, fs);

	mModelUniformLocation = glGetUniformLocation(mProgram, "uModelMatrix");
	mViewUniformLocation = glGetUniformLocation(mProgram, "uViewMatrix");
	mProjUniformLocation = glGetUniformLocation(mProgram, "uProjMatrix");
	mMatricesUniformLocation = glGetUniformLocation(mProgram, "rotationMatrices");
	mAvatarTranslationUniformLocation = glGetUniformLocation(mProgram, "avatarTrans");

    m0AttribLocation = glGetAttribLocation(mProgram, "aPosition");
    m1AttribLocation = glGetAttribLocation(mProgram, "aWeight");
	m2AttribLocation = glGetAttribLocation(mProgram, "aNormal");
	m3AttribLocation = glGetAttribLocation(mProgram, "aMatrixIndices");
	m4AttribLocation = glGetAttribLocation(mProgram, "aTexCoord");
	
	mTextureUniformLocation = glGetUniformLocation(mProgram, "uTexture");
	mTeamUniformLocation = glGetUniformLocation(mProgram, "uTeam");
	mLightPosUniformLocation = glGetUniformLocation(mProgram, "uLightPos");
	mLightColorUniformLocation = glGetUniformLocation(mProgram, "uLightColor");
	mLightNomUniformLocation = glGetUniformLocation(mProgram, "uLightNom");
	mTimeUniformLocation = glGetUniformLocation(mProgram, "uSeed");

#if 0
	const std::string elvs = STRING
    (
        uniform mat4 uModelMatrix;
        uniform mat4 uViewMatrix;
        uniform mat4 uProjMatrix;
		uniform vec4 uLightPos;

		attribute vec3 aPosition;
		attribute vec4 aColor;
		attribute vec2 aTexCoord;

		varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;

		void main()
			{
			vec4 pos = vec4(aPosition, 1.0);

			vNormal = vec3(0.0, 0.0, -1.0);

			gl_Position = pos; // uProjMatrix * uViewMatrix * pos;
			//gl_Position.z = 0.0;
			vLightPos = uLightPos;
            vColor = aColor;
			//vPosition = gl_Position.xyz;
			}
		);

    // Fragment Shader source
    const std::string elfs = STRING
		(
        precision mediump float;

		uniform sampler2D f_texture;

        varying vec4 vColor;
		varying vec3 vNormal;
		varying vec3 vPosition;
		varying vec2 vTexCoord;
		varying vec4 vLightPos;

        void main()
			{
			vec4 f_Color = texture2D(f_texture, vTexCoord);

			f_Color.r += vColor.r;
			f_Color.g += vColor.g;
			f_Color.b += vColor.b;
			f_Color.a += vColor.a;

			vec4 f_AmbientColor = f_Color * 0.4;

			vec4 fLightPos = vLightPos;

			vec4 f_LightColor = vec4(10.3, 17.7, 10.1, 1.0);

			vec3 L = normalize(fLightPos.xyz - vPosition);
			vec4 Idiff = f_LightColor * max(dot(vNormal, L), 0.0);
			Idiff = clamp(Idiff, 0.0, 1.0);

			gl_FragColor = f_AmbientColor + (f_Color * Idiff);
			gl_FragColor.a *= vColor.a;

			gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
			}
		);
#endif

#if 0
	g_ElementBank = new unElementBank();

    // Set up the shader and its uniform/attribute locations.
    g_ElementBank->mElProgram = acProgram(elvs, elfs);

	g_ElementBank->m0ElVertexAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aPosition");
	g_ElementBank->m1ElColorAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aColor");
	g_ElementBank->m2ElTexCoordAttribLocation = glGetAttribLocation(g_ElementBank->mElProgram, "aTexCoord");

	g_ElementBank->mElModelUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uModelMatrix");
	g_ElementBank->mElViewUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uViewMatrix");
	g_ElementBank->mElProjUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uProjMatrix");

	g_ElementBank->mElTextureUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "f_texture");
	g_ElementBank->mElLightPosUniformLocation = glGetUniformLocation(g_ElementBank->mElProgram, "uLightPos");
#endif

    // Then set up the cube geometry.
    GLfloat vertexPositions[] =
		{
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
		};

    glGenBuffers(1, &mVertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLfloat vertexColors[] =
    {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
    };

    glGenBuffers(1, &mVertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    short indices[] =
    {
        0, 1, 2, // -x
        1, 3, 2,

        4, 6, 5, // +x
        5, 6, 7,

        0, 5, 1, // -y
        0, 4, 5,

        2, 7, 6, // +y
        2, 3, 7,
              
        0, 6, 4, // -z
        0, 2, 6,
              
        1, 7, 3, // +z
        1, 5, 7,
    };

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#if 0
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

		m_frag_shadow = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"normal_mesh",
				(const char **)m_frag_options);

		checkError("normal_mesh", "cgCreateProgram");

		m_frag_terrain = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"mrt_normal_terrain",
				(const char **)m_frag_options);

		checkError("mrt_normal_terrain", "cgCreateProgram");

		m_frag_alpha = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE,programtext,
				CG_PROFILE_ARBFP1,
				"alpha_avatar",
				(const char **)m_frag_options);

		checkError("alpha_avatar", "cgCreateProgram");

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

			//*cgGLLoadProgram(m_frag_shadow);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_terrain);
			CgCheckError();

			//*cgGLLoadProgram(m_frag_alpha);
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
			m_terrainsampler=cgGetNamedParameter(m_vert_terrain,"PhysicsSamp");
			m_terrainwidth=cgGetNamedParameter(m_vert_terrain,"texwidth");

			m_meshcolormap=cgGetNamedParameter(m_frag_mesh,"colortex");
			m_meshAmbient=cgGetNamedParameter(m_frag_mesh,"f_Ambient");
			m_meshDiffuse=cgGetNamedParameter(m_frag_mesh,"f_Diffuse");
			m_meshSpecular=cgGetNamedParameter(m_frag_mesh,"f_Specular");
			m_meshLightVec=cgGetNamedParameter(m_frag_mesh,"f_LightVec");
			m_meshEyeVec=cgGetNamedParameter(m_frag_mesh,"f_EyeVec");
			m_meshAlpha=cgGetNamedParameter(m_frag_mesh,"f_Alpha");

			m_shadowcolormap=cgGetNamedParameter(m_frag_shadow,"colortex");
			m_shadowAmbient=cgGetNamedParameter(m_frag_shadow,"f_Ambient");
			m_shadowDiffuse=cgGetNamedParameter(m_frag_shadow,"f_Diffuse");
			m_shadowSpecular=cgGetNamedParameter(m_frag_shadow,"f_Specular");
			m_shadowLightVec=cgGetNamedParameter(m_frag_shadow,"f_LightVec");
			m_shadowEyeVec=cgGetNamedParameter(m_frag_shadow,"f_EyeVec");
			m_shadowAlpha=cgGetNamedParameter(m_frag_shadow,"f_Alpha");

			m_terraincolormap=cgGetNamedParameter(m_frag_terrain,"colortex");
			m_terrainAmbient=cgGetNamedParameter(m_frag_terrain,"f_Ambient");
			m_terrainDiffuse=cgGetNamedParameter(m_frag_terrain,"f_Diffuse");
			m_terrainSpecular=cgGetNamedParameter(m_frag_terrain,"f_Specular");
			m_terrainLightVec=cgGetNamedParameter(m_frag_terrain,"f_LightVec");
			m_terrainEyeVec=cgGetNamedParameter(m_frag_terrain,"f_EyeVec");
			m_terrainAlpha=cgGetNamedParameter(m_frag_terrain,"f_Alpha");

#if 0
			m_alphadepthmap=cgGetNamedParameter(m_frag_alpha,"depthtex");
			m_alphacolormap=cgGetNamedParameter(m_frag_alpha,"colortex");
#endif

			m_alphaAmbient=cgGetNamedParameter(m_frag_alpha,"f_Ambient");
			m_alphaDiffuse=cgGetNamedParameter(m_frag_alpha,"f_Diffuse");
			m_alphaSpecular=cgGetNamedParameter(m_frag_alpha,"f_Specular");
			m_alphaLightVec=cgGetNamedParameter(m_frag_alpha,"f_LightVec");
			m_alphaEyeVec=cgGetNamedParameter(m_frag_alpha,"f_EyeVec");
			m_alphaAlpha=cgGetNamedParameter(m_frag_alpha,"f_Alpha");
			m_alphaPlanes=cgGetNamedParameter(m_frag_alpha,"f_Planes");
			m_alphaView=cgGetNamedParameter(m_frag_alpha,"f_View");

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

			if(!m_shadowcolormap) printf("ERROR:::LoadPrograms m_shadowcolormap parameter not found\n");
			if(!m_shadowAmbient) printf("ERROR:::LoadPrograms m_shadowAmbient parameter not found\n");
			if(!m_shadowDiffuse) printf("ERROR:::LoadPrograms m_shadowDiffuse parameter not found\n");
			if(!m_shadowSpecular) printf("ERROR:::LoadPrograms m_shadowSpecular parameter not found\n");
			if(!m_shadowLightVec) printf("ERROR:::LoadPrograms m_shadowLightVec parameter not found\n");
			if(!m_shadowEyeVec) printf("ERROR:::LoadPrograms m_shadowEyeVec parameter not found\n");
			if(!m_shadowAlpha) printf("ERROR:::LoadPrograms m_shadowAlpha parameter not found\n");

			if(!m_terraincolormap) printf("ERROR:::LoadPrograms m_terraincolormap parameter not found\n");
			if(!m_terrainAmbient) printf("ERROR:::LoadPrograms m_terrainAmbient parameter not found\n");
			if(!m_terrainDiffuse) printf("ERROR:::LoadPrograms m_terrainDiffuse parameter not found\n");
			if(!m_terrainSpecular) printf("ERROR:::LoadPrograms m_terrainSpecular parameter not found\n");
			if(!m_terrainLightVec) printf("ERROR:::LoadPrograms m_terrainLightVec parameter not found\n");
			if(!m_terrainEyeVec) printf("ERROR:::LoadPrograms m_terrainEyeVec parameter not found\n");
			if(!m_terrainAlpha) printf("ERROR:::LoadPrograms m_terrainAlpha parameter not found\n");

			if(!m_alphadepthmap) printf("ERROR:::LoadPrograms m_alphadepthmap parameter not found\n");
			if(!m_alphacolormap) printf("ERROR:::LoadPrograms m_alphacolormap parameter not found\n");
			if(!m_alphaAmbient) printf("ERROR:::LoadPrograms m_alphaAmbient parameter not found\n");
			if(!m_alphaDiffuse) printf("ERROR:::LoadPrograms m_alphaDiffuse parameter not found\n");
			if(!m_alphaSpecular) printf("ERROR:::LoadPrograms m_alphaSpecular parameter not found\n");
			if(!m_alphaLightVec) printf("ERROR:::LoadPrograms m_alphaLightVec parameter not found\n");
			if(!m_alphaEyeVec) printf("ERROR:::LoadPrograms m_alphaEyeVec parameter not found\n");
			if(!m_alphaAlpha) printf("ERROR:::LoadPrograms m_alphaAlpha parameter not found\n");
			if(!m_alphaPlanes) printf("ERROR:::LoadPrograms m_alphaPlanes parameter not found\n");
			if(!m_alphaView) printf("ERROR:::LoadPrograms m_alphaView parameter not found\n");

			if(!m_terraintile) printf("ERROR:::LoadPrograms tile parameter not found\n");
			if(!m_terraindepth) printf("ERROR:::LoadPrograms depth parameter not found\n");
			if(!m_terrainsampler) printf("ERROR:::LoadPrograms terrain sampler parameter not found\n");
			if(!m_terrainwidth) printf("ERROR:::LoadPrograms terrain physics texture width parameter not found\n");

			m_ndiffuse=cgGetNamedParameter(m_frag_prog_normal,"diffuse");
			m_nspecular=cgGetNamedParameter(m_frag_prog_normal,"specular");
			m_nplanes=cgGetNamedParameter(m_frag_prog_normal,"planes");
			m_rdiffuse=cgGetNamedParameter(m_frag_prog_relief,"diffuse");
			m_rspecular=cgGetNamedParameter(m_frag_prog_relief,"specular");
			m_rplanes=cgGetNamedParameter(m_frag_prog_relief,"planes");
			m_stepmap=cgGetNamedParameter(m_frag_prog_relief,"stepmap");
			m_rtdepth=cgGetNamedParameter(m_frag_prog_relief,"rtdepth");

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

	//AST-
	//////- SHADER AROUND ALOT -/////
	pString f_Shader_Around_Vertex_PATH;
	pString f_Shader_Around_Fragment_PATH;
	f_Shader_Around_Vertex_PATH.format("shaders\\Cg\\cg_ssao_vert.cg",
										(const char *)g_render->app_path,
										(const char *)g_render->shader_path);
	f_Shader_Around_Fragment_PATH.format("shaders\\Cg\\cg_around_agi_frag.cg",
										(const char *)g_render->app_path,
										(const char *)g_render->shader_path);
	char *f_Shader_Around_Vertex_ProgramText = LoadTextFile(f_Shader_Around_Vertex_PATH);
	char *f_Shader_Around_Fragment_ProgramText = LoadTextFile(f_Shader_Around_Fragment_PATH);

	if(f_Shader_Around_Vertex_ProgramText)
		{
		//aroundVertProfile = cgGetProfile("glslv");
		aroundVertProfile = CG_PROFILE_ARBVP1;
		//aroundVertProfile = //*cgGLGetLatestProfile(CG_GL_VERTEX);
 
		// Validate Our Profile Determination Was Successful
		if (aroundVertProfile == CG_PROFILE_UNKNOWN)
			{
		//	MessageBox(NULL, "Invalid profile type ref vertex ssao", "Error", MB_OK);
			return FALSE;                               // We Cannot Continue
			}

		////*cgGLSetOptimalOptions(ssaoVertProfile);

		checkError("Get Profile", "selecting aroundVertProfile profile");

		m_vert_around_agi = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE, f_Shader_Around_Vertex_ProgramText,
				aroundVertProfile,
				"view_ssao",
				(const char **)m_vert_options);

		checkError("view_ssao", "cgCreateProgram");

		if(m_vert_around_agi)
			{
			//*cgGLLoadProgram(m_vert_around_agi);
			CgCheckError();
			}
		}

	count = 0;
	if(f_Shader_Around_Fragment_ProgramText)
		{
		//aroundFragProfile = cgGetProfile("glslf");
		aroundFragProfile = CG_PROFILE_ARBFP1;
		//aroundFragProfile = //*cgGLGetLatestProfile(CG_GL_FRAGMENT);
 
		// Validate Our Profile Determination Was Successful
		if(aroundFragProfile == CG_PROFILE_UNKNOWN)
			{
//			MessageBox(NULL, "Invalid profile type aroundFragProfile", "Error", MB_OK);
			return FALSE;                               // We Cannot Continue
			}

		//*cgGLSetOptimalOptions(aroundFragProfile);

		checkError("Get Profile", "selecting aroundFragProfile profile");

		m_frag_around_agi = cgCreateProgram(
				g_render->cgcontext,
				CG_SOURCE, f_Shader_Around_Fragment_ProgramText,
				aroundFragProfile,
				"mrt_around_agi",
				(const char **)m_frag_options);

		checkError("m_frag_around_agi", "cgCreateProgram");

		if(m_frag_around_agi)
			{
			//*cgGLLoadProgram(m_frag_around_agi);
			CgCheckError();

			m_around_sampoints = cgGetNamedParameter(m_frag_around_agi, "points");
			m_around_white_out = cgGetNamedParameter(m_frag_around_agi, "whiteout");
			m_around_seedst = cgGetNamedParameter(m_frag_around_agi, "seedst");
			m_around_ScreenWidth = cgGetNamedParameter(m_frag_around_agi, "g_ScreenWidth");
			m_around_ScreenHeight = cgGetNamedParameter(m_frag_around_agi, "g_ScreenHeight");
			m_around_ScreenDepth = cgGetNamedParameter(m_frag_around_agi, "g_ScreenDepth");
			m_around_var_Final_Attenuation = cgGetNamedParameter(m_frag_around_agi, "var_Final_Attenuation");
			m_around_var_Radius123_Boost = cgGetNamedParameter(m_frag_around_agi, "var_Radius123_Boost");
			m_around_var_Cutoff_Threshold = cgGetNamedParameter(m_frag_around_agi, "var_Cutoff_Threshold");

			if(!m_around_sampoints) printf("ERROR:::LoadPrograms m_around_sampoints parameter not found\n");
			if(!m_around_white_out) printf("ERROR:::LoadPrograms m_around_white_out parameter not found\n");
			if(!m_around_seedst) printf("ERROR:::LoadPrograms m_around_seedst parameter not found\n");
			if(!m_around_ScreenWidth) printf("ERROR:::LoadPrograms m_around_ScreenWidth parameter not found\n");
			if(!m_around_ScreenHeight) printf("ERROR:::LoadPrograms m_around_ScreenHeight parameter not found\n");
			if(!m_around_ScreenDepth) printf("ERROR:::LoadPrograms m_around_ScreenDepth parameter not found\n");
			if(!m_around_var_Final_Attenuation) printf("ERROR:::LoadPrograms m_around_var_Final_Attenuation parameter not found\n");
			if(!m_around_var_Radius123_Boost) printf("ERROR:::LoadPrograms m_around_var_Radius123_Boost parameter not found\n");
			if(!m_around_var_Cutoff_Threshold) printf("ERROR:::LoadPrograms m_around_var_Cutoff_Threshold parameter not found\n");
			}
		}

	int tex;
	tex=g_render->build_onepixelmap(255,255,255);
	m_null_color=g_render->picid[tex];
	tex=g_render->build_onepixelmap(128,128,255);
	m_null_normal=g_render->picid[tex];
#endif
#if 0
	unConsoleReset();

	///// Reflective Shadow Mapping /////
#if 0
	m_RSM = new RSM();
#endif

	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk();

	//QActiveFrameWork.Acquire("GlobalQActiveFrameWork");
	//QActiveFrameWork = new QAGE::QActiveFramewrk();

	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	//DigiMass.Acquire("GlobalDigiMass");
	//DigiMass = new Digi::DigiMassCore();

	//*QActiveFrameWork->DigiMass = new DigiMassCore();
	//*QActiveFrameWork->DigiMass->Start();

	playerAV.Allocate("playerAV");//, Q_PlacementMarker->m_Count);

	QActiveFrameWork->acActiveInit();

	//for(int i = 0; i < 500; i++) Digi::CreateCube(PxVec3(((rand()%50)-25), ((rand()%50)-25), ((rand()%50)-25)),1);
	//for(int i = 0; i < 200; i++) DigiMass->acCreateCube(PxVec3(((rand()%500)-250), 125, ((rand()%500)-250)), 1);

#ifndef QAGE_OPMOD_B

	//f_CSpeechDlg = new CSpeechDlg();
	//f_CSpeechDlg->acInit();

	//f_OsirusCore = new OSI::OsirusCore();

#if 0
	f_OsirusCore->acTest();
#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

	//UNMessageCore->m_memorymanager->acLockModule("Unification.exe");

	//UNMessageCore->m_memorymanager->acSetPriority();

	// Test Engine Dynamic Shapes
	//f_ShapeBank.Acquire("GlobalShapeBank");

#if 0
	f_ShapeBank = new UN::unShapeBank();

#if 1
	f_ShapeBank->acCreateShape(UN_SHAPE_SPHERE, 50);
#endif
#endif

	//f_ShapeBank->acAddInstance(0, 0, 0, 0);

	//f_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
	//f_shape.Acquire("Globalshape");

#if 0
#if 1
	QActiveFrameWork->m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);

#if 0
	QActiveFrameWork->m_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");
#endif
	QActiveFrameWork->m_trrCell->acLoad(0, 0, 0, 0, 0, NULL);

#if 1
	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->m_trrCell, 12, false);
	QActiveFrameWork->f_TrrBank->acAddInstance(0, 0, 0, 0);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif
#endif

	QActiveFrameWork->DigiMass->incInternalState();
#endif

	//*QActiveFrameWork->DigiMass->acWait(DIGI_START);

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridTwo(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

#if 0
	QActiveFrameWork->DigiMass->acStartEngine();

	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[1]);
	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[2]);
	QActiveFrameWork->DigiMass->m_Engine.acCloseModels();

	QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
	QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
#endif

	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 12, false);

	//### Load Center Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridOne(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 13, false);

#if 0
	QActiveFrameWork->f_TrrBank->acAddInstance(1, 0, 0, 0);
#endif

	//### Load Empty Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridThree(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 14, false);

	//### Load Hut Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridFour(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 15, false);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(1, 0, 0, 0, 12);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif

#if 0
	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);
	float f_xslt;
	float f_zslt;
	int f_value = 5;
	int f_ins = 18;
	int f_counter = 1;

	/// ----- Rings in the Dirt ----- ///
	for(int f_count = 2; f_count < 7; f_count++)
		{
		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -(f_gridincrement * f_count);

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = f_gridincrement * f_count;

		for(int xdir = 0; xdir < f_value; xdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt + (f_gridincrement * xdir), 0, f_zslt, f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt + (f_gridincrement * xdir);
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt;
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = -(f_gridincrement * f_count);
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 20;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_xslt = f_gridincrement * f_count;
		f_zslt = -((f_gridincrement * f_count) - f_gridincrement);

		for(int zdir = 0; zdir < f_value - 2; zdir++)
			{
			float f_finger = ((float)rand() / 32767) * 10;

			///### Empty Square ###///
			//if(f_finger >= 0 && f_finger < 18.35) QActiveFrameWork->f_TrrBank->acAddClone(2, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

			///### Spawn Hut Square ###///
			if(f_finger >= 18.35 && f_finger < 20)
				{
				//QActiveFrameWork->f_TrrBank->acAddClone(3, f_xslt, 0, f_zslt + (f_gridincrement * zdir), f_ins);

				QAGE::QSpawnPoint *f_SpawnPoint = new QAGE::QSpawnPoint(f_counter);
				f_SpawnPoint->m_CellCenter.x = f_xslt;
				f_SpawnPoint->m_CellCenter.y = 0;
				f_SpawnPoint->m_CellCenter.z = f_zslt + (f_gridincrement * zdir);
				QActiveFrameWork->m_QSpawnPntController->m_SpawnPoint.push_back(f_SpawnPoint);
				f_counter++;
				}

			f_ins++;
			}

		f_value += 2;
		}
#endif

	//*QActiveFrameWork->DigiMass->incInternalState();

	//*QActiveFrameWork->DigiMass->m_Engine.acSetState(2, 3);


	////////====-- Set Shadow Effect Scales --====////////
								// 11
	player[g_Player]->ShadowEffect_Counter = 11;
								//  2.0
	player[g_Player]->ShadowEffect_Scale[0] = 2.0;
	player[g_Player]->ShadowEffect_Scale[1] = 1.9;
	player[g_Player]->ShadowEffect_Scale[2] = 1.8;
	player[g_Player]->ShadowEffect_Scale[3] = 1.7;
	player[g_Player]->ShadowEffect_Scale[4] = 1.6;
	player[g_Player]->ShadowEffect_Scale[5] = 1.5;
	player[g_Player]->ShadowEffect_Scale[6] = 1.4;
	player[g_Player]->ShadowEffect_Scale[7] = 1.3;
	player[g_Player]->ShadowEffect_Scale[8] = 1.2;
	player[g_Player]->ShadowEffect_Scale[9] = 1.1;
	player[g_Player]->ShadowEffect_Scale[10] = 1;

#if 0
#if 0
	m_TestModel = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]);
#else
	m_TestModel = g_render->load_mesh(meshfile);
#endif

	m_TestModel->nlight = 0;
#endif

	TCHAR szDirectory[255];
	if(!::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory))
		{
		printf("GetDirectoryERROR Cant find current directory\n");
		for(;;) {}
		}

	std::cout << "Current Directory ::: " << szDirectory << "'..." << std::endl;
	//TCHAR pstrDirName[PATH_STR] = "C:\Projects Base\Rapid3DRenderer";
	//SetCurrentDirectory(pstrDirName);

	// Set App Path
	//g_render->set_app_path(szDirectory);
	
	//_->mesh = g_render->load_mesh(meshfilehe, 8.0f);

	for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
		{
		_->mesh->cam[f_gap].pos.y += 705;
		}

#if 0
	_->mesh = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]);
#endif

	//_->mesh->nlight = 0;

#if 0
	terrainMaterial = &_->mesh->mat[_->mesh->face[5].material];
#endif

	//BlurTexture = EmptyTexture();
#endif

	return true;
}

void unRenderer::acInit(void)
{
	///// Active Framework /////
	QActiveFrameWork = new QAGE::QActiveFramewrk();

	QNetwork.Initialize();

	///// DigiMass /////
	//~~~Initialize the Digital Mass Library
	//DigiMass.Acquire("GlobalDigiMass");
	//DigiMass = new Digi::DigiMassCore();

	//*QActiveFrameWork->DigiMass = new DigiMassCore();
	//*QActiveFrameWork->DigiMass->Start();

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		playerAV[g_Player].Allocate("playerAV");//, Q_PlacementMarker->m_Count);
		}

	g_Player = 0;

	QActiveFrameWork->acActiveInit();

#ifndef QAGE_OPMOD_B

	//f_CSpeechDlg = new CSpeechDlg();
	//f_CSpeechDlg->acInit();

	//f_OsirusCore = new OSI::OsirusCore();

#if 0
	f_OsirusCore->acTest();
#endif

	//UNMessageCore = new UN::unMessageCore(g_render->hwnd);

	//UNMessageCore->m_memorymanager->acLockModule("Unification.exe");

	//UNMessageCore->m_memorymanager->acSetPriority();

#endif

	// Test Engine Dynamic Shapes
#if 0
	f_ShapeBank = new UN::unShapeBank();

	f_ShapeBank->acCreateShape(UN_SHAPE_SPHERE, 50);
#endif

	//f_ShapeBank->acAddInstance(0, 0, 0, 0);

	//f_shape = new UN::unShape(UN_SHAPE_CUBE, 109, 10);
	//f_shape.Acquire("Globalshape");

#if 0
#if 1
	QActiveFrameWork->m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);

#if 0
	QActiveFrameWork->m_trrCell->acLoad(0, 0, "Data/Terrain/foundation.trr");
#endif
	QActiveFrameWork->m_trrCell->acLoad(0, 0, 0, 0, 0, NULL);

#if 1
	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->m_trrCell, 12, false);
	QActiveFrameWork->f_TrrBank->acAddInstance(0, 0, 0, 0);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif
#endif

	QActiveFrameWork->DigiMass->incInternalState();
#endif

	//*QActiveFrameWork->DigiMass->acWait(DIGI_START);

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridTwo(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

#if 0
	QActiveFrameWork->DigiMass->acStartEngine();

	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[1]);
	QActiveFrameWork->DigiMass->m_Engine.acPushOpen(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->veclayer[2]);
	QActiveFrameWork->DigiMass->m_Engine.acCloseModels();

	QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
	QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]->m_Floor = QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_Floor;
#endif

	QActiveFrameWork->f_TrrBank = new trr::unTrrBank();
	QActiveFrameWork->f_TrrBank->acSetDimensions(QActiveFrameWork->DigiMass->m_Engine.m_trrCell->m_fdim);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 12, false);

	//### Load Center Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridOne(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 13, false);

#if 0
	QActiveFrameWork->f_TrrBank->acAddInstance(1, 0, 0, 0);
#endif

	//### Load Empty Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridThree(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 14, false);

	//### Load Hut Piece ###//
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell = new unTerrainCell(TRR_SPLIT_BUFFERS, TRR_GRID_SIZE, TRR_GRID_SIZE);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acPrepGridFour(NULL);

	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadMin(0, 0, 0, 0, 0);
	QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acLoadExt(0, 0, 0, 0, 0);

	QActiveFrameWork->f_TrrBank->acServeBank(QActiveFrameWork->DigiMass->m_Engine.m_trrCell, 15, false);

	float f_gridincrement = (TCELL_GRID_SIZE * TCELL_GRID_SCALE) - (TCELL_GRID_SCALE);

	QActiveFrameWork->f_TrrBank->acAddClone(1, 0, 0, 0, 12);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, 0, 13);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, 0, 11);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, f_gridincrement, 7);
	QActiveFrameWork->f_TrrBank->acAddClone(0, 0, 0, -f_gridincrement, 17);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, f_gridincrement, 6);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, f_gridincrement, 8);
	QActiveFrameWork->f_TrrBank->acAddClone(0, f_gridincrement, 0, -f_gridincrement, 16);
	QActiveFrameWork->f_TrrBank->acAddClone(0, -f_gridincrement, 0, -f_gridincrement, 18);
#endif

	//*QActiveFrameWork->DigiMass->incInternalState();

	//*QActiveFrameWork->DigiMass->m_Engine.acSetState(2, 3);

	////////====-- Set Shadow Effect Scales --====////////
								// 11
	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		player[g_Player]->ShadowEffect_Counter = 11;
		//  2.0
		player[g_Player]->ShadowEffect_Scale[0] = 2.0;
		player[g_Player]->ShadowEffect_Scale[1] = 1.9;
		player[g_Player]->ShadowEffect_Scale[2] = 1.8;
		player[g_Player]->ShadowEffect_Scale[3] = 1.7;
		player[g_Player]->ShadowEffect_Scale[4] = 1.6;
		player[g_Player]->ShadowEffect_Scale[5] = 1.5;
		player[g_Player]->ShadowEffect_Scale[6] = 1.4;
		player[g_Player]->ShadowEffect_Scale[7] = 1.3;
		player[g_Player]->ShadowEffect_Scale[8] = 1.2;
		player[g_Player]->ShadowEffect_Scale[9] = 1.1;
		player[g_Player]->ShadowEffect_Scale[10] = 1;
		}

	g_Player = 0;

#if 0
#if 0
	m_TestModel = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[1]);
#else
	m_TestModel = g_render->load_mesh(meshfile);
#endif

	m_TestModel->nlight = 0;
#endif

#if 0
	TCHAR szDirectory[255];
	if(!::GetCurrentDirectory(sizeof(szDirectory) - 1, szDirectory))
		{
		printf("GetDirectoryERROR Cant find current directory\n");
		for(;;) {}
		}

	std::cout << "Current Directory ::: " << szDirectory << "'..." << std::endl;
	//TCHAR pstrDirName[PATH_STR] = "C:\Projects Base\Rapid3DRenderer";
	//SetCurrentDirectory(pstrDirName);

	// Set App Path
	//g_render->set_app_path(szDirectory);
	
	//_->mesh = g_render->load_mesh(meshfilehe, 8.0f);
#endif

#if 0
	_->mesh = g_render->load_mesh_digimodel(m_Testmeshfile, QActiveFrameWork->DigiMass->m_Engine.vec_Model[0]);

	_->mesh->nlight = 0;

	terrainMaterial = &_->mesh->mat[_->mesh->face[5].material];

	BlurTexture = EmptyTexture();
#endif
}

//Issue Start Command
void unRenderer::sync_PhysicsMemory(void)
{
	//*m_VehicleCount = QActiveFrameWork->DigiMass->getVehicleCount();

	//printf("trace m_VehicleCount %i\n", m_VehicleCount);

	printf("--//  User loaded...       //\n");
	printf("-//  Issue Start Command  //-\n");
	printf("// Start Command!        //--\n");

	g_LOAD = true;
}

void unRenderer::free_programs()
{
	/*if (m_vert_prog)
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

	m_frag_prog_antialias=0;*/
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

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,0);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,0);
}

void unRenderer::bind_mesh_normal()
{
	//*cgGLBindProgram(m_frag_prog_normal);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
}

void unRenderer::unbind_mesh_normal()
{
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,0);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
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

//AST-
void unRenderer::bind_around(void)
{
	//*cgGLBindProgram(m_frag_around_agi);
	//*cgGLEnableProfile(aroundFragProfile);

#if 0
	//*cgGLBindProgram(m_vert_around_agi);
	//*cgGLEnableProfile(CG_PROFILE_ARBVP1);
#endif
}

void unRenderer::unbind_around(void)
{
#if 1
	//*cgGLDisableProfile(aroundFragProfile);
#endif

#if 0
	//*cgGLDisableProfile(aroundVertProfile);
#endif
}
//AST-

void unRenderer::set_normal_params(const pVector& diffuse,const pVector& specular,float tile,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_normal_params_mesh(const float& diffuse,const float& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse);
	//*cgGLSetParameter4fv(m_nspecular,&specular);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_normal_params_static(const pVector& diffuse,const pVector& specular,float tile,GLuint texcolor,GLuint texnormal)
{
	//*cgGLSetParameter4fv(m_ndiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_nspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);

	//*cgGLSetParameter2f(m_nplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_relief_params(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse,&diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular,&specular.x);
	//*cgGLSetParameter1f(m_vtile,tile);
	//*cgGLSetParameter1f(m_vdepth,depth);
	//*cgGLSetParameter1f(m_rtdepth,1);

	////*cgGLSetTextureParameter(m_stepmap, stepmap.m_TexID);
	//cgSetSamplerState(m_stepmap);

	//*cgGLSetParameter2f(m_rplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
}

void unRenderer::set_relief_params_terrain(const pVector& diffuse,const pVector& specular,float tile,float depth,int texcolor,int texnormal)
{
	//*cgGLSetParameter4fv(m_rdiffuse, &diffuse.x);
	//*cgGLSetParameter4fv(m_rspecular, &specular.x);
	//*cgGLSetParameter1f(m_terraintile, tile);
	//*cgGLSetParameter1f(m_terraindepth, depth);
	//*cgGLSetParameter1f(m_rtdepth, 1);

	//*cgGLSetParameter2f(m_rplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor==-1?m_null_color:g_render->picid.buf[texcolor]);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal==-1?m_null_normal:g_render->picid.buf[texnormal]);
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
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
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
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D,texcolor);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D,texnormal);
}

void unRenderer::set_light_params(const pVector& lightpos,const pVector& lightcolor)
{
	//*cgGLSetParameter4fv(m_lpos,&lightpos.x);
	//*cgGLSetParameter3fv(m_lcolor,&lightcolor.x);

	//*cgGLSetParameter2f(m_lplanes, 
	//*	-g_render->farplane/(g_render->farplane-g_render->nearplane),
	//*	-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));
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
			//*param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,(i-k)*fp,0);
		}
	}
	else
	{
		float fp=1.25/(m_sizey/UNREND_BLOOM_SCALE);
		for( i=0;i<j;i++ )
		{
			//*param=cgGetArrayParameter(m_bdisp,i);
			//*cgGLSetParameter2f(param,0,(i-k)*fp);
		}
	}
}

void unRenderer::fb_bind_render(int buffer)
{
	//if (m_fb)
	//	m_fb[buffer]->Bind();
}

void unRenderer::fb_unbind_render(int buffer)
{
	//if (m_fb)
	//	m_fb[buffer]->Unbind();
}

void unRenderer::fb_bind_texture(int buffer,int texunit)
{
	//if (m_fb[buffer])
	//{
		//QDglActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
	//	m_fb[buffer]->BindAsTexture(WGL_FRONT_LEFT_ARB);
		glEnable(GL_TEXTURE_2D);
	//}
}

void unRenderer::fb_unbind_texture(int buffer,int texunit)
{
	//if (m_fb[buffer])
	//{
		//QDglActiveTextureARB(GL_TEXTURE0_ARB+texunit);
		glBindTexture(GL_TEXTURE_2D,m_fbtex[buffer]);
	//	m_fb[buffer]->ReleaseTexture(WGL_FRONT_LEFT_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
	//}
}

void unRenderer::mrt_bind_render()
{
	//if (m_mrt)
	//{
	//	m_mrt->Bind();
	//	glDrawBuffersATI(m_nv_render_depth_texture?3:4,gl_buffers);
	//}
}

void unRenderer::mrt_unbind_render()
{
	//if (m_mrt)
	//	m_mrt->Unbind();
}

void unRenderer::mrt_bind_texture(int target)
{
	//if (m_mrt)
	//{
		if (target>=0)
		{
	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[target]);
	//		m_mrt->BindAsTexture(wgl_buffers[target]);
			glEnable(GL_TEXTURE_2D);
		}
		else
		{
	//		//QDglActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[3]);
	//		m_mrt->BindAsTexture(wgl_buffers[3]);

	//		//QDglActiveTextureARB(GL_TEXTURE2_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[2]);
	//		m_mrt->BindAsTexture(wgl_buffers[2]);

	//		//QDglActiveTextureARB(GL_TEXTURE1_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[1]);
	//		m_mrt->BindAsTexture(wgl_buffers[1]);

	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_mrttex[0]);
	//		m_mrt->BindAsTexture(wgl_buffers[0]);
		}
	//}
}

void unRenderer::mrt_unbind_texture(int target)
{
	//if (m_mrt)
	//{
		if (target>=0)
		{
	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[target]);
			glBindTexture(GL_TEXTURE_2D,0);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
	//		//QDglActiveTextureARB(GL_TEXTURE3_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[3]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE2_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[2]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE1_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[1]);
			glBindTexture(GL_TEXTURE_2D,0);

	//		//QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//		m_mrt->ReleaseTexture(wgl_buffers[0]);
			glBindTexture(GL_TEXTURE_2D,0);
		}
	//}
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
			/*gluUnProject(
				pixels[i][0],pixels[i][1],10,
				g_render->cam_model_mat,g_render->cam_proj_mat,
				viewport,&d[0],&d[1],&d[2]);*/
			f[i].vec((float)d[0],(float)d[1],(float)d[2]);
			f[i]-=g_render->camera.pos;
			f[i].normalize();
			f[i]=f[i]*view_rot;
		}

		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
	else
	if (flipy)
	{
		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
	else
	{
		/*//*glBegin(GL_QUADS);
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
		//*glEnd();*/
	}
}

void unRenderer::ViewOrtho(void)								// Set Up An Ortho View
{
	/*glMatrixMode(GL_PROJECTION);								// Select Projection
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();											// Reset The Matrix
	glOrtho( 0, 640 , 480 , 0, -1, 1 );							// Select Ortho Mode (640x480)
	glMatrixMode(GL_MODELVIEW);									// Select Modelview Matrix
	glPushMatrix();												// Push The Matrix
	glLoadIdentity();											// Reset The Matrix*/
}

void unRenderer::ViewPerspective(void)							// Set Up A Perspective View
{
	//glMatrixMode( GL_PROJECTION );								// Select Projection
	//glPopMatrix();												// Pop The Matrix
	//glMatrixMode( GL_MODELVIEW );								// Select Modelview
	//glPopMatrix();												// Pop The Matrix
}

void unRenderer::RenderToTexture_Prep(void)          // Renders To A Texture
{
	//glColorMask(true,true,true,true);
	//glDepthMask(false);

	//mrt_unbind_texture(-1);
	//mrt_unbind_render();

	//glLoadIdentity();

    //glViewport(0, 0, 128, 128);                    // Set Our Viewport (Match Texture Size)
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
}

void unRenderer::RenderToTexture_Tex(void)          // Renders To A Texture
{
    // Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
    //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 128, 128, 0);

	// compute lighting
	//draw_lights(_->mesh,false);

	// draw antialias (blur edges)
	//if (1) draw_antialias();

	// compute bloom
	//if (1) draw_bloom();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask(false);

	fb_bind_texture(0,0);

	draw_rect(0, 0, g_render->sizex/4, g_render->sizey/4, false, true);

	glBindTexture(GL_TEXTURE_2D, BlurTexture);           // Bind To The Blur Texture

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, g_render->sizex/4, g_render->sizey/4, 0);

	fb_unbind_texture(0,0);
 
    //glClearColor(0.0f, 0.0f, 0.5f, 0.5);                // Set The Clear Color To Medium Blue
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And Depth Buffer
 
	//glViewport(0, 0, g_render->sizex, g_render->sizey);                 // Set Viewport (0,0 to 640x480)

	//glColorMask(false,false,false,false);
	//glDepthMask(true);

	//mrt_bind_texture(-1);
	//mrt_bind_render();
}

GLuint unRenderer::EmptyTexture(void)							// Create An Empty Texture
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((g_render->sizex * g_render->sizey)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((g_render->sizex * g_render->sizey)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, g_render->sizex, g_render->sizey, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}

void unRenderer::ClearBlur(void)					// Draw The Blurred Image
{
#if 0
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alpha = 0;											// Starting Alpha Value

	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
	glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Set Blending Mode
	glEnable(GL_BLEND);											// Enable Blending
	glBindTexture(GL_TEXTURE_2D, BlurTexture);					// Bind To The Blur Texture
	ViewOrtho();												// Switch To An Ortho View

	//*glBegin(GL_QUADS);											// Begin Drawing Quads
	glColor4f(0, 0, 0, alpha);					// Set The Alpha Value (Starts At 0.2)
	glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
	glVertex2f(0,0);									// First Vertex		(   0,   0 )

	glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
	glVertex2f(0,480);									// Second Vertex	(   0, 480 )

	glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
	glVertex2f(640,480);								// Third Vertex		( 640, 480 )

	glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
	glVertex2f(640,0);									// Fourth Vertex	( 640,   0 )
	//*glEnd();													// Done Drawing Quads

	ViewPerspective();											// Switch To A Perspective View

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
	glDisable(GL_BLEND);										// Disable Blending
	glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
#endif
}

void unRenderer::DrawBlur(int times, float inc)					// Draw The Blurred Image
{
#if 0
	float spost = 0.0f;											// Starting Texture Coordinate Offset
	float alphainc = 0.9f / times;								// Fade Speed For Alpha Blending
	float alpha = 0.2f;											// Starting Alpha Value

	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glEnable(GL_TEXTURE_2D);									// Enable 2D Texture Mapping
	glDisable(GL_DEPTH_TEST);									// Disable Depth Testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);							// Set Blending Mode
	glEnable(GL_BLEND);											// Enable Blending
	glBindTexture(GL_TEXTURE_2D, BlurTexture);					// Bind To The Blur Texture
	ViewOrtho();												// Switch To An Ortho View

	alphainc = alpha / times;									// alphainc=0.2f / Times To Render Blur

	//*glBegin(GL_QUADS);											// Begin Drawing Quads
	for (int num = 0; num < times; num++)						// Number Of Times To Render Blur
		{
		glColor4f(1.0f, 1.0f, 1.0f, alpha);					// Set The Alpha Value (Starts At 0.2)
		glTexCoord2f(0+spost,1-spost);						// Texture Coordinate	( 0, 1 )
		glVertex2f(0,0);									// First Vertex		(   0,   0 )

		glTexCoord2f(0+spost,0+spost);						// Texture Coordinate	( 0, 0 )
		glVertex2f(0,g_render->sizey);									// Second Vertex	(   0, 480 )

		glTexCoord2f(1-spost,0+spost);						// Texture Coordinate	( 1, 0 )
		glVertex2f(g_render->sizex,g_render->sizey);								// Third Vertex		( 640, 480 )

		glTexCoord2f(1-spost,1-spost);						// Texture Coordinate	( 1, 1 )
		glVertex2f(g_render->sizex,0);									// Fourth Vertex	( 640,   0 )

		spost += inc;										// Gradually Increase spost (Zooming Closer To Texture Center)
		alpha = alpha - alphainc;							// Gradually Decrease alpha (Gradually Fading Image Out)
		}
	//*glEnd();													// Done Drawing Quads

	ViewPerspective();											// Switch To A Perspective View

	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable(GL_TEXTURE_2D);									// Disable 2D Texture Mapping
	glDisable(GL_BLEND);										// Disable Blending
	glBindTexture(GL_TEXTURE_2D,0);								// Unbind The Blur Texture
#endif
}

void unRenderer::draw_depth(pMesh *m)
{
	int va=0,vb=1;

	//glScalef(1.9f,1.9f,1.9f);

	m->array_lock(va,vb);

	m->array_draw(vb);

	m->array_unlock();
}

void unRenderer::draw_depth_terrain(pMesh *m)
{
#if 0
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock_physics(va, vb, true);

	bind_terrain_vertex();

	//*cgGLSetParameter1f(m_terrainwidth, m->m_PhysicsTextureWidth);

	//*cgGLSetTextureParameter(m_terrainsampler, m->m_PhysicsTexture);
	//*cgGLEnableTextureParameter(m_terrainsampler);
	cgSetSamplerState(m_terrainsampler);

	glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

	unbind_vertex();

	m->array_unlock();
#endif
}

void unRenderer::draw_depth_meshes(void)
{
#if 0
	int va=0,vb=1;
	pVector PosTest;

	for(int i = 0; i < _->NomSEnergy; i++)
		{
		if(i > 0 && i < _->MaxNomSEnergy)
			{
			for(int k = 0; k < 5; k++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Xform.Translation.z);
				glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

				glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);

				if(Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar < 2)
					{
					pMesh* f_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar]->m_submesh[0];
					f_mesh->array_lock(va,vb);

					f_mesh->array_draw(vb);

					f_mesh->array_unlock();
					}
				}
			}
		}

	for(unsigned int i = 0; i < _->MaxNomLEnergy; i++)
		{
		if(Q_LEnergy->LEnergy[i].EnergyBall.m_Alpha > 0)
			{
			for(unsigned int k = 0; k < 5; k++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[i].EnergyBall.Xform.Translation.z);

				/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[0] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[1] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[2] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[3]= (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[4] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[5] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[6] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[7] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[8] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[9] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[10] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[11] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[12] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[13] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[14] = (((float)rand() / 32767)-0.5);
				Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf[15] = (((float)rand() / 32767)-0.5);*/

				Qpo->Transform_New_XRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);
				Qpo->Transform_New_YRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);
				Qpo->Transform_New_ZRotation(&AIfriendly, (((float)rand() / 32767)*(PI*2)));
				Qpo->Transform_Multiply(&Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform, &AIfriendly, &Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform);

				glMultMatrixf(Q_SEnergy->SEnergy[i].AvatarFlag[k].Viewform.Matrix.mf);

				//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
				glScalef(Q_LEnergy->LEnergy[i].EnergyBall.Scale.x, Q_LEnergy->LEnergy[i].EnergyBall.Scale.y, Q_LEnergy->LEnergy[i].EnergyBall.Scale.z);

				pMesh* f_mesh = QActiveFrameWork->meshstaticTemplates[Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar]->m_submesh[0];
				f_mesh->array_lock(va,vb);

				f_mesh->array_draw(vb);

				f_mesh->array_unlock();
				}
			}
		}

	if(player[g_Player]->WeaponStatus > 1)
		{
		glLoadIdentity();

		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
		playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
		playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

		/*if(player[g_Player]->AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);
		else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV, true);

		//##### MiniGUN Rotation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
			Ange.y = -0.87; //WeaponvalueshtY;//PI;
			Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

			// Set the actor's angle
			Qpo->Transform_RotateY(&player[g_Player]->RFistPosV, Ange.y);
			Qpo->Transform_RotateX(&player[g_Player]->RFistPosV, Ange.x);
			Qpo->Transform_RotateZ(&player[g_Player]->RFistPosV, Ange.z);
			//#####
			}

		glTranslatef(player[g_Player]->RFistPosV.Translation.x, player[g_Player]->RFistPosV.Translation.y, player[g_Player]->RFistPosV.Translation.z);
		glMultMatrixf(player[g_Player]->RFistPosV.Matrix.mf);

		//##### MiniGUN Translation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			//glTranslatef(19.24, 71.057, 14.87);
			//glTranslatef(10.65, -83.68, 26.31);
			glTranslatef(10.98, -71.22, 22.12);
			//glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
			}
		else
			{
			glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
			}

		pMesh* f_mesh;
		for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_submesh.num; f_meshcnt++)
			{											 //player[g_Player]->Weapon.Avatar
			f_mesh = QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_submesh[f_meshcnt];

			f_mesh->array_lock(va,vb);

			f_mesh->array_draw(vb);

			f_mesh->array_unlock();
			}
		}

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].WeaponStatus > 1)
				{
				PosTest.x = Q_Forge->Forge[SCRAM].AV.Xform.Translation.x;
				PosTest.y = Q_Forge->Forge[SCRAM].AV.Xform.Translation.y;
				PosTest.z = Q_Forge->Forge[SCRAM].AV.Xform.Translation.z;

				if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[SCRAM].HB_DeadTimer > 0)
					{
					glLoadIdentity();

					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.x = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.y = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[SCRAM].AV.Avatar.Scale.z = Q_Forge->Forge[SCRAM].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[SCRAM].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
						{
						Qpo->AvatarView_GetBoneTransform(&Q_Forge->Forge[SCRAM].AV, "BIP01 R HAND", &player[g_Player]->RFistPosV, false);

						Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
						Ange.y = -0.87; //WeaponvalueshtY;//PI;
						Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

						// Set the actor's angle
						Qpo->Transform_RotateY(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.y);
						Qpo->Transform_RotateX(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.x);
						Qpo->Transform_RotateZ(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.z);
						//#####
						}
					else Qpo->Avatar_GetBoneTransformMP(Q_Forge->Forge[SCRAM].AV, "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV);

					glTranslatef(Q_Forge->Forge[SCRAM].RFistPosV.Translation.x, Q_Forge->Forge[SCRAM].RFistPosV.Translation.y, Q_Forge->Forge[SCRAM].RFistPosV.Translation.z);
					glMultMatrixf(Q_Forge->Forge[SCRAM].RFistPosV.Matrix.mf);

					//##### MiniGUN Translation
					if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
						{
						//glTranslatef(19.24, 71.057, 14.87);
						//glTranslatef(10.65, -83.68, 26.31);
						glTranslatef(10.98, -71.22, 22.12);
						//glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
						}
					else
						{
						glTranslatef(WeaponvalueX, WeaponvalueY, WeaponvalueZ);
						}

					pMesh* f_mesh;
					for(int f_meshcnt = 0; f_meshcnt < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_submesh.num; f_meshcnt++)
						{
						f_mesh = QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_submesh[f_meshcnt];

						f_mesh->array_lock(va,vb);

						f_mesh->array_draw(vb);

						f_mesh->array_unlock();
						}
					}
				}
			}

		SCRAM++;
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int f_vehicleiter = 0; f_vehicleiter < m_VehicleCount; f_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[f_vehicleiter].getColumnMajor44(glMat);
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
			pMesh* f_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh[i];

			f_mesh->array_lock(va,vb);

			f_mesh->array_draw(vb);

			f_mesh->array_unlock();
			}
		}
#endif
#endif
}

void unRenderer::draw_depth_avatars(void)
{
#if 0
	//// DEBUG: CLOTH SIM
	static QunVector spherePosition;
	spherePosition.set(playerAV[g_Player]->Avatar.Mesh->Sphere.x, playerAV[g_Player]->Avatar.Mesh->Sphere.y, playerAV[g_Player]->Avatar.Mesh->Sphere.z);
	static float sphereRadius = 15.0f;

	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setSphere(spherePosition.x, spherePosition.y, spherePosition.z, sphereRadius);

	glColor3f(1.0f, 1.0f, 1.0f);
	//*glBegin(GL_LINE_STRIP);
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
	//*glEnd();
	//// DEBUG END
#endif

  //QunSkeleton *pQunSkeleton = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton();

  // Note :
  // You have to call coreSkeleton.calculateBoundingBoxes(calCoreModel)
  // during the initialisation (before qunModel.create(calCoreModel))
  // if you want to use bounding boxes.

#if 0
  playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->calculateBoundingBoxes();
#endif

	// Note:
	// Uncomment the next lines if you want to test the experimental collision system.
	// Also remember that you need to call calculateBoundingBoxes()

	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setForceVector(QunVector(0.0f,0.0f,0.0f));
	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSpringSystem()->setCollisionDetection(true);  
#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}*/

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

			//if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
			//{
			//printf("Treace no error\n");
			//}

			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	//////////////////////////////////////
	////// Render Player Shadows /////////

	///// Mesh Settings /////
	if(player[g_Player]->ShadowsOn)
		{
		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			for(hardwareMeshId=0;hardwareMeshId<player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}
			}
		}


	//////////////////////////////////////
	////// Render NON-Player Meshes //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		// Decrement on death timer
		if(Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].HB_Dead == 1) 
			{
			Q_Forge->Forge[i].HB_DeadTimer--;
			}

		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(Q_Forge->Forge[i].LIVE == 1 && g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0)
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
					QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

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

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			//////////////////////////////////////
			////// Render AI Shadows /////////////

			///// Mesh Settings /////
			if(Q_Forge->Forge[i].ShadowsOn && 0)
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
							QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

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

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	unbind_mesh_vertex();

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}*/

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

			//if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
			//{
			//printf("Treace no error\n");
			//}

			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}
#endif
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_avatars_shell(void)
{
	/*glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_mesh_vertex();

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);
	
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	//glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

	glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

	std::vector<QunBone *>& vectorBone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

	///// Mesh Settings /////
	bool f_setPos = 0;
	int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
		{
#if 0
		if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_SetMesh[hardwareMeshId] != -1)
			{
			glTranslatef(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId], playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
			}
#endif

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
			{
			QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
			QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

			QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
			/*if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getLineOffSetX(hardwareMeshId) == -1)
				{
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetX[hardwareMeshId]);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetY[hardwareMeshId]);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_Line_OffSetZ[hardwareMeshId]);
				}
			else
				{*/
				/*transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=(translationBoneSpace.x + _PositioningOffset.x);
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=(translationBoneSpace.y + _PositioningOffset.y);
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=(translationBoneSpace.z + _PositioningOffset.z);
				//}]
#endif

#if 0
			if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
#endif

			/*transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
		else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
		}

	//////////////////////////////////////
	////// Render Player Shadows /////////

#if 0
	///// Mesh Settings /////
	if(player[g_Player]->ShadowsOn)
		{
		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			for(hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				}
			}
		}
#endif


	//////////////////////////////////////
	////// Render NON-Player Meshes //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		// Decrement on death timer
		if(Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].HB_Dead == 1)
			{
			Q_Forge->Forge[i].HB_DeadTimer--;
			}

		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].LIVE == 1)
			{
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);
			
			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

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

			Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

			glScalef(Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)),Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)));

			std::vector<QunBone *>& vectorBoneAI = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			int hardwareMeshId = 0;
			for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

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

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));

#if 0
				printf("glDrawElements %f", Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh);
#endif
				}

			//////////////////////////////////////
			////// Render AI Shadows /////////////

#if 0
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

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					int hardwareMeshId = 0;
					for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
						float transformation[500];

						int boneId;
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}
				}
#endif
			}
		}

	unbind_mesh_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);*/
}

void unRenderer::draw_depth_terrain_old(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_vertex();

	int f_iterator;
	int f_layer;
	int f_instance;
	int f_index;

	trr::unTerrainCell* f_Cell;

	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			///// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, f_Cell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
				//glDrawElements(GL_TRIANGLES, f_Cell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);
				}
			}
		}

	unbind_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif

#if 0	// Trace Instance Count
	printf("%i Instances\n", f_Cell[0]->m_Instance.size());
#endif
}

void unRenderer::draw_depth_shapes(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	//bind_terrain_vertex();
	bind_terrain_vertex();

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
	//glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL)+ 0));

	//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_shape_instances(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

		for(f_instance = 0; f_instance < f_ShapeBank->m_Shape[f_iterator]->m_Instance.size(); f_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->x, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->y, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->z);
			//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[f_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}*/
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_depth_shape_energy(void)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	bind_terrain_vertex();

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				//glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

	unbind_terrain_vertex();

	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_material(pMesh *m,bool relief)
{
	int va=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT,vb=1;
	m->array_lock(va,vb);

	int i, j = m->nfacemat, k;
	pMaterial *mat;
	
	bind_vertex();

	bind_normal();

	//glScalef(1.9f,1.9f,1.9f);

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

	//bind_blur();

	//glScalef(1.9f,1.9f,1.9f);

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

	//unbind_relief();

	unbind_vertex();

	m->array_unlock();
}

void unRenderer::draw_material_terrain(pMesh *m, bool relief)
{
#if 0
	int va = P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TANGENT, vb = 1;
	m->array_lock_physics(va, vb, true);

	pMaterial *mat = &m->mat[0];

	bind_terrain_vertex();

	//*cgGLSetParameter1f(m_terrainwidth, m->m_PhysicsTextureWidth);

	//*cgGLSetTextureParameter(m_terrainsampler, m->m_PhysicsTexture);
	//*cgGLEnableTextureParameter(m_terrainsampler);
	cgSetSamplerState(m_terrainsampler);

	if(!relief)
		{
		bind_normal();

		set_normal_params(mat->diffuse, mat->specular, 5, mat->texid, mat->texnormalid);

		glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

		unbind_normal();
		}

	if(relief)
		{
		bind_relief();

		set_relief_params_terrain(mat->diffuse, mat->specular, 1, 5, mat->texid, mat->texnormalid);

		glDrawElements(GL_TRIANGLES, m->nface * 3, GL_UNSIGNED_INT, NULL);

		unbind_relief();
		}

	unbind_vertex();

	m->array_unlock();
#endif
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
	int va = 0;
	int vb = 1;
	bool relief = true;
	pVector PosTest;
	QpoVec3d Anf;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	if(mProgram == 0)
		{
		return;
		}

	glUseProgram(mProgram);

	pFrustum f_View;

	float cameraDistance = (((750.0f / g_Zoom) * (1 - g_ZoomFactor)) + 300.0f) * g_ArenaSize;

	float fov = 115.0f;
	float aspect = float(1280.0f) / float(1080.0f);
	float farplane = 10000.0f;
	pVector f_camX(1.0f, 0.0f, 0.0f);
	pVector f_camY(0.0f, 1.0f, 0.5f);
	pVector f_camZ(0.0f, -1.0f, 1.0f);

	pVector f_PlayerPos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	f_camX.normalize();
	f_camY.normalize();
	f_camZ.normalize();

	pVector f_CamPos = f_PlayerPos + (f_camZ * (cameraDistance * 2));

	f_View.build(f_CamPos,
		f_camX,
		f_camY,
		f_camZ,
		fov / aspect,
		aspect,
		farplane);

#if 0
	f_View.draw();
#endif

	float f_Transport[4];
	
	if(_->NomSEnergy > 0)
		{
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[0]);
		glEnableVertexAttribArray(m0AttribLocation);
		glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Array - Normals
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[2]);
		glEnableVertexAttribArray(m2AttribLocation);
		glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Texture Coords
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[4]);
		glEnableVertexAttribArray(m4AttribLocation);
		glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Weights
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[1]);
		glEnableVertexAttribArray(m1AttribLocation);
		glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - MatrixIndex
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[3]);
		glEnableVertexAttribArray(m3AttribLocation);
		glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Elements Array - Face Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[0]->m_bufferObject[5]);

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

#if 0
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, g_render->camera.mat_t.mf);
#else
		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));
#endif

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

		for(unsigned int f_Iter = 0; f_Iter < _->NomSEnergy; f_Iter++)
			{
			if(f_Iter > 0 && f_Iter < _->MaxNomSEnergy)
				{
				PosTest.x = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x;
				PosTest.y = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.y;
				PosTest.z = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z;

				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Matrix.mf);

				if(f_View.is_inside(PosTest))
					{
					ag_Calc_Light(Cube::BiVector(Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.y, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z));

					glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
					glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
					glUniform1f(mLightNomUniformLocation, g_LightNom);

					f_Transport[0] = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.x - playerAV[0]->Xform.Translation.x;
					f_Transport[1] = Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.y - playerAV[0]->Xform.Translation.y;
					f_Transport[2] = (Q_SEnergy->SEnergy[f_Iter].AvatarFlag[0].Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1.0f;

					f_Transport[3] = Q_SEnergy->SEnergy[f_Iter].Scale;

					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					int hardwareMeshId = 0;
					for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
						{
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

						// set the material diffuse color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

						// set the material specular color
						QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getBoneCount(); boneId++)
							{
							//glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getMapUserData(0));
							glUniform1i(mTextureUniformLocation, 0);
							}

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
						glUniform1f(mTimeUniformLocation, Cube::random());

#if 0
						if (hardwareMeshId < 38)
							{
							diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						if (diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
#endif

						if(sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[0]->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	if(player[g_Player]->WeaponStatus > 1)
		{
		ag_Calc_Light(Cube::BiVector(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 55, playerAV[g_Player]->Xform.Translation.z));

		glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
		glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
		glUniform1f(mLightNomUniformLocation, g_LightNom);

		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[0]);
		glEnableVertexAttribArray(m0AttribLocation);
		glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Normal Array - Normals
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[2]);
		glEnableVertexAttribArray(m2AttribLocation);
		glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Texture Coords
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[4]);
		glEnableVertexAttribArray(m4AttribLocation);
		glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - Weights
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[1]);
		glEnableVertexAttribArray(m1AttribLocation);
		glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Vertex Array - MatrixIndex
		glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[3]);
		glEnableVertexAttribArray(m3AttribLocation);
		glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

		//Elements Array - Face Indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_bufferObject[5]);

		MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

		glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

		MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
		glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

		/*if(player[g_Player]->AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV);
		else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &player[g_Player]->RFistPosV, true);

		//##### MiniGUN Rotation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
			Ange.y = -0.87; //WeaponvalueshtY;//PI;
			Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

			// Set the actor's angle
			Qpo->Transform_RotateY(&player[g_Player]->RFistPosV, Ange.y);
			Qpo->Transform_RotateX(&player[g_Player]->RFistPosV, Ange.x);
			Qpo->Transform_RotateZ(&player[g_Player]->RFistPosV, Ange.z);
			//#####
			}

		glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, player[g_Player]->RFistPosV.Matrix.mf);

		//##### MiniGUN Translation
		if(player[g_Player]->Weapon.Avatar == 3 || player[g_Player]->Weapon.Avatar == 4)
			{
			Anf.x = player[g_Player]->RFistPosV.Translation.x + 10.98;
			Anf.y = player[g_Player]->RFistPosV.Translation.y - 71.22;
			Anf.z = player[g_Player]->RFistPosV.Translation.z + 22.12;
			}
		else
			{
			Anf.x = player[g_Player]->RFistPosV.Translation.x + WeaponvalueX;
			Anf.y = player[g_Player]->RFistPosV.Translation.x + WeaponvalueY;
			Anf.z = player[g_Player]->RFistPosV.Translation.x + WeaponvalueZ;
			}

		PosTest.x = Anf.x;
		PosTest.y = Anf.y;
		PosTest.z = Anf.z;

		if(f_View.is_inside(PosTest))
			{
			if(g_Player == 0)
				{
				f_Transport[0] = 0.0f;
				f_Transport[1] = 0.0f;
				f_Transport[2] = 0.0f;
				}
			else
				{
				f_Transport[0] = Anf.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = Anf.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (Anf.z - playerAV[0]->Xform.Translation.z) * -1.0f;
				}

			f_Transport[3] = player[g_Player]->Weapon.Scale.x;

			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
			for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
				{
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

				// set the material diffuse color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

				// set the material specular color
				QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

				float transformation[896];

				int boneId;
				for(boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getBoneCount(); boneId++)
					{
					//glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getMapUserData(0));
					glUniform1i(mTextureUniformLocation, 0);
					}

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
				glUniform1f(mTimeUniformLocation, Cube::random());

				if(sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[player[g_Player]->Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
				}
			}
		}

	SCRAM=0;
	while(SCRAM < _->NomAI)
		{
		if(Q_Forge->Forge[SCRAM].LIVE == 1)
			{
			if(Q_Forge->Forge[SCRAM].WeaponStatus > 1)
				{
				ag_Calc_Light(Cube::BiVector(Q_Forge->Forge[SCRAM].AV.Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 45, playerAV[g_Player]->Xform.Translation.z));

				glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
				glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
				glUniform1f(mLightNomUniformLocation, g_LightNom);

				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[0]);
				glEnableVertexAttribArray(m0AttribLocation);
				glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				//Normal Array - Normals
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[2]);
				glEnableVertexAttribArray(m2AttribLocation);
				glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - Texture Coords
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[4]);
				glEnableVertexAttribArray(m4AttribLocation);
				glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - Weights
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[1]);
				glEnableVertexAttribArray(m1AttribLocation);
				glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				//Vertex Array - MatrixIndex
				glBindBuffer(GL_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[3]);
				glEnableVertexAttribArray(m3AttribLocation);
				glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

				//Elements Array - Face Indices
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_bufferObject[5]);

				MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();

				glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

				MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
				glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

				/*if(Q_Forge->Forge[SCRAM].AirJinkRotFG == 1) Qpo->WeaponView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV);
				else*/ Qpo->AvatarView_GetBoneTransform(playerAV[g_Player].operator ->(), "BIP01 R HAND", &Q_Forge->Forge[SCRAM].RFistPosV, true);

				//##### MiniGUN Rotation
				if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
					{
					Ange.x = 1.7; //WeaponvalueshtX;//(PI/2);
					Ange.y = -0.87; //WeaponvalueshtY;//PI;
					Ange.z = 1.65; //WeaponvalueshtZ;//(PI/2);

					// Set the actor's angle
					Qpo->Transform_RotateY(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.y);
					Qpo->Transform_RotateX(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.x);
					Qpo->Transform_RotateZ(&Q_Forge->Forge[SCRAM].RFistPosV, Ange.z);
					//#####
					}

				glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[SCRAM].RFistPosV.Matrix.mf);

				//##### MiniGUN Translation
				if(Q_Forge->Forge[SCRAM].Weapon.Avatar == 3 || Q_Forge->Forge[SCRAM].Weapon.Avatar == 4)
					{
					Anf.x = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + 10.98;
					Anf.y = Q_Forge->Forge[SCRAM].RFistPosV.Translation.y - 71.22;
					Anf.z = Q_Forge->Forge[SCRAM].RFistPosV.Translation.z + 22.12;
					}
				else
					{
					Anf.x = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueX;
					Anf.y = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueY;
					Anf.z = Q_Forge->Forge[SCRAM].RFistPosV.Translation.x + WeaponvalueZ;
					}

				PosTest.x = Anf.x;
				PosTest.y = Anf.y;
				PosTest.z = Anf.z;

				if(f_View.is_inside(PosTest))
					{
					if(g_Player == 0)
						{
						f_Transport[0] = 0.0f;
						f_Transport[1] = 0.0f;
						f_Transport[2] = 0.0f;
						}
					else
						{
						f_Transport[0] = Anf.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = Anf.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (Anf.z - playerAV[0]->Xform.Translation.z) * -1.0f;
						}

					f_Transport[3] = Q_Forge->Forge[SCRAM].Weapon.Scale.x;

					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					int hardwareMeshId = 0;
					for(hardwareMeshId = 0; hardwareMeshId < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getHardwareMeshCount(); hardwareMeshId++)
						{
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);

						// set the material diffuse color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);

						// set the material specular color
						QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);

						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getBoneCount(); boneId++)
							{
							//glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, (GLuint)QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getMapUserData(0));
							glUniform1i(mTextureUniformLocation, 0);
							}

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
						glUniform1f(mTimeUniformLocation, Cube::random());

						if (sizeof(QunIndex) == 2) glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + QActiveFrameWork->meshstaticTemplates[Q_Forge->Forge[SCRAM].Weapon.Avatar]->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}

		SCRAM++;
		}

#if 0
	//--- Vehicle Testing ---//
	float glMat[16];
	for(unsigned int f_vehicleiter = 0; f_vehicleiter < m_VehicleCount; f_vehicleiter++)
		{
		glLoadIdentity();
		glMultMatrixf((float *)&g_render->camera.mat_t);
		glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

		vec_VehiclePos[f_vehicleiter].getColumnMajor44(glMat);
		glMultMatrixf(glMat);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(-90, 0.0f, 0.0f, 1.0f);

		//glTranslatef(Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.x, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.y, Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Xform.Translation.z);
		//glMultMatrixf(Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Viewform.Matrix.mf);

		//glScalef(Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.x, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.y, Q_SEnergy->SEnergy[i].AvatarFlag[k].Scale.z);
		glScalef(0.007, 0.007, 0.007);

		for(int iter = 0; iter < QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[i].AvatarFlag[k].Avatar*/]->m_submesh.num; iter++)
			{
			pMesh* f_mesh = QActiveFrameWork->meshVehicleTemplates[0/*Q_SEnergy->SEnergy[f_Iter].AvatarFlag[l].Avatar*/]->m_submesh[iter];

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
					//set_relief_params_static(mat->diffuse,mat->specular,1,1,Medias->expandro1,Medias->expandro1);
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
#endif
}

void unRenderer::draw_material_avatars(bool relief)
{
	glEnable(GL_DEPTH_TEST);

	glDisable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);
	
	if(mProgram == 0)
		{
        return;
		}

	glUseProgram(mProgram);

	pFrustum f_View;

	float cameraDistance = (((750.0f / g_Zoom) * (1 - g_ZoomFactor)) + 300.0f) * g_ArenaSize;

	float fov = 115.0f;
	float aspect = float(1280.0f) / float(1080.0f);
	float farplane = 10000.0f;
	pVector f_camX(1.0f, 0.0f, 0.0f);
	pVector f_camY(0.0f, 1.0f, 0.5f);
	pVector f_camZ(0.0f, -1.0f, 1.0f);

	pVector f_PlayerPos(playerAV[0]->Xform.Translation.x, playerAV[0]->Xform.Translation.y, playerAV[0]->Xform.Translation.z);

	f_camX.normalize();
	f_camY.normalize();
	f_camZ.normalize();

	pVector f_CamPos = f_PlayerPos + (f_camZ * (cameraDistance * 2));

	f_View.build(f_CamPos,
		f_camX,
		f_camY,
		f_camZ,
		fov / aspect,
		aspect,
		farplane);

#if 0
	f_View.draw();
#endif

	float f_Transport[4];
	float f_Team[4];

	for(unsigned int f_CountPlayer = 0; f_CountPlayer < g_PlayerNom; f_CountPlayer++)
		{
		g_Player = f_CountPlayer;

		if(f_View.is_inside(pVector(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z)) && (playerAV[g_Player]->Avatar.Mesh->m_rebuild == 0))
			{
			  /////////////////
			 // Q_Light
			//
			ag_Calc_Light(Cube::BiVector(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 45, playerAV[g_Player]->Xform.Translation.z));
							

			glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
			glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
			glUniform1f(mLightNomUniformLocation, g_LightNom);

			//Vertex Array - Position
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
			glEnableVertexAttribArray(m0AttribLocation);
			glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Normal Array - Normals
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
			glEnableVertexAttribArray(m2AttribLocation);
			glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Texture Coords
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
			glEnableVertexAttribArray(m4AttribLocation);
			glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Weights
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
			glEnableVertexAttribArray(m1AttribLocation);
			glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - MatrixIndex
			glBindBuffer(GL_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
			glEnableVertexAttribArray(m3AttribLocation);
			glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Elements Array - Face Indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

			 ////////////////////////////////
			////// Render Player Mesh //////
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, playerAV[g_Player]->Xform.Matrix.mf);

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			if(player[g_Player]->Team == 0)
				{
				f_Team[0] = 0.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 1)
				{
				f_Team[0] = 0.21;
				f_Team[1] = 0.0;
				f_Team[2] = 1.0;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 2)
				{
				f_Team[0] = 1.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 3)
				{
				f_Team[0] = 1.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.25;
				f_Team[3] = 1.0;
				}
			else if(player[g_Player]->Team == 4)
				{
				f_Team[0] = 0.5;
				f_Team[1] = 0.5;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}

			glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

			    //////////////////////
			   // Enemy LockOn //  //
			  //////////////////////
			 // Work on Please //
			////////////////////
			QpoVec3d f_Diff;
			float f_Length = 150.0f;
			bool f_Touch = false;
			int f_Index = 0;

			for(int f_Count = 0; f_Count < _->NomAI; f_Count++)
				{
				if(Q_Forge->Forge[f_Count].LIVE)
					{
					if(Q_Forge->Forge[f_Count].Team != player[g_Player]->Team)
						{
						if(Q_Forge->Forge[f_Count].HB_Dead == 0)
							{
							Qpo->Vec3d_Subtract(&playerAV[g_Player]->Xform.Translation, &Q_Forge->Forge[f_Count].AV.Xform.Translation, &f_Diff);

							float f_AvatarLength = Qpo->Vec3d_Length(&f_Diff);

							if(f_AvatarLength < f_Length)
								{
								f_Length = f_AvatarLength;
								f_Index = f_Count;
								f_Touch = true;
								}
							}
						}
					}
				}

			if((f_Touch == true) && (player[g_Player]->attackon > 0) && (player[g_Player]->HB_Dead == 0))
				{
				float f_X = (Q_Forge->Forge[f_Index].AV.Xform.Translation.x - playerAV[g_Player]->Xform.Translation.x) * 0.2;
				float f_Y = (Q_Forge->Forge[f_Index].AV.Xform.Translation.z - playerAV[g_Player]->Xform.Translation.z) * 0.2;

				if(f_X > 2.9)
					{
					f_X = 2.9;
					}

				if(f_Y > 2.9)
					{
					f_Y = 2.9;
					}

				playerAV[g_Player]->Xform.Translation.x += f_X * _->TimeScale;
				playerAV[g_Player]->Xform.Translation.z += f_Y * _->TimeScale;
				}

#if 0
			if(_->TimeHole == 0)
				{
				g_ZoomFactor -= 0.05;

				if(g_ZoomFactor <= 0.0)
					{
					g_ZoomFactor = 0.0;
					}
				}
			else
				{
				g_ZoomFactor += 0.09;

				if(g_ZoomFactor >= 1.0)
					{
					g_ZoomFactor = 1.0;
					}
				}
#endif

			if(g_Player == 0)
				{
				f_Transport[0] = 0.0f;
				f_Transport[1] = 0.0f;
				f_Transport[2] = 0.0f;
				}
			else
				{
				f_Transport[0] = playerAV[g_Player]->Xform.Translation.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = playerAV[g_Player]->Xform.Translation.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (playerAV[g_Player]->Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1.0f;
				}

			f_Transport[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2));

			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
				// set the material diffuse color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
				// set the material specular color
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

				float transformation[896];

				int f_BoneCount = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount();

				int boneId;
				for(boneId = 0; boneId < 56; boneId++)
					{
					if(boneId < f_BoneCount)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
						transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
						transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
						transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;

						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						glUniform1i(mTextureUniformLocation, 0);
						}
					else
						{
						QunQuaternion rotationBoneSpace;// = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						rotationBoneSpace.clear();
						QunVector translationBoneSpace;// = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						translationBoneSpace.clear();
						//try second get all bone rotations etc allways

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId * 16)] = rotationMatrix.dxdx; transformation[(boneId * 16) + 4] = rotationMatrix.dxdy; transformation[(boneId * 16) + 8] = rotationMatrix.dxdz; transformation[(boneId * 16) + 12] = translationBoneSpace.x;
						transformation[(boneId * 16) + 1] = rotationMatrix.dydx; transformation[(boneId * 16) + 5] = rotationMatrix.dydy; transformation[(boneId * 16) + 9] = rotationMatrix.dydz; transformation[(boneId * 16) + 13] = translationBoneSpace.y;
						transformation[(boneId * 16) + 2] = rotationMatrix.dzdx; transformation[(boneId * 16) + 6] = rotationMatrix.dzdy; transformation[(boneId * 16) + 10] = rotationMatrix.dzdz; transformation[(boneId * 16) + 14] = translationBoneSpace.z;
						transformation[(boneId * 16) + 3] = 0.0; transformation[(boneId * 16) + 7] = 0.0; transformation[(boneId * 16) + 11] = 0.0; transformation[(boneId * 16) + 15] = 1.0;

						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						glUniform1i(mTextureUniformLocation, 0);
						}
					}

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
				glUniform1f(mTimeUniformLocation, Cube::random());

#if 0
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				else
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}

				if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}
#endif

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL) + playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			  ////////////////////////////////////
			 ////// Render Player Shadows ///////
			////////////////////////////////////
			if(player[g_Player]->ShadowsOn == true)
				{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glEnable(GL_BLEND);

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

					viewMatrix = MathHelper::SimpleViewMatrix();
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

					projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

					if(player[g_Player]->Team == 0)
						{
						f_Team[0] = 0.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 1)
						{
						f_Team[0] = 0.21;
						f_Team[1] = 0.0;
						f_Team[2] = 1.0;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 2)
						{
						f_Team[0] = 1.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 3)
						{
						f_Team[0] = 1.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.25;
						f_Team[3] = 1.0;
						}
					else if(player[g_Player]->Team == 4)
						{
						f_Team[0] = 0.5;
						f_Team[1] = 0.5;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}

					glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

					if(g_Player == 0)
						{
						f_Transport[0] = 0.0f;
						f_Transport[1] = 0.0f;
						f_Transport[2] = 0.0f;
						}
					else
						{
						f_Transport[0] = playerAV[g_Player]->Xform.Translation.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = playerAV[g_Player]->Xform.Translation.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (playerAV[g_Player]->Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1.0f;
						}

					f_Transport[3] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height / 100) - 0.5) * 2)), player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC * (((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight / 100) - 0.5) * 2));
				
					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Player Mesh Settings ///
					hardwareMeshId = 0;
					for(hardwareMeshId=0;hardwareMeshId<player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
						{
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
						// set the material diffuse color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
						// set the material specular color
						player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
							{
							QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

							transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
							transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
							transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
							transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;
							
							//glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							glUniform1i(mTextureUniformLocation, 0);
							}

						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
						glUniform1f(mTimeUniformLocation, Cube::random());

#if 0
						if(hardwareMeshId < 38)
							{
							diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}

						if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
#endif

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	 ///////////////////////////////////////
	////// Render AI NON-Player Mesh //////
	pVector PosTest;
	for(int i = 0; i < _->NomAI; i++)
		{
		if((f_View.is_inside(pVector(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z))) && (Q_Forge->Forge[i].HB_DeadTimer > 0) && (Q_Forge->Forge[i].LIVE == 1) && (Q_Forge->Forge[i].AV.Avatar.Mesh->m_rebuild == 0))
			{
			glDisable(GL_BLEND);

			ag_Calc_Light(Cube::BiVector(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z));

			glUniform4fv(mLightPosUniformLocation, 10, &(g_LightPos[0]));
			glUniform4fv(mLightColorUniformLocation, 10, &(g_LightColor[0]));
			glUniform1f(mLightNomUniformLocation, g_LightNom);

			if(mProgram == 0)
				{
				return;
				}

			glUseProgram(mProgram);

			//Vertex Array - Position
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glEnableVertexAttribArray(m0AttribLocation);
			glVertexAttribPointer(m0AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Normal Array - Normals
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glEnableVertexAttribArray(m2AttribLocation);
			glVertexAttribPointer(m2AttribLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Texture Coords
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glEnableVertexAttribArray(m4AttribLocation);
			glVertexAttribPointer(m4AttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - Weights
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glEnableVertexAttribArray(m1AttribLocation);
			glVertexAttribPointer(m1AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Vertex Array - MatrixIndex
			glBindBuffer(GL_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glEnableVertexAttribArray(m3AttribLocation);
			glVertexAttribPointer(m3AttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

			//Elements Array - Face Indices
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

			 ////////////////////////////////
			////// Render Avatar Mesh //////
			glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[i].AV.Xform.Matrix.mf);

			MathHelper::Matrix4 viewMatrix = MathHelper::SimpleViewMatrix();
			glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

			MathHelper::Matrix4 projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
			glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

			if(Q_Forge->Forge[i].Team == 0)
				{
				f_Team[0] = 0.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 1)
				{
				f_Team[0] = 0.21;
				f_Team[1] = 0.0;
				f_Team[2] = 1.0;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 2)
				{
				f_Team[0] = 1.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 3)
				{
				f_Team[0] = 1.0;
				f_Team[1] = 0.0;
				f_Team[2] = 0.25;
				f_Team[3] = 1.0;
				}
			else if(Q_Forge->Forge[i].Team == 4)
				{
				f_Team[0] = 0.5;
				f_Team[1] = 0.5;
				f_Team[2] = 0.0;
				f_Team[3] = 1.0;
				}

			glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

			if(g_ZoomFactor == 0 || 1)
				{
				f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - playerAV[0]->Xform.Translation.x;
				f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y - playerAV[0]->Xform.Translation.y;
				f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1.0f;
				}
			else
				{
				f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - (playerAV[g_Player]->Xform.Translation.x * g_ZoomFactor);
				f_Transport[1] = (Q_Forge->Forge[i].AV.Xform.Translation.z + Q_Forge->Forge[i].AV.Xform.Translation.y) - ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y) * g_ZoomFactor);
				f_Transport[2] = 0.0f;
				}

			f_Transport[3] = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Height / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2));

			glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

			/// Player Mesh Settings ///
			int hardwareMeshId = 0;
			for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
				// set the material diffuse color
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
				// set the material specular color
				Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

				float transformation[896];

				int boneId;
				for(boneId = 0; boneId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
					transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
					transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
					transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;

					//glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					glUniform1i(mTextureUniformLocation, 0);
					}

				glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
				glUniform1f(mTimeUniformLocation, Cube::random());

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].AV.Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				}

			//###- Render avatar shadows
			if(Q_Forge->Forge[i].ShadowsOn == true)
				{
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				glEnable(GL_BLEND);

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
					glUniformMatrix4fv(mModelUniformLocation, 1, GL_FALSE, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);

					viewMatrix = MathHelper::SimpleViewMatrix();
					glUniformMatrix4fv(mViewUniformLocation, 1, GL_FALSE, &(viewMatrix.m[0][0]));

					projectionMatrix = MathHelper::SimpleProjectionMatrix(float(g_Width) / float(g_Height));
					glUniformMatrix4fv(mProjUniformLocation, 1, GL_FALSE, &(projectionMatrix.m[0][0]));

					if(Q_Forge->Forge[i].Team == 0)
						{
						f_Team[0] = 0.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 1)
						{
						f_Team[0] = 0.21;
						f_Team[1] = 0.0;
						f_Team[2] = 1.0;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 2)
						{
						f_Team[0] = 1.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 3)
						{
						f_Team[0] = 1.0;
						f_Team[1] = 0.0;
						f_Team[2] = 0.25;
						f_Team[3] = 1.0;
						}
					else if(Q_Forge->Forge[i].Team == 4)
						{
						f_Team[0] = 0.5;
						f_Team[1] = 0.5;
						f_Team[2] = 0.0;
						f_Team[3] = 1.0;
						}

					glUniform4fv(mTeamUniformLocation, 1, &(f_Team[0]));

					if(g_ZoomFactor == 0 || 1)
						{
						f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - playerAV[0]->Xform.Translation.x;
						f_Transport[1] = Q_Forge->Forge[i].AV.Xform.Translation.y - playerAV[0]->Xform.Translation.y;
						f_Transport[2] = (Q_Forge->Forge[i].AV.Xform.Translation.z - playerAV[0]->Xform.Translation.z) * -1.0f;
						}
					else
						{
						f_Transport[0] = Q_Forge->Forge[i].AV.Xform.Translation.x - (playerAV[g_Player]->Xform.Translation.x * g_ZoomFactor);
						f_Transport[1] = (Q_Forge->Forge[i].AV.Xform.Translation.z + Q_Forge->Forge[i].AV.Xform.Translation.y) - ((playerAV[g_Player]->Xform.Translation.z + playerAV[g_Player]->Xform.Translation.y) * g_ZoomFactor);
						f_Transport[2] = 0.0f;
						}

					f_Transport[3] = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Height / 100) - 0.5) * 2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC * (((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight / 100) - 0.5) * 2));

					glUniform4fv(mAvatarTranslationUniformLocation, 1, &(f_Transport[0]));

					/// Avatar Mesh Settings ///
					hardwareMeshId = 0;
					for(hardwareMeshId=0;hardwareMeshId<Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
						{
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

#if 0
						unsigned char meshColor[4];
						float materialColor[4];
						float diffuseColor[4];
						float specularColor[4];

						// set the material ambient color
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
						materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
						// set the material diffuse color
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
						diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
						// set the material specular color
						Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
						specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
						//*glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
						// set the material shininess factor
						float shininess;
						shininess = 50.0f; //m_calHardwareModel->getShininess();
						//*glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
#endif

						float transformation[896];

						int boneId;
						for(boneId = 0; boneId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
							{
							QunQuaternion rotationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());
							QunVector translationBoneSpace = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton());

							QunMatrix rotationMatrix = rotationBoneSpace;

							transformation[(boneId*16)]=rotationMatrix.dxdx;transformation[(boneId*16)+4]=rotationMatrix.dxdy;transformation[(boneId*16)+8]=rotationMatrix.dxdz;transformation[(boneId*16)+12]=translationBoneSpace.x;
							transformation[(boneId*16)+1]=rotationMatrix.dydx;transformation[(boneId*16)+5]=rotationMatrix.dydy;transformation[(boneId*16)+9]=rotationMatrix.dydz;transformation[(boneId*16)+13]=translationBoneSpace.y;
							transformation[(boneId*16)+2]=rotationMatrix.dzdx;transformation[(boneId*16)+6]=rotationMatrix.dzdy;transformation[(boneId*16)+10]=rotationMatrix.dzdz;transformation[(boneId*16)+14]=translationBoneSpace.z;
							transformation[(boneId*16)+3]=0.0;transformation[(boneId*16)+7]=0.0;transformation[(boneId*16)+11]=0.0;transformation[(boneId*16)+15]=1.0;

							//glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, (GLuint)Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
							glUniform1i(mTextureUniformLocation, 0);
							}
						
						glUniformMatrix4fv(mMatricesUniformLocation, 56, GL_FALSE, &(transformation[0]));
						glUniform1f(mTimeUniformLocation, Cube::random());

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						else glDrawElements(GL_TRIANGLES, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getStartIndex()));
						}
					}
				}
			}
		}

	 /////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif
}

void unRenderer::draw_material_avatars_shell(bool relief)
{
#if 0
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	////////////////////////////////
	////// Render Player Mesh //////

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#ifndef QAGEMODE_SURGERY
	if(player[g_Player]->AirJinkRotFG == 1)
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Viewform.mf);
		}
	else
		{
		glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
		glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);
		}
#endif

	playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
	playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

	glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

	std::vector<QunBone *>& vectorBone = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

	if(!player[g_Player]->ShadowsOn)
		{
		/// Player Mesh Settings ///
		int hardwareMeshId = 0;
		for(hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
			{
			unsigned char meshColor[4];
			float materialColor[4];
			float diffuseColor[4];
			float specularColor[4];

			// set the material ambient color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
			// set the material diffuse color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
			// set the material specular color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
			specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
				{
				QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
				QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

				QunMatrix rotationMatrix = rotationBoneSpace;

	#if 0
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
	#endif

	#if 0
				if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
	#endif

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

				////QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, (GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
				}

			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
			diffuseColor[0] = 1;
			diffuseColor[1] = 1;
			diffuseColor[2] = 1;

			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 0 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 1 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 2 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 9 ||
			   player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 10)
				{
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				}
			else
				{
				diffuseColor[0] = 0;
				diffuseColor[1] = 0;
				diffuseColor[2] = 0;
				}

			if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
				{
				diffuseColor[0] = 1;
				diffuseColor[1] = 1;
				diffuseColor[2] = 1;
				}
	#endif

			//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
			//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
			//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
			//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

			//pVector lightpos;
			//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
			//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
			//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

			pVector eyepos;
			eyepos.x = g_render->camera.pos.x;
			eyepos.y = g_render->camera.pos.y;
			eyepos.z = g_render->camera.pos.z;

			//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
			//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

			if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			}
		}
	else // Shadows ON
		{
		//glDisable(GL_DEPTH_TEST);
		//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		//glEnable(GL_BLEND);

		/// Player Mesh Settings ///
		int hardwareMeshId = 0;
		for(hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
			{
			unsigned char meshColor[4];
			float materialColor[4];
			float diffuseColor[4];
			float specularColor[4];

			// set the material ambient color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
			materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
			// set the material diffuse color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
			diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
			// set the material specular color
			playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
			specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
			glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
			// set the material shininess factor
			float shininess;
			shininess = 50.0f; //m_calHardwareModel->getShininess();
			glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

			float transformation[500];

			int boneId;
			for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
				{
				QunQuaternion rotationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
				QunVector translationBoneSpace = vectorBone[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

				QunMatrix rotationMatrix = rotationBoneSpace;

#if 0
				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;
#endif

#if 0
				if(playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->m_vectorSetPos[hardwareMeshId] == -1)
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
#endif

				transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
				transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
				transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

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
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

				//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
				cgSetSamplerState(m_meshcolormap);

				////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

				//glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, (GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
				}
		
			//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
			if(player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 0 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 1 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 2 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 9 ||
				player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BDataID == 10)
				{
				if(hardwareMeshId < 38)
					{
					diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
					diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
					diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
					}
				else
					{
					diffuseColor[0] = 1;
					diffuseColor[1] = 1;
					diffuseColor[2] = 1;
					}
				}

			if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
				{
				diffuseColor[0] = 1;
				diffuseColor[1] = 1;
				diffuseColor[2] = 1;
				}

#if 0
			diffuseColor[0] += 5;
			diffuseColor[1] += 5;
			diffuseColor[2] += 5;
#endif
#endif

			//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
			//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
			//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
			//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

			//pVector lightpos;
			//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
			//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
			//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

			pVector eyepos;
			eyepos.x = g_render->camera.pos.x;
			eyepos.y = g_render->camera.pos.y;
			eyepos.z = g_render->camera.pos.z;

			//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
			//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

			//glPushMatrix();
			//RenderToTexture_Prep();

			if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));

			//RenderToTexture_Tex();
			//glPopMatrix();

			//if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			//else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
			}
		}

	//glDisable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

	////////////////////////////////////
	////// Render Player Shadows ///////

#if 0
	if(player[g_Player]->ShadowsOn)
		{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			glDisable(GL_DEPTH_TEST);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glEnable(GL_BLEND);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
				{
				/// Player Mesh Settings ///
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D, (GLuint)(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
					diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
					diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
	#endif

					diffuseColor[0] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
					diffuseColor[1] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
					diffuseColor[2] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
					//*cgGLSetParameter1f(m_meshAlpha, player[g_Player]->Shadows[SCRAM].Avatar.m_Alpha/255);

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			}
		}

	glDisable(GL_BLEND);
#endif

	////////////////////////////////////
	////// Render NON-Player Mesh //////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
		PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
		PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

		if(Q_Forge->Forge[i].LIVE == 1 && g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0)
			{
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

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

			Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
			Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

			glScalef(Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)), Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)),Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2)));

			std::vector<QunBone *>& vectorBoneAI = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			if(!Q_Forge->Forge[i].ShadowsOn)
				{
					/// Avatar Mesh Settings ///
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
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
					for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

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

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D, (GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(Q_Forge->Forge[i].CharDATA.BDataID == 0 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 1 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 2 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 9 ||
					   Q_Forge->Forge[i].CharDATA.BDataID == 10)
						{
						if(hardwareMeshId < 38 && hardwareMeshId != 24 && hardwareMeshId != 18 && hardwareMeshId != 0 && hardwareMeshId != 2 && hardwareMeshId != 3 && hardwareMeshId != 4 && hardwareMeshId != 5 && hardwareMeshId != 6 && hardwareMeshId != 7 && hardwareMeshId != 8 && hardwareMeshId != 9 && hardwareMeshId != 10 && hardwareMeshId != 11 &&
							hardwareMeshId != 17 && hardwareMeshId != 19 && hardwareMeshId != 20 && hardwareMeshId != 21 && hardwareMeshId != 22 && hardwareMeshId != 23 && hardwareMeshId != 28 && hardwareMeshId != 29 && hardwareMeshId != 30 && hardwareMeshId != 31)
							{
							diffuseColor[0] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

#if 0
					if(hardwareMeshId < 38)
						{
						diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
						diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
						diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}
#endif

					if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
					//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].AV.Avatar.m_Alpha);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			else //Shadows ON
				{
				int hardwareMeshId = 0;
				for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount ; hardwareMeshId++)
					{
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
					for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneAI[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

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

						////QDglActiveTextureARB(GL_TEXTURE0_ARB);
						glBindTexture(GL_TEXTURE_2D, (GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(Q_Forge->Forge[i].CharDATA.BDataID == 0 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 1 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 2 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 9 ||
						Q_Forge->Forge[i].CharDATA.BDataID == 10)
						{
						if(hardwareMeshId < 38 && hardwareMeshId != 24 && hardwareMeshId != 18 && hardwareMeshId != 0 && hardwareMeshId != 2 && hardwareMeshId != 3 && hardwareMeshId != 4 && hardwareMeshId != 5 && hardwareMeshId != 6 && hardwareMeshId != 7 && hardwareMeshId != 8 && hardwareMeshId != 9 && hardwareMeshId != 10 && hardwareMeshId != 11 &&
							hardwareMeshId != 17 && hardwareMeshId != 19 && hardwareMeshId != 20 && hardwareMeshId != 21 && hardwareMeshId != 22 && hardwareMeshId != 23 && hardwareMeshId != 28 && hardwareMeshId != 29 && hardwareMeshId != 30 && hardwareMeshId != 31)
							{
							diffuseColor[0] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
							diffuseColor[1] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
							diffuseColor[2] = (Q_Forge->Forge[i].CharDATA.AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
							}
						else
							{
							diffuseColor[0] = 1;
							diffuseColor[1] = 1;
							diffuseColor[2] = 1;
							}
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

	#if 0
					if(hardwareMeshId < 38)
						{
						diffuseColor[0] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255) + 0.25;
						diffuseColor[1] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255) + 0.25;
						diffuseColor[2] = (player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255) + 0.25;
						}
					else
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}
	#endif

					if(diffuseColor[0] == 0.25 && diffuseColor[1] == 0.25 && diffuseColor[2] == 0.25)
						{
						diffuseColor[0] = 1;
						diffuseColor[1] = 1;
						diffuseColor[2] = 1;
						}

#if 0
					diffuseColor[0] *= 5;
					diffuseColor[1] *= 5;
					diffuseColor[2] *= 5;
#endif

					//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
					//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
					//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].AV.Avatar.m_Alpha);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}

			//glDisable(GL_BLEND);
			//glEnable(GL_DEPTH_TEST);

			////////////////////////////////////
			////// Render AI Shadows ///////////

#if 0
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

					glColor4f(1.0f, 1.0f, 1.0f, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha/255);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
						{
						int hardwareMeshId = 0;
						for(hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
							{
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
							for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
								{
								QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
								QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

								QunMatrix rotationMatrix = rotationBoneSpace;

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

								////QDglActiveTextureARB(GL_TEXTURE0_ARB);
								glBindTexture(GL_TEXTURE_2D, (GLuint)(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
								}

							for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
								{
								transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
								}

							//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

							if(hardwareMeshId < 38)
								{
								diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.RED[hardwareMeshId] / 255;
								diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
								diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
								}
							else
								{
								diffuseColor[0] = 0;
								diffuseColor[1] = 0;
								diffuseColor[2] = 0;
								}

							diffuseColor[0] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
							diffuseColor[1] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];
							diffuseColor[2] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt];

							//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
							//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
							//*cgGLSetParameter4fv(m_meshLightVec, &_->mesh->light[0].pos.x);
							//*cgGLSetParameter1f(m_meshAlpha, Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha);

							if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
							else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
							}
						}
					}
#endif
				}
				
			glDisable(GL_BLEND);
			}

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
#endif
}

void unRenderer::draw_alpha_shadows(void)
{
#if 0
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Bind CG programs
	bind_mesh_vertex();
	bind_blur();
	////*cgGLBindProgram(m_frag_alpha);
	////*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	//*cgGLSetParameter3fv(m_alphaView, &g_render->camera.pos.x);

	//*cgGLSetParameter2f(m_alphaPlanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	////////////////////////////////////
	////// Player Shadow Amount  ///////

	if(player[g_Player]->ShadowsOn)
		{
		player[g_Player]->ShadowsAMT += 0.1;
		if(player[g_Player]->ShadowsAMT > 1) player[g_Player]->ShadowsAMT = 1;
		}
	else
		{
		player[g_Player]->ShadowsAMT -= 0.1;
		if(player[g_Player]->ShadowsAMT <= 0) player[g_Player]->ShadowsAMT = 0;
		}

	////////////////////////////////////
	////// Render Player Shadows ///////
	if(player[g_Player]->ShadowsAMT > 0)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

		std::vector<QunBone *>& vectorBonePS = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

		std::vector<QunBone *>& vectorBoneSS = player[g_Player]->Shadows[1].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

		for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
			glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

			glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

			if(player[g_Player]->Aposestate == 73) //JSRUSH
				{
				/// Player Mesh Settings ///
				for(int hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBoneSS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBoneSS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif

						////QDglActiveTextureARB(GL_TEXTURE4_ARB);
						glBindTexture(GL_TEXTURE_2D, (GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * player[g_Player]->ShadowsAMT * playerAV[g_Player]->Avatar.Scale.y;
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					//diffuseColor[0] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
					//diffuseColor[1] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
					//diffuseColor[2] = (1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 5;
	#endif

					//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
					//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
					////*cgGLSetParameter1f(m_alphaAlpha, (float)((((player[g_Player]->ShadowEffect_Scale[f_MeshCnt] - 1) * 0.95) * 0.5) + 0.05));
					//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			else
				{
				/// Player Mesh Settings ///
				for(int hardwareMeshId=0; hardwareMeshId < playerAV[g_Player]->Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
					{
					unsigned char meshColor[4];
					float materialColor[4];
					float diffuseColor[4];
					float specularColor[4];

					// set the material ambient color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
					materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
					// set the material diffuse color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
					diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
					// set the material specular color
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
					specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
					glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
					// set the material shininess factor
					float shininess;
					shininess = 50.0f; //m_calHardwareModel->getShininess();
					glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
						{
						QunQuaternion rotationBoneSpace = vectorBonePS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
						QunVector translationBoneSpace = vectorBonePS[(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

						////QDglActiveTextureARB(GL_TEXTURE4_ARB);
						glBindTexture(GL_TEXTURE_2D, (GLuint)(*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
						}

					for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
						{
						transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * player[g_Player]->ShadowsAMT * playerAV[g_Player]->Avatar.Scale.y;
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
					diffuseColor[0] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
					diffuseColor[1] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
					diffuseColor[2] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
	#endif

					//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
					//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
					//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
					////*cgGLSetParameter1f(m_alphaAlpha, (float)((((player[g_Player]->ShadowEffect_Scale[f_MeshCnt] - 1) * 0.95) * 0.5) + 0.05));
					//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

					//pVector lightpos;
					//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
					//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
					//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

					pVector eyepos;
					eyepos.x = g_render->camera.pos.x;
					eyepos.y = g_render->camera.pos.y;
					eyepos.z = g_render->camera.pos.z;

					//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
					//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					else glDrawElements(GL_TRIANGLES, (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*playerAV[g_Player]->Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
					}
				}
			}


		for(SCRAM = 1; SCRAM < 4; SCRAM++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

			glTranslatef(player[g_Player]->Shadows[SCRAM].Xform.Translation.x, player[g_Player]->Shadows[SCRAM].Xform.Translation.y, player[g_Player]->Shadows[SCRAM].Xform.Translation.z);
			glMultMatrixf(player[g_Player]->Shadows[SCRAM].Xform.Matrix.mf);

			playerAV[g_Player]->Avatar.Scale.x = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.y = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Height/100)-0.5)*2));
			playerAV[g_Player]->Avatar.Scale.z = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AvatarSCALE + (AVSCALEINC*(((player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].BodySKILL.Weight/100)-0.5)*2));

			glScalef(playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y, playerAV[g_Player]->Avatar.Scale.y);

			std::vector<QunBone *>& vectorBonePS = player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

			/// Player Mesh Settings ///
			for(int hardwareMeshId=0; hardwareMeshId < player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
				{
				unsigned char meshColor[4];
				float materialColor[4];
				float diffuseColor[4];
				float specularColor[4];

				// set the material ambient color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
				materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
				
				// set the material diffuse color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
				diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
				
				// set the material specular color
				player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
				specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
				glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
				
				// set the material shininess factor
				float shininess;
				shininess = 50.0f; //m_calHardwareModel->getShininess();
				glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
					{
					QunQuaternion rotationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
					QunVector translationBoneSpace = vectorBonePS[(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif

					////QDglActiveTextureARB(GL_TEXTURE4_ARB);
					glBindTexture(GL_TEXTURE_2D, (GLuint)(*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
				diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.RED[hardwareMeshId] / 255;
				diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
				diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.CurrCHAR].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
#endif

				//diffuseColor[0] /= 2;
				//diffuseColor[1] /= 2;
				//diffuseColor[2] /= 2;

				//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
				//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
				//*cgGLSetParameter1f(m_alphaAlpha, (float)(player[g_Player]->Shadows[SCRAM].Avatar.m_Alpha/255));

				//pVector lightpos;
				//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
				//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
				//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				else glDrawElements(GL_TRIANGLES, (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*player[g_Player]->Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
				}
			}
		}

	////////////////////////////////////
	////// Render AI Shadows ///////////

	pVector PosTest;
	for(i = 0; i < _->NomAI; i++)
		{
		if(Q_Forge->Forge[i].ShadowsOn && Q_Forge->Forge[i].HB_Dead == 0)
			{
			Q_Forge->Forge[i].ShadowsAMT += 0.1;
			if(Q_Forge->Forge[i].ShadowsAMT > 1) Q_Forge->Forge[i].ShadowsAMT = 1;
			}
		else
			{
			Q_Forge->Forge[i].ShadowsAMT -= 0.1;
			if(Q_Forge->Forge[i].ShadowsAMT <= 0) Q_Forge->Forge[i].ShadowsAMT = 0;
			}

		if(Q_Forge->Forge[i].ShadowsAMT > 0)
			{
			PosTest.x = Q_Forge->Forge[i].AV.Xform.Translation.x;
			PosTest.y = Q_Forge->Forge[i].AV.Xform.Translation.y + 35;
			PosTest.z = Q_Forge->Forge[i].AV.Xform.Translation.z;

			if(g_render->view.is_inside(PosTest) && Q_Forge->Forge[i].HB_DeadTimer > 0 && Q_Forge->Forge[i].LIVE == 1)
				{
				//Vertex Array - Position
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[0]);
				glVertexPointer(3, GL_FLOAT, 0, NULL);
				glEnableClientState(GL_VERTEX_ARRAY);

				//Normal Array - Normals
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[2]);
				glNormalPointer(GL_FLOAT, 0, 0);
				glEnableClientState(GL_NORMAL_ARRAY);

				//Vertex Array - Texture Coords
				glClientActiveTextureARB(GL_TEXTURE0_ARB);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[4]);
				glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				//Vertex Array - Weights
				glClientActiveTextureARB(GL_TEXTURE1_ARB);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[1]);
				glTexCoordPointer(4, GL_FLOAT, 0, 0);

				//Vertex Array - MatrixIndex
				glClientActiveTextureARB(GL_TEXTURE2_ARB);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[3]);
				glTexCoordPointer(4, GL_FLOAT, 0, 0);

				//Elements Array - Face Indices
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Q_Forge->Forge[i].AV.Avatar.Mesh->m_bufferObject[5]);

				for(int f_MeshCnt = 0; f_MeshCnt < player[g_Player]->ShadowEffect_Counter; f_MeshCnt++)
					{
					////// Set Camera //////
					glLoadIdentity();
					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					glTranslatef(Q_Forge->Forge[i].AV.Xform.Translation.x, Q_Forge->Forge[i].AV.Xform.Translation.y, Q_Forge->Forge[i].AV.Xform.Translation.z);
					glMultMatrixf(Q_Forge->Forge[i].AV.Xform.Matrix.mf);

					Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					glScalef(Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].AV.Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].AV.Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
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
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

							////QDglActiveTextureARB(GL_TEXTURE4_ARB);
							glBindTexture(GL_TEXTURE_2D, (GLuint)(*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
							}

						for(unsigned int f_Jit = 0; f_Jit < 500; f_Jit++)
							{
							transformation[f_Jit] *= player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * Q_Forge->Forge[i].ShadowsAMT * Q_Forge->Forge[i].AV.Avatar.Scale.y;
							}

						//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

#if 1
						diffuseColor[0] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
						diffuseColor[1] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
						diffuseColor[2] = player[g_Player]->ShadowEffect_Scale[f_MeshCnt] * 5;
#endif

						//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
						//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
						//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
						////*cgGLSetParameter1f(m_alphaAlpha, (float)Q_Forge->Forge[i].AV.Avatar.m_Alpha/255);
						//*cgGLSetParameter1f(m_alphaAlpha, (float)(((((1 - (player[g_Player]->ShadowEffect_Scale[f_MeshCnt] / 2)) * 0.95) * 0.5) * (Q_Forge->Forge[i].ShadowsAMT - 0.15)) / 2));

						//pVector lightpos;
						//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
						//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
						//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

						pVector eyepos;
						eyepos.x = g_render->camera.pos.x;
						eyepos.y = g_render->camera.pos.y;
						eyepos.z = g_render->camera.pos.z;

						//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
						//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].AV.Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}

				for(SCRAM = 1; SCRAM < 4; SCRAM++)
					{
					////// Set Camera //////
					glLoadIdentity();
					glMultMatrixf((float *)&g_render->camera.mat_t);
					glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

					glTranslatef(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.x, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.y, Q_Forge->Forge[i].Shadows[SCRAM].Xform.Translation.z);
					glMultMatrixf(Q_Forge->Forge[i].Shadows[SCRAM].Xform.Matrix.mf);

					Q_Forge->Forge[i].AV.Avatar.Scale.x = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.y = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Height/100)-0.5)*2));
					Q_Forge->Forge[i].AV.Avatar.Scale.z = Q_Forge->Forge[i].CharDATA.AvatarSCALE + (AVSCALEINC*(((Q_Forge->Forge[i].CharDATA.BodySKILL.Weight/100)-0.5)*2));

					glScalef(Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y, Q_Forge->Forge[i].AV.Avatar.Scale.y);

					std::vector<QunBone *>& vectorBoneAIS = Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_qunModel->getSkeleton()->getVectorBone();

					for(int hardwareMeshId=0; hardwareMeshId < Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_MeshData->m_MeshCount; hardwareMeshId++)
						{
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
						for(boneId = 0; boneId < (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BoneCount; boneId++)
							{
							QunQuaternion rotationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getRotationBoneSpace();
							QunVector translationBoneSpace = vectorBoneAIS[(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_BonesIndices[boneId]]->getTranslationBoneSpace();

							QunMatrix rotationMatrix = rotationBoneSpace;

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

							////QDglActiveTextureARB(GL_TEXTURE4_ARB);
							glBindTexture(GL_TEXTURE_2D, (GLuint)(*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_IntanceTexture);
							}

						//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

	#if 1
						diffuseColor[0] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.RED[hardwareMeshId] / 255;
						diffuseColor[1] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.GREEN[hardwareMeshId] / 255;
						diffuseColor[2] = player[g_Player]->BFO.CharDATA[player[g_Player]->BFO.AVATARDATA[i].CDATID].AngelCOLOURS.BLUE[hardwareMeshId] / 255;
	#endif

						//diffuseColor[0] /= 2;
						//diffuseColor[1] /= 2;
						//diffuseColor[2] /= 2;

						//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
						//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
						//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
						//*cgGLSetParameter1f(m_alphaAlpha, (float)(Q_Forge->Forge[i].Shadows[SCRAM].Avatar.m_Alpha/255));

						//pVector lightpos;
						//lightpos.x = mesh->light[1].pos.x - playerAV[g_Player]->Xform.Translation.x;
						//lightpos.y = mesh->light[1].pos.y - playerAV[g_Player]->Xform.Translation.y;
						//lightpos.z = mesh->light[1].pos.z - playerAV[g_Player]->Xform.Translation.z;

						pVector eyepos;
						eyepos.x = g_render->camera.pos.x;
						eyepos.y = g_render->camera.pos.y;
						eyepos.z = g_render->camera.pos.z;

						//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
						//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

						if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						else glDrawElements(GL_TRIANGLES, (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_FaceCount * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ (*Q_Forge->Forge[i].Shadows[SCRAM].Avatar.Mesh->m_HardMesh)[hardwareMeshId].m_StartIndex));
						}
					}
				}
			}
		}

	glDisable(GL_BLEND);

	unbind_mesh_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
#endif
}

void unRenderer::draw_alpha_energy(void)
{
#if 0
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_BLEND);

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_alpha);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	//*cgGLSetParameter3fv(m_alphaView, &g_render->camera.pos.x);

	//*cgGLSetParameter2f(m_alphaPlanes, 
		-g_render->farplane/(g_render->farplane-g_render->nearplane),
		-g_render->farplane*g_render->nearplane/(g_render->farplane-g_render->nearplane));

	glClientActiveTextureARB(GL_TEXTURE4_ARB);
	glBindTexture(GL_TEXTURE_2D, (GLuint)1);

	unsigned char meshColor[4];
	float materialColor[4];
	float diffuseColor[4];
	float specularColor[4];

	meshColor[0] = 1;
	meshColor[1] = 1;
	meshColor[2] = 1;
	meshColor[3] = 1;

	materialColor[0] = 1;
	materialColor[1] = 1;
	materialColor[2] = 1;
	materialColor[3] = 1;

	diffuseColor[0] = 1;
	diffuseColor[1] = 1;
	diffuseColor[2] = 1;
	diffuseColor[3] = 1;

	specularColor[0] = 1;
	specularColor[1] = 1;
	specularColor[2] = 1;
	specularColor[3] = 1;

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0/* && Q_LEnergy->LEnergy[f_instance].Live == 1*/)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				//*cgGLSetParameter4fv(m_alphaAmbient, materialColor);
				//*cgGLSetParameter4fv(m_alphaDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_alphaSpecular, specularColor);
				//*cgGLSetParameter1f(m_alphaAlpha, (float)Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha/255);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_alphaLightVec, &_->mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_alphaEyeVec, &eyepos.x);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);
				}
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	//bind_terrain_vertex();

	terrainMaterial->diffuse.x = 1;
	terrainMaterial->diffuse.y = 1;
	terrainMaterial->diffuse.z = 1;

	terrainMaterial->specular.x = 1;
	terrainMaterial->specular.y = 1;
	terrainMaterial->specular.z = 1;

	bind_vertex();

#if 0
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);
#else
	bind_normal();

	set_normal_params(terrainMaterial->diffuse, terrainMaterial->specular, 1, terrainMaterial->texid, terrainMaterial->texnormalid);
#endif

	int f_iterator;
	int f_layer;
	int f_instance;
	int f_index;

	trr::unTerrainCell* f_Cell;

#if 0
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_TerrainCell.size(); f_iterator++)
#else
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
#endif
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, (GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texnormalid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/

#if 0
				glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
#endif
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, (GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texnormalid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	
	set_relief_params(terrainMaterial->diffuse,terrainMaterial->specular,1,1,terrainMaterial->texid,terrainMaterial->texnormalid);

#if 0
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_TerrainCell.size(); f_iterator++)
#else
	for(f_iterator = 0; f_iterator < QActiveFrameWork->f_TrrBank->m_CellPop.size(); f_iterator++)
#endif
		{
		f_Cell = QActiveFrameWork->f_TrrBank->m_CellPop[f_iterator];

		for(f_layer = 0; f_layer < f_Cell->veclayer.size(); f_layer++)
			{
			////// Render Layer Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[0]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[2]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[4]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[1]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[3]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[5]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, (GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				//glBindTexture(GL_TEXTURE_2D, (GLuint)mesh->mat[0]->texid);
				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_IndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}

			// Render Seal Instances
			//Vertex Array - Position
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[6]);
			glVertexPointer(3, GL_FLOAT, 0, NULL);
			glEnableClientState(GL_VERTEX_ARRAY);

			//Normal Array - Normals
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[8]);
			glNormalPointer(GL_FLOAT, 0, 0);
			glEnableClientState(GL_NORMAL_ARRAY);

			//Vertex Array - Texture Coords
			glClientActiveTextureARB(GL_TEXTURE0_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[10]);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);

			//Vertex Array - Weights
			glClientActiveTextureARB(GL_TEXTURE1_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[7]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Vertex Array - MatrixIndex
			glClientActiveTextureARB(GL_TEXTURE2_ARB);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[9]);
			glTexCoordPointer(4, GL_FLOAT, 0, 0);

			//Elements Array - Face Indices
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_bufferObject[11]);

			for(f_instance = 0; f_instance < f_Cell->m_Instance.size(); f_instance++)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

				glTranslatef(f_Cell->m_Instance[f_instance]->x, f_Cell->m_Instance[f_instance]->y, f_Cell->m_Instance[f_instance]->z);
	
#if 0
				//QDglActiveTextureARB(GL_TEXTURE0_ARB);
				glBindTexture(GL_TEXTURE_2D, (GLuint)1);

				//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
				//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
				//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
				//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

				pVector eyepos;
				eyepos.x = g_render->camera.pos.x;
				eyepos.y = g_render->camera.pos.y;
				eyepos.z = g_render->camera.pos.z;

				//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
				//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

				//glDrawElements(GL_TRIANGLES, QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

				//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glBindTexture(GL_TEXTURE_2D, (GLuint)terrainMaterial->texid);

				glDrawElements(GL_TRIANGLES, f_Cell->veclayer[f_layer].m_BufferSet[0]->m_sIndexCounter, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
			}
		}

#if 0
	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	unbind_vertex();
	unbind_relief();

    ///// clear light //////
    glDisable(GL_LIGHTING);
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

void unRenderer::draw_material_shapes(bool relief)
{
#if 0
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
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[0]);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_VERTEX_ARRAY);

	//Vertex Array - Position
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[0]);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glEnableClientState(GL_VERTEX_ARRAY);

#if 1
	//Normal Array - Normals
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[2]);
	glNormalPointer(GL_FLOAT, 0, 0);
	glEnableClientState(GL_NORMAL_ARRAY);

	//Vertex Array - Texture Coords
	glClientActiveTextureARB(GL_TEXTURE0_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[4]);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//Vertex Array - Weights
	glClientActiveTextureARB(GL_TEXTURE1_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[1]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);

	//Vertex Array - MatrixIndex
	glClientActiveTextureARB(GL_TEXTURE2_ARB);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[3]);
	glTexCoordPointer(4, GL_FLOAT, 0, 0);
#endif

	//Elements Array - Face Indices
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_shape->m_bufferObject[5]);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, playerAV[g_Player]->Avatar.Mesh->m_bufferObject[5]);

	glLoadIdentity();
	glMultMatrixf((float *)&g_render->camera.mat_t);
	glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

	glTranslatef(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	////QDglActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D, (GLuint)1);

#if 0
	//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
	//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
	//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
	//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

	pVector eyepos;
	eyepos.x = g_render->camera.pos.x;
	eyepos.y = g_render->camera.pos.y;
	eyepos.z = g_render->camera.pos.z;

	//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
	//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

	//glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, (((int*)NULL) + 0));

	//glTranslatef(playerAV[g_Player]->Xform.Translation.x + 15, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

	glDrawElements(GL_TRIANGLES, f_shape->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

	///// Mesh Settings /////
	/*int hardwareMeshId;
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		float transformation[500];

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

			transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
			transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
			transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
			pMaterial *mat;
			mat=&mesh->mat[mesh->face[0].material];
			set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
			glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

			//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
			cgSetSamplerState(m_meshcolormap);

			////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
			}

		//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}*/

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);

	/////////////////////////////////////////////
	////// Render MESH Relief (UNFINISHED) //////

#if 0
	unbind_normal();
	bind_mesh_relief();

	///// Per Mesh Settings /////
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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

void unRenderer::draw_material_shape_instances(bool relief)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < f_ShapeBank->m_Shape[f_iterator]->m_Instance.size(); f_instance++)
			{
			glLoadIdentity();
			glMultMatrixf((float *)&g_render->camera.mat_t);
			glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
			glTranslatef(f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->x, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->y, f_ShapeBank->m_Shape[f_iterator]->m_Instance[f_instance]->z);
			//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

			glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[f_iterator]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

			///// Mesh Settings /////
			/*int hardwareMeshId;
			for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
				{
				playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

				float transformation[500];

				int boneId;
				for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
					{
					QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
					QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

					QunMatrix rotationMatrix = rotationBoneSpace;

					transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
					transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
					transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

#pragma message("FIXME:::Set RELIEF Map in Second Slot")
#if 0
					pMaterial *mat;
					mat=&mesh->mat[mesh->face[0].material];
					set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
					glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

					//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
					cgSetSamplerState(m_meshcolormap);

					////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
#endif
					}

				//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

				if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
				else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
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

void unRenderer::draw_material_shape_energy(bool relief)
{
#if 0
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Bind CG programs
	bind_terrain_vertex();
	//*cgGLBindProgram(m_frag_terrain);
	//*cgGLEnableProfile(CG_PROFILE_ARBFP1);

	int f_iterator;
	int f_instance;
	for(f_iterator = 0; f_iterator < f_ShapeBank->m_Shape.size(); f_iterator++)
		{
		//Vertex Array - Position
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[0]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glEnableClientState(GL_VERTEX_ARRAY);

		//Normal Array - Normals
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
		glEnableClientState(GL_NORMAL_ARRAY);

		//Vertex Array - Texture Coords
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[4]);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//Vertex Array - Weights
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[1]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Vertex Array - MatrixIndex
		glClientActiveTextureARB(GL_TEXTURE2_ARB);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[3]);
		glTexCoordPointer(4, GL_FLOAT, 0, 0);

		//Elements Array - Face Indices
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, f_ShapeBank->m_Shape[f_iterator]->m_BufferSet[0]->m_bufferObject[5]);

#if 0
		//*cgGLSetParameter4fv(m_meshAmbient, materialColor);
		//*cgGLSetParameter4fv(m_meshDiffuse, diffuseColor);
		//*cgGLSetParameter4fv(m_meshSpecular, specularColor);
		//*cgGLSetParameter1f(m_meshAlpha, playerAV[g_Player]->Avatar.m_Alpha);

		pVector eyepos;
		eyepos.x = g_render->camera.pos.x;
		eyepos.y = g_render->camera.pos.y;
		eyepos.z = g_render->camera.pos.z;

		//*cgGLSetParameter4fv(m_meshLightVec, &mesh->light[1].pos.x);
		//*cgGLSetParameter4fv(m_meshEyeVec, &eyepos.x);
#endif

		for(f_instance = 0; f_instance < _->MaxNomLEnergy; f_instance++)
			{
			if(Q_LEnergy->LEnergy[f_instance].EnergyBall.m_Alpha > 0)
				{
				glLoadIdentity();
				glMultMatrixf((float *)&g_render->camera.mat_t);
				glTranslatef(-g_render->camera.pos.x,-g_render->camera.pos.y,-g_render->camera.pos.z);

#pragma message("FIXME::Invert positioning for faster placement")
				glTranslatef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Xform.Translation.z);
				//glMultMatrixf(playerAV[g_Player]->Xform.Matrix.mf);

				glScalef(Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.x, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.y, Q_LEnergy->LEnergy[f_instance].EnergyBall.Scale.z);

				glBindTexture(GL_TEXTURE_2D, (GLuint)Medias->flame[Q_LEnergy->LEnergy[f_instance].BmpCountSP]);

				glDrawElements(GL_TRIANGLES, f_ShapeBank->m_Shape[Q_LEnergy->LEnergy[f_instance].EnergyBall.Avatar]->getFacesCount() * 3, GL_UNSIGNED_INT, NULL);

				///// Mesh Settings /////
				/*int hardwareMeshId;
				for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
					{
					playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

					float transformation[500];

					int boneId;
					for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
						{
						QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
						QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

						QunMatrix rotationMatrix = rotationBoneSpace;

						transformation[(boneId*12)]=rotationMatrix.dxdx;transformation[(boneId*12)+1]=rotationMatrix.dxdy;transformation[(boneId*12)+2]=rotationMatrix.dxdz;transformation[(boneId*12)+3]=translationBoneSpace.x;
						transformation[(boneId*12)+4]=rotationMatrix.dydx;transformation[(boneId*12)+5]=rotationMatrix.dydy;transformation[(boneId*12)+6]=rotationMatrix.dydz;transformation[(boneId*12)+7]=translationBoneSpace.y;
						transformation[(boneId*12)+8]=rotationMatrix.dzdx;transformation[(boneId*12)+9]=rotationMatrix.dzdy;transformation[(boneId*12)+10]=rotationMatrix.dzdz;transformation[(boneId*12)+11]=translationBoneSpace.z;

	#pragma message("FIXME:::Set RELIEF Map in Second Slot")
	#if 0
						pMaterial *mat;
						mat=&mesh->mat[mesh->face[0].material];
						set_normal_params(mat->diffuse,mat->specular,1,mat->texid,mat->texnormalid);
						glBindTexture(GL_TEXTURE_2D, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));

						//*cgGLSetTextureParameter(m_meshcolormap, (GLuint)playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getMapUserData(0));
						cgSetSamplerState(m_meshcolormap);

						////*cgGLSetMatrixParameterfr(m_meshmatrix, &transformation[boneId*12]);
	#endif
						}

					//*cgGLSetMatrixParameterArrayfr(m_meshrotationMatrices, 0, boneId, &transformation[0]);

					if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
					}*/
				}
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
	for(hardwareMeshId=0;hardwareMeshId<playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getHardwareMeshCount() ; hardwareMeshId++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->selectHardwareMesh(hardwareMeshId);

		unsigned char meshColor[4];	
		float materialColor[4];
		float diffuseColor[4];
		float specularColor[4];

		//// WARNING MAY BE ERRONEOUS

		// set the material ambient color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getAmbientColor(&meshColor[0]);
		materialColor[0] = meshColor[0] / 255.0f;  materialColor[1] = meshColor[1] / 255.0f; materialColor[2] = meshColor[2] / 255.0f; materialColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
		
		// set the material diffuse color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getDiffuseColor(&meshColor[0]);
		diffuseColor[0] = meshColor[0] / 255.0f;  diffuseColor[1] = meshColor[1] / 255.0f; diffuseColor[2] = meshColor[2] / 255.0f; diffuseColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
		
		// set the material specular color
		playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getSpecularColor(&meshColor[0]);
		specularColor[0] = meshColor[0] / 255.0f;  specularColor[1] = meshColor[1] / 255.0f; specularColor[2] = meshColor[2] / 255.0f; specularColor[3] = meshColor[3] / 255.0f;
		glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
		
		// set the material shininess factor
		float shininess;
		shininess = 50.0f; //m_calHardwareModel->getShininess();
		glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

		int boneId;
		for(boneId = 0; boneId < playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getBoneCount(); boneId++)
			{
			QunQuaternion rotationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getRotationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());
			QunVector translationBoneSpace = playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getTranslationBoneSpace(boneId, playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton());

			QunMatrix rotationMatrix = rotationBoneSpace;

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

		if(sizeof(QunIndex)==2) glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_SHORT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		else glDrawElements(GL_TRIANGLES, playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getFaceCount() * 3, GL_UNSIGNED_INT, (((QunIndex *)NULL)+ playerAV[g_Player]->Avatar.Mesh->m_calHardwareModel->getStartIndex()));
		}

	unbind_mesh_relief();
	unbind_mesh_vertex();
#endif

    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

    ///// clear light //////
    glDisable(GL_LIGHTING);
	//glClientActiveTextureARB(GL_TEXTURE0_ARB);
#endif
}

GLint unRenderer::getVertexUniformIndex(void)//*CGparameter parameter)
{
	const std::vector<float> zeroes(m_VertexMaxUniforms * 4, 0);

	//glProgramParameters4fvNV(GL_VERTEX_PROGRAM_NV, 0, m_VertexMaxUniforms, &zeroes[0]);

	const float ones[4] = {1, 1, 1, 1};
        
	//*cgGLSetParameterArray4f(parameter, 0, 1, ones);

	for (GLint i = 0; i < m_VertexMaxUniforms; ++i)
		{
		float modified[4];

		//glGetProgramParameterfvNV(GL_VERTEX_PROGRAM_NV, i, GL_PROGRAM_PARAMETER_NV, modified);

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

void unRenderer::draw_lights(pMesh *m, bool scissor, int f_AOGI, int f_whiteout, int f_FAAB_Camera)
{
	fb_bind_render(0);

	// 2D ortho porjection
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,m_sizex,0,m_sizey,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	glBlendFunc(GL_ONE,GL_ONE);
	glDisable(GL_BLEND);

	// draw ambient pass
	if(f_AOGI == AOGI_AROUND)
		{
		glDisable(GL_BLEND);

		mrt_bind_texture(-1); // bind all mrt textures

		bind_around();

		draw_rect(0, 0, m_sizex, m_sizey, false, false);
	
		unbind_around();
		}
	else
		{
#if 0
		glColor4fv(&m->ambient.x);
		printf("m->ambient.x %f m->ambient.y %f m->ambient.z %f m->ambient.w %f\n", m->ambient.x, m->ambient.y, m->ambient.z, m->ambient.w);
#else
		//glColor4f(0.45, 0.45 ,0.45, 0.45);
#endif

		glDisable(GL_BLEND);

		mrt_bind_texture(1);	// bind diffuse mrt texture
		draw_rect(0, 0, m_sizex, m_sizey, false,false);
		mrt_unbind_texture(1);
		//glColor4f(1, 1, 1, 1);
		
		mrt_bind_texture(-1); // bind all mrt textures
		}

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

			//glColor4f(1,1,1,0.075);

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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0,bloom_sx,0,bloom_sy,-1,1);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
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

void unRenderer::draw_avatars(void)
{
	try
		{
		draw_material_avatars(true);
		}
	catch (...)
		{
		int i = 1;
		}
}

void unRenderer::draw_geometry(pMesh *m,bool relief)
{
	//*mrt_bind_render();

	if(KEY_DOWN(QIN_F9) && (_->NomPntSprite < Q_PNTSPRITE_MAX))
		{
		//#### Initialise One Particle ####//
		Q_PntSprite->PntSprite[_->NomPntSprite].Type = QPOLY_TYPE_PNT;
		Q_PntSprite->PntSprite[_->NomPntSprite].RenderFlags = QPOLY_REND_NO_OCCLUDE;		//QPOLY_REND_DEPTH_SORT
		Q_PntSprite->PntSprite[_->NomPntSprite].Scale = 0.15;		//0.025f//0.002f
		Q_PntSprite->PntSprite[_->NomPntSprite].PartType = 2;

		Q_PntSprite->PntSprite[_->NomPntSprite].Alpha = 255;
		Q_PntSprite->PntSprite[_->NomPntSprite].Speed = 0;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.x = playerAV[g_Player]->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.y = playerAV[g_Player]->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].Pos.z = playerAV[g_Player]->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.x = playerAV[g_Player]->Xform.Translation.x;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.y = playerAV[g_Player]->Xform.Translation.y + 65;
		Q_PntSprite->PntSprite[_->NomPntSprite].InitPos.z = playerAV[g_Player]->Xform.Translation.z;
		Q_PntSprite->PntSprite[_->NomPntSprite].Direction = 0;

		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.x = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.y = (((float)rand() / 32767)-0.5)*3;
		Q_PntSprite->PntSprite[_->NomPntSprite].TraVec.z = (((float)rand() / 32767)-0.5)*3;

		Q_PntSprite->PntSprite[_->NomPntSprite].Live = 1;

		_->NomPntSprite++;

		Q.WriteNEWCharacterDataV3(&player[g_Player]->BFO);
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
			Q_HHSpike->HHSpike[_->NomSpikes].CenterPos = playerAV[g_Player]->Xform.Translation;
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
			if(_->NomSpikes > 750) _->NomSpikes = 0;

			jet++;
			}
		}

	float steering = 0;
	float acceleration = 0;
	bool handbrake = false;
	bool f_press = false;

	if(KEY_DOWN(QIN_KP4))
		{
		steering = -1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP6))
		{
		steering = 1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP8))
		{
		acceleration = 1;
		f_press = true;
		}

	if(KEY_DOWN(QIN_KP5))
		{
		acceleration = -1;
		f_press = true;
		}

	//*//SDL_mutexP(m_mutex_Mesh);

#if 1
	//###-- - Sense Vector - --###//
if(KEY_DOWN(QIN_KP4))
	{
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueshtX += 0.01;

		printf("Sense Vector Left WeaponvalueshtX - %f\n", WeaponvalueshtX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueshtX -= 0.01;

		printf("Sense Vector Left WeaponvalueshtX - %f\n", WeaponvalueshtX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueshtY += 0.01;

		printf("Sense Vector Up WeaponvalueshtY - %f\n", WeaponvalueshtY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueshtY -= 0.01;

		printf("Sense Vector Up WeaponvalueshtY - %f\n", WeaponvalueshtY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueshtZ += 0.01;

		printf("Sense Vector In WeaponvalueshtZ - %f\n", WeaponvalueshtZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueshtZ -= 0.01;

		printf("Sense Vector In WeaponvalueshtZ - %f\n", WeaponvalueshtZ);
		}
	}
else
	{
	if(KEY_DOWN(QIN_KP7))
		{
		WeaponvalueX += 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP1))
		{
		WeaponvalueX -= 0.01;

		printf("Sense Vector Left WeaponvalueX - %f\n", WeaponvalueX);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		WeaponvalueY += 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP2))
		{
		WeaponvalueY -= 0.01;

		printf("Sense Vector Up WeaponvalueY - %f\n", WeaponvalueY);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		WeaponvalueZ += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP3))
		{
		WeaponvalueZ -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP6))
		{
		WeaponvalueW += 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}

	if(KEY_DOWN(QIN_KP5))
		{
		WeaponvalueW -= 0.01;

		printf("Sense Vector In WeaponvalueZ - %f\n", WeaponvalueZ);
		}
	}
#endif

	if(f_press)
		{
		//*QActiveFrameWork->DigiMass->ControlVehicle(steering, acceleration, handbrake);
		}

#if 1	//Positioned for lighting
	if(QNetwork.m_Playing) QNetwork.PlayWorld(1.0f);
#endif

#if 0
	QActiveFrameWork->acQFrame();

	//*if(KEY_DOWN(QIN_u)) UNMessageCore->acPrintName(0);
#endif

	/**g_render->set_camera();

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_ONE,GL_ZERO);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//glColor4f(1,1,1,1);
	glClearColor(g_render->bgcolor.x,g_render->bgcolor.y,g_render->bgcolor.z,1);
	//glClearDepth(1);
	glDisable(GL_TEXTURE_2D);

	glColorMask(true,true,true,true);
	glDepthMask(true);

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);*/

	//*ClearBlur();

	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acNxRender(0, false);
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acBuffer();

	//QpoTransform f_transform;
	//Qpo->Avatar_GetBoneTransform(playerAV[g_Player]->operator ->(), "BIP01 R HAND", &f_transform);

	//f_ShapeBank->m_Shape[0]->m_Instance[0]->x = f_transform.Translation.x;
	//f_ShapeBank->m_Shape[0]->m_Instance[0]->y = f_transform.Translation.y;
	//f_ShapeBank->m_Shape[0]->m_Instance[0]->z = f_transform.Translation.z;

#ifdef QAGEMODE_SURGERY
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
	//playerAV[g_Player]->Avatar.Mesh->BlendAnim(35, valuepose, 1);
	//playerAV[g_Player]->Avatar.Mesh->BlendAnimPhysics(35, valuepose, 1);

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
	if(KEY_DOWN(QIN_g)) QActiveFrameWork->f_TrrBank->acAddInstance(0, playerAV[g_Player]->Xform.Translation.x + ((((float)rand() / 32767) * 300)-150), playerAV[g_Player]->Xform.Translation.y + ((((float)rand() / 32767) * 300)-150), playerAV[g_Player]->Xform.Translation.z + ((((float)rand() / 32767) * 300)-150));
#endif

	//f_CSpeechDlg->m_pVoice->GetStatus(&f_CSpeechDlg->m_VoiceStatus, NULL);
	//if(f_CSpeechDlg->m_VoiceStatus.dwRunningState == 1) f_CSpeechDlg->acVoice();

	if(KEY_DOWN(QIN_g))
		{
		if(!vecvarDpress[1])
			{
			vecvarDpress[1] = true;

			QpoVec3d f_playerin;
			Qpo->Transform_GetRight(&player[g_Player]->Camrot,&f_playerin);
			//*PxVec3 f_force(f_playerin.x * -35, f_playerin.y * -35, f_playerin.z * -35);
			//*QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 5, &f_force);
			//QActiveFrameWork->DigiMass->acCreateCubeV2(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 10, &f_force);
			}
		}
	else vecvarDpress[1] = false;

	if(KEY_DOWN(QIN_h) && 0)
		{
		if(!vecvarDpress[2])
			{
			vecvarDpress[2] = true;
#if 1
			QpoVec3d f_playerin;
			Qpo->Transform_GetRight(&player[g_Player]->Camrot,&f_playerin);
			//*PxVec3 f_force(f_playerin.x * -35, f_playerin.y * -35, f_playerin.z * -35);
#if 0
			QActiveFrameWork->DigiMass->acCreateSphere(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 5.0f, 1.0f);
#endif
			//QActiveFrameWork->DigiMass->acCreateCubeV3(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 60, playerAV[g_Player]->Xform.Translation.z), 10, &f_force);
			//*QActiveFrameWork->DigiMass->acCreateCube(PxVec3(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y + 105, playerAV[g_Player]->Xform.Translation.z), 17, &f_force);
#endif

#if 0
			playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();

			// get the skeleton we need to update
			QunSkeleton *pSkeleton;
			pSkeleton = playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton();

			// clear the skeleton state
			//pSkeleton->clearState();

			// get the bone vector of the skeleton
			std::vector<QunBone *>& vectorBone = pSkeleton->getVectorBone();

			// lock the skeleton state
			//pSkeleton->lockState();

			//QunBone *pBone = vectorBone[8];

			playerAV[g_Player]->Avatar.Mesh->m_RagDoll = Digi::DigiMassCore::instance()->acSkeletonPose(playerAV[g_Player]->Avatar.Mesh->m_qunModel->getSkeleton(), vectorBone);
			printf("Physics Ragdoll created %i\n", playerAV[g_Player]->Avatar.Mesh->m_RagDoll);

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

#if 1
	if(KEY_DOWN(QIN_h))
		{
		Q_ItemRef f_ItemREF = Q.CreatePlayerItem(150, 0, 17.25);
		}
#endif

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
				FILE* f_filecheck = nullptr;
				bool fileSwit = true;

				while(!f_filecheck)
					{
					int random = rand()%55000;

					itoa(random, casecntbuf, 10);

					std::string strname = "Recording";
					std::string strnumber = casecntbuf;
					strFilename = strname + strnumber;

					f_filecheck = fopen(strFilename.c_str(), "rb");
					}
				fclose(f_filecheck);

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
				//QNetwork.OpenTapeBuffer("Recording9034.txt");//
				//QNetwork.OpenTapeBuffer("Recording7719.txt");
				//QNetwork.OpenTapeBuffer("Recording26835.txt");

				//6
				//QNetwork.OpenTapeBuffer("Recording25554.txt");
				//QNetwork.OpenTapeBuffer("Recording8532.txt");
				QNetwork.OpenTapeBuffer("Recording3441.txt");

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

	//*g_render->set_camera();

#if 0	//@#@
	draw_depth_shape_energy();
#endif

	

#if 0	//@#@
	draw_depth_terrain_old();
#endif

	// DigiMass Player Character
	/*QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb.empty();
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[0] = playerAV[g_Player]->Xform.Translation.x - 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[1] = playerAV[g_Player]->Xform.Translation.y - 5;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._min[2] = playerAV[g_Player]->Xform.Translation.z - 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[0] = playerAV[g_Player]->Xform.Translation.x + 50;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[1] = playerAV[g_Player]->Xform.Translation.y + 95;
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb._max[2] = playerAV[g_Player]->Xform.Translation.z + 50;*/

#if 0
	QActiveFrameWork->DigiMass->m_Engine.m_Playeraabb.visualization();
#endif

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_depth_avatars();
#endif

#if 0
	//#### _ PLAYER FINAL COLLDET _ ####//
	player[g_Player]->finalcolldet_oldposCRT = player[g_Player]->finalcolldet_oldpos;
	player[g_Player]->finalcolldet_oldposCRT.y += 40;
	player[g_Player]->finalcolldet_Trans_CRT = playerAV[g_Player]->Xform.Translation;
	player[g_Player]->finalcolldet_Trans_CRT.y += 40;

	if(Qpo->Collision_RayTest(/*&playerAV[g_Player]->Mins, &playerAV[g_Player]->Maxs*/ NULL, NULL, &player[g_Player]->finalcolldet_oldposCRT, &player[g_Player]->finalcolldet_Trans_CRT, 0xffffffff, NULL, NULL, &player[g_Player]->Collision))
		{
		playerAV[g_Player]->Xform.Translation.x += (player[g_Player]->finalcolldet_oldpos.x - playerAV[g_Player]->Xform.Translation.x) * 15;
		playerAV[g_Player]->Xform.Translation.y += (player[g_Player]->finalcolldet_oldpos.y - playerAV[g_Player]->Xform.Translation.y) * 15;
		playerAV[g_Player]->Xform.Translation.z += (player[g_Player]->finalcolldet_oldpos.z - playerAV[g_Player]->Xform.Translation.z) * 15;
		}
	else
		{
		player[g_Player]->finalcolldet_oldpos = playerAV[g_Player]->Xform.Translation;
		}
#endif

#if 0
#if 1
	draw_depth_avatars();
#else
	draw_depth_avatars_shell();
#endif
#endif

	//*g_render->set_camera();


	//if(KEY_DOWN(QIN_0)) QActiveFrameWork->DigiMass->acSimulate();
	/*if(KEY_DOWN(QIN_9))*/ //QActiveFrameWork->DigiMass->acRender(true);
	//glTranslatef(0, 356, 0);

	//Item Positioning
	/*if(KEY_DOWN(QIN_d))
		{
		if(!vecvarDpress[16])
			{
			4++;
			if(4 > 11) 4 = 11;
			}

		vecvarDpress[16] = true;
		}
	else vecvarDpress[16] = false;

	if(KEY_DOWN(QIN_a))
		{
		if(!vecvarDpress[17])
			{
			4--;
			if(4 < 1) 4 = 1;
			}

		vecvarDpress[17] = true;
		}
	else vecvarDpress[17] = false;*/

	/*if(KEY_DOWN(QIN_KP6))
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


#if 0
	draw_depth_meshes();
#endif

	//*g_render->set_camera();

#if 0	//Weapon Testing
	draw_depth(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0]);
#endif

	//*g_render->set_camera();

	//draw_depth_terrain(m_TestModel);

#if 0
#if 1	//Trheight
	glTranslatef(0, +654.446411, 0);
#else
	glTranslatef(0, +2438.339233, 0);
#endif
#endif

#if 0
	draw_depth(m);
#endif

	//*glColorMask(true,true,true,true);
	//*glDepthMask(false);

#if 0
	draw_material(m, relief);
#endif

	//*g_render->set_camera();

#if 0
	//draw_material_terrain(m_TestModel, relief);
#endif

#if 0
	draw_material_meshes();
#endif

#if 0
	draw_material_mesh(QActiveFrameWork->meshstaticTemplates[1]->m_submesh[0], true);
#endif

#if 0	//@#@
	draw_material_terrain_old(relief);
#endif

	//glTranslatef(0, -356, 0);
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acRender(0, false);
	//QActiveFrameWork->DigiMass->acRender();
	//glTranslatef(0, 356, 0);

#ifdef QAGEMODE_SURGERY
	if(rendswitchA) draw_material_avatars(relief);
#endif

	//*g_render->set_camera();

#if 1
#if 1
	draw_material_avatars(relief);
#else
	draw_material_avatars_shell(relief);
#endif
#endif

	//printf("player[g_Player]->HB_Energy %f player[g_Player]->HB_MaxEnergy %f\n", player[g_Player]->HB_Energy, player[g_Player]->HB_MaxEnergy);
	if(KEY_DOWN(QIN_b)) player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;

// OLD POSITION

#if 0	//@#@
	draw_material_shape_instances(relief);
#endif

#if 0	//@#@
	draw_material_shape_energy(relief);
#endif

#if 0
	draw_material_shapes(relief);
#endif
	
	//QActiveFrameWork->f_TrrBank->m_TerrainCell[0]->acNxRender(0, false);

	//UNMessageCore->acPrintName(0);

#if 0
	Qpo->Player_RenderBoneBoundingBox("BIP01 R HAND");
	Qpo->Player_GetBoneBoxes("BIP01 R HAND", &pCorner, &DX, &DY, &DZ, &ColldetBox);

	Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

	player[g_Player]->LimPosBox.Matrix = playerAV[g_Player]->Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
	coldetresult = playerAV[g_Player]->Xform.Matrix.multiply_rotation(pCorner);

	player[g_Player]->LimPosBox.Translation.x = coldetresult.x + playerAV[g_Player]->Xform.Translation.x;
	player[g_Player]->LimPosBox.Translation.y = coldetresult.y + playerAV[g_Player]->Xform.Translation.y;
	player[g_Player]->LimPosBox.Translation.z = coldetresult.z + playerAV[g_Player]->Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&Box, xScale, yScale, zScale, &player[g_Player]->LimPosBox);
	Qpo->Box_Render(Box);

	Qpo->Camera_Set();

	ColldetBox.Min = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Min);
	ColldetBox.Max = playerAV[g_Player]->Xform.Matrix.multiply_rotation(ColldetBox.Max);

	glColor3f(0.25f, 0.25f, 1.0f);
	//*glBegin(GL_LINES);

		glVertex3f(ColldetBox.Min.x + playerAV[g_Player]->Xform.Translation.x, ColldetBox.Min.y + playerAV[g_Player]->Xform.Translation.y, ColldetBox.Min.z + playerAV[g_Player]->Xform.Translation.z);
		glVertex3f(ColldetBox.Max.x + playerAV[g_Player]->Xform.Translation.x, ColldetBox.Max.y + playerAV[g_Player]->Xform.Translation.y, ColldetBox.Max.z + playerAV[g_Player]->Xform.Translation.z);

	//*glEnd();

	Qpo->Avatar_RenderBoneBoundingBox(0, "BIP01 HEAD");
	Qpo->Avatar_GetBoneBoundingBox(0, "BIP01 HEAD", &pCorner, &DX, &DY, &DZ);

	Qpo->Transform_New_LeftUpIn(&player[g_Player]->LimPosBox, &DY, &DX, &DZ);
	Qpo->Transform_Orthonormalize(&player[g_Player]->LimPosBox);

	player[g_Player]->LimPosBox.Matrix = Q_Forge->Forge[0].AV.Xform.Matrix * player[g_Player]->LimPosBox.Matrix;
	coldetresult = Q_Forge->Forge[0].AV.Xform.Matrix.multiply_rotation(pCorner);

	player[g_Player]->LimPosBox.Translation.x = coldetresult.x + Q_Forge->Forge[0].AV.Xform.Translation.x;
	player[g_Player]->LimPosBox.Translation.y = coldetresult.y + Q_Forge->Forge[0].AV.Xform.Translation.y;
	player[g_Player]->LimPosBox.Translation.z = coldetresult.z + Q_Forge->Forge[0].AV.Xform.Translation.z;

	xScale = Qpo->Vec3d_Length(&DZ)/1.5;
	yScale = Qpo->Vec3d_Length(&DY)/1.5;
	zScale = Qpo->Vec3d_Length(&DX)/1.5;
	Qpo->Box_Set(&_->KokBox, xScale, yScale, zScale, &player[g_Player]->LimPosBox);
	Qpo->Box_Render(_->KokBox);

	if(Qpo->Box_DetectCollisionBetween(&_->KokBox, &Box)) printf("Trace Collision\n");
	else printf("Trace...\n");
#endif

#if 0
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

	//if(TimeAlter) _->TimeScale = 0.065;

	QActiveFrameWork->DigiMass->acSetTimeScale(_->TimeScale);
#endif

#if 0
	Qpo->Camera_Set();

	glColor3f(1.0f, 1.0f, 0.25f);
	//*glBegin(GL_LINES);

		glVertex3f(0,-297,0);
		glVertex3f(500, -297, 0);

	//*glEnd();
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
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetUp(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif

#if 0
	Qpo->Transform_GetIn(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	//*glEnd();
#endif


#ifdef QAGEMODE_SURGERY
	playerAV[g_Player]->Xform.Translation = Origin;
#endif

	//glLoadIdentity();

#ifdef QAGEMODE_SURGERY
	SurgeryFocus = m_PointLocator->getPos();
#endif

#if 0	// Trails Pose Reset
	playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
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

	for(SCRAM = 0; SCRAM < playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment.size(); SCRAM++)
		{
		playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);

		glColorMask(true,true,true,true);
		glDepthMask(false);

		playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[SCRAM]->draw(true);
		}
#endif

	/**glEnable(GL_BLEND);

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping*/

#if 0
	mrt_bind_texture(-1); // bind all mrt textures

	draw_alpha_shadows();

	draw_alpha_energy();

	mrt_unbind_texture(-1);
#endif

	//*Qpo->resetExecMode();

#if 0
	QActiveFrameWork->acQFrame();

	if(KEY_DOWN(QIN_u))
		{
		QActiveFrameWork->m_QSpawnPntController->m_SpawnON = true;
#if 0
		UNMessageCore->acPrintName(0);
#endif
		}
#endif

	//*Qpo->resetExecMode();

#if 0	// Positioned for after effects
	QActiveFrameWork->acWorldFrame();
#endif

#if 0
	Qpo->Transform_GetLeft(&playerAV[g_Player]->Xform,&playerAV[g_Player]->Up);
	Qpo->Camera_Set();
	glColor3f(1.0f, 0.0f, 0.0f);
	//*glBegin(GL_LINES);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x, playerAV[g_Player]->Xform.Translation.y, playerAV[g_Player]->Xform.Translation.z);
	glVertex3f(playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250), playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250), playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250));
	glVertex3f(0, 0, 0);
	glVertex3f(0, -250, 0);
	//*glEnd();
#endif

#if 0
	for(int f_gap = 0; f_gap < _->mesh->ncam; f_gap++)
		{
		//printf("CAM %i x %f y %f z %f\n", f_gap, _->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		Qpo->Camera_Set();
		//glColor3f(0.0f, 1.0f, 0.0f);	//GREEN
		////*glBegin(GL_LINES);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y + 175, _->mesh->cam[f_gap].pos.z);
		////*glEnd();
		//glColor3f(0.0f, 1.0f, 1.0f);	//GREEN
		////*glBegin(GL_LINES);
		//glVertex3f(_->mesh->cam[f_gap].pos.x, _->mesh->cam[f_gap].pos.y, _->mesh->cam[f_gap].pos.z);
		//glVertex3f(_->mesh->cam[f_gap].pos.x + (_->mesh->cam[f_gap].Z.x * 100), _->mesh->cam[f_gap].pos.y + (_->mesh->cam[f_gap].Z.y * 100), _->mesh->cam[f_gap].pos.z + (_->mesh->cam[f_gap].Z.z * 100));
		////*glEnd();
		}
#endif

	//for(int test = 0; test < _->NomAI; test++) Q_Forge->Forge[test].AV.Xform.Translation = Origin;

#if 0
#if 0
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
			player[g_Player]->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &Origin);
		player[g_Player]->MoveReactSpeed = 0;

		player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
		player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
		player[g_Player]->HB_Dead = 0;
		}
#else
	if(KEY_DOWN(QIN_k))
		{
		aero=0;
		while(aero < _->NomAI)
			{
			player[g_Player]->AvatarDMGSTORE[aero] = 0;
			aero++;
			}

		Qpo->Vec3d_Copy(&playerAV[g_Player]->Xform.Translation, &Origin);
		player[g_Player]->MoveReactSpeed = 0;

		player[g_Player]->HB_Health = player[g_Player]->HB_MaxHealth;
		player[g_Player]->HB_Energy = player[g_Player]->HB_MaxEnergy;
		player[g_Player]->HB_Dead = 0;
		}
#endif
#endif

#if 0
	if(KEY_DOWN(QIN_KP4))
		{
		f_GlobalAxisVector.x -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP5))
		{
		f_GlobalAxisVector.y -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP6))
		{
		f_GlobalAxisVector.z -= 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP7))
		{
		f_GlobalAxisVector.x += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP8))
		{
		f_GlobalAxisVector.y += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP9))
		{
		f_GlobalAxisVector.z += 0.01;
		QActiveFrameWork->DigiMass->acJointSetGlobalAxis(0, f_GlobalAxisVector);
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}

	if(KEY_DOWN(QIN_KP0))
		{
		printf("GlobalAxis %i Vector x %f y %f z %f\n", 0, f_GlobalAxisVector.x, f_GlobalAxisVector.y, f_GlobalAxisVector.z);
		}
#endif

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	/**glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();

	QActiveFrameWork->trrcursor->acRender();*/

	//QActiveFrameWork->DigiMass->m_Engine.acDraw(0, 1);

	//QActiveFrameWork->DigiMass->m_Engine.m_trrCell->acRenderFloor(0, 1);

#if 0
	QpoVec3d f_start;
	QpoVec3d f_end;

	f_start.x = playerAV[g_Player]->Xform.Translation.x;
	f_start.y = playerAV[g_Player]->Xform.Translation.x;
	f_start.z = playerAV[g_Player]->Xform.Translation.x;
	f_end.x = playerAV[g_Player]->Xform.Translation.x + (playerAV[g_Player]->Up.x * 250);
	f_end.y = playerAV[g_Player]->Xform.Translation.y + (playerAV[g_Player]->Up.y * 250);
	f_end.z = playerAV[g_Player]->Xform.Translation.z + (playerAV[g_Player]->Up.z * 250);

	Q.ShowLine(&f_start, &f_end, &player[g_Player]->ViewXForm.Translation, 5, Medias->BulletCount, 255, 255, 255, 255, 0);
#endif

#ifdef QAGEMODE_SURGERY
	//playerAV[g_Player]->Avatar.Mesh->m_qunModel->getMixer()->ClearAnim();
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

	playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->draw(true);

	glColorMask(true,true,true,true);
	glDepthMask(false);

#if 1	//HERE
	playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->draw(true);
#endif

	unbind_terrain_vertex();
	//*cgGLDisableProfile(CG_PROFILE_ARBFP1);
#endif

#if 0
	if(KEY_DOWN(QIN_UP)) playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->getNxCloth()->addForceAtPos(PxVec3(0,-250,0), PxVec3(1,0,0), 500);
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

				PxVec3 f_position = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
				printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
				}
			}
		else vecvarDpress[7] = false;

		if(KEY_DOWN(QIN_KP4))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.z -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP6))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.z += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP8))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.y -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP2))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.y += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP7))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.x += 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP1))
			{
			f_LocalBonePosition = QActiveFrameWork->DigiMass->acSkeletonGetBoneLocalPos(0, f_BoneIter);
			f_LocalBonePosition.x -= 0.01;
			QActiveFrameWork->DigiMass->acSkeletonSetBoneLocalPos(0, f_BoneIter, f_LocalBonePosition);
			printf("Bone %i Local Position x %f y %f z %f\n", f_BoneIter, f_LocalBonePosition.x, f_LocalBonePosition.y, f_LocalBonePosition.z);
			}

		if(KEY_DOWN(QIN_KP9))
			{
			if(!vecvarDpress[5])
				{
				vecvarDpress[5] = true;

				if(f_BoneIter < 14) f_BoneIter++;
				printf("f_BoneIter %i\n", f_BoneIter);
				}
			}
		else vecvarDpress[5] = false;

		if(KEY_DOWN(QIN_KP3))
			{
			if(!vecvarDpress[6])
				{
				vecvarDpress[6] = true;

				if(f_BoneIter > 0) f_BoneIter--;
				printf("f_BoneIter %i\n", f_BoneIter);
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(-0.2, 0, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0.2, 0, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0.2, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, -0.2, 0));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, 0.2));
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
				playerAV[g_Player]->Avatar.Mesh->m_ClothAttachment[0]->incPosition(PxVec3(0, 0, -0.2));
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

	//#### Test Instancing ### 
	if(KEY_DOWN(QIN_k))
		{
		if(!vecvarDpress[13])
			{
			vecvarDpress[13] = true;

			//### Test 01
			int f_CharacterSelect = 0;
			int f_CharacterTeam = 1;
			int f_CharacterBoneStructure = 0;
			QpoVec3d f_PosVector;
			helly = 0;
			while(helly < _->NomAI)
				{
				f_CharacterBoneStructure = Q_Forge->Forge[helly].AV.Avatar.Mesh->m_BoneStructure;

				f_PosVector.x = (((float)rand() / 32767)-0.5)*750;
				f_PosVector.y = -350;
				f_PosVector.z = (((float)rand() / 32767)-0.5)*750;

				if((rand() % 11) >= 5) f_CharacterSelect = 0;
				else f_CharacterSelect = 11;

				int f_BDATID = (int)rand() % 10;

#ifdef QAGE_OPMOD_B
				f_BDATID = 0;
#endif

				float f_finger = ((float)rand() / 32767);
				if(f_finger < 0.5) f_CharacterTeam = 0;
				else f_CharacterTeam = 1;

				//QActiveFrameWork->acSpawnAvatar(helly, rand() % 11, f_BDATID, f_CharacterTeam, f_PosVector, f_CharacterBoneStructure, 255, 255, 255, 255, 255, 255);

				helly++;
				}
			}
		}
	else vecvarDpress[13] = false;

	if(KEY_DOWN(QIN_MINUS))
		{
		if(!vecvarDpress[14])
			{
			vecvarDpress[14] = true;

			player[g_Player]->BFO.BDATID--;
			if(player[g_Player]->BFO.BDATID < 0) player[g_Player]->BFO.BDATID = 11;
			//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.BDATID);
			helly = 0;
			while(helly <= 2)
				{
				helly++;
				//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);
				}
			}
		}
	else vecvarDpress[14] = false;

	if(KEY_DOWN(QIN_PLUS))
		{
		if(!vecvarDpress[15])
			{
			vecvarDpress[15] = true;

			player[g_Player]->BFO.BDATID++;
			if(player[g_Player]->BFO.BDATID > 11) player[g_Player]->BFO.BDATID = 11;
			//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct_physics(playerAV[g_Player]->Avatar.Mesh, player[g_Player]->BFO.BDATID);
			helly = 0;
			while(helly <= 2)
				{
				helly++;
				//QActiveFrameWork->meshShellTemplates[player[g_Player]->BFO.BDATID]->clone_struct(player[g_Player]->Shadows[helly].Avatar.Mesh);
				}
			}
		}
	else vecvarDpress[15] = false;

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	//*glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	//glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	//glDisable(GL_BLEND);									// Enable Blending
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	//glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	//*g_render->set_camera();

	//QActiveFrameWork->DigiMass->acSimulate(_->TimeScale);
	//QActiveFrameWork->DigiMass->acRenderBoxes();

	if(rendswitchP)//NX_BF_ENERGY_SLEEP_TEST
		{
		//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		//glClearDepth(1.0f);									// Depth Buffer Setup
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		//*g_render->set_camera();

		//*QActiveFrameWork->DigiMass->acRenderScene(true);
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

	//glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	/**glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
	glEnable(GL_BLEND);									// Enable Blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	//glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	g_render->set_camera();*/

#if 1
	//QActiveFrameWork->DigiMass->acSimulate();
	//*QActiveFrameWork->DigiMass->acRender();
#endif

#if 0
	QActiveFrameWork->DigiMass->acRenderScene(true);
#endif

	//=== Render Position Locators ===//
	//*g_render->set_camera();

	//QpoVec3d f_pos = m_PointLocator->getPos();
	//if(f_pos.x != 0 && f_pos.y != 0 && f_pos.z != 0) m_PointLocator->acRender();

	//f_pos = QActiveFrameWork->trrcursor->getPos();
	//if(f_pos.x != 0 && f_pos.y != 0 && f_pos.z != 0) QActiveFrameWork->trrcursor->acRender();

	//*mrt_unbind_render();

	//*QActiveFrameWork->acGameEventsFrame();

#if 0
	if(KEY_DOWN(QIN_RBUTTON) && !KEY_DOWN(QIN_SHIFT) && !g_render->fullscreen)
		{
		if(!vecvarDpress[4])
			{
			vecvarDpress[4] = true;

			PxVec3 f_vecpoint;
			/*if(g_render->fullscreen) f_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x, temppos.y);
			else*/ f_vecpoint = QActiveFrameWork->DigiMass->acPick(temppos.x - 8, temppos.y - 48);

			m_PointLocator->setPos(f_vecpoint.x, f_vecpoint.y, f_vecpoint.z);
			QActiveFrameWork->trrcursor->setPos(f_vecpoint.x, f_vecpoint.y, f_vecpoint.z);
			if(gPickStay) QActiveFrameWork->DigiMass->PickSetPosition(f_vecpoint);
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

	//*//SDL_mutexV(m_mutex_Mesh);
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

	//pPBuffer *tmp;
	//tmp=m_fb[0];
	//m_fb[0]=m_fb[1];
	//m_fb[1]=tmp;
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

	//Frame Memory
//#ifdef UNRENDER_FRAMEMEMORY
#if 1
	if(g_render->framememory)
		{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_FrameMemory[m_Fcursor]);					// Bind To The Blur Texture
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, g_render->sizex, g_render->sizey, 0);
		m_Fcursor++;
		if(m_Fcursor >= UNREND_FRAMEMEMSIZE) m_Fcursor = 0;

		int f_cursor = m_Fcursor - UNREND_FRAMEMEMSIZE;
		if(f_cursor < 0) f_cursor = UNREND_FRAMEMEMSIZE + f_cursor;
		for(int mm = 0; mm < UNREND_FRAMEMEMSIZE; mm++)
			{
			glBindTexture(GL_TEXTURE_2D, m_FrameMemory[f_cursor]);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glEnable(GL_BLEND);

			//glColor4f(1.0f, 1.0f, 1.0f, 0.2f);

			if(g_render->fullscreen)
				{
				////*glBegin(GL_QUADS);
					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);

					//glTexCoord2f(0, 0);
					//glVertex2i(0, g_render->sizey);

					//glTexCoord2f(1, 0);
					//glVertex2i(g_render->sizex, g_render->sizey);

					//glTexCoord2f(1, 1);
					//glVertex2i(g_render->sizex, 0);

					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);
				////*glEnd();
				}
			else
				{
				////*glBegin(GL_QUADS);
					//glTexCoord2f(0,1);
					//glVertex2i(0,0);

					//glTexCoord2f(0, 0);
					//glVertex2i(0, g_render->sizey);

					//glTexCoord2f(1, 0);
					//glVertex2i(g_render->sizex, g_render->sizey);

					//glTexCoord2f(1, 1);
					//glVertex2i(g_render->sizex, 0);

					//glTexCoord2f(0, 1);
					//glVertex2i(0, 0);
				////*glEnd();
				}

			f_cursor++;
			if(f_cursor >= UNREND_FRAMEMEMSIZE) f_cursor = 0;
			}
		}
#endif
}

void unRenderer::checkError(const char *name, const char *situation)
{
	//*CGerror error;
	//*const char *string = cgGetLastErrorString(&error);
  
	//*if (error != CG_NO_ERROR)
	//*	{
	//*	if (error == CG_COMPILER_ERROR)
	//*		{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s\n\n"
			"Cg compiler output...\n%s",
			name, situation, string,
			cgGetLastListing(g_render->cgcontext));*/

			//*		std::string errorstr;
			//*errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG Compile ERROR", MB_OK);
			//*printf("CG:::Compile Error:::%s:::%s:::\n %s\n", name, situation, errorstr.c_str());
			//*for(;;) {};
			//*}
			//*else
			//*{
			/*fprintf(stderr,
			"Program: %s\n"
			"Situation: %s\n"
			"Error: %s",
			name, situation, string);*/

			//std::string errorstr("ERROR::: ");
			//errorstr += cgGetLastListing(g_render->cgcontext);

			//MessageBox (0, errorstr.c_str(), "CG ERROR", MB_OK);
			//*printf("CG:::General Execution Error");
			//*}
		//while(1) { /* Infinite Loop */ }
		//exit(1);
		//*}
}

void unRenderer::GLEnable2D(void)
{
   int vPort[4];

   glGetIntegerv(GL_VIEWPORT, vPort);

   //glMatrixMode(GL_PROJECTION);
   //glPushMatrix();
   //glLoadIdentity();

   //glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
   //glMatrixMode(GL_MODELVIEW);
   //glPushMatrix();
   //glLoadIdentity();
}

void unRenderer::GLDisable2D(void)
{
   //glMatrixMode(GL_PROJECTION);
   //glPopMatrix();
   //glMatrixMode(GL_MODELVIEW);
   //glPopMatrix();
}

void unRenderer::DrawPane(unsigned int f_texture, int f_x, int f_y, int f_scalex, int f_scaley)
{
	int m_x[4];
	int m_y[4];

	int strendX = f_x + f_scalex;
	int strendY = g_Height - (f_y + f_scaley);

	m_x[0] = strendX;
	m_y[0] = g_Height - f_y;
	m_x[1] = f_x;
	m_y[1] = g_Height - f_y;
	m_x[2] = f_x;
	m_y[2] = strendY;
	m_x[3] = strendX;
	m_y[3] = strendY;

	GLEnable2D();

	glEnable(GL_TEXTURE_2D);

	glBindTexture( GL_TEXTURE_2D, f_texture );

	////*glBegin( GL_QUADS );

	for(size_t id=0; id < 4; id++)
		{
		//glTexCoord2i(texxcoords[id*2], texxcoords[(id*2)+1]);
		//glVertex2d(m_x[id], m_y[id]);
		}

	////*glEnd();

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

				//*glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
					glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
					glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
					glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
					glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				//*glEnd();										// Done Building Triangle Strip

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

	return true;											// Everything Went OK
}

#endif

inline void unRenderer::testfunction(void)
	{

	}

GLuint unRenderer::CreateEmptyTexture(int f_x, int f_y)
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((f_x * f_y)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((f_x * f_y)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, f_x, f_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}
#endif