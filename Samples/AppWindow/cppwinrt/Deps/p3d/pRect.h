/*! \file */

#ifndef PRECT_H
#define PRECT_H

//! Rect class
/*!
	Represents a 2D rectangle.
	It is presumption that in the current system of coordinates x increase from
	left to right and y increase from top to down, i.e, system coordinate origin
	is placed at top left corner.
*/
class P3D_API pRect
{
	public:
		int m_x,		
			m_y,		
			m_width,	
			m_height,
			m_translate_x, // used to scroll scissors
			m_translate_y; // used to scroll scissors

	//! Default constructor.
	pRect() :
		m_x(0),		
		m_y(0),		
		m_width(10),	
		m_height(10),
		m_translate_x(0),
		m_translate_y(0)
	{ }

	//! Copy-constructor.
	/*!
		@param in the new capsule
	*/
	pRect(const pRect& in) :
		m_x(in.m_x),		
		m_y(in.m_y),		
		m_width(in.m_width),	
		m_height(in.m_height),
		m_translate_x(in.m_translate_x),
		m_translate_y(in.m_translate_y)
	{ }

	//! Assignment operator.
	/*!
		@param in the new rect
	*/
	void operator=(const pRect& in)
	{
		m_x=in.m_x;		
		m_y=in.m_y;		
		m_width=in.m_width;	
		m_height=in.m_height;
		m_translate_x=in.m_translate_x;
		m_translate_y=in.m_translate_y;
	}

	//! Tests if (x,y) point belongs to this rect.
	/*!
		@param x point x
		@param y point y
		@return true if (x,y) point belongs to this rect and false otherwise
	*/
	bool is_inside(int x,int y) const
	{ return m_x<=x && x<=(m_x+m_width) && m_y<=y && y<=(m_y+m_height); }

	//! Calculates the intersection between two rects.
	/*!
		@param r1 a rect
		@param r2 a rect
	*/
	void intersection(const pRect& r1,const pRect& r2);
};

#endif
