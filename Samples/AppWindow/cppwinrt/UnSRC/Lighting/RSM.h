/*

	Reflective Shadow Maps - Raw GL
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __RSM__
#define __RSM__

#include "paralelo3d.h"

class RSM
{
public:
	RSM();
	~RSM();

	pPBuffer *m_shadow_buffer;		//!< offline buffer for shadow map (WGL_ARB_pbuffer)

	int m_size;						//!< shadow map dimension
	unsigned int m_shadow_map;		//!< OpenGL texture id shadow map
	float m_shadow_offset_factor;	//!< factor parameter of glPolygonOffset command
	float m_shadow_offset_units;	//!< units parameter of glPolygonOffset command
	static bool s_support_NV_render_depth_texture;

	// Z buffer
	void StartZbuffer(void);
	void StopZbuffer(void);

	void DrawPane(unsigned int i_texture, int i_x, int i_y, int i_scalex, int i_scaley);
	void PrintZBuffer(void);

	unsigned int m_map[5];
};

#if 0
		//! Initialize all resources.
		/*!
			@param size texture size (default = 512)
		*/
		void init(int size=512);

		//! Reset all resources.
		void reset();

		//! Given a spot light, generates a shadow map.
		/*!
			@param light current light
		*/
		void generate_shadow_map(pLight *light);

		//! Bind shadow map.
		/*!
			@param light current light
		*/
		void bind_shadow_map(pLight *light) const;

		//! Unbind shadow map.
		void unbind_shadow_map() const;

		//! Draw
		void draw() const;

		//! Set camera of view point light
		/*!
			@param light current light
		*/
		void setup_camera(pLight *light);

		void bind_pbuffer_as_texture() const;
		void release_pbuffer_texture() const;

		//! Test if shadow map is supported.
		/*!
			@return true if this effect is supported
		*/
		static bool test();
#endif

#endif