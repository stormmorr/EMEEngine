/*! \file */

#ifndef PGUIOBJECT_H
#define PGUIOBJECT_H

class P3D_API pGUIEventHandler
{
	public:
		virtual int event_handler(unsigned int msg,unsigned int obj,int iparam,void *pparam)=0;
};

//! Graphic User Interface Window class
/*!
	This class implements a base class to graphic user interface objects.		
*/
class P3D_API pGUIObject
{
	friend class pGUIObjectManager;

	public:

		unsigned int m_type;  //!< object class type
		unsigned int m_id;    //!< object unique id
		unsigned int m_flags; //!< bit flags

		int m_clickable;
		int m_focusable;
		int m_modal;
		int m_popup;
		int m_draggable;
		int m_droppable;

		int m_pos_x,	//!< position in screen coordinates
			m_pos_y;	//!< position in screen coordinates
		int m_global_x,	//!< position in screen coordinates
			m_global_y;	//!< position in screen coordinates
		int m_width,	//!< width in screen coordinates
			m_height;	//!< height in screen coordinates
		int m_hotspot_x,//!< hotspot position in screen coordinates
			m_hotspot_y;//!< hotspot position in screen coordinates

		int m_content_height;
		pString m_name; //!< object name
		pString m_text; //!< object text

		pGUIObject *m_parent; //!< pointer to parent object

		pArray<pGUIObject *> m_child; //!< array of children objects

		pVector m_color;	//!< object color
	
		int m_font;			//!< object font file
		int m_font_size;	//!< object font size

		int m_mouse_cursor;	//!< mouse cursor for this object
		int m_mouse_cursor_can_drop; //!< mouse cursor for this object when m_droppable==true
		int m_mouse_cursor_cannot_drop; //!< mouse cursor for this object when m_droppable==false

		pString m_tooltip;
		int m_tooltip_flag;
		int m_tooltip_x;
		int m_tooltip_y;

		//! Default/Initialization constructor.
		/*!
			@param parent a pointer to parent window
		*/
		pGUIObject(pGUIObject *parent=0);

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUIObject(const pGUIObject& in);

		//! Destructor.
		virtual ~pGUIObject();

		//! Clone operation.
		/*!
			This is an abstract method and must be implemented by all classes
			that inherit of this class.
			@returns a copy of this object
		*/
		virtual pGUIObject* clone() const=0;

		//! Initialize the object.
		/*!
			This is a virtual method. The default implementation do nothing.
			On creation, this function is called.
		*/
		virtual void init();

		//! Updates the object's state accordingly to elapsed time.
		/*!
			This is a virtual method. The default implementation sets the global
			transformation of this object to the global vector parameter. Moreover,
			it updates bounding boxes associated with this object. Finally, it calls
			the step of all children recursively.
			@param elapsed_time elapsed time in seconds
			@param global_x global x translation that will transform this objects and its children
			@param global_y global y translation that will transform this objects and its children
		*/
		virtual void step(const float elapsed_time,const int& global_x,const int& global_y);

		//! Draws this object.
		/*!
			This is a virtual method. The default implementation do nothing.
			@param scissor_rect rect used in OpenGL scissor test
		*/
		virtual void draw(pRect& scissor_rect);

		//! Stores common/custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/ 
		int get_common_param_desc(int i,pParamDesc *pd);
		virtual int get_custom_param_desc(int i,pParamDesc *pd);

		//! It is called before/after some parameter is changed.
		/*!
			This is a virtual method. The default implementation do nothing.
			@param i i-th parameter
		*/
		virtual void on_pre_parameter_change(int i);
		virtual void on_pos_parameter_change(int i);

		virtual void on_get_mouse();
		virtual void on_kill_mouse();

		virtual void on_get_focus();
		virtual void on_kill_focus();

		virtual int get_content_height();

		virtual void process_mouse_input(pGUIEventHandler *event_handler);
		virtual void process_keyboard_input(int keycode,int mod,unsigned char ch);

		virtual void on_begin_drag();
		virtual void on_end_drag();

		//! Tests if (x,y) point belongs to this gui object.
		/*!
			@param x point x
			@param y point y
			@return true if (x,y) point belongs to this gui object and false otherwise
		*/
		bool is_inside(int x,int y) const
		{
			return m_global_x<=x && x<=(m_global_x+m_width) &&
	               m_global_y<=y && y<=(m_global_y+m_height);
		}

	protected:

		//! Update vertex buffer objects
		virtual void update_vbo();
};

#endif

