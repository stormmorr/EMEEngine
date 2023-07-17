/*! \file */

#ifndef PROGROUP_H
#define PROGROUP_H

//! Render Object Group class
/*!
	This class implements a container to render objects. It is used to group
	objects, e.g, a pROMesh that represents a ship's engine with a pROTrail that
	represents the trail created by the ship's engine.
*/
class P3D_API pROGroup : public pRenderObject
{
	public:

		enum
		{
			CMD_PLAY=0,
			CMD_PAUSE,
			CMD_STOP
		};
		int m_command;				//!< it can be CMD_PLAY, CMD_PAUSE or CMD_STOP
		int m_curr_anim;			//!< current animation
		pMesh *m_animations;		//!< stores an animation to this object
		pVector m_anim_rot;			//!< animation rotation
		float m_time;				//!< start time (in seconds)
		float m_time_to_die;		//!< time to die (0 for keep alive)

		//! Default constructor.
		pROGroup() :
			m_time(0.0f),
			m_command(CMD_STOP),
			m_curr_anim(-1),
			m_animations(0),
			m_anim_rot(0),
			m_time_to_die(0)
		{ m_type=TYPE_RO_GROUP; }

		//! Destructor.
		virtual ~pROGroup()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROGroup(const pROGroup& in) :
			pRenderObject(in),
			m_time(in.m_time),
			m_command(in.m_command),
			m_curr_anim(in.m_curr_anim),
			m_animations(in.m_animations),
			m_anim_rot(in.m_anim_rot),
			m_time_to_die(in.m_time_to_die)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROGroup(*this); }

		//! Initializes the state of this object.
		/*!
			Calculates a bounding boxe to this group.
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It calls recursively the step of all children.
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
};

//! Render Object Group Class Descriptor
/*!
	It is a descriptor to pROGroup classes and is used, mainly, in objects
	building process.
*/
class pROGroup_desc : public pClassDesc
{
	public:
		//! Creates a new group object.
		/*! 
			@return a pointer to the new group object
		*/
		void *create() const { return new pROGroup; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "group"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_GROUP; }
};

#endif
