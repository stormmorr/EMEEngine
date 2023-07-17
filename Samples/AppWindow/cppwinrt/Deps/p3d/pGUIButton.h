/*! \file */

#ifndef PGUIBUTTON_H
#define PGUIBUTTON_H

class P3D_API pGUIButton : public pGUIObject
{
	private:
		int m_curr_icon;
		float m_u0,m_v0,m_u1,m_v1;

		// attributes for animation map in background texture
		float m_start_time;	//!< animation map start time
		int m_num_frames;	//!< number of frames of animation map

		//! Update the number of frames.
		void update_num_frames();
		
		void select_curr_icon();
		void calc_tex_coords();

	public:
		int m_state;
		int m_icon_disabled;
		int m_icon_enabled;
		int m_icon_hover;
		int m_icon_pressed;
		pIconGridInfo m_icon_grid;

		int m_text_align;
		int m_text_border_size;
		pVector m_text_color;

		int m_icon2_align;
		int m_icon2_tex;

		int m_default;
		int m_cancel;

		// attributes for animation map in background texture
		enum
		{
			CMD_PLAY=0,
			CMD_PLAY_ONCE,
			CMD_PAUSE,
			CMD_STOP,
		};
		int m_background_tex;	//!< background texture
		int m_command;			//!< 0 - Play, 1 - Play once, 2 - Pause, 3 - Stop
		int m_current_frame;	//!< current frame
		float m_frame_rate;		//!< frame rate of animation map
		
		//! Default/Initialization constructor.
		pGUIButton() :
			m_curr_icon(-1),
			m_u0(0.0f),m_v0(0.0f),m_u1(1.0f),m_v1(1.0f),
			m_state(1),
			m_icon_disabled(-1),
			m_icon_enabled(-1),
			m_icon_hover(-1),
			m_icon_pressed(-1),
			m_text_align(0),
			m_text_border_size(2),
			m_text_color(0.0f),
			m_icon2_align(0),
			m_icon2_tex(-1),
			m_default(0),
			m_cancel(0),
			// attributes for animation map in background texture
			m_background_tex(-1),
			m_start_time(0.0f),
			m_num_frames(1),
			m_command(CMD_STOP),
			m_current_frame(0),
			m_frame_rate(0.0f)
		{ m_type=TYPE_GUI_BUTTON; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUIButton(const pGUIButton& in) :
			pGUIObject(in),
			m_curr_icon(in.m_curr_icon),
			m_u0(in.m_u0),m_v0(in.m_v0),m_u1(in.m_u1),m_v1(in.m_v1),
			m_state(in.m_state),
			m_icon_disabled(in.m_icon_disabled),
			m_icon_enabled(in.m_icon_enabled),
			m_icon_hover(in.m_icon_hover),
			m_icon_pressed(in.m_icon_pressed),
			m_icon_grid(in.m_icon_grid),
			m_text_align(in.m_text_align),
			m_text_border_size(in.m_text_border_size),
			m_text_color(in.m_text_color),
			m_icon2_align(in.m_icon2_align),
			m_icon2_tex(in.m_icon2_tex),
			m_default(in.m_default),
			m_cancel(in.m_cancel),
			// attributes for animation map in background texture
			m_background_tex(in.m_background_tex),
			m_start_time(in.m_start_time),
			m_num_frames(in.m_num_frames),
			m_command(in.m_command),
			m_current_frame(in.m_current_frame),
			m_frame_rate(in.m_frame_rate)
		{ };

		virtual ~pGUIButton(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIButton(*this); };

		void init();

		//! Draws this object.
		/*!
			@param scissor_rect rect used in OpenGL scissor test
		*/
		void draw(pRect& scissor_rect);

		void process_mouse_input(pGUIEventHandler *event_handler);

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, the method only returns the number of parameters.
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

		void on_kill_mouse();
};

//! GUI Button Object Class Descriptor
/*!
	It is a descriptor to the pGUIButton class and is used, mainly, in objects
	building process.
*/
class pGUIButton_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIButton; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "button"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_BUTTON; }
};

#endif
