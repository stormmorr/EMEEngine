#include "paralelo3d.h"
#include "../viewer.h"

//pCamera pcamera;

//// THE FOLLOWING SOURCE PRENDER
int load_tex(const char *texfile,int flags,int load);
void set_tex_params(pPicture *p,unsigned int type1,unsigned int type2);
void build_mipmaps(pPicture *picture,unsigned int type2);

int load_tex(const char *texfile,int flags,int load)
{
	int texdetail = 0;
	if (texfile==0 || texfile[0]==0 || texfile[0]==' ')
		return -1;

	//int i;
	//for( i=0;i<pic.num;i++ )
	//	if (pic.buf[i])
	//	if (!stricmp(texfile,(const char *)pic.buf[i]->name)
	//		&& pic.buf[i]->flags==flags)
	//	{
	//		if (picid.buf[i]>0)
	//			pic.buf[i]->refcount++;
	//		return i;
	//	}

	unsigned int id;
	pPicture *p=new pPicture;

	if (load)
	{
		id=p->LoadPIC(texfile);
		if (id==0)
		{
			delete p;
			return -1;
		}
		p->refcount=1;
	    p->CheckSize(texdetail);
	}
	else
		p->refcount=0;

	p->name=texfile;
	//pic.add(p);

	p->flags=flags;

	if (load)
	{
#ifndef P_DISABLE_3D
		glGenTextures(1,&id);
		//picid.add(id);
		if (p->flags&P_PICFLAGS_TEX3D)
		{
			glBindTexture(GL_TEXTURE_3D,id);
			set_tex_params(p,GL_TEXTURE_3D,GL_TEXTURE_3D);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D,id);
			set_tex_params(p,GL_TEXTURE_2D,GL_TEXTURE_2D);
		}
#else
		//picid.add(0);
#endif
	}
	else
		//picid.add(0);

	//if (load)
		//pic.buf[pic.num-1]->FreePicture();

	return 1;//picid.num-1;
}

void set_tex_params(pPicture *p,unsigned int type1,unsigned int type2)
{
	int texmipmap=1;
	int texfilter=1;
#ifndef P_DISABLE_3D
	if (p==0)
		return;

	if (p->bytespixel==4)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,GL_RGBA,p->sx,p->sy,0,GL_RGBA,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,GL_RGBA,p->sx,p->sy,p->sz,0,GL_RGBA,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
	else
	if (p->bytespixel==3)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,GL_RGB,p->sx,p->sy,0,GL_RGB,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,GL_RGB,p->sx,p->sy,p->sz,0,GL_RGB,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
	else
	if (p->bytespixel==1)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,1,p->sx,p->sy,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,1,p->sx,p->sy,p->sz,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
#endif
}

void build_mipmaps(pPicture *picture,unsigned int type2)
{
#ifndef P_DISABLE_3D
	if (picture->buf==0 || 
		(picture->flags&P_PICFLAGS_NOMIPMAP))
		return;

	int format=0;
	if (picture->bytespixel==1)
		format=GL_LUMINANCE;
	else
	if (picture->bytespixel==3)
		format=GL_RGB;
	else
	if (picture->bytespixel==4)
		format=GL_RGBA;

	if (format)
		gluBuild2DMipmaps(GL_TEXTURE_2D,picture->bytespixel,
			picture->sx,picture->sy,format,GL_UNSIGNED_BYTE,picture->buf);
#endif
}

void sel_tex(int tex)
{
#ifndef P_DISABLE_3D
	if (tex<0 || tex>=theViewer.picid.num)
		glDisable(GL_TEXTURE_2D);
	else
	{
		glBindTexture(GL_TEXTURE_2D,theViewer.picid.buf[tex]);
		glEnable(GL_TEXTURE_2D);
	}
#endif
}

///// Usefull Shape Funtions

#if 0	// TEXTURED QUAD
	glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
		glTexCoord2d(1,1); glVertex3f(+50.5f,+50.5f,0); // Top Right
		glTexCoord2d(0,1); glVertex3f(-50.5f,+50.5f,0); // Top Left
		glTexCoord2d(1,0); glVertex3f(+50.5f,-50.5f,0); // Bottom Right
		glTexCoord2d(0,0); glVertex3f(-50.5f,-50.5f,0); // Bottom Left
	glEnd();										// Done Building Triangle Strip
#endif

#if 0	// TEXTURED CUBE
	glBindTexture(GL_TEXTURE_2D, newtexture.m_TexID);

	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  10.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  10.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -10.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f,  10.0f,  10.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f,  10.0f,  10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -10.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f, -10.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  10.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  10.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 10.0f,  10.0f, -10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 10.0f,  10.0f,  10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 10.0f, -10.0f,  10.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, -10.0f, -10.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-10.0f, -10.0f,  10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-10.0f,  10.0f,  10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f,  10.0f, -10.0f);
	glEnd();
#endif