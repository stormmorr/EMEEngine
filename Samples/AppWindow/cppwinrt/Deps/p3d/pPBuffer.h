/*! \file */
#if 0 // QAGE_DESKTOP
#ifndef PPBUFFER_H
#define PPBUFFER_H

class P3D_API pPBuffer
{
   private:
      HPBUFFERARB m_buffer;
      HGLRC m_RC;
      HDC m_DC;
      HGLRC m_prevRC;
      HDC m_prevDC;

   public:
	   int m_width,m_height;

	  //create a Pbuffer with the correct attributes
      pPBuffer(int width, int height, int bpp, 
		  bool isFloat, bool hasDepth, bool hasStencil, 
		  bool texture, bool depthtexture, 
		  bool recttexture, bool mipmap, bool share, int numauxbuf);
      ~pPBuffer();

      //is this buffer usable
      bool IsValid();
      
      //make it available for rendering
      void Bind();
      void Unbind();

      //make it available as a texture if applicable 
      void BindAsTexture(int buffer);
      void ReleaseTexture(int buffer);

      //swap if applicable
      void Swap();
};

#endif
#endif