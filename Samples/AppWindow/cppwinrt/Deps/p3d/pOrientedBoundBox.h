/*! \file */

#ifndef PORIENTEDBOUNDBOX_H
#define PORIENTEDBOUNDBOX_H

//! Oriented Bounding Box class
/*!
	This class implements an oriented bounding box (OBB), which every object in the scene must have.
	The bounding box is used in collision calculations. The	OBB is defined by an AABB and a transform
	that represents its orientation.
*/
class P3D_API pOrientedBoundBox
{
	public:
		pBoundBox bb;		//!< AABB
		pMatrix transform;	//!< orientation
		pString name;		//!< name

	//! Default constructor.
	pOrientedBoundBox()
	{ }

	//! Copy-constructor.
	/*!
		@param in the new oriented bounding box
	*/
	pOrientedBoundBox(const pOrientedBoundBox& in) : 
		bb(in.bb),
		transform(in.transform),
		name(in.name)
	{ }

	//! Assignment operator.
	/*!
		@param in the new oriented bounding box
	*/
	void operator=(const pOrientedBoundBox& in)
	{
		bb=in.bb;
		transform=in.transform;
		name=in.name;
	}

	//! Test if point pt is inside the bounding box.
	/*!
		@param pt a given point
		@return true if pt is inside the bounding box and false otherwise
	*/
	bool is_inside(const pVector& pt) const
	{
		pMatrix m;
		transform.get_affine_inverse(m);
		return bb.is_inside(pt*m);
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
	int ray_intersect(const pVector& ro,const pVector& rd,float& tnear,float& tfar) const
	{
		pMatrix m;
		transform.get_affine_inverse(m);
		pVector rro = ro*m;
		pVector rrd = m.multiply_rotation(rd);
		return bb.ray_intersect(rro,rrd,tnear,tfar);
	}

	//! Calculates the square distance between an oriented bounding box and a pt point.
	/*!
		@param pt a point
		@return the square distance between an oriented bounding box and pt
	*/
	float distance2(const pVector& pt) const;

	//! Calculates the distance between an oriented bounding box and a pt point.
	/*!
		@param pt a point
		@return the distance between an oriented bounding box and pt
	*/
	float distance(const pVector& pt) const;

	//! Draw the oriented bounding box.
	void draw();

	//! Writes oriented bounding box's data into file fp.
	/*!
		@param fp a file
	*/
	void write(FILE *fp) const;

	//! Reads to memory oriented bounding box's data into file fp.
	/*!
		@param fp a file
	*/
	void read(pFile& fp,int ver);

	//! Calculates the center of oriented bounding box.
	/*!
		@return the center of oriented bounding box
	*/
	pVector get_center() const
	{ return transform*bb.get_center(); }

	//! Calculates the square distance between an oriented bounding box and a pt point.
	/*!
		Parameters (ot1,ot2,ot3) holds parametric values to respective nearest point in obb.
		@param obb oriented bounding box
		@param pt a point
		@param ot1 parametric value of oriented bounding box
		@param ot2 parametric value of oriented bounding box
		@param ot3 parametric value of oriented bounding box
		@return the square distance between an oriented bounding box and pt
	*/
	static float distance2(const pOrientedBoundBox& obb,const pVector& pt,float& ot1,float& ot2,float& ot3);

	//! Calculates the distance between an oriented bounding box and a pt point.
	/*!
		Parameters (ot1,ot2,ot3) holds parametric values to respective nearest point in obb.
		@param obb oriented bounding box
		@param pt a point
		@param ot1 parametric value of oriented bounding box
		@param ot2 parametric value of oriented bounding box
		@param ot3 parametric value of oriented bounding box
		@return the distance between an oriented bounding box and pt
	*/
	static float distance(const pOrientedBoundBox& obb,const pVector& pt,float& ot1,float& ot2,float& ot3);
};

#endif
