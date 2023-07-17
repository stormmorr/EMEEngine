/*! \file */

#ifndef PCAPSULE_H
#define PCAPSULE_H

//! Capsule class
/*!
	A capsule is a cylinder that has two hemispherical caps attached at the end
	points. Mathematically, it can be defined as the set of all points that are
	distant 'radius' > 0 from a line segment.
*/
class P3D_API pCapsule
{
	public:
		pLineSegment line;	//!< line segment
		float radius;		//!< radius that defines the capsule

	//! Default constructor.
	pCapsule() :
		radius(0)
	{ }

	//! Copy-constructor.
	/*!
		@param in the new capsule
	*/
	pCapsule(const pCapsule& in) :
		line(in.line),
		radius(in.radius)
	{ }

	//! Assignment operator.
	/*!
		@param in the new capsule
	*/
	pCapsule operator=(const pCapsule& in)
	{
		line=in.line;
		radius=in.radius;
		return *this;
	}

	//! Test if point pt is inside the capsule
	/*!
		@param pt a given point
		@return true if pt is inside the capsule and false otherwise
	*/
	bool is_inside(const pVector& pt) const
	{
		if (line.distance(pt)<radius)
			return true;
		return false;
	}

	//! Calculates the center of capsule.
	/*!
		@return center of capsule
	*/
	pVector get_center() const
	{ return (line.start+line.end)*0.5f; }

	//! Draw capsule.
	/*!
		@param res how tesselated the capsule will be drawn
	*/
	void draw(const int res=32) const;
};

#endif
