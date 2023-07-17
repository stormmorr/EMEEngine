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


#include <windows.h>
#include <gl/gl.h>
#include <stdio.h>
#include <assert.h>

#include "Model_Shl.h"
#include "../Digi/Vertex.h"

#pragma warning(disable: 4996)

ModelShl::ModelShl(int num_frame, int num_vtx, double *vtxs_frames, int num_tri, unsigned int *tris)
{
	Init(num_frame, num_vtx, (Digi::Vertex *)vtxs_frames, num_tri, tris);
}

ModelShl::ModelShl(int num_frame, int num_vtx, Digi::Vertex *vtxs_frames, int num_tri, unsigned int *tris)
{
	Init(num_frame, num_vtx, vtxs_frames, num_tri, tris);
}

void
ModelShl::Init(int num_frame, int num_vtx, Digi::Vertex *vtxs_frames, int num_tri, unsigned int *tris)
{
	_num_frame = num_frame;
	_num_vtx = num_vtx;
	_num_tri = num_tri;

	_tris = new unsigned int[_num_tri*3];
	memcpy(_tris, tris, sizeof(unsigned int)*_num_tri*3);

	_vtxs_frames = new Digi::Vertex[_num_frame*_num_vtx];
	memcpy(_vtxs_frames, vtxs_frames, sizeof(double)*3*_num_frame*_num_vtx);

	_vtxs = new Digi::Vertex[_num_vtx];
	for (unsigned int i=0; i<_num_vtx; i++)
		_vtxs[i] = _vtxs_frames[i];

	_colors = new unsigned char[_num_vtx*3];
	_nrms = new Digi::Vertex[_num_vtx];
	m_tri_nrms = new Digi::Vertex[_num_tri];

	UpdateNorm();
}


ModelShl::~ModelShl()
{
	delete [] _tris;
	delete [] _vtxs_frames;

	delete [] _vtxs;
	delete [] _colors;
	delete [] _nrms;
	delete [] m_tri_nrms;
}

void
ModelShl::Deform(float t, float circle)
{
	while (t > circle)
		t -= circle;

	t = t/circle*_num_frame;
	unsigned int prev_frame = ((unsigned int)t)%_num_frame;
	unsigned int next_frame = (prev_frame+1)%_num_frame;
	UpdateVert(prev_frame, next_frame, t-prev_frame);
	UpdateNorm();
}

inline Digi::Vertex interp(Digi::Vertex &p1, Digi::Vertex &p2, float t)
{
	return p1*(1-t)+p2*t;
}

void
ModelShl::UpdateVert(unsigned int prev, unsigned int next, float t)
{
	Digi::Vertex *prev_pt = _vtxs_frames+prev*_num_vtx;
	Digi::Vertex *next_pt = _vtxs_frames+next*_num_vtx;

	for (unsigned int i=0; i<_num_vtx; i++)
		_vtxs[i] = interp(prev_pt[i], next_pt[i], t);
}
