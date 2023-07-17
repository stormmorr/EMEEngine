/*! \file */

#ifndef PROMESH_H
#define PROMESH_H

//! Render Object Mesh class
/*!
	This class implements an object that supports triangles meshes.
*/
class P3D_API pROMesh : public pRenderObject
{
	public:
		pMesh *m_mesh;	//!< a triangle mesh

		//! Default constructor.
		pROMesh() :
			m_mesh(0)
		{
			m_type=TYPE_RO_MESH;
			m_flags|=P_ROFLAGS_HASMESH;
		}

		//! Destructor.
		virtual ~pROMesh()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROMesh(const pROMesh& in) :
			pRenderObject(in),
			m_mesh(in.m_mesh)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROMesh(*this); }

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

		//! Stores the i-th attach point in a given pDummy object.
		/*! 
			If d is equals to 0, these methods only return the number of attach points.
			@param i i-th attach point
			@param d pDummy object that holds all informations about the i-th attach point
			@return the number of attach points
		*/
		int get_attach_point(int i,pDummy **d);

		//! Get the i-th obb pointer.
		/*! 
			If o is equals to 0, these methods only return the number of obb.
			This is a virtual method. The default implementation returns 0 obb.
			@param i i-th attach point
			@param o address of pointer variable to recive pointer to pOrientedBoundBox object
			@return the number of attach points
		*/
		int get_obb(int i,pOrientedBoundBox **o);

		//! Intersects a ray with this object and all children.
		/*!
			@param ri contains all informations about the nearest intersection during the process
			@return true if there is intersection and false otherwise
		*/
		bool ray_intersect(pRayIntersectInfo *ri);

		void setup_light();

		pMesh *get_mesh()
		{ return m_mesh; }
};

//! Render Object Mesh Class Descriptor
/*!
	It is a descriptor to pROMesh classes and is used, mainly, in objects
	building process.
*/
class pROMesh_desc : public pClassDesc
{
	public:
		//! Creates a new mesh object.
		/*! 
			@return a pointer to the new mesh object
		*/
		void *create()	const { return new pROMesh; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH; }
};

#endif

