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


#include <stdlib.h>
#include <assert.h>

#include "paralelo3d.h"

namespace pColdet
{

extern int tri_contact (double *P1, double *P2, double *P3, double *Q1, double *Q2, double *Q3);

static DigiModel *s_mdl1, *s_mdl2;
static bool s_self = false;
#define IsLeaf(node) (node->_left == NULL)

#include <vector>
static std::vector<unsigned int> s_rets;

void
bvh_tree::collide(bvh_tree *other)
{
	s_mdl1 = this->_mdl;
	s_mdl2 = other->_mdl;
	s_self = false;

	m_rets.erase(m_rets.begin(), m_rets.end());
	_root->collide(other->_root);
}

void
bvh_tree::collide(trr::trrPanel *other)
{
	s_mdl1 = this->_mdl;
	s_self = false;

	m_rets.erase(m_rets.begin(), m_rets.end());
	_root->collide(other);
}

void
bvh_tree::self_collide()
{
	s_mdl1 = this->_mdl;
	s_mdl2 = this->_mdl;
	s_self = true;

	m_rets.erase(m_rets.begin(), m_rets.end());
	_root->self_collide();
}

#define set_vtx_color(mdl, id) {\
			mdl->vec_Colors[id*3] = 0;\
			mdl->vec_Colors[id*3+1] = 255;\
			mdl->vec_Colors[id*3+2] = 0;\
}

bool
bvh_tree::get_contact(int i, unsigned int &id1, unsigned int &id2)
{
	id1 = -1;
	id2 = -1;

	int num = m_rets.size()/2;
	
	if (i<0 || i>=num)
		return false;

	id1 = m_rets[i*2];
	id2 = m_rets[i*2+1];
	return true;

}

void
bvh_tree::color()
{
	int idx=0;
	unsigned int vtx_id;

	for (std::vector<unsigned int>::iterator it=m_rets.begin(); it!=m_rets.end(); it++) {
		unsigned int trf_id = *it;
		if (idx%2) {// odd
			vtx_id = s_mdl2->vec_Face[trf_id].m_v1;
			set_vtx_color(s_mdl2, vtx_id);
			vtx_id = s_mdl2->vec_Face[trf_id].m_v2;
			set_vtx_color(s_mdl2, vtx_id);
			vtx_id = s_mdl2->vec_Face[trf_id].m_v3;
			set_vtx_color(s_mdl2, vtx_id);
		} else { //even
			vtx_id = s_mdl1->vec_Face[trf_id].m_v1;
			set_vtx_color(s_mdl1, vtx_id);
			vtx_id = s_mdl1->vec_Face[trf_id].m_v2;
			set_vtx_color(s_mdl1, vtx_id);
			vtx_id = s_mdl1->vec_Face[trf_id].m_v3;
			set_vtx_color(s_mdl1, vtx_id);
		}
		idx++;
	}
}

int
bvh_node::test_triangle(unsigned int id1, unsigned int id2)
{
	vec3d p1;
	vec3d p2;
	vec3d p3;
	vec3d q1;
	vec3d q2;
	vec3d q3;
	p1.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][0];
	p1.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][1];
	p1.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][2];
	p2.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][0];
	p2.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][1];
	p2.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][2];
	p3.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][0];
	p3.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][1];
	p3.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][2];
	q1.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v1][0];
	q1.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v1][1];
	q1.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v1][2];
	q2.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v2][0];
	q2.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v2][1];
	q2.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v2][2];
	q3.x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v3][0];
	q3.y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v3][1];
	q3.z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id2].m_v3][2];

	return tri_contact((double *)&p1, (double *)&p2, (double *)&p3, (double *)&q1, (double *)&q2, (double *)&q3);
}

inline vec3d interp(vec3d &p1, vec3d &p2, float t)
{
	return p1*(1-t)+p2*t;
}

static vec3d P[3], Q[3];
static float eps_interp = float(10e-5);

inline int tri_contact (vec3d *p, vec3d *q, unsigned int cov)
{
	if (cov == 3)
		return true;

	if (cov == 0) {
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++) {
				P[i].v[j] = p[i][j];
				Q[i].v[j] = q[i][j];
			}

		return tri_contact(P[0].v, P[1].v, P[2].v, Q[0].v, Q[1].v, Q[2].v);
	}

	if (cov == 1) {
		for (int i=1; i<3; i++)
			for (int j=0; j<3; j++) {
				P[i].v[j] = p[i][j];
				Q[i].v[j] = q[i][j];
			}

		vec3d mid = interp(p[1], p[2], 0.5);
		vec3d p0 = interp(p[0], mid, eps_interp);

		mid = interp(q[1], q[2], 0.5);
		vec3d q0 = interp(q[0], mid, eps_interp);

		for (int j=0; j<3; j++) {
			P[0].v[j] = p0[j];
			Q[0].v[j] = q0[j];
		}

		return tri_contact(P[0].v, P[1].v, P[2].v, Q[0].v, Q[1].v, Q[2].v);
	}

	if (cov == 2) {
		for (int j=0; j<3; j++) {
			P[0].v[j] = p[0][j];
			Q[0].v[j] = q[0][j];
		}

		vec3d p1 = interp(p[1], p[0], eps_interp);
		vec3d p2 = interp(p[2], p[0], eps_interp);
		for (int j=0; j<3; j++) {
			P[1].v[j] = p1[j];
			P[2].v[j] = p2[j];
		}

		vec3d q1 = interp(q[1], q[0], eps_interp);
		vec3d q2 = interp(q[2], q[0], eps_interp);
		for (int j=0; j<3; j++) {
			Q[1].v[j] = q1[j];
			Q[2].v[j] = q2[j];
		}

		return tri_contact(P[0].v, P[1].v, P[2].v, Q[0].v, Q[1].v, Q[2].v);
	}

	assert(0);
	return false;
}

int
bvh_node::test_triangle(unsigned int id1, unsigned int id2,
						unsigned int cov, unsigned int st1, unsigned int st2)
{
	unsigned int f_id1 = id1 + st1;
	unsigned int f_id2 = id2 + st2;
	if(id1 + st1 > s_mdl1->vec_Face.size()) return 0;
	if(id2 + st2 > s_mdl2->vec_Face.size()) return 0;

	vec3d *p = new vec3d[3];
	p[0].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v1][0];
	p[0].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v1][1];
	p[0].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v1][2];
	p[1].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v2][0];
	p[1].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v2][1];
	p[1].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v2][2];
	p[2].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v3][0];
	p[2].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v3][1];
	p[2].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[f_id1].m_v3][2];

	vec3d *q = new vec3d[3];
	q[0].x = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v1][0];
	q[0].y = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v1][1];
	q[0].z = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v1][2];
	q[1].x = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v2][0];
	q[1].y = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v2][1];
	q[1].z = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v2][2];
	q[2].x = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v3][0];
	q[2].y = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v3][1];
	q[2].z = s_mdl2->vec_Vert[s_mdl2->vec_Face[f_id2].m_v3][2];

	return tri_contact(p, q, cov);
}

int
bvh_node::test_trf_panel(unsigned int id1, unsigned int cov, unsigned int st1, trrPanel* f_Panel, int f_Side)
{
	vec3d *p = new vec3d[3];
	p[0].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][0];
	p[0].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][1];
	p[0].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v1][2];
	p[1].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][0];
	p[1].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][1];
	p[1].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v2][2];
	p[2].x = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][0];
	p[2].y = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][1];
	p[2].z = s_mdl1->vec_Vert[s_mdl1->vec_Face[id1].m_v3][2];

	vec3d *q = new vec3d[3];
	q[0].x = f_Panel->Vert[f_Panel->Face[f_Side].m_v1][0];
	q[0].y = f_Panel->Vert[f_Panel->Face[f_Side].m_v1][1];
	q[0].z = f_Panel->Vert[f_Panel->Face[f_Side].m_v1][2];
	q[1].x = f_Panel->Vert[f_Panel->Face[f_Side].m_v2][0];
	q[1].y = f_Panel->Vert[f_Panel->Face[f_Side].m_v2][1];
	q[1].z = f_Panel->Vert[f_Panel->Face[f_Side].m_v2][2];
	q[2].x = f_Panel->Vert[f_Panel->Face[f_Side].m_v3][0];
	q[2].y = f_Panel->Vert[f_Panel->Face[f_Side].m_v3][1];
	q[2].z = f_Panel->Vert[f_Panel->Face[f_Side].m_v3][2];

	return tri_contact(p, q, cov);
}

void
bvh_node::self_collide()
{
	if (IsLeaf(this))
		return;

	_left->self_collide();
	_right->self_collide();
	_left->collide(_right);
}

void
bvh_node::collide(bvh_node *other)
{
	assert(other);

	s_mdl1->_num_box_tests++;
	if (!_box.collide(other->_box)) {
		return;
	}

	if (IsLeaf(this) && IsLeaf(other)){
		unsigned int st1 = 0, st2 = 0;
		unsigned int cov = 0;
		
		if (s_self)
			cov = s_mdl1->acCovertex(_id, other->_id, st1, st2);

		s_mdl1->_num_trf_tests++;
		if (test_triangle(_id, other->_id, cov, st1, st2)) {
			s_mdl1->_num_contacts++;
			_tree->m_rets.push_back(_id);
			_tree->m_rets.push_back(other->_id);
		}
		return;
	}

	if (IsLeaf(this)) {
		collide(other->_left);
		collide(other->_right);
	} else {
		_left->collide(other);
		_right->collide(other);
	}
}

void
bvh_node::collide(trr::trrPanel* f_Panel)
{
	if(IsLeaf(this))
		{
		unsigned int st1 = 0, st2 = 0;
		unsigned int cov = 0;
		
		//if (s_self)
		//	cov = s_mdl1->acCovertex(_id, other->_id, st1, st2);

		s_mdl1->_num_trf_tests++;

		if (test_trf_panel(_id, cov, st1, f_Panel, 0))
			{
			s_mdl1->_num_contacts++;
			_tree->m_rets.push_back(_id);
			}

		s_mdl1->_num_trf_tests++;

		if (test_trf_panel(_id, cov, st1, f_Panel, 1))
			{
			s_mdl1->_num_contacts++;
			_tree->m_rets.push_back(_id);
			}

		return;
		}

	if(!IsLeaf(this))
		{
		_left->collide(f_Panel);
		_right->collide(f_Panel);
		}
}

};