#include "pch.h"
#include "paralelo3d.h"

pRenderPass::pRenderPass() :
	m_texid(-1),
	m_texclamp(0),
	m_envmap(0)
{
	m_tcmod_scale[0]=1.0f;
	m_tcmod_scale[1]=1.0f;
	m_tcmod_scroll[0]=0.0f;
	m_tcmod_scroll[1]=0.0f;
	m_tcmod_rotate=0.0f;
}

pRenderPass::pRenderPass(const pRenderPass& in) :
	m_texname(in.m_texname),
	m_texid(in.m_texid),
	m_texclamp(in.m_texclamp),
	m_envmap(in.m_envmap)
{
	m_tcmod_scale[0]=in.m_tcmod_scale[0];
	m_tcmod_scale[1]=in.m_tcmod_scale[1];
	m_tcmod_scroll[0]=in.m_tcmod_scroll[0];
	m_tcmod_scroll[1]=in.m_tcmod_scroll[1];
	m_tcmod_rotate=in.m_tcmod_rotate;
	m_tcmod_stretch_func=in.m_tcmod_stretch_func;
}

void pRenderPass::operator=(const pRenderPass& in)
{
	m_texname=in.m_texname;
	m_texid=in.m_texid;
	m_texclamp=in.m_texclamp;
	m_envmap=in.m_envmap;
	m_tcmod_scale[0]=in.m_tcmod_scale[0];
	m_tcmod_scale[1]=in.m_tcmod_scale[1];
	m_tcmod_scroll[0]=in.m_tcmod_scroll[0];
	m_tcmod_scroll[1]=in.m_tcmod_scroll[1];
	m_tcmod_rotate=in.m_tcmod_rotate;
	m_tcmod_stretch_func=in.m_tcmod_stretch_func;
}

void pRenderPass::write(FILE *fp) const
{
	m_texname.write(fp);
	fwrite(&m_texclamp,1,sizeof(int),fp);
	fwrite(&m_envmap,1,sizeof(int),fp);
	fwrite(m_tcmod_scale,2,sizeof(float),fp);
	fwrite(m_tcmod_scroll,2,sizeof(float),fp);
	fwrite(&m_tcmod_rotate,1,sizeof(float),fp);
	m_tcmod_stretch_func.write(fp);
}

void pRenderPass::read(pFile& fp,int ver)
{
	m_texname.read(fp);
	fp.read(&m_texclamp,sizeof(int));
	fp.read(&m_envmap,sizeof(int));
	fp.read(m_tcmod_scale,2*sizeof(float));
	fp.read(m_tcmod_scroll,2*sizeof(float));
	fp.read(&m_tcmod_rotate,sizeof(float));
	m_tcmod_stretch_func.read(fp,ver);
}

void pRenderPass::load_texture(const pString& p3dfile)
{
	pString str,file;

	if (m_texname[0]!=0)
	{
		str=m_texname;
		file=m_texname;
		if (str[1]==':' || (str[0]=='\\' && str[1]=='\\'))
			check_path(g_render->app_path,p3dfile,file);
		else
		{
			str=g_render->app_path+file;
			check_path(g_render->app_path,str,file);
		}

		if (file.length())
			m_texid=g_render->load_tex(file,0,g_render->texload);
	}
}

void pRenderPass::setup_pass(unsigned int texture_unit) const
{
#ifndef P_DISABLE_3D
	glActiveTextureARB(texture_unit);
	glClientActiveTextureARB(texture_unit);
	g_render->sel_tex(m_texid);

	// clamp
	if(m_texclamp)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	}
	
	// environment map
	if(m_envmap)
	{
		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}
	else
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	// addtive blend
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
	glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);

	// tc mod
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glTranslatef(0.5f,0.5f,0.0f);
	glRotatef(fmodf(m_tcmod_rotate*g_render->curtimef,360.0f),0.0f,0.0f,1.0f);
	glScalef(m_tcmod_scale[0],m_tcmod_scale[1],1.0f);
	if (m_tcmod_stretch_func.m_type)
	{
		float y=1.0f/m_tcmod_stretch_func.eval(g_render->curtimef);
		glScalef(y,y,1.0f);
	}
	glTranslatef((m_tcmod_scroll[0]!=0)?m_tcmod_scroll[0]*fmodf(g_render->curtimef,1.0f/(m_tcmod_scroll[0]*m_tcmod_scale[0])):0.0f,
				 (m_tcmod_scroll[1]!=0)?m_tcmod_scroll[1]*fmodf(g_render->curtimef,1.0f/(m_tcmod_scroll[1]*m_tcmod_scale[1])):0.0f,
				 0.0f);
	glTranslatef(-0.5f,-0.5f,0.0f);
	glMatrixMode(GL_MODELVIEW);
#endif
}

void pRenderPass::clear_pass(unsigned int texture_unit)
{
#ifndef P_DISABLE_3D
	glActiveTextureARB(texture_unit);
	glClientActiveTextureARB(texture_unit);
	g_render->sel_tex(-1);

	// environment map
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// multiplicative blend
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	// tc mode
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
#endif
}
