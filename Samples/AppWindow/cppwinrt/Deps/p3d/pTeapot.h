/*! \file */

#ifndef PTEAPOT_H
#define PTEAPOT_H

#define P_TEAPOT_NUMVERTS 127
#define P_TEAPOT_NUMPATCHES 10

enum pTeapotMode { P_TEAPOT_OPENGL,P_TEAPOT_DIRECTX };

struct pTeapotVertex
{
	float pos[3];
	float normal[3];
	float tangent[3];
	float binormal[3];
	float texcoord[2];
};

class pTeapot
{
	static float patchverts[P_TEAPOT_NUMVERTS][3];
	static int patchmirror[P_TEAPOT_NUMPATCHES];
	static int patchfaces[P_TEAPOT_NUMPATCHES][16];

	int numverts,numfaces;
	pTeapotVertex *verts;
	int *faces;

	void build_verts(int tesselation,float scale,pTeapotMode mode);
	void build_faces(int tesselation,pTeapotMode mode);
	void evaluate_patch(int patch,float u,float v,pTeapotVertex *vertex);

public:
	pTeapot();
	~pTeapot();

	void reset();

	void build(int tesselation,float m_scale,pTeapotMode mode);

	int get_numverts()
	{ 
		return numverts; 
	}

	const pTeapotVertex *get_verts()
	{ 
		return verts; 
	}

	int get_numfaces()
	{ 
		return numfaces; 
	}

	const int *get_faces()
	{ 
		return faces; 
	}
};

#endif
