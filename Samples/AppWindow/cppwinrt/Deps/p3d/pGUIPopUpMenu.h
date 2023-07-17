/*! \file */

#ifndef PGUIPOPUPMENU_H
#define PGUIPOPUPMENU_H

class pGUIPopUpMenuItem
{
	public:
		pString m_text;
		int m_cookie;
		int m_state;
		int m_separator;

		pGUIPopUpMenuItem() :
			m_cookie(-1),
			m_state(0),
			m_separator(0)
		{
		};

		pGUIPopUpMenuItem(const pGUIPopUpMenuItem &in) :
			m_cookie(in.m_cookie),
			m_state(in.m_state),
			m_separator(in.m_separator)
		{
			m_text=in.m_text;
		};

		void operator=(const pGUIPopUpMenuItem &in)
		{
			m_cookie=in.m_cookie;
			m_state=in.m_state;
			m_separator=in.m_separator;
			m_text=in.m_text;
		}
};

class P3D_API pGUIPopUpMenu : public pGUIObject
{
	public:
		int m_item_height;
		int m_item_separator_height;

		pIconGridInfo m_item_icon_grid;
		int m_item_icon_disabled;
		int m_item_icon_normal;
		int m_item_icon_hover;
		int m_item_icon_pressed;

		pVector m_item_textcolor_disabled;
		pVector m_item_textcolor_normal;
		pVector m_item_textcolor_hover;
		pVector m_item_textcolor_pressed;

		int m_item_text_align; //0: left, 1: right, 2: center

		int m_item_border;

		int m_item_separator_tex;

		pArray<pGUIPopUpMenuItem> m_items;
		int m_nitems;

		unsigned int m_caller_id;
		pGUIEventHandler *m_caller_event_handler;
		
		//! Default/Initialization constructor.
		pGUIPopUpMenu() :
			m_item_height(20),
			m_item_separator_height(5),
			m_item_icon_disabled(-1),
			m_item_icon_normal(-1),
			m_item_icon_hover(-1),
			m_item_icon_pressed(-1),
			m_item_textcolor_disabled(0.5f),
			m_item_textcolor_normal(1.0f),
			m_item_textcolor_hover(0.0f),
			m_item_textcolor_pressed(0.5f),
			m_item_text_align(0),
			m_item_border(0),
			m_item_separator_tex(-1),
			m_nitems(0),
			m_caller_id(0),
			m_caller_event_handler(0)
		{ m_type=TYPE_GUI_POP_UP_MENU; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUIPopUpMenu(const pGUIPopUpMenu& in) :
			pGUIObject(in),
			m_item_height(in.m_item_height),
			m_item_separator_height(in.m_item_separator_height),
			m_item_icon_grid(in.m_item_icon_grid),
			m_item_icon_disabled(in.m_item_icon_disabled),
			m_item_icon_normal(in.m_item_icon_normal),
			m_item_icon_hover(in.m_item_icon_hover),
			m_item_icon_pressed(in.m_item_icon_pressed),
			m_item_textcolor_disabled(in.m_item_textcolor_disabled),
			m_item_textcolor_normal(in.m_item_textcolor_normal),
			m_item_textcolor_hover(in.m_item_textcolor_hover),
			m_item_textcolor_pressed(in.m_item_textcolor_pressed),
			m_item_text_align(in.m_item_text_align),
			m_item_border(in.m_item_border),
			m_item_separator_tex(in.m_item_separator_tex),
			m_nitems(in.m_nitems),
			m_caller_id(in.m_caller_id),
			m_caller_event_handler(in.m_caller_event_handler)
		{ 
			m_items.clear();
			for(int i=0;i<in.m_items.num;i++)
				m_items.add(in.m_items[i]);
		};

		virtual ~pGUIPopUpMenu()
		{
		};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIPopUpMenu(*this); };

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
		void on_kill_focus();

		void set_position_from_mouse();
		void set_context_object(const unsigned int id);
		
		void add_item(const pString &text,const int cookie,const int state);
		void add_separator();
		void remove_item(const int ind);
		void get_item_text(const int ind, pString &text);
		int get_item_cookie(const int ind);
		int get_item_state(const int ind);
		int get_item_separator(const int ind);
		void set_item_text(const int ind, const pString &text);
		void set_item_cookie(const int ind, const int cookie);
		void set_item_state(const int ind, const int state);
		void set_item_separator(const int ind, const int separator);
};

//! GUI Pop Up Menu Object Class Descriptor
/*!
	It is a descriptor to the pGUIPopUpMenu class and is used, mainly, in objects
	building process.
*/
class pGUIPopUpMenu_desc : public pClassDesc
{
	public:
		//! Creates a new pGUIPopUpMenu object.
		/*! 
			@return a pointer to the new pGUIPopUpMenu object
		*/
		void *create()	const { return new pGUIPopUpMenu; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "pop_up_menu"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_POP_UP_MENU; }
};

#endif