/*! \file */
#if 0 // QAGE_DESKTOP
#ifndef PROPARTICLESYSTEMGPU_H
#define PROPARTICLESYSTEMGPU_H

//! Render Object Mesh class
/*!
	This class implements an object that supports triangles meshes.
*/
class P3D_API pROParticleSystemGPU : public pRenderObject
{
	public:
		int m_current;
		int m_texsize;
		int m_texmap;
		int m_blendadd;
		int m_rotflag;
		float m_life;
		float m_lifevar;
		float m_fade;
		float m_vel;
		float m_veldamp;
		float m_velvar;
		pVector m_psize;
		pVector m_color0;
		pVector m_color1;
		pVector m_radius;
		pVector m_radiusvar;

#ifndef P_DISABLE_3D
		pPBuffer *m_pb_pos[2];
		pPBuffer *m_pb_vel[2];
		
		unsigned int m_pb_pos_tex;
		unsigned int m_pb_vel_tex;

		pRenderVertexBuffer *m_rva_pos;
		pRenderVertexBuffer *m_rva_vel;
#endif

#if 0 // P_SUPPORT_CG
		static int s_ps_refcount;
		
		static //*CGprogram s_ps_prog_pos;
		static //*CGparameter s_ps_elapsed_time_pos;

		static //*CGprogram s_ps_prog_vel;
		static //*CGparameter s_ps_elapsed_time_vel;
		static //*CGparameter s_ps_veldamp_vel;
		static //*CGparameter s_ps_rotfact_vel;

		static //*CGprogram s_ps_prog_vert;
		static //*CGparameter s_ps_modelview_vert;
		static //*CGparameter s_ps_modelviewproj_vert;
		static //*CGparameter s_ps_color0_vert;
		static //*CGparameter s_ps_color1_vert;
		static //*CGparameter s_ps_fade_vert;
		static //*CGparameter s_ps_psize_vert;
#endif
		
		//! Default constructor.
		pROParticleSystemGPU();

		//! Destructor.
		virtual ~pROParticleSystemGPU();
		
		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROParticleSystemGPU(const pROParticleSystemGPU& in);

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROParticleSystemGPU(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);
		void reset();

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

		//! Setup p-buffer intial state
		void setup_pbuffer();
};

//! Render Object Mesh Class Descriptor
/*!
	It is a descriptor to pROParticleSystemGPU classes and is used, mainly, in objects
	building process.
*/
class pROParticleSystemGPU_desc : public pClassDesc
{
	public:
		//! Creates a new mesh object.
		/*! 
			@return a pointer to the new mesh object
		*/
		void *create()	const { return new pROParticleSystemGPU; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "particle_system_gpu"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_PARTICLE_SYSTEM_GPU; }
};

#endif
#endif