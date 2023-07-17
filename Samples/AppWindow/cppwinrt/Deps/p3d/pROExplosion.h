/*! \file */

#ifndef PROEXPLOSION_H
#define PROEXPLOSION_H

//! Render Object Explosion class
/*!
	This class implements an explosion effect.
*/
class P3D_API pROExplosion : public pRenderObject
{
	public:
		float m_angle_x;
		float m_angle_y;

		float m_speed;
		float m_speed_var;
		float m_ang_speed;
		float m_ang_speed_var;

		float m_delay;

		pVector m_explode_pos;

		//! Default constructor.
		pROExplosion() :
			m_angle_x(10.0f),
			m_angle_y(10.0f),
			m_speed(10.0f),
			m_speed_var(1.0f),
			m_ang_speed(1.0f),
			m_ang_speed_var(0.2f),
			m_explode_pos(0),
			m_delay(0)
		{ m_type=TYPE_RO_EXPLOSION; }

		//! Destructor.
		virtual ~pROExplosion()
		{ }

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROExplosion(const pROExplosion& in) :
			pRenderObject(in),
			m_angle_x(in.m_angle_x),
			m_angle_y(in.m_angle_y),
			m_speed(in.m_speed),
			m_speed_var(in.m_speed_var),
			m_ang_speed(in.m_ang_speed),
			m_ang_speed_var(in.m_ang_speed_var),
			m_explode_pos(in.m_explode_pos),
			m_delay(in.m_delay)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROExplosion(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active)
		{ active = true; }

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It selects a mesh accordingly to distance of the camera, updates the
			bounding boxe associated with this object and calls recursively step
			of all children.
			@param elapsed_time elapsed time in seconds
			@param global global transformation that will transform this objects and its children
		*/
		void step(const float elapsed_time,const pMatrix& global);

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/
		int get_custom_param_desc(int i,pParamDesc *pd);

	protected:
		//! Performs an explosion, sending the children flying away.
		void explode();
};

//! Render Object Explosion Class Descriptor
/*!
	It is a descriptor to pROExplosion classes and is used, mainly, in object
	building processes.
*/
class pROExplosion_desc : public pClassDesc
{
	public:
		//! Creates a new mesh LOD object.
		/*! 
			@return a pointer to the new mesh LOD object
		*/
		void *create()	const { return new pROExplosion; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "explosion"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_EXPLOSION; }
};

#endif
