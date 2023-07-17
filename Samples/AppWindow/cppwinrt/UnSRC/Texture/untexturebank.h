/*

    unTextureBank - Texture Management Library
    Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stss.co.nr

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __unTextureBank__
#define __unTextureBank__

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//

#include <vector>

//#include "../Geometry/unTrr.h"
#include "textureDef.h"
#include "../avatar/tgacal3d.h"
#include "SDL.h"

#define GL_BGR 0x80E0

//----------------------------------------------------------------------------//
// Defines                                                                    //
//----------------------------------------------------------------------------//

namespace icGL
{
	class GLtexture
	{
	public:
		GLtexture() {};
		virtual ~GLtexture() {};

	public:
		GLuint m_texture;
		float m_width;
		float m_height;
	};
};

//----------------------------------------------------------------------------//
// Class Declarations                                                         //
//----------------------------------------------------------------------------//

class unTextureBank
{
public:
	unTextureBank();
    virtual ~unTextureBank();

	void acLoadIntro(void);
	bool acInit(void);

#if 0
	icGL::GLtexture unTextureBank::icGLloadBMP( const char * filename );
	TextureAttributeItemHandle * nvloadTexture( const char * filename, int & width, int & height );
#endif

	GLuint GLloadTGA( const char * filename );
	GLuint GLloadTGA( const char * filename, int & width, int & height );
	GLuint GLloadTGA(std::string file);

#if 0
    static nvsg::TextureAttributeItemHandle *loadTexture (std::string path, const char *file);
#endif

	static unTextureBank* instance(void);

	void Spread(int Scale);
	void acNamePlateUpdate(void);

	void acPush(unsigned int i_texture, int i_width, int i_height);

	//trr::trrgrid materiallayer;

	//NxScene* acGetScene(void) const { return gScene; }

	std::vector<unGL::GLtexture> vecGLtextures;

private:
    // static instance variable
    static unTextureBank* s_instance;
};

#endif