/*! \file */

#ifndef PMATERIAL_H
#define PMATERIAL_H

class P3D_API pMaterial
{
	public:
		pVector diffuse;
		pVector specular;
		pVector skincolor;
		pVector selfillum;
		float opacity;
		float reflection;
		float refraction;
		float bump;
		float envscale;
		int texid;
		int texnormalid;
		int texselfillumid;
		int flags;
		pString name;
		pString texname;
		pString texnormalname;
		pString texselfillumname;

		pArray<pRenderPass> passes;
		
	pMaterial();

	pMaterial(const pMaterial& in);

	void operator=(const pMaterial& in);

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

	void load_textures(const pString& p3dfile);
};

#endif
