/************************************************************************
                         REPLACEMENT FOR GLAUX
 ************************************************************************
	This is not a full blown bitmap loader.  It is a quick and easy
	way to replace the glAux dependant code in my older tutorials
	with code that does not depend on the glAux library!

    This code only loads Truecolor Bitmap Images.  It will not load
	8-bit bitmaps.  If you encounter a bitmap that will not load
	use a program such as Irfanview to convert the bitmap to 24 bits.
 ************************************************************************/

#include "textureDef.h"

unGL::GLtexture LoadGLBitmap(LPTSTR szFileName)					// Creates Texture From A Bitmap File
{
	HBITMAP hBMP;														// Handle Of The Bitmap
	BITMAP	BMP;														// Bitmap Structure
	unGL::GLtexture texture;

	glGenTextures(1, &texture.m_TexID);											// Create The Texture
	hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBMP) printf("ERROR::: Texture Failed to load\n");							// Does The Bitmap Exist?

	GetObject(hBMP, sizeof(BMP), &BMP);									// Get The Object
																		// hBMP:        Handle To Graphics Object
																		// sizeof(BMP): Size Of Buffer For Object Information
																		// &BMP:        Buffer For Object Information

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);								// Pixel Storage Mode (Word Alignment / 4 Bytes)

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture.m_TexID);								// Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, BMP.bmBits);

	texture.m_width = BMP.bmWidth;
	texture.m_height = BMP.bmHeight;

	DeleteObject(hBMP);													// Delete The Object

	return texture;														// Loading Was Successful
}