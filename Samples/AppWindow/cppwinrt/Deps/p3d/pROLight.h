/*! \file */

#ifndef PROLIGHT_H
#define PROLIGHT_H

//! Render Object Light class
/*!
*/
class P3D_API pROLight : public pRenderObject
{
	public:
		int m_enabled;
		float m_radius;
		float m_multiplier;
		pVector m_color;
		float m_angle;			//!< only for spot light
		pLight m_light;
		pPeriodicFunc m_func;
		
		int m_shadow;			//!< 0 - no shadow, 1 - shadow volume, 2 - shadow map
		int m_global;

	//! Default constructor.
	pROLight() :
		m_enabled(1),
		m_radius(100),
		m_multiplier(1),
		m_color(1),
		m_angle(0.0f),
		m_shadow(0),
		m_global(0)
	{ m_type=TYPE_RO_LIGHT; }

	//! Destructor.
	virtual ~pROLight()
	{ }
	
	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pROLight(const pROLight& in) :
		pRenderObject(in),
		m_enabled(in.m_enabled),
		m_radius(in.m_radius),
		m_multiplier(in.m_multiplier),
		m_color(in.m_color),
		m_angle(in.m_angle),
		m_light(in.m_light),
		m_func(in.m_func),
		m_shadow(in.m_shadow),
		m_global(in.m_global)
	{ }

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pRenderObject* clone() const
	{ return new pROLight(*this); }

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

//! Render Object Light Class Descriptor
/*!
	It is a descriptor to pROLight classes and is used, mainly, in objects
	building process.
*/
class pROLight_desc : public pClassDesc
{
	public:
	//! Creates a new light object.
	/*! 
		@return a pointer to the new group object
	*/
	void *create() const { return new pROLight; }

	//! Retrieves the name of the associated class.
	/*! 
		@return the name of the associated class
	*/
	const char *get_name() const { return "light"; }

	//! Retrieves the type of the associated class.
	/*! 
		@return the type of the associated class
	*/
	int get_type() const { return TYPE_RO_LIGHT; }
};

#endif

