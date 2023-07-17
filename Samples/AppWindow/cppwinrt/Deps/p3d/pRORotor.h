/*! \file */

#ifndef PROROTOR_H
#define PROROTOR_H

//! Render Object Rotor class
/*!
	This class has engine behavior, i.e, an object that applies to all children
	a kind of animation. Specifically, this object applies a rotation with
	controlled by an angular velocity.
*/
class P3D_API pRORotor : public pRenderObject
{
	private:
		float m_angle;			//!< current calculated angle
		pMatrix m_mat_rot;		//!< internal matrix to calculus
		float m_calc_scale;		//!< scale factor (to support huge mesh)

	public:
		pVector m_angular_vel;	//!< (x,y,z) - rotation axis / w - angle in degrees

		//! Default constructor.
		pRORotor() :
			m_angle(0.0f),
			m_angular_vel(0.0f,0.0f,1.0f,0.0f)
		{ m_type=TYPE_RO_ROTOR; }

		//! Destructor.
		virtual ~pRORotor()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pRORotor(const pRORotor& in) :
			pRenderObject(in),
			m_angle(in.m_angle),
			m_angular_vel(in.m_angular_vel)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pRORotor(*this); }

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

//! Render Object Rotor Class Descriptor
/*!
	It is a descriptor to pRORotor classes and is used, mainly, in objects
	building process.
*/
class pRORotor_desc : public pClassDesc
{
	public:
		//! Creates a new rotor object.
		/*! 
			@return a pointer to the new rotor object
		*/
		void *create()	const { return new pRORotor; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "rotor"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_ROTOR; }
};

#endif
