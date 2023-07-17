#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pRORotor::init(bool active)
{
	m_bbox.max.vec(2);
	m_bbox.min.vec(-2);
}

void pRORotor::step(const float elapsed_time,const pMatrix& global)
{
	// calculates the new angle accordingly to elapsed time and angular velocity
	m_angle=fmodf(m_angle+m_angular_vel.w*elapsed_time,360.0f);
	
	// calculates a matrix that represents the angle-axis rotation
	m_mat_rot.set_rotation(m_angle,m_angular_vel);

	// calculates global transformation matrix
	pMatrix m=m_mat_rot*m_transform*global;

	pRenderObject::step(elapsed_time,m);
}

int pRORotor::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='f';
			pd->data=&m_angular_vel.w;
			pd->name="angular_velocity";
			pd->comment="Rotor's angular speed";
			break;
		case 1:
			pd->type='v';
			pd->data=&m_angular_vel;
			pd->name="axis";
			pd->comment="Rotor's rotation axis";
			break;
	}
	return 2;
}

void pRORotor::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 1:
			m_angular_vel.normalize();
		break;
	}
}

#endif
