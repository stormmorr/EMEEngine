/*

    unTextureBank - Texture Management Library
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include "unTextureBank.h"
#include <string>

inline std::string icNoPath (std::string strFilename, std::string strDelimiters = "/\\")
{
	std::string::size_type uiPos = strFilename.find_last_of(strDelimiters);

	if(uiPos != std::string::npos)
		{
		return strFilename.substr(uiPos + 1);
		}
	else
		{
		return strFilename;
		}
}

//----------------------------------------------------------------------------//
// Instance                                                                   //
//----------------------------------------------------------------------------//

unTextureBank* unTextureBank::s_instance = 0;
unTextureBank* unTextureBank::instance()
{
    return s_instance;
}

//----------------------------------------------------------------------------//
// Constructor                                                                //
//----------------------------------------------------------------------------//

unTextureBank::unTextureBank()
{
    //assert(s_instance == 0);
    s_instance = this;
}

//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//

unTextureBank::~unTextureBank()
{
	for(int i = 0; i < vecGLtextures.size(); i++)
		{
		glDeleteTextures(1, &vecGLtextures[i].m_TexID);
		vecGLtextures[i].m_TexID = 0;
		}

	vecGLtextures.clear();

    s_instance = 0;
}

GLuint unTextureBank::GLloadTGA( const char * filename )
{
	GLuint pId=0;
	CTga *Tga;
	Tga = new CTga();

	//Note: This will always make a 32-bit texture
	if(Tga->ReadFile(filename)==0)
		{
		printf("ERROR - texture : %s : failed to load\n", filename);
		Tga->Release();
		return false;
		}

    //Bind texture
	int width = Tga->GetSizeX();
	int height = Tga->GetSizeY();
	int depth = Tga->Bpp() / 8;

	glEnable(GL_TEXTURE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &pId);
	
	glBindTexture(GL_TEXTURE_2D, pId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
	glTexImage2D(GL_TEXTURE_2D, 0, ((depth == 3) ? GL_RGB : GL_RGBA), width, height, 0, ((depth == 3) ? GL_RGB : GL_RGBA) , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

	Tga->Release();

	return pId;
}

GLuint unTextureBank::GLloadTGA( const char * filename, int & width, int & height )
{
	GLuint pId=0;
	CTga *Tga;
	Tga = new CTga();

	//Note: This will always make a 32-bit texture
	if(Tga->ReadFile(filename)==0)
		{
		printf("ERROR - texture : %s : failed to load\n", filename);
		Tga->Release();
		return false;
		}

    //Bind texture
	width = Tga->GetSizeX();
	height = Tga->GetSizeY();
	int depth = Tga->Bpp() / 8;

	glEnable(GL_TEXTURE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &pId);
      
	glBindTexture(GL_TEXTURE_2D, pId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
	glTexImage2D(GL_TEXTURE_2D, 0, ((depth == 3) ? GL_RGB : GL_RGBA), width, height, 0, ((depth == 3) ? GL_RGB : GL_RGBA) , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

	Tga->Release();

	return pId;
}

GLuint unTextureBank::GLloadTGA( std::string file )
{
	GLuint pId=0;
	CTga *Tga;
	Tga = new CTga();

	//Note: This will always make a 32-bit texture
	if(Tga->ReadFile(file)==0)
		{
		//*unConsoleAttribute(CONSOLE_ERROR);
		printf("ERROR - texture : failed to load\n");
		//*unConsoleAttribute(CONSOLE_INIT);
		Tga->Release();
		return false;
		}

    //Bind texture
	int width = Tga->GetSizeX();
	int height = Tga->GetSizeY();
	int depth = Tga->Bpp() / 8;

	glEnable(GL_TEXTURE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &pId);
	
	glBindTexture(GL_TEXTURE_2D, pId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     
	glTexImage2D(GL_TEXTURE_2D, 0, ((depth == 3) ? GL_RGB : GL_RGBA), width, height, 0, ((depth == 3) ? GL_RGB : GL_RGBA) , GL_UNSIGNED_BYTE, (char*)Tga->GetPointer() );

	Tga->Release();

	return pId;
}

void unTextureBank::acLoadIntro(void)
{
	using namespace unGL;

	//*unConsoleAttribute(CONSOLE_ERROR);

	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\bannersplash.bmp"));

	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME1.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME2.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME3.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME4.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME5.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME6.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME7.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME8.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME9.bmp"));
	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\NAME10.bmp"));

	vecGLtextures.push_back(LoadGLBitmap((LPTSTR)"Art\\Logos\\NAMEPLATE\\EFFECTSTEST.bmp"));

	//*unConsoleAttribute(CONSOLE_INIT);
}

bool unTextureBank::acInit(void)
{
	/// Init Variables
	int width, height;

	using namespace unGL;

	acNamePlateUpdate();

#if 0
	std::string m_path = "data/textures/construction/";
	std::string strFilename = "panel_test2.png";
	std::string strFullPath = m_path + strFilename;
#endif

#if 0
	/// Load Texture Library
	std::string m_path = "data/textures/construction/";
	std::string strFilename = "panel_test2.png";
	std::string strFullPath = m_path + strFilename;

	//*unConsoleAttribute(CONSOLE_INIT);

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// PopupCow
	m_path = "data/textures/GUI/";
	strFilename = "PopupCow.tga";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// Terrain 1
	m_path = "../mk/textures/";
	strFilename = "stone_texture.jpg";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// TrrTool1
	m_path = "data/textures/GUI/";
	strFilename = "TrrTool3.tga";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// TrrSand
	m_path = "data/textures/terrain/";
	strFilename = "trrSand.png";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// TrrStone
	m_path = "data/textures/terrain/";
	strFilename = "trrStone.png";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// TrrGrass
	m_path = "data/textures/terrain/";
	strFilename = "trrGrass.png";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	/// TrrTool1
	m_path = "data/textures/GUI/";
	strFilename = "TrrTool4.tga";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

  ///////////////////////////////////////////////////////////
	/// Grass
	m_path = "data/textures/terrain/";
	strFilename = "GroundVeg_47_seamless_1024.png";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

  ///////////////////////////////////////////////////////////
	/// Sand
	m_path = "data/textures/terrain/";
	strFilename = "Sand_3_Seamless_1024.png";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

  ///////////////////////////////////////////////////////////
	/// Rock
	m_path = "data/textures/terrain/";
	strFilename = "242-diffuse.jpg";
	strFullPath = m_path + strFilename;

	vecNVtextures.push_back(nvloadTexture( strFullPath.c_str(), width, height ));
	printf("||-NVSG Texture Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	vecGLtextures.push_back(LoadGLBitmap("data/textures/GUI/Gizmo2.bmp"));
	//vecGLtextures.push_back(LoadGLBitmap("data/textures/GUI/TTOplate.bmp"));

	acNamePlateUpdate();
#endif

#if 1
	///////				////////
	///////	GL TEXTURES ////////
	///////				////////

#if 0
	unGL::GLtexture texture;
	SDL_Surface *surface;	// This surface will tell us the details of the image

	if ( (surface = SDL_LoadBMP(strFullPath.c_str())) )
		{
		// Check that the image's width is a power of 2
		//if ( (surface->w & (surface->w - 1)) != 0 )
		//	printf("warning: image.bmp's width is not a power of 2\n");
		
		// Also check if the height is a power of 2
		//if ( (surface->h & (surface->h - 1)) != 0 )
		//	printf("warning: image.bmp's height is not a power of 2\n");
	        
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture.m_TexID );
	 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture.m_TexID );
		
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );
		}
	else
		{
		//*unConsoleAttribute(CONSOLE_ERROR);
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		//*unConsoleAttribute(CONSOLE_INIT);
		return false;
		}
#endif

#if 0
	//[13]
	m_path = "data/textures/GUI/";
	strFilename = "Gizmo2.bmp";
	strFullPath = m_path + strFilename;

	unGL::GLtexture texture = LoadGLBitmap((LPTSTR)strFullPath.c_str());
	texture.m_width = 424.0f;
	texture.m_height = 432.0f;
	vecGLtextures.push_back(texture);
	printf("||-GL Texture Loaded %s\n", strFullPath.c_str());
#endif

#if 0
	// Free the SDL_Surface only if it was successfully created
	if ( surface ) SDL_FreeSurface( surface );
#endif

	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////

#if 0
	m_path = "data/textures/GUI/";
	strFilename = "TTOplate.bmp";
	strFullPath = m_path + strFilename;

	if ( (surface = SDL_LoadBMP(strFullPath.c_str())) )
		{ 
	 
		// Check that the image's width is a power of 2
		//if ( (surface->w & (surface->w - 1)) != 0 )
		//	printf("warning: image.bmp's width is not a power of 2\n");
		
		// Also check if the height is a power of 2
		//if ( (surface->h & (surface->h - 1)) != 0 )
		//	printf("warning: image.bmp's height is not a power of 2\n");
	        
		// Have OpenGL generate a texture object handle for us
		GLGenTextures( 1, &texture.m_TexID );
	 
		// Bind the texture object
		GLBindTexture( GL_TEXTURE_2D, texture.m_TexID );
	 
		// Set the texture's stretching properties
		GLTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		GLTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	 
		// Edit the texture object's image data using the information SDL_Surface gives us
		GLTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );
		}
	else
		{
		//*unConsoleAttribute(CONSOLE_ERROR);
		printf("SDL could not load image.bmp: %s\n", SDL_GetError());
		//*unConsoleAttribute(CONSOLE_INIT);
		return false;
		}

	texture.m_width = 424.0f;
	texture.m_height = 432.0f;
	vecGLtextures.push_back(texture);
	printf("||-GL Texture Loaded %s\n", strFullPath.c_str());

	// Free the SDL_Surface only if it was successfully created
	if ( surface ) SDL_FreeSurface( surface );
#endif

#endif

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/// Load GUI MENU TGAs		[14]

#if 0
	m_path = "data/textures/GUI/";
	strFilename = "GizmoFrame6.tga";
	//strFilename = "PopupCow.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 424.0f;
	texture.m_height = 432.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/// Load GUI MENU TGAs		[15]
	m_path = "data/textures/GUI/";
	strFilename = "PopupCow.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 350.0f;
	texture.m_height = 308.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/// Load GUI MENU TGAs		[16]
	m_path = "data/textures/GUI/";
	strFilename = "Ayane.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 266.0f;
	texture.m_height = 525.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/// Load GUI MENU TGAs		[17]
	m_path = "data/textures/GUI/";
	strFilename = "GUIEDIT01.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 128.0f;
	texture.m_height = 128.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////
	/// Load GUI SYMBOLS		[18]
	m_path = "data/textures/GUI/";
	strFilename = "GUIS01.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	m_path = "data/textures/GUI/";
	strFilename = "GUIS02.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	m_path = "data/textures/GUI/";
	strFilename = "GUIS03.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	m_path = "data/textures/GUI/";
	strFilename = "GUIS04.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	m_path = "data/textures/GUI/";
	strFilename = "GUIS05.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	m_path = "data/textures/GUI/";
	strFilename = "GUIS06.tga";
	strFullPath = m_path + strFilename;
	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	////// Texture Array [24]
	m_path = "data/textures/GUI/";
	strFilename = "GUIS07.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	////// Texture Array [25]
	m_path = "data/textures/GUI/";
	strFilename = "GUIS08.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 36.0f;
	texture.m_height = 36.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	////// Texture Array [26]
	m_path = "data/textures/GUI/";
	strFilename = "GUIS09.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 17.0f;
	texture.m_height = 17.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded %s\n", strFullPath.c_str());

	acNamePlateUpdate();

	////// Texture Array [27]
	m_path = "data/textures/GUI/";
	strFilename = "Login.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 93.0f;
	texture.m_height = 75.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded 27 %s\n", strFullPath.c_str());

	////// Texture Array [28]
	m_path = "data/textures/GUI/";
	strFilename = "PTemplate.tga";
	strFullPath = m_path + strFilename;

	texture.m_width = 640.0f;
	texture.m_height = 480.0f;
	texture.m_TexID = GLloadTGA(strFullPath.c_str());
	vecGLtextures.push_back(texture);
	printf("||-GL TGA Loaded 28 %s\n", strFullPath.c_str());
#endif

	acNamePlateUpdate();

	return true;
}

void unTextureBank::acNamePlateUpdate(void)
{
	
}

void unTextureBank::acPush(unsigned int i_texture, int i_width, int i_height)
{
	unGL::GLtexture texture;

	texture.m_width = i_width;
	texture.m_height = i_height;

	vecGLtextures.push_back(texture);

#if 0
	printf("||-acPush Gui Text Texture\n");
#endif
}