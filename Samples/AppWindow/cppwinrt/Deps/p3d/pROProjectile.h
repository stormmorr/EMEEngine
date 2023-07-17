/*! \file */

#ifndef PROPROJECTILE_H
#define PROPROJECTILE_H

//! Render Object Projectile class
/*!
	This class implements an axial billboard that represents a projectile.
*/
class P3D_API pROProjectile : public pRenderObject
{
	private:

		int m_blendadd;			//!< additive blend mode?
		int m_glow;				//!< applies glow or not in this object

		float m_size_front;		//!< size
		float m_size_side_x;	//!< width of support plane
		float m_size_side_y;	//!< height of support plane
		
		int m_tex_front;		//!< texture id
		int m_tex_side;			//!< texture id

		float m_si[2],m_sf[2],m_ti[2],m_tf[2]; //!< texture coordinates for anim map
		int m_num_frames[2];							   //!< number of frames of animation map
		int m_num_frames_x[2];						   //!< number of frames in x direction of animation map
		int m_num_frames_y[2];						   //!< number of frames in y direction of animation map

		void update_bounding_box();

	public:

		pVector m_color;		//!< color of billboard
		pMesh *m_mesh;			//!< a triangle mesh
		float m_start_time;								   //!< animation map start time
		float m_frame_rate[2];				//!< frame rate of animation map
		int m_frame_size_x[2],m_frame_size_y[2];	//!< frame size needed for grid anim maps

		//! Default constructor.
		pROProjectile() :
			m_blendadd(0),
			m_glow(0),
			m_size_front(10.0f),
			m_size_side_x(20.0f),
			m_size_side_y(10.0f),
			m_color(1.0f),
			m_tex_front(-1),
			m_tex_side(-1),
			m_mesh(NULL)
		{
			m_start_time=0.0f;
			m_si[0]=m_si[1]=0.0f;
			m_sf[0]=m_sf[1]=1.0f;
			m_num_frames[0]=m_num_frames[1]=0;
			m_num_frames_x[0]=m_num_frames_x[1]=0;
			m_num_frames_y[0]=m_num_frames_y[1]=0;
			m_frame_rate[0]=m_frame_rate[1]=0.0f;
			m_frame_size_x[0]=m_frame_size_x[1]=16;
			m_frame_size_y[0]=m_frame_size_y[1]=16;
			m_type=TYPE_RO_PROJECTILE;
		}

		//! Destructor.
		virtual ~pROProjectile()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROProjectile(const pROProjectile& in) :
			pRenderObject(in),
			m_blendadd(in.m_blendadd),
			m_glow(in.m_glow),
			m_size_front(in.m_size_front),
			m_size_side_x(in.m_size_side_x),
			m_size_side_y(in.m_size_side_y),
			m_color(in.m_color),
			m_tex_front(in.m_tex_front),
			m_tex_side(in.m_tex_side),
			m_mesh(in.m_mesh)
		{
			m_start_time=in.m_start_time;
			m_si[0]=in.m_si[0];
			m_si[1]=in.m_si[1];
			m_sf[0]=in.m_sf[0];
			m_sf[1]=in.m_sf[1];
			m_num_frames[0]=in.m_num_frames[0];
			m_num_frames[1]=in.m_num_frames[1];
			m_num_frames_x[0]=in.m_num_frames_x[0];
			m_num_frames_x[1]=in.m_num_frames_x[1];
			m_num_frames_y[0]=in.m_num_frames_y[0];
			m_num_frames_y[1]=in.m_num_frames_y[1];
			m_frame_rate[0]=in.m_frame_rate[0];
			m_frame_rate[1]=in.m_frame_rate[1];
			m_frame_size_x[0]=in.m_frame_size_x[0];
			m_frame_size_x[1]=in.m_frame_size_x[1];
			m_frame_size_y[0]=in.m_frame_size_y[0];
			m_frame_size_y[1]=in.m_frame_size_y[1];
			m_type=TYPE_RO_PROJECTILE;
		}

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROProjectile(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It updates the bounding boxe associated with this object and calls
			the recursive step of all children.
			@param elapsed_time elapsed time in seconds
			@param global global transformation that will transform this objects and its children
		*/
		void step(const float elapsed_time,const pMatrix& global);

		//! Draws this object.
		void draw();

		//! Calculates a matrix transformation that place billboard in pos and aligne it with axis
		/*!
			@param pos translation billboard
			@param axis fixed axis of axial billboard
		*/
		void update_transform(const pVector& pos,const pVector& axis);

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/
		int get_custom_param_desc(int i,pParamDesc *pd);

		//! It is called after some parameter is changed.
		/*!
			@param i i-th parameter
		*/
		void on_pos_parameter_change(int i);
};

//! Render Object Projectile Class Descriptor
/*!
	It is a descriptor to pROProjectile classes and is used, mainly, in objects
	building process.
*/
class pROProjectile_desc : public pClassDesc
{
	public:
		//! Creates a new projectile object.
		/*! 
			@return a pointer to the new projectile object
		*/
		void *create()	const { return new pROProjectile; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "projectile"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_PROJECTILE; }
};

#endif

