/*! \file */

#ifndef PGUIMODELVIWER_H
#define PGUIMODELVIWER_H

//! GUI Progress Bar Object class
/*!
*/
class P3D_API pGUIModelViewer : public pGUIObject
{
	public:
		pMesh *m_mesh;				//!< p3d model file to view
		pVector m_lightpos;			//!< light position 
		pVector m_lightcolor;		//!< light color
		pVector m_lightambient;		//!< light ambient
		pVector m_rot;				//!< object rotation
		pVector m_rotvel;			//!< rotation velocity

	//! Default constructor.
	pGUIModelViewer() :
		m_mesh(0),
		m_lightpos(0,0,1000,10000),
		m_lightcolor(1),
		m_lightambient(0.25),
		m_rot(0),
		m_rotvel(0)
	{	m_type=TYPE_GUI_MODELVIEWER;	}

	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pGUIModelViewer(const pGUIModelViewer& in) :
		pGUIObject(in),
		m_mesh(in.m_mesh),
		m_lightpos(in.m_lightpos),
		m_lightcolor(in.m_lightcolor),
		m_lightambient(in.m_lightambient),
		m_rot(in.m_rot),
		m_rotvel(in.m_rotvel)
	{
	}

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pGUIObject* clone() const
	{ return new pGUIModelViewer(*this); };

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
};

//! GUI Progress Bar Object Class Descriptor
/*!
*/
class pGUIModelViewer_desc : public pClassDesc
{
	public:
		//! Creates a new partial disk object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIModelViewer; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "model_viewer"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_MODELVIEWER; }
};

#endif
