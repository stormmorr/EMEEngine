/*! \file */

#ifndef PROMESHHUGE_H
#define PROMESHHUGE_H

//! Render Object Mesh Huge class
/*!
	This class implements an object that supports huge triangle meshes. It is a
	special kind of object because it is drawn in a special region of view
	frustum.
	The view frustum is divided into three regions:
	- region1: between camera and far plane
	- region2: between far plane and double far plane
	- region3: between double far plane and huge plane.
	A Render Object Mesh Huge has a real position in the region 3, but to the
	OpenGL hardware, view frustum is formed by regions 1 and 2. So, a Render
	Object Mesh Huge must be transformded to a relative place into region 2.
	Others visible objects are drawn into region 1.
*/
class P3D_API pROMeshHuge : public pRenderObject
{
	private:
		bool m_culled;				//!< was object culled?
		float m_calc_scale;			//!< scale factor to draw mesh into region 2

		//! Updates object bounding box.
		void update_bound_box();

	public:
		float m_final_scale;		//!< calc_scale*size_scale
		double m_size_scale;		//!< scale factor to resize object
		pMesh *m_mesh;				//!< a triangle mesh
		pDVector m_pos;				//!< double-precision global position

		//! Default constructor.
		pROMeshHuge() :
			m_culled(false),
			m_calc_scale(1.0f),
			m_final_scale(1.0f),
			m_size_scale(1.0f),
			m_mesh(0)
		{
			m_type=TYPE_RO_MESH_HUGE;
			m_flags|=P_ROFLAGS_HASMESH;
		}

		//! Destructor.
		virtual ~pROMeshHuge()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROMeshHuge(const pROMeshHuge& in) :
			pRenderObject(in),
			m_culled(in.m_culled),
			m_calc_scale(in.m_calc_scale),
			m_final_scale(in.m_final_scale),
			m_size_scale(in.m_size_scale),
			m_mesh(in.m_mesh),
			m_pos(in.m_pos)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROMeshHuge(*this); }

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

//! Render Object Mesh Huge Class Descriptor
/*!
	It is a descriptor to pROMeshHuge classes and is used, mainly, in objects
	building process.
*/
class pROMeshHuge_desc : public pClassDesc
{
	public:
		//! Creates a new mesh huge object.
		/*! 
			@return a pointer to the new mesh huge object
		*/
		void *create()	const { return new pROMeshHuge; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh_huge"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH_HUGE; }
};

#endif
