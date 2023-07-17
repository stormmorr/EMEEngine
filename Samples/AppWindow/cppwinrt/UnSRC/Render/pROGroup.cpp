#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROGroup::init(bool active)
{
	m_bbox.max.vec(2);
	m_bbox.min.vec(-2);
}

void pROGroup::draw()
{
	if (g_render->debug)
	{
		//*glMultMatrixf(&m_transform.mf[0]);
		//*glRotatef(-m_anim_rot.z,0,0,1);
		//*glRotatef(-m_anim_rot.y,0,1,0);
		//*glRotatef(-m_anim_rot.x,1,0,0);

		int i;
		if (m_animations)
		for( i=0;i<m_animations->ndummy;i++ )
			m_animations->dummy[i].draw();
	}
}

void pROGroup::step(const float elapsed_time,const pMatrix& global)
{
	pMatrix mat;

	if(m_animations && (-1<m_curr_anim && m_curr_anim<m_animations->ndummy))
	{
		pDummy *dummy=&m_animations->dummy[m_curr_anim];
		switch(m_command)
		{
			case CMD_PLAY:
				m_time+=elapsed_time;
			break;

			case CMD_STOP:
				m_time=0.0f;
			break;
		}
		
		pVector pos,rot;

		dummy->anim_pos_x.update(m_time,&pos.x);
		dummy->anim_pos_y.update(m_time,&pos.y);
		dummy->anim_pos_z.update(m_time,&pos.z);
		dummy->anim_rot_x.update(m_time,&rot.x);
		dummy->anim_rot_y.update(m_time,&rot.y);
		dummy->anim_rot_z.update(m_time,&rot.z);
		rot*=-PIUNDER180;

		mat.set_rotation(rot.x,pVector(1,0,0));
		mat.rotate(rot.y,pVector(0,1,0));
		mat.rotate(rot.z,pVector(0,0,1));
		
		mat.set_translate(pos);

		mat.rotate(m_anim_rot.x,pVector(1,0,0));
		mat.rotate(m_anim_rot.y,pVector(0,1,0));
		mat.rotate(m_anim_rot.z,pVector(0,0,1));
	}

	if (m_time_to_die>0)
	{
		m_time_to_die-=elapsed_time;
		if (m_time_to_die<=0)
		{
			m_time_to_die=0.001f;
			g_romanager->post_deactivate(m_id);
		}
	}

	pRenderObject::step(elapsed_time,mat*m_transform*global);
}

int pROGroup::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='m';
			pd->data=&m_animations;
			pd->name="animations";
			pd->comment="Animation .P3D file";
		break;

		case 1:
			pd->type='i';
			pd->data=&m_curr_anim;
			pd->name="curr_anim";
			pd->comment="Current animation";
		break;

		case 2:
			pd->type='i';
			pd->data=&m_command;
			pd->name="command";
			pd->comment="Animation command|Play|Pause|Stop";
		break;

		case 3:
			pd->type='v';
			pd->data=&m_anim_rot;
			pd->name="anim_rot";
			pd->comment="Animation rotation";
		break;

		case 4:
			pd->type='f';
			pd->data=&m_time_to_die;
			pd->name="time_to_die";
			pd->comment="Time to die (0 for keep alive)";
		break;
	}

	return 5;
}

#endif
