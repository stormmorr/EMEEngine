/*! \file */
#if 0 // QAGE_DESKTOP
#ifndef PRENDERGLOW_H
#define PRENDERGLOW_H

#ifndef P_DISABLE_3D

class P3D_API pRenderGlow
{
	public:
		pPBuffer *m_glowpb[2];
		unsigned int m_curpb;
		unsigned int m_tex;
		unsigned int m_size;
		
		unsigned int m_blurnumpass;
		float m_blurfeedbackfact;
#if 0 // P_SUPPORT_CG
		//*CGprogram m_blur_prog;
		//*CGparameter m_texture_param;
		//*CGparameter m_dispuv_param;
#endif
	pRenderGlow() :
		m_curpb(0),
		m_tex(0),
		m_size(256),
		m_blurnumpass(2),
		m_blurfeedbackfact(0.5f)
	{ 
		m_glowpb[0]=0;
		m_glowpb[1]=0;
#if 0 // P_SUPPORT_CG
		m_blur_prog=0;
		m_texture_param=0;
		m_dispuv_param=0;
#endif
	}

	~pRenderGlow()
	{ reset(); }

	static bool test();
	
	void init(int size);
	void reset();
	
	void generate_glow();
	void draw_glow();

	private:
	bool load_program();
	void draw_rect(bool blur);
};

#endif
#endif
#endif