/*! \file */
#ifndef PFRUSTUM_H
#define PFRUSTUM_H

//! Frustum class
/*!
	This class implements a view frustum, i.e, a pyramid formed by the camera
	position as vertex and limited by a plane called far plane. This entity is
	used to perform culling.
*/
class P3D_API pFrustum
{
	public:
		pVector verts[5];	//!< the frustum vertices
		pVector planes[5];	//!< the frustum planes
		int bboxindx[8][3];	//!< the frustum bounding box's vertices index

	//! Default constructor.
	pFrustum() 
	{ 
		int i;
		for (i = 0; i<5; i++) 
		{
			verts[i]=0.0f;
			planes[i]=0.0f;
			bboxindx[i][0]=0;
			bboxindx[i][1]=0;
			bboxindx[i][2]=0;
		}
	}

	//! Copy-constructor.
	/*!
		@param in the new frustum
	*/
	pFrustum(const pFrustum& in) 
	{ 
		int i;
		for (i = 0; i<5; i++) 
		{
			verts[i]=in.verts[i];
			planes[i]=in.planes[i];
			bboxindx[i][0]=in.bboxindx[i][0];
			bboxindx[i][1]=in.bboxindx[i][1];
			bboxindx[i][2]=in.bboxindx[i][2];
		}
	}

	//! Assignment operator.
	/*!
		@param in the new frustum
	*/
	void operator=(const pFrustum& in) 
	{ 
		int i;
		for (i = 0; i<5; i++) 
		{
			verts[i]=in.verts[i];
			planes[i]=in.planes[i];
			bboxindx[i][0]=in.bboxindx[i][0];
			bboxindx[i][1]=in.bboxindx[i][1];
			bboxindx[i][2]=in.bboxindx[i][2];
		}
	}

	//! Test if point p is inside the frustum.
	/*!
		@param p a given point
		@return true if p is inside the frustum and false otherwise
	*/
	bool is_inside(const pVector& p) const;

	//! Test the given bounding box against the frustum for clipping.
	/*!
		@param bbox a given bounding box
		@param nplanes number of planes to test for clipping
		@return 1 if bbox clip the frustum and false otherwise
	*/
	int clip_bbox(const pBoundBox& bbox,const int nplanes=5) const;
	
	//! Build the view frustum from position 'pos' and system given by (X,Y,Z).
	/*!
		@param pos pyramid apex (generally camera position)
		@param X x axis of the system that defines the frustum orientation
		@param Y y axis of the system that defines the frustum orientation
		@param Z z axis of the system that defines the frustum orientation
		@param camangle fovy of the frustum (in degrees)
		@param aspect aspect ratio
		@param farplane the plane that limits the pyramid
	*/
	void build(
		const pVector& pos,
		const pVector& X,const pVector& Y,const pVector& Z,
		float camangle,float aspect,float farplane);
	
	//! Draw the view frustum.
	void draw() const;
};

#endif
