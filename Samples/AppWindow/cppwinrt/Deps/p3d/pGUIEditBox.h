	/*! \file */

#ifndef PGUIEDITBOX_H
#define PGUIEDITBOX_H

#include "paralelo3d.h"

class P3D_API pGUIEditBox : public pGUIObject
{
	public:
		int				m_text_align;
		pVector			m_text_color;
		int				m_text_border_size;
		int				m_tex;
		pVector			m_cursor_color1;
		pVector			m_cursor_color2;
		pPeriodicFunc	m_cursor_blink_func;
		int				m_max_chars;
		int				m_masked;
		pString			m_valid_chars;
		pVector			m_sel_bg_color;
		pVector			m_sel_text_color;

		int				m_caret_pos;
		int				m_sel_start;
		int				m_sel_end;

		pGUIEditBox() :
			m_text_align(0),
			m_text_color(0.0f),
			m_text_border_size(0),
			m_tex(-1),
			m_cursor_color1(0.0f),
			m_cursor_color2(0.0f),
			m_max_chars(16),
			m_masked(0),
			m_sel_bg_color(0.0f),
			m_sel_text_color(1.0f),
			m_caret_pos(0),
			m_sel_start(0),
			m_sel_end(0)
		{
			m_type=TYPE_GUI_EDIT_BOX;
			m_cursor_blink_func.m_type=P_PERIODICFUNC_TRIANGLE;
		};

		pGUIEditBox(const pGUIEditBox& in) :
			pGUIObject(in),
			m_text_align(in.m_text_align),
			m_text_color(in.m_text_color),
			m_text_border_size(in.m_text_border_size),
			m_tex(in.m_tex),
			m_cursor_color1(in.m_cursor_color1),
			m_cursor_color2(in.m_cursor_color2),
			m_cursor_blink_func(in.m_cursor_blink_func),
			m_max_chars(in.m_max_chars),
			m_masked(in.m_masked),
			m_valid_chars(in.m_valid_chars),
			m_sel_bg_color(in.m_sel_bg_color),
			m_sel_text_color(in.m_sel_text_color),
			m_caret_pos(in.m_caret_pos),
			m_sel_start(in.m_sel_start),
			m_sel_end(in.m_sel_end)
		{ };

		virtual ~pGUIEditBox(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIEditBox(*this); };

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

		void process_mouse_input(pGUIEventHandler *event_handler);
		void process_keyboard_input(int keycode,int mod,unsigned char ch);

		void on_get_focus();
};

//! GUI Edit Box Object Class Descriptor
/*!
	It is a descriptor to the pGUIEditBox class and is used, mainly, in objects
	building process.
*/
class pGUIEditBox_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIEditBox; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "edit_box"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_EDIT_BOX; }
};

#endif

