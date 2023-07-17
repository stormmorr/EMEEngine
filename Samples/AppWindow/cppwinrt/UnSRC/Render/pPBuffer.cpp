#include "pch.h"
#include "paralelo3d.h"
#ifndef P_DISABLE_3D

#define MAX_ATTRIBS 64
#define MAX_FORMATS 64

pPBuffer::pPBuffer( int width, int height, int bpp, bool isFloat, bool hasDepth, bool hasStencil, bool texture, bool depthtexture, bool recttexture, bool mipmap, bool share, int numauxbuf) :
   m_buffer(0), m_RC(0), m_DC(0), m_prevRC(0), m_prevDC(0)
{
	int iAttribs[MAX_ATTRIBS];
	float fAttribs[MAX_ATTRIBS];
	int niAttribs = 0;
	int pformats[MAX_FORMATS];
	unsigned int nformat;

	// necessary for option depthtexture
	bool support_NV_render_depth_texture=false;
	const char *wglext="";
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if (wglGetExtensionsStringARB)
		wglext=wglGetExtensionsStringARB(wglGetCurrentDC());
	if(strstr(wglext,"WGL_NV_render_depth_texture"))
		support_NV_render_depth_texture=true;

	m_width = width;
	m_height = width;

	HGLRC rc = wglGetCurrentContext();
	HDC hdc = wglGetCurrentDC();

	memset( iAttribs, 0, sizeof(int)*MAX_ATTRIBS);
	memset( fAttribs, 0, sizeof(float)*MAX_ATTRIBS);

	iAttribs[ niAttribs++] = WGL_PIXEL_TYPE_ARB;
	iAttribs[ niAttribs++] = isFloat ? WGL_TYPE_RGBA_FLOAT_ATI : WGL_TYPE_RGBA_ARB;

	iAttribs[ niAttribs++] = WGL_SUPPORT_OPENGL_ARB;
	iAttribs[ niAttribs++] = GL_TRUE;

	iAttribs[ niAttribs++] = WGL_DRAW_TO_PBUFFER_ARB;
	iAttribs[ niAttribs++] = GL_TRUE;

	iAttribs[ niAttribs++] = WGL_DOUBLE_BUFFER_ARB;
	iAttribs[ niAttribs++] = GL_FALSE;

	if (bpp)
	{
		iAttribs[ niAttribs++] = WGL_RED_BITS_ARB;
		iAttribs[ niAttribs++] = bpp/4;

		iAttribs[ niAttribs++] = WGL_GREEN_BITS_ARB;
		iAttribs[ niAttribs++] = bpp/4;

		iAttribs[ niAttribs++] = WGL_BLUE_BITS_ARB;
		iAttribs[ niAttribs++] = bpp/4;

		iAttribs[ niAttribs++] = WGL_ALPHA_BITS_ARB;
		iAttribs[ niAttribs++] = bpp/4;

		iAttribs[ niAttribs++] = WGL_COLOR_BITS_ARB;
		iAttribs[ niAttribs++] = bpp;
	}

	if (hasDepth)
	{
		iAttribs[ niAttribs++] = WGL_DEPTH_BITS_ARB;
		iAttribs[ niAttribs++] = 24;
	}

	if (hasStencil)
	{
		iAttribs[ niAttribs++] = WGL_STENCIL_BITS_ARB;
		iAttribs[ niAttribs++] = 8;
	}

	if (support_NV_render_depth_texture && depthtexture)
	{
		iAttribs[ niAttribs++] = WGL_BIND_TO_TEXTURE_DEPTH_NV;
		iAttribs[ niAttribs++] = GL_TRUE;
	}

	if (texture)
	{
		iAttribs[ niAttribs++] = WGL_BIND_TO_TEXTURE_RGBA_ARB;
		iAttribs[ niAttribs++] = GL_TRUE;
	}

	if (numauxbuf)
	{
		iAttribs[ niAttribs++] = WGL_AUX_BUFFERS_ARB;
		iAttribs[ niAttribs++] = numauxbuf;
	}

	iAttribs[niAttribs] = 0;

   if (wglChoosePixelFormatARB( hdc, iAttribs, fAttribs, MAX_FORMATS, pformats, &nformat))
   {
      niAttribs = 0;
	  if (support_NV_render_depth_texture && depthtexture)
	  {
		  iAttribs[niAttribs++] = WGL_DEPTH_TEXTURE_FORMAT_NV;
		  iAttribs[niAttribs++] = WGL_TEXTURE_DEPTH_COMPONENT_NV;
	  }

      if (texture)
      {
		  iAttribs[niAttribs++] = WGL_TEXTURE_FORMAT_ARB;
		  iAttribs[niAttribs++] = WGL_TEXTURE_RGBA_ARB;
 
		  if (recttexture)
		  {
			iAttribs[ niAttribs++] = WGL_TEXTURE_TARGET_ARB;
			iAttribs[ niAttribs++] = WGL_TEXTURE_RECTANGLE_NV;
		  }
		  else
		  {
			iAttribs[niAttribs++] = WGL_TEXTURE_TARGET_ARB;
			iAttribs[niAttribs++] = WGL_TEXTURE_2D_ARB;
		  }

		  if (mipmap)
		  {
			 iAttribs[ niAttribs++] = WGL_MIPMAP_TEXTURE_ARB;
			 iAttribs[ niAttribs++] = GL_TRUE;
		  }
      }

      iAttribs[niAttribs] = 0;
      m_buffer = wglCreatePbufferARB( hdc, pformats[0], width, height, iAttribs);

      if (m_buffer)
      {
         m_DC = wglGetPbufferDCARB( m_buffer);

         if (m_DC)
         {
            m_RC = wglCreateContext( m_DC);

            if (m_RC)
            {
               if (share)
               {
                  wglShareLists( rc, m_RC);
               }
            }
            else
            {
               wglReleasePbufferDCARB( m_buffer, m_DC);
               m_DC = NULL;
               wglDestroyPbufferARB( m_buffer);
               m_buffer = NULL;
            }
         }
         else
         {
            wglDestroyPbufferARB( m_buffer);
            m_buffer = NULL;
         }
      }
   }
}

pPBuffer::~pPBuffer()
{
   if (m_RC)
   {
		wglDeleteContext( m_RC);
		m_RC = NULL;
   }

   if (m_DC)
   {
		wglReleasePbufferDCARB( m_buffer,m_DC );
		m_DC = NULL;
   }

   if (m_buffer)
   {
		wglDestroyPbufferARB( m_buffer);
		m_buffer = NULL;
   }
}

bool pPBuffer::IsValid()
{
   return (m_RC !=0);
}

void pPBuffer::Bind()
{
   m_prevDC = wglGetCurrentDC();
   m_prevRC = wglGetCurrentContext();

   wglMakeCurrent( m_DC, m_RC);
}

void pPBuffer::Unbind()
{
   wglMakeCurrent( m_prevDC, m_prevRC);
}

void pPBuffer::BindAsTexture( int buffer)
{
   wglBindTexImageARB( m_buffer, buffer);
}

void pPBuffer::ReleaseTexture( int buffer)
{
   wglReleaseTexImageARB( m_buffer, buffer);
}

void pPBuffer::Swap()
{
   wglSwapLayerBuffers( m_DC, WGL_SWAP_MAIN_PLANE);
}

#endif

