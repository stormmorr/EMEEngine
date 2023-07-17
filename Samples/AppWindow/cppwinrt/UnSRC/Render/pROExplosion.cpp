#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROExplosion::step(const float elapsed_time,const pMatrix& global)
{
	m_delay-=elapsed_time;
	if (m_delay<=0)
	{
		int i;
		pMatrix m=m_transform*global;

		for( i=0;i<m_child.num;i++ )
			if (m_child.buf[i]->m_flags&P_ROFLAGS_ENABLED)
				m_child.buf[i]->m_transform*=m;

		explode();
		release_child();
		g_romanager->post_deactivate(m_id);
	}
}

void pROExplosion::explode()
{
	pVector dir;
	pVector rotdir;
	pROExplodeObject *active;
	
	for(int i=0;i<m_child.num;i++)
	{
		if(m_child[i]->m_type==TYPE_RO_EXPLODE_OBJECT)
		{
			// calculates the explosion direction
			dir=m_child[i]->m_transform_global.get_translate()-m_explode_pos;
			if(	fabsf(dir.x-0.0f)<0.001f 
				&& fabsf(dir.y-0.0f)<0.001f 
				&& fabsf(dir.z-0.0f)<0.001f)
			{
				if (m_angle_x==0 && m_angle_y==0)
					dir.vec(FRAND,FRAND,FRAND);
				else 
					dir.vec(FRAND*m_angle_x,FRAND*m_angle_y,1);
			}
			dir.normalize();

			// find a rotation vector orthogonal to dir (code extracted from pMatrix::align_z)
			if(fabsf(dir.z)>=0.99f)
			{
				rotdir.x=-dir.y*dir.x;
				rotdir.y=1-dir.y*dir.y;
				rotdir.z=-dir.y*dir.z;

				rotdir.normalize();
			}
			else 
			{
				rotdir.x=-dir.z*dir.x;
				rotdir.y=-dir.z*dir.y;
				rotdir.z=1.0f-dir.z*dir.z;

				rotdir.normalize();
			}

			// activates current object
			active=(pROExplodeObject*)m_child[i];

			// calculates the linear velocity vector of the active object
			active->m_lin_vel=dir*(m_speed+m_speed_var*FRAND);

			// calculates the angular velocity vector of the active object
			active->m_ang_vel=rotdir;
			active->m_ang_vel.w=m_ang_speed+m_ang_speed_var*FRAND;
		}
	}
}

int pROExplosion::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
		{
			pd->type='f';
			pd->data=&m_angle_x;
			pd->name="explode_angle_x";
		}
		break;
		case 1:
		{
			pd->type='f';
			pd->data=&m_angle_y;
			pd->name="explode_angle_y";
		}
		break;
		case 2:
		{
			pd->type='f';
			pd->data=&m_speed;
			pd->name="linear_speed";
		}
		break;
		case 3:
		{
			pd->type='f';
			pd->data=&m_speed_var;
			pd->name="linear_speed_var";
		}
		break;
		case 4:
		{
			pd->type='f';
			pd->data=&m_ang_speed;
			pd->name="angular_speed";
		}
		break;
		case 5:
		{
			pd->type='f';
			pd->data=&m_ang_speed_var;
			pd->name="angular_speed_var";
		}
		break;
		case 6:
		{
			pd->type='v';
			pd->data=&m_explode_pos;
			pd->name="explode_position";
		}
		break;
		case 7:
		{
			pd->type='f';
			pd->data=&m_delay;
			pd->name="delay";
		}
		break;
	}

	return 8;
}

#endif
