#include "pch.h"
#include "paralelo3d.h"

void pCapsule::draw(const int res) const
{
#ifndef P_DISABLE_3D
	GLUquadricObj *sph_mesh=gluNewQuadric();
	GLUquadricObj *cyl_mesh=gluNewQuadric();

	gluQuadricDrawStyle(sph_mesh,GLU_LINE);
	gluQuadricDrawStyle(cyl_mesh,GLU_LINE);

	pVector nrm(line.end-line.start);
	float sz=nrm.length();
	nrm.normalize();
	double eq1[4]={(double)nrm.x,(double)nrm.y,(double)nrm.z,0.0};
	nrm.negate();
	double eq0[4]={(double)nrm.x,(double)nrm.y,(double)nrm.z,0.0};

	pVector mid((line.end+line.start)*0.5f);
	mid=mid-nrm*sz*0.5f;

	pVector Z(0.0f,0.0f,1.0f);
	pVector axis;
	axis.cross(nrm,Z);
	float angle=PIUNDER180*acosf(VECDOT(nrm,Z));
 
	glEnable(GL_CLIP_PLANE0);
	glPushMatrix();
		glTranslatef(line.start.x,line.start.y,line.start.z);
		glClipPlane(GL_CLIP_PLANE0,eq0);
		gluSphere(sph_mesh,radius,res,res);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE0);

	glPushMatrix();
		glTranslatef(mid.x,mid.y,mid.z);
		glRotatef(-angle,axis.x,axis.y,axis.z);
		gluCylinder(cyl_mesh,radius,radius,sz,res,res);
	glPopMatrix();

	glEnable(GL_CLIP_PLANE1);
	glPushMatrix();
		glTranslatef(line.end.x,line.end.y,line.end.z);
		glClipPlane(GL_CLIP_PLANE1,eq1);
		gluSphere(sph_mesh,radius,res,res);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE1);

	gluDeleteQuadric(cyl_mesh);
	gluDeleteQuadric(sph_mesh);

	glLineWidth(3.0f);
	//*glBegin(GL_LINES);
		//*glVertex3fv(&(line.start.x));
		//*glVertex3fv(&(line.end.x));
	//*glEnd();
	glLineWidth(1.0f);
#endif
}

