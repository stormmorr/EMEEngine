#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ
#ifdef P_SOUND

void pROSound::process_sound()
{
	if(is_valid())
	{
		switch(m_command)
		{
			case CMD_PLAY:
				alSourcei(m_source_sound,AL_LOOPING,AL_TRUE);
				alSourcePlay(m_source_sound);
			break;

			case CMD_PLAY_ONCE:
				alSourcei(m_source_sound,AL_LOOPING,AL_FALSE);
				alSourcePlay(m_source_sound);
			break;

			case CMD_PAUSE:
				alSourcePause(m_source_sound);
			break;

			case CMD_STOP:
				alSourceStop(m_source_sound);
				alSourceRewind(m_source_sound);
			break;
		}
	}
}

pROSound::~pROSound()
{
	if(m_source)
	{
		alSourceStop(m_source_sound);
		alDeleteSources(1,&m_source_sound);
	}
}
		
void pROSound::init(bool active)
{
	m_bbox.max.vec(2.0f);
	m_bbox.min.vec(-2.0f);

	if(active)
	{
		alGenSources(1,&m_source_sound);
		if(is_valid())
		{
			alSourcef(m_source_sound,AL_REFERENCE_DISTANCE,m_reference_dist);
			alSourcef(m_source_sound,AL_GAIN,m_gain);
			alSourcef(m_source_sound,AL_CONE_INNER_ANGLE,m_cone_inner_angle);
			alSourcef(m_source_sound,AL_PITCH,get_pitch());
			alSourcei(m_source_sound,AL_BUFFER,g_soundmanager->m_soundid[m_sounds[m_cur_sound]]);
		}
		process_sound();
	}
}

void pROSound::step(const float elapsed_time,const pMatrix& global)
{
	pMatrix m=m_transform*global;

	if(is_valid())
	{
		if(m_die && m_command==CMD_PLAY_ONCE)
		{
			int state;
			alGetSourcei(m_source_sound,AL_SOURCE_STATE,&state);
			if(state==AL_STOPPED)
				g_romanager->post_deactivate(m_id);
		}

		if(m_global)
			alSourcefv(m_source_sound,AL_POSITION,&(g_render->camera.pos.x));
		else
			alSourcefv(m_source_sound,AL_POSITION,&(m.get_translate().x));
		
		if(m_directional)
			alSourcefv(m_source_sound,AL_DIRECTION,&(m.get_column3(2).x));
		else
			alSource3f(m_source_sound,AL_DIRECTION,0.0f,0.0f,0.0f);

		alSource3f(m_source_sound,AL_VELOCITY,0.0f,0.0f,0.0f);
		if(m_velocity)
		{
			if(elapsed_time>0.0001f)
			{
				pVector vel(m.get_translate()-m_transform_global.get_translate());
				vel/=elapsed_time;
				float len=vel.length();
				if (len>0.0001f)
				{
					vel/=len;
					len*=g_soundmanager->m_doppler_factor;
					if (len>g_soundmanager->m_doppler_velocity)
						len=g_soundmanager->m_doppler_velocity-1.0f;
					vel*=len;
					alSource3f(m_source_sound,AL_VELOCITY,vel.x,vel.y,vel.z);
				}
			}
		}
	}

	pRenderObject::step(elapsed_time,m);
}

void pROSound::draw()
{ }

int pROSound::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type=-'h';
			pd->data=&m_sounds;
			pd->name="sounds";
			pd->comment="Sound files";
		break;

		case 1:
			pd->type='i';
			pd->data=&m_command;
			pd->name="command";
			pd->comment="Sound command|Play|Play Once|Pause|Stop";
		break;

		case 2:
			pd->type='f';
			pd->data=&m_reference_dist;
			pd->name="ref_dist";
			pd->comment="The distance at which the listener will experience gain";
		break;

		case 3:
			pd->type='f';
			pd->data=&m_gain;
			pd->name="gain";
			pd->comment="Volume control";
		break;

		case 4:
			pd->type='b';
			pd->data=&m_directional;
			pd->name="directional";
			pd->comment="Directional/Non-Directional flag";
		break;

		case 5:
			pd->type='b';
			pd->data=&m_global;
			pd->name="global";
			pd->comment="Global/Local flag";
		break;

		case 6:
			pd->type='b';
			pd->data=&m_die;
			pd->name="die";
			pd->comment="Die or not";
		break;

		case 7:
			pd->type='b';
			pd->data=&m_velocity;
			pd->name="velocity";
			pd->comment="Turn on/off calculus of velocity";
		break;

		case 8:
			pd->type='f';
			pd->data=&m_cone_inner_angle;
			pd->name="cone_inner_angle";
			pd->comment="Cone inner angle";
		break;

		case 9:
			pd->type='f';
			pd->data=&m_pitch;
			pd->name="pitch";
			pd->comment="Pitch value";
		break;

		case 10:
			pd->type='f';
			pd->data=&m_pitch_min_range;
			pd->name="pitch_min_range";
			pd->comment="Minimum range of pitch";
		break;
		
		case 11:
			pd->type='f';
			pd->data=&m_pitch_max_range;
			pd->name="pitch_max_range";
			pd->comment="Maximum range pitch";
		break;

		case 12:
			pd->type='i';
			pd->data=&m_cur_sound;
			pd->name="cur_sound";
			pd->comment="Current sound";
		break;
	}

	return 13;
}

void pROSound::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		{
			if(is_valid())
			{
				alSourceStop(m_source_sound);
				alSourcei(m_source_sound,AL_BUFFER,g_soundmanager->m_soundid[m_sounds[m_cur_sound]]);
				if(m_command==CMD_PLAY)
					alSourcePlay(m_source_sound);
			}
		}
		break;

		case 1:
		{
			process_sound();
		}
		break;

		case 2:
		{
			if(is_valid())
				alSourcef(m_source_sound,AL_REFERENCE_DISTANCE,m_reference_dist);
		}
		break;

		case 3:
		{
			if(is_valid())
				alSourcef(m_source_sound,AL_GAIN,m_gain);
		}
		break;

		case 8:
		{
			if(is_valid())
				alSourcef(m_source_sound,AL_CONE_INNER_ANGLE,m_cone_inner_angle);
		}
		break;

		case 9:
		case 10:
		case 11:
		{
			if(is_valid())
			{
				float pitch=get_pitch();
				alSourcef(m_source_sound,AL_PITCH,pitch>0.0f?pitch:0.1f);
			}
		}
		break;

		case 12:
		{
			if(m_cur_sound<0)
				alSourceStop(m_source_sound);
			else
			{
				m_cur_sound=m_cur_sound%m_sounds.num;			
				if(is_valid())
				{
					alSourceStop(m_source_sound);
					alSourcei(m_source_sound,AL_BUFFER,g_soundmanager->m_soundid[m_sounds[m_cur_sound]]);
					if(m_command==CMD_PLAY)
						alSourcePlay(m_source_sound);
				}
			}
		}
		break;
	}
}

#endif
#endif
