/*! \file */
#ifndef PLINESEGMENT_H
#define PLINESEGMENT_H

//! Line Segment class
/*!
	This class implements a line segment formed by to extremities points: start
	and end.
*/
class P3D_API pLineSegment
{
	public:
		pVector start;	//!< start point
		pVector end;	//!< end point


	//! Default constructor.
	pLineSegment() :
		start(0),
		end(0)
	{ }

	//! Copy-constructor.
	/*!
		@param in the new line segment
	*/
	pLineSegment(const pLineSegment& in) :
		start(in.start),
		end(in.end)
	{ }

	//! Initialization constructor.
	/*!
		Defines a new line segment given by another line segment and a transformation
		@param in a line segment
		@param m a transformation
	*/
	pLineSegment(const pLineSegment& in,const pMatrix& m) :
		start(in.start*m),
		end(in.end*m)
	{ }

	//! Assignment operator.
	/*!
		@param in the new line segment
	*/
	void operator=(const pLineSegment& in)
	{
		start=in.start;
		end=in.end;
	}

	//! Calculates the distance between a line segment and a pt point.
	/*!
		@param pt a point
		@return the distance between a line segment and pt
	*/
	float distance(const pVector& pt) const
	{
		pVector v1(pt-start);
		pVector v2(pt-end);
		pVector r(end-start);

		float dot=VECDOT(v1,r);
		if (dot<0)
			return v1.length();
		else
		if (VECDOT(v2,r)>0)
			return v2.length();
		else
		{
			r.normalize();
			dot=VECDOT(v1,r);
			return (v1-r*dot).length();
		}
	}

	//! Calculates the square distance between two line segments.
	/*!
		@param ls another line segment
		@return the square distance between two line segments
	*/
	float distance2(const pLineSegment& ls) const;

	//! Calculates the distance between two line segments.
	/*!
		@param ls another line segment
		@return the distance between two line segments
	*/
	float distance(const pLineSegment& ls) const;

	//! Calculates the square distance between a line segment and an oriented bounding box.
	/*!
		@param obb an oriented bounding box
		@return the square distance between a line segment and an oriented bounding box
	*/
	float distance2(const pOrientedBoundBox& obb) const;
	
	//! Calculates the distance between a line segment and an oriented bounding box.
	/*!
		@param obb an oriented bounding box
		@return the distance between a line segment and an oriented bounding box
	*/
	float distance(const pOrientedBoundBox& obb) const;

	//! Test if line segment is inside bounding box bb.
	/*!
		@param bb a bounding box
		@return true if line segment is inside bb and false otherwise
	*/
	bool is_inside(const pBoundBox& bb) const
	{
		pVector dir=end-start;
		float len=dir.length();
		dir*=1.0f/len;

		float t1,t2;
		int i=bb.ray_intersect(start,dir,t1,t2);
		if (i==-1)
			return false;
		
		if (t1<0) t1=t2;
		if (t1<len) return true;

		return false;
	}

	//! Test if line segment is inside oriented bounding box obb.
	/*!
		@param obb an oriented bounding box
		@return true if line segment is inside obb and false otherwise
	*/
	bool is_inside(const pOrientedBoundBox& obb) const
	{
		pMatrix m;
		obb.transform.get_affine_inverse(m);
		
		pLineSegment l(*this,m);

		return l.is_inside(obb.bb);
	}

	//! Calculates the square distance between two line segments.
	/*!
		Parameters t1 and t2 holds parametric values to respective nearest points
		between ls1 and ls2.
		@param ls1 first line segment
		@param ls2 second line segment
		@param t1 parametric value of first line segment
		@param t2 parametric value of second line segment
		@return the square distance between two line segments
	*/
	static float distance2(const pLineSegment& ls1,const pLineSegment& ls2,float& t1,float& t2);

	//! Calculates the distance between two line segments.
	/*!
		Parameters t1 and t2 holds parametric values to respective nearest points
		between ls1 and ls2.
		@param ls1 first line segment
		@param ls2 second line segment
		@param t1 parametric value of first line segment
		@param t2 parametric value of second line segment
		@return the distance between two line segments
	*/
	static float distance(const pLineSegment& ls1,const pLineSegment& ls2,float& t1,float& t2);

	//! Calculates the square distance between a line segment and an oriented bounding box.
	/*!
		Parameters lt and (ot1,ot2,ot3) holds parametric values to respective nearest points
		between ls and obb.
		@param ls line segment
		@param obb oriented bounding box
		@param lt parametric value of line segment
		@param ot1 parametric value of oriented bounding box
		@param ot2 parametric value of oriented bounding box
		@param ot3 parametric value of oriented bounding box
		@return the square distance between a line segment and an oriented bounding box
	*/
	static float distance2(const pLineSegment& ls,const pOrientedBoundBox& obb,float& lt,float& ot1,float& ot2,float& ot3);

	//! Calculates the distance between a line segment and an oriented bounding box.
	/*!
		Parameters lt and (ot1,ot2,ot3) holds parametric values to respective nearest points
		between ls and obb.
		@param ls line segment
		@param obb oriented bounding box
		@param lt parametric value of line segment
		@param ot1 parametric value of oriented bounding box
		@param ot2 parametric value of oriented bounding box
		@param ot3 parametric value of oriented bounding box
		@return the distance between a line segment and an oriented bounding box
	*/
	static float distance(const pLineSegment& ls,const pOrientedBoundBox& obb,float& lt,float& ot1,float& ot2,float& ot3);
};

#endif
