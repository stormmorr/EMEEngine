/*! \file */

#ifndef PROMESHTEAPOT_H
#define PROMESHTEAPOT_H

//! Render Object Mesh class
/*!
	This class implements an object that supports triangles meshes.
*/
class P3D_API pROMeshTeapot : public pRenderObject
{
	public:
		int m_tesselation;
		int m_texmap,m_normalmap;
		float m_scale;
		pVector m_diffuse;
		pVector m_specular;
		
		pTeapot m_teapot;
		pMesh m_mesh;

		//! Default constructor.
		pROMeshTeapot() :
			m_tesselation(6),
			m_texmap(-1),
			m_normalmap(-1),
			m_scale(1),
			m_diffuse(1),
			m_specular(1,1,1,64)
		{
			m_type=TYPE_RO_MESH_TEAPOT;
			m_flags|=P_ROFLAGS_HASMESH;
		}

		//! Destructor.
		virtual ~pROMeshTeapot();
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROMeshTeapot(const pROMeshTeapot& in) :
			pRenderObject(in),
			m_tesselation(in.m_tesselation),
			m_texmap(in.m_texmap),
			m_normalmap(in.m_normalmap),
			m_scale(in.m_scale),
			m_diffuse(in.m_diffuse),
			m_specular(in.m_specular)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROMeshTeapot(*this); }

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
		void draw_shadows(const pVector& lightpos);

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

		void setup_light();
};

//! Render Object Mesh Class Descriptor
/*!
	It is a descriptor to pROMeshTeapot classes and is used, mainly, in objects
	building process.
*/
class pROMeshTeapot_desc : public pClassDesc
{
	public:
		//! Creates a new mesh object.
		/*! 
			@return a pointer to the new mesh object
		*/
		void *create()	const { return new pROMeshTeapot; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh_teapot"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH_TEAPOT; }
};

#endif
