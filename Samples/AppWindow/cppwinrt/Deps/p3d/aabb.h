/*************************************************************************\

  Copyright 2007 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
   fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             GAMMA Research Group at UNC
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919)962-1749

  EMail:              {geom, tangm}@cs.unc.edu


\**************************************************************************/


#pragma once

#include "vec4d.h"

class pVertex;

namespace pColdet
{

class aabb {
public:
	vec3f _color;

	vec3f _min;
	vec3f _max;

	aabb();
	aabb(const vec3f &);

	bool collide(const aabb& b) const;
	bool collide(aabb* b);
	bool inside(const vec3f &) const;

	aabb &operator += (const vec3f &);
	aabb &operator += (const vec3d &);
	aabb &operator += (const aabb &);
	aabb &operator += (const pVertex &p);

	float width()  const { return _max[0] - _min[0]; }
	float height() const { return _max[1] - _min[1]; }
	float depth()  const { return _max[2] - _min[2]; }
	vec3f center() const { return (_min+_max)*0.5; }
	pVertex centered();
	void empty();
	void visualization();
};

};