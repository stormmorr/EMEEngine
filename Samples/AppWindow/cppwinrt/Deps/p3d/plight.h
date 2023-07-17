/*! \file */

#ifndef PLIGHT_H
#define PLIGHT_H

//// Reverse include Unification Specifically
//#include "../UnSrc/Lighting/

class P3D_API pLight
{
	public:
		pVector pos;
		pVector color;
		float angle;			//!< only for spot light
		pMatrix orientation;	//!< only for spot light
		int flags;
		pString name;
		pBoundBox bbox;			//!< only for omni light
		pFrustum frustum;		//!< only for spot light

		int type_shadow;		//!< used shadow algorithm (0 - shadow volume, 1 - shadow map)
		enum
		{
			SHADOW_VOLUME=0,
			SHADOW_MAP,
		};

		pAnimation anim_pos_x;
		pAnimation anim_pos_y;
		pAnimation anim_pos_z;
		pAnimation anim_radius;
		pAnimation anim_color;

		pArray<pRenderObject *> objlistlight;

		bool m_Live;

	pLight() : 
		pos(0,0,0,100),
		color(1,1,1),
		angle(0.0f),
		flags(0),
		type_shadow(0)
	{ }

	pLight(const pLight& in) : 
		pos(in.pos),color(in.color),
		angle(in.angle),orientation(in.orientation),
		flags(in.flags), name(in.name),
		anim_pos_x(in.anim_pos_x), 
		anim_pos_y(in.anim_pos_y), 
		anim_pos_z(in.anim_pos_z), 
		anim_radius(in.anim_radius), 
		anim_color(in.anim_color),
		objlistlight(in.objlistlight),
		bbox(in.bbox),
		frustum(in.frustum),
		type_shadow(in.type_shadow)
	{ }

	void operator=(const pLight& in) 
	{ 
		pos = in.pos;
		color = in.color;
		angle = in.angle;
		orientation = in.orientation;
		flags = in.flags;
		name = in.name;
		anim_pos_x = in.anim_pos_x; 
		anim_pos_y = in.anim_pos_y; 
		anim_pos_z = in.anim_pos_z; 
		anim_radius = in.anim_radius;
		anim_color = in.anim_color;
		objlistlight = in.objlistlight;
		bbox = in.bbox;
		frustum = in.frustum;
		type_shadow = in.type_shadow;
	}

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

	//! Adds or not a render object into the light array of objects
	/*!
		Given a render object, verifies if it is illuminated by this light. If it
		is true, adds this object into the light objects and return true. Otherwise
		do nothing and return false.
		@param obj a given render object
		@return true if object was considered and false otherwise
	*/
	bool update_objects_light(pRenderObject *obj);

	//! If it is a spot light, build its frustum.
	void build_frustum();

	//! Turn on this light with OpenGL commands.
	/*!
		@param light_id OpenGL light id
	*/
	void turn_on(unsigned light_id) const;

	//! Animate light parameters
	/*!
		@param time time in sec for current animation position
	*/
	void animate(float time);
};

#if 0
class Globe Map light

class bidirectional light source
{
private:
	//std::ref
	//std::auto_ptr
	unShader::GShape	ShapeHandle;

	unsigned int CalcFlag;

public:
		pVector pos;
		pVector color;
		float angle;			//!< only for spot light
		pMatrix orientation;	//!< only for spot light
		int flags;
		pString name;
		pBoundBox bbox;			//!< only for omni light
		pFrustum frustum;		//!< only for spot light

		int type_shadow;		//!< used shadow algorithm (0 - shadow volume, 1 - shadow map)
		enum
		{
			SHADOW_VOLUME=0,
			SHADOW_MAP,
		};

		pAnimation anim_pos_x;
		pAnimation anim_pos_y;
		pAnimation anim_pos_z;
		pAnimation anim_radius;
		pAnimation anim_color;

		pArray<pRenderObject *> objlistlight;

	pLight() : 
		pos(0,0,0,100),
		color(1,1,1),
		angle(0.0f),
		flags(0),
		type_shadow(0)
	{ }

	pLight(const pLight& in) : 
		pos(in.pos),color(in.color),
		angle(in.angle),orientation(in.orientation),
		flags(in.flags), name(in.name),
		anim_pos_x(in.anim_pos_x), 
		anim_pos_y(in.anim_pos_y), 
		anim_pos_z(in.anim_pos_z), 
		anim_radius(in.anim_radius), 
		anim_color(in.anim_color),
		objlistlight(in.objlistlight),
		bbox(in.bbox),
		frustum(in.frustum),
		type_shadow(in.type_shadow)
	{ }

	void operator=(const pLight& in) 
	{ 
		pos = in.pos;
		color = in.color;
		angle = in.angle;
		orientation = in.orientation;
		flags = in.flags;
		name = in.name;
		anim_pos_x = in.anim_pos_x; 
		anim_pos_y = in.anim_pos_y; 
		anim_pos_z = in.anim_pos_z; 
		anim_radius = in.anim_radius;
		anim_color = in.anim_color;
		objlistlight = in.objlistlight;
		bbox = in.bbox;
		frustum = in.frustum;
		type_shadow = in.type_shadow;
	}

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

	//! Adds or not a render object into the light array of objects
	/*!
		Given a render object, verifies if it is illuminated by this light. If it
		is true, adds this object into the light objects and return true. Otherwise
		do nothing and return false.
		@param obj a given render object
		@return true if object was considered and false otherwise
	*/
	bool update_objects_light(pRenderObject *obj);

	//! If it is a spot light, build its frustum.
	void build_frustum();

	//! Turn on this light with OpenGL commands.
	/*!
		@param light_id OpenGL light id
	*/
	void turn_on(unsigned light_id) const;

	//! Animate light parameters
	/*!
		@param time time in sec for current animation position
	*/
	void animate(float time);
}

class light manipulation wavelet

//// Include GShapes from mesh cache header
class light block shape

class pLight
{
	public:
		pVector pos;
		pVector color;
		float angle;			//!< only for spot light
		pMatrix orientation;	//!< only for spot light
		int flags;
		pString name;
		pBoundBox bbox;			//!< only for omni light
		pFrustum frustum;		//!< only for spot light

		int type_shadow;		//!< used shadow algorithm (0 - shadow volume, 1 - shadow map)
		enum
		{
			SHADOW_VOLUME=0,
			SHADOW_MAP,
		};

		pAnimation anim_pos_x;
		pAnimation anim_pos_y;
		pAnimation anim_pos_z;
		pAnimation anim_radius;
		pAnimation anim_color;

		pArray<pRenderObject *> objlistlight;

	pLight() : 
		pos(0,0,0,100),
		color(1,1,1),
		angle(0.0f),
		flags(0),
		type_shadow(0)
	{ }

	pLight(const pLight& in) : 
		pos(in.pos),color(in.color),
		angle(in.angle),orientation(in.orientation),
		flags(in.flags), name(in.name),
		anim_pos_x(in.anim_pos_x), 
		anim_pos_y(in.anim_pos_y), 
		anim_pos_z(in.anim_pos_z), 
		anim_radius(in.anim_radius), 
		anim_color(in.anim_color),
		objlistlight(in.objlistlight),
		bbox(in.bbox),
		frustum(in.frustum),
		type_shadow(in.type_shadow)
	{ }

	void operator=(const pLight& in) 
	{ 
		pos = in.pos;
		color = in.color;
		angle = in.angle;
		orientation = in.orientation;
		flags = in.flags;
		name = in.name;
		anim_pos_x = in.anim_pos_x; 
		anim_pos_y = in.anim_pos_y; 
		anim_pos_z = in.anim_pos_z; 
		anim_radius = in.anim_radius;
		anim_color = in.anim_color;
		objlistlight = in.objlistlight;
		bbox = in.bbox;
		frustum = in.frustum;
		type_shadow = in.type_shadow;
	}

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

	//! Adds or not a render object into the light array of objects
	/*!
		Given a render object, verifies if it is illuminated by this light. If it
		is true, adds this object into the light objects and return true. Otherwise
		do nothing and return false.
		@param obj a given render object
		@return true if object was considered and false otherwise
	*/
	bool update_objects_light(pRenderObject *obj);

	//! If it is a spot light, build its frustum.
	void build_frustum();

	//! Turn on this light with OpenGL commands.
	/*!
		@param light_id OpenGL light id
	*/
	void turn_on(unsigned light_id) const;

	//! Animate light parameters
	/*!
		@param time time in sec for current animation position
	*/
	void animate(float time);
};
#endif

#endif
