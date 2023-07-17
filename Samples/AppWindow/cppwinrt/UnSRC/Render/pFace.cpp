#include "pch.h"
#include "paralelo3d.h"

void pFace::write(FILE *fp) const
{
	fwrite(&material,1,sizeof(int),fp);
	fwrite(&flags,1,sizeof(int),fp);
}

void pFace::read(pFile& fp,int ver)
{
	fp.read(&material,sizeof(int));
	fp.read(&flags,sizeof(int));
}

#ifdef P_MESH_SHORT_FACE
int pFace::ray_intersect(const pVertex *verts,const unsigned short *facevert,const pVector& ro,const pVector& rd,pVector& ip,float& dist) const
#else
int pFace::ray_intersect(const pVertex *verts,const unsigned int *facevert,const pVector& ro,const pVector& rd,pVector& ip,float& dist) const
#endif
{
	float x=VECDOT(face_normal,rd);
	if ((flags&P_FACEFLAGS_TWOSIDE)==0 && x>0)
		return 0;

	dist=(face_normal.w - VECDOT(face_normal,ro))/x;
	if (dist<0.001f)
		return 0;

	ip=ro+rd*dist;

	pVector edge_normal;
	const float *vv[3];

	vv[0]=&verts[facevert[vertindx]].pos[0];
	vv[1]=&verts[facevert[vertindx+1]].pos[0];
	vv[2]=&verts[facevert[vertindx+2]].pos[0];

	int i,j;
	for( i=0;i<3;i++ )
	{
		j=(i+1)%3;
		edge_normal.cross(pVector(vv[j][0]-vv[i][0],vv[j][1]-vv[i][1],vv[j][2]-vv[i][2]),face_normal);
		if ((ip.x-vv[i][0])*edge_normal.x+
			(ip.y-vv[i][1])*edge_normal.y+
			(ip.z-vv[i][2])*edge_normal.z>0.001f)
			return 0;
	}

	return 1;
}

void pFace::compute_dudv(const pVertex *verts,const int *facevert,const pVector& ip,float u,float v,pVector& dU,pVector& dV) const
{
	float uv[3][2],a,b;
	pVector du,dv,d0;

	pVector v0,v1,v2;
	const pVertex *vv0,*vv1,*vv2;
	vv0=&verts[facevert[vertindx]];
	vv1=&verts[facevert[vertindx+1]];
	vv2=&verts[facevert[vertindx+2]];
	v0.vec(vv0->pos[0],vv0->pos[1],vv0->pos[2]);
	v1.vec(vv1->pos[0],vv1->pos[1],vv1->pos[2]);
	v2.vec(vv2->pos[0],vv2->pos[1],vv2->pos[2]);

	d0=v0-ip;
	du=v1-v0;
	dv=v2-v0;

	uv[1][0]=vv1->tx[0] - vv0->tx[0];
	uv[1][1]=vv1->tx[1] - vv0->tx[1];
	uv[2][0]=vv2->tx[0] - vv0->tx[0];
	uv[2][1]=vv2->tx[1] - vv0->tx[1];

	float delta=uv[1][0]*uv[2][1]-uv[2][0]*uv[1][1];
	if (delta>0)
	{
		uv[0][0]=u-vv0->tx[0]+(float)0.01;
		uv[0][1]=v-vv0->tx[1];
		a=(uv[0][0]*uv[2][1]-uv[2][0]*uv[0][1])/delta;
		b=(uv[1][0]*uv[0][1]-uv[0][0]*uv[1][1])/delta;
		dU=(a*du + b*dv)+d0;
		dU.normalize();

		uv[0][0]=u-vv0->tx[0];
		uv[0][1]=v-vv0->tx[1]+(float)0.01;
		a=(uv[0][0]*uv[2][1]-uv[2][0]*uv[0][1])/delta;
		b=(uv[1][0]*uv[0][1]-uv[0][0]*uv[1][1])/delta;
		dV=(a*du + b*dv)+d0;
		dV.normalize();
	}
	else
	{
		dU.vec(0);
		dV.vec(0);
	}
}
