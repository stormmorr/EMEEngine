/*! \file */

#ifndef PICONGRIDINFO_H
#define PICONGRIDINFO_H

//! Icon Grid Info class
/*!
	This class implements a container of several textures that can represent,
	for example, textures to all states of a button.
*/
class pIconGridInfo
{
	public:
		int m_grid_pic;		//!< icon grid texture id
		int m_icon_width;	//!< width of all icons into grid
		int m_icon_height;	//!< height of all icons into grid

	//! Default constructor.
	pIconGridInfo() :
		m_grid_pic(-1),
		m_icon_width(16),
		m_icon_height(16)
	{ }

	//! Copy-constructor.
	pIconGridInfo(const pIconGridInfo& in) :
		m_grid_pic(in.m_grid_pic),
		m_icon_width(in.m_icon_width),
		m_icon_height(in.m_icon_height)
	{ }

	//! Calculates texture coordinate to the i-th icon.
	/*!
		@param i i-th icon
		@param u0 u texture coordinate of the botton left corner
		@param v0 v texture coordinate of the botton left corner
		@param u1 u texture coordinate of the botton left corner
		@param v1 v texture coordinate of the botton left corner
		@return true if successful and false otherwise
	*/
	bool get_icon_tex_coord(int i,float &u0,float &v0,float &u1,float &v1) const;
};

#endif
