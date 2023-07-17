#include "pch.h"
#include "paralelo3d.h"

void pDummy::write(FILE *fp) const
{
	name.write(fp);
	params.write(fp);
	fwrite(&transform,16,sizeof(float),fp);
	fwrite(&pmin.x,3,sizeof(float),fp);
	fwrite(&pmax.x,3,sizeof(float),fp);
	anim_pos_x.write(fp);
	anim_pos_y.write(fp);
	anim_pos_z.write(fp);
	anim_rot_x.write(fp);
	anim_rot_y.write(fp);
	anim_rot_z.write(fp);
}

void pDummy::read(pFile& fp,int ver)
{
	name.read(fp);
	params.read(fp);
	fp.read(&transform,16*sizeof(float));
	fp.read(&pmin.x,3*sizeof(float));
	fp.read(&pmax.x,3*sizeof(float));
	if(ver>=P3D_FILEVER+3)
	{
		anim_pos_x.read(fp,ver);
		anim_pos_y.read(fp,ver);
		anim_pos_z.read(fp,ver);
		anim_rot_x.read(fp,ver);
		anim_rot_y.read(fp,ver);
		anim_rot_z.read(fp,ver);
	}
}

float pDummy::get_maxanimtime()
{
	float maxanimtime=0;

	if (anim_pos_x.get_maxtime()>maxanimtime)
		maxanimtime=anim_pos_x.get_maxtime();
	if (anim_pos_y.get_maxtime()>maxanimtime)
		maxanimtime=anim_pos_y.get_maxtime();
	if (anim_pos_z.get_maxtime()>maxanimtime)
		maxanimtime=anim_pos_z.get_maxtime();

	if (anim_rot_x.get_maxtime()>maxanimtime)
		maxanimtime=anim_rot_x.get_maxtime();
	if (anim_rot_y.get_maxtime()>maxanimtime)
		maxanimtime=anim_rot_y.get_maxtime();
	if (anim_rot_z.get_maxtime()>maxanimtime)
		maxanimtime=anim_rot_z.get_maxtime();

	return maxanimtime;
}

void pDummy::draw()
{
#ifndef P_DISABLE_3D
	int i,j=200;
	pVector p;

	g_render->sel_tex(-1);
	glLineWidth(1);
	glColor4f(1,1,1,1);
	//*glBegin(GL_LINE_STRIP);
	for( i=0;i<j;i++ )
	{
		float t=(float)i/j;
		t*=anim_pos_x.get_maxtime();
		anim_pos_x.update(t,&p.x);
		anim_pos_y.update(t,&p.y);
		anim_pos_z.update(t,&p.z);
		//*glVertex3fv(&p.x);
	}
	//*glEnd();
#endif
}