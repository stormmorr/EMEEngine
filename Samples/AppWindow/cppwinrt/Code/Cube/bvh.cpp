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

#include "pch.h"

#include <stdlib.h>
#include <assert.h>

#include "paralelo3d.h"

extern float middle_xyz(char xyz, const vec3d &p1, const vec3d &p2, const vec3d &p3);
extern float middle_xyz(char xyz, const pVertex &p1, const pVertex &p2, const pVertex &p3);

#define IsLeaf(node) (node->_left == NULL)

namespace pColdet
{

FILE *m_File;

bvh_tree::bvh_tree(pMesh *f_Mesh)
{
	aabb total;
	for (unsigned int i=0; i<f_Mesh->nvert; i++)
		total += f_Mesh->vert[i];

	//m_File = fopen("bvh_tree.trc", "w");

	assert(f_Mesh->_tri_boxes == NULL);
	assert(f_Mesh->_tri_centers == NULL);

	f_Mesh->_tri_boxes = new aabb[f_Mesh->nface];
	f_Mesh->_tri_centers = new vec3f[f_Mesh->nface];

	aap pln(total);

	//fprintf(m_File, "aap pln.xyz %i pln.p %f\n", pln.xyz, pln.p);

	unsigned int *idx_buffer = new unsigned int[f_Mesh->nface];
	unsigned int left_idx = 0, right_idx = f_Mesh->nface;

	//fprintf(m_File, "NEW BVH_TREE m_Tricount %i right_idx %i\n", mdl->m_Tricount, right_idx);

	//fclose(m_File);

	for (unsigned int i=0; i<f_Mesh->nface; i++) {
		pVertex &p1 = f_Mesh->vert[f_Mesh->face[i].vertindx];
		pVertex &p2 = mdl->vec_Vert[mdl->vec_Face[i].m_v2];
		pVertex &p3 = mdl->vec_Vert[mdl->vec_Face[i].m_v3];

		mdl->_tri_centers[i][0] = middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i][1] = middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i][2] = middle_xyz(2, p1, p2, p3);

		//fprintf(m_File, "mdl->_tri_centers[i] %f %f %f\n", mdl->_tri_centers[i][0], mdl->_tri_centers[i][1], mdl->_tri_centers[i][2]);
		//fprintf(m_File, "pln.inside(mdl->_tri_centers[i]) = %i\n", pln.inside(mdl->_tri_centers[i]));

		if (pln.inside(mdl->_tri_centers[i]))
			{
			idx_buffer[left_idx++] = i;
			//fprintf(m_File, "p3 i %i left_idx %i\n", i, left_idx);
			}
		else
			{
			idx_buffer[--right_idx] = i;
			//fprintf(m_File, "p3 i %i right_idx %i\n", i, right_idx);
			}

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	if(left_idx == 0)
		{
		printf("DigiMass:::new bvh_tree ERROR DigiModel face centers are alligned centrally FIX rotate mesh 90 degrees\n");
		for(;;) {}
		}

	_root = new bvh_node(this);
	_root->_box = total;
	_root->_left = new bvh_node(this, idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(this, idx_buffer+left_idx, mdl->m_Tricount-left_idx, mdl);
	_mdl = mdl;

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;

	delete [] idx_buffer;
}

bvh_tree::bvh_tree(digiDataMesh *mdl)
{
	aabb total;
	for (unsigned int i=0; i<mdl->m_Vtxcount; i++)
		total += mdl->vec_Vert[i];

	//m_File = fopen("bvh_tree.trc", "w");

	assert(mdl->_tri_boxes == NULL);
	assert(mdl->_tri_centers == NULL);

	mdl->_tri_boxes = new aabb[mdl->m_Tricount];
	mdl->_tri_centers = new vec3f[mdl->m_Tricount];

	aap pln(total);

	//printf("aap pln.xyz %i pln.p %f\n", pln.xyz, pln.p);

	unsigned int *idx_buffer = new unsigned int[mdl->m_Tricount];
	unsigned int left_idx = 0, right_idx = mdl->m_Tricount;

	//printf("NEW BVH_TREE m_Tricount %i right_idx %i\n", mdl->m_Tricount, right_idx);

	//fclose(m_File);

	for (unsigned int i=0; i<mdl->m_Tricount; i++) {
		Digi::Vertex &p1 = mdl->vec_Vert[mdl->vec_Face[i].m_v1];
		Digi::Vertex &p2 = mdl->vec_Vert[mdl->vec_Face[i].m_v2];
		Digi::Vertex &p3 = mdl->vec_Vert[mdl->vec_Face[i].m_v3];

		mdl->_tri_centers[i][0] = middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i][1] = middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i][2] = middle_xyz(2, p1, p2, p3);

		//fprintf(m_File, "mdl->_tri_centers[i] %f %f %f\n", mdl->_tri_centers[i][0], mdl->_tri_centers[i][1], mdl->_tri_centers[i][2]);
		//fprintf(m_File, "pln.inside(mdl->_tri_centers[i]) = %i\n", pln.inside(mdl->_tri_centers[i]));

		if (pln.inside(mdl->_tri_centers[i]))
			{
			idx_buffer[left_idx++] = i;
			//fprintf(m_File, "p3 i %i left_idx %i\n", i, left_idx);
			}
		else
			{
			idx_buffer[--right_idx] = i;
			//fprintf(m_File, "p3 i %i right_idx %i\n", i, right_idx);
			}

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	if(left_idx == 0)
		{
		printf("DigiMass:::new bvh_tree ERROR DigiModel face centers are alligned centrally FIX rotate mesh 90 degrees\n");
		for(;;) {}
		}

	_root = new bvh_node(this);
	_root->_box = total;
	_root->_left = new bvh_node(this, idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(this, idx_buffer+left_idx, mdl->m_Tricount-left_idx, mdl);
	_mesh = mdl;

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;

	delete [] idx_buffer;
}

bvh_tree::bvh_tree(digiShellMesh *mdl)
{
	aabb total;

	printf("trace %i %i\n", mdl->m_Vtxcount, mdl->vec_Vert[0].size());

	for (unsigned int i=0; i < mdl->m_Vtxcount; i++)
		total += mdl->vec_Vert[0][i];

	//m_File = fopen("bvh_tree.trc", "w");

	assert(mdl->_tri_boxes == NULL);
	assert(mdl->_tri_centers == NULL);

	mdl->_tri_boxes = new aabb[mdl->m_Tricount];
	mdl->_tri_centers = new vec3f[mdl->m_Tricount];

	aap pln(total);

	//printf("aap pln.xyz %i pln.p %f\n", pln.xyz, pln.p);

	unsigned int *idx_buffer = new unsigned int[mdl->m_Tricount];
	unsigned int left_idx = 0, right_idx = mdl->m_Tricount;

	//printf("NEW BVH_TREE m_Tricount %i right_idx %i\n", mdl->m_Tricount, right_idx);

	//fclose(m_File);

	for (unsigned int i=0; i<mdl->m_Tricount; i++) {
		Digi::Vertex &p1 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v1];
		Digi::Vertex &p2 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v2];
		Digi::Vertex &p3 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v3];

		mdl->_tri_centers[i][0] = middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i][1] = middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i][2] = middle_xyz(2, p1, p2, p3);

		//fprintf(m_File, "mdl->_tri_centers[i] %f %f %f\n", mdl->_tri_centers[i][0], mdl->_tri_centers[i][1], mdl->_tri_centers[i][2]);
		//fprintf(m_File, "pln.inside(mdl->_tri_centers[i]) = %i\n", pln.inside(mdl->_tri_centers[i]));

		if (pln.inside(mdl->_tri_centers[i]))
			{
			idx_buffer[left_idx++] = i;
			//fprintf(m_File, "p3 i %i left_idx %i\n", i, left_idx);
			}
		else
			{
			idx_buffer[--right_idx] = i;
			//fprintf(m_File, "p3 i %i right_idx %i\n", i, right_idx);
			}

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	if(left_idx == 0)
		{
		printf("DigiMass:::new bvh_tree ERROR DigiModel face centers are alligned centrally FIX rotate mesh 90 degrees\n");
		for(;;) {}
		}

	_root = new bvh_node(this);
	_root->_box = total;
	_root->_left = new bvh_node(this, idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(this, idx_buffer+left_idx, mdl->m_Tricount-left_idx, mdl);
	_meshsh = mdl;

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;

	delete [] idx_buffer;
}

bvh_tree::bvh_tree(digiBodyMesh *mdl)
{
	aabb total;

	printf("trace %i %i\n", mdl->m_Vtxcount, mdl->vec_Vert[0].size());

	for (unsigned int i=0; i < mdl->m_Vtxcount; i++)
		total += mdl->vec_Vert[0][i];

	//m_File = fopen("bvh_tree.trc", "w");

	assert(mdl->_tri_boxes == NULL);
	assert(mdl->_tri_centers == NULL);

	mdl->_tri_boxes = new aabb[mdl->m_Tricount];
	mdl->_tri_centers = new vec3f[mdl->m_Tricount];

	aap pln(total);

	//printf("aap pln.xyz %i pln.p %f\n", pln.xyz, pln.p);

	unsigned int *idx_buffer = new unsigned int[mdl->m_Tricount];
	unsigned int left_idx = 0, right_idx = mdl->m_Tricount;

	//printf("NEW BVH_TREE m_Tricount %i right_idx %i\n", mdl->m_Tricount, right_idx);

	//fclose(m_File);

	for (unsigned int i=0; i<mdl->m_Tricount; i++) {
		Digi::Vertex &p1 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v1];
		Digi::Vertex &p2 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v2];
		Digi::Vertex &p3 = mdl->vec_Vert[0][mdl->vec_Face[0][i].m_v3];

		mdl->_tri_centers[i][0] = middle_xyz(0, p1, p2, p3);
		mdl->_tri_centers[i][1] = middle_xyz(1, p1, p2, p3);
		mdl->_tri_centers[i][2] = middle_xyz(2, p1, p2, p3);

		//fprintf(m_File, "mdl->_tri_centers[i] %f %f %f\n", mdl->_tri_centers[i][0], mdl->_tri_centers[i][1], mdl->_tri_centers[i][2]);
		//fprintf(m_File, "pln.inside(mdl->_tri_centers[i]) = %i\n", pln.inside(mdl->_tri_centers[i]));

		if (pln.inside(mdl->_tri_centers[i]))
			{
			idx_buffer[left_idx++] = i;
			//fprintf(m_File, "p3 i %i left_idx %i\n", i, left_idx);
			}
		else
			{
			idx_buffer[--right_idx] = i;
			//fprintf(m_File, "p3 i %i right_idx %i\n", i, right_idx);
			}

		mdl->_tri_boxes[i] += p1;
		mdl->_tri_boxes[i] += p2;
		mdl->_tri_boxes[i] += p3;
	}

	if(left_idx == 0)
		{
		printf("DigiMass:::new bvh_tree ERROR DigiModel face centers are alligned centrally FIX rotate mesh 90 degrees\n");
		for(;;) {}
		}

	_root = new bvh_node(this);
	_root->_box = total;
	_root->_left = new bvh_node(this, idx_buffer, left_idx, mdl);
	_root->_right = new bvh_node(this, idx_buffer+left_idx, mdl->m_Tricount-left_idx, mdl);
	_meshgm = mdl;

	delete [] mdl->_tri_boxes;
	delete [] mdl->_tri_centers;
	mdl->_tri_boxes = NULL;
	mdl->_tri_centers = NULL;

	delete [] idx_buffer;
}

bvh_tree::~bvh_tree()
{
	delete _root;
}

void
bvh_tree::visualization(int level)
{
	_root->visualization(level);
}

void
bvh_tree::setmeshbm(digiBodyMesh *f_meshbm)
{
	_meshgm = f_meshbm;
}

static int s_num_leaf;
static DigiModel *s_mdl;
static digiShellMesh *s_mdlsh;
static digiBodyMesh *s_mdlgm;

int
bvh_tree::refit()
{
	s_num_leaf = 0;
	s_mdl = _mdl;

	_root->refit();

	return s_num_leaf;
}

int
bvh_tree::refitbm()
{
	s_num_leaf = 0;
	s_mdlgm = _meshgm;

	_root->refitbm();

	return s_num_leaf;
}

//#################################################################

bvh_node::bvh_node(bvh_tree *f_tree)
{
	_id = UINT_MAX;
	_left = _right = NULL;
	_tree = f_tree;
}

bvh_node::~bvh_node()
{
	if (_left) delete _left;
	if (_right) delete _right;
}

bvh_node::bvh_node(bvh_tree *f_tree, unsigned int id)
{
	_left = _right = NULL;
	_id = id;
	_tree = f_tree;
}

bvh_node::bvh_node(bvh_tree *f_tree, unsigned int *lst, unsigned int lst_num, DigiModel *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	_tree = f_tree;

	//fprintf(m_File, "NEW BVH_NODE lst_num %i\n", lst_num);

	if (lst_num == 1)
		{
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
		}
	else
		{ // try to split them
		for (unsigned int t=0; t<lst_num; t++)
			{
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
			}

		if (lst_num == 2)
			{ // must split it!
			_left = new bvh_node(_tree, lst[0]);
			_right = new bvh_node(_tree, lst[1]);
			}
		else
			{
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++)
				{
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else
					{// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
					}
				}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
				{
				_left = new bvh_node(_tree, lst, hal, mdl);
				_right = new bvh_node(_tree, lst+hal, lst_num-hal, mdl);
				}
			else
				{
				_left = new bvh_node(_tree, lst, left_idx, mdl);
				_right = new bvh_node(_tree, lst+left_idx, lst_num-left_idx, mdl);
				}

			}
		}
}

bvh_node::bvh_node(bvh_tree *f_tree, unsigned int *lst, unsigned int lst_num, digiDataMesh *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	_tree = f_tree;

	//fprintf(m_File, "NEW BVH_NODE lst_num %i\n", lst_num);

	if (lst_num == 1)
		{
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
		}
	else
		{ // try to split them
		for (unsigned int t=0; t<lst_num; t++)
			{
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
			}

		if (lst_num == 2)
			{ // must split it!
			_left = new bvh_node(_tree, lst[0]);
			_right = new bvh_node(_tree, lst[1]);
			}
		else
			{
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++)
				{
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else
					{// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
					}
				}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
				{
				_left = new bvh_node(_tree, lst, hal, mdl);
				_right = new bvh_node(_tree, lst+hal, lst_num-hal, mdl);
				}
			else
				{
				_left = new bvh_node(_tree, lst, left_idx, mdl);
				_right = new bvh_node(_tree, lst+left_idx, lst_num-left_idx, mdl);
				}

			}
		}
}

bvh_node::bvh_node(bvh_tree *f_tree, unsigned int *lst, unsigned int lst_num, digiShellMesh *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	_tree = f_tree;

	//fprintf(m_File, "NEW BVH_NODE lst_num %i\n", lst_num);

	if (lst_num == 1)
		{
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
		}
	else
		{ // try to split them
		for (unsigned int t=0; t<lst_num; t++)
			{
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
			}

		if (lst_num == 2)
			{ // must split it!
			_left = new bvh_node(_tree, lst[0]);
			_right = new bvh_node(_tree, lst[1]);
			}
		else
			{
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++)
				{
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else
					{// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
					}
				}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
				{
				_left = new bvh_node(_tree, lst, hal, mdl);
				_right = new bvh_node(_tree, lst+hal, lst_num-hal, mdl);
				}
			else
				{
				_left = new bvh_node(_tree, lst, left_idx, mdl);
				_right = new bvh_node(_tree, lst+left_idx, lst_num-left_idx, mdl);
				}

			}
		}
}

bvh_node::bvh_node(bvh_tree *f_tree, unsigned int *lst, unsigned int lst_num, digiBodyMesh *mdl)
{
	assert(lst_num > 0);
	_left = _right = NULL;
	_id = UINT_MAX;
	_tree = f_tree;

	//fprintf(m_File, "NEW BVH_NODE lst_num %i\n", lst_num);

	if (lst_num == 1)
		{
		_id = lst[0];
		_box = mdl->_tri_boxes[_id];
		}
	else
		{ // try to split them
		for (unsigned int t=0; t<lst_num; t++)
			{
			int i=lst[t];
			_box += mdl->_tri_boxes[i];
			}

		if (lst_num == 2)
			{ // must split it!
			_left = new bvh_node(_tree, lst[0]);
			_right = new bvh_node(_tree, lst[1]);
			}
		else
			{
			aap pln(_box);
			unsigned int left_idx = 0, right_idx = lst_num-1;

			for (unsigned int t=0; t<lst_num; t++)
				{
				int i=lst[left_idx];
				if (pln.inside(mdl->_tri_centers[i]))
					left_idx++;
				else
					{// swap it
					unsigned int tmp = i;
					lst[left_idx] = lst[right_idx];
					lst[right_idx--] = tmp;
					}
				}

			int hal = lst_num/2;
			if (left_idx == 0 || left_idx == lst_num)
				{
				_left = new bvh_node(_tree, lst, hal, mdl);
				_right = new bvh_node(_tree, lst+hal, lst_num-hal, mdl);
				}
			else
				{
				_left = new bvh_node(_tree, lst, left_idx, mdl);
				_right = new bvh_node(_tree, lst+left_idx, lst_num-left_idx, mdl);
				}

			}
		}
}

void
bvh_node::visualization(int level)
{
	if (IsLeaf(this))
		_box.visualization();
	else
		if ((level > 0)) {
			if (level == 1)
				_box.visualization();
			else
			if (_left)
				_left->visualization(level-1);
			if (_right)
				_right->visualization(level-1);
		}
}

aabb &
bvh_node::refit()
{
	if (IsLeaf(this)) {
		s_num_leaf++;

		int i = _id;
		Digi::Vertex &p1 = s_mdl->vec_Vert[s_mdl->vec_Face[i].m_v1];
		Digi::Vertex &p2 = s_mdl->vec_Vert[s_mdl->vec_Face[i].m_v2];
		Digi::Vertex &p3 = s_mdl->vec_Vert[s_mdl->vec_Face[i].m_v3];

		_box.empty();
		_box += p1;
		_box += p2;
		_box += p3;
	} else {
		_box = _left->refit();
		_box += _right->refit();
	}

	return _box;
}

aabb &
bvh_node::refitbm()
{
	if (IsLeaf(this)) {
		s_num_leaf++;

		int i = _id;
		Digi::Vertex &p1 = _tree->_meshgm->vec_Vert[0][_tree->_meshgm->vec_Face[0][i].m_v1];
		Digi::Vertex &p2 = _tree->_meshgm->vec_Vert[0][_tree->_meshgm->vec_Face[0][i].m_v2];
		Digi::Vertex &p3 = _tree->_meshgm->vec_Vert[0][_tree->_meshgm->vec_Face[0][i].m_v3];

		_box.empty();
		_box += p1;
		_box += p2;
		_box += p3;
	} else {
		_box = _left->refitbm();
		_box += _right->refitbm();
	}

	return _box;
}

};