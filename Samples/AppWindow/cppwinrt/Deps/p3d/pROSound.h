/*! \file */

#ifndef PROSOUND_H
#define PROSOUND_H

//! Render Object Sound class
/*!
*/
class P3D_API pROSound : public pRenderObject
{
	private:
	   
		void process_sound();

	public:

		enum
		{
			CMD_PLAY=0,
			CMD_PLAY_ONCE,
			CMD_PAUSE,
			CMD_STOP
		};
		int m_cur_sound;
		int m_command;			//!< CMD_PLAY, CMD_PLAY_ONCE, CMD_PAUSE or CMD_STOP 
		int m_directional;
		int m_global;
		int m_die;
		int m_velocity;
		ALuint m_source_sound;
		float m_reference_dist;
		float m_gain;
		float m_pitch;
		float m_pitch_min_range;
		float m_pitch_max_range;
		float m_cone_inner_angle;
		pArray<int> m_sounds;

		//! Default constructor.
		pROSound() :
			m_cur_sound(0),
			m_command(CMD_STOP),
			m_directional(0),
			m_global(0),
			m_die(0),
			m_velocity(0),
			m_reference_dist(1.0f),
			m_gain(1.0f),
			m_pitch(1.0f),
			m_pitch_min_range(0.1f),
			m_pitch_max_range(1.0f),
			m_cone_inner_angle(360.0f)
		{ m_type=TYPE_RO_SOUND; }

		//! Destructor.
		~pROSound();
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROSound(const pROSound& in) :
			pRenderObject(in),
			m_cur_sound(in.m_cur_sound),
			m_command(in.m_command),
			m_sounds(in.m_sounds),
			m_directional(in.m_directional),
			m_global(in.m_global),
			m_die(in.m_die),
			m_velocity(in.m_velocity),
			m_reference_dist(in.m_reference_dist),
			m_gain(in.m_gain),
			m_pitch(in.m_pitch),
			m_pitch_min_range(in.m_pitch_min_range),
			m_pitch_max_range(in.m_pitch_max_range),
			m_cone_inner_angle(in.m_cone_inner_angle)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROSound(*this); }

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

		//! It is called after some parameter is changed.
		/*!
			@param i i-th parameter
		*/
		void on_pos_parameter_change(int i);

		float get_pitch() const
		{ return (m_pitch_max_range-m_pitch_min_range)*m_pitch+m_pitch_min_range; }

		bool is_valid() const
		{ return m_source && 0<=m_cur_sound && m_cur_sound<m_sounds.num && m_sounds[m_cur_sound]<g_soundmanager->m_soundid.num; }
};

//! Render Object Sound Class Descriptor
/*!
	It is a descriptor to pROSound classes and is used, mainly, in objects
	building process.
*/
class pROSound_desc : public pClassDesc
{
	public:
		//! Creates a new group object.
		/*! 
			@return a pointer to the new group object
		*/
		void *create() const { return new pROSound; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "sound"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_SOUND; }
};

#endif
