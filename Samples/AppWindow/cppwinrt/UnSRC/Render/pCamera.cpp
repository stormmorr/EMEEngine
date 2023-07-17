#include "pch.h"
#include "paralelo3d.h"

void pCamera::align_z(const pVector& z,const pVector& up)
{
	Y=up-z*VECDOT(z,up);
	Y.normalize();
	X.cross(Y,z);
	Z=z;

	update_mat();
}

void pCamera::align_z(const pVector& z)
{
	if (fabsf(z.z)>=0.99f)
	{
		Y.x=-z.y*z.x;
		Y.y=1-z.y*z.y;
		Y.z=-z.y*z.z;

		Y.normalize();
		X.cross(Y,z);
	}
	else 
	{		
		Y.x=-z.z*z.x;
		Y.y=-z.z*z.y;
		Y.z=1-z.z*z.z;

		Y.normalize();
		X.cross(Y,z);
	}

	Z=z;

	update_mat();
}

void pCamera::update_mat()
{
#if 0
	mat.null();

	mat.m[0][0]=X.x;
	mat.m[0][1]=X.y;
	mat.m[0][2]=X.z;

	mat.m[1][0]=Y.x;
	mat.m[1][1]=Y.y;
	mat.m[1][2]=Y.z;

	mat.m[2][0]=Z.x;
	mat.m[2][1]=Z.y;
	mat.m[2][2]=Z.z;
	
	mat.m[3][3]=1;

	int i,j;
	for( i=0;i<4;i++ )
		for( j=0;j<4;j++ )
			mat_t.m[i][j]=mat.m[j][i];
#else
	//mat_t =mat;

	int i,j;
	for( i=0;i<4;i++ )
		for( j=0;j<4;j++ )
			mat.m[i][j]=mat_t.m[j][i];
#endif
}

void pCamera::rotate(const pVector &v, const pVector &u, float maxang)
{
	float f=VECDOT(u,v);
	if(f<0.9999f)
	{
		f=acosf(f)*PIUNDER180;
		if(f>maxang)
			f=maxang;

		pVector c;
		c.cross(v, u);
		c.normalize();
		rotate(f, c);
	}
}

void pCamera::rotate(const pVector& rot)
{
	pMatrix m;

	m.set_rotation(rot.x,X);
	m.rotate(rot.y,Y);
	m.rotate(rot.z,Z);

	X=X*m;
	Y=Y*m;
	Z=Z*m;
	
	update_mat();
}

void pCamera::rotate(float ang,const pVector& v)
{
	pMatrix m;

	m.set_rotation(ang,v);

	X=X*m;
	Y=Y*m;
	Z=Z*m;
	
	update_mat();
}

void pCamera::write(FILE *fp) const
{
	name.write(fp);
	fwrite(&pos.x,3,sizeof(float),fp);
	fwrite(&X.x,3,sizeof(float),fp);
	fwrite(&Y.x,3,sizeof(float),fp);
	fwrite(&fov,1,sizeof(float),fp);
	anim_pos_x.write(fp);
	anim_pos_y.write(fp);
	anim_pos_z.write(fp);
	anim_rot_x.write(fp);
	anim_rot_y.write(fp);
	anim_rot_z.write(fp);
	anim_fov.write(fp);
}

void pCamera::read(pFile& fp,int ver)
{
	name.read(fp);
	fp.read(&pos.x,3*sizeof(float));
	fp.read(&X.x,3*sizeof(float));
	fp.read(&Y.x,3*sizeof(float));
	fp.read(&fov,sizeof(float));
	if(ver>=P3D_FILEVER+3)
	{
		anim_pos_x.read(fp,ver);
		anim_pos_y.read(fp,ver);
		anim_pos_z.read(fp,ver);
		anim_rot_x.read(fp,ver);
		anim_rot_y.read(fp,ver);
		anim_rot_z.read(fp,ver);
	}
	else
	{
		pAnimation a;
		a.read(fp,ver);
		a.read(fp,ver);
	}
	anim_fov.read(fp,ver);
	Z.cross(X,Y);
	update_mat();
}

void pCameraCtrlObs::check_input()
{
	pCamera *cam=&g_render->camera;
	move.vec(0);
	rot.vec(0);

	/*if (GetAsyncKeyState(VK_MENU)&0x80000000)
	{
		if (GetAsyncKeyState(VK_LEFT)&0x80000000)
			move-=cam->X*movevel;
		if (GetAsyncKeyState(VK_RIGHT)&0x80000000)
			move+=cam->X*movevel;

		if (GetAsyncKeyState(VK_DOWN)&0x80000000)
			move-=cam->Y*movevel;
		if (GetAsyncKeyState(VK_UP)&0x80000000)
			move+=cam->Y*movevel;
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT)&0x80000000)
			rot.y-=rotvel;
		if (GetAsyncKeyState(VK_RIGHT)&0x80000000)
			rot.y+=rotvel;

		if (GetAsyncKeyState(VK_DOWN)&0x80000000)
			rot.x-=rotvel;
		if (GetAsyncKeyState(VK_UP)&0x80000000)
			rot.x+=rotvel;

		if (GetAsyncKeyState(g_render->camkeys[2])&0x80000000)
			move-=cam->X*movevel;
		if (GetAsyncKeyState(g_render->camkeys[3])&0x80000000)
			move+=cam->X*movevel;

		if (GetAsyncKeyState(g_render->camkeys[4])&0x80000000)
			rot.z-=rotvel;
		if (GetAsyncKeyState(g_render->camkeys[5])&0x80000000)
			rot.z+=rotvel;
	}*/

	/*if (GetAsyncKeyState(g_render->camkeys[0])&0x80000000)
		move-=cam->Z*movevel;
	if (GetAsyncKeyState(g_render->camkeys[1])&0x80000000)
		move+=cam->Z*movevel;*/
}

void pCameraCtrlObs::update()
{
	pCamera *cam=&g_render->camera;

	pBoundBox bb;
	bb.min=-pVector(radius);
	bb.max=pVector(radius);

	cam->pos+=move*g_render->curdtf;
	cam->rotate(rot*g_render->curdtf);

	move.vec(0);
	rot.vec(0);
}

void pCameraCtrlOrbit::check_input()
{
	move.vec(0);
	movedist=0;
	pCamera *cam=&g_render->camera;

	/*if (GetAsyncKeyState(VK_LEFT)&0x80000000)
		move-=cam->X*rotvel;
	if (GetAsyncKeyState(VK_RIGHT)&0x80000000)
		move+=cam->X*rotvel;

	if (GetAsyncKeyState(VK_DOWN)&0x80000000)
		move-=cam->Y*rotvel;
	if (GetAsyncKeyState(VK_UP)&0x80000000)
		move+=cam->Y*rotvel;

	if (GetAsyncKeyState(g_render->camkeys[0])&0x80000000)
		movedist-=movevel;
	if (GetAsyncKeyState(g_render->camkeys[1])&0x80000000)
		movedist+=movevel;*/
}		

void pCameraCtrlOrbit::update()
{
	pVector up(0,0,1);
	pVector dir,p;
	float d,animtime=0.3f;

	pCamera *cam=&g_render->camera;

	if (zdelta)
	{
		movedist+=movevel*zdelta;
		zdelta=0;
	}

	if (g_render->target_moving==0)
	{
		if (moving==0)
		{
			if ((target-g_render->target_pos).length2()>0.01f)
			{
				last_pos=cam->pos;
				last_target=t;
				time=animtime;
				dir=cam->pos-target;
				target=g_render->target_pos;
				pos=target+dir;
			}

			if (time>0)
			{
				d=time/animtime;
				p=pos*(1-d)+last_pos*d;
				t=target*(1-d)+last_target*d;
				time-=g_render->curdtf;
				if (time<0)
					time=0;
			}
			else
			{
				t=g_render->target_pos;
				p=cam->pos;
			}
		}
		else
		{
			moving=0;
			dir=cam->pos-target;
			target=g_render->target_pos;
			p=target+dir;
			t=target;
		}
	}
	else
	{
		moving=1;
		dir=cam->pos-target;
		target=g_render->target_pos;
		p=target+dir;
		t=target;
	}

	dir=p-t;
	d=dir.length();
	if (d<0.01f || (target-cam->pos).length2()<0.01f)
		return;

	dir*=1.0f/d;
	movedist*=g_render->curdtf*d/50;
	move*=g_render->curdtf*d/50;
	movedist+=d;

	cam->align_z(dir);

	if (movedist<g_render->nearplane)
		movedist=g_render->nearplane;
	if (movedist>g_render->farplane*0.95f) 
		movedist=g_render->farplane*0.95f;

	p=p+move;
	dir=p-t;
	dir.normalize();

	if (fabsf(dir.z)<0.99f)
	{
		cam->pos=t+dir*movedist;
		cam->align_z(dir);
	}

	move.vec(0);
	movedist=0;
}

void pCamera::animate(float time)
{
	anim_pos_x.update_loop(time,&pos.x);
	anim_pos_y.update_loop(time,&pos.y);
	anim_pos_z.update_loop(time,&pos.z);
	anim_fov.update_loop(time,&fov);
	if (anim_rot_x.numkey || 
		anim_rot_y.numkey ||
		anim_rot_z.numkey)
	{
		pVector rot(0);
		anim_rot_x.update_loop(time,&rot.x);
		anim_rot_y.update_loop(time,&rot.y);
		anim_rot_z.update_loop(time,&rot.z);
		rot*=PIUNDER180;

		pMatrix m;
		m.set_transformation(rot,pVector(0.0f));

		X.vec(m.m[0][0],m.m[1][0],m.m[2][0]);
		Y.vec(m.m[0][1],m.m[1][1],m.m[2][1]);
		Z.vec(m.m[0][2],m.m[1][2],m.m[2][2]);
		update_mat();
	}
}
