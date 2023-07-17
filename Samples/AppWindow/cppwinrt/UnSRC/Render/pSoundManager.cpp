#include "pch.h"
#include "paralelo3d.h"

#ifdef P_SOUND

P3D_API pSoundManager *g_soundmanager=new pSoundManager;

pSoundManager::pSoundManager() :
	m_doppler_factor(1.0f),
	m_doppler_velocity(343.0f)
{
	alutInit(NULL,0);
}

pSoundManager::~pSoundManager()
{
	reset();
	alutExit();
}

void pSoundManager::reset()
{
	for(int i=0;i<m_sounds.num;i++)
		delete m_sounds[i];
	m_sounds.free();
}

int pSoundManager::load_sound(const char *sndfile)
{
	if(sndfile==0 || sndfile[0]==0 || sndfile[0]==' ')
		return -1;

	int i;
	for(i=0;i<m_sounds.num;i++)
		if(m_sounds.buf[i])
			if(!_stricmp(sndfile,(const char *)m_sounds.buf[i]->m_name))
				return i;

	pSound *snd=new pSound;

	char str[1024];
	strcpy(str,(g_render->app_path+sndfile));
	if(snd->load_sound(str)==0)
	{
		delete snd;
		return -1;
	}

	snd->m_name=sndfile;
	m_sounds.add(snd);
	m_soundid.add(snd->m_bufferid);

	return m_soundid.num-1;
}

void pSoundManager::set_listener(const float *pos,const float *dir,const float *up)
{
	float tmp[6]={dir[0],dir[1],dir[2],up[0],up[1],up[2]};
	alListenerfv(AL_POSITION,pos);
	alListenerfv(AL_ORIENTATION,tmp);
}

void pSoundManager::set_listener(const pVector& pos,const pVector& dir,const pVector& up)
{
	set_listener(&pos.x,&dir.x,&up.x);
}

void pSoundManager::update_doppler_factor()
{
	alDopplerFactor(m_doppler_factor);
}

void pSoundManager::update_doppler_velocity()
{
	alDopplerVelocity(m_doppler_velocity);
}

#endif