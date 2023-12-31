/*! \file */

#ifndef PFACE_H
#define PFACE_H


class P3D_API pFace
{
	public:
		pVector face_normal;
		int vertindx;
		int material;
		int flags;
		int lastdraw;

	pFace() :
		flags(0),material(-1),lastdraw(0),
		vertindx(-1),face_normal(0,0,0,0)
	{ 
	}

	pFace(pFace& in) :
		flags(in.flags),material(in.material),
	        lastdraw(in.lastdraw),vertindx(in.vertindx),
	        face_normal(in.face_normal)
	{
	}

	void operator=(const pFace& in)
	{
		flags=in.flags;
		material=in.material;
		lastdraw=in.lastdraw;
		vertindx=in.vertindx;
		face_normal=in.face_normal;
	}

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);

#ifdef P_MESH_SHORT_FACE
	int ray_intersect(const pVertex *verts,const unsigned short *facevert,const pVector& ro,const pVector& rd,pVector& ip,float& dist) const;
#else
	int ray_intersect(const pVertex *verts,const unsigned int *facevert,const pVector& ro,const pVector& rd,pVector& ip,float& dist) const;
#endif
	void compute_dudv(const pVertex *verts,const int *facevert,const pVector& ip,float u,float v,pVector& dU,pVector& dV) const;
	
	inline float distance(const pVector &v) const
	{ return VECDOT(face_normal,v)-face_normal.w; }
	inline float distance(const float *f) const
	{ return face_normal.x*f[0]+face_normal.y*f[1]+face_normal.z*f[2]-face_normal.w; }
};

#endif
