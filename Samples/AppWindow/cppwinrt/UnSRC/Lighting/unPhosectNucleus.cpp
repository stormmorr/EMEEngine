/*

	unPhosectNucleus
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

/// Thread type switch
#define CTHREAD 0

#define GLH_EXT_SINGLE_FILE
/// Unification Engine includes
#include "unPhosectNucleus.h"
//#include "../Utility/nvparse.h"

#include <sys/stat.h>

#include "../Texture/tgaload.h"
#include "../Texture/texture.h"

/// Function Declarations
void draw_scene(void);

/// External Program Layer
GLuint VP_ShadowMap;

GLuint texturenew;

HDC			m_hdc=NULL;		// Private GDI Device Context
HGLRC		m_hRC=NULL;
GLuint		PixelFormat;

float Light[3] = { -10.0, 1.0, -10.0 };

const int SHADOW_MAP_RES = 1024;

const unsigned int texxcoordsnew[] =
{
1, 0,
0, 0,
0, 1,
1, 1
};

const unsigned int texxreversednew[] =
{
1, 1,
0, 1,
0, 0,
1, 0
};

UINT unPhosectNucleus::Start(LPVOID lpParam)
{
	Initialize();
	return 0;
}

unPhosectNucleus::unPhosectNucleus(void* pOwnerObject, icThreadData *pData) : CThread(pOwnerObject, pData)
{
	/// Initialize Threading
#if CTHREAD
	SUPPORT_THREAD_SYNCHRONIZATION(unPhosectNucleus)
	SUPPORT_THREAD_NOTIFICATION
#endif

	m_NomPhosect = 0;
	m_Update = true;

	/// To call from main instance
	/// Initialise threads
	//unPhosectNucleus.Start();
}

bool unPhosectNucleus::acSplitContext(void)
{
#if 0
	int			pf;	/* Pixel format ID */
	PIXELFORMATDESCRIPTOR pfd;	/* Pixel format information */
	PAINTSTRUCT		ps;	/* WM_PAINT message info */
	RECT			rect;	/* Current client area rectangle */

	pfd.nSize        = sizeof(pfd);
	pfd.nVersion     = 1;
	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.dwLayerMask  = PFD_MAIN_PLANE;	/* Main drawing plane */
	pfd.iPixelType   = PFD_TYPE_RGBA;	/* RGB color buffer */
	pfd.cColorBits   = 0;			/* Best color buffer please */
	pfd.cDepthBits   = 32;			/* Need a depth buffer */
	pfd.cStencilBits = 0;			/* No stencil buffer */
	pfd.cAccumBits   = 0;			/* No accumulation buffer */

	pf = ChoosePixelFormat(m_hdc, &pfd);
	if (pf == 0)
		MessageBox(NULL,"texscene was unable to choose a suitable pixel format!","ERROR",MB_OK|MB_ICONEXCLAMATION);
	else if (!SetPixelFormat(m_hdc, pf, &pfd))
		MessageBox(NULL,"texscene was unable to set the pixel format!","ERROR",MB_OK|MB_ICONEXCLAMATION);
#endif

#if 1
	m_hdc = g_render->hdc;

	//m_hRC = wglCreateContext(m_hdc);
	//wglMakeCurrent(m_hdc, m_hRC);
	//wglShareLists(m_hRC, g_render->hrc);
#endif

#if 0
	texturenew = TextureLoadBitmap("data//Particle2.bmp");
	textureone = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );

	DrawPane(texturenew, 0, 0, 512, 512);

	SwapBuffers(m_hdc);
#endif

	sysInt(texturenew);

	return true;
}

bool unPhosectNucleus::Initialize(void)
{
	acSplitContext();
	//wglMakeCurrent(m_hdc, m_hRC);

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
	glGenProgramsARB(1, &VP_ShadowMap);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, VP_ShadowMap);
	glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, strlen( vp_shadowmap),vp_shadowmap );
	  
	GLint errorPos;
	  
	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);

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

	/*if (errorPos != -1)
		{
		ShowCursor(true);
		MessageBox(NULL,"VP_RENDER contains Errors!", "ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
		}*/

	const char *rc_shadowmux = readRegCombinerFile( "shaders/ARBraw/rc_shadowmux.txt" );

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

	//textureone = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );

	Run();

	return true;
}

unPhosectNucleus::~unPhosectNucleus(void)
{

}

unPhosectNucleus* unPhosectNucleus::s_instance = 0;
unPhosectNucleus* unPhosectNucleus::instance()
{
  return s_instance;
}

///////////////////////////////////////////////////////////////////////////////
// WORKER THREAD CLASS GENERATOR - Do not remove/edit this method!
// MAIN THREAD HANDLER - The only method that must be implemented.
///////////////////////////////////////////////////////////////////////////////
int unPhosectNucleus::ThreadHandler()
{
	bool bCanContinue = true;
	int nIncomingCommand;

		do
		{
		WaitForNotification(nIncomingCommand);

		switch (nIncomingCommand)
			{
			case CThread::CMD_INITIALIZE:
				Initialize();
				HandleCommandImmediately(CThread::CMD_RUN);
				break;

			case CThread::CMD_RUN:
				Lock();
				Run();
				Unlock();
				break;

			case CThread::CMD_PAUSE:
				SetActivityStatus(CThread::THREAD_PAUSED);
				break;

			case CThread::CMD_STOP:
				bCanContinue = false;
				break;

			default:
				break;
			};

		} while (bCanContinue);

	return 0;	// ... if Thread task completition OK
}

///// Run /////
void unPhosectNucleus::Run(void)
{
	//sysFloat(CameraVertex.pos[0]);
	//sysFloat(CameraVertex.pos[1]);
	//sysFloat(CameraVertex.pos[2]);

	for(;;)
		{
		/// Update Texture Cache

		//if(UpdateCache()) UpdateNucleus();

		//m_Phosect[0]->m_Eye[0] = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );
		//DrawPane(textureone, 0, 0, 512, 512);
		//DrawPane(m_Phosect[0]->m_Eye[0], 0, 0, 512, 512);
		//sysInt(m_Phosect[0]->m_Eye[0]);

		//sysInt(115);


		//sysInt(textureone);
		wglMakeCurrent(m_hdc, m_hRC);

		textureone = tgaLoadAndBind ( "data//rockbumpstep.tga",  TGA_DEFAULT );

		DrawPane(textureone, 0, 0, 512, 512);
		SwapBuffers(m_hdc);
		}
}

///// Update Phosect Texture Bank /////
/// Should always have some cached ///
bool unPhosectNucleus::UpdateCache(void)
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

bool unPhosectNucleus::UpdateNucleus(void)
{
	//if(!m_Update) return true;	/// return checks

	while(m_NewVertexserve.size() > 0)
		{
		m_Phosect[m_NewVertexserve.size() - 1]->Scan(m_NewVertexserve[m_NewVertexserve.size() - 1]);
		m_NewVertexserve.pop_back();
		}

	return true;
}

void unPhosectNucleus::ServeNucleus(void/*DRAT ENVIROMENT*/)
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

void/*NNmemREAL*/ unPhosectNucleus::DelocPhosect(Uint16 i_element)
{
	std::vector<unPhosect*>::iterator itElement = m_Phosect.begin() + i_element;

	delete *itElement;

	//// Increment Vector Server
	m_PhoVectorserver.push_back(i_element);

	//return DATA
}

unPhosect::unPhosect(void)
{
	//m_hglrc = wglGetCurrentContext();
    //m_hdc = wglGetCurrentDC();
	//WGLAttachContext(m_hdc, m_hglrc);
	//wglMakeCurrent( m_hdc, g_render->hrc );

	//wglMakeCurrent(m_hdc, m_hRC);
	//wglShareLists(m_hRC, g_render->hrc);

	wglMakeCurrent(m_hdc, m_hRC);
	wglShareLists(m_hRC, g_render->hrc);

	unsigned int textureone;

	unPhosectNucleus::sysInt(textureone);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &textureone);

	unPhosectNucleus::sysInt(textureone);

	///// Initialize Parameters
	m_Active = false;
	m_Eye[0] = 0;
	m_Eye[1] = 0;

	unPhosectNucleus::sysInt(m_Eye[0]);

	glGenTextures(1, &m_Eye[0]);

	unPhosectNucleus::sysInt(m_Eye[0]);

	//// Create First Hemisphere
	glBindTexture(GL_TEXTURE_2D, m_Eye[0]);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//// Create Second Hemisphere
	glBindTexture(GL_TEXTURE_2D, m_Eye[1]);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//unPhosectNucleus::sysInt(m_Eye[1]);

	//MessageBox (0, "New Phosect", "ERROR", MB_OK);
}

unPhosect::~unPhosect(void)
{
	//// DeAllocate and Clear Phosect Arrays
}

bool unPhosect::Scan(pVertex i_Vertex)
{
	wglMakeCurrent(m_hdc, m_hRC);

	//unPhosectNucleus::sysMessage("unPhosect::Scan");
	i_Vertex.pos[0] = 5;
	unPhosectNucleus::sysFloat(i_Vertex.pos[0]);
	unPhosectNucleus::sysFloat(i_Vertex.pos[1]);
	unPhosectNucleus::sysFloat(i_Vertex.pos[2]);

	glEnable(GL_VERTEX_PROGRAM_ARB);
	//  Render the scene using the dual-paraboloid projection, and save the depth
	//  buffer. Do this for both hemispheres. }
	//  glDisable(GL_LIGHTING);
	//  The alpha test culls away fragments that belong in the other hemisphere.
	glEnable(GL_ALPHA_TEST);

	glViewport(0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);
	glBindProgramARB(GL_VERTEX_PROGRAM_ARB, VP_ShadowMap);
	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 1, Light[0], Light[1], Light[2], 0);

	// First hemisphere:
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glAlphaFunc(GL_GEQUAL, 0.5);

	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 2, 0, 0, -1, 1);  // d0
	glTranslatef(-i_Vertex.pos[0], -i_Vertex.pos[1], -i_Vertex.pos[2]);

	////// ACCESS SCENE OBJECTS //////
	//draw_scene();

	glBindTexture(GL_TEXTURE_2D, m_Eye[0]);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);

	// Second hemisphere:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glAlphaFunc(GL_LEQUAL, 0.5);

	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB, 2, 0, 0, 1, 1);
	glTranslatef(-i_Vertex.pos[0], -i_Vertex.pos[1], -i_Vertex.pos[2]);

	////// ACCESS SCENE OBJECTS //////
	//draw_scene();

	glBindTexture(GL_TEXTURE_2D, m_Eye[1]);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, SHADOW_MAP_RES, SHADOW_MAP_RES);

	// Restore viewport:
	glViewport(0, 0, 800,600);

	glDisable(GL_ALPHA_TEST);

	/// Set Phosect Parameters
	m_Vertex = i_Vertex;
	return m_Active = true;
}

char *unPhosectNucleus::readRegCombinerFile( const char *fileName )
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

void unPhosectNucleus::sysMessage(const char *i_Message)
{
	std::string messagestr("MSG::: ");
	messagestr += i_Message;

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus MSG", MB_OK);
}

void unPhosectNucleus::sysFloat(float i_Float)
{
	std::string messagestr("FLOAT::: ");
	messagestr += stringify(i_Float);

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus Float", MB_OK);
}

void unPhosectNucleus::sysInt(unsigned int i_Int)
{
	std::string messagestr("INT::: ");
	messagestr += stringint(i_Int);

	MessageBox (0, messagestr.c_str(), "Pho-Nucleus Int", MB_OK);
}

void unPhosectNucleus::GLEnable2D(void)
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

void unPhosectNucleus::GLDisable2D(void)
{
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void unPhosectNucleus::DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley)
{
	//wglMakeCurrent(m_hdc, m_hRC);

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

/*static UINT ThreadFunc(LPVOID lpParam)
{
	int threadId = (lpParam ? 1 : 0);
	static int nProc = GetNProc();

	if (nProc > 1)
		wglMakeCurrent(PencilDC, PencilRC[threadId]);
	
	// Setup Lighting and initial configuration of a circle
	{
		glViewport(0,0,rec_width, rec_height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float)rec_width / (float)rec_height,
			0.1, 10000.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_Media->DECAL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, -50.0f, -500.0f);
		if (threadId == 0)
			glRotatef(75.0f, 1.0, 0.0, 0.0);
		else
		{
			glTranslatef(0.0f, 0.0f, -100.0f);
			glRotatef(40.0f, 1.0, 0.0, 0.0);
			glRotatef(80.0f, 0.0, 1.0, 0.0);
		}
		glRotatef(g_zAngle,0.0f, 0.0f, 1.0f);
	}

	for (int i=0;i<NUM_PENCILS;i++)
	{
		glPushMatrix();
		// Render each pencil
		{
			glRotatef(360.0f * i / NUM_PENCILS, 0.0f, 0.0f, 1.0f);
			glTranslatef(300.0f, 0.0f, 0.0f);

			glRotatef(PencilHeading[i], 0.0, -1.0, 0.0);
			glRotatef(PencilPitch[i], 1.0, 0.0, 0.0);
			glRotatef(PencilRoll[i], 0.0, 0.0, -1.0);

			gluQuadricNormals(PencilObj, GLU_FLAT);
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, PencilTexture[threadId] );

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -20.0);
				gluCylinder(PencilObj, 5.0, 5.0, 40.0, 6, 2);
			}
			glPopMatrix();

			gluQuadricNormals(PencilObj, GLU_SMOOTH);
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, LeadTexture[threadId] );

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 20.0);
				gluCylinder(PencilObj, 5.0, 0.0, 7.5, 6, 2);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -20.0);

				gluCylinder(PencilObj, 5.0, 0.0, 0.0, 6, 2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glFinish();

	return 0;
}*/