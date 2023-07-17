/*! \file */

#ifndef PRENDERPROFILEFRAG_H
#define PRENDERPROFILEFRAG_H

#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG

class P3D_API pRenderProfileFragmentMP : public pRenderProfile
{
	public:
		int null_normalmap,null_texturemap;
		bool full;

#if 0 // P_SUPPORT_CG
		//*CGprofile vert_profile;
		//*CGprofile frag_profile;
		
		//*CGprogram cgprog_vert_ambient;
		//*CGprogram cgprog_vert_light;
		//*CGprogram cgprog_frag_light;
		//*CGprogram cgprog_vert_shadow;
		
		//*CGparameter cgparam_vert_shadow_modelviewproj;
		//*CGparameter cgparam_vert_shadow_lightpos;

		//*CGparameter cgparam_vert_viewinverse;
		//*CGparameter cgparam_vert_lightviewprojbias;
		//*CGparameter cgparam_vert_farplane;
		//*CGparameter cgparam_vert_camerapos;
		//*CGparameter cgparam_vert_lightpos;
		//*CGparameter cgparam_vert_lightspot;
		
		//*CGparameter cgparam_frag_camerapos;
		//*CGparameter cgparam_frag_specular;
		//*CGparameter cgparam_frag_skincolor;
		//*CGparameter cgparam_frag_lightcolor;
		//*CGparameter cgparam_frag_lightpos;
		//*CGparameter cgparam_frag_lightspot;
		//*CGparameter cgparam_frag_shadowmapflag;
		//*CGparameter cgparam_frag_bump;
#endif

	pRenderProfileFragmentMP(const char *profile_name,bool full_quality)
	{ 
		name=profile_name;
		full=full_quality;
		null_normalmap=-1;
		null_texturemap=-1;

#if 0 // P_SUPPORT_CG
		vert_profile=CG_PROFILE_ARBVP1;
		frag_profile=CG_PROFILE_ARBFP1;
		
		cgprog_vert_ambient=0;
		cgprog_vert_light=0;
		cgprog_frag_light=0;
		cgprog_vert_shadow=0;

		cgparam_vert_shadow_modelviewproj=0;
		cgparam_vert_shadow_lightpos=0;
		
		cgparam_vert_viewinverse=0;
		cgparam_vert_lightviewprojbias=0;
		cgparam_vert_farplane=0;
		cgparam_vert_camerapos=0;
		cgparam_vert_lightpos=0;
		cgparam_vert_lightspot=0;

		cgparam_frag_specular=0;
		cgparam_frag_camerapos=0;
		cgparam_frag_skincolor=0;
		cgparam_frag_lightcolor=0;
		cgparam_frag_lightpos=0;
		cgparam_frag_lightspot=0;
		cgparam_frag_shadowmapflag=0;
#endif
	}

	virtual ~pRenderProfileFragmentMP()
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

#endif
