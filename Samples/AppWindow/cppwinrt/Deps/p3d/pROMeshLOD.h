/*! \file */

#ifndef PROMESHLOD_H
#define PROMESHLOD_H

//! Render Object Mesh Level Of Detail class
/*!
	This class supports discrete LOD models for geometry.
*/
class P3D_API pROMeshLOD : public pRenderObject
{
	public:
		pArray<pMesh *> m_mesh;		//!< the static mesh files for each lod
		int m_selmesh;				//!< currently selected lod
		pArray<float> m_dist;		//!< the length of the influence region of the LOD process 
		int m_draw_after_maxdist;	//!< draw after maxdist?

		//! Default constructor.
		pROMeshLOD() :
			m_selmesh(-1),
			m_draw_after_maxdist(1)
		{ 
			m_type=TYPE_RO_MESH_LOD;
			m_flags|=P_ROFLAGS_HASMESH;
		}

		//! Destructor.
		virtual ~pROMeshLOD()
		{ }

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROMeshLOD(const pROMeshLOD& in) :
			pRenderObject(in),
			m_mesh(in.m_mesh),
			m_selmesh(in.m_selmesh),
			m_dist(in.m_dist),
			m_draw_after_maxdist(in.m_draw_after_maxdist)
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROMeshLOD(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It selects a mesh accordingly to distance of the camera, updates the
			bounding boxe associated with this object and calls recursively step
			of all children.
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

		void setup_light();

		pMesh *get_mesh()
		{
			if(m_selmesh!=-1)
				return m_mesh.buf[m_selmesh];
			return NULL;
		}

		//! Intersects a ray with this object and all children.
		/*!
			@param ri contains all informations about the nearest intersection during the process
			@return true if there is intersection and false otherwise
		*/
		bool ray_intersect(pRayIntersectInfo *ri);
};

//! Render Object Mesh Level Of Detail Class Descriptor
/*!
	It is a descriptor to pROMeshLOD classes and is used, mainly, in objects
	building process.
*/
class pROMeshLOD_desc : public pClassDesc
{
	public:
		//! Creates a new mesh LOD object.
		/*! 
			@return a pointer to the new mesh LOD object
		*/
		void *create()	const { return new pROMeshLOD; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh_lod"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH_LOD; }
};

#endif
