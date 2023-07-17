/*! \file */

#ifndef PGUIPROGRESSDISK_H
#define PGUIPROGRESSDISK_H

//! GUI Progress Disk Object class
/*!
*/
class P3D_API pGUIProgressDisk : public pGUIObject
{
	private:
		float* m_vertex_array;	//!< array of vertices
		int* m_index_array;		//!< array of indices
		unsigned int m_vertex_buffer;	//!< vbo id
		unsigned int m_index_buffer;	//!< vbo id

		//! Update vertex buffer objects
		void update_vbo();
		//! Load geometry data to GPU 
		void push_data() const;
		//! Unload geometry data from GPU 
		void pop_data() const;

	public:
		int m_slices;					//!< the number of quadrilaterals
		float m_inner_radius;			//!< the inner radius of the progress disk
		float m_outer_radius;			//!< the outer radius of the progress disk
		float m_start_angle;			//!< start angle (in degrees)
		float m_end_angle;				//!< end angle (in degrees)
		float m_percent;				//!< represents the number of slices that will be filled with fill color
		pVector m_fill_color;			//!< (x,y,z) - fill color (w) - transparent
		pPeriodicFunc m_color_func;		//!< function to change color

	//! Default constructor.
	pGUIProgressDisk();

	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pGUIProgressDisk(const pGUIProgressDisk& in);

	//! Destructor.
	virtual ~pGUIProgressDisk();

	//! Clone operation.
	/*!
		@returns a copy of this object
	*/
	pGUIObject* clone() const
	{ return new pGUIProgressDisk(*this); };

	//! Initialize the object.
	/*!
		This is a virtual method. The default implementation do nothing.
		On creation, this function is called.
	*/
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

	//! It is called after some parameter is changed.
	/*!
		@param i i-th parameter
	*/
	void on_pos_parameter_change(int i);

	//! Free all memory of progress disk and resets all data.
	void reset();

	//! Build a progress disk.
	/*!
		@param ns number of slices
		@param ir inner radius
		@param or outer radius
		@param sa start angle (in degrees)
		@param fa final angle (in degrees)
	*/
	void build(int ns,float ir,float _or,float sa,float fa);
};

//! GUI Partial Disk Object Class Descriptor
/*!
*/
class pGUIProgressDisk_desc : public pClassDesc
{
	public:
		//! Creates a new partial disk object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIProgressDisk; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "progress_disk"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_PROGRESSDISK; }
};

#endif
