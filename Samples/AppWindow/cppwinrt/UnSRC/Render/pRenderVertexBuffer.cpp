#include "pch.h"
#include "paralelo3d.h"

#ifndef P_DISABLE_3D

pRenderVertexBuffer::pRenderVertexBuffer(int nverts, int size, int type) :
	m_nverts(nverts), m_size(size), m_usage(GL_STREAM_COPY), m_type(type)
{
    switch(m_type) 
	{
        case GL_HALF_FLOAT_NV: m_bytes_per_component = 2; break;
        case GL_FLOAT: m_bytes_per_component = sizeof(float); break;
        default:
            fprintf(stderr, "Error: unsupported RenderVertexArray type\n");
            return;
    }
    switch(m_size) 
	{
        case 1: m_format = GL_LUMINANCE; break;
        case 3: m_format = GL_RGB; break;
        case 4: m_format = GL_RGBA; break;
        default:
            fprintf(stderr, "Error: unsupported RenderVertexArray size\n");
            return;
    }

    // create the buffer object
    glGenBuffersARB(1, &m_buffer);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, m_buffer);
	glBufferDataARB(GL_PIXEL_PACK_BUFFER_EXT, m_nverts*m_size*m_bytes_per_component, 0, m_usage); // undefined data
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, 0);
}

pRenderVertexBuffer::~pRenderVertexBuffer()
{
    glDeleteBuffersARB(1, &m_buffer);
}

void pRenderVertexBuffer::LoadData(void *data)
{
    // load data to buffer object
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, m_buffer);
    glBufferDataARB(GL_PIXEL_PACK_BUFFER_EXT, m_nverts*m_size*m_bytes_per_component, data, m_usage);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, 0);
}

void pRenderVertexBuffer::Read(int buffer, int w, int h)
{
    // bind buffer object to pixel pack buffer
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, m_buffer);
    // read from frame buffer to buffer object
    glReadBuffer(buffer);
    glReadPixels(0, 0, w, h, m_format, m_type, 0);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, 0);
}

void pRenderVertexBuffer::Write(int buffer, int w, int h,void *data)
{
    // bind buffer object to pixel pack buffer
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, m_buffer);
    // write to frame buffer from buffer object
    glDrawBuffer(buffer);
	glDrawPixels(w,h,m_format,m_type,data);
    glBindBufferARB(GL_PIXEL_PACK_BUFFER_EXT, 0);
}

void pRenderVertexBuffer::SetVertexPointer()
{
    // bind buffer object to vertex array 
    glBindBufferARB(GL_ARRAY_BUFFER, m_buffer);
    glVertexPointer(m_size, m_type, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER, 0);
}

void pRenderVertexBuffer::SetTexcoordPointer()
{
    // bind buffer object to texcoord array 
    glBindBufferARB(GL_ARRAY_BUFFER, m_buffer);
    glTexCoordPointer(m_size, m_type, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER, 0);
}

void pRenderVertexBuffer::SetAttribPointer(int index)
{
    // bind buffer object to vertex array 
    glBindBufferARB(GL_ARRAY_BUFFER, m_buffer);
    glVertexAttribPointerARB(index, m_size, m_type, GL_FALSE, 0, 0);
    glBindBufferARB(GL_ARRAY_BUFFER, 0);
}

#endif
