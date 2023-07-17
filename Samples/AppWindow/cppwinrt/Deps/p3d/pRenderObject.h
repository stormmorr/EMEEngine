/*! \file */

#ifndef PRENDEROBJECT_H
#define PRENDEROBJECT_H

//! This struct is used to hold all informations about the nearest intersection point.
typedef struct 
{
	pVector ro;			//!< ray origin (input)
	pVector rd;			//!< ray direction (input)
	
	pVector ip;			//!< intersection point (output)
	float dist;			//!< intersection distance (output)
	pRenderObject *obj; //!< intersection object (output)
	pMesh *mesh;		//!< intersection mesh (output)
	unsigned int face;	//!< intersection face (output)
} pRayIntersectInfo;

class pProjectileInfo
{
public:
	unsigned int obj;	//!< object id
	pVector pos;		//!< object position (float-precision)
	pVector vel;		//!< object velocity
	float start_time;	//!< animation map start time

	pProjectileInfo() :
		start_time(-1.0f)
	{ }
};

class pDProjectileInfo
{
public:
	unsigned int obj;	//!< object id
	pDVector pos;		//!< object position (double-precision)
	pVector vel;		//!< object velocity
	float start_time;	//!< animation map start time

	pDProjectileInfo() :
		start_time(-1.0f)
	{ }
};

//! Render Object class
/*!
	This class implements a base class to render objects.
*/
class P3D_API pRenderObject
{
	friend class pRenderObjectManager;

	public:
		unsigned int m_type;	//!< object class type
		unsigned int m_id;		//!< object unique id
		unsigned int m_flags;	//!< bit flags

		pMatrix m_transform;		//!< transformation matrix (translate/rotate)
		pMatrix m_transform_global; //!< global transformation matrix (translate/rotate)

		int m_num_frustum_planes;		//!< number of frustum planes to culling
		pBoundBox m_bbox;				//!< bound box in local space
		pBoundBox m_bbox_global;		//!< bound box in global space
		pBoundBox m_bbox_global_childs; //!< bound box in global space including all childs

		pArray<pLight*> m_light;
		
		pString m_name; //!< object name

		pArray<pRenderObject *> m_child; //!< array of children objects
		pRenderObject *m_parent;		 //!< pointer to parent object
		const pRenderObject *m_source;   //!< pointer to original stock if active 

		//! Default constructor.
		pRenderObject();

		//! Destructor.
		virtual ~pRenderObject();
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pRenderObject(const pRenderObject& in);

		//! Clone operation.
		/*!
			This is an abstract method and must be implemented by all classes
			that inherit of this class.
			@returns a copy of this object
		*/
		virtual pRenderObject* clone() const=0;

		//! Initializes the state of this object.
		/*!
			This is a virtual method. The default implementation do nothing.
			@param active true if this is an active object and false otherwise
		*/
		virtual void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			This is a virtual method. The default implementation sets the global
			transformation of this object to the global matrix parameter. Moreover,
			it updates bounding boxes associated with this object. Finally, it call
			recursive the step of all children.
			@param elapsed_time elapsed time in seconds
			@param global global transformation that will transform this objects and its children
		*/
		virtual void step(const float elapsed_time,const pMatrix& global);

		//! Updates the huge object's state accordingly to elapsed time.
		/*!
			It performs a special step for objects that are between farplane and hugeplane. 
			@param elapsed_time elapsed time in seconds
			@param global global transformation that will transform this objects and its children
			@param translation stores translation apllied on object
			@param scale stores scale apllied on object
			@param culled true if this object must be culled
		*/
#ifdef P_MANAGER_OBJ
		virtual void step_huge_objects(const float elapsed_time,const pMatrix& global,const pDVector& pos,float *scale=NULL,bool *culled=NULL);
#endif

		//! Draws this object.
		/*!
			This is a virtual method. The default implementation do nothing.
		*/
		virtual void draw();

		//! Draws this object.
		/*!
			This is a virtual method. The default implementation do nothing.
		*/
		virtual void draw_shadows(const pVector& lightpos);

		//! Draws this object after all others.
		/*!
			This is a virtual method. The default implementation do nothing.
		*/
		virtual void post_draw();

		//! Draws this object in 2d mode.
		/*!
			This is a virtual method. The default implementation do nothing.
		*/
		virtual void draw2d();

		//! Stores common/custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, these methods only return the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/
		int get_common_param_desc(int i,pParamDesc *pd);
		virtual int get_custom_param_desc(int i,pParamDesc *pd);
		
		//! Get the i-th attach point pointer.
		/*! 
			If d is equals to 0, these methods only return the number of attach points.
			This is a virtual method. The default implementation returns 0 attach
			points.
			@param i i-th attach point
			@param d address of pointer to recive pointer to pDummy object
			@return the number of attach points
		*/
		virtual int get_attach_point(int i,pDummy **d);

		//! Get the i-th obb pointer.
		/*! 
			If o is equals to 0, these methods only return the number of obb.
			This is a virtual method. The default implementation returns 0 obb.
			@param i i-th attach point
			@param o address of pointer variable to recive pointer to pOrientedBoundBox object
			@return the number of attach points
		*/
		virtual int get_obb(int i,pOrientedBoundBox **o);

		//! It is called before/after some parameter is changed.
		/*!
			This is a virtual method. The default implementation do nothing.
			@param i i-th parameter
		*/
		virtual void on_pre_parameter_change(int i);
		virtual void on_pos_parameter_change(int i);

		//! Intersects a ray with this object and all children.
		/*!
			This is a virtual method. The default implementation tests by intersection to
			all children.
			@param ri contains all informations about the nearest intersection during the process
			@return true if there is intersection and false otherwise
		*/
		virtual bool ray_intersect(pRayIntersectInfo *ri);

		//! Translates object world by given vector
		/*!
			This is a virtual method. The default implementation adds the given translation 
			to the object's transform matrix only if object is a active root and recurse down children.
			@param t translation to be applied to world
		*/
		virtual void translate_world(const pVector& t);

		virtual void setup_light();

		virtual pMesh *get_mesh();

protected:
#ifdef P_MANAGER_OBJ
		//! Release child objects from their parent and insert them into the active hash.
		/*!
			This method onle makes sense when called from active objects. Calling it from
			stock objects will have no effect.
			@param i child index, -1 for releasing all of them (default: -1)
			@param new_parent an optional new parent object for the released children, 0 for setting them as roots (default: 0)
		*/
		void release_child(int i=-1,pRenderObject *new_parent=0);

		//! Link the given object to this as a child.
		/*!
			This method onle makes sense when called from active objects. Calling it from
			stock objects will have no effect.
			@param o the object to be linked to this as a child
		*/
		void link_child(pRenderObject *o);
#endif
};

#endif

