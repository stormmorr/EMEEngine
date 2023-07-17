/*! \file */

#ifndef PGUIPROGRESSBAR_H
#define PGUIPROGRESSBAR_H

//! GUI Progress Bar Object class
/*!
*/
class P3D_API pGUIProgressBar : public pGUIObject
{
	public:
		int m_orientation;			//!< progress bar orientation (0:vertical,1:horizontal)
		int m_tex_bg;				//!< background texture
		int m_tex_fill;				//!< fill texture
		float m_min_range;			//!< min range
		float m_max_range;			//!< max range
		float m_percent;			//!< represents the number of slices that will be filled with fill color
		pPeriodicFunc m_tex_func;	//!< function to combine fill texture with background texture

	//! Default constructor.
	pGUIProgressBar() :
		m_orientation(1),
		m_min_range(0.0f),
		m_max_range(1.0f),
		m_percent(0.5),
		m_tex_bg(-1),
		m_tex_fill(-1)
	{ m_type=TYPE_GUI_PROGRESSBAR; }

	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pGUIProgressBar(const pGUIProgressBar& in) :
		pGUIObject(in),
		m_orientation(in.m_orientation),
		m_min_range(in.m_min_range),
		m_max_range(in.m_max_range),
		m_percent(in.m_percent),
		m_tex_bg(in.m_tex_bg),
		m_tex_fill(in.m_tex_fill),
		m_tex_func(in.m_tex_func)
	{ }

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pGUIObject* clone() const
	{ return new pGUIProgressBar(*this); };

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

	float get_percent() const;
};

//! GUI Progress Bar Object Class Descriptor
/*!
*/
class pGUIProgressBar_desc : public pClassDesc
{
	public:
		//! Creates a new partial disk object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIProgressBar; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "progress_bar"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_PROGRESSBAR; }
};
#endif

