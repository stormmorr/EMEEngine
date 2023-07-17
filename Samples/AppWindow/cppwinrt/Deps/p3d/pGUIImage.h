/*! \file */

#ifndef PGUIIMAGE_H
#define PGUIIMAGE_H

class P3D_API pGUIImage : public pGUIObject
{
	private:
		// attributes for animation map in background texture
		float m_start_time;	//!< animation map start time
		int m_num_frames;	//!< number of frames of animation map

		//! Update the number of frames.
		void update_num_frames();

	public:
		int m_rescale_tex_flag;
		int	m_tex;
		
		int m_addblend;
		pPeriodicFunc m_color_func;
		pPeriodicFunc m_transp_func;

		// attributes for animation map in background texture
		enum
		{
			CMD_PLAY=0,
			CMD_PLAY_ONCE,
			CMD_PAUSE,
			CMD_STOP,
		};
		int m_command;			//!< 0 - Play, 1 - Play once, 2 - Pause, 3 - Stop
		int m_current_frame;	//!< current frame
		float m_frame_rate;		//!< frame rate of animation map
		
		// attributes for stretch and rotate in background texture
		float m_rotation_vel;				//!< degrees per second
		pPeriodicFunc m_vert_stretch_func;	//!< vertical stretch function
		pPeriodicFunc m_horz_stretch_func;	//!< horizontal stretch function

		pGUIImage() :
			m_rescale_tex_flag(1),
			m_tex(-1),
			// attributes for animation map in background texture
			m_start_time(0.0f),
			m_num_frames(1),
			m_command(CMD_STOP),
			m_current_frame(0),
			m_frame_rate(0.0f),
			// attributes for stretch and rotate in background texture
			m_rotation_vel(0.0f),
			m_addblend(0)
		{
			m_type=TYPE_GUI_IMAGE;
		};

		pGUIImage(const pGUIImage& in) :
			pGUIObject(in),
			m_rescale_tex_flag(in.m_rescale_tex_flag),
			m_tex(in.m_tex),
			// attributes for animation map in background texture
			m_start_time(in.m_start_time),
			m_num_frames(in.m_num_frames),
			m_command(in.m_command),
			m_current_frame(in.m_current_frame),
			m_frame_rate(in.m_frame_rate),
			// attributes for stretch and rotate in background texture
			m_rotation_vel(in.m_rotation_vel),
			m_vert_stretch_func(in.m_vert_stretch_func),
			m_horz_stretch_func(in.m_horz_stretch_func),
			m_addblend(in.m_addblend),
			m_color_func(in.m_color_func),
			m_transp_func(in.m_transp_func)
		{ };

		virtual ~pGUIImage(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIImage(*this); };

		//! Initialize the object.
		/*!
			This is a virtual method. The default implementation do nothing.
			On creation, this function is called.
		*/
		void init();

		//! Draws this object.
		/*!
			@param scissor_rect rect used in OpenGL scissor test
		*/
		void draw(pRect& scissor_rect);

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, the method only returns the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/ 
		int get_custom_param_desc(int i,pParamDesc *pd);

		//! It is called before/after some parameter is changed.
		/*!
			This is a virtual method. The default implementation do nothing.
			@param i i-th parameter
		*/
		void on_pos_parameter_change(int i);
};

//! GUI Image Object Class Descriptor
/*!
	It is a descriptor to the pGUIImage class and is used, mainly, in objects
	building process.
*/
class pGUIImage_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIImage; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "image"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_IMAGE; }
};

#endif
