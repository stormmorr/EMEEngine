/*! \file */

#ifndef PGUICHECKBOX_H
#define PGUICHECKBOX_H

class P3D_API pGUICheckBox : public pGUIObject
{
	private:
		int m_curr_icon;
		float m_u0,m_v0,m_u1,m_v1;
		
		void select_curr_icon();
		void calc_tex_coords();

	public:
		pVector m_text_color;

		int m_state; // 0: unchecked, 1: checked, 2: indeterminate
		int m_border_size;
		int m_text_spacing;

		int m_tex;
		
		int m_icon_unchecked;
		int m_icon_checked;
		int m_icon_indeterminate;
		pIconGridInfo m_icon_grid;

		//! Default/Initialization constructor.
		pGUICheckBox() :
			m_curr_icon(-1),
			m_u0(0.0f),m_v0(0.0f),m_u1(1.0f),m_v1(1.0f),
			m_text_color(0.0f),
			m_state(0),
			m_border_size(0),
			m_text_spacing(10),
			m_tex(-1),
			m_icon_unchecked(-1),
			m_icon_checked(-1),
			m_icon_indeterminate(-1)
		{ m_type=TYPE_GUI_CHECK_BOX; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUICheckBox(const pGUICheckBox& in) :
			pGUIObject(in),
			m_curr_icon(in.m_curr_icon),
			m_u0(in.m_u0),m_v0(in.m_v0),m_u1(in.m_u1),m_v1(in.m_v1),
			m_text_color(in.m_text_color),
			m_state(in.m_state),
			m_border_size(in.m_border_size),
			m_text_spacing(in.m_text_spacing),
			m_tex(in.m_tex),
			m_icon_unchecked(in.m_icon_unchecked),
			m_icon_checked(in.m_icon_checked),
			m_icon_indeterminate(in.m_icon_indeterminate),
			m_icon_grid(in.m_icon_grid)
		{ };

		virtual ~pGUICheckBox(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUICheckBox(*this); };

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

		void on_pos_parameter_change(int i);
};

//! GUI Button Object Class Descriptor
/*!
	It is a descriptor to the pGUICheckBox class and is used, mainly, in objects
	building process.
*/
class pGUICheckBox_desc : public pClassDesc
{
	public:
		//! Creates a new check box object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUICheckBox; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "check_box"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_CHECK_BOX; }
};

#endif
