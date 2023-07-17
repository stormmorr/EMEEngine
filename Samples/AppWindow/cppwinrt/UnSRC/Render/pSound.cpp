#include "pch.h"
#include "paralelo3d.h"

#ifdef P_SOUND

pSound::pSound()
{ }

pSound::pSound(const pSound& in) :
	m_name(in.m_name),
	m_bufferid(in.m_bufferid)
{ }
		
pSound::~pSound()
{
	alDeleteBuffers(1,&m_bufferid);
}

void pSound::operator=(const pSound& in)
{
	m_name=in.m_name;
	m_bufferid=in.m_bufferid;
}

int pSound::load_sound(char *file)
{
	int ret=0;
	m_name=file;
	char *c=strrchr(file,'.');
	if((unsigned int)(c-file)==strlen(file)-4)
	{
		if(!_stricmp(c,".wav"))
			ret=load_WAV(file);
	}
	return ret;
}
		
int pSound::load_WAV(char *file)
{
	// generate buffer
	alGetError();
	alGenBuffers(1,&m_bufferid);
	if(alGetError()!=AL_NO_ERROR)
		return 0;
	
	// load wav file
	alutLoadWAVFile(file,&m_format,&m_data,&m_size,&m_freq,&m_looping);
	if(alGetError()!=AL_NO_ERROR)
	{
		alDeleteBuffers(1,&m_bufferid);
		return 0;
	}
	
	// copy data into AL buffer
	alBufferData(m_bufferid,m_format,m_data,m_size,m_freq);
	if(alGetError()!=AL_NO_ERROR)
	{
		alDeleteBuffers(1,&m_bufferid);
		return 0;
	}

	// unload data
	alutUnloadWAV(m_format,m_data,m_size,m_freq);
	if(alGetError()!=AL_NO_ERROR)
	{
		alDeleteBuffers(1,&m_bufferid);
		return 0;
	}

	return 1;
}

#endif