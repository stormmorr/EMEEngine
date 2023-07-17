/*! \file */
#if 0 // QAGE_DESKTOP
#ifndef PRENDERRIPPLE_H
#define PRENDERRIPPLE_H

class P3D_API pRenderRipple
{
	public:
		pPBuffer *m_ripplepb;
		unsigned int m_tex;
		unsigned int m_size;
		float m_start_time;
		float m_radius;
		float m_duration;
		float m_intensity;
		pVector m_point;
		int m_prog;
		int m_fragment;
		int m_vertexgridsize;
		int m_vertexbuffer;
		float *m_gridvert;

#if 0 // P_SUPPORT_CG
		//*CGprofile m_profile;
		//*CGprogram m_ripple_prog;
		//*CGparameter m_modelviewproj_param;
		//*CGparameter m_point_param;
		//*CGparameter m_texture_param;
#endif

	pRenderRipple() :
		m_ripplepb(0),
		m_tex(0),
		m_size(512),
		m_radius(1.0f),
		m_duration(0.6f),
		m_intensity(0.2f),
		m_start_time(0),
		m_prog(0),
		m_fragment(1),
		m_vertexgridsize(32),
		m_vertexbuffer(1),
		m_gridvert(0)
	{ 
#if 0 // P_SUPPORT_CG
		m_ripple_prog=0;
		m_modelviewproj_param=0;
		m_point_param=0;
		m_texture_param=0;
#endif
	}
	
	~pRenderRipple()
	{ reset(); }

	static bool test();
	
	void init(int size,int prog=2);
	void reset();
	void draw();
	void add_ripple(float posu,float posv,float radius,float duration,float intensity);
	
	private:
	void draw_rect();
	void build_grid();
	bool load_program(int prog);
};

#endif
#endif