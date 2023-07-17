/*! \file */

#ifndef PROPARTICLESYSTEM_H
#define PROPARTICLESYSTEM_H

//! Color Particle class
/*! 
	This class implements a particle that has colour and transparency.
*/
class P3D_API pColorParticle
{	
	public:
		pVector m_pos,		//!< particle position
			    m_vel;		//!< particle velocity
		float m_life;		//!< particle life in seconds
		float m_time;       //!< particle time in seconds

		pVector m_color;	//!< the particle color
		float m_size;		//!< the particle size

		int m_rotflag;		//!< rotation bit flag (0:no rot, 1:constant rot, 2:linear rotation)
		pVector m_rotconst;	//!< constant rotation
		pVector m_rotlin;	//!< linear rotation

		pMesh *m_mesh;		//!< mesh associated to this particle

		//! Default constructor.
		pColorParticle() :
			m_pos(0,0,0),
			m_vel(0,0,0),
			m_life(0),
			m_time(0),
			m_color(1),
			m_size(5),
			m_rotflag(0),
			m_rotconst(0),
			m_rotlin(0),
			m_mesh(0)
		{ }

		//! Assignment operator.
		/*!
			@param in the new color particle
		*/
		void operator=(const pColorParticle &in)
		{
			m_pos=in.m_pos;
			m_vel=in.m_vel;
			m_life=in.m_life;
			m_time=in.m_time;
			m_color=in.m_color;
			m_size=in.m_size;
			m_rotflag=in.m_rotflag;
			m_rotconst=in.m_rotconst;
			m_rotlin=in.m_rotlin;
			m_mesh=in.m_mesh;
		}

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It is called once per frame, moves the particle for the time elapsed since the
			last frame.
			@param elapsed_time elapsed time in seconds
		*/
		void step(const float elapsed_time);

		//! OpenGL drawing function, is called whenever the engine's camera can see the object
		/*!
			If m is not NULL, m will be the particle representation. The viewalign is a flag,
			if it equals 1 all particles always faces toward the eye and are always aligned with
			the screen.
			@param m the particle representation
			@param viewalign view aligned flag
		*/
		void draw(float s,float t);
		void draw_viewalign(float s,float t);

		void draw_velalign(float s,float t,int m_viewalign);
		void update_transform(const pVector& pos,const pVector& axis,pMatrix& m_transform,int m_viewalign);
};

//! Render Object Particle System class
/*!
	This class implements a particle system. Always that a particle dies, it
	is again created by the sender.
*/
class pROParticleSystem : public pRenderObject
{
	public:
		int m_enabled;			//!< is particle system enabled

		pVector	m_color,		//!< the emmited particles' color
				m_colorf,		//!< the final particles' color
				m_colorvar;		//!< variation of the emmited particles' color
		pPeriodicFunc m_func;	//!< function to changer color
		
		float m_radius,			//!< the emmited particles' radius
			  m_radiusvar,		//!< variation of the emmited particles' radius
			  m_speed,			//!< the emmited particles' speed
			  m_speedvar,		//!< variation of the emmited particles' speed
			  m_ax,				//!< maximum random emmition angle in x
			  m_ay;				//!< maximum random emmition angle in y

		int m_velalign;			//!< align particle with velocity vector
		int m_rot;				//!< rotation flag
		pVector m_rotvel,		//!< rotation velocity in degrees/sec
				m_rotvelvar;	//!< rotation velocity variance in degrees/sec
		
		int m_num_frames;		//!< anim texture number of frames (sizex/sizey)
		float m_frame_rate;		//!< anim texture frame fate in farmes/second
		int m_loop;				//!< anim texture loop flag

		int m_texture;			//!< the emmited particles' applied texture
		int m_blendadd;			//!< additive blend mode?
		int m_viewalign;		//!< align particle to view
		int m_pointsprite;		//!< use or not point sprite?

		float m_life,			//!< life of each particle in ms
		 	  m_fade,			//!< fade time of each particle in ms
			  m_emission,		//!< duration time of particles emission
			  m_totdt;			//!< accumulated ellapsed time

		pArray<pMesh *> m_models; //!< the emmited particles' mesh

		int m_total;			//!< total number of particles to be emmited
		pCircularList<pColorParticle> m_part; //!< color particle circular buffer

		//! Default constructor.
		pROParticleSystem() :
			m_enabled(1),
			m_color(0.9f,0.9f,0.9f,1.0f),m_colorf(0.1f,0.1f,0.1f,1.0f),m_colorvar(0.1f),
			m_radius(1),m_radiusvar(0.1f),m_speed(10),m_speedvar(1),m_ax(0),m_ay(0),
			m_texture(-1),m_num_frames(0),m_frame_rate(0),m_loop(1),m_velalign(0),
			m_blendadd(0),m_viewalign(1),m_pointsprite(0),
			m_total(20),m_life(5.0f),m_fade(0.25f),m_emission(0.0f),m_totdt(0),
			m_rot(0),m_rotvel(0),m_rotvelvar(0)
		{ m_type = TYPE_RO_PARTICLE_SYSTEM; }

		//! Destructor.
		virtual ~pROParticleSystem()
		{ }

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROParticleSystem(const pROParticleSystem& in) :
			pRenderObject(in),
			m_enabled(in.m_enabled),
			m_color(in.m_color),m_colorf(in.m_colorf),m_colorvar(in.m_colorvar),m_func(in.m_func),
			m_radius(in.m_radius),m_radiusvar(in.m_radiusvar),
			m_speed(in.m_speed),m_speedvar(in.m_speedvar),m_ax(in.m_ax),m_ay(in.m_ay),
			m_blendadd(in.m_blendadd),m_viewalign(in.m_viewalign),m_pointsprite(in.m_pointsprite),
			m_texture(in.m_texture),m_num_frames(in.m_num_frames),m_frame_rate(in.m_frame_rate),m_loop(in.m_loop),
			m_models(in.m_models),m_total(in.m_total),m_life(in.m_life),m_velalign(in.m_velalign),
			m_fade(in.m_fade),m_emission(in.m_emission),m_totdt(in.m_totdt),
			m_rot(in.m_rot),m_rotvel(in.m_rotvel),m_rotvelvar(in.m_rotvelvar)
		{ }
	
		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROParticleSystem(*this); }

		//! Initializes the state of this object.
		/*!
			@param active true if this is an active object and false otherwise
		*/
		void init(bool active);

		//! Updates the object's state accordingly to elapsed time.
		/*!
			It selected active particles, updates the bounding boxe associated with
			all active particles and calls recursively step of all children.
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

		//! Translates object world by given vector
		/*!
			This is a virtual method. The default implementation adds the given translation 
			to the object's transform matrix only if object is a active root and recurse down children.
			@param t translation to be applied to world
		*/
		void translate_world(const pVector& t);

		void setup_light();
};

//! Render Object Particle System Class Descriptor
/*!
	It is a descriptor to pROParticleSystem classes and is used, mainly, in objects
	building process.
*/
class pROParticleSystem_desc : public pClassDesc
{
	public:
		//! Creates a new particle system object.
		/*! 
			@return a pointer to the new particle system object
		*/
		void *create()	const { return new pROParticleSystem; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "particle_system"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_PARTICLE_SYSTEM; }
};

#endif
