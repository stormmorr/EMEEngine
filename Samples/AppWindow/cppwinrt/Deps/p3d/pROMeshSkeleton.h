/*! \file */

#ifndef PROMESHSKELETON_H
#define PROMESHSKELETON_H

//! Render Object Mesh class
/*!
	This class implements an object that supports triangles meshes.
*/
class P3D_API pROMeshSkeleton : public pRenderObject
{
	public:
		pMeshSkeleton *m_mesh;		//!< the skeleton mesh
		pArray<pString> m_ani;		//!< animation file list
		pArray<pString> m_mtg;		//!< morph target file list
		pArray<pString> m_mtgani;	//!< morph target file list
		int m_curani;				//!< currently selected animation
		int m_curmtgani[4];			//!< currently selected morph target animation in each channel
		float m_mtgani_weight[4];	//!< animation weight for each channel
		float m_mtgani_blendtime[4];//!< animation blend time for each channel
		float m_time_ani;			//!< current animation time
		float m_time_mtg[4];		//!< current mtg animation time
		float m_blendtime;			//!< duration for animation blending
		float m_timefactor_ani;		//!< factor to multiply animation time
		float m_timefactor_mtg[4];	//!< factor to multiply mtg time
		pArray<pMesh *> m_attach_mesh;		//!< meshes attached to skeleton
		pArray<int> m_attach_bone;			//!< bones for each attached mesh

		//! Default constructor.
		pROMeshSkeleton() :
			m_mesh(0),
			m_curani(0),
			m_time_ani(0),
			m_blendtime(0.25f),
			m_timefactor_ani(1.0f)
		{
			m_type=TYPE_RO_MESH_SKELETON;
			m_flags|=P_ROFLAGS_HASMESH;
			m_curmtgani[0]=m_curmtgani[1]=-1;
			m_curmtgani[2]=m_curmtgani[3]=-1;
			m_mtgani_blendtime[0]=m_mtgani_blendtime[1]=0.25f;
			m_mtgani_blendtime[2]=m_mtgani_blendtime[3]=0.25f;
			m_mtgani_weight[0]=m_mtgani_weight[1]=1.0f;
			m_mtgani_weight[2]=m_mtgani_weight[3]=1.0f;
			m_time_mtg[0]=m_time_mtg[1]=
			m_time_mtg[2]=m_time_mtg[3]=0;
			m_timefactor_mtg[0]=m_timefactor_mtg[1]=
			m_timefactor_mtg[2]=m_timefactor_mtg[3]=1.0f;
		}

		//! Destructor.
		virtual ~pROMeshSkeleton()
		{ }
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROMeshSkeleton(const pROMeshSkeleton& in) :
			pRenderObject(in),
			m_mesh(in.m_mesh),
			m_ani(in.m_ani),
			m_mtg(in.m_mtg),
			m_curani(in.m_curani),
			m_mtgani(in.m_mtgani),
			m_time_ani(in.m_time_ani),
			m_blendtime(in.m_blendtime),
			m_timefactor_ani(in.m_timefactor_ani),
			m_attach_mesh(in.m_attach_mesh),
			m_attach_bone(in.m_attach_bone)
		{ 
			m_curmtgani[0]=in.m_curmtgani[0];
			m_curmtgani[1]=in.m_curmtgani[1];
			m_curmtgani[2]=in.m_curmtgani[2];
			m_curmtgani[3]=in.m_curmtgani[3];
			m_mtgani_weight[0]=in.m_mtgani_weight[0];
			m_mtgani_weight[1]=in.m_mtgani_weight[1];
			m_mtgani_weight[2]=in.m_mtgani_weight[2];
			m_mtgani_weight[3]=in.m_mtgani_weight[3];
			m_mtgani_blendtime[0]=in.m_mtgani_blendtime[0];
			m_mtgani_blendtime[1]=in.m_mtgani_blendtime[1];
			m_mtgani_blendtime[2]=in.m_mtgani_blendtime[2];
			m_mtgani_blendtime[3]=in.m_mtgani_blendtime[3];
			m_time_mtg[0]=in.m_time_mtg[0];
			m_time_mtg[1]=in.m_time_mtg[1];
			m_time_mtg[2]=in.m_time_mtg[2];
			m_time_mtg[3]=in.m_time_mtg[3];
			m_timefactor_mtg[0]=in.m_timefactor_mtg[0];
			m_timefactor_mtg[1]=in.m_timefactor_mtg[1];
			m_timefactor_mtg[2]=in.m_timefactor_mtg[2];
			m_timefactor_mtg[3]=in.m_timefactor_mtg[3];
		}

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROMeshSkeleton(*this); }

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

		pMesh *get_mesh()
		{ return m_mesh; };
};

//! Render Object Mesh Class Descriptor
/*!
	It is a descriptor to pROMeshSkeleton classes and is used, mainly, in objects
	building process.
*/
class pROMeshSkeleton_desc : public pClassDesc
{
	public:
		//! Creates a new mesh object.
		/*! 
			@return a pointer to the new mesh object
		*/
		void *create()	const { return new pROMeshSkeleton; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh_skeleton"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH_SKELETON; }
};
#endif

