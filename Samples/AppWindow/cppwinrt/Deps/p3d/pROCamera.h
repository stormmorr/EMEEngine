/*! \file */

#ifndef PROCAMERA_H
#define PROCAMERA_H

//!  Render Object Camera class
/*!
	This class implements a third person target camera.
*/
class P3D_API pROCamera : public pRenderObject
{
	public:
		float m_radius;
		float m_fov;
		pVector m_target_trans;
		float m_dist;
		float m_angle_x;
		float m_angle_y;
		float m_follow_speed;

		//! Default constructor.
		pROCamera() :
			m_radius(5),
			m_fov(60.0f),
			m_target_trans(0),
			m_dist(100),
			m_angle_x(0),
			m_angle_y(0),
			m_follow_speed(0.5f)
		{ m_type=TYPE_RO_CAMERA; }

		//! Destructor.
		virtual ~pROCamera()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROCamera(const pROCamera& in) :
			pRenderObject(in),
			m_radius(in.m_radius),
			m_fov(in.m_fov),
			m_target_trans(in.m_target_trans),
			m_dist(in.m_dist),
			m_angle_x(in.m_angle_x),
			m_angle_y(in.m_angle_y),
			m_follow_speed(in.m_follow_speed)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROCamera(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active)
		{ active = true; }

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It updates the bounding box associated with this object and calls
			the recursive step of all children.
			@param elapsed_time elapsed time in milli seconds
			@param global global transformation that will transform this objects and its children
		*/
		void step(const float elapsed_time,const pMatrix& global);

		//! Draws this object.
		void draw();

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/
		int get_custom_param_desc(int i,pParamDesc *pd);

		//! Called after some parameter is changed.
		/*!
			Called after an event of parameter changing occurs.
			@param i i-th parameter
		*/
		void on_pos_parameter_change(int i);

		void set_render_camera();
		void set_target(pRenderObject *o);
};

//! Render Object Camera Class Descriptor
/*!
	It is a descriptor to pROCamera classes and is used, mainly, in objects
	building process.
*/
class pROCamera_desc : public pClassDesc
{
	public:
		//! Creates a new camera object.
		/*! 
			@return a pointer to the new camera object
		*/
		void *create()	const { return new pROCamera; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "camera"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_CAMERA; }
};


#endif
