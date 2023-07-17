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
/*

aabb.cpp - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "Include\Cube.h"

//#include "vec4d.h"
//#include "aabb.h"
//#include "aap.h"

#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

namespace Cube
{

aap::aap(char xyz, float p)
{
#if 0
	assert(xyz >= 0 && xyz <= 2);
	this->xyz = xyz;
	this->p = p;
#endif
}

aap::aap(const aabb &total)
{
#if 0
	vec3f center = total.center();
	char xyz = 2;

	if (total.width() >= total.height() && total.width() >= total.depth()) {
		xyz = 0;
	} else
	if (total.height() >= total.width() && total.height() >= total.depth()) {
		xyz = 1;
	}

	this->xyz = xyz;
	this->p = center[xyz];
#endif
}

float middle_xyz(char xyz, std::shared_ptr<BiVector> p1, std::shared_ptr<BiVector> p2, std::shared_ptr<BiVector> p3)
{
#if 0
	float t0, t1;

	t0 = MIN(p1[xyz], p2[xyz]);
	t0 = MIN(t0, p3[xyz]);
	t1 = MAX(p1[xyz], p2[xyz]);
	t1 = MAX(t1, p3[xyz]);
	return (t0+t1)*0.5;
#else
	return 0.5f;
#endif
}

//float middle_xyz(char xyz, const Digi::Vertex &p1, const Digi::Vertex &p2, const Digi::Vertex &p3)
//{
//	float t0, t1;
//
//	t0 = MIN(p1[xyz], p2[xyz]);
//	t0 = MIN(t0, p3[xyz]);
//	t1 = MAX(p1[xyz], p2[xyz]);
//	t1 = MAX(t1, p3[xyz]);
//	return (t0+t1)*0.5;
//}

bool aap::inside(std::shared_ptr<BiVector> mid) const
{
	//return mid[xyz] > p;

	return false;
}

bool aap::inside(std::shared_ptr<BiVector> p1, std::shared_ptr<BiVector> p2, std::shared_ptr<BiVector> p3) const
{
	//return middle_xyz(xyz, p1, p2, p3) > p;

	return false;
}

void vmin(std::shared_ptr<BiVector> a, std::shared_ptr<BiVector> b)
{
	a->m_X = MIN(a->m_X, b->m_X);
	a->m_Y = MIN(a->m_Y, b->m_Y);
	a->m_Z = MIN(a->m_Z, b->m_Z);
}

void vmax(std::shared_ptr<BiVector> a, std::shared_ptr<BiVector> b)
{
	a->m_X = MAX(a->m_X, b->m_X);
	a->m_Y = MAX(a->m_Y, b->m_Y);
	a->m_Z = MAX(a->m_Z, b->m_Z);
}

void aabb::empty()
{
	_max->m_X = FLT_MIN;
	_max->m_Y = FLT_MIN;
	_max->m_Z = FLT_MIN;
	_min->m_X = FLT_MAX;
	_min->m_Y = FLT_MAX;
	_min->m_Z = FLT_MAX;
}

aabb::aabb()
{
	std::string f_ref_CurrentPath = g_ref_global_start + "aabb::aabb";

	ag_StatusLive(f_ref_CurrentPath, "_min");
	_min = std::make_shared<BiVector>();
	ag_StatusLive(f_ref_CurrentPath, "_max");
	_max = std::make_shared<BiVector>();
	ag_StatusLive(f_ref_CurrentPath, "_center");
	_center = std::make_shared<BiVector>();

	empty();

#ifdef CUBE_AABB_USE_COLOR
	_color = BiVector(frand48(), frand48(), frand48());
#endif
}

#if 1
aabb &aabb::operator += (const std::shared_ptr<BiVector> &p)
{
	_min->m_X = MIN(_min->m_X, p->m_X);
	_min->m_Y = MIN(_min->m_Y, p->m_Y);
	_min->m_Z = MIN(_min->m_Z, p->m_Z);
	_max->m_X = MAX(_max->m_X, p->m_X);
	_max->m_Y = MAX(_max->m_Y, p->m_Y);
	_max->m_Z = MAX(_max->m_Z, p->m_Z);
	return *this;
}

void aabb::acAdd_vector(std::shared_ptr<BiVector> p)
{
	_min->m_X = MIN(_min->m_X, p->m_X);
	_min->m_Y = MIN(_min->m_Y, p->m_Y);
	_min->m_Z = MIN(_min->m_Z, p->m_Z);
	_max->m_X = MAX(_max->m_X, p->m_X);
	_max->m_Y = MAX(_max->m_Y, p->m_Y);
	_max->m_Z = MAX(_max->m_Z, p->m_Z);
}
#else
aabb &aabb::operator += (const BiVector &p)
{
	vmin(_min, p);
	vmax(_max, p);
	return *this;
}
#endif

aabb &aabb::operator += (const aabb &b)
{
	vmin(_min, b._min);
	vmax(_max, b._max);
	return *this;
}

bool aabb::collide(const aabb& b) const
{
	if (_min->m_X > b._max->m_X) return false;
	if (_min->m_Y > b._max->m_Y) return false;
	if (_min->m_Z > b._max->m_Z) return false;

	if (_max->m_X < b._min->m_X) return false;
	if (_max->m_Y < b._min->m_Y) return false;
	if (_max->m_Z < b._min->m_Z) return false;

	return true;
}

bool aabb::isin(std::shared_ptr<aabb> b)
{
	if (b->_min->m_X < _min->m_X || b->_min->m_X > _max->m_X) return false;
	if (b->_min->m_Y < _min->m_Y || b->_min->m_Y > _max->m_Y) return false;
	if (b->_min->m_Z < _min->m_Z || b->_min->m_Z > _max->m_Z) return false;

	if (b->_max->m_X < _min->m_X || b->_max->m_X > _max->m_X) return false;
	if (b->_max->m_Y < _min->m_Y || b->_max->m_Y > _max->m_Y) return false;
	if (b->_max->m_Z < _min->m_Z || b->_max->m_Z > _max->m_Z) return false;

	return false;
}

bool aabb::collide(std::shared_ptr<aabb> b)
{
	if (_min->m_X > b->_max->m_X) return false;
	if (_min->m_Y > b->_max->m_Y) return false;
	if (_min->m_Z > b->_max->m_Z) return false;

	if (_max->m_X < b->_min->m_X) return false;
	if (_max->m_Y < b->_min->m_Y) return false;
	if (_max->m_Z < b->_min->m_Z) return false;

	return true;
}

bool aabb::inside(std::shared_ptr<BiVector> p)
{
	if (p->m_X < _min->m_X || p->m_X > _max->m_X) return false;
	if (p->m_Y < _min->m_Y || p->m_Y > _max->m_Y) return false;
	if (p->m_Z < _min->m_Z || p->m_Z > _max->m_Z) return false;

	return true;
}

std::shared_ptr<BiVector> aabb::center(void)
{
	_center->m_X = (_min->m_X + _max->m_X) * 0.5;
	_center->m_Y = (_min->m_Y + _max->m_Y) * 0.5;
	_center->m_Z = (_min->m_Z + _max->m_Z) * 0.5;

	return _center;
}

float aabb::volume(void)
{
	float f_Volume = width() * height() * depth();

	return f_Volume;
}

std::shared_ptr<BiVector> aabb::centered(void)
{
	return center();
}

#ifdef CUBE_AABB_USE_COLOR
void aabb::visualization()
{
	glColor3f(_color[0], _color[1], _color[2]);
	glPushMatrix();
	vec3f org = center();
	glTranslatef(org[0], org[1], org[2]);
	glScalef(width(), height(), depth());
	glutWireCube(1.f);
	glPopMatrix();
}
#endif

};