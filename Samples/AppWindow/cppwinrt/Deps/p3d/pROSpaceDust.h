/*! \file */

#ifndef PROSPACEDUST_H
#define PROSPACEDUST_H

//! Render Object Space Dust class
/*!
	This class implements a tilable gourp of points in space 
	to represent space dust.
*/
class P3D_API pROSpaceDust : public pRenderObject
{
	public:
		int m_count;
		float m_size;
		float m_pointsize;
		float m_linewidth;
		pVector m_color;
		pVector m_lastcampos;
		int m_line;
		float m_line_scale;
		int m_initflag;
		pArray<pVector> m_points;

		//! Default constructor.
		pROSpaceDust() :
			m_count(250),
			m_size(250),
			m_pointsize(2),
			m_linewidth(1),
			m_color(1),
			m_lastcampos(0),
			m_line(1),
			m_initflag(0),
			m_line_scale(1)
		{ 
			m_type=TYPE_RO_SPACE_DUST; 
		}

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROSpaceDust(const pROSpaceDust& in) :
			pRenderObject(in),
			m_count(in.m_count),
			m_size(in.m_size),
			m_pointsize(in.m_pointsize),
			m_linewidth(in.m_linewidth),
			m_color(in.m_color),
			m_lastcampos(in.m_lastcampos),
			m_line(in.m_line),
			m_points(in.m_points),
			m_initflag(in.m_initflag),
			m_line_scale(in.m_line_scale)
		{ }
		
		//! Destructor.
		virtual ~pROSpaceDust()
		{ }

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROSpaceDust(*this); }

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
		//! Draws this object after all others.
		void post_draw();

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
};

//! Render Object Panorama Class Descriptor
/*!
	It is a descriptor to pROSpaceDust classes and is used, mainly, in objects
	building process.
*/
class pROSpaceDust_desc : public pClassDesc
{
	public:
		//! Creates a new panorama object.
		/*! 
			@return a pointer to the new panorama object
		*/
		void *create() const { return new pROSpaceDust; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "spacedust"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_SPACE_DUST; }
};

#endif
