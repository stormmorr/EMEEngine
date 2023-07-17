/*! \file */

#ifndef PROBILBOARD_H
#define PROBILBOARD_H

//! Render Object Billboard class
/*!
	This class implements the billboarding technique. A billboard is an object
	that always faces toward the eye. There is two kinds of	billboards: view
	aligned and axis aligned. A view aligned billboard is always aligned with
	the screen. A axis aligned billboard is always aligned with a given axis.
*/
class P3D_API pROBillboard : public pRenderObject
{
	private:

		float m_cursize_x;				//!< width of support plane
		float m_cursize_y;				//!< height of support plane

		float m_si,m_sf;				//!< texture coordinates for anim map
		float m_start_time;				//!< animation map start time
		int m_num_frames;				//!< number of frames of animation map
		bool m_deactivate;				//!< deactivate on next frame

	public:

		enum
		{
			NONE_ALIGNED=0,
			AXIS_ALIGNED,
			VIEW_ALIGNED
		};
		int m_alignment;				//!< alignment (0:none,1:axis,2:view)
		int m_blendadd;					//!< additive blend mode?
		int m_alphatest;				//!< consider alpha test?

		float m_size_x;					//!< width of support plane
		float m_size_y;					//!< height of support plane
		pPeriodicFunc m_size_func;		//!< function that animates the size over time

		int m_texture;					//!< texture id
		pVector m_color;				//!< initial color of billboard
		pVector m_colorf;				//!< final color of billboard
		pPeriodicFunc m_color_func;		//!< function to change color
		pPeriodicFunc m_transp_func;	//!< function to change transparency

		int m_loop;						//!< die after last frame if not on loop
		float m_frame_rate;				//!< frame rate of animation map

	public:

		//! Default constructor.
		pROBillboard() :
			m_alignment(VIEW_ALIGNED),
			m_blendadd(0),
			m_alphatest(0),
			m_size_x(10.0f),
			m_size_y(10.0f),
			m_texture(-1),
			m_color(1.0f),
			m_colorf(1.0f),
			m_loop(1),
			m_si(0.0f),m_sf(1.0f),
			m_num_frames(0),
			m_start_time(0.0f),
			m_frame_rate(0.0f),
			m_deactivate(false)
		{ m_type=TYPE_RO_BILLBOARD; }

		//! Destructor.
		virtual ~pROBillboard()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROBillboard(const pROBillboard& in) :
			pRenderObject(in),
			m_alignment(in.m_alignment),
			m_blendadd(in.m_blendadd),
			m_alphatest(in.m_alphatest),
			m_size_x(in.m_size_x),
			m_size_y(in.m_size_y),
			m_size_func(in.m_size_func),
			m_texture(in.m_texture),
			m_color(in.m_color),
			m_colorf(in.m_colorf),
			m_color_func(in.m_color_func),
			m_transp_func(in.m_transp_func),
			m_loop(in.m_loop),
			m_si(in.m_si),m_sf(in.m_sf),
			m_num_frames(in.m_num_frames),
			m_start_time(in.m_start_time),
			m_frame_rate(in.m_frame_rate),
			m_deactivate(in.m_deactivate)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROBillboard(*this); }

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
};

//! Render Object Billboard Class Descriptor
/*!
	It is a descriptor to pROBillboard classes and is used, mainly, in objects
	building process.
*/
class pROBillboard_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new billboard object
		*/
		void *create()	const { return new pROBillboard; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "billboard"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_BILLBOARD; }
};

#endif

