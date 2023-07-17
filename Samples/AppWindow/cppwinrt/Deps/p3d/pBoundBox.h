/*! \file */

#ifndef PBOUNDBOX_H
#define PBOUNDBOX_H

//! Axis-aligned bounding box class
/*!
	This class implements an axis-aligned bounding box (AABB), which every object in the scene must have.
	The bounding box is used in collision calculations, and for the engine's aggressive view culling. The
	AABB is defined by its minimum and maximum points, and this class provides methods for testing if a given 
	point is inside the box, testing if two AABBs intersect, calculating collision and ray-intersection.
*/
class P3D_API pBoundBox
{
	public:
		pVector	min,	//!< bounding box minimum point
				max;	//!< bounding box maximum point

	static int facevert[6][4];		//!< indices of the corresponding vertices for each face
	static int edgevert[12][2];		//!< indices of the corresponding vertices for each edge
	static int edgefaces[12][2];	//!< indices of the corresponding faces for each edge
	static pVector vertnorm[8];		//!< normals of each vertex 
	static pVector edgenorm[12];	//!< normals of each edge 
	static pVector facenorm[6];		//!< normals of each face 
	static pVector facetexcoord[4];	//!< texture coordinates for each face vertex
	static pVector edgedir[12];		//!< normalized edge directions for each edge
	static pVector edgedirth[12];	//!< edgedir divided by 100
	
	//! Default constructor.
	pBoundBox()
	{ min=0.0f;	max=0.0f; }

	//! Construct a bounding box given the minimum and maximum points.
	/*!
		@param mmin minimum point
		@param mmax maximum point
	*/
	pBoundBox(const pVector& mmin,const pVector& mmax)
	{ min=mmin;	max=mmax; }

	//! Copy-constructor.
	/*!
		@param in the new bounding box
	*/
	pBoundBox(const pBoundBox& in)
	{ min=in.min; max=in.max; }

	//! Destructor.
	~pBoundBox()  
	{ }

	//! Atribuition operator.
	/*!
		@param in the new bounding box
	*/
	void operator=(const pBoundBox& in) 
	{ min=in.min; max=in.max; }

	//! Return the vertex corresponding to the given index.
	/*!
		@param ind the given index
		@return the vertex corresponding to the given index
	*/
	pVector get_vert(int ind) const 
	{
		switch(ind)
		{
		case 0: return min;
		case 1: return max;
		case 2: return pVector(max.x,min.y,min.z);
		case 3: return pVector(min.x,max.y,max.z);
		case 4: return pVector(max.x,max.y,min.z);
		case 5: return pVector(min.x,min.y,max.z);
		case 6: return pVector(min.x,max.y,min.z);
		case 7: return pVector(max.x,min.y,max.z);
		default: return pVector(0,0,0);
		}
	}
	
	//! Return the distance of the plane corresponding to the given index (0=min[x], 1=min[y], 2=min[z], 3=max[x], 4=max[y], 5=max[z]).
	/*!
		@param ind the given index
		@return the distance of the plane corresponding to the given index
	*/
	float get_plane_dist(int ind) const 
	{ return ind>2?-min[ind-3]:max[ind]; }

	//! Test if a any part of a given bound box is inside the boundbox.
	/*!
		@param bbmin minimum point of the given bounding box
		@param bbmax maximum point of the given bounding box
		@return true if a any part of a given bound box is inside the boundbox and false otherwise
	*/
	bool clip_bbox(const pVector& bbmin,const pVector& bbmax) const
	{
		if (max.x>=bbmin.x && min.x<=bbmax.x &&
			max.y>=bbmin.y && min.y<=bbmax.y &&
			max.z>=bbmin.z && min.z<=bbmax.z)
			return true;
		return false;
	}

	//! Test if a any part of a given bound box is inside the boundbox.
	/*!
		@param bb the given bounding box
		@return true if a any part of a given bound box is inside the boundbox and false otherwise
	*/
	bool is_inside(const pBoundBox& bb) const
	{
		if (max.x>=bb.min.x && min.x<=bb.max.x &&
			max.y>=bb.min.y && min.y<=bb.max.y &&
			max.z>=bb.min.z && min.z<=bb.max.z)
			return true;
		return false;
	}

	//! Test if point p is inside the bounding box
	/*!
		@param p a given point
		@return true if p is inside the bounding box and false otherwise
	*/
	bool is_inside(const pVector& p) const 
	{
		return	p.x>=min.x && p.x<=max.x &&
				p.y>=min.y && p.y<=max.y &&
				p.z>=min.z && p.z<=max.z;
	}
	
	//! Test if point f is inside the  bounding box
	/*!
		@param f a given point where (f[0]=x, f[1]=y and f[2]=z)
		@return true if p is inside the bounding box and false otherwise
	*/
	bool is_inside(const float *f) const 
	{
		return	f[0]>=min.x && f[0]<=max.x &&
				f[1]>=min.y && f[1]<=max.y &&
				f[2]>=min.z && f[2]<=max.z;
	}

	//! Collide ray defined by ray origin (ro) and ray direction (rd) with the bounding box
	/*!
		Distances to the collision points are stored in tnear and tfar.
		@param ro ray origin
		@param rd ray direction
		@param tnear distance to nearest collision point
		@param tfar distance to farthest collision point
		@return -1 on no collision and the face index for first intersection if a collision is found
	*/
	int ray_intersect(const pVector& ro,const pVector& rd,float& tnear,float& tfar) const;

	//! Collide edge (p1,p2) moving in direction dir with edge (p3,p4).
	/*!
		@param p1 start point of first edge
		@param p2 end point of first edge
		@param dir movement direction of first edge
		@param p3 start point of second edge
		@param p4 end point of second edge
		@param dist distance to collision point
		@param ip intersection point
		@return 1 if a collision is found and 0 otherwise
	*/
	int edge_collision(const pVector& p1,const pVector& p2,const pVector& dir,const pVector& p3,const pVector& p4,float& dist,pVector& ip) const;
	
	//! Collide the bounding box moving in the direction dir with movement magnitude (len) with another bounding box (bbox)
	/*!
		@param bbox another bounding box
		@param dir movement normalized direction
		@param len movement magnitude
		@param normal intersection normal
		@param ip intersection point
		@return 1 if a collision is found and 0 otherwise
	*/
	int collide(const pBoundBox& bbox,const pVector& dir,float& len,pVector& normal,pVector& ip) const;
	
	int collide(pMesh *m,const pVector& p,const pVector& dir,float& len,pVector& ip,pVector& n) const;
	int collide(pMesh *m,const pMatrix& rot, const pVector& p,const pVector& dir,float& len,pVector& ip,pVector& n) const;

	//! Reset all data.
	void reset() 
	{ min.vec(BIG,BIG,BIG); max.vec(-BIG,-BIG,-BIG); }

	//! Add a point to the bounding box (expand its boundaries if necessary).
	/*!
		@param p point
	*/
	void add_point(const pVector &p);
	
	//! Add a point (3 floats) to the bounding box (expand its boundaries if necessary).
	/*!
		@param p point (3 floats)
	*/
	void add_point(const float *p);

	//! Add another box to the bounding box (expand its boundaries if necessary).
	/*!
		@param b another bounding box 
	*/
	void add_bbox(const pBoundBox& b);
	
	//! Add another box with tranformations (translate/rotate) to the bounding box (expand its boundaries if necessary).
	/*!
		@param b another bounding box 
		@param m bounding box's transformation
	*/
	void add_bbox(const pBoundBox& b,const pMatrix& m);

	//! Draw boundbox as lines.
	void draw() const;

	//! Calculates bounding box center point.
	/*!
		@return bounding box center point
	*/
	pVector get_center() const
	{ return (min+max)*0.5f; }

	//! Given a face, retrieves vertex indices that each face share.
	/*!
		@param face a given face
		@param verts vertex indices that each face share
	*/
	void get_face_verts(const int face,int verts[4]) const;

	//! Given an edge, retrieves vertex indices that each edge share.
	/*!
		@param edge a given edge
		@param verts vertex indices that each edge share
	*/
	void get_edge_verts(const int edge,int verts[2]) const;

	//! Given an edge, retrieves faces that each edge share.
	/*!
		@param edge a given edge
		@param faces faces that each edge share
	*/
	void get_edge_faces(const int edge,int faces[2]) const;

	//! Given an edge, retrieves the correspondent normalized edge vectors.
	/*!
		@param edge a given edge
		@return normalized edge vectors
	*/
	pVector get_edge_dir(const int edge) const;

	//! Given an edge, retrieves the correspondent normalized edge vectors divided by 100.
	/*!
		@param edge a given edge
		@return normalized edge vectors divided by 100
	*/
	pVector get_edge_dir_th(const int edge) const;

	//! Given a vertex, retrieves the correspondent normal.
	/*!
		@param vert a given vertex
		@return vertex normal
	*/
	pVector get_vert_normal(const int vert) const;

	//! Given an edge, retrieves the correspondent normal.
	/*!
		@param edge a given edge
		@return edge normal
	*/
	pVector get_edge_normal(const int edge) const;

	//! Given a face, retrieves the correspondent normal.
	/*!
		@param face a given face
		@return face normal
	*/
	pVector get_face_normal(const int face) const;
	
	//! Calculates bounding box diagonal vector.
	/*!
		@return bounding box diagonal vector
	*/
	pVector get_diagonal() const
	{ return max-min; }

	//! Writes bounding box's data into file fp.
	/*!
		@param fp a file
	*/
	void write(FILE *fp) const;

	//! Reads to memory bounding box's data into file fp.
	/*!
		@param fp a file
	*/
	void read(pFile& fp,int ver);
};

#endif
