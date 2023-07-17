/*! \file */

#ifndef PGUIWINDOW_H
#define PGUIWINDOW_H

class P3D_API pGUIWindow : public pGUIObject
{
	private:
		// attributes for animation map in background texture
		float m_start_time;	//!< animation map start time
		int m_num_frames;	//!< number of frames of animation map

		//! Update the number of frames.
		void update_num_frames();

	public:
		int		m_text_align;
		pVector	m_text_color;
		int		m_text_border_size;

		int		m_title_height;
		pVector	m_title_bg_color;
		int		m_title_border_size;

		int		m_tex_title_start;
		int		m_tex_title_mid;
		int		m_tex_title_end;
		int		m_tex_close;
		int		m_tex_bg;
		int		m_tex_stretch;

		int		m_close_button_align;

		int				m_glow_tex;
		pVector			m_glow_color0,m_glow_color1;
		pPeriodicFunc	m_glow_func;
		
		float m_scroll_y;
		int m_scroll_bar_width;
		int m_scroll_tex_button;
		int m_scroll_tex_bg;
		int m_scroll_tex_bar;
		pVector m_scroll_button_color;
		pVector m_scroll_bg_color;
		pVector m_scroll_bar_color;
		int m_scroll_unit;
		float m_scroll_speed;
		float m_scroll_timeout;
		int m_scroll_bar_drag;

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

		//! Default/Initialization constructor.
		pGUIWindow() :
			m_text_align(0),
			m_text_color(0.0f),
			m_text_border_size(0),
			m_title_height(0),
			m_title_bg_color(1.0f),
			m_title_border_size(0),
			m_tex_title_start(-1),
			m_tex_title_mid(-1),
			m_tex_title_end(-1),
			m_tex_close(-1),
			m_tex_bg(-1),
			m_tex_stretch(1),
			m_close_button_align(1),
			m_glow_tex(-1),
			m_glow_color0(0.0f),
			m_glow_color1(1.0f),
			m_scroll_y(0.0f),m_scroll_bar_width(5),m_scroll_tex_button(-1),m_scroll_tex_bg(-1),
			m_scroll_tex_bar(-1),m_scroll_button_color(1.0f),m_scroll_unit(5),m_scroll_speed(1.0f),
			m_scroll_timeout(0.5f),m_scroll_bg_color(0.0f),m_scroll_bar_color(1.0f),m_scroll_bar_drag(0),
			// attributes for animation map in background texture
			m_start_time(0.0f),
			m_num_frames(1),
			m_command(CMD_STOP),
			m_current_frame(0),
			m_frame_rate(0.0f),
			// attributes for stretch and rotate in background texture
			m_rotation_vel(0.0f)
		{ m_type=TYPE_GUI_WINDOW; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUIWindow(const pGUIWindow& in) :
			pGUIObject(in),
			m_text_align(in.m_text_align),
			m_text_color(in.m_text_color),
			m_text_border_size(in.m_text_border_size),
			m_title_height(in.m_title_height),
			m_title_bg_color(in.m_title_bg_color),
			m_title_border_size(in.m_title_border_size),
			m_tex_title_start(in.m_tex_title_start),
			m_tex_title_mid(in.m_tex_title_mid),
			m_tex_title_end(in.m_tex_title_end),
			m_tex_close(in.m_tex_close),
			m_tex_bg(in.m_tex_bg),
			m_tex_stretch(in.m_tex_stretch),
			m_close_button_align(in.m_close_button_align),
			m_glow_tex(in.m_glow_tex),
			m_glow_color0(in.m_glow_color0),
			m_glow_color1(in.m_glow_color1),
			m_glow_func(in.m_glow_func),
			m_scroll_bar_width(in.m_scroll_bar_width),m_scroll_y(in.m_scroll_y),m_scroll_tex_button(in.m_scroll_tex_button),
			m_scroll_tex_bg(in.m_scroll_tex_bg),m_scroll_tex_bar(in.m_scroll_tex_bar),m_scroll_button_color(in.m_scroll_button_color),
			m_scroll_bg_color(in.m_scroll_bg_color),m_scroll_bar_color(in.m_scroll_bar_color),m_scroll_unit(in.m_scroll_unit),
			m_scroll_speed(in.m_scroll_speed),m_scroll_timeout(in.m_scroll_timeout),m_scroll_bar_drag(in.m_scroll_bar_drag),
			// attributes for animation map in background texture
			m_start_time(in.m_start_time),
			m_num_frames(in.m_num_frames),
			m_command(in.m_command),
			m_current_frame(in.m_current_frame),
			m_frame_rate(in.m_frame_rate),
			// attributes for stretch and rotate in background texture
			m_rotation_vel(in.m_rotation_vel),
			m_vert_stretch_func(in.m_vert_stretch_func),
			m_horz_stretch_func(in.m_horz_stretch_func)
		{ };

		virtual ~pGUIWindow(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIWindow(*this); };

		//! Initialize the object.
		/*!
			This is a virtual method. The default implementation do nothing.
			On creation, this function is called.
		*/
		void init();

		void step(const float elapsed_time,const int& global_x,const int& global_y);

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

		int get_content_height();
		void process_mouse_input(pGUIEventHandler *event_handler);

		void on_begin_drag();
		void on_end_drag();

		void draw_scroll_bar(pRect& scissor_rect);
};

//! GUI Window Object Class Descriptor
/*!
	It is a descriptor to the pGUIWindow class and is used, mainly, in objects
	building process.
*/
class pGUIWindow_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIWindow; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "window"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_WINDOW; }
};

#endif

