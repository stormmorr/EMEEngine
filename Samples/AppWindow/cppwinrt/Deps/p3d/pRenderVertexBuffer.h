/*! \file */

#ifndef PRENDERVERTEXBUFFER_H
#define PRENDERVERTEXBUFFER_H

//! Render Vertex Array class
/*!
	This class implements support for rendering to a vertex array.
	You can use the vertex array as a float texture map or as a vertex buffer. 
*/
#ifndef P_DISABLE_3D

class P3D_API pRenderVertexBuffer 
{
protected:
	int m_usage;     // vbo usage flag
	unsigned int m_buffer;
	unsigned int m_index;
	unsigned int m_nverts;
	int m_size;       // size of attribute       
	int m_format;    // readpixels image format
	int m_type;      // FLOAT or HALF_FLOAT
	int m_bytes_per_component;

public:
	pRenderVertexBuffer(int nverts, int size, int type);
	~pRenderVertexBuffer();

	unsigned int GetNVerts() const { return m_nverts; };
	int GetSize() const { return m_size; };
	int GetType() const { return m_type; };
	int GetFormat() const { return m_format; };
	int GetBytesPerComponent() const { return m_bytes_per_component; };

	void LoadData(void *data);                // load vertex data from memory
	void Read(int buffer, int w, int h);   // read vertex data from frame buffer
	void Write(int buffer, int w, int h, void *data);  // write vertex data to frame buffer
	void SetVertexPointer();
	void SetTexcoordPointer();
	void SetAttribPointer(int index);
};

#endif
#endif
