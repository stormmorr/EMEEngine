/*! \file */

#ifndef PROTRAIL_H
#define PROTRAIL_H

//! Render Object Trail class
/*!
	This class implements an effect that represents a vapor trails emanating from
	a jet or a missile.
*/
class P3D_API pROTrail : public pRenderObject
{
	private:
		class pListData
		{
		public:
			pVector pos;
			pVector vel;
			pListData()
			{ }
			pListData(const pVector& p,const pVector& v)
			{ 
				pos=p;
				vel=v;
			}
			pListData(const pListData& in)
			{ 
				pos=in.pos;
				vel=in.vel;
			}
			void operator=(pListData& in)
			{
				pos=in.pos;
				vel=in.vel;
			}
		};

		float m_start_time;					//!< animation map start time
		int m_num_frames;					//!< number of frames of animation map
		pCircularList<pListData> m_path;	//!< array with trail points in global space
		float m_delay;						//!< delay of time between the generation of segments
		float m_totdt;

	public:
		int m_num_trail_points;			//!< total of trail points
		float m_width;					//!< the path width
		float m_threshold;				//!< maximum distance between two first trail points
		
		int m_blendadd;					//!< additive blending mode
		pVector m_color;				//!< the path color
		int m_texture;					//!< the texture applied to the path
		
		float m_tcmod_vel_s;			//!< velocity in s-direction (texture space)
		int m_tcmod_texture;			//!< texture for texture coordinates modifier
		
		float m_vel;
		float m_fade;					//!< the fade time for each path segment
		float m_duration;				//!< the duration of each path segment
		float m_frame_rate;				//!< frame rate of animation map

		//! Default constructor.
		pROTrail() :
			m_start_time(0.0f),
			m_num_frames(0),
			m_delay(0.025f),
			m_totdt(0.0f),
			m_num_trail_points(30),
			m_width(10.0f),
			m_threshold(1.0f),
			m_blendadd(0),
			m_color(1.0f),
			m_texture(-1),
			m_tcmod_vel_s(0.0f),
			m_tcmod_texture(-1),
			m_vel(0.0f),
			m_fade(0.2f),
			m_duration(1.0f),
			m_frame_rate(0.0f)
		{ m_type=TYPE_RO_TRAIL; }

		//! Destructor.
		virtual ~pROTrail() 
		{ }

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROTrail(const pROTrail& in) :
			pRenderObject(in),
			m_start_time(in.m_start_time),
			m_num_frames(in.m_num_frames),
			m_path(in.m_path),
			m_delay(in.m_delay),
			m_totdt(in.m_totdt),
			m_num_trail_points(in.m_num_trail_points),
			m_width(in.m_width),
			m_threshold(in.m_threshold),
			m_blendadd(in.m_blendadd),
			m_color(in.m_color),
			m_texture(in.m_texture),
			m_tcmod_vel_s(in.m_tcmod_vel_s),
			m_tcmod_texture(in.m_tcmod_texture),
			m_vel(in.m_vel),
			m_fade(in.m_fade),
			m_duration(in.m_duration),
			m_frame_rate(in.m_frame_rate)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject *clone() const
		{ return new pROTrail(*this); }

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

		//! Translates object world by given vector
		/*!
			This is a virtual method. The default implementation adds the given translation 
			to the object's transform matrix only if object is a active root and recurse down children.
			@param t translation to be applied to world
		*/
		void translate_world(const pVector& t);
};

//! Render Object Trail Class Descriptor
/*!
	It is a descriptor to pROTrail classes and is used, mainly, in objects
	building process.
*/
class pROTrail_desc : public pClassDesc
{
	public:
		//! Creates a new trail object.
		/*! 
			@return a pointer to the new trail object
		*/
		void *create() const { return new pROTrail; };

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "trail"; };

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_TRAIL; };
};

#endif
