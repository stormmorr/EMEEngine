/*! \file */

#ifndef PGUIRADIALCURSOR_H
#define PGUIRADIALCURSOR_H

//! Graphic User Interface Radial Group class
/*!
	This class implements a cursor that moves around a circle.		
*/
class P3D_API pGUIRadialCursor : public pGUIObject
{
	public:
		int m_pic;
		float m_dist;
		float m_angle_start;
		float m_angle_end;
		float m_percent;
		int m_rotatepic;
		float m_cur_angle;
		int m_point_target_x;
		int m_point_target_y;

	//! Default/Initialization constructor.
	/*!
		@param parent a pointer to parent window
	*/
	pGUIRadialCursor() :
		m_pic(-1),
		m_dist(25),
		m_angle_start(0),
		m_angle_end(180),
		m_percent(0),
		m_rotatepic(1),
		m_cur_angle(0),
		m_point_target_x(0),
		m_point_target_y(0)
	{
		m_type=TYPE_GUI_RADIALCURSOR;
	}

	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pGUIRadialCursor(const pGUIRadialCursor& in) :
		pGUIObject(in),
		m_pic(in.m_pic),
		m_dist(in.m_dist),
		m_angle_start(in.m_angle_start),
		m_angle_end(in.m_angle_end),
		m_percent(in.m_percent),
		m_rotatepic(in.m_rotatepic),
		m_cur_angle(in.m_cur_angle),
		m_point_target_x(in.m_point_target_x),
		m_point_target_y(in.m_point_target_y)
	{
	}

	//! Detructor.
	virtual ~pGUIRadialCursor()
	{
	}

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pGUIObject* clone() const
	{ return new pGUIRadialCursor(*this); };

	//! Draws this object.
	/*!
		@param scissor_rect rect used in OpenGL scissor test
	*/
	void draw(pRect& scissor_rect);

	//! It is called after some parameter is changed.
	/*!
		@param i i-th parameter
	*/
	void on_pos_parameter_change(int i);

	//! Stores custom parameters in a given pParamDesc object.
	/*! 
		If pd is equals to 0, the method only returns the number of parameters.
		@param i i-th parameter
		@param pd pParamDesc object that holds all informations about the i-th parameter
		@return the number of parameters
	*/ 
	int get_custom_param_desc(int i,pParamDesc *pd);
};

//! GUI Object Group Class Descriptor
/*!
	It is a descriptor to pGUIRadialCursor classes and is used, mainly, in objects
	building process.
*/
class pGUIRadialCursor_desc : public pClassDesc
{
	public:
		//! Creates a new billboard object.
		/*! 
			@return a pointer to the new billboard object
		*/
		void *create()	const { return new pGUIRadialCursor; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "radial_cursor"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_RADIALCURSOR; }
};

#endif

