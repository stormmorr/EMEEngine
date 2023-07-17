/*! \file */

#ifndef PRENDERPROFILEVERT_H
#define PRENDERPROFILEVERT_H

#ifndef P_DISABLE_3D
#if 0 // P_SUPPORT_CG

class P3D_API pRenderProfileVertexMP : public pRenderProfile
{
	public:
#if 0 // P_SUPPORT_CG
		//*CGprofile vert_profile;
		
		//*CGprogram cgprog_vert_shadow;
		//*CGprogram cgprog_vert_ambient;
		//*CGprogram cgprog_vert_light;
		
		//*CGparameter cgparam_vert_shadow_modelviewproj;
		//*CGparameter cgparam_vert_shadow_lightpos;

		//*CGparameter cgparam_vert_viewinverse;
		//*CGparameter cgparam_vert_lightviewprojbias;
		//*CGparameter cgparam_vert_camerapos;
		//*CGparameter cgparam_vert_specular;
		//*CGparameter cgparam_vert_skincolor;
		//*CGparameter cgparam_vert_lightcolor;
		//*CGparameter cgparam_vert_lightpos;
		//*CGparameter cgparam_vert_lightspot;
#endif

	pRenderProfileVertexMP(const char *profile_name)
	{ 
		name=profile_name;

#if 0 // P_SUPPORT_CG
		vert_profile=CG_PROFILE_ARBVP1;
		
		cgprog_vert_shadow=0;
		cgprog_vert_ambient=0;
		cgprog_vert_light=0;

		cgparam_vert_shadow_modelviewproj=0;
		cgparam_vert_shadow_lightpos=0;

		cgparam_vert_viewinverse=0;
		cgparam_vert_lightviewprojbias=0;
		cgparam_vert_specular=0;
		cgparam_vert_camerapos=0;
		cgparam_vert_skincolor=0;
		cgparam_vert_lightcolor=0;
		cgparam_vert_lightpos=0;
		cgparam_vert_lightspot=0;
#endif
	}

	virtual ~pRenderProfileVertexMP()
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
