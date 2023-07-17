/*

	textureDef - Texture Definitions NameSpace
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of The original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef TEXTUREDEF_H
#define TEXTUREDEF_H

#include <windows.h>				// Header File For Windows
#include <stdio.h>					// Header File For Standard Input/Output
#include <gl\gl.h>					// Header File For The OpenGL32 Library

namespace unGL
{
class GLtexture
{
	public:
		GLtexture() {};
		virtual ~GLtexture() {};

	public:
		GLubyte	* m_imageData;									// Image Data (Up To 32 Bits)
		GLuint	m_bpp;											// Image Color Depth In Bits Per Pixel
		GLuint	m_width;										// Image Width
		GLuint	m_height;										// Image Height
		GLuint	m_TexID;										// Texture ID Used To Select A Texture
		GLuint	m_type;											// Image Type (GL_RGB, GL_RGBA)
};

class GLvecf2
{
	public:
		GLvecf2() {};
		virtual ~GLvecf2() {};

		/// Functional Constructors Entry
		GLvecf2(float x, float y) { m_x = x; m_y = y; }

		void set(float x, float y) { m_x = x; m_y = y; }

	public:
		float m_x;
		float m_y;
};

class GLmaterial
{
	public:
		GLmaterial() { m_alpha = 1.0f; };
		virtual ~GLmaterial() {};

		/// Functional Constructors Entry
		inline GLmaterial(int textype, int texlist) { m_textype = textype; m_texlist = texlist; m_alpha = 0.5f; }

		//void set(float x, float y) { m_x = x; m_y = y; }

	public:
		float m_alpha;
		int m_textype;
		int m_texlist;
};

typedef struct GLtexmin
{
	GLuint  m_TexID;	// Image OpenGL Identification number
	GLuint	m_width;	// Image Width
	GLuint	m_height;	// Image Height
} GLtexmin;

////// Function Prototypes
unGL::GLtexture LoadGLBitmap(LPTSTR szFileName);
bool LoadTGA(unGL::GLtexture, char *);
bool LoadUncompressedTGA(unGL::GLtexture *, char *, FILE *);	// Load an Uncompressed file
bool LoadCompressedTGA(unGL::GLtexture *, char *, FILE *);		// Load a Compressed file

};

#endif