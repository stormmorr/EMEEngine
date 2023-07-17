/*! \file */

#ifndef PROEXPLODEDOBJECT_H
#define PROEXPLODEDOBJECT_H

//! Render Object Explode Object class
/*!
	This class implements an object that can blow up.
*/
class P3D_API pROExplodeObject : public pRenderObject
{
	private:
		float m_opac;			//!< object's opacity
		bool m_restore;			//!< if true restore object's opacity

	public:
		float m_save_life;		//!< store life
		float m_life;			//!< life in seconds
		float m_fade_in;		//!< duration of fade in effect in seconds
		float m_fade_out;		//!< duration of fade out effect in seconds
		pVector m_lin_vel;		//!< constant linear velocity of object
		pVector m_ang_vel;		//!< constant angular velocity of object
		pRenderObject *m_obj;	//!< associated render object

		//! Default constructor.
		pROExplodeObject() :
			m_opac(1.0f),
			m_restore(true),
			m_save_life(0.0f),
			m_life(0.0f),
			m_fade_in(0.0f),
			m_fade_out(0.0f),
			m_lin_vel(0.0f,0.0f,0.0f),
			m_ang_vel(0.0f,0.0f,0.0f,0.0f),
			m_obj(0)
		{ 
			m_type=TYPE_RO_EXPLODE_OBJECT;
			m_flags|=P_ROFLAGS_CONTAINER;
		}

		//! Destructor.
		virtual ~pROExplodeObject();

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROExplodeObject(const pROExplodeObject& in) :
			pRenderObject(in),
			m_opac(in.m_opac),
			m_restore(in.m_restore),
			m_save_life(in.m_save_life),
			m_life(in.m_life),
			m_fade_in(in.m_fade_in),
			m_fade_out(in.m_fade_out),
			m_lin_vel(in.m_lin_vel),
			m_ang_vel(in.m_ang_vel),
			m_obj(in.m_obj)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROExplodeObject(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It selects a mesh accordingly to distance of the camera, updates the
			bounding boxe associated with this object and calls recursively step
			of all children.
			@param elapsed_time elapsed time in seconds
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

		//! It is called before/after some parameter is changed.
		/*!
			@param i i-th parameter
		*/
		void on_pre_parameter_change(int i);
		void on_pos_parameter_change(int i);

	private:
		int m_activeid;			//!< active object
		//! active objects in hash by id. It is used to process m_obj correctly.
		pHashTable<pRenderObject *> m_active;
		//! visible active objects list
		pArray<pRenderObject *> m_active_visible;
		//! transparent visible active objects list
		pArray<pRenderObject *> m_active_visible_transp;
		//! transparent visible active objects list
		pArray<pRenderObject *> m_active_visible_mesh;

		//! Activates a given stock object.
		/*!
			It is used to process m_obj correctly.
			Activates a given stock object and return the handle for the activated copy.
			@param stockobj stock object's pointer
			@return a handle to the activated object
		*/
		unsigned int activate(pRenderObject *stockobj);

		//! Deactivates a given active object.
		/*!
			It is used to process m_obj correctly.
			Deactivates a given active object (removing it from simulation).
			@param activeobj active object's handle
		*/
		void deactivate(unsigned int activeobj);

		//! Restore the opacity values of all changed mesh belongs to m_obj.
		/*!
			It is used to process m_obj correctly.
		*/
		void restore_opacity();

		//! Draw an array of pRenderObject's.
		void draw(pArray<pRenderObject *>& objects);
};

//! Render Object Explode Object Class Descriptor
/*!
	It is a descriptor to pROExplodeObject classes and is used, mainly, in objects
	building process.
*/
class pROExplodeObject_desc : public pClassDesc
{
	public:
		//! Creates a new explode object.
		/*! 
			@return a pointer to the new explode object
		*/
		void *create()	const { return new pROExplodeObject; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "explode_object"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_EXPLODE_OBJECT; }
};

#endif

