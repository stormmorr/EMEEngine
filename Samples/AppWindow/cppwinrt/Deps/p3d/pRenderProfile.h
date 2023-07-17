/*! \file */

#ifndef PRENDERPROFILE_H
#define PRENDERPROFILE_H

class P3D_API pRenderProfile
{
	public:
		pString name;

	pRenderProfile()
	{ }
	virtual ~pRenderProfile()
	{ }
		
	virtual int test() const=0;
	virtual int get_caps() const=0;
	virtual void print(pString& str) const=0;
	virtual void reset()=0;
	virtual void load()=0;
	virtual void ambient_pass(pArray<pRenderObject *>& o);
	virtual void draw_mp(pLight *l)=0;
	virtual void draw_mp(pArray<pRenderObject *>& o)=0;
	virtual void draw_sp(pArray<pRenderObject *>& o)=0;
	virtual void draw_shadows(pLight *l)=0;
	virtual void load_mat(const pMaterial *mat,int rendermode)=0;
	virtual void unload_mat(const pMaterial *mat,int rendermode)=0;
};

#ifndef P_DISABLE_3D

class P3D_API pRenderProfileStandardSP : public pRenderProfile
{
	public:
		int m_max_lights;

	pRenderProfileStandardSP(const char *profile_name)
	{ 
		name=profile_name;
	}
	virtual ~pRenderProfileStandardSP()
	{ reset(); }
		
	int test() const;
	int get_caps() const;
	void print(pString& str) const;
	void reset();
	void load();
	void draw_mp(pLight *l);
	void draw_mp(pArray<pRenderObject *>& o);
	void draw_sp(pArray<pRenderObject *>& o);
	void draw_shadows(pLight *l);
	void load_mat(const pMaterial *mat,int rendermode);
	void unload_mat(const pMaterial *mat,int rendermode);
};

class P3D_API pRenderProfileStandardMP : public pRenderProfile
{
	public:
		int m_max_lights;
		pString vert_extension;

#if 0 // P_SUPPORT_CG
		//*CGprofile vert_profile;
		//*CGprogram cgprog_vert_shadow;
		//*CGparameter cgparam_vert_shadow_modelviewproj;
		//*CGparameter cgparam_vert_shadow_lightpos;
#endif

	pRenderProfileStandardMP(const char *profile_name)
	{ 
		name=profile_name;

#if 0 // P_SUPPORT_CG
		vert_profile=CG_PROFILE_ARBVP1;
		cgprog_vert_shadow=0;
		cgparam_vert_shadow_modelviewproj=0;
		cgparam_vert_shadow_lightpos=0;
#endif
	}

	virtual ~pRenderProfileStandardMP()
	{ reset(); }
		
	int test() const;
	int get_caps() const;
	void print(pString& str) const;
	void reset();
	void load();
	void draw_mp(pLight *l);
	void draw_mp(pArray<pRenderObject *>& o);
	void draw_sp(pArray<pRenderObject *>& o);
	void draw_shadows(pLight *l);
	void load_mat(const pMaterial *mat,int rendermode);
	void unload_mat(const pMaterial *mat,int rendermode);
};

#endif

#endif
