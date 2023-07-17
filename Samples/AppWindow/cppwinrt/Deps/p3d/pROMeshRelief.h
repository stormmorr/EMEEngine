/*! \file */

#ifndef PROMESHRELIEF_H
#define PROMESHRELIEF_H

//! Render Object Mesh Relief class
/*!
	This class implements an relief map effect.
	It uses a single quad with a normal/depth map.
*/

class P3D_API pROMeshRelief : public pRenderObject
{
private:
	pVector m_diff;	
	pVector m_spec;	
	
	int m_progmode;
	int m_shadows;
	int m_doubleprec;
	int m_depthcorrect;
	int m_depthbias;
	int m_borderclamp;
	int m_curved;
	int m_tile;
	float m_depth;
	
	int m_texture_color;
	int m_texture_relief;
	int m_texture_null;
	pMesh *m_mesh;

#if 0 // P_SUPPORT_CG
	pRM *m_rm;				//!< rm object
#endif

public:
	//! Default constructor.
	pROMeshRelief() :
		m_diff(1,1,1,1),
		m_spec(1,1,1,64),
		m_texture_color(-1),
		m_texture_relief(-1),
		m_texture_null(-1),
		m_progmode(0),
		m_shadows(0),
		m_depthcorrect(0),
		m_depthbias(0),
		m_borderclamp(0),
		m_doubleprec(0),
		m_curved(0),
		m_tile(1),
		m_depth(1),
		m_mesh(0)
#if 0 // P_SUPPORT_CG
		,m_rm(0)
#endif
	{
		m_type=TYPE_RO_MESH_RELIEF;
//		m_flags|=P_ROFLAGS_HASMESH;
	}

	//! Destructor.
	virtual ~pROMeshRelief()
	{ 
#if 0 // P_SUPPORT_CG
		if (m_source==0)
			delete m_rm;
#endif
	}	

	//! Copy constructor.
	/*!
		@param in the new object
	*/
	pROMeshRelief(const pROMeshRelief& in) :
		pRenderObject(in),
		m_diff(in.m_diff),
		m_spec(in.m_spec),
		m_texture_color(in.m_texture_color),
		m_texture_relief(in.m_texture_relief),
		m_texture_null(in.m_texture_null),
		m_progmode(in.m_progmode),
		m_shadows(in.m_shadows),
		m_depthcorrect(in.m_depthcorrect),
		m_depthbias(in.m_depthbias),
		m_borderclamp(in.m_borderclamp),
		m_doubleprec(in.m_doubleprec),
		m_curved(in.m_curved),
		m_tile(in.m_tile),
		m_depth(in.m_depth),
		m_mesh(in.m_mesh)
#if 0 // P_SUPPORT_CG
		,m_rm(in.m_rm)
#endif
	{ }

	//! Clone operation.
	/*!
	@returns a copy of this object
	*/
	pRenderObject* clone() const
	{ return new pROMeshRelief(*this); }

	void init(bool active);
	void step(const float elapsed_time,const pMatrix& global);	
	void draw();
	void draw_shadows(const pVector& lightpos);
	int get_custom_param_desc(int i,pParamDesc *pd);
	void on_pos_parameter_change(int i);
	void setup_light();

	pMesh *get_mesh()
	{ return m_mesh; };
};

//! Render Object Atmosphere Class Descriptor
/*!
	It is a descriptor to pROMeshRelief classes and is used, mainly, in objects
	building process.
*/
class pROMeshRelief_desc : public pClassDesc
{
	public:
		//! Creates a new atmosphere object.
		/*! 
			@return a pointer to the new atmosphere object
		*/
		void *create()	const { return new pROMeshRelief; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "mesh_relief"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_MESH_RELIEF; }
};

#endif
