/*! \file */

#ifndef PROOBFUSCATINGPOINT_H
#define PROOBFUSCATINGPOINT_H

//! Render Object Obfuscating Point class
/*!
*/
class P3D_API pROObfuscatingPoint : public pRenderObject
{
	public:
		pVector m_color;
		float m_min_angle;
		pPeriodicFunc m_func;
		float m_near_attenuation;
		float m_far_attenuation;

		float m_start_time;
		
	//! Default constructor.
	pROObfuscatingPoint() :
		m_color(1.0f),
		m_min_angle(1.0f),
		m_near_attenuation(100.0f),
		m_far_attenuation(200.0f),
		m_start_time(0.0f)
	{ m_type=TYPE_RO_OBFUSCATING_POINT; }

	//! Destructor.
	virtual ~pROObfuscatingPoint()
	{
		g_render->const_blink(pVector(0.0f,0.0f,0.0f,0.0f));
	}
	
	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pROObfuscatingPoint(const pROObfuscatingPoint& in) :
		pRenderObject(in),
		m_color(in.m_color),
		m_min_angle(in.m_min_angle),
		m_func(in.m_func),
		m_near_attenuation(in.m_near_attenuation),
		m_far_attenuation(in.m_far_attenuation),
		m_start_time(in.m_start_time)
	{ }

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pRenderObject* clone() const
	{ return new pROObfuscatingPoint(*this); }

	//! Initializes the state of this object.
	/*!
		Calculates a bounding boxe to this group.
		@param active true if this is an active object and false otherwise
	*/
	void init(bool active);

	//! Updates the object's state accordingly to elapsed time.
	/*!
		It calls recursively the step of all children.
		@param elapsed_time elapsed time in seconds
		@param global global transformation that will transform this objects and its children
	*/
	void step(const float elapsed_time,const pMatrix& global);

	//! Draws this object.
	void draw();

	//! Stores custom parameters in a given pParamDesc object.
	/*! 
		If pd is equals to 0, these methods only return the number of parameters.
		@param i i-th parameter
		@param pd pParamDesc object that holds all informations about the i-th parameter
		@return the number of parameters
	*/
	int get_custom_param_desc(int i,pParamDesc *pd);
};

//! Render Object Obfuscating Point Class Descriptor
/*!
	It is a descriptor to pROObfuscatingPoint classes and is used, mainly, in objects
	building process.
*/
class pROObfuscatingPoint_desc : public pClassDesc
{
	public:
	//! Creates a new obfuscating point object.
	/*! 
		@return a pointer to the new group object
	*/
	void *create() const { return new pROObfuscatingPoint; }

	//! Retrieves the name of the associated class.
	/*! 
		@return the name of the associated class
	*/
	const char *get_name() const { return "obfuscating_point"; }

	//! Retrieves the type of the associated class.
	/*! 
		@return the type of the associated class
	*/
	int get_type() const { return TYPE_RO_OBFUSCATING_POINT; }
};

#endif

