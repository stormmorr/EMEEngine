/*! \file */

#ifndef PROPANORAMA_H
#define PROPANORAMA_H

//! Render Object Panorama class
/*!
	This class implements an object that supports a sky box, i.e, a box whose faces
	representing the background of the scene.
*/
class P3D_API pROPanorama : public pRenderObject
{
	public:
		// Draw modes for stars
		enum
		{
			STARS_WITH_TEXTURE=0,
			STARS_WITH_GL_POINTS,
			STARS_WITH_POINT_SPRITES,
		};

		int addblend;			//!< additive blend mode
		float m_size;			//!< size of each image
		pVector m_color;		//!< color applied to the images
		
		int m_img[6];			//!< array of images that compose the panorama (in order: up, down, left, right, front, back)
		float m_tile;			//!< tile of each image
		
		pMesh *m_mesh;			//!< mesh to use as panorama (replaces the 6 images)
		int tex1;				//!< mesh panorama texture 1
		int tex2;				//!< texture used to draw stars
		float tile_u,tile_v;	//!< mesh panorama texture 2 tile factor in u and v directions
		int m_stars_flag;		//!< flag to control draw mode of stars: STARS_WITH_TEXTURE, STARS_WITH_GL_POINTS or STARS_WITH_POINT_SPRITES
		int m_sprite;			//!< texture used to point sprites
		int m_count;			//!< number of stars
		float m_size_volume;	//!< size of the volume where points will be created
		float m_point_size;		//!< size of points
		pArray<pVector> m_points;
		unsigned int m_stars;	//!< display list for points

		pMesh *m_detail_mesh;	//!< mesh to use as detail of panorama
		int m_detail_tex;		//!< texture of detail mesh

		pVector m_rot;

		//! Default constructor.
		pROPanorama() : 
			addblend(0),m_size(1000.0f),m_color(1.0f),
			m_tile(1.0f),
			m_mesh(0),tex1(-1),
			tex2(-1),m_sprite(-1),
			tile_u(2),tile_v(1),
			m_stars_flag(STARS_WITH_TEXTURE),
			m_count(250),m_size_volume(250),m_point_size(2.0f),m_stars(0),
			m_detail_mesh(0),m_detail_tex(-1),
			m_rot(0)
		{ 
			m_type=TYPE_RO_PANORAMA; 
			m_img[0]=m_img[1]=m_img[2]=m_img[3]=m_img[4]=m_img[5]=-1;
		}

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pROPanorama(const pROPanorama& in) :
			pRenderObject(in),
			addblend(in.addblend),m_size(in.m_size),m_color(in.m_color),
			m_tile(in.m_tile),
			m_mesh(in.m_mesh),tex1(in.tex1),
			tex2(in.tex2),m_sprite(in.m_sprite),
			tile_u(in.tile_u),tile_v(in.tile_v),
			m_stars_flag(in.m_stars_flag),
			m_count(in.m_count),m_size_volume(in.m_size_volume),m_point_size(in.m_point_size),
			m_points(in.m_points),
			m_detail_mesh(in.m_detail_mesh),m_detail_tex(in.m_detail_tex),
			m_rot(in.m_rot)
		{ 
			for( int i=0;i<6;i++ )
				m_img[i]=in.m_img[i];
		}

		//! Destructor.
		virtual ~pROPanorama();

		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pRenderObject* clone() const
		{ return new pROPanorama(*this); }

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

		//! Draw cube with one texture per face.
		void draw_cube();
};

//! Render Object Panorama Class Descriptor
/*!
	It is a descriptor to pROPanorama classes and is used, mainly, in objects
	building process.
*/
class pROPanorama_desc : public pClassDesc
{
	public:
		//! Creates a new panorama object.
		/*! 
			@return a pointer to the new panorama object
		*/
		void *create() const { return new pROPanorama; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "panorama"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_RO_PANORAMA; }
};

#endif
