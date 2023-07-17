/*! \file */

#ifndef PRENDERPASS_H
#define PRENDERPASS_H

class P3D_API pRenderPass
{
	public:
		pString m_texname;
		int m_texid;

		int m_texclamp;
		int m_envmap;

		float m_tcmod_scale[2];
		float m_tcmod_scroll[2];
		float m_tcmod_rotate;
		pPeriodicFunc m_tcmod_stretch_func;

	pRenderPass();
	pRenderPass(const pRenderPass& in);

	void operator=(const pRenderPass& in);

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);
	void load_texture(const pString& p3dfile);
	void setup_pass(unsigned int texture_unit) const;
	static void clear_pass(unsigned int texture_unit);
};

#endif
