/*

	unPhosectNucleusNT - No Threads
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#define GLH_EXT_SINGLE_FILE
/// Unification Engine includes
#include "unPhosectNucleusNT.h"
//#include "../Utility/nvparse.h"

#include <sys/stat.h>

#include "../Texture/tgaload.h"

/// Function Declarations
void draw_scene(void);

/// External Program Layer
GLuint VP_ShadowMapNT;

float LightNT[3] = { -10.0, 1.0, -10.0 };

unPhosectNucleusNT::unPhosectNucleusNT(void)
{
	m_NomPhosect = 0;
	m_Update = true;
}

bool unPhosectNucleusNT::Initialize(void)
{
	/*if(!glh_init_extensions("GL_ARB_multitexture "))
		{
		ShowCursor(true);
		MessageBox(NULL,"GL_ARB_multitexture extension was not found",
		"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
		}

	char *ext = (char*)glGetString( GL_EXTENSIONS );

	if( strstr( ext, "GL_ARB_vertex_program" ) == NULL )
		{
		ShowCursor(true);
		MessageBox(NULL,"GL_ARB_vertex_program extension was not found",
		"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
		}

	glGenProgramsARB             = (PFNGLGENPROGRAMSARBPROC )wglGetProcAddress("glGenProgramsARB");
	glDeleteProgramsARB          = (PFNGLDELETEPROGRAMSARBPROC )wglGetProcAddress("glDeleteProgramsARB");
	glBindProgramARB             = (PFNGLBINDPROGRAMARBPROC )wglGetProcAddress("glBindProgramARB");   
	glProgramStringARB           = (PFNGLPROGRAMSTRINGARBPROC  )wglGetProcAddress("glProgramStringARB"); 
	glProgramEnvParameter4fARB   = (PFNGLPROGRAMENVPARAMETER4FARBPROC )wglGetProcAddress("glProgramEnvParameter4fARB"); 
	glProgramLocalParameter4fARB = (PFNGLPROGRAMLOCALPARAMETER4FARBPROC )wglGetProcAddress("glProgramLocalParameter4fARB");
	glActiveTextureARB           = (PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB         = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glClientActiveTextureARB     = (PFNGLCLIENTACTIVETEXTUREARBPROC )wglGetProcAddress("glClientActiveTextureARB");*/

	const GLubyte *err = NULL;

	// Load the dual paraboloid projection shader.
	const char *vp_shadowmap = readRegCombinerFile( "shaders/ARBraw/VP_ShadowMap.txt" );
	  
	glEnable(GL_VERTEX_PROGRAM_ARB);
	glGenProgramsARB(1, &VP_ShadowMapNT);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, VP_ShadowMapNT);
	glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, strlen( vp_shadowmap),vp_shadowmap );
	  
	GLint errorPos;
	  
	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);

	//glBindProgramARB(GL_VERTEX_PROGRAM_ARB, 0);

	/*if ((errorPos != -1))
		{ 
		ShowCursor(true);
		MessageBox(NULL,"VP_SHADOWMAP contains Errors!", "ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
		}*/

	// Load the normal rendering shader.
	const char *vp_render = readRegCombinerFile( "shaders/ARBraw/VP_Render.txt" );

	glEnable(GL_VERTEX_PROGRAM_ARB);
	glGenProgramsARB(1, &VP_Render);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, VP_Render);
	glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, strlen( vp_render), vp_render );

	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);

	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, 0);

	glDisable(GL_VERTEX_PROGRAM_ARB);

	/*if (errorPos != -1)
		{
		ShowCursor(true);
		MessageBox(NULL,"VP_RENDER contains Errors!", "ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
		}*/

	//const char *rc_shadowmux = readRegCombinerFile( "shaders/ARBraw/rc_shadowmux.txt" );

	//RC_Mux = glGenLists(1);
	//glNewList( RC_Mux, GL_COMPILE );
	//nvparse( rc_shadowmux );
	//glEndList();

	//char * const * error = nvparse_get_errors();

	//if (error<=NULL)
	//	{
	//	ShowCursor(true);
	//	MessageBox(NULL,"NVparse reported errors!", "ERROR",MB_OK|MB_ICONEXCLAMATION);
	//	return false;
	//	}

	//MessageBox (0, "UpdateNucleus", "ERROR", MB_OK);

	//textureone = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );

	//DrawPane(textureone, 0, 0, 512, 512);
	//MessageBox (0, "Load Texture", "ERROR", MB_OK);
	//sysInt(textureone);

	return true;
}

unPhosectNucleusNT::~unPhosectNucleusNT(void)
{

}

unPhosectNucleusNT* unPhosectNucleusNT::s_instance = 0;
unPhosectNucleusNT* unPhosectNucleusNT::instance()
{
  return s_instance;
}

///// Run /////
void unPhosectNucleusNT::Run(void)
{
	//sysFloat(CameraVertex.pos[0]);
	//sysFloat(CameraVertex.pos[1]);
	//sysFloat(CameraVertex.pos[2]);

	/// Update Texture Cache
	if(UpdateCache()) UpdateNucleus();
	//m_Phosect[0]->m_Eye[0] = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );
	//DrawPane(textureone, 0, 0, 512, 512);
	//DrawPane(m_Phosect[0]->m_Eye[0], 0, 0, 512, 512);
	//sysInt(m_Phosect[0]->m_Eye[0]);
}

///// Update Phosect Texture Bank /////
/// Should always have some cached ///
bool unPhosectNucleusNT::UpdateCache(void)
{
	//// Insert Intelligent Caching
	if(m_NomPhosect == MED_PHOSECT) return false;	/// Replicate return checks

	if(m_NomPhosect < MED_PHOSECT)
		{
		for(int i = 0; i < MED_PHOSECT; ++i)
			{
			ServeNucleus(/*DRAT ENVIROMENT*/);
			}
		}
	else
		{
		for(int i = m_NomPhosect; i > MED_PHOSECT; --i)
			{
			DelocPhosect(i);
			}
		}

	return true;
}

bool unPhosectNucleusNT::UpdateNucleus(void)
{
	//if(!m_Update) return true;	/// return checks

	while(m_NewVertexserve.size() > 0)
		{
		m_Phosect[m_NewVertexserve.size() - 1]->Scan(m_NewVertexserve[m_NewVertexserve.size() - 1]);
		m_NewVertexserve.pop_back();
		}

	return true;
}

void unPhosectNucleusNT::ServeNucleus(void/*DRAT ENVIROMENT*/)
{
	//// Access VectorServer
	if(!m_PhoVectorserver.size())
		{
		m_Phosect.push_back(new unPhosect(/*DRAT*/));
		m_NomPhosect++;
		}
	else
		{
		m_Phosect[m_PhoVectorserver[m_PhoVectorserver.size() - 1]] = new unPhosect(/*DRAT*/);
		m_PhoVectorserver.pop_back();
		m_NomPhosect++;
		}
}

void/*NNmemREAL*/ unPhosectNucleusNT::DelocPhosect(Uint16 i_element)
{
	std::vector<unPhosect*>::iterator itElement = m_Phosect.begin() + i_element;

	delete *itElement;

	//// Increment Vector Server
	m_PhoVectorserver.push_back(i_element);

	//return DATA
}

char *unPhosectNucleusNT::readRegCombinerFile( const char *fileName )
{
    FILE *file = fopen( fileName, "r" );

    if( file == NULL )
    {
        MessageBox( NULL, "Cannot open registry combiner file!", "ERROR",
            MB_OK | MB_ICONEXCLAMATION );
		return 0;
    }

    struct _stat fileStats;

    if( _stat( fileName, &fileStats ) != 0 )
    {
        MessageBox( NULL, "Cannot get file stats for registry combiner file!", "ERROR",
                    MB_OK | MB_ICONEXCLAMATION );
        return 0;
    }

    char *buffer = new char[fileStats.st_size];

	int bytes = fread( buffer, 1, fileStats.st_size, file );

    buffer[bytes] = 0;

	fclose( file );

	return buffer;
}

void unPhosectNucleusNT::sysMessage(const char *i_Message)
{
	std::string messagestr("MSG::: ");
	messagestr += i_Message;

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus MSG", MB_OK);
}

void unPhosectNucleusNT::sysFloat(float i_Float)
{
	std::string messagestr("FLOAT::: ");
	messagestr += stringify(i_Float);

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus Float", MB_OK);
}

void unPhosectNucleusNT::sysInt(unsigned int i_Int)
{
	std::string messagestr("INT::: ");
	messagestr += stringint(i_Int);

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus Int", MB_OK);
}

void unPhosectNucleusNT::GLEnable2D(void)
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

void unPhosectNucleusNT::GLDisable2D(void)
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void unPhosectNucleusNT::DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley)
{
	int m_x[4];
	int m_y[4];
	int VID_WIDTH = 800;
	int VID_HEIGHT = 600;

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

	glBindTexture( GL_TEXTURE_2D, i_texture );

	glBegin( GL_QUADS );

	for(size_t id=0; id < 4; id++)
		{
		glTexCoord2i(texxcoordsnew[id*2], texxcoordsnew[(id*2)+1]);
		glVertex2d(m_x[id], m_y[id]);
		}

	glEnd();

	GLDisable2D();
}