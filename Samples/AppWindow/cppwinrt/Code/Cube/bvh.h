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

#include "aabb.h"
#include <vector>

#include "pMesh.h"

class pMesh;
class bvh_tree;

namespace pColdet
{

class bvh_node
{
	aabb  _box;

	unsigned int _id;
	bvh_node *_left;
	bvh_node *_right;

	bvh_tree *_tree;

public:
	bvh_node(bvh_tree *f_tree);
	bvh_node(bvh_tree *f_tree, unsigned int);
	bvh_node(bvh_tree *f_tree, unsigned int *, unsigned int, pMesh *);

	~bvh_node();
	void visualization(int level);
	void collide(bvh_node *);
	void self_collide();

	int test_triangle(unsigned int id1, unsigned int id2);
	int test_triangle(unsigned int id1, unsigned int id2, unsigned int cov, unsigned int st1, unsigned int st2);

	aabb &refit();
	aabb &refitbm();

friend class bvh_tree;
};

class bvh_tree
{
	bvh_node			*_root;
	pMesh				*_mesh;

public:
	bvh_tree(pMesh *);
	~bvh_tree();

	std::vector<unsigned int> m_rets;

	void visualization(int level);
	void collide(bvh_tree *);
	void self_collide();

	void color();
	int refit();
	int refitbm();
	bool get_contact(int i, unsigned int &id1, unsigned int &id2);
};

};