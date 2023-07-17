/*! \file */

#ifndef PCAMERA_H
#define PCAMERA_H

class P3D_API pCamera
{
	public:
		pVector pos;	//!< translation position
		pVector	X,		//!< rotation local axis X direction
				Y,		//!< rotation local axis Y direction
				Z;		//!< rotation local axis Z direction
		pMatrix	mat,	//!< rotation matrix
				mat_t;	//!< inverse rotation matrix (transpose of the rotation matrix)
		float fov;		//!< camera angle
		pString name;	//!< camera name

		pAnimation anim_pos_x;
		pAnimation anim_pos_y;
		pAnimation anim_pos_z;
		pAnimation anim_fov;
		pAnimation anim_rot_x;
		pAnimation anim_rot_y;
		pAnimation anim_rot_z;

		int flag;

	//! Update the rotation matrices
	void update_mat();
	//! Rotate the local system axis by 'rot'
	void rotate(const pVector& rot);
	//! Rotate the local system axis of angle 'ang' around vector 'v'
	void rotate(float ang,const pVector& v);
	//! Rotate the local system axis from 'v' to 'u', in the plane defined by 'v' and 'u', at a maximum angle of 'maxang' degrees
	void rotate(const pVector &v, const pVector &u, float maxang=360);
	//! Align the z axis of the local system with the given vector
	void align_z(const pVector& z);
	void align_z(const pVector& z,const pVector& up);
	void animate(float time);
	
	//! Default constructor
	pCamera() : 
		pos(0,0,100), X(1,0,0), Y(0,1,0), Z(0,0,1), fov(80), flag(0)
	{ }

	//! Copy-constructor
	pCamera(const pCamera& in) : 
		pos(in.pos), X(in.X), Y(in.Y), Z(in.Z), 
		mat(in.mat), mat_t(in.mat_t), 
		fov(in.fov), name(in.name),
		anim_pos_x(in.anim_pos_x),
		anim_pos_y(in.anim_pos_y),
		anim_pos_z(in.anim_pos_z),
		anim_fov(in.anim_fov),
		anim_rot_x(in.anim_rot_x),
		anim_rot_y(in.anim_rot_y),
		anim_rot_z(in.anim_rot_z),
		flag(in.flag)
	{ }

	//! Atribuition operator
	void operator=(const pCamera& in) 
	{ 
		pos = in.pos;
		X = in.X;
		Y = in.Y;
		Z = in.Z;
		mat = in.mat;
		mat_t = in.mat_t;
		fov = in.fov;
		name = in.name;
		anim_pos_x = in.anim_pos_x;
		anim_pos_y = in.anim_pos_y;
		anim_pos_z = in.anim_pos_z;
		anim_fov = in.anim_fov;
		anim_rot_x = in.anim_rot_x;
		anim_rot_y = in.anim_rot_y;
		anim_rot_z = in.anim_rot_z;
		flag = in.flag;
	}

	void write(FILE *fp) const;
	void read(pFile& fp,int ver);
};

class P3D_API pCameraCtrl
{
	public:
		float zdelta;

	pCameraCtrl() :
		zdelta(0)
	{ }

	virtual ~pCameraCtrl()
	{ }

	virtual void check_input()=0;
	virtual void update()=0;
};

class P3D_API pCameraCtrlObs : public pCameraCtrl
{
	public:
		float movevel;
		float rotvel;
		float radius;

		pVector move;
		pVector rot;

	pCameraCtrlObs() :
		movevel(100.0f),
		rotvel(100.0f),
		radius(20.0f)
	{ }

	~pCameraCtrlObs()
	{ }

	void check_input();
	void update();
};

class P3D_API pCameraCtrlOrbit : public pCameraCtrl
{
	public:
		float movevel;
		float rotvel;

		pVector move;
		float movedist;
		pVector target,t,pos;
		pVector last_target,last_pos;
		float time;
		int moving;

	pCameraCtrlOrbit() :
		movevel(100.0f),
		rotvel(100.0f),
		move(0.0f),
		movedist(0.0f),
		target(0.0f),
		pos(1.0f),
		time(0),
		moving(0)
	{ }

	~pCameraCtrlOrbit()
	{ }

	void check_input();
	void update();
};


#endif
