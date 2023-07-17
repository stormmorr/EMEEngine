/*! \file */

#ifndef PROLENSFLARE_H
#define PROLENSFLARE_H

//! Render Object Lens Flare class
/*!
*/
class P3D_API pROLensFlare : public pRenderObject
{
	private:

		int m_num_elem;						//!< number of elements (used to prevent arrays of different sizes)
		pArray<float> m_elem_calc_size;		//!< element calculated size (in pixels)
		pArray<pVector> m_elem_calc_pos;	//!< element calculated position
		pArray<float> m_elem_calc_opac;		//!< element calculated opacity

		//! calculate number of elements
		void calc_num_elements();

	public:

		pArray<int> m_elem_tex;				//!< element texture
		pArray<float> m_elem_pos;			//!< element position [0,1]
		pArray<float> m_elem_size;			//!< element size (as a scale factor)
		pArray<float> m_elem_opac;			//!< element opacity
		pArray<pVector> m_elem_color;		//!< element color
		float m_scale_opacity;				//!< controls opacity of textures whose position (m_elem_pos) is 0

		double cam_model_mat[16],cam_proj_mat[16];

		//! Default constructor.
		pROLensFlare() :
			m_num_elem(0),
			m_scale_opacity(1.0f)
		{ m_type=TYPE_RO_LENS_FLARE; }

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROLensFlare(const pROLensFlare& in) :
			pRenderObject(in),
			m_num_elem(in.m_num_elem),
			m_elem_calc_size(in.m_elem_calc_size),
			m_elem_calc_pos(in.m_elem_calc_pos),
			m_elem_calc_opac(in.m_elem_calc_opac),
			m_elem_tex(in.m_elem_tex),
			m_elem_pos(in.m_elem_pos),
			m_elem_size(in.m_elem_size),
			m_elem_opac(in.m_elem_opac),
			m_elem_color(in.m_elem_color),
			m_scale_opacity(in.m_scale_opacity)
		{ }

		//! Destructor.
		virtual ~pROLensFlare()
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROLensFlare(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It updates the bounding boxe associated with this object and calls
			the recursive step of all children.
			@param elapsed_time elapsed time in seconds
			@param global global transformation that will transform this objects and its children
		*/
		void step(const float elapsed_time,const pMatrix& global);

		//! Draws this object.
		void draw();

		//! Draws this object in 2d mode.
		/*!
			This is a virtual method. The default implementation do nothing.
		*/
		void draw2d();

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
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
};

//! Render Object Lens Flare Class Descriptor
/*!
	It is a descriptor to pROLensFlare classes and is used, mainly, in objects
	building process.
*/
class pROLensFlare_desc : public pClassDesc
{
	public:
		//! Creates a new lens flare object.
		/*! 
			@return a pointer to the new lens flare object
		*/
		void *create()	const { return new pROLensFlare; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "lens_flare"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_LENS_FLARE; }
};

#endif
