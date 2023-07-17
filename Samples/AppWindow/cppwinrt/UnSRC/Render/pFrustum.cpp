#include "pch.h"
#include "paralelo3d.h"

void pFrustum::build(const pVector& pos,const pVector& X,const pVector& Y,const pVector& Z,float camangle,float aspect,float farplane)
{
	float disty=farplane*(float)tan(camangle*0.5f*PIOVER180);
	float distx=disty*aspect;

	verts[0]=pos;
	
	verts[1].x = pos.x - farplane*Z.x + distx*X.x + disty*Y.x;
	verts[1].y = pos.y - farplane*Z.y + distx*X.y + disty*Y.y;
	verts[1].z = pos.z - farplane*Z.z + distx*X.z + disty*Y.z;

	verts[2].x = pos.x - farplane*Z.x + distx*X.x - disty*Y.x;
	verts[2].y = pos.y - farplane*Z.y + distx*X.y - disty*Y.y;
	verts[2].z = pos.z - farplane*Z.z + distx*X.z - disty*Y.z;

	verts[3].x = pos.x - farplane*Z.x - distx*X.x - disty*Y.x;
	verts[3].y = pos.y - farplane*Z.y - distx*X.y - disty*Y.y;
	verts[3].z = pos.z - farplane*Z.z - distx*X.z - disty*Y.z;

	verts[4].x = pos.x - farplane*Z.x - distx*X.x + disty*Y.x;
	verts[4].y = pos.y - farplane*Z.y - distx*X.y + disty*Y.y;
	verts[4].z = pos.z - farplane*Z.z - distx*X.z + disty*Y.z;

	planes[0].cross(verts[2]-verts[1],verts[0]-verts[1]);
	planes[0].normalize();
	planes[0].w=VECDOT(verts[0],planes[0]);

	planes[1].cross(verts[3]-verts[2],verts[0]-verts[2]);
	planes[1].normalize();
	planes[1].w=VECDOT(verts[0],planes[1]);

	planes[2].cross(verts[4]-verts[3],verts[0]-verts[3]);
	planes[2].normalize();
	planes[2].w=VECDOT(verts[0],planes[2]);

	planes[3].cross(verts[1]-verts[4],verts[0]-verts[4]);
	planes[3].normalize();
	planes[3].w=VECDOT(verts[0],planes[3]);

	planes[4].cross(verts[3]-verts[1],verts[2]-verts[1]);
	planes[4].normalize();
	planes[4].w=VECDOT(verts[1],planes[4]);

	static int table[8][3]=
		{ {4,5,6},{4,5,2},{4,1,6},{4,1,2},
		{0,5,6},{0,5,2},{0,1,6},{0,1,2} };
	int i,j;
	for( i=0;i<5;i++ )
	{
		j =	(FPSIGNBIT(planes[i].x)>>29)|
			(FPSIGNBIT(planes[i].y)>>30)|
			(FPSIGNBIT(planes[i].z)>>31);
		bboxindx[i][0]=table[j][0];
		bboxindx[i][1]=table[j][1];
		bboxindx[i][2]=table[j][2];
	}
}

bool pFrustum::is_inside(const pVector& p) const
{
#if 0
   for (int i=0;i<5;i++)
	   if ((VECDOT(planes[i],p)-planes[i].w)<0.0f)
		   return false;
#else
   for (int i=0;i<5;i++)
       if ((VECDOT(planes[i],p) - planes[i].w)<0.0f)
           return false;
#endif

   return true;
}

int pFrustum::clip_bbox(const pBoundBox& bbox,const int nplanes) const
{
	float *f=(float *)&bbox.min.x;

	for( int i=0;i<nplanes;i++ )
		if (planes[i].x*f[bboxindx[i][0]]+
			planes[i].y*f[bboxindx[i][1]]+
			planes[i].z*f[bboxindx[i][2]]-planes[i].w<0)
			return 0;
	return 1;
}

void pFrustum::draw() const 
{
#ifndef P_DISABLE_3D
	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//*glBegin(GL_LINES);
	//*glVertex3fv(&verts[0].x);
	//*glVertex3fv(&verts[1].x);
	//*glVertex3fv(&verts[0].x);
	//*glVertex3fv(&verts[2].x);
	//*glVertex3fv(&verts[0].x);
	//*glVertex3fv(&verts[3].x);
	//*glVertex3fv(&verts[0].x);
	//*glVertex3fv(&verts[4].x);
	//*glEnd();
	glPopAttrib();
#endif
	printf("verts[0] %f %f %f verts[1] %f %f %f verts[2] %f %f %f verts[3] %f %f %f verts[4] %f %f %f\n", verts[0].x, verts[0].y, verts[0].z, verts[1].x, verts[1].y, verts[1].z, verts[2].x, verts[2].y, verts[2].z, verts[3].x, verts[3].y, verts[3].z, verts[4].x, verts[4].y, verts[4].z);

#if 0
	for(;;)
	{}
#endif
}
