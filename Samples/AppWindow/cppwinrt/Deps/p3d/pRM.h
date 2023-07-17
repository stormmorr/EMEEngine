/*! \file */

#ifndef PRM_H
#define PRM_H

#if 0 // P_SUPPORT_CG
class pRM
{
	#define P_RM_PROFILES 5

	static //*CGprofile s_frag_profile[P_RM_PROFILES];
	static char *s_frag_ext[P_RM_PROFILES];
	static char *s_frag_main[P_RM_PROFILES];

	bool m_shadows;
	bool m_doubleprec;
	bool m_depthcorrect;
	bool m_depthbias;
	bool m_borderclamp;
	bool m_curved;
	int m_progmode;

	//*CGprogram m_vert_prog;

	//*CGprogram m_frag_prog;
	//*CGparameter m_lightpos;
	//*CGparameter m_lightspot;
	//*CGparameter m_tile;
	//*CGparameter m_depth;
	//*CGparameter m_camerapos;
	//*CGparameter m_ambient;
	//*CGparameter m_diffuse;
	//*CGparameter m_specular;
	//*CGparameter m_planes;
	//*CGparameter m_viewinv_lightviewprojbias;

	//*CGprogram m_frag_shadow_prog;
	//*CGparameter m_tile_sh;
	//*CGparameter m_depth_sh;
	//*CGparameter m_planem_sh;

	bool load_programs(
		int progmode,
		bool shadows,
		bool doubleprec,
		bool depthcorrect,
		bool depthbias,
		bool borderclamp,
		bool curved);

	void free_programs();

public:
	pRM();
	~pRM();

	// loads a .rm file with given compile program options
	void load(
		int progmode,
		bool shadows,
		bool doubleprec,
		bool depthcorrect,
		bool depthbias,
		bool borderclamp,
		bool curved);

	// draws the relief map mesh with given program options
	void draw(	
		pMesh *mesh,
		int color_tex,
		int relief_tex,
		int dist_tex,
		unsigned int tile,
		float depth,
		const pVector& amb,
		const pVector& diff,
		const pVector& spec,
		pLight *light);

	// draw relief map in shadow map (relief shadow shader)
	void draw_shadows(
		pMesh *mesh,
		int relief_tex,
		unsigned int tile,
		float depth,
		float radius);
	
	// get current program mode
	int get_progmode() 
	{ return m_progmode; };
};
#endif


#endif
