/*! \file */

#ifndef PDUMMY_H
#define PDUMMY_H


class P3D_API pDummy
{
	public:
		pString name;
		pString params;
		pMatrix	transform;
		pVector pmin,pmax;

		pAnimation anim_pos_x;
		pAnimation anim_pos_y;
		pAnimation anim_pos_z;
		pAnimation anim_rot_x;
		pAnimation anim_rot_y;
		pAnimation anim_rot_z;

	//! Default constructor
	pDummy() :
		pmin(0),
		pmax(0)
	{
		transform.load_identity();
	}

	//! Copy-constructor
	pDummy(const pDummy& in) : 
		name(in.name),
		params(in.params),
		transform(in.transform),
		pmin(in.pmin),
		pmax(in.pmax),
		anim_pos_x(in.anim_pos_x),
		anim_pos_y(in.anim_pos_y),
		anim_pos_z(in.anim_pos_z),
		anim_rot_x(in.anim_rot_x),
		anim_rot_y(in.anim_rot_y),
		anim_rot_z(in.anim_rot_z)
	{ }

	//! Atribuition operator
	void operator=(const pDummy& in) 
	{ 
		name = in.name;
		params = in.params;
		transform = in.transform;
		pmin = in.pmin;
		pmax = in.pmax;
		anim_pos_x = in.anim_pos_x;
		anim_pos_y = in.anim_pos_y;
		anim_pos_z = in.anim_pos_z;
		anim_rot_x = in.anim_rot_x;
		anim_rot_y = in.anim_rot_y;
		anim_rot_z = in.anim_rot_z;
	}

	void write(FILE *fp) const;
	void read(pFile& fp, int ver);

	float get_maxanimtime();
	void draw();
};

#endif
