#include "pch.h"
#include "paralelo3d.h"

pMaterial::pMaterial() :
	diffuse(0.5f,0.5f,0.5f,1.0f),
	specular(1.0f,1.0f,1.0f,16.0f),
	selfillum(0,0,0,0),
	skincolor(0,0,0),
	opacity(1.0f),
	reflection(0.0f),
	refraction(1.0f),
	bump(0.0f),
	envscale(0.5f),
	texid(-1),
	texnormalid(-1),
	texselfillumid(-1),
	flags(0)
{ }

pMaterial::pMaterial(const pMaterial& in) :
	diffuse(in.diffuse),
	specular(in.specular),
	selfillum(in.selfillum),
	skincolor(in.skincolor),
	opacity(in.opacity),
	reflection(in.reflection),
	refraction(in.refraction),
	bump(in.bump),
	envscale(in.envscale),
	texid(in.texid),
	texnormalid(in.texnormalid),
	texselfillumid(in.texselfillumid),
	flags(in.flags),
	name(in.name),
	texname(in.texname),
	texnormalname(in.texnormalname),
	texselfillumname(in.texselfillumname),
	passes(in.passes)
{ }

void pMaterial::operator=(const pMaterial& in)
{
	diffuse=in.diffuse;
	specular=in.specular;
	selfillum=in.selfillum;
	skincolor=in.skincolor;
	opacity=in.opacity;
	reflection=in.reflection;
	refraction=in.refraction;
	bump=in.bump;
	envscale=in.envscale;
	texid=in.texid;
	texnormalid=in.texnormalid;
	texselfillumid=in.texselfillumid;
	flags=in.flags;
	name=in.name;
	texname=in.texname;
	texnormalname=in.texnormalname;
	texselfillumname=in.texselfillumname;
	passes=in.passes;
}

void pMaterial::write(FILE *fp) const
{
	name.write(fp);
	fwrite(&diffuse,3,sizeof(float),fp);
	fwrite(&specular,4,sizeof(float),fp);
	fwrite(&selfillum,3,sizeof(float),fp);
	fwrite(&skincolor,3,sizeof(float),fp);
	fwrite(&opacity,1,sizeof(float),fp);
	fwrite(&reflection,1,sizeof(float),fp);
	fwrite(&refraction,1,sizeof(float),fp);
	fwrite(&bump,1,sizeof(float),fp);
	fwrite(&envscale,1,sizeof(float),fp);
	fwrite(&flags,1,sizeof(int),fp);
	texname.write(fp);
	texnormalname.write(fp);
	texselfillumname.write(fp);

	int i,j=passes.num;
	fwrite(&j,1,sizeof(int),fp);
	for( i=0;i<j;i++ )
		passes.buf[i].write(fp);
}

void pMaterial::read(pFile& fp,int ver)
{
	name.read(fp);
	fp.read(&diffuse,3*sizeof(float));
	fp.read(&specular,4*sizeof(float));
	fp.read(&selfillum,3*sizeof(float));
	if(ver>=P3D_FILEVER+4)
		fp.read(&skincolor,3*sizeof(float));
	fp.read(&opacity,sizeof(float));
	fp.read(&reflection,sizeof(float));
	fp.read(&refraction,sizeof(float));
	fp.read(&bump,sizeof(float));
	fp.read(&envscale,sizeof(float));
	fp.read(&flags,sizeof(int));
	texname.read(fp);
	texnormalname.read(fp);
	if (ver>=P3D_FILEVER+6)
		texselfillumname.read(fp);
	texid=-1;
	texnormalid=-1;
	texselfillumid=-1;

	if (ver>=P3D_FILEVER+7)
	{
		int i,j;
		pRenderPass rp;
		fp.read(&j,sizeof(int));
		for( i=0;i<j;i++ )
		{
			rp.read(fp,ver);
			passes.add(rp);
		}
	}
}

void pMaterial::load_textures(const pString& p3dfile)
{
	pString str,file;
	int f=(flags&P_MATFLAGS_NOMIPMAP)?P_PICFLAGS_NOMIPMAP:0;

	if (texname[0]!=0)
	{
		str=texname;
		file=texname;
		if (str[1]==':' || (str[0]=='\\' && str[1]=='\\'))
			check_path(g_render->app_path,p3dfile,file);
		else
		{
			str=g_render->app_path+file;
			check_path(g_render->app_path,str,file);
		}

		if (file.length())
			texid=g_render->load_tex(file,f,g_render->texload);
	}

	if (texnormalname[0]!=0)
	{
		str=texnormalname;
		file=texnormalname;
		if (str[1]==':' || (str[0]=='\\' && str[1]=='\\'))
			check_path(g_render->app_path,p3dfile,file);
		else
		{
			str=g_render->app_path+file;
			check_path(g_render->app_path,str,file);
		}

		if (file.length())
			texnormalid=g_render->load_tex(file,f|P_PICFLAGS_NORMALMAP,g_render->texload);
	}

	if (texselfillumname[0]!=0)
	{
		str=texselfillumname;
		file=texselfillumname;
		if (str[1]==':' || (str[0]=='\\' && str[1]=='\\'))
			check_path(g_render->app_path,p3dfile,file);
		else
		{
			str=g_render->app_path+file;
			check_path(g_render->app_path,str,file);
		}

		if (file.length())
			texselfillumid=g_render->load_tex(file,f,g_render->texload);
	}

	int i;
	for( i=0;i<passes.num;i++ )
		passes.buf[i].load_texture(p3dfile);
}
