/*! \file */

#ifndef PGUIMULTILINETEXT_H
#define PGUIMULTILINETEXT_H

class P3D_API pGUIMultilineText : public pGUIObject
{
	friend class pGUIListControl;

	public:
		int				m_tex;
		int				m_text_horz_align;
		int				m_text_vert_align;
		pVector			m_default_text_color;
		pArray<pVector> m_custom_text_colors;
		int				m_text_border_size;

		int				m_add_blend;

		pGUIMultilineText();
		pGUIMultilineText(const pGUIMultilineText& in);

		virtual ~pGUIMultilineText(){};

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIMultilineText(*this); };

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

		void on_pos_parameter_change(int i);

	protected:
		pArray<pString> m_lines;

		void process_lines();
		
		void draw_multiline(int i);
		void draw_line(int i);

		void draw_text(int x,int y,const char *text,int fontsize,int n=-1) const;
		void draw_text_center(int x,int y,const char *text,int fontsize) const;
		int get_text_size_without_colors(const char *text, int fontsize) const;
};

//! GUI Window Object Class Descriptor
/*!
	It is a descriptor to the pGUIMultilineText class and is used, mainly, in objects
	building process.
*/
class pGUIMultilineText_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIMultilineText; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "multiline_text"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_MULTILINE_TEXT; }
};

#endif

